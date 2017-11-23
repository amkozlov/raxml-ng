#include "BootstrapTree.hpp"

#include "../common.h"

using namespace std;

BootstrapTree::BootstrapTree (const Tree& tree) : Tree(tree), _num_bs_trees(0)
{
  _pll_splits_hash = nullptr;
  _node_split_map.resize(num_splits());

  add_splits_to_hashtable(pll_utree_root(), true);
}

BootstrapTree::~BootstrapTree ()
{
  pllmod_utree_split_hashtable_destroy(_pll_splits_hash);
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
  pll_unode_t ** node_split_map = ref_tree ? _node_split_map.data() : nullptr;
  int update_only = ref_tree ? 0 : 1;

  pll_split_t * ref_splits = pllmod_utree_split_create((pll_unode_t*) &root,
                                                       _num_tips,
                                                       node_split_map);

  _pll_splits_hash = pllmod_utree_split_hashtable_insert(_pll_splits_hash,
                                                         ref_splits,
                                                         _num_tips,
                                                         num_splits(),
                                                         nullptr,
                                                         update_only);

  pllmod_utree_split_destroy(ref_splits);
}

void BootstrapTree::calc_support()
{
  vector<unsigned char> support(_pll_splits_hash->entry_count);

  for (unsigned int i = 0; i < _pll_splits_hash->table_size; ++i)
  {
    bitv_hash_entry_t * e =  _pll_splits_hash->table[i];
    while (e != NULL)
    {
      assert(e->support-1 <= _num_bs_trees);

//      printf("split %d, support %d\n", e->bip_number, e->support);
      support[e->bip_number] = (unsigned char) round((e->support - 1) * 100 / _num_bs_trees);
      e = e->next;
    }
  }

//  printf("\n\n");
//  for (size_t i = 0; i < 3 * (_num_tips - 2); ++i)
//    printf("node_id %d, split_id %d\n", i, _node_split_map[i]);
//  printf("\n\n");

  for (size_t i = 0; i < _node_split_map.size(); ++i)
  {
    auto node = _node_split_map[i];

    /* this has to be an inner node! */
    assert(node->next);

    assert(support[i] <= 100);

    node->label = node->next->label = node->next->next->label =
        strdup(std::to_string(support[i]).c_str());
  }
}
