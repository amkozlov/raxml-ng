#ifndef RAXML_BOOTSTRAP_CONSENSUSTREE_HPP_
#define RAXML_BOOTSTRAP_CONSENSUSTREE_HPP_

#include "SupportTree.hpp"

class ConsensusTree : public SupportTree
{
public:
  ConsensusTree (const TreeList& trees, unsigned int consense_cutoff);
  virtual
  ~ConsensusTree ();

protected:
  virtual void add_tree(const pll_unode_t& root);
  virtual bool compute_support();

private:
   double _cutoff;
};

#endif /* RAXML_BOOTSTRAP_CONSENSUSTREE_HPP_ */
