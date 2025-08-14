#include "ModelScheduler.hpp"
#include "../ParallelContext.hpp"
#include "DistributedScheduling.hpp"
#include "ModelEvaluator.hpp"
#include "Heuristics.hpp"
#include <functional>

ModelScheduler::ModelScheduler()
{
}

size_t determine_binary_candidates_size(const std::vector<ModelEvaluator> &evaluations)
{
    size_t size = sizeof(uint64_t);

    for (auto &eval : evaluations)
    {
        size += sizeof(uint64_t) + BinaryStream::serialized_size(eval.get_result());
    }

    return size;
}

void ModelScheduler::initialize(std::vector<candidate_model_t> _candidate_models, const PartitionedMSA &msa,
            const Options &options,
            CheckpointManager &checkpoint_manager,
            ResourceEstimatorFunction resource_estimator,
            bool use_rhas_heuristic, bool use_freerate_heuristic) {
    candidate_models = std::move(_candidate_models);
    partition_count = msa.part_count();
    branch_count = BasicTree(msa.taxon_count()).num_branches();
    this->msa = &msa;
    this->checkpoint_manager = &checkpoint_manager;

    /* Substitution model used for heuristics, e.g. use GTR to test RHAS feasibility */
    reference_model.emplace(this->candidate_models.at(0).substitution_model);


    this->evaluators = std::make_unique<std::vector<ModelEvaluator>>();
    evaluators->reserve(candidate_models.size() * partition_count);
    selected_rhas.clear();
    for (unsigned int p = 0; p < partition_count; ++p) {
        const auto &pinfo = msa.part_info(p);
        for (unsigned int i = 0; i < candidate_models.size(); ++i) {
            auto &candidate_model = candidate_models.at(i);
            const auto priority  =
                    candidate_model.substitution_model == reference_model
                        ? EvaluationPriority::HIGH
                        : EvaluationPriority::NORMAL;
            const auto thread_count = CORAX_MIN(resource_estimator(options, pinfo, candidate_model, priority),
                                                ParallelContext::num_threads());

            evaluators->emplace_back(&candidate_model, pinfo.stats(), p, priority, thread_count);

            if (p == 0 && candidate_model.substitution_model == reference_model) {
                selected_rhas.push_back(candidate_model.rate_heterogeneity);
            }
        }
    }


    const auto heuristics_selection = (use_freerate_heuristic ? static_cast<unsigned int>(HeuristicSelection::FREERATE) : 0) |
                                      (use_rhas_heuristic ? static_cast<unsigned int>(HeuristicSelection::RHAS) : 0);
    heuristics = std::make_unique<Heuristics>(partition_count, heuristics_selection, selected_rhas, *reference_model, options);
    distributed_scheduling = std::make_unique<DistributedSchedulingImpl>(determine_binary_candidates_size(*evaluators));

    std::sort(evaluators->begin(), evaluators->end(),
                [](const ModelEvaluator &a, const ModelEvaluator &b) {
                    // Sort by priority, high priority should come first
                    return a.priority() > b.priority();
                });

    if (ParallelContext::master_rank()) {
        for (const auto &[index, model_evaluation] : checkpoint_manager.get_model_candidates())
        {
            update_result(evaluators->at(index), model_evaluation, true, false);
        }
    }

    while (true) {
        evaluation_index = distributed_scheduling->next_evaluation_index();

        if (evaluation_index >= evaluators->size())
            break;

        const bool result_already_present = evaluators->at(evaluation_index).get_status() != EvaluationStatus::WAITING;
        const bool can_skip_heuristically = heuristics->can_skip(evaluators->at(evaluation_index).partition_index(), *evaluators->at(evaluation_index).candidate_model());

        if (result_already_present || can_skip_heuristically) {
            continue;
        } else {
            break;
        }
    }
}

void ModelScheduler::finalize() {
    distributed_scheduling->finalize();
}

void ModelScheduler::update_result(ModelEvaluator &evaluator, ModelEvaluation result, bool announce, bool write_checkpoint) {
    std::lock_guard<std::mutex> lock(mutex_evaluation);

    evaluator.store_result(std::move(result));
    heuristics->update(evaluator.partition_index(), *evaluator.candidate_model(), evaluator.get_result().ic_score);

    const uint64_t index = std::distance(evaluators->data(), std::addressof(evaluator));

    if (announce) {
        distributed_scheduling->announce_result(index, evaluator.get_result());
    }

    if (write_checkpoint && ParallelContext::master_rank()) {
        checkpoint_manager->update_and_write(index, evaluator.get_result());
    }
}

void ModelScheduler::print_results(int partition_index, ModelEvaluation &result) {
    std::lock_guard<std::mutex> lock(mutex_log);

    LOG_WORKER_TS(LogLevel::info) << "Partition #" << partition_index << ": model = "
                                    << setfill(' ') << left << setw(20) << result.model.to_string()
                                    << "  LogLH = " << std::right << setw(15) << FMT_LH(result.loglh)
    << "  BIC = " << right << setw(15) << FMT_LH(result.ic_score)
    << endl;
}

void ModelScheduler::fetch_global_results()
{
    ModelUpdateCallback callback = [this](uint64_t i, const ModelEvaluation &m) {
        update_result(evaluators->at(i), m, false, true);
    };
    distributed_scheduling->fetch_results(*evaluators, callback);
}

ModelEvaluator *ModelScheduler::get_next_model()
{
    if (evaluators->empty()) {
        throw std::logic_error("attempted to get next model before initialization");
    }

    std::lock_guard<std::mutex> lock(mutex_evaluation);

    while (evaluation_index < evaluators->size() &&
           evaluators->at(evaluation_index).get_status() != EvaluationStatus::WAITING)
    {
        fetch_global_results(); // TODO: determine whether to pull this out of the loop

        evaluation_index = distributed_scheduling->next_evaluation_index();
        if (evaluation_index >= evaluators->size()) {
            break;
        }

        auto &evaluation = evaluators->at(evaluation_index);
        
        /* Skip candidates heuristically */
        if (heuristics->can_skip(evaluation.partition_index(), *evaluation.candidate_model())) {
            evaluation.abort();
            continue;
        }
    }

    if (evaluation_index >= evaluators->size())
        return nullptr;

    auto &evaluation = evaluators->at(evaluation_index);
    assert(evaluation.get_status() == EvaluationStatus::WAITING);
    bool success = evaluation.join_team();
    assert(success);

    if (evaluation.get_status() == EvaluationStatus::RUNNING) {
        logger().logstream(LogLevel::progress, LogScope::thread) << RAXML_LOG_TIMESTAMP << "Evaluating model " << evaluation_index << "/" << evaluators->size() << std::endl;
    }
    return &evaluation;
}

vector<vector<ModelEvaluation const *>> ModelScheduler::collect_finished_results_by_partition() const {
    vector<vector<ModelEvaluation const *>> results(partition_count);

    for (const auto &evaluation: *evaluators) {
        if (evaluation.get_status() == EvaluationStatus::FINISHED) {
            results.at(evaluation.partition_index()).push_back(&evaluation.get_result());
        }
    }

    return results;
}

const vector<ModelEvaluator> &ModelScheduler::get_evaluations() const {
    return *evaluators;
}
