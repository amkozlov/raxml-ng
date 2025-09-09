#include "ModelTest.hpp"

#include <iomanip>
#include <memory>

#include "../ICScoreCalculator.hpp"
#include "Heuristics.hpp"
#include "ModelDefinitions.hpp"
#include "ModelScheduler.hpp"
#include "corax/tree/treeinfo.h"

static thread_local std::unique_ptr<std::ofstream> thread_log;
#define LOG_THREAD_TS                                                                                                  \
  (*thread_log << std::setprecision(19) << global_timer().elapsed_seconds() << " MT Thread "                           \
               << ParallelContext::thread_id())
#define LOG_THREAD (*thread_log)

Options modify_options(const Options &other)
{
  Options options(other);
  options.lh_epsilon = 0.01;                  // Use same LH-epsilon as ModelTest-NG
  options.brlen_linkage = CORAX_BRLEN_LINKED; // Partitions are computed in isolation, no need for scalers

  return options;
}

const std::vector<string> get_matrix_names(const DataType datatype)
{
  switch (datatype) {
  case DataType::dna:
    return dna_substitution_matrix_names;
  case DataType::protein:
    return aa_substitution_matrix_names;
  case DataType::binary:
    return std::vector<string>({"BIN"});

  case DataType::autodetect:
  case DataType::multistate:
  case DataType::genotype10:
  case DataType::genotype16:
    throw unsupported_datatype_error();
  }

  return {};
}

vector<ModelDescriptor> ModelTest::generate_candidate_model_names(const DataType &dt) const
{
  vector<ModelDescriptor> candidate_models;
  check_supported_datatype(dt);

  const auto freerate_cmin = options.free_rate_min_categories;
  const auto freerate_cmax = options.free_rate_max_categories;
  const auto gamma_category_count = 4;

  const auto subst_models =
      options.modeltest_subst_models.empty() ? get_matrix_names(dt) : options.modeltest_subst_models;

  for (const auto &subst_model : subst_models) {
    for (const auto &frequency_type : default_frequency_type) {
      for (const auto &rate_heterogeneity : options.modeltest_rhas) {
        switch (rate_heterogeneity) {
        case RateHeterogeneityType::FREE_RATE:
        case RateHeterogeneityType::INVARIANT_FREE_RATE:
          // If category range is not positive, skip freerate models
          if (freerate_cmin == 0 && freerate_cmax == 0) {
            continue;
          }

          for (unsigned int c = freerate_cmin; c <= freerate_cmax; ++c) {
            candidate_models.emplace_back(dt, subst_model, frequency_type, rate_heterogeneity, c);
          }
          break;
        case RateHeterogeneityType::GAMMA:
        case RateHeterogeneityType::INVARIANT_GAMMA:
          candidate_models.emplace_back(dt, subst_model, frequency_type, rate_heterogeneity, gamma_category_count);
          break;
        default:
          candidate_models.emplace_back(dt, subst_model, frequency_type, rate_heterogeneity);
          break;
        }
      }
    }
  }

  return candidate_models;
}

/** Estimate the number of threads to optimize a given partition.
 *
 * We cannot reuse the existing ResourceEstimator, because it estimates the
 * number of cores across _all_ partitions, whereas we need the estimated
 * number of cores _per_ partition.
 */
size_t modeltest_estimate_cores(const Options &options, const PartitionInfo &pinfo,
                                const ModelDescriptor &candidate_model, EvaluationPriority priority)
{
  RAXML_UNUSED(options);

  const auto taxon_clv_size =
      pinfo.length() * candidate_model.rate_heterogeneity.category_count * pinfo.model().num_states();

  /* cf. `StaticResourceEstimator::compute_estimates`
   * response for high priority tasks, throughput for all others
   */
  size_t elems_per_core = priority > EvaluationPriority::NORMAL ? 4000 : 80000;

  const size_t naive_cores = CORAX_MAX(round(static_cast<double>(taxon_clv_size) / elems_per_core), 1.);
  if (naive_cores <= 8)
    elems_per_core /= 4. - log2(naive_cores);
  else
    elems_per_core *= log2(naive_cores) - 2;

  return CORAX_MAX(round(static_cast<double>(taxon_clv_size) / elems_per_core), 1.);
}

ModelTest::ModelTest(const Options &original_options, const PartitionedMSA &msa, const Tree &tree,
                     const IDVector &tip_msa_idmap, CheckpointManager &checkpoint_manager)
    : options(modify_options(original_options)), optimizer(options), checkpoint_manager(checkpoint_manager), msa(msa),
      tree(tree), tip_msa_idmap(tip_msa_idmap),
      model_scheduler(generate_candidate_model_names(msa.part_info(0).model().data_type()), msa, options,
                      checkpoint_manager, modeltest_estimate_cores)
{
}

vector<Model> ModelTest::optimize_model()
{
  if (options.log_level == LogLevel::debug && !options.outfile_prefix.empty()) {
    thread_log.reset(new std::ofstream(options.outfile_prefix + ".raxml.modeltest.rank" +
                                       std::to_string(ParallelContext::rank_id()) + ".thread" +
                                       std::to_string(ParallelContext::thread_id()) + ".log"));
  } else {
    thread_log.reset(new std::ofstream("/dev/null"));
  }

  // sync ALL threads across ALL workers
  ParallelContext::global_barrier();

  const auto default_precision = std::cout.precision();
  cout << std::setprecision(19);

  while (true) {
    ModelEvaluator *evaluator;
    const auto t_start = global_timer().elapsed_seconds();
    evaluator = model_scheduler.get_next_model();

    if (evaluator == nullptr) {
      break;
    }

    LOG_THREAD_TS << " scheduled to work on " << evaluator->candidate_model().descriptor() << " as thread "
                  << evaluator->thread_id() + 1 << " out of " << evaluator->proposed_thread_count() << endl;

    evaluator->wait();

    const auto scheduling_overhead = global_timer().elapsed_seconds() - t_start;

    /* If a heuristic applies by now, just continue with the next candidate */
    if (evaluator->get_status() == EvaluationStatus::SKIPPED)
      continue;

    LOG_THREAD_TS << " begins work after waiting for " << 1e3 * scheduling_overhead << " milliseconds." << endl;

    const auto &model_descriptor = evaluator->candidate_model().descriptor();

    PartitionAssignment assignment;
    {
      /* Assign a fair share of sites to all threads, with the higher thread ids taking care of the remainder */

      assert(evaluator->thread_id() < evaluator->assigned_threads());
      const auto n = msa.part_info(evaluator->partition_index()).length();
      const auto fair_share = n / evaluator->assigned_threads();

      const auto remainder_tid = evaluator->assigned_threads() - n % evaluator->assigned_threads();
      const bool remainder_assigned = evaluator->thread_id() >= remainder_tid;
      const auto assigned_sites = remainder_assigned ? fair_share + 1 : fair_share;

      size_t start_index;
      if (remainder_assigned) {
        start_index = remainder_tid * fair_share + (evaluator->thread_id() - remainder_tid) * (fair_share + 1);
      } else {
        start_index = evaluator->thread_id() * fair_share;
      }
      assignment.assign_sites(0, start_index, assigned_sites,
                              evaluator->candidate_model().rate_heterogeneity.category_count);
      LOG_THREAD_TS << " assigned sites offset=" << start_index << " length=" << assigned_sites << " total_sites=" << n
                    << endl;
    }

    evaluator->barrier();
    const Model &model = evaluator->get_result().model;
    TreeInfo treeinfo(options, tree, msa, tip_msa_idmap, assignment, evaluator->partition_index(), model);

    treeinfo.custom_reduce(evaluator, ModelEvaluator::reduce);
    optimizer.optimize_model(treeinfo);
    evaluator->barrier();

    if (evaluator->thread_id() == 0) {
      // Retrieve values from optimized partition.
      // The partition id is always 0, since our treeinfo only contains a single partition
      Model optimized_model(model.to_string());
      assign(optimized_model, treeinfo, 0);

      const double loglh = treeinfo.pll_treeinfo().partition_loglh[0];
      const size_t free_params = model.num_free_params() + treeinfo.tree().num_branches();
      const size_t sample_size = msa.part_info(evaluator->partition_index()).stats().site_count;
      ICScoreCalculator ic_score_calculator(free_params, sample_size);

      double ic_score = ic_score_calculator.compute(options.model_selection_criterion, loglh);

      const auto t0 = global_timer().elapsed_seconds();
      model_scheduler.update_result(*evaluator, ModelEvaluation{std::move(optimized_model), loglh, ic_score});
      const auto t1 = global_timer().elapsed_seconds();

      LOG_THREAD_TS << " evaluation of " << evaluator->candidate_model().descriptor()
                    << " finished, IC = " << evaluator->get_result().ic_score
                    << ", LogLH = " << evaluator->get_result().loglh
                    << ", aborted = " << (evaluator->get_status() == EvaluationStatus::SKIPPED) << std::endl;
      LOG_THREAD_TS << " announced results in " << 1e3 * (t1 - t0) << " milliseconds." << endl;
    }

    LOG_THREAD_TS << " evaluation of " << model_descriptor << " concluded." << endl;
  }

  cout << std::setprecision(default_precision);

  // sync ALL threads across ALL workers
  const auto t0 = global_timer().elapsed_seconds();
  ParallelContext::global_barrier();
  const auto t1 = global_timer().elapsed_seconds();
  LOG_THREAD_TS << " final synchronization took " << 1e3 * (t1 - t0) << " milliseconds." << endl;

  if (ParallelContext::local_group_id() == 0 && ParallelContext::group_master_thread()) {
    model_scheduler.fetch_global_results();
  }

  vector<Model> best_model_per_part;
  if (ParallelContext::master()) {
    auto xml_fname = options.output_fname("modeltest.xml");
    fstream xml_stream(xml_fname, std::ios::out);
    model_scheduler.print_xml(xml_stream);
    xml_stream.close();

    LOG_DEBUG << "XML model selection file written to " << xml_fname << endl;

    auto bestmodel_fname = options.output_fname("modeltest.bestModel");
    fstream bestmodel_stream(bestmodel_fname, std::ios::out);

    LOG_INFO << endl << "Best model(s):" << endl;
    const auto results = model_scheduler.collect_finished_results_by_partition();
    for (auto p = 0U; p < msa.part_count(); ++p) {
      auto bic_ranking = rank_by_score(results.at(p));
      const auto &best_model = results.at(p).at(bic_ranking.at(0));
      logger().logstream(LogLevel::result, LogScope::thread)
          << "Partition #" << p << ": " << best_model->model.to_string() << " (LogLH = " << FMT_LH(best_model->loglh)
          << "  BIC = " << FMT_LH(best_model->ic_score) << ")" << endl;

      bestmodel_stream << best_model->model.to_string(true, logger().precision(LogElement::model)) << ", "
                       << msa.part_info(p).name() << " = " << msa.part_info(p).range_string() << endl;

      best_model_per_part.emplace_back(best_model->model);
    }
  }

  thread_log->close();

  return best_model_per_part;
}

vector<size_t> ModelTest::rank_by_score(const vector<ModelEvaluation const *> &results)
{
  std::vector<size_t> ranking(results.size(), 0);
  std::iota(ranking.begin(), ranking.end(), 0);

  std::sort(ranking.begin(), ranking.end(),
            [&results](const size_t &a, const size_t &b) { return results.at(a)->ic_score < results.at(b)->ic_score; });

  return ranking;
}

unsigned int ModelTest::recommended_thread_count() const { return model_scheduler.recommended_thread_count(); }
