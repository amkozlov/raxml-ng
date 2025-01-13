#ifndef MODELTEST_HPP_
#define MODELTEST_HPP_
#include "../TreeInfo.hpp"
#include "../Optimizer.hpp"

struct PartitionModelEvaluation {
    Model model;
    double partition_loglh;
    std::map<InformationCriterion, double> ic_criteria;
};

class ModelTest {
public:
    ModelTest(const Options &options, PartitionedMSA &msa, const Tree &tree, const IDVector &tip_msa_idmap,
              const PartitionAssignment &part_assign, Optimizer &optimizer);

    void optimize_model();

private:
    const Options &options;
    PartitionedMSA &msa;
    const Tree &tree;
    const IDVector &tip_msa_idmap;
    const PartitionAssignment &part_assign;
    Optimizer &optimizer;

    /// map from model descriptor to per-partition evaluation results
    using EvaluationResults = unordered_map<string, vector<PartitionModelEvaluation> >;


    vector<PartitionModelEvaluation> choose_best_fit(const EvaluationResults &results, InformationCriterion ic) const;
};


#endif //MODELTEST_HPP_
