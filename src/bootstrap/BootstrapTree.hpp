#ifndef RAXML_BOOTSTRAP_BOOTSTRAPTREE_HPP_
#define RAXML_BOOTSTRAP_BOOTSTRAPTREE_HPP_

#include "../Tree.hpp"

typedef std::shared_ptr<pll_split_t> PllSplitSharedPtr;

class BootstrapTree : public Tree
{
public:
  BootstrapTree (const Tree& tree);

  virtual
  ~BootstrapTree ();

  void add_bootstrap_tree(const Tree& tree);

  void calc_support(bool support_in_pct = true);

protected:
  virtual void add_boot_splits_to_hashtable(const pll_unode_t& root);
  virtual void add_ref_splits_to_hashtable(const pll_unode_t& root);

  std::string format_support_value(double support);

protected:
  size_t _num_bs_trees;
  PllSplitSharedPtr _ref_splits;
  bitv_hashtable_t* _pll_splits_hash;
  std::vector<pll_unode_t*> _node_split_map;

private:
  void add_splits_to_hashtable(const pll_unode_t& root, bool update_only);
};

#endif /* RAXML_BOOTSTRAP_BOOTSTRAPTREE_HPP_ */
