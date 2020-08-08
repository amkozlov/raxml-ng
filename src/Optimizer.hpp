#ifndef RAXML_OPTIMIZER_H_
#define RAXML_OPTIMIZER_H_

#include "TreeInfo.hpp"
#include "Checkpoint.hpp"

class Optimizer
{
public:
  Optimizer (const Options& opts);
  virtual
  ~Optimizer ();

  double optimize_model(TreeInfo& treeinfo, double lh_epsilon);
  double optimize_model(TreeInfo& treeinfo) { return optimize_model(treeinfo, _lh_epsilon); };
  double optimize_topology(TreeInfo& treeinfo, CheckpointManager& cm);
  double evaluate(TreeInfo& treeinfo, CheckpointManager& cm);
private:
  double _lh_epsilon;
  int _spr_radius;
  double _spr_cutoff;
};

#endif /* RAXML_OPTIMIZER_H_ */
