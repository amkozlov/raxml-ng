#include "ModelTest.hpp"

#include <cstdint>
#include <iomanip>
#include <memory>
#include <mpi.h>
#include <mutex>
#include <sstream>
#include <stdexcept>

#include <list>
#include <optional>

#include "ModelScheduler.hpp"
#include "ModelDefinitions.hpp"
#include "../ICScoreCalculator.hpp"
#include "corax/tree/treeinfo.h"

static thread_local std::unique_ptr<std::ofstream> thread_log;
#define LOG_THREAD_TS (*thread_log << std::setprecision(19) << global_timer().elapsed_seconds() << " MT Thread " << ParallelContext::thread_id())
#define LOG_THREAD (*thread_log)



Options modify_options(const Options &other) {
    Options options(other);
    options.lh_epsilon = 0.01; // Use same LH-epsilon as ModelTest-NG
    options.brlen_linkage = CORAX_BRLEN_LINKED; // Partitions are computed in isolation, no need for scalers

    return options;
}

const std::vector<string> get_matrix_names(const DataType datatype) {
    switch(datatype) {
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

vector<candidate_model_t> ModelTest::generate_candidate_model_names(const DataType &dt) const {
    vector<candidate_model_t> candidate_models;
    check_supported_datatype(dt);

    const auto freerate_cmin = options.free_rate_min_categories;
    const auto freerate_cmax = options.free_rate_max_categories;
    const auto gamma_category_count = 4;

    for (const auto &subst_model: get_matrix_names(dt)) {
        for (const auto &frequency_type: default_frequency_type) {
            for (const auto &rate_heterogeneity: default_rate_heterogeneity) {
                if (rate_heterogeneity == rate_heterogeneity_type::FREE_RATE) {
                    // If category range is not positive, skip freerate models
                    if (freerate_cmin == 0 && freerate_cmax == 0) {
                        continue;
                    }

                    for (unsigned int c = freerate_cmin; c < freerate_cmax; ++c) {
                        candidate_models.emplace_back(dt, subst_model, frequency_type, rate_heterogeneity, c);
                    }
                } else if (rate_heterogeneity == rate_heterogeneity_type::GAMMA || rate_heterogeneity ==
                        rate_heterogeneity_type::INVARIANT_GAMMA) {
                    candidate_models.emplace_back(dt, subst_model, frequency_type, rate_heterogeneity,
                                                gamma_category_count);
                } else {
                    candidate_models.emplace_back(dt, subst_model, frequency_type, rate_heterogeneity);
                }
            }
        }
    }

    return candidate_models;
}


ModelTest::ModelTest(const Options &original_options, const PartitionedMSA &msa, const Tree &tree, const IDVector &tip_msa_idmap,
                    const PartitionAssignment &part_assign)
    : options(modify_options(original_options)), optimizer(options), msa(msa), tree(tree),
                                            tip_msa_idmap(tip_msa_idmap), part_assign(part_assign) { }


ExecutionStatus execution_status; // shared across all threads.


/** Estimate the ideal number of threads to optimize a given partition.
 *
 * We cannot reuse the existing ResourceEstimator, because it estimates the
 * number of cores across _all_ partitions, whereas we need the estimated
 * number of cores _per_ partition.
 */
size_t estimate_cores(const Options &options, const PartitionInfo &pinfo, const candidate_model_t &candidate_model,
                      EvaluationPriority priority) {
    RAXML_UNUSED(options);

    const auto taxon_clv_size = pinfo.length() * candidate_model.rate_heterogeneity.category_count * pinfo.model().
                                num_states();

    /* cf. `StaticResourceEstimator::compute_estimates`
     * response for high priority tasks, throughput for all others
     */
    size_t elems_per_core = priority == EvaluationPriority::HIGH ? 4000 : 80000;

    const size_t naive_cores = CORAX_MAX(round(static_cast<double>(taxon_clv_size) / elems_per_core), 1.);
    if (naive_cores <= 8)
        elems_per_core /= 4. - log2(naive_cores);
    else
        elems_per_core *= log2(naive_cores) - 2;

    return CORAX_MAX(round(static_cast<double>(taxon_clv_size) / elems_per_core), 1.);
}

vector<Model> ModelTest::optimize_model() {
    if (options.log_level == LogLevel::debug) {
        thread_log.reset(new std::ofstream(options.outfile_prefix + ".raxml.modeltest.rank" + std::to_string(ParallelContext::rank_id()) + ".thread" + std::to_string(ParallelContext::thread_id()) + ".log"));
    } else {
        thread_log.reset(new std::ofstream("/dev/null"));
    }
    const bool enable_rhas_heuristic = std::getenv("MODELTEST_RHAS_NOSKIP") == nullptr;
    const bool enable_freerate_heuristic = std::getenv("MODELTEST_FREERATE_NOSKIP") == nullptr;

    if (ParallelContext::group_master_thread()) {
        // TODO: support multiple partitions with mixed datatypes
        auto candidate_models = generate_candidate_model_names(msa.part_info(0).model().data_type());
        execution_status.initialize(candidate_models, msa, options, estimate_cores, enable_rhas_heuristic,
                                    enable_freerate_heuristic);
    }

    // sync ALL threads across ALL workers
    ParallelContext::global_barrier();

    PartitionModelEvaluation *evaluation = nullptr;

    const auto default_precision = std::cout.precision();
    cout << std::setprecision(19);

    while (true) {
        const auto t_start = global_timer().elapsed_seconds();
        evaluation = execution_status.get_next_model();

        if (evaluation == nullptr) {
            break;
        }

        LOG_THREAD_TS << " scheduled to work on " << evaluation->candidate_model().descriptor() << " as thread " << evaluation->thread_id() + 1 << " out of " << evaluation->proposed_thread_count() << endl;

        evaluation->wait();

        const auto scheduling_overhead = global_timer().elapsed_seconds() - t_start;

        /* If a heuristic applies by now, just continue with the next candidate */
        if (evaluation->get_status() == EvaluationStatus::ABORTED)
            continue;

        LOG_THREAD_TS << " begins work after waiting for " << 1e3 * scheduling_overhead << " milliseconds." << endl;

        const auto &model_descriptor = evaluation->candidate_model().descriptor();

        PartitionAssignment assignment;

        {
            /* Assign a fair share of sites to all threads, with the higher thread ids taking care of the remainder */

            assert(evaluation->thread_id() < evaluation->assigned_threads());
            const auto n = msa.part_info(evaluation->partition_index()).length();
            const auto fair_share = n / evaluation->assigned_threads();

            const auto remainder_tid = evaluation->assigned_threads() - n % evaluation->assigned_threads();
            const bool remainder_assigned = evaluation->thread_id() >= remainder_tid;
            const auto assigned_sites = remainder_assigned ? fair_share + 1 : fair_share;

            size_t start_index;
            if (remainder_assigned) {
                start_index = remainder_tid * fair_share + (evaluation->thread_id() - remainder_tid) * (fair_share + 1);
            } else {
                start_index = evaluation->thread_id() * fair_share;
            }
            assignment.assign_sites(0, start_index, assigned_sites, evaluation->candidate_model().rate_heterogeneity.category_count);
            LOG_THREAD_TS << " assigned sites offset=" << start_index << " length=" << assigned_sites << " total_sites=" << n << endl;
        }


        evaluation->barrier();
        Model model(model_descriptor);
        assign(model, msa.part_info(evaluation->partition_index()).stats());
        TreeInfo treeinfo(options, tree, msa, tip_msa_idmap, assignment, evaluation->partition_index(), model);

        treeinfo.custom_reduce(evaluation, PartitionModelEvaluation::reduce);
        optimizer.optimize_model(treeinfo);


        if (evaluation->thread_id() == 0) {
            // Retrieve values from optimized partition.
            // The partition id is always 0, since our treeinfo only contains a single partition
            assign(model, treeinfo, 0); 

            const double partition_loglh = treeinfo.pll_treeinfo().partition_loglh[0];
            const size_t free_params = model.num_free_params() + treeinfo.tree().num_branches();
            const size_t sample_size = msa.part_info(evaluation->partition_index()).stats().site_count;
            ICScoreCalculator ic_score_calculator(free_params, sample_size);

            EvaluationResult partition_results {model, partition_loglh, ic_score_calculator.all(partition_loglh)};

            const auto t0 = global_timer().elapsed_seconds();
            execution_status.update_result(*evaluation, std::move(partition_results));
            const auto t1 = global_timer().elapsed_seconds();

            LOG_THREAD_TS << " announced results in " << 1e3 * (t1 - t0) << " milliseconds." << endl;
        }

        LOG_THREAD_TS << " evaluation of " << evaluation->candidate_model().descriptor() << " concluded." << endl;
    }

    cout << std::setprecision(default_precision);

    // sync ALL threads across ALL workers
    ParallelContext::global_barrier();

    vector<Model> best_model_per_part;
    if (ParallelContext::master()) {
        auto xml_fname = options.output_fname("modeltest.xml");
        fstream xml_stream(xml_fname, std::ios::out);

        print_xml(xml_stream, execution_status.get_evaluations());
        xml_stream.close();

        LOG_DEBUG << "XML model selection file written to " << xml_fname << endl;




        auto bestmodel_fname = options.output_fname("modeltest.bestModel");
        fstream bestmodel_stream(bestmodel_fname, std::ios::out);

        LOG_INFO << endl << "Best model(s):" << endl;
        const auto results = execution_status.collect_finished_results_by_partition();
        for (auto p = 0U; p < msa.part_count(); ++p) {
            auto bic_ranking = rank_by_score(results.at(p), InformationCriterion::bic);
            const auto &best_model = results.at(p).at(bic_ranking.at(0));
            logger().logstream(LogLevel::result, LogScope::thread) << "Partition #" << p << ": " << best_model.model.to_string()
                     << " (LogLH = " << FMT_LH(best_model.partition_loglh)
                     << "  BIC = "  << FMT_LH(best_model.ic_criteria.at(InformationCriterion::bic))
                     << ")" << endl;

            bestmodel_stream << best_model.model.to_string(true, logger().precision(LogElement::model)) << ", " << msa.part_info(p).name() 
                << " = " << msa.part_info(p).range_string() << endl;


            best_model_per_part.emplace_back(best_model.model);
        }
    }

    thread_log->close();

    if (ParallelContext::group_master_thread()) {
        execution_status.finalize();
    }


    return best_model_per_part;
}

vector<size_t> ModelTest::rank_by_score(const vector<EvaluationResult> &results,
                                        InformationCriterion ic) {
    std::vector<size_t> ranking(results.size(), 0);
    std::iota(ranking.begin(), ranking.end(), 0);

    std::sort(ranking.begin(), ranking.end(),
              [ic, &results](const size_t &a, const size_t &b) {
                  return results.at(a).ic_criteria.at(ic) <
                         results.at(b).ic_criteria.at(ic);
              });

    return ranking;
}


vector<double> transform_delta_to_weight(const vector<double> &deltas) {
    vector<double> weights(deltas.size());
    weights.clear();

    for (const double &delta: deltas) {
        weights.push_back(std::exp(-delta / 2));
    }

    // normalize
    const double fac = 1 / std::accumulate(weights.begin(), weights.end(), 0.0);

    for (double &w: weights) {
        w *= fac;
    }

    return weights;
}


void ModelTest::print_xml(ostream &os, const vector<PartitionModelEvaluation> &results) {
    os << setprecision(17);
    os << "<modeltestresults>" << endl;

    for (const auto &evaluation: results) {
        os << "<model partition=\"" << evaluation.partition_index()
                << "\" name=\"" << evaluation.candidate_model().descriptor()
                << "\" status=\"";
        switch (evaluation.get_status()) {
            case EvaluationStatus::WAITING:
                os << "WAITING";
                break;
            case EvaluationStatus::RUNNING:
                os << "RUNNING";
                break;
            case EvaluationStatus::ABORTED:
                os << "ABORTED";
                break;
            case EvaluationStatus::FINISHED:
                os << "FINISHED";
                break;
        }

        if (evaluation.get_status() == EvaluationStatus::FINISHED) {
            const auto &result = evaluation.get_result();
            os << "\" lnL=\"" << result.partition_loglh
                    << "\" score-bic=\"" << result.ic_criteria.at(InformationCriterion::bic)
                    << "\" score-aic=\"" << result.ic_criteria.at(InformationCriterion::aic)
                    << "\" score-aicc=\"" << result.ic_criteria.at(InformationCriterion::aicc)
                    << "\" free-params=\"" << result.model.num_free_params() << "\" />" << endl;
        } else {
            os << "\" />" << endl;
        }
    }

    os << "</modeltestresults>" << endl;
}
