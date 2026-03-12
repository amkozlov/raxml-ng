#ifndef MODELTEST_HPP_
#define MODELTEST_HPP_

#include "../Optimizer.hpp"
#include "ModelDefinitions.hpp"
#include "ModelScheduler.hpp"

class ModelTest
{
public:
  ModelTest(const Options &options, const PartitionedMSA &msa, const Tree &tree, const IDVector &tip_msa_idmap,
            CheckpointManager &checkpoint_manager);

  /* Optimize the model and return model name per partition */
  const vector<Model>& optimize_model();
  void print_results_to_file() const;
  vector<vector<ModelEvaluation const *>> get_results() const;

  unsigned int recommended_thread_count() const;

private:
  const Options options;
  Optimizer optimizer;
  CheckpointManager &checkpoint_manager;
  const PartitionedMSA &msa;
  const Tree &tree;
  const IDVector &tip_msa_idmap;

  vector<Model> best_model_per_part;

  ModelScheduler model_scheduler;

  using PartitionModelResults = vector<ModelEvaluation const *>;
  
  static void sort_by_score(PartitionModelResults &results);

  vector<ModelDescriptor> generate_candidate_model_names(const DataType &dt) const;
  vector<PartitionModelResults> _results;
};

#endif // MODELTEST_HPP_
