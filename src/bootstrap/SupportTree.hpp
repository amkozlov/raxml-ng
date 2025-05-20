#ifndef SRC_BOOTSTRAP_SUPPORTTREE_HPP_
#define SRC_BOOTSTRAP_SUPPORTTREE_HPP_

#include "SplitsTree.hpp"

typedef std::shared_ptr<corax_split_t> PllSplitSharedPtr;

class SupportTree : public SplitsTree
{
public:
  SupportTree (const Tree& tree = Tree());

  virtual
  ~SupportTree ();

  virtual bool compute_support();
  void draw_support(bool support_in_pct = true);

  const doubleVector& support() const { return _support; }

protected:
  void normalize_support_in_hashtable();
  void collect_support();

protected:
  doubleVector _support;
};

#endif /* SRC_BOOTSTRAP_SUPPORTTREE_HPP_ */
