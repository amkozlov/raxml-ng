#include "SplitsTree.hpp"

using namespace std;

SplitsTree::SplitsTree(const Tree& tree, bool ref_splits_only) : Tree(tree), _num_bs_trees(0),
    _ref_splits_only(ref_splits_only), _ref_splits(nullptr), _pll_splits_hash(nullptr)
{
  if (num_splits() > 0)
    set_reference_tree();
}

SplitsTree::SplitsTree (const SplitsTree& other) : Tree(other), _num_bs_trees(0),
    _ref_splits_only(other._ref_splits_only), _ref_splits(nullptr), _pll_splits_hash(nullptr)
{
  if (num_splits() > 0)
    set_reference_tree();
  add_splits(other);
}

SplitsTree::SplitsTree (SplitsTree&& other) : Tree(other)
{
  swap(_num_bs_trees, other._num_bs_trees);
  swap(_ref_splits_only, other._ref_splits_only);
  swap(_pll_splits_hash, other._pll_splits_hash);
  _ref_splits.swap(other._ref_splits);
}

SplitsTree& SplitsTree::operator=(SplitsTree&& other)
{
  Tree::operator=(other);
  if (this != &other)
  {
    _num_bs_trees = 0;
    corax_utree_split_hashtable_destroy(_pll_splits_hash);
    _pll_splits_hash = nullptr;
    _ref_splits.reset();

    _pll_utree.reset(other._pll_utree.release());

    swap(_num_bs_trees, other._num_bs_trees);
    swap(_pll_splits_hash, other._pll_splits_hash);
    swap(_ref_splits, other._ref_splits);
  }

  return *this;
}


SplitsTree::~SplitsTree ()
{
  if (_pll_splits_hash)
    corax_utree_split_hashtable_destroy(_pll_splits_hash);
}

void SplitsTree::init_hashtable(unsigned int slot_count)
{
  assert(!_pll_splits_hash && _num_tips > 0);
  _pll_splits_hash = corax_utree_split_hashtable_create(_num_tips, slot_count);
}

PllSplitSharedPtr SplitsTree::extract_splits_from_tree(const corax_unode_t& root,
                                                       corax_unode_t ** node_split_map)
{
  PllSplitSharedPtr splits(corax_utree_split_create((corax_unode_t*) &root,
                                                       _num_tips,
                                                       node_split_map),
                           corax_utree_split_destroy);

  return splits;
}

void SplitsTree::add_splits_to_hashtable(const PllSplitSharedPtr& splits,
                                         const doubleVector& support, bool update_only)
{
  _pll_splits_hash = corax_utree_split_hashtable_insert(_pll_splits_hash,
                                                         splits.get(),
                                                         _num_tips,
                                                         num_splits(),
                                                         support.empty() ? nullptr: support.data(),
                                                         update_only);
}

void SplitsTree::set_reference_tree()
{
  assert(num_splits() > 0);

  _node_split_map.resize(num_splits());
   doubleVector support(num_splits(), 0.);

  /* extract reference tree splits and add them into hashtable */
  _ref_splits = extract_splits_from_tree(pll_utree_root(), _node_split_map.data());

  add_splits_to_hashtable(_ref_splits, support, false);
}

void SplitsTree::get_replicate_supports(const corax_unode_t& root,
                                         PllSplitSharedPtr& splits, doubleVector& support)
{
  /* by default, do not modify support vector -> every split gets support +1 */
  RAXML_UNUSED(root);
  RAXML_UNUSED(splits);
  RAXML_UNUSED(support);
}

void SplitsTree::add_replicate_tree(const Tree& tree)
{
  if (tree.num_tips() != _num_tips)
    throw runtime_error("SplitsTree: Incompatible replicate tree!");

  _num_bs_trees++;

  /* extract replicate tree splits and add them into hashtable */
  const corax_unode_t& root = tree.pll_utree_root();
  auto splits = extract_splits_from_tree(root, nullptr);

  doubleVector support;
  get_replicate_supports(root, splits, support);

  add_splits_to_hashtable(splits, support, _ref_splits_only);
//  LOG_DEBUG_TS << "Added replicate trees: " << _num_bs_trees << endl;
}

void SplitsTree::add_splits(const SplitsTree& other)
{
  if (other.num_tips() != _num_tips)
    throw runtime_error("SplitsTree: Incompatible replicate tree!");

  /* copy splits from existing hashtable in other support tree */
  auto splits_added = corax_utree_split_hashtable_insert_copy(_pll_splits_hash,
                                                              other._pll_splits_hash);

  libpll_check_error();

  _num_bs_trees += other.num_bs_trees();

  LOG_DEBUG_TS << "Added " << splits_added << " splits from "
               << other.num_bs_trees() << " replicate trees." << endl;
}
