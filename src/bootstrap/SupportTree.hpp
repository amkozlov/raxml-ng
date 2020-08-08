#ifndef SRC_BOOTSTRAP_SUPPORTTREE_HPP_
#define SRC_BOOTSTRAP_SUPPORTTREE_HPP_

#include "../Tree.hpp"

typedef std::shared_ptr<pll_split_t> PllSplitSharedPtr;


class SupportTree : public Tree
{
public:
  SupportTree (const Tree& tree = Tree());

  virtual
  ~SupportTree ();

  virtual void add_replicate_tree(const Tree& tree);

  void draw_support(bool support_in_pct = true);

protected:
  PllSplitSharedPtr extract_splits_from_tree(const pll_unode_t& root,
                                             pll_unode_t ** node_split_map);
  void add_splits_to_hashtable(const PllSplitSharedPtr& splits,
                               const doubleVector& support, bool update_only);
  void add_tree(const Tree& tree);
  virtual void add_tree(const pll_unode_t& root) = 0;


  void normalize_support_in_hashtable();
  void collect_support();
  virtual bool compute_support();

protected:
  size_t _num_bs_trees;
  bitv_hashtable_t* _pll_splits_hash;
  std::vector<pll_unode_t*> _node_split_map;
  doubleVector _support;
};

#endif /* SRC_BOOTSTRAP_SUPPORTTREE_HPP_ */
