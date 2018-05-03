#include "ResourceEstimator.hpp"
#include "../Options.hpp"

ResourceEstimator::ResourceEstimator(const PartitionedMSA& parted_msa, const Options& opts)
{
  _taxon_clv_size = parted_msa.taxon_clv_size();
  _num_patterns = opts.use_pattern_compression ? parted_msa.total_patterns() :
                                                 parted_msa.total_sites();
  _num_taxa = parted_msa.taxon_count();
  _num_partitions = parted_msa.part_count();
}

ResEstimates ResourceEstimator::estimate()
{
  ResEstimates res;
  compute_estimates(res);
  return res;
};

StaticResourceEstimator::StaticResourceEstimator(const PartitionedMSA& parted_msa,
                                                 const Options& opts) :
  ResourceEstimator(parted_msa, opts)
{
  if (opts.use_tip_inner)
  {
    _num_tipvecs = _num_taxa;
    _num_clvs = _num_taxa - 2;
  }
  else
  {
    _num_tipvecs = 0;
    _num_clvs = _num_taxa + _num_taxa - 2;
  }

// TODO: account for site repeats
//  if (opts.use_repeats)

}

void StaticResourceEstimator::compute_estimates(ResEstimates& res)
{
  size_t mem_size = 0;

  mem_size += _num_clvs * _taxon_clv_size * sizeof(double);
  mem_size += _num_tipvecs * _num_patterns * sizeof(unsigned char);

  res.total_mem_size = mem_size;
  res.taxon_clv_size = _taxon_clv_size;
  res.num_threads_response = PLL_MAX(_taxon_clv_size / 4000, 1);
  res.num_threads_throughput = PLL_MAX(_taxon_clv_size / 80000, 1);
  res.num_threads_balanced = PLL_MAX(_taxon_clv_size / 16000, 1);
}
