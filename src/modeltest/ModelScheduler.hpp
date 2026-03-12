#ifndef MODEL_SCHEDULER_HPP_
#define MODEL_SCHEDULER_HPP_

#include <functional>
#include <iostream>
#include <vector>
#include <mutex>
#include <unordered_map>
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

        void update_result(ModelEvaluator &evaluator, const ModelEvaluation &result, bool announce = true, bool write_checkpoint = true);
        void print_results(int partition_index, const ModelEvaluation &result);
        ModelEvaluator *get_next_model(); 
        ModelEvaluator *get_by_descriptor(const PartitionCandidateModel &candidate_model);
        vector<vector<ModelEvaluation const *>> collect_finished_results_by_partition() const;
        void fetch_global_results();
        const SubstitutionModelDescriptor &get_reference_model();

        static vector<size_t> determine_acceptable_thread_counts(size_t total_cores);
        static size_t pick_acceptable_thread_count(const vector<size_t> &acceptable_thread_counts, size_t requested_thread_count);

        void print_xml(ostream &os) const;

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

    /** Keep map that points into the evaluators array to allow addressing by candidate model */
    unordered_map<PartitionCandidateModel, uint64_t> evaluator_map;

    Heuristics heuristics;
    DistributedSchedulingImpl distributed_scheduling;

    void _fetch_global_results();
    void _update_result(ModelEvaluator &evaluator, const ModelEvaluation &result, bool announce = true, bool write_checkpoint = true);
    ModelEvaluator &_get_evaluator(size_t index);

    using EvaluationStatusCounts = std::array<uint64_t, static_cast<uint64_t>(EvaluationStatus::FINISHED) + 1>;
    EvaluationStatusCounts _collect_progress() const;
    const std::string _ic_score_label() const;
    void read_from_checkpoint(CheckpointManager &checkpoint_manager);
    void globally_init_evaluation_index();

    unsigned int candidate_model_descriptor_width;
};

#endif
