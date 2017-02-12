#ifndef RAXML_TREEINFO_HPP_
#define RAXML_TREEINFO_HPP_

#include "common.h"
#include "Tree.hpp"
#include "Options.hpp"

class TreeInfo
{
public:
  TreeInfo (const Options &opts, const Tree& tree, const PartitionedMSA& parted_msa);
  virtual
  ~TreeInfo ();

  double loglh(bool incremental = false);

private:
  pllmod_treeinfo_t * _pll_treeinfo;
};

pll_partition_t* create_pll_partition(const Options& opts, const PartitionInfo& pinfo,
                                      const Tree& tree);


#endif /* RAXML_TREEINFO_HPP_ */
