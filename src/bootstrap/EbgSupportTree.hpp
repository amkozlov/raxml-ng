#ifndef SRC_BOOTSTRAP_EBGSUPPORTTREE_HPP_
#define SRC_BOOTSTRAP_EBGSUPPORTTREE_HPP_

#include "BootstrapTree.hpp"

class EbgSupportTree : public BootstrapTree
{
public:
  EbgSupportTree (const Tree& tree);
  EbgSupportTree (const Tree& tree, const TreeList& pars_trees, const TreeList& pars_boot_trees);

  virtual
  ~EbgSupportTree ();

  void add_parsimony_trees(const TreeList& treelist);
  void add_parsimony_boostrap_trees(const TreeList& treelist);

protected:
  virtual bool compute_support();

private:
  BootstrapTree _ps_tree;
  BootstrapTree _pbs_tree;
  double _pbs_avg_rrf;
  double _pbs_skewness;
};

#endif /* SRC_BOOTSTRAP_EBGSUPPORTTREE_HPP_ */
