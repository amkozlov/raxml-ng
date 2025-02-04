#ifndef SRC_BOOTSTRAP_SUPPORTTREE_HPP_
#define SRC_BOOTSTRAP_SUPPORTTREE_HPP_

#include "../Tree.hpp"

typedef std::shared_ptr<corax_split_t> PllSplitSharedPtr;

class SupportTree : public Tree
{
public:
  SupportTree (const Tree& tree = Tree());

  virtual
  ~SupportTree ();

  virtual void add_replicate_tree(const Tree& tree);

  virtual bool compute_support();
  void draw_support(bool support_in_pct = true);

  const doubleVector& support() const { return _support; }

protected:
  PllSplitSharedPtr extract_splits_from_tree(const corax_unode_t& root,
                                             corax_unode_t ** node_split_map);
  void add_splits_to_hashtable(const PllSplitSharedPtr& splits,
                               const doubleVector& support, bool update_only);
  void set_reference_tree();

  virtual void get_replicate_supports(const corax_unode_t& root,
                                      PllSplitSharedPtr& splits, doubleVector& support);

  void normalize_support_in_hashtable();
  void collect_support();

protected:
  size_t _num_bs_trees;
  bool _ref_splits_only;
  PllSplitSharedPtr _ref_splits;
  bitv_hashtable_t* _pll_splits_hash;
  std::vector<corax_unode_t*> _node_split_map;
  doubleVector _support;
};

#endif /* SRC_BOOTSTRAP_SUPPORTTREE_HPP_ */
