#ifndef SRC_TOPOLOGY_CONSTRAINTTREE_HPP_
#define SRC_TOPOLOGY_CONSTRAINTTREE_HPP_

#include "../bootstrap/SupportTree.hpp"

class ConstraintTree : public Tree
{
public:
  ConstraintTree() : Tree() {};
  ConstraintTree(const corax_utree_t& pll_utree);

  virtual ~ConstraintTree ();
//  ConstraintTree (const ConstraintTree &other);
//  ConstraintTree (ConstraintTree &&other);
//  ConstraintTree& operator= (const ConstraintTree &other);
//  ConstraintTree& operator= (ConstraintTree &&other);

  bool compatible(const Tree& tree) const;

private:
  mutable PllSplitSharedPtr _cons_splits;

  void extract_splits() const;
};

#endif /* SRC_TOPOLOGY_CONSTRAINTTREE_HPP_ */
