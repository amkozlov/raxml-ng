#include "TransferBootstrapTree.hpp"

/*typedef unsigned int TBEFlags;

const unsigned int TBE_DO_TABLE = 1;
const unsigned int TBE_DO_ARRAY = 2;
const unsigned int TBE_DO_OTHER = 4;

TransferBootstrapTree bstree(tree, true, 1., TBE_DO_TABLE | TBE_DO_OTHER);

TransferBootstrapTree bstree(tree, true, 1., false, true, false);
*/

TransferBootstrapTree::TransferBootstrapTree(const Tree& tree, bool naive, double tbe_cutoff, bool doTable, bool doArray, bool doTree) :
   SupportTree (tree), _split_info(nullptr), _naive_method(naive)
{
  assert(num_splits() > 0);
  _split_node_map.resize(num_splits());

  /* extract reference tree splits and add them into hashtable */
  add_tree(pll_utree_root());

  if (!_naive_method)
  {
    _split_info = pllmod_utree_tbe_nature_init((pll_unode_t*) &pll_utree_root(), _num_tips,
                                              (const pll_unode_t**) _split_node_map.data());
    if (doTable || doArray || doTree) {
      _extra_info = pllmod_tbe_extra_info_create(num_splits(), _num_tips, tbe_cutoff, doTable, doArray, doTree);
    }
  }
}

const std::vector<pll_unode_t*> TransferBootstrapTree::get_split_node_map() const {
	return _split_node_map;
}

pllmod_tbe_extra_info_t* TransferBootstrapTree::get_extra_info() const {
	return _extra_info;
}

pllmod_tbe_split_info_t* TransferBootstrapTree::get_split_info() const {
	return _split_info;
}

/*
void TransferBootstrapTree::collect_support() {
	SupportTree::collect_support();
	// do the postprocessing of extra info
}
*/

TransferBootstrapTree::~TransferBootstrapTree()
{
  if (_split_info)
    free(_split_info);
  if (_extra_info)
	pllmod_tbe_extra_info_destroy(_extra_info, num_splits());
}

void TransferBootstrapTree::add_tree(const pll_unode_t& root)
{
  bool ref_tree = (_num_bs_trees == 0);
  doubleVector support(num_splits(), 0.);

  if (ref_tree)
  {
    _ref_splits = extract_splits_from_tree(root, _split_node_map.data());

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
      pllmod_utree_tbe_nature_extra(_ref_splits.get(), splits.get(), (pll_unode_t*) &root,
                                               _num_tips, support.data(), _split_info, _extra_info);
    }

    add_splits_to_hashtable(_ref_splits, support, 1);
  }
}
