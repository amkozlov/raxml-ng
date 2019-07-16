#include "SupportTree.hpp"

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


SupportTree::SupportTree(const Tree& tree) : Tree(tree), _num_bs_trees(0)
{
  _pll_splits_hash = nullptr;
}

SupportTree::~SupportTree ()
{
  if (_pll_splits_hash)
    pllmod_utree_split_hashtable_destroy(_pll_splits_hash);
}

PllSplitSharedPtr SupportTree::extract_splits_from_tree(const pll_unode_t& root,
                                                        pll_unode_t ** node_split_map)
{
  PllSplitSharedPtr splits(pllmod_utree_split_create((pll_unode_t*) &root,
                                                       _num_tips,
                                                       node_split_map),
                           pllmod_utree_split_destroy);

  return splits;
}

void SupportTree::add_splits_to_hashtable(const PllSplitSharedPtr& splits,
                                          const doubleVector& support, bool update_only)
{
  _pll_splits_hash = pllmod_utree_split_hashtable_insert(_pll_splits_hash,
                                                         splits.get(),
                                                         _num_tips,
                                                         num_splits(),
                                                         support.empty() ? nullptr: support.data(),
                                                         update_only);
}


void SupportTree::add_tree(const Tree& tree)
{
  add_tree(tree.pll_utree_root());
}

void SupportTree::add_replicate_tree(const Tree& tree)
{
  if (tree.num_tips() != _num_tips)
    throw runtime_error("Incompatible tree!");

  _num_bs_trees++;

  /* extract replicate tree splits and add them into hashtable */
  add_tree(tree);
//  LOG_DEBUG_TS << "Added replicate trees: " << _num_bs_trees << endl;
}

void SupportTree::normalize_support_in_hashtable()
{
  for (unsigned int i = 0; i < _pll_splits_hash->table_size; ++i)
  {
    bitv_hash_entry_t * e =  _pll_splits_hash->table[i];
    while (e != NULL)
    {
      e->support /= _num_bs_trees;
      e = e->next;
    }
  }
}

void SupportTree::collect_support()
{
  _support.resize(_pll_splits_hash->entry_count);

  for (unsigned int i = 0; i < _pll_splits_hash->table_size; ++i)
  {
    bitv_hash_entry_t * e =  _pll_splits_hash->table[i];
    while (e != NULL)
    {
      _support[e->bip_number] = e->support;
      e = e->next;
    }
  }
}

bool SupportTree::compute_support()
{
  normalize_support_in_hashtable();

  collect_support();

  return true;
}

void SupportTree::draw_support(bool support_in_pct)
{
  if (!compute_support())
    return;

  LOG_DEBUG_TS << "Drawing support values on consensus tree..." << endl;

//  printf("\n\n");
//  for (size_t i = 0; i < num_splits(); ++i)
//    printf("node_id %d, split_id %d\n", _node_split_map[i]->node_index, i);
//  printf("\n\n");

  pll_unode_t ** node_map = _node_split_map.empty() ? nullptr : _node_split_map.data();
  pllmod_utree_draw_support(_pll_utree.get(), _support.data(), node_map,
                            support_in_pct ? support_fmt_pct : support_fmt_prop);

  LOG_DEBUG_TS << "Done!" << endl << endl;
}
