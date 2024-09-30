#ifndef RAXML_BOOTSTRAP_BOOTSTRAPTREE_HPP_
#define RAXML_BOOTSTRAP_BOOTSTRAPTREE_HPP_

#include "SupportTree.hpp"

class BootstrapTree : public SupportTree
{
public:
  BootstrapTree (const Tree& tree);

  virtual
  ~BootstrapTree ();
};

#endif /* RAXML_BOOTSTRAP_BOOTSTRAPTREE_HPP_ */
