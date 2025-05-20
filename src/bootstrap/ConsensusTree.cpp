#include "ConsensusTree.hpp"

using namespace std;

ConsensusTree::ConsensusTree(const SplitsTree& splits, unsigned int consense_cutoff) : SupportTree()
{
  init_cutoff(consense_cutoff);
  pll_utree(splits.pll_utree());
  init_hashtable();
  add_splits(splits);
}


ConsensusTree::ConsensusTree (const TreeList& trees, unsigned int consense_cutoff) : SupportTree()
{
  assert(!trees.empty());

  init_cutoff(consense_cutoff);
  /* add new splits from replicates */
  _ref_splits_only = false;

  pll_utree(trees[0].pll_utree());

  LOG_DEBUG_TS << "Extractring splits from replicate trees..." << endl;

  for (const auto& t: trees)
    add_replicate_tree(t);

  assert(_num_bs_trees == trees.size());

  LOG_DEBUG_TS << "Extracted " << _pll_splits_hash->entry_count << " splits from "
               << _num_bs_trees << " trees." <<  endl;
}

ConsensusTree::~ConsensusTree ()
{
}

void ConsensusTree::init_cutoff(unsigned int consense_cutoff)
{
  assert(consense_cutoff <= 100);
  _cutoff = ((double) consense_cutoff) / 100.;
}

void ConsensusTree::add_tree(const corax_unode_t& root)
{
  corax_unode_t ** node_split_map = nullptr;
  doubleVector support;
  int update_only = 0;

  auto splits = extract_splits_from_tree(root, node_split_map);

  add_splits_to_hashtable(splits, support, update_only);
}

bool ConsensusTree::compute_support()
{
  LOG_DEBUG_TS << "Building consensus split system..." << endl;

  /* normalize support values */
  normalize_support_in_hashtable();

  /* build final split system */
  corax_split_system_t * split_system = corax_utree_split_consensus(_pll_splits_hash,
                                                                   _num_tips,
                                                                   _cutoff);

  if (!split_system)
    libpll_check_error("Failed to create consensus tree (pllmod_utree_split_consensus)");

  LOG_DEBUG_TS << "Split system size: " << split_system->split_count << endl;

  LOG_DEBUG_TS << "Building consensus tree topology..." << endl;

  /* build tree from splits */
  corax_consensus_utree_t * cons_tree = corax_utree_from_splits(split_system,
                                                               _num_tips,
                                                               (char * const *) tip_labels_cstr().data());

  if (!cons_tree)
    libpll_check_error("Failed to create consensus tree (pllmod_utree_from_splits)");

  LOG_DEBUG_TS << "Consensus tree has " << to_string(cons_tree->branch_count)
               << " internal branches." << endl;

  /* set consensus tree topology */
  pll_utree(_num_tips, *cons_tree->tree);

  /* map pll_unodes to splits */
  if (cons_tree->branch_count > 0)
  {
    _node_split_map.resize(_pll_utree->inner_count);
    _support.resize(_pll_utree->inner_count);
    for (unsigned int i = 0; i < _pll_utree->inner_count; ++i)
    {
      auto node = _pll_utree->nodes[_pll_utree->tip_count + i];
      assert(node->data);
      _node_split_map[i] = node;
      _support[i] = ((corax_consensus_data_t *) node->data)->support;
    }
  }

  // after calling corax_utree_split_consensus(), node->data contains
  // non-owning pointers to a separate data structure which we do not need
  // and which will be destroyed before return -> hence reset those pointers!
  for (auto n: subnodes())
  {
    n->data = 0;
  }

  corax_utree_split_system_destroy(split_system);
  corax_utree_consensus_destroy(cons_tree);

  return true;
}


