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

    vector<std::string> generate_candidate_model_names(const DataType &dt) const;

    void optimize_model();

private:
    const Options &options;
    PartitionedMSA &msa;
    const Tree &tree;
    const IDVector &tip_msa_idmap;
    const PartitionAssignment &part_assign;
    Optimizer &optimizer;

    /// map from model descriptor to per-partition evaluation results
    using EvaluationResults = vector<PartitionModelEvaluation>;


    [[nodiscard]]
    static vector<size_t> rank_by_score(const EvaluationResults &results, InformationCriterion ic,
                                        unsigned int partition_idx, unsigned int part_count);

    static void print_xml(ostream &os, EvaluationResults &results, unsigned int partition_count);
};


#endif //MODELTEST_HPP_
