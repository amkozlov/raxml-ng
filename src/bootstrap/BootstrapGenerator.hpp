#ifndef RAXML_BOOTSTRAP_BOOTSTRAPGENERATOR_HPP_
#define RAXML_BOOTSTRAP_BOOTSTRAPGENERATOR_HPP_

#include "../PartitionedMSA.hpp"

struct BootstrapReplicate
{
  WeightVectorList site_weights;
};

typedef std::vector<BootstrapReplicate> BootstrapReplicateList;

typedef std::tuple<const PartitionedMSA&, const BootstrapReplicate&> BootstrapMSA;

class BootstrapGenerator
{
public:
  BootstrapGenerator ();
  virtual
  ~BootstrapGenerator ();

  BootstrapReplicate generate(const PartitionedMSA& parted_msa, unsigned long random_seed);
  WeightVector generate(const MSA& msa, unsigned long random_seed);

private:
  WeightVector generate(const MSA& msa, RandomGenerator& gen);
};

#endif /* RAXML_BOOTSTRAP_BOOTSTRAPGENERATOR_HPP_ */
