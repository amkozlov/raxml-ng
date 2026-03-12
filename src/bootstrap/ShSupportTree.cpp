#include "ShSupportTree.hpp"

ShSupportTree::ShSupportTree (const Tree& tree, const doubleVector& sh_support_values) :
  SupportTree(tree)
{
  doubleVector support(num_splits(), 0.);

  for (size_t i = 0; i < _node_split_map.size(); ++i)
  {
    auto pmat_idx = _node_split_map[i]->pmatrix_index;
    support[i] = sh_support_values[pmat_idx] / 100.;
  }

  add_splits_to_hashtable(_ref_splits, support, false);
}

ShSupportTree::~ShSupportTree ()
{
}

