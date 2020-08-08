#include "TransferBootstrapTree.hpp"

TransferBootstrapTree::TransferBootstrapTree(const Tree& tree) :
   BootstrapTree (tree)
{
}

TransferBootstrapTree::~TransferBootstrapTree()
{
}


void TransferBootstrapTree::add_boot_splits_to_hashtable(const pll_unode_t& root)
{
  doubleVector tbe(num_splits(), 1.0);

  assert(_ref_splits);

  pll_split_t * splits = pllmod_utree_split_create((pll_unode_t*) &root,
                                                       _num_tips,
                                                       nullptr);

  // compute TBE
  pllmod_utree_split_transfer_support(_ref_splits.get(), splits, _num_tips, tbe.data());

  pllmod_utree_split_destroy(splits);

  _pll_splits_hash = pllmod_utree_split_hashtable_insert(_pll_splits_hash,
                                                         _ref_splits.get(),
                                                         _num_tips,
                                                         num_splits(),
                                                         tbe.data(),
                                                         1 /* update_only */);
}
