#include "TransferBootstrapTree.hpp"

TransferBootstrapTree::TransferBootstrapTree(const Tree& tree, bool naive) :
   SupportTree (tree), _split_info(nullptr), _naive_method(naive)
{
  assert(num_splits() > 0);

  if (!_naive_method)
  {
    _split_info = corax_utree_tbe_nature_init((corax_unode_t*) &pll_utree_root(),
                                              (unsigned int) _num_tips,
                                              (const corax_unode_t**) _node_split_map.data());
  }
}

TransferBootstrapTree::~TransferBootstrapTree()
{
  if (_split_info)
    free(_split_info);
}

void TransferBootstrapTree::get_replicate_supports(const Tree& tree,
                                                   PllSplitSharedPtr& splits, doubleVector& support)
{
    assert(_ref_splits);

    support.resize(num_splits());

    const corax_unode_t& root = tree.pll_utree_root();

    // compute TBE
    if (_naive_method)
    {
      corax_utree_tbe_naive(_ref_splits.get(),
                            num_splits(),
                            splits.get(),
                            tree.num_splits(),
                            (unsigned int) _num_tips,
                            support.data());
    }
    else
    {
      corax_utree_tbe_nature(_ref_splits.get(),
                             splits.get(),
                             (corax_unode_t*) &root,
                             (unsigned int) _num_tips,
                             support.data(),
                             _split_info);
    }

    /* NB: With TBE, each replicate split can contribute support to multiple reference branches!
     * Hence, we must update support for ALL ref branches, not just those found in the replicate! */
    splits = _ref_splits;

//    printf("TBE support: ");
//    for (auto s: support)
//      printf("%lf ", s);
//    printf("\n");
}
