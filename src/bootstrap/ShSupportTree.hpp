#ifndef SRC_BOOTSTRAP_SHSUPPORTTREE_HPP_
#define SRC_BOOTSTRAP_SHSUPPORTTREE_HPP_

#include "SupportTree.hpp"

class ShSupportTree : public SupportTree
{
public:
  ShSupportTree (const Tree& tree, const doubleVector& sh_support_values);
  virtual
  ~ShSupportTree ();
};

#endif /* SRC_BOOTSTRAP_SHSUPPORTTREE_HPP_ */
