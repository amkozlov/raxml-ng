#ifndef RAXML_BOOTSTRAP_GCFSUPPORTTREE_HPP_
#define RAXML_BOOTSTRAP_GCFSUPPORTTREE_HPP_

#include "SupportTree.hpp"

class GCFSupportTree : public SupportTree
{
public:
  GCFSupportTree (const Tree& tree = Tree());
  virtual ~GCFSupportTree() override;

  virtual void add_replicate_tree(const Tree& tree) override;
  virtual bool compute_support() override;

private:
  uintVector _num_decisive_trees;
};

#endif /* RAXML_BOOTSTRAP_GCFSUPPORTTREE_HPP_ */
