#ifndef RAXML_PARSIMONYMSA_HPP_
#define RAXML_PARSIMONYMSA_HPP_

#include "PartitionedMSA.hpp"

class ParsimonyMSA
{
public:
  ParsimonyMSA(std::shared_ptr<PartitionedMSA> parted_msa, unsigned int attributes, bool compress_patterns);

  virtual
  ~ParsimonyMSA ();

  const PartitionedMSA& part_msa() const { return *_pars_msa; };
  const NameList& taxon_names()  const { return _pars_msa->taxon_names(); };
  const std::vector<corax_partition*>& pll_partitions() const { return _pll_partitions; }

  /* Estimated memory footprint of parsimony structure, in bytes */
  size_t memsize_estimate() const;

private:
  std::shared_ptr<PartitionedMSA> _pars_msa;
  std::vector<corax_partition*> _pll_partitions;

  void init_pars_msa(std::shared_ptr<PartitionedMSA> parted_msa, bool compress_patterns);

  void create_pll_partitions(unsigned int attributes);
  void free_pll_partitions();
};

#endif /* RAXML_PARSIMONYMSA_HPP_ */
