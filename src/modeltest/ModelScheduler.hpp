#ifndef MODEL_SCHEDULER_HPP_
#define MODEL_SCHEDULER_HPP_

#include <functional>
#include <iostream>
#include <vector>
#include <mutex>
#include "DistributedScheduling.hpp"
#include "ModelEvaluator.hpp"
#include "../PartitionedMSA.hpp"
#include "../Checkpoint.hpp"
#include "../Options.hpp"
#include "Heuristics.hpp"
#include "ModelDefinitions.hpp"

using std::vector;
using namespace std;

using ResourceEstimatorFunction = std::function<size_t(const Options &, const PartitionInfo&, const ModelDescriptor&,EvaluationPriority)>;

class ModelScheduler final {
    public:
        ModelScheduler(std::vector<ModelDescriptor> _candidate_models,
                       const PartitionedMSA &msa,
                       const Options &options,
                       CheckpointManager &checkpoint_manager,
                       ResourceEstimatorFunction resource_estimator);

        unsigned int recommended_thread_count() const;
        void finalize();
        ~ModelScheduler() = default; 

        void update_result(ModelEvaluator &evaluation, ModelEvaluation result, bool announce = true, bool checkpoint = true);
        void print_results(int partition_index, ModelEvaluation &result);
        ModelEvaluator *get_next_model(); 
        vector<vector<ModelEvaluation const *>> collect_finished_results_by_partition() const;
        void fetch_global_results();
        void print_xml(std::ostream &os) const;

private:
    std::mutex mutex_evaluation;
    std::mutex mutex_log;
    std::mutex mutex_mpi;

    const Options &options;
    const PartitionedMSA &msa;
    CheckpointManager &checkpoint_manager;

    const size_t partition_count, branch_count;

    const std::vector<ModelDescriptor> candidate_models;
    const SubstitutionModelDescriptor &reference_model;

    uint64_t evaluation_index;
    vector<ModelEvaluator> evaluators;
    Heuristics heuristics;
    DistributedSchedulingImpl distributed_scheduling;

    void _fetch_global_results();
    void _update_result(ModelEvaluator &evaluation, ModelEvaluation result, bool announce = true, bool checkpoint = true);
    ModelEvaluator &_get_evaluator(size_t index);

    using EvaluationStatusCounts = std::array<uint64_t, static_cast<uint64_t>(EvaluationStatus::FINISHED) + 1>;
    EvaluationStatusCounts _collect_progress() const;
    const std::string _ic_score_label() const;
    void read_from_checkpoint(CheckpointManager &checkpoint_manager);
    void globally_init_evaluation_index();

    unsigned int candidate_model_descriptor_width;
};

#endif
