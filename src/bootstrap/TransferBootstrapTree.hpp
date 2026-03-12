#ifndef RAXML_BOOTSTRAP_TRANSFERBOOTSTRAPTREE_HPP_
#define RAXML_BOOTSTRAP_TRANSFERBOOTSTRAPTREE_HPP_

#include "SupportTree.hpp"

class TransferBootstrapTree : public SupportTree
{
public:
  TransferBootstrapTree(const Tree& tree, bool naive = false);
  virtual ~TransferBootstrapTree();

protected:
  virtual void get_replicate_supports(const corax_unode_t& root,
                                      PllSplitSharedPtr& splits, doubleVector& support);

private:
  corax_tbe_split_info_t * _split_info;
  bool _naive_method;
};

#endif /* RAXML_BOOTSTRAP_TRANSFERBOOTSTRAPTREE_HPP_ */
