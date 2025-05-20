#ifndef SRC_BOOTSTRAP_SPLITSTREE_HPP_
#define SRC_BOOTSTRAP_SPLITSTREE_HPP_

#include "../Tree.hpp"

typedef std::shared_ptr<corax_split_t> PllSplitSharedPtr;

class SplitsTree : public Tree
{
public:
  SplitsTree (const Tree& tree = Tree(), bool ref_splits_only = false);

  SplitsTree (const SplitsTree& other);
  SplitsTree& operator=(const SplitsTree& other) = delete;
  SplitsTree (SplitsTree&& other);
  SplitsTree& operator=(SplitsTree&& other);

  virtual
  ~SplitsTree ();

  virtual void add_replicate_tree(const Tree& tree);
  void add_splits(const SplitsTree& other);

  size_t num_bs_trees() const { return _num_bs_trees; }

protected:
  void init_hashtable(unsigned int slot_count = 0);

  PllSplitSharedPtr extract_splits_from_tree(const corax_unode_t& root,
                                             corax_unode_t ** node_split_map);
  void add_splits_to_hashtable(const PllSplitSharedPtr& splits,
                               const doubleVector& support, bool update_only);
  void set_reference_tree();

  virtual void get_replicate_supports(const corax_unode_t& root,
                                      PllSplitSharedPtr& splits, doubleVector& support);


protected:
  size_t _num_bs_trees;
  bool _ref_splits_only;
  PllSplitSharedPtr _ref_splits;
  bitv_hashtable_t* _pll_splits_hash;
  std::vector<corax_unode_t*> _node_split_map;
};

#endif /* SRC_BOOTSTRAP_SPLITSTREE_HPP_ */
