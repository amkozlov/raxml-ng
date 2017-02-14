#ifndef RAXML_OPTIMIZER_H_
#define RAXML_OPTIMIZER_H_

#include "TreeInfo.hpp"

class Optimizer
{
public:
  Optimizer (const Options &opts);
  virtual
  ~Optimizer ();

  double optimize(TreeInfo& treeinfo, double lh_epsilon);
  double optimize(TreeInfo& treeinfo) { return optimize(treeinfo, _lh_epsilon); };
  double optimize_topology(TreeInfo& treeinfo);
private:
  double _lh_epsilon;
  int _spr_radius;
  double _spr_cutoff;
};

#endif /* RAXML_OPTIMIZER_H_ */
