#ifndef RAXML_BOOTSTRAP_CONSENSUSTREE_HPP_
#define RAXML_BOOTSTRAP_CONSENSUSTREE_HPP_

#include "SupportTree.hpp"

class ConsensusTree : public SupportTree
{
public:
  ConsensusTree (const TreeList& trees, unsigned int consense_cutoff);
  ConsensusTree (const SplitsTree& splits, unsigned int consense_cutoff);
  virtual
  ~ConsensusTree ();

  virtual bool compute_support();

protected:
  void init_cutoff(unsigned int consense_cutoff);
  virtual void add_tree(const corax_unode_t& root);

private:
   double _cutoff;
};

#endif /* RAXML_BOOTSTRAP_CONSENSUSTREE_HPP_ */
