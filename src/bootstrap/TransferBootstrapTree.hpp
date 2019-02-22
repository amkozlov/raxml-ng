#ifndef RAXML_BOOTSTRAP_TRANSFERBOOTSTRAPTREE_HPP_
#define RAXML_BOOTSTRAP_TRANSFERBOOTSTRAPTREE_HPP_

#include "BootstrapTree.hpp"

class TransferBootstrapTree : public BootstrapTree
{
public:
  TransferBootstrapTree(const Tree& tree, bool naive = false);
  virtual ~TransferBootstrapTree();

protected:
  virtual void add_boot_splits_to_hashtable(const pll_unode_t& root);

private:
  pllmod_tbe_split_info_t * _split_info;
  bool _naive_method;
};

#endif /* RAXML_BOOTSTRAP_TRANSFERBOOTSTRAPTREE_HPP_ */
