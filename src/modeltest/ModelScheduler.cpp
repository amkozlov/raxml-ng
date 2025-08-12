#include "ModelScheduler.hpp"
#include "../ParallelContext.hpp"
#include "DistributedScheduling.hpp"
#include "Evaluation.hpp"
#include "Heuristics.hpp"

ExecutionStatus::ExecutionStatus()
{
}

void ExecutionStatus::initialize(std::vector<candidate_model_t> _candidate_models, const PartitionedMSA &msa,
            const Options &options,
            ResourceEstimatorFunction resource_estimator,
            bool use_rhas_heuristic, bool use_freerate_heuristic) {
    candidate_models = std::move(_candidate_models);
    partition_count = msa.part_count();
    evaluation_index = 0;
    branch_count = BasicTree(msa.taxon_count()).num_branches();
    this->msa = &msa;

    /* Substitution model used for heuristics, e.g. use GTR to test RHAS feasibility */
    reference_model.emplace(this->candidate_models.at(0).substitution_model);


    this->evaluations = std::make_unique<std::vector<PartitionModelEvaluation>>();
    evaluations->reserve(candidate_models.size() * partition_count);
    selected_rhas.clear();
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

            this->evaluations->emplace_back(&candidate_model, p, priority, thread_count);

            if (p == 0 && candidate_model.substitution_model == reference_model) {
                selected_rhas.push_back(candidate_model.rate_heterogeneity);
            }
        }
    }

    const auto heuristics_selection = (use_freerate_heuristic ? static_cast<unsigned int>(HeuristicSelection::FREERATE) : 0) |
                                      (use_rhas_heuristic ? static_cast<unsigned int>(HeuristicSelection::RHAS) : 0);
    heuristics = std::make_unique<Heuristics>(partition_count, heuristics_selection, selected_rhas, *reference_model, options);
    distributed_scheduling = std::make_unique<DistributedSchedulingImpl>(evaluations->size());

    std::sort(evaluations->begin(), evaluations->end(),
                [](const PartitionModelEvaluation &a, const PartitionModelEvaluation &b) {
                    // Sort by priority, high priority should come first
                    return a.priority() > b.priority();
                });
}

void ExecutionStatus::finalize() {
    distributed_scheduling->finalize();
}

void ExecutionStatus::update_result(PartitionModelEvaluation &evaluation, EvaluationResult result) {
    LOG_DEBUG_TS << "Model evaluation of " << evaluation.candidate_model()->descriptor() << " finished, BIC = " << result.ic_criteria.at(InformationCriterion::bic) << ", LogLH = " << result.partition_loglh << ", aborted = " << (evaluation.get_status() == EvaluationStatus::ABORTED) << std::endl;
    std::lock_guard<std::mutex> lock(mutex_evaluation);

    evaluation.store_result(std::move(result));
    const double bic = evaluation.get_result()->ic_criteria.at(InformationCriterion::bic);
    heuristics->update(evaluation.partition_index(), *evaluation.candidate_model(), bic);

    const uint64_t index = std::distance(evaluations->data(), std::addressof(evaluation));
    assert(std::addressof(evaluation) == std::addressof(evaluations->at(index)));
    distributed_scheduling->announce_result(index, evaluation.get_result().value());
}

void ExecutionStatus::print_results(int partition_index, PartitionModelEvaluation &evaluation) {
    std::lock_guard<std::mutex> lock(mutex_log);

    const auto &result = evaluation.get_result();
    const auto bic_score = result->ic_criteria.at(InformationCriterion::bic);
    LOG_WORKER_TS(LogLevel::info) << "Partition #" << partition_index << ": model = "
                                    << setfill(' ') << left << setw(20) << result->model->to_string()
                                    << "  LogLH = " << std::right << setw(15) << FMT_LH(result->partition_loglh)
    << "  BIC = " << right << setw(15) << FMT_LH(bic_score)
    << endl;
}

void ExecutionStatus::fetch_global_results()
{
    std::function<void(IndexedEvaluationResult)> callback = [this](IndexedEvaluationResult indexed_result) {
        auto &evaluation = evaluations->at(indexed_result.index);

        const auto free_params = indexed_result.result.model->num_free_params() + branch_count;
        const auto sample_size = msa->part_info(evaluation.partition_index()).stats().site_count;
        indexed_result.result.recompute_ic_criteria(free_params, sample_size);

        evaluation.store_result(std::move(indexed_result.result));
    };
    distributed_scheduling->fetch_results(callback);
}

PartitionModelEvaluation *ExecutionStatus::get_next_model()
{
    if (evaluations->empty()) {
        throw std::logic_error("attempted to get next model before initialization");
    }

    std::lock_guard<std::mutex> lock(mutex_evaluation);

    while (evaluation_index < evaluations->size() &&
           evaluations->at(evaluation_index).get_status() != EvaluationStatus::WAITING)
    {
        fetch_global_results(); // TODO: determine whether to pull this out of the loop

        evaluation_index = distributed_scheduling->next_evaluation_index();
        if (evaluation_index >= evaluations->size()) {
            break;
        }

        auto &evaluation = evaluations->at(evaluation_index);
        
        /* Skip candidates heuristically */
        if (heuristics->can_skip(evaluation.partition_index(), *evaluation.candidate_model())) {
            evaluation.abort();
            continue;
        }
    }

    if (evaluation_index >= evaluations->size())
        return nullptr;

    auto &evaluation = evaluations->at(evaluation_index);
    assert(evaluation.get_status() == EvaluationStatus::WAITING);
    bool success = evaluation.join_team();
    assert(success);

    if (evaluation.get_status() == EvaluationStatus::RUNNING) {
        logger().logstream(LogLevel::progress, LogScope::thread) << RAXML_LOG_TIMESTAMP << "Evaluating model " << evaluation_index << "/" << evaluations->size() << std::endl;
    }
    return &evaluation;
}

vector<vector<EvaluationResult const *>> ExecutionStatus::collect_finished_results_by_partition() const {
    vector<vector<EvaluationResult const *>> results(partition_count);

    for (const auto &evaluation: *evaluations) {
        if (evaluation.get_status() == EvaluationStatus::FINISHED) {
            results.at(evaluation.partition_index()).push_back(&evaluation.get_result().value());
        }
    }

    return results;
}

const vector<PartitionModelEvaluation> &ExecutionStatus::get_evaluations() const {
    return *evaluations;
}
