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

pllmod_msa_stats_t * PartitionInfo::compute_stats(unsigned long stats_mask) const
{
  const unsigned int * weights = _msa.weights().empty() ? nullptr : _msa.weights().data();
  pllmod_msa_stats_t * stats = pllmod_msa_compute_stats(_msa.pll_msa(), _model.num_states(),
                                                        _model.charmap(), weights, stats_mask);

  if (!stats)
    throw runtime_error(pll_errmsg);

  if ((stats_mask & PLLMOD_MSA_STATS_FREQS) &&_msa.probabilistic() &&
      _model.param_mode(PLLMOD_OPT_PARAM_FREQUENCIES) == ParamValue::empirical)
  {
    assert(stats->states == _msa.states());
    assert(stats->freqs);

    auto freqs = _msa.state_freqs();
    memcpy(stats->freqs, freqs.data(), _msa.states() * sizeof(double));
  }

  return stats;
}

const pllmod_msa_stats_t * PartitionInfo::stats() const
{
  if (!_stats)
  {
    unsigned long stats_mask = PLLMOD_MSA_STATS_GAP_PROP;
    stats_mask |= PLLMOD_MSA_STATS_FREQS;
    stats_mask |= PLLMOD_MSA_STATS_INV_PROP;

    if (_model.param_mode(PLLMOD_OPT_PARAM_SUBST_RATES) == ParamValue::empirical)
      stats_mask |= PLLMOD_MSA_STATS_SUBST_RATES;

    _stats = compute_stats(stats_mask);
  }

  return _stats;
};


void PartitionInfo::set_modeL_empirical_params()
{
  stats();

  // check for zero state frequencies
  if (_model.param_mode(PLLMOD_OPT_PARAM_FREQUENCIES) == ParamValue::empirical)
  {
    for (unsigned int i = 0; i < _stats->states; ++i)
    {
      if (!(_stats->freqs[i] > 0.))
      {
        LOG_ERROR << "\nBase frequencies: ";
        for (unsigned int j = 0; j < _stats->states; ++j)
          LOG_ERROR << _stats->freqs[j] <<  " ";
        LOG_ERROR << endl;

        throw runtime_error("Frequency of state " + to_string(i) +
                            " in partition " + _name + " is 0!\n"
                            "Please either change your partitioning scheme or "
                            "use model state frequencies for this partition!");
      }
    }
  }

  assign(_model, stats());
}

void PartitionInfo::fill_tip_clv(unsigned int tip_id, doubleVector& clv,
                                 unsigned int states_padded) const
{
  auto clv_size = _msa.length() * states_padded;
  clv.resize(clv_size);
  auto clvp = clv.begin();
  auto seq = _msa.at(tip_id);
  auto charmap = _model.charmap();
  auto errmodel = _model.error_model();

  for (size_t j = 0; j < _msa.length(); ++j)
  {
    auto charstate = (unsigned int) seq[j];
    unsigned int state = charmap ? charmap[(int) charstate] : charstate;

    errmodel->state_probs(state, clvp);

    if (j == 0 && 0)
    {
      printf("state: %u ", state);
      for (size_t k = 0; k < _model.num_states(); ++k)
        printf("%lf ", clvp[k]);
      printf("\n");
    }

    clvp += states_padded;
  }

  assert(clvp == clv.end());
}

