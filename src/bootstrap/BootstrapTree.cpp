#include "BootstrapTree.hpp"

#include "../common.h"

BootstrapTree::BootstrapTree (const Tree& tree) : SupportTree(tree)
{
  assert(num_splits() > 0);
  _node_split_map.resize(num_splits());

  /* extract reference tree splits and add them into hashtable */
  add_tree(pll_utree_root());
}

BootstrapTree::~BootstrapTree ()
{
}

void BootstrapTree::add_tree(const pll_unode_t& root)
{
  bool ref_tree = (_num_bs_trees == 0);
  pll_unode_t ** node_split_map = ref_tree ? _node_split_map.data() : nullptr;
  int update_only = ref_tree ? 0 : 1;
  doubleVector support(num_splits(), ref_tree ? 0. : 1.);

  auto splits = extract_splits_from_tree(root, node_split_map);

  add_splits_to_hashtable(splits, support, update_only);
}
