#ifndef RAXML_OPTIMIZER_H_
#define RAXML_OPTIMIZER_H_

#include "TreeInfo.hpp"
#include "Checkpoint.hpp"

#include <stdio.h>
#include "adaptive/StoppingCriterion.hpp"

class Optimizer
{
public:
  Optimizer (const Options& opts, bool rapid_bs = false);
  virtual
  ~Optimizer ();

  double optimize_model(TreeInfo& treeinfo, double lh_epsilon);
  double optimize_model(TreeInfo& treeinfo) { return optimize_model(treeinfo, _lh_epsilon); };
  double optimize_topology(TreeInfo& treeinfo, CheckpointManager& cm);
  double optimize_topology_standard(TreeInfo& treeinfo, CheckpointManager& cm);
  double optimize_topology_adaptive(TreeInfo& treeinfo, CheckpointManager& cm);
  
  double optimize_topology_rbs(TreeInfo& treeinfo, CheckpointManager& cm);
  double optimize_topology_nni(TreeInfo& treeinfo, CheckpointManager& cm);

  double evaluate(TreeInfo& treeinfo, CheckpointManager& cm);
  void nni(TreeInfo& treeinfo, nni_round_params& nni_params, double& loglh);

  void set_stopping_criterion(StoppingCriterion* sc) { _criterion = sc; } // have to fix this
  void disable_stopping_rule();

private:
  TopologyOptMethod _topology_opt_method;
  double _lh_epsilon;
  double _lh_epsilon_brlen_triplet;
  int _spr_radius;
  double _spr_cutoff;
  int _spr_ntopol_keep;
  corax_random_state * _rstate;

  // nni params
  double _nni_epsilon;
  double _nni_tolerance;

  // stoping criteria
  StoppingRule _stopping_rule;
  StoppingCriterion *_criterion;

  // functions for adaptive mode
  int adaptive_radius(double difficulty);
};

#endif /* RAXML_OPTIMIZER_H_ */
