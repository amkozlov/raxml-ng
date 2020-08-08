#include "BootstrapGenerator.hpp"

BootstrapGenerator::BootstrapGenerator ()
{
  // TODO Auto-generated constructor stub

}

BootstrapGenerator::~BootstrapGenerator ()
{
  // TODO Auto-generated destructor stub
}

BootstrapReplicate BootstrapGenerator::generate(const PartitionedMSA& parted_msa,
                                                unsigned long random_seed)
{
  BootstrapReplicate result;

  RandomGenerator gen(random_seed);

  for (const auto& pinfo: parted_msa.part_list())
    result.site_weights.emplace_back(generate(pinfo.msa(), gen));

  return result;
}

WeightVector BootstrapGenerator::generate(const MSA& msa, unsigned long random_seed)
{
  RandomGenerator gen(random_seed);

  return generate(msa, gen);
}

WeightVector BootstrapGenerator::generate(const MSA& msa, RandomGenerator& gen)
{
  unsigned int orig_len = msa.num_sites();
  unsigned int comp_len = msa.length();

  WeightVector w_buf(orig_len, 0);

  std::uniform_int_distribution<unsigned int> distr(0, orig_len-1);

  for (unsigned int i = 0; i < orig_len; ++i)
  {
    auto site = distr(gen);
    w_buf[site]++;
  }

  if (orig_len == comp_len)
    return w_buf;
  else
  {
    WeightVector result(comp_len, 0);
    auto orig_weights = msa.weights();

    assert(!orig_weights.empty());

    unsigned int pos = 0;
    for (unsigned int i = 0; i < comp_len; ++i)
    {
      for (unsigned int j = 0; j < orig_weights[i]; ++j)
        result[i] += w_buf[pos++];
    }

    return result;
  }
}

