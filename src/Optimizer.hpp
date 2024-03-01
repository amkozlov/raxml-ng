#ifndef RAXML_OPTIMIZER_H_
#define RAXML_OPTIMIZER_H_

#include "TreeInfo.hpp"
#include "Checkpoint.hpp"

#include <stdio.h>
#include "adaptive/StoppingCriterion.hpp"

class Optimizer
{
public:
  Optimizer (const Options& opts);
  virtual
  ~Optimizer ();

  double optimize_model(TreeInfo& treeinfo, double lh_epsilon);
  double optimize_model(TreeInfo& treeinfo) { return optimize_model(treeinfo, _lh_epsilon); };
  
  // optimization routines
  double optimize_topology(TreeInfo& treeinfo, CheckpointManager& cm);
  double optimize_topology_adaptive(TreeInfo& treeinfo, CheckpointManager& cm);
  double optimize_topology_modified(TreeInfo& treeinfo, CheckpointManager& cm);
  
  double evaluate(TreeInfo& treeinfo, CheckpointManager& cm);
  void nni(TreeInfo& treeinfo, nni_round_params& nni_params, double& loglh);

  void set_stopping_criterion(StoppingCriterion* _criterion) { criterion = _criterion; } // have to fix this

private:
  double _lh_epsilon;
  double _lh_epsilon_brlen_triplet;
  int _spr_radius;
  double _spr_cutoff;

  // nni params
  double _nni_epsilon;
  double _nni_tolerance;

  // stoping criteria
  int _stopping_criterion;
  bool _modified_version;
  StoppingCriterion *criterion;

  // functions for adaptive mode
  int spr_radius_limit_adaptive(double difficulty);
  int spr_radius_step_adaptive(int spr_radius_max);

  bool call_modified_version() {return (_modified_version || (_stopping_criterion >= 0)); }
};

#endif /* RAXML_OPTIMIZER_H_ */
