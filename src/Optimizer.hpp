#ifndef RAXML_OPTIMIZER_H_
#define RAXML_OPTIMIZER_H_

#include "TreeInfo.hpp"
#include "Checkpoint.hpp"

#include <stdio.h>

class Optimizer
{
public:
  Optimizer (const Options& opts);
  virtual
  ~Optimizer ();

  double optimize_model(TreeInfo& treeinfo, double lh_epsilon);
  double optimize_model(TreeInfo& treeinfo) { return optimize_model(treeinfo, _lh_epsilon); };
  double optimize_topology(TreeInfo& treeinfo, CheckpointManager& cm);
  double optimize_topology_adaptive(TreeInfo& treeinfo, CheckpointManager& cm, double difficulty);
  double evaluate(TreeInfo& treeinfo, CheckpointManager& cm);
  void nni(TreeInfo& treeinfo, nni_round_params& nni_params, double& loglh);

private:
  double _lh_epsilon;
  int _spr_radius;
  double _spr_cutoff;
  bool _optimized_spr;

  // nni params
  double _nni_epsilon;
  double _nni_tolerance;

  // functions for adaptive mode
  double convergence_rate(CheckpointManager& cm, double test_loglh);
  bool first_search_done(CheckpointManager& cm);
  bool converged(CheckpointManager& cm, double test_loglh, double epsilon);
  int adaptive_slow_spr_radius(double difficulty);
};

#endif /* RAXML_OPTIMIZER_H_ */
