#include "PartitionInfo.hpp"

#include "Options.hpp"

using namespace std;

PartitionInfo::~PartitionInfo ()
{
  if (_stats)
    pllmod_msa_destroy_stats(_stats);
}

size_t PartitionInfo::mark_partition_sites(unsigned int part_num, std::vector<unsigned int>& site_part)
{
  size_t start, end, stride;
  size_t i;
  size_t sites_assigned = 0;
  const char * range = _range_string.c_str();

  do
  {
    while(*range == ',')
      range++;

    int read = 0;
    /* try to parse strided format first */
    read = sscanf(range, "%lu-%lu\\%lu", &start, &end, &stride);
    if (read != 3)
    {
      /* try to parse contiguous range format first */
      stride = 1;
      read = sscanf(range, "%lu-%lu", &start, &end);
      if (read != 2)
      {
        /* finally, check if we have a single column */
        read = sscanf(range, "%lu", &start);
        end = start;
      }
    }
    if (read && start >= 1 && end <= site_part.size() && start <= end)
    {
      /* remember indices are 1-based in the partition file! */
      for (i = start-1; i <= end-1; ++i)
      {
        if ((i - start + 1) % stride == 0)
        {
          if (!site_part[i])
          {
            site_part[i] = part_num;
            sites_assigned++;
          }
          else
            throw MultiplePartitionForSiteException(*this, i+1);
        }
      }
    }
    else
      throw InvalidPartitionRangeException(*this);
  }
  while ((range = strchr(range, ',')) != NULL);

  return sites_assigned;
}

void PartitionInfo::compress_patterns()
{
  _msa.compress_patterns(model().charmap());
}

pllmod_msa_stats_t * PartitionInfo::compute_stats() const
{
  unsigned long stats_mask = PLLMOD_MSA_STATS_GAP_PROP;
  stats_mask |= PLLMOD_MSA_STATS_FREQS;
  stats_mask |= PLLMOD_MSA_STATS_INV_PROP;

  if (_model.param_mode(PLLMOD_OPT_PARAM_SUBST_RATES) == ParamValue::empirical)
    stats_mask |= PLLMOD_MSA_STATS_SUBST_RATES;

  const unsigned int * weights = _msa.weights().empty() ? nullptr : _msa.weights().data();
  _stats = pllmod_msa_compute_stats(_msa.pll_msa(), _model.num_states(), _model.charmap(),
                                    weights, stats_mask);

  assert(_stats);

  if (_msa.probabilistic() &&
      _model.param_mode(PLLMOD_OPT_PARAM_FREQUENCIES) == ParamValue::empirical)
  {
    assert(_stats->states == _msa.states());
    assert(_stats->freqs);

    auto freqs = _msa.state_freqs();
    memcpy(_stats->freqs, freqs.data(), _msa.states() * sizeof(double));
  }

  return _stats;
}

void PartitionInfo::set_modeL_empirical_params()
{
  assign(_model, stats());
}
