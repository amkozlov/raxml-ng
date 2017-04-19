#include "BootstrapTree.hpp"

#include "../common.h"

using namespace std;

BootstrapTree::BootstrapTree (const Tree& tree) : Tree(tree), _num_bs_trees(0), _num_splits(0)
{
  _pll_splits_hash = nullptr;

  add_splits_to_hashtable(pll_utree_root(), true);
}

BootstrapTree::~BootstrapTree ()
{
  pll_utree_destroy(_pll_utree, nullptr);
  pllmod_utree_split_hashtable_destroy(_pll_splits_hash);
  free(_node_split_map);
}

void BootstrapTree::add_bootstrap_tree(const Tree& tree)
{
  if (tree.num_tips() != _num_tips)
    throw runtime_error("Incompatible tree!");

  add_splits_to_hashtable(tree.pll_utree_root(), false);
  _num_bs_trees++;
}

void BootstrapTree::add_splits_to_hashtable(const pll_unode_t& root, bool ref_tree)
{
  unsigned int n_splits;
  int ** node_split_map = ref_tree ? &_node_split_map : nullptr;
  int update_only = ref_tree ? 0 : 1;

  pll_split_t * ref_splits = pllmod_utree_split_create((pll_unode_t*) &root,
                                                       _num_tips,
                                                       &n_splits,
                                                       node_split_map);

  _pll_splits_hash = pllmod_utree_split_hashtable_insert(_pll_splits_hash,
                                                         ref_splits,
                                                         _num_tips,
                                                         n_splits,
                                                         update_only);

  pllmod_utree_split_destroy(ref_splits);

  if (ref_tree)
    _num_splits = n_splits;
}

void BootstrapTree::calc_support()
{
  vector<unsigned char> support(_pll_splits_hash->entry_count);

  for (unsigned int i = 0; i < _pll_splits_hash->table_size; ++i)
  {
    bitv_hash_entry_t * e =  _pll_splits_hash->table[i];
    while (e != NULL)
    {
//      printf("split %d, support %d\n", e->bip_number, e->support);
      support[e->bip_number] = (unsigned char) (e->support - 1) * 100 / _num_bs_trees;
      e = e->next;
    }
  }

//  printf("\n\n");
//  for (size_t i = 0; i < 3 * (_num_tips - 2); ++i)
//    printf("node_id %d, split_id %d\n", i, _node_split_map[i]);
//  printf("\n\n");

  PllNodeVector inner(_pll_utree->nodes + _pll_utree->tip_count,
                      _pll_utree->nodes + _pll_utree->tip_count + _pll_utree->inner_count - 1);

  vector<bool> split_plotted(_num_splits);
  for (auto node: inner)
  {
    assert(node->next);

    auto n = node;
    do
    {
      if (pllmod_utree_is_tip(n->back))
        continue;

      auto node_id = n->node_index - _num_tips;
      auto split_id = _node_split_map[node_id];
      assert(split_id >= 0);

      if (split_plotted[split_id])
        continue;

      n->label = n->next->label = n->next->next->label =
          strdup(std::to_string(support[split_id]).c_str());

      split_plotted[split_id].flip();

      break;
    }
    while ((n = n->next) != node);
  }
}


