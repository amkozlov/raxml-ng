#ifndef MODELTEST_HPP_
#define MODELTEST_HPP_
#include <iosfwd>
#include <optional>
#include <vector>

#include "../TreeInfo.hpp"
#include "../Optimizer.hpp"
#include "ModelDefinitions.hpp"
#include "ModelEvaluator.hpp"

class ModelTest {
public:
    ModelTest(const Options &options, const PartitionedMSA &msa, const Tree &tree, const IDVector &tip_msa_idmap,
              const PartitionAssignment &part_assign, CheckpointManager &checkpoint_manager);

    vector<candidate_model_t> generate_candidate_model_names(const DataType &dt) const;

    /* Optimize the model and return model name per partition */
    vector<Model> optimize_model();

private:
    Options options;
    Optimizer optimizer;
    CheckpointManager checkpoint_manager;
    const PartitionedMSA &msa;
    const Tree &tree;
    const IDVector &tip_msa_idmap;
    const PartitionAssignment &part_assign;

    /// map from model descriptor to per-partition evaluation results
    [[nodiscard]]
    static vector<size_t> rank_by_score(const vector<ModelEvaluation const *> &results);

    static void print_xml(ostream &os, const vector<ModelEvaluator> &results);
};


#endif //MODELTEST_HPP_
