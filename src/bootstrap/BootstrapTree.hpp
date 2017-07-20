#ifndef RAXML_BOOTSTRAP_BOOTSTRAPTREE_HPP_
#define RAXML_BOOTSTRAP_BOOTSTRAPTREE_HPP_

#include "../Tree.hpp"

class BootstrapTree : public Tree
{
public:
  BootstrapTree (const Tree& tree);

  virtual
  ~BootstrapTree ();

  void add_bootstrap_tree(const Tree& tree);

  void calc_support();

private:
  size_t _num_bs_trees;
  bitv_hashtable_t* _pll_splits_hash;
  std::vector<pll_unode_t*> _node_split_map;

  void add_splits_to_hashtable(const pll_unode_t& root, bool update_only);
};

#endif /* RAXML_BOOTSTRAP_BOOTSTRAPTREE_HPP_ */
