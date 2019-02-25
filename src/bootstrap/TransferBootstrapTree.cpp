#include "TransferBootstrapTree.hpp"

TransferBootstrapTree::TransferBootstrapTree(const Tree& tree, bool naive) :
   BootstrapTree (tree), _split_info(nullptr), _naive_method(naive)
{
  if (!_naive_method)
  {
    _split_info = pllmod_utree_tbe_nature_init((pll_unode_t*) &pll_utree_root(), _num_tips,
                                              (const pll_unode_t**) _node_split_map.data());
  }
}

TransferBootstrapTree::~TransferBootstrapTree()
{
  if (_split_info)
    free(_split_info);
}

void TransferBootstrapTree::add_boot_splits_to_hashtable(const pll_unode_t& root)
{
  doubleVector tbe(num_splits(), 1.0);

  assert(_ref_splits);

  pll_split_t * splits = pllmod_utree_split_create((pll_unode_t*) &root,
                                                       _num_tips,
                                                       nullptr);

  // compute TBE
  if (_naive_method)
    pllmod_utree_tbe_naive(_ref_splits.get(), splits, _num_tips, tbe.data());
  else
  {
    pllmod_utree_tbe_nature(_ref_splits.get(), splits, (pll_unode_t*) &root,
                                             _num_tips, tbe.data(), _split_info);
  }

  pllmod_utree_split_destroy(splits);

  _pll_splits_hash = pllmod_utree_split_hashtable_insert(_pll_splits_hash,
                                                         _ref_splits.get(),
                                                         _num_tips,
                                                         num_splits(),
                                                         tbe.data(),
                                                         1 /* update_only */);
}
