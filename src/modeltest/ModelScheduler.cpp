#include "ModelScheduler.hpp"
#include "../ParallelContext.hpp"
#include "../ICScoreCalculator.hpp"
#include "DistributedScheduling.hpp"
#include "ModelDefinitions.hpp"
#include "ModelEvaluator.hpp"
#include "Heuristics.hpp"
#include <functional>
#include <mutex>
#include <string>
#include <unistd.h>


size_t determine_binary_candidates_size(const std::vector<ModelEvaluator> &evaluations)
{
    size_t size = sizeof(uint64_t);

    for (auto &eval : evaluations)
    {
        size += sizeof(uint64_t) + BinaryStream::serialized_size(eval.get_result());
    }

    return size;
}

EvaluationPriority prioritize_candidate_model(const ModelDescriptor &candidate_model, const SubstitutionModelDescriptor &reference_model)
{
    const bool is_reference = candidate_model.substitution_model == reference_model;
    const bool is_rhas_likely = candidate_model.rate_heterogeneity.category_count <= 4;

    if (is_reference) {
        return is_rhas_likely ? EvaluationPriority::HIGHEST : EvaluationPriority::HIGH;
    } else {
        return is_rhas_likely ? EvaluationPriority::NORMAL : EvaluationPriority::LOW;
    }
    
}

vector<ModelEvaluator> build_evaluators(const PartitionedMSA &msa,
                                        const Options &options,
                                        const SubstitutionModelDescriptor &reference_model,
                                        ResourceEstimatorFunction resource_estimator,
                                        const std::vector<ModelDescriptor> &candidate_models,
                                        unsigned int partition_count)
{
    vector<ModelEvaluator> evaluators;
    evaluators.reserve(candidate_models.size() * partition_count);

    for (unsigned int p = 0; p < partition_count; ++p) {
        const auto &pinfo = msa.part_info(p);
        for (unsigned int i = 0; i < candidate_models.size(); ++i) {
            const auto &candidate_model = candidate_models.at(i);
            const auto priority = prioritize_candidate_model(candidate_model, reference_model);
            const auto thread_count = CORAX_MIN(resource_estimator(options, pinfo, candidate_model, priority),
                                                ParallelContext::num_threads());

            evaluators.emplace_back(candidate_model, pinfo.stats(), p, priority, thread_count);
        }
    }

    return evaluators;
}
std::vector<RateHeterogeneityDescriptor> get_selected_rhas(const std::vector<ModelDescriptor> &candidate_models,
                                                    const SubstitutionModelDescriptor &reference_model)
{
    std::vector<RateHeterogeneityDescriptor> selected_rhas;

    for (const auto &candidate : candidate_models) {
        if (candidate.substitution_model == reference_model) {
            selected_rhas.push_back(candidate.rate_heterogeneity);
        }
    }

    return selected_rhas;
}

std::vector<size_t> sort_evaluators(const std::vector<ModelEvaluator> &evaluators)
{
    std::vector<size_t> v(evaluators.size());
    std::iota(v.begin(), v.end(), 0);


    return v;
}

template<typename Iterator>
unsigned int max_descriptor_width(Iterator begin, Iterator end)
{
    auto it = begin;
    size_t w = 0;
    while(it != end)
    {
        w = std::max(w, it->descriptor().size());
        ++it;
    }

    return w;
}

ModelScheduler::ModelScheduler(
            std::vector<ModelDescriptor> _candidate_models,
            const PartitionedMSA &msa,
            const Options &options,
            CheckpointManager &checkpoint_manager,
            ResourceEstimatorFunction resource_estimator)
 : mutex_evaluation{},
   mutex_log{},
   mutex_mpi{},
   options{options},
   msa{msa},
   checkpoint_manager{checkpoint_manager},
   partition_count{msa.part_count()},
   branch_count{BasicTree(msa.taxon_count()).num_branches()},
   candidate_models{_candidate_models},
   reference_model{candidate_models.at(0).substitution_model},
   evaluation_index{0},
   evaluators{build_evaluators(msa, options, reference_model, resource_estimator, candidate_models, partition_count)},
   heuristics{partition_count, options.modeltest_heuristics, get_selected_rhas(candidate_models, reference_model), reference_model, options.free_rate_min_categories, options.free_rate_max_categories, options.modeltest_significant_ic_delta, options.modeltest_rhas_heuristic_mode},
   distributed_scheduling{determine_binary_candidates_size(evaluators)},
   candidate_model_descriptor_width(max_descriptor_width(candidate_models.cbegin(), candidate_models.cend()))
   {

    std::stable_sort(evaluators.begin(), evaluators.end(),
                [](const ModelEvaluator &a, const ModelEvaluator &b) {
                    // Sort by priority, high priority should come first
                    return a.priority() > b.priority();
                });

    read_from_checkpoint(checkpoint_manager);
    globally_init_evaluation_index();
}

void ModelScheduler::read_from_checkpoint(CheckpointManager &checkpoint_manager)
{
    const auto t0 = global_timer().elapsed_seconds();

    std::unordered_map<PartitionCandidateModel, size_t> evaluator_index;
    for (size_t i = 0; i < evaluators.size(); ++i)
    {
        PartitionCandidateModel key { evaluators.at(i).partition_index(), evaluators.at(i).candidate_model() };
        evaluator_index[key] = i;
    }

    for (auto &checkpointed_candidate : checkpoint_manager.get_model_candidates())
    {
        const PartitionCandidateModel &key = checkpointed_candidate.first;
        ModelEvaluation evaluation = checkpointed_candidate.second;

        auto it = evaluator_index.find(key);
        if (it == evaluator_index.end()) {
            // Set of candidate models changed because of user parameters, disregard model
            continue;
        }

        // Recompute information criterion (selection criterion might have changed since last run)
        const ICScoreCalculator ic_calc(evaluation.model.num_free_params(), msa.part_info(key.partition).stats().site_count);
        evaluation.ic_score = ic_calc.compute(options.model_selection_criterion, evaluation.loglh);

        update_result(evaluators.at(it->second), evaluation, false, false);
    }

    const auto t1 = global_timer().elapsed_seconds();

    if (ParallelContext::master())
        logger().logstream(LogLevel::debug, LogScope::thread) << "Restored " << checkpoint_manager.get_model_candidates().size() << " candidate models from checkpoint in " << (1e3 * (t1 - t0)) << "ms.\n";
}

/** Initialize evaluation_index in light of checkpointed results and in accordance with other MPI ranks */
void ModelScheduler::globally_init_evaluation_index()
{
    while (true) {
        evaluation_index = distributed_scheduling.next_evaluation_index();

        if (evaluation_index >= evaluators.size())
            break;

        const bool result_already_present = evaluators.at(evaluation_index).get_status() != EvaluationStatus::WAITING;
        const bool can_skip_heuristically = heuristics.can_skip(evaluators.at(evaluation_index).partition_index(), evaluators.at(evaluation_index).candidate_model());

        if (result_already_present || can_skip_heuristically) {
            continue;
        } else {
            break;
        }
    }

}

/** Get the number of threads recommended to perform model selection. */
unsigned int ModelScheduler::recommended_thread_count() const
{
    unsigned int thread_count = 0;

    for (const auto &evaluator : evaluators)
    {
        if (evaluator.priority() != EvaluationPriority::HIGHEST) break;

        thread_count += evaluator.proposed_thread_count();
    }

    return std::max(1U, thread_count);
}

void ModelScheduler::update_result(ModelEvaluator &evaluator, ModelEvaluation result, bool announce, bool write_checkpoint) {
    std::lock_guard<std::mutex> lock(mutex_evaluation);
    _update_result(evaluator, std::move(result), announce, write_checkpoint);

    // Only show progress for new results
    if (write_checkpoint)
    {
        const auto progress = _collect_progress();
        const auto n_finished = progress.at(static_cast<uint64_t>(EvaluationStatus::FINISHED));
        const auto n_waiting = progress.at(static_cast<uint64_t>(EvaluationStatus::WAITING));
        const auto width = std::to_string(evaluators.size() + 1).size();

        logger().logstream(LogLevel::progress, LogScope::thread) << RAXML_LOG_TIMESTAMP << std::setfill(' ') << "Evaluated model " 
            << "(" << std::setw(width) << n_finished << "/" << std::setw(width) << (n_finished + n_waiting) << ") "
            << std::setw(candidate_model_descriptor_width) << std::left << evaluator.candidate_model().descriptor() << " " << right
            << options.ic_name() << " = " << FMT_LH(evaluator.get_result().ic_score)
            << "\n";
    }
}

void ModelScheduler::_update_result(ModelEvaluator &evaluator, ModelEvaluation result, bool announce, bool write_checkpoint) {
    // TODO: replace calls to `std::distance` with `index` field inside ModelEvaluator
    const uint64_t index = std::distance(evaluators.data(), std::addressof(evaluator));

    evaluator.store_result(std::move(result));
    heuristics.update(evaluator.partition_index(), evaluator.candidate_model(), evaluator.get_result().ic_score);

    if (announce) {
        distributed_scheduling.announce_result(index, evaluator.get_result());
    }

    if (write_checkpoint && ParallelContext::master_rank()) {
        checkpoint_manager.update_and_write(PartitionCandidateModel { evaluator.partition_index(), evaluator.candidate_model() }, evaluator.get_result());
    }
}

void ModelScheduler::print_results(int partition_index, ModelEvaluation &result) {
    std::lock_guard<std::mutex> lock(mutex_log);

    LOG_WORKER_TS(LogLevel::info) << "Partition #" << partition_index << ": model = "
                                    << setfill(' ') << left << setw(20) << result.model.to_string()
                                    << "  LogLH = " << std::right << setw(15) << FMT_LH(result.loglh)
    << "  " << options.ic_name() << " = " << right << setw(15) << FMT_LH(result.ic_score)
    << endl;
}

void ModelScheduler::fetch_global_results()
{
    std::lock_guard<std::mutex> lock(mutex_evaluation);
    _fetch_global_results();
}

void ModelScheduler::_fetch_global_results()
{
    ModelUpdateCallback callback = [this](uint64_t i, const ModelEvaluation &m) {
        _update_result(evaluators.at(i), m, false, true);
    };
    distributed_scheduling.fetch_results(callback);
}

ModelEvaluator *ModelScheduler::get_next_model()
{
    if (evaluators.empty()) {
        throw std::logic_error("attempted to get next model before initialization");
    }

    std::lock_guard<std::mutex> lock(mutex_evaluation);

    while (evaluation_index < evaluators.size() &&
           evaluators.at(evaluation_index).get_status() != EvaluationStatus::WAITING)
    {
        _fetch_global_results(); // TODO: determine whether to pull this out of the loop

        evaluation_index = distributed_scheduling.next_evaluation_index();
        if (evaluation_index >= evaluators.size()) {
            break;
        }

        auto &evaluation = evaluators.at(evaluation_index);
        
        /* Skip candidates heuristically */
        if (heuristics.can_skip(evaluation.partition_index(), evaluation.candidate_model())) {
            evaluation.skip();
            continue;
        }
    }

    if (evaluation_index >= evaluators.size())
        return nullptr;

    auto &evaluation = evaluators.at(evaluation_index);
    assert(evaluation.get_status() == EvaluationStatus::WAITING);
    bool success = evaluation.join_team();
    assert(success);

    return &evaluation;
}

vector<vector<ModelEvaluation const *>> ModelScheduler::collect_finished_results_by_partition() const {
    vector<vector<ModelEvaluation const *>> results(partition_count);

    for (const auto &evaluation: evaluators) {
        if (evaluation.get_status() == EvaluationStatus::FINISHED) {
            results.at(evaluation.partition_index()).push_back(&evaluation.get_result());
        }
    }

    return results;
}

void ModelScheduler::print_xml(ostream &os) const {
    os << setprecision(17);
    os << "<modeltestresults criterion=\"" << options.ic_name() << "\">" << endl;

    for (const auto &evaluator: evaluators) {
        os << "<model partition=\"" << evaluator.partition_index()
                << "\" name=\"" << evaluator.candidate_model().descriptor()
                << "\" status=\"";
        switch (evaluator.get_status()) {
            case EvaluationStatus::WAITING:
                os << "WAITING";
                break;
            case EvaluationStatus::RUNNING:
                os << "RUNNING";
                break;
            case EvaluationStatus::SKIPPED:
                os << "SKIPPED";
                break;
            case EvaluationStatus::FINISHED:
                os << "FINISHED";
                break;
        }

        if (evaluator.get_status() == EvaluationStatus::FINISHED) {
            const auto &result = evaluator.get_result();
            const bool essential = heuristics.evaluation_essential(evaluator.partition_index(), evaluator.candidate_model());

            os << "\" lnL=\"" << result.loglh
                    << "\" essential=\"" << (essential ? "1" : "0")
                    << "\" score=\"" << result.ic_score
                    << "\" free-params=\"" << result.model.num_free_params() 
                    << "\" params=\"" << result.model.to_string(true, 19)
                    << "\" />" << endl;
        } else {
            os << "\" />" << endl;
        }
    }

    os << "</modeltestresults>" << endl;
}

ModelScheduler::EvaluationStatusCounts ModelScheduler::_collect_progress() const
{
    ModelScheduler::EvaluationStatusCounts counts;
    counts.fill(0);

    // TODO: this is currently O(N^2)
    for (const auto &evaluator : evaluators)
    {
        const uint64_t status = static_cast<uint64_t>(evaluator.get_status());
        ++counts.at(status);
    }

    return counts;
}

