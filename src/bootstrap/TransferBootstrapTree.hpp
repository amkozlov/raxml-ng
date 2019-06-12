#ifndef RAXML_BOOTSTRAP_TRANSFERBOOTSTRAPTREE_HPP_
#define RAXML_BOOTSTRAP_TRANSFERBOOTSTRAPTREE_HPP_

#include "SupportTree.hpp"

class TransferBootstrapTree : public SupportTree
{
public:
  TransferBootstrapTree(const Tree& tree, bool naive = false, double tbe_cutoff = 0.3, bool doTable = false, bool doArray = false, bool doTree = false);
  virtual ~TransferBootstrapTree();

  void postprocess_extra(); //...
  pllmod_tbe_extra_info_t* get_extra_info() const;
  const std::vector<pll_unode_t*> get_split_node_map() const;
  pllmod_tbe_split_info_t* get_split_info() const;

protected:
  virtual void add_tree(const pll_unode_t& root);

protected:
  PllSplitSharedPtr _ref_splits;

private:
  pllmod_tbe_split_info_t * _split_info;
  pllmod_tbe_extra_info_t * _extra_info;
  bool _naive_method;
};

#endif /* RAXML_BOOTSTRAP_TRANSFERBOOTSTRAPTREE_HPP_ */
