
#include "ModelTest.hpp"

#include <iomanip>
#include <memory>
#include <mutex>
#include <sstream>
#include <stdexcept>

#include <list>
#include <optional>

#include "FreerateHeuristic.hpp"
#include "ModelDefinitions.hpp"
#include "../ICScoreCalculator.hpp"
#include "RHASHeuristic.hpp"
#include "corax/tree/treeinfo.h"

static thread_local std::unique_ptr<std::ofstream> thread_log;
#define LOG_THREAD_TS (*thread_log << std::setprecision(19) << global_timer().elapsed_seconds() << " MT Thread " << ParallelContext::thread_id())



Options modify_options(const Options &other) {
Options options(other);
options.lh_epsilon = 0.01; // Use same LH-epsilon as ModelTest-NG
options.brlen_linkage = CORAX_BRLEN_LINKED; // Partitions are computed in isolation, no need for scalers

return options;
}


thread_local unsigned int PartitionModelEvaluation::_thread_id = 0;
thread_local int PartitionModelEvaluation::_barrier_mycycle = 0;
PartitionModelEvaluation::PartitionModelEvaluation(candidate_model_t &candidate_model,
                                                   size_t partition_index, EvaluationPriority priority,
                                                   const size_t proposed_thread_count)
    : _proposed_thread_count{proposed_thread_count},
      _candidate_model{candidate_model},
      _partition_index{partition_index},
      _priority{priority}, status{EvaluationStatus::WAITING},
      _barrier_counter(0),
      _barrier_proceed(0),
      _assigned_threads(0),
      _reduce_buffer(_proposed_thread_count * 2, 0.),
      _result() {
}

bool PartitionModelEvaluation::join_team() {
    if (status != EvaluationStatus::WAITING)
        return false;

    assert(_assigned_threads < _proposed_thread_count);

    _thread_id = _assigned_threads++;
    _barrier_mycycle = 0;

    if (_assigned_threads == _proposed_thread_count) {
        status = EvaluationStatus::RUNNING;
    }


    return true;
}

void PartitionModelEvaluation::abort() {
    status = EvaluationStatus::ABORTED;
}

EvaluationStatus PartitionModelEvaluation::wait() const {
    while (status == EvaluationStatus::WAITING) {
    }

    return status;
}

void PartitionModelEvaluation::store_result(EvaluationResult &&result) {
    if (status != EvaluationStatus::RUNNING) {
        return;
    }

    this->_result = result;
    status = EvaluationStatus::FINISHED;
}

const volatile EvaluationStatus &PartitionModelEvaluation::get_status() const {
    return status;
}

const size_t &PartitionModelEvaluation::partition_index() const {
    return _partition_index;
}

const candidate_model_t &PartitionModelEvaluation::candidate_model() const {
    return _candidate_model;
}

const unsigned int &PartitionModelEvaluation::thread_id() const {
    return _thread_id;
}

const unsigned int volatile &PartitionModelEvaluation::assigned_threads() const {
    return _assigned_threads;
}

EvaluationPriority PartitionModelEvaluation::priority() const {
    return _priority;
}

const EvaluationResult &PartitionModelEvaluation::get_result() const {
    assert(status == EvaluationStatus::FINISHED);
    return _result;
}

/* cf. ParallelContext::thread_barrier */
void PartitionModelEvaluation::barrier()
{
  assert(status != EvaluationStatus::WAITING);

  __sync_fetch_and_add( &_barrier_counter, 1);

  if(_thread_id == 0)
  {
    while(_barrier_counter != _assigned_threads);
    _barrier_counter = 0;
    _barrier_proceed = !_barrier_proceed;
  }
  else
  {
    while(_barrier_mycycle == _barrier_proceed);
    _barrier_mycycle = !_barrier_mycycle;
  }
}

void PartitionModelEvaluation::reduce(void *context, double *data, size_t size, int op)
{
  PartitionModelEvaluation *c = static_cast<PartitionModelEvaluation *>(context);

  /* synchronize */
  c->barrier();

  double *double_buf = (double*) c->_reduce_buffer.data();

  /* collect data from threads */
  size_t i, j;
  for (i = 0; i < size; ++i)
    double_buf[c->_thread_id * size + i] = data[i];

  /* synchronize */
  c->barrier();

  /* reduce */
  for (i = 0; i < size; ++i)
  {
    switch(op)
    {
      case CORAX_REDUCE_SUM:
      {
        data[i] = 0.;
        for (j = 0; j < c->_assigned_threads; ++j)
          data[i] += double_buf[j * size + i];
      }
      break;
      case CORAX_REDUCE_MAX:
      {
        data[i] = double_buf[i];
        for (j = 1; j < c->_assigned_threads; ++j)
          data[i] = max(data[i], double_buf[j * size + i]);
      }
      break;
      case CORAX_REDUCE_MIN:
      {
        data[i] = double_buf[i];
        for (j = 1; j < c->_assigned_threads; ++j)
          data[i] = min(data[i], double_buf[j * size + i]);
      }
      break;
    }
  }
}

const size_t &PartitionModelEvaluation::proposed_thread_count() const
{
    return _proposed_thread_count;

}
ModelTest::ModelTest(const Options &original_options, const PartitionedMSA &msa, const Tree &tree, const IDVector &tip_msa_idmap,
                     const PartitionAssignment &part_assign)
    : options(modify_options(original_options)), optimizer(options), msa(msa), tree(tree),
                                            tip_msa_idmap(tip_msa_idmap), part_assign(part_assign) { }

const vector<string> get_matrix_names(const DataType datatype) {
    switch(datatype) {
    case DataType::dna:
        return dna_substitution_matrix_names;
    case DataType::protein:
        return aa_substitution_matrix_names;
    case DataType::binary:
        return vector<string>({"BIN"});

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


class ExecutionStatus final {
public:
    ExecutionStatus() : use_rhas_heuristic(false), use_freerate_heuristic(false) {
    }

    template<typename F>
    void initialize(std::vector<candidate_model_t> _candidate_models, const PartitionedMSA &msa,
                    const Options &options,
                    F resource_estimator,
                    bool use_rhas_heuristic = false, bool use_freerate_heuristic = false) {
        this->candidate_models = std::move(_candidate_models);
        partition_count = msa.part_count();

        /* Substitution model used for heuristics, e.g. use GTR to test RHAS feasibility */
        reference_model.emplace(this->candidate_models.at(0).substitution_model);

        this->evaluations = std::make_unique<vector<PartitionModelEvaluation> >();
        evaluations->reserve(candidate_models.size() * partition_count);


        std::vector<rate_heterogeneity_t> selected_rhas;

        for (unsigned int p = 0; p < partition_count; ++p) {
            const auto &pinfo = msa.part_info(p);
            for (unsigned int i = 0; i < candidate_models.size(); ++i) {
                auto &candidate_model = candidate_models.at(i);
                const auto priority =
                        candidate_model.substitution_model == reference_model
                            ? EvaluationPriority::HIGH
                            : EvaluationPriority::NORMAL;
                const auto thread_count = CORAX_MIN(resource_estimator(options, pinfo, candidate_model, priority),
                                                    ParallelContext::num_threads());

                this->evaluations->emplace_back(candidate_model, p, priority, thread_count);

                if (p == 0 && candidate_model.substitution_model == reference_model) {
                    selected_rhas.push_back(candidate_model.rate_heterogeneity);
                }
            }
        }

        /* TODO: sort by priority across partitions
        std::sort(evaluations->begin(), evaluations->end(),
                  [](const PartitionModelEvaluation &a, const PartitionModelEvaluation &b) {
                      // Sort by priority, high priority should come first
                      return a.priority() > b.priority();
                  });
                  */


        iterator = evaluations->begin();

        this->use_rhas_heuristic = use_rhas_heuristic;
        this->use_freerate_heuristic = use_freerate_heuristic;

        this->rhas_heuristic_per_part.clear();
        this->rhas_heuristic_per_part.resize(partition_count, RHASHeuristic(*reference_model, selected_rhas));

        this->freerate_heuristic_per_part.clear();
        this->freerate_heuristic_per_part.resize(partition_count,
                                                 FreerateHeuristic(options.free_rate_min_categories,
                                                                   options.free_rate_max_categories));
    }

    virtual ~ExecutionStatus() = default;


    void update_result(PartitionModelEvaluation &evaluation, EvaluationResult &&result) {
        LOG_DEBUG_TS << "Model evaluation of " << evaluation.candidate_model().descriptor() << " finished, BIC = " << result.ic_criteria.at(InformationCriterion::bic) << ", LogLH = " << result.partition_loglh << endl;
        std::lock_guard<std::mutex> lock(mutex_evaluation);

        evaluation.store_result(std::move(result));

        const double bic = evaluation.get_result().ic_criteria.at(InformationCriterion::bic);
        const auto p = evaluation.partition_index();

        if (use_freerate_heuristic) {
            this->freerate_heuristic_per_part.at(p).
                    update(evaluation.candidate_model(), bic);
        }

        if (use_rhas_heuristic) {
            this->rhas_heuristic_per_part.at(p).update(evaluation.candidate_model(), bic);
        }

        /* Notify RHAS heuristic if freerate heuristic has converged */
        if (use_rhas_heuristic && use_freerate_heuristic) {
                const auto optimal_category_count = this->freerate_heuristic_per_part.at(p).optimal_category_count(*reference_model);

                if (optimal_category_count > 0) {
                    this->rhas_heuristic_per_part.at(p).freerate_complete(optimal_category_count);
                }
        }
    }

    bool can_skip_heuristically() const {
        if (iterator == evaluations->end())
            return false;

        if (use_freerate_heuristic &&
            freerate_heuristic_per_part.at(iterator->partition_index()).can_skip(iterator->candidate_model())) {
            LOG_THREAD_TS << " skipping " << iterator->candidate_model().descriptor() << " due to FreerateHeuristic" << endl;
            return true;
        }

        if (use_rhas_heuristic &&
            rhas_heuristic_per_part.at(iterator->partition_index()).can_skip(iterator->candidate_model())) {
            LOG_THREAD_TS << " skipping " << iterator->candidate_model().descriptor() << " due to RHASHeuristic" << endl;
            return true;
        }

        return false;
    }

    void print_results(int partition_index, PartitionModelEvaluation &evaluation) {
        std::lock_guard<std::mutex> lock(mutex_log);

        const auto &result = evaluation.get_result();
        const auto bic_score = result.ic_criteria.at(InformationCriterion::bic);
        LOG_WORKER_TS(LogLevel::info) << "Partition #" << partition_index << ": model = "
                                      << std::setfill(' ') << std::left << setw(20) << result.model.to_string()
                                      << "  LogLH = " << std::right << setw(15) << FMT_LH(result.partition_loglh)
        << "  BIC = " << std::right << setw(15) << FMT_LH(bic_score)
        << endl;
    }

    bool is_iterator_valid() const {
        return iterator != evaluations->end();
    }

    PartitionModelEvaluation *get_next_model() {
        if (evaluations->empty()) {
            throw std::logic_error("attempted to get next model before initialization");
        }

        std::lock_guard<std::mutex> lock(mutex_evaluation);

        // Skip candidates that either can be skipped because of heuristic assumptions or that do not need further threads
        while (is_iterator_valid() && (can_skip_heuristically() || iterator->get_status() !=
                                       EvaluationStatus::WAITING)) {
            if (can_skip_heuristically() && iterator->get_status() == EvaluationStatus::WAITING) {
                iterator->abort();
            }
            ++iterator;
        }

        if (!is_iterator_valid())
            return nullptr;

        assert(iterator->get_status() == EvaluationStatus::WAITING);
        bool success = iterator->join_team();
        assert(success);

        if (iterator->get_status() == EvaluationStatus::RUNNING) {
            size_t model_index = iterator - evaluations->begin();
            logger().logstream(LogLevel::progress, LogScope::thread) << RAXML_LOG_TIMESTAMP << "Evaluating model " << model_index << "/" << evaluations->size() << endl;
        }

        return &(*iterator);
    }

    vector<vector<EvaluationResult> > collect_finished_results_by_partition() const {
        vector<vector<EvaluationResult> > results(partition_count);

        for (const auto &evaluation: *evaluations) {
            if (evaluation.get_status() == EvaluationStatus::FINISHED) {
                results.at(evaluation.partition_index()).push_back(evaluation.get_result());
            }
        }

        return results;
    }


    vector<PartitionModelEvaluation> &get_results() const {
        return *evaluations;
    }

private:
    using Evaluations = vector<PartitionModelEvaluation>;
    std::vector<candidate_model_t> candidate_models;
    std::mutex mutex_evaluation;
    std::mutex mutex_log;
    Evaluations::iterator iterator;
    size_t partition_count;
    std::optional<substitution_model_t> reference_model;

    bool use_rhas_heuristic;
    std::vector<RHASHeuristic> rhas_heuristic_per_part;
    bool use_freerate_heuristic;
    std::vector<FreerateHeuristic> freerate_heuristic_per_part;

    std::unique_ptr<Evaluations> evaluations;
};

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
    thread_log.reset(new std::ofstream(options.outfile_prefix + ".raxml.modeltest.thread" + std::to_string(ParallelContext::thread_id()) + ".log"));
    const bool enable_rhas_heuristic = std::getenv("MODELTEST_RHAS_NOSKIP") == nullptr;
    const bool enable_freerate_heuristic = std::getenv("MODELTEST_FREERATE_NOSKIP") == nullptr;

    // TODO this destroyed timestamps -> use local formatting!
//    LOG_INFO << std::setprecision(20) << std::setfill(' ') << std::left;

    if (ParallelContext::master()) {
        // TODO: support multiple partitions with mixed datatypes
        auto candidate_models = generate_candidate_model_names(msa.part_info(0).model().data_type());
        execution_status.initialize(candidate_models, msa, options, estimate_cores, enable_rhas_heuristic,
                                    enable_freerate_heuristic);
    }

    // sync ALL threads across ALL workers
    // TODO: MPI
    ParallelContext::global_thread_barrier();


    PartitionModelEvaluation *evaluation = nullptr;

    const auto default_precision = std::cout.precision();
    cout << std::setprecision(19);

    while ((evaluation = execution_status.get_next_model()) != nullptr) {
        LOG_THREAD_TS << " scheduled to work on " << evaluation->candidate_model().descriptor() << " as thread " << evaluation->thread_id() << " out of " << evaluation->proposed_thread_count() << endl;

        const auto scheduling_time = global_timer().elapsed_seconds();
        evaluation->wait();

        const auto scheduling_overhead = global_timer().elapsed_seconds() - scheduling_time;

        /* If a heuristic applies by now, just continue with the next candidate */
        if (evaluation->get_status() == EvaluationStatus::ABORTED)
            continue;

        LOG_THREAD_TS << " begins work after waiting for " << 1e3 * scheduling_overhead << " milliseconds." << endl;


        // TODO: * use proper PartitionAssignment to distribute sites among threads
        //       * Set custom parallel_reduce_cb
        //       * Write back results
        //       * Run through valgrind, observe race conditions
        //       * Test in prod
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


        //LOG_WORKER_TS(LogLevel::info) << "partition " << partition_index + 1 << "/" << msa.part_count()
        //        << " model " << normalize_model_name(model_descriptor) << endl;

        // TODO: proper synchronization
        evaluation->barrier();
        Model model(model_descriptor);
        assign(model, msa.part_info(evaluation->partition_index()).stats());
        //msa.model(size_t index)
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

            EvaluationResult partition_results{model, partition_loglh, ic_score_calculator.all(partition_loglh)};

            execution_status.update_result(*evaluation, std::move(partition_results));
        }

        LOG_THREAD_TS << " evaluation of " << evaluation->candidate_model().descriptor() << " concluded." << endl;
    }

    cout << std::setprecision(default_precision);

    // sync ALL threads across ALL workers
    // TODO: MPI
    ParallelContext::global_thread_barrier();

    vector<Model> best_model_per_part;
    if (ParallelContext::master()) {
        auto xml_fname = options.output_fname("modeltest.xml");
        fstream xml_stream(xml_fname, std::ios::out);

        print_xml(xml_stream, execution_status.get_results());
        xml_stream.close();

        LOG_DEBUG << "XML model selection file written to " << xml_fname << endl;




        auto bestmodel_fname = options.output_fname("modeltest.bestModel");
        fstream bestmodel_stream(bestmodel_fname, std::ios::out);

        LOG_INFO << endl << "Best model(s):" << endl;
        auto all_results = execution_status.get_results();

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
            const auto result = evaluation.get_result();
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
