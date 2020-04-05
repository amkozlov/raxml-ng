#ifndef RAXML_MUTATIONMAP_HPP_
#define RAXML_MUTATIONMAP_HPP_

#include "common.h"
#include "Tree.hpp"
#include "AncestralStates.hpp"
#include "PartitionedMSA.hpp"

struct MutationMap
{
  Tree tree;
  NameList mut_names;
  std::vector<IDVector> mut_list;

  MutationMap(const AncestralStates& ancestral, const PartitionedMSA& pmsa);

  void init(const AncestralStates& ancestral, const PartitionedMSA& pmsa);
};

#endif /* RAXML_MUTATIONMAP_HPP_ */
