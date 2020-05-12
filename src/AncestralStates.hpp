#ifndef RAXML_ANCESTRALSTATES_HPP_
#define RAXML_ANCESTRALSTATES_HPP_

#include "common.h"
#include "Tree.hpp"
#include "PartitionedMSA.hpp"
#include "loadbalance/PartitionAssignment.hpp"

typedef std::vector<doubleVector> PartitionAncestralProbs;

struct AncestralStates
{
  Tree tree;
  std::shared_ptr<PartitionedMSA> parted_msa;
  size_t num_nodes;
  size_t num_states;
  std::vector<size_t> part_num_sites;
  NameList state_names;
  StateNameMap state_namemap;
  NameList node_names;
  NameIdMap node_namemap;
  std::vector<PartitionAncestralProbs> probs;

  bool ambiguity;
  double prob_eps;

  AncestralStates(size_t nodes = 0, size_t states = 0, size_t sites = 0);
  AncestralStates(size_t nodes, const std::shared_ptr<PartitionedMSA>& part_msa);

  void allocate_probs();

  size_t num_parts() const;
  std::string ml_state_seq(size_t node_idx, size_t part_idx = 0) const;
  std::string ml_state_seq(const std::string& node_name, size_t part_idx = 0) const;
  std::string ml_state_tipseq(const std::string& tip_name, size_t part_idx = 0) const;
  std::string ml_state(doubleVector::const_iterator& prob) const;
  std::string ml_state(size_t node_idx, size_t site_idx, size_t part_idx = 0) const;

private:
  const doubleVector& node_prob_vector(size_t node_idx, size_t part_idx) const;
  std::string ml_state_seq(const doubleVector& probvec, size_t num_sites) const;
};

typedef std::shared_ptr<AncestralStates> AncestralStatesSharedPtr;

void assign_tree(AncestralStates& ancestral, const pllmod_ancestral_t& pll_ancestral);
void assign_probs(AncestralStates& ancestral, const pllmod_ancestral_t& pll_ancestral,
                  const PartitionAssignment& part_assign);

#endif /* RAXML_ANCESTRALSTATES_HPP_ */
