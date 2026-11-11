#ifndef RAXML_BOOTSTRAP_TCFSUPPORTTREE_HPP_
#define RAXML_BOOTSTRAP_TCFSUPPORTTREE_HPP_

#include "SupportTree.hpp"

class TCFSupportTree : public SupportTree
{
public:
  TCFSupportTree (const Tree& tree = Tree());
  virtual ~TCFSupportTree() override;

  virtual void add_replicate_tree(const Tree& tree) override;
  virtual bool compute_support() override;

private:
  uintVector _num_decisive_trees;
};

#endif /* RAXML_BOOTSTRAP_TCFSUPPORTTREE_HPP_ */
