#include "BootstrapTree.hpp"

#include "../common.h"

using namespace std;

char * support_fmt_pct(double support)
{
  char *str;
  int size_alloced = asprintf(&str, "%u", (unsigned int) round(support * 100.));

  return size_alloced >= 0 ? str : NULL;
}

char * support_fmt_prop(double support)
{
  const unsigned int precision = logger().precision(LogElement::brlen);

  char * str;
  int size_alloced = asprintf(&str, "%.*lf", precision, support);

  return size_alloced >= 0 ? str : NULL;
}


BootstrapTree::BootstrapTree (const Tree& tree) : Tree(tree), _num_bs_trees(0)
{
  _pll_splits_hash = nullptr;
  _node_split_map.resize(num_splits());

  add_ref_splits_to_hashtable(pll_utree_root());
}

BootstrapTree::~BootstrapTree ()
{
  pllmod_utree_split_hashtable_destroy(_pll_splits_hash);
}

void BootstrapTree::add_bootstrap_tree(const Tree& tree)
{
  if (tree.num_tips() != _num_tips)
    throw runtime_error("Incompatible tree!");

  add_boot_splits_to_hashtable(tree.pll_utree_root());
  _num_bs_trees++;
  LOG_DEBUG_TS << "Added bootstrap trees: " << _num_bs_trees << endl;
}

void BootstrapTree::add_boot_splits_to_hashtable(const pll_unode_t& root)
{
  add_splits_to_hashtable(root, false);
}

void BootstrapTree::add_ref_splits_to_hashtable(const pll_unode_t& root)
{
  add_splits_to_hashtable(root, true);
}

void BootstrapTree::add_splits_to_hashtable(const pll_unode_t& root, bool ref_tree)
{
  pll_unode_t ** node_split_map = ref_tree ? _node_split_map.data() : nullptr;
  int update_only = ref_tree ? 0 : 1;
  doubleVector support(num_splits(), ref_tree ? 0. : 1.);

  PllSplitSharedPtr splits(pllmod_utree_split_create((pll_unode_t*) &root,
                                                       _num_tips,
                                                       node_split_map),
                           pllmod_utree_split_destroy);

  if (ref_tree)
    _ref_splits = splits;

  _pll_splits_hash = pllmod_utree_split_hashtable_insert(_pll_splits_hash,
                                                         splits.get(),
                                                         _num_tips,
                                                         num_splits(),
                                                         support.data(),
                                                         update_only);
}

void BootstrapTree::calc_support(bool support_in_pct)
{
  vector<double> support(_pll_splits_hash->entry_count);

  for (unsigned int i = 0; i < _pll_splits_hash->table_size; ++i)
  {
    bitv_hash_entry_t * e =  _pll_splits_hash->table[i];
    while (e != NULL)
    {
      assert(e->support <= _num_bs_trees);

//      printf("split %d, support %lf\n", e->bip_number, e->support);
      support[e->bip_number] = e->support / _num_bs_trees;
      e = e->next;
    }
  }

//  printf("\n\n");
//  for (size_t i = 0; i < 3 * (_num_tips - 2); ++i)
//    printf("node_id %d, split_id %d\n", i, _node_split_map[i]);
//  printf("\n\n");

  pllmod_utree_draw_support(_pll_utree.get(), support.data(), _node_split_map.data(),
      support_in_pct ? support_fmt_pct : support_fmt_prop);
}
