#ifndef RAXML_BOOTSTRAP_BOOTSTRAPTREE_HPP_
#define RAXML_BOOTSTRAP_BOOTSTRAPTREE_HPP_

#include "SupportTree.hpp"

class BootstrapTree : public SupportTree
{
public:
  BootstrapTree (const Tree& tree);

  virtual
  ~BootstrapTree ();

protected:
  virtual void add_tree(const pll_unode_t& root);
};

#endif /* RAXML_BOOTSTRAP_BOOTSTRAPTREE_HPP_ */
