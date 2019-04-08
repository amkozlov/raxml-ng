#ifndef RAXML_ANCESTRALSTATES_HPP_
#define RAXML_ANCESTRALSTATES_HPP_

#include "common.h"
#include "Tree.hpp"

struct AncestralStates
{
  Tree tree;
  size_t num_nodes;
  size_t num_states;
  size_t num_sites;
  NameList state_names;
  StateNameMap state_namemap;
  NameList node_names;
  std::vector<doubleVector> probs;

  bool ambiguity;
  double prob_eps;

  AncestralStates(size_t nodes = 0, size_t states = 0, size_t sites = 0);

  std::string ml_state_seq(size_t node_idx) const ;
  std::string ml_state(size_t node_idx, size_t site_idx) const;
};

typedef std::shared_ptr<AncestralStates> AncestralStatesSharedPtr;

#endif /* RAXML_ANCESTRALSTATES_HPP_ */
