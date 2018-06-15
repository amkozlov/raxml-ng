#ifndef RAXML_RESOURCEESTIMATOR_HPP_
#define RAXML_RESOURCEESTIMATOR_HPP_

#include "../PartitionedMSA.hpp"

struct ResEstimates
{
  size_t taxon_clv_size;
  size_t total_mem_size;
  size_t num_threads_response;
  size_t num_threads_throughput;
  size_t num_threads_balanced;
};

class ResourceEstimator
{
public:
  ResourceEstimator(const PartitionedMSA& parted_msa, const Options& opts);
  virtual ~ResourceEstimator() {}

  ResEstimates estimate();

protected:
  virtual void compute_estimates(ResEstimates& res) = 0;

protected:
  size_t _num_taxa;
  size_t _num_partitions;
  size_t _num_patterns;
  size_t _taxon_clv_size;
};

class StaticResourceEstimator : public ResourceEstimator
{
public:
  StaticResourceEstimator(const PartitionedMSA& parted_msa, const Options& opts);

protected:
  virtual void compute_estimates(ResEstimates& res);

private:
  size_t estimate_cores(size_t taxon_clv_size, size_t elems_per_core);

protected:
  size_t _num_tipvecs;
  size_t _num_clvs;
};



#endif /* RAXML_RESOURCEESTIMATOR_HPP_ */
