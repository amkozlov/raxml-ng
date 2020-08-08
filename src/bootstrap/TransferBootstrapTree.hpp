#ifndef RAXML_BOOTSTRAP_TRANSFERBOOTSTRAPTREE_HPP_
#define RAXML_BOOTSTRAP_TRANSFERBOOTSTRAPTREE_HPP_

#include "SupportTree.hpp"

class TransferBootstrapTree : public SupportTree
{
public:
  TransferBootstrapTree(const Tree& tree, bool naive = false);
  virtual ~TransferBootstrapTree();

protected:
  virtual void add_tree(const pll_unode_t& root);

protected:
  PllSplitSharedPtr _ref_splits;

private:
  pllmod_tbe_split_info_t * _split_info;
  bool _naive_method;
};

#endif /* RAXML_BOOTSTRAP_TRANSFERBOOTSTRAPTREE_HPP_ */
