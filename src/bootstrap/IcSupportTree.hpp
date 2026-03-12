#ifndef SRC_BOOTSTRAP_ICSUPPORTTREE_HPP_
#define SRC_BOOTSTRAP_ICSUPPORTTREE_HPP_

#include "SupportTree.hpp"

/* Internode certainty measures as described in:
 *
 * Leonidas Salichos, Alexandros Stamatakis  Antonis Rokas
 * "Novel Information Theory-Based Measures for Quantifying Incongruence among Phylogenetic Trees"
 * Molecular Biology and Evolution, 2014
 *
 * https://doi.org/10.1093/molbev/msu061
 *
 * */
class IcSupportTree : public SupportTree
{
public:
  IcSupportTree (const Tree& tree, bool icAll = false);
  virtual ~IcSupportTree ();

  virtual bool compute_support();

protected:
  bool _ic_all;
  bool _ica_filter;
  double _ica_cutoff;
};

#endif /* SRC_BOOTSTRAP_ICSUPPORTTREE_HPP_ */
