#include "BootstrapTree.hpp"

#include "../common.h"

BootstrapTree::BootstrapTree (const Tree& tree) : SupportTree(tree)
{
  assert(num_splits() > 0);
}

BootstrapTree::~BootstrapTree ()
{
}
