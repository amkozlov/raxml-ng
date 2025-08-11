#ifndef MODEL_SCHEDULER_HPP_
#define MODEL_SCHEDULER_HPP_

#include <functional>
#include <iostream>
#include <vector>
#include "DistributedScheduling.hpp"
#include "Evaluation.hpp"
#include "../PartitionedMSA.hpp"
#include "../Tree.hpp"
#include "../Options.hpp"
#include "../log.hpp"
#include "../common.h"
#include "FreerateHeuristic.hpp"
#include "Heuristics.hpp"
#include "ModelDefinitions.hpp"
#include "RHASHeuristic.hpp"

using std::vector;
using namespace std;

using ResourceEstimatorFunction = std::function<size_t(const Options &, const PartitionInfo&, const candidate_model_t&,EvaluationPriority)>;

class ExecutionStatus final {
    public:
        ExecutionStatus();

        void initialize(std::vector<candidate_model_t> _candidate_models, const PartitionedMSA &msa,
                    const Options &options,
                    ResourceEstimatorFunction resource_estimator,
                    bool use_rhas_heuristic = false, bool use_freerate_heuristic = false);


        void finalize();
        ~ExecutionStatus() = default; 

        void update_result(PartitionModelEvaluation &evaluation, EvaluationResult result);
        void print_results(int partition_index, PartitionModelEvaluation &evaluation);
        PartitionModelEvaluation *get_next_model(); 
        vector<vector<EvaluationResult>> collect_finished_results_by_partition() const;
        const vector<PartitionModelEvaluation> &get_evaluations() const;

private:
    std::mutex mutex_evaluation;
    std::mutex mutex_log;
    std::mutex mutex_mpi;

    size_t partition_count, branch_count;
    std::vector<candidate_model_t> candidate_models;
    std::optional<substitution_model_t> reference_model;
    std::vector<rate_heterogeneity_t> selected_rhas;

    std::unique_ptr<vector<PartitionModelEvaluation>> evaluations;
    uint64_t evaluation_index;
    std::unique_ptr<Heuristics> heuristics;
    std::unique_ptr<DistributedSchedulingImpl> distributed_scheduling;

    const PartitionedMSA *msa;

    void fetch_global_results();
};

#endif
