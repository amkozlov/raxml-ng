#include "TransferBootstrapTree.hpp"

TransferBootstrapTree::TransferBootstrapTree(const Tree& tree, bool naive) :
   SupportTree (tree), _split_info(nullptr), _naive_method(naive)
{
  assert(num_splits() > 0);
  _node_split_map.resize(num_splits());

  /* extract reference tree splits and add them into hashtable */
  add_tree(pll_utree_root());

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

void TransferBootstrapTree::add_tree(const pll_unode_t& root)
{
  bool ref_tree = (_num_bs_trees == 0);
  doubleVector support(num_splits(), 0.);

  if (ref_tree)
  {
    _ref_splits = extract_splits_from_tree(root, _node_split_map.data());

    add_splits_to_hashtable(_ref_splits, support, 0);
  }
  else
  {
    assert(_ref_splits);

    auto splits = extract_splits_from_tree(root, nullptr);

    // compute TBE
    if (_naive_method)
      pllmod_utree_tbe_naive(_ref_splits.get(), splits.get(), _num_tips, support.data());
    else
    {
      pllmod_utree_tbe_nature(_ref_splits.get(), splits.get(), (pll_unode_t*) &root,
                                               _num_tips, support.data(), _split_info);
    }

    add_splits_to_hashtable(_ref_splits, support, 1);
  }
}
