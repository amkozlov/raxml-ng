#ifndef MODELTEST_HPP_
#define MODELTEST_HPP_
#include <iosfwd>
#include <iosfwd>
#include <vector>
#include <vector>

#include "../TreeInfo.hpp"
#include "../Optimizer.hpp"
#include "ModelDefinitions.hpp"

struct PartitionModelEvaluation {
    Model model;
    double partition_loglh;
    std::map<InformationCriterion, double> ic_criteria;
};


class ModelTest {
public:
    ModelTest(const Options &options, const PartitionedMSA &msa, const Tree &tree, const IDVector &tip_msa_idmap,
              const PartitionAssignment &part_assign);

    vector<candidate_model_t> generate_candidate_model_names(const DataType &dt) const;

    /* Optimize the model and return model name per partition */
    vector<string> optimize_model();

private:
    Options options;
    Optimizer optimizer;
    const PartitionedMSA &msa;
    const Tree &tree;
    const IDVector &tip_msa_idmap;
    const PartitionAssignment &part_assign;

    /// map from model descriptor to per-partition evaluation results
    using EvaluationResults = vector<vector<PartitionModelEvaluation> >;


    [[nodiscard]]
    static vector<size_t> rank_by_score(const EvaluationResults &results, InformationCriterion ic,
                                        unsigned int partition_idx);

    static void print_xml(ostream &os, EvaluationResults &results);
};


#endif //MODELTEST_HPP_
