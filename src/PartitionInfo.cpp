#include "PartitionInfo.hpp"

#include "Options.hpp"

using namespace std;

PartitionInfo::~PartitionInfo ()
{
}

size_t PartitionInfo::length() const
{
  const auto& st = stats();
  return st.pattern_count ? st.pattern_count : st.site_count;
}

size_t PartitionInfo::taxon_clv_size(bool partial) const
{
  auto sites = partial ? (_msa.num_patterns() ? _msa.num_patterns() : _msa.num_sites()) : length();
  return _model.clv_entry_size() * sites;
}

size_t PartitionInfo::mark_partition_sites(unsigned int part_num, std::vector<unsigned int>& site_part) const
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
      read = sscanf(range, "%lu-%lu/%lu", &start, &end, &stride);
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

void PartitionInfo::compress_patterns(bool store_backmap)
{
  _msa.compress_patterns(model().charmap(), store_backmap);
}

pllmod_msa_stats_t * PartitionInfo::compute_stats(unsigned long stats_mask) const
{
  const unsigned int * weights = _msa.weights().empty() ? nullptr : _msa.weights().data();
  pllmod_msa_stats_t * stats = pllmod_msa_compute_stats(_msa.pll_msa(), _model.num_states(),
                                                        _model.charmap(), weights, stats_mask);

  libpll_check_error("ERROR computing MSA stats");
  assert(stats);

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

const PartitionStats& PartitionInfo::stats() const
{
  if (_stats.empty() && !_msa.empty())
  {
    unsigned long stats_mask = PLLMOD_MSA_STATS_GAP_PROP;
    stats_mask |= PLLMOD_MSA_STATS_FREQS;
    stats_mask |= PLLMOD_MSA_STATS_INV_PROP;
    stats_mask |= PLLMOD_MSA_STATS_GAP_SEQS;

    if (_model.param_mode(PLLMOD_OPT_PARAM_SUBST_RATES) == ParamValue::empirical)
      stats_mask |= PLLMOD_MSA_STATS_SUBST_RATES;

    auto pll_stats = compute_stats(stats_mask);
    auto states = _model.num_states();

    _stats.site_count = _msa.num_sites();
    _stats.pattern_count = _msa.num_patterns();
    _stats.inv_prop = pll_stats->inv_prop;

    _stats.gap_prop = pll_stats->gap_prop;
    _stats.gap_seqs.assign(pll_stats->gap_seqs, pll_stats->gap_seqs + pll_stats->gap_seqs_count);

    _stats.emp_base_freqs.assign(pll_stats->freqs, pll_stats->freqs + states);
    if (pll_stats->subst_rates)
    {
      _stats.emp_subst_rates.assign(pll_stats->subst_rates,
                                    pll_stats->subst_rates + pllmod_util_subst_rate_count(states));
    }

    pllmod_msa_destroy_stats(pll_stats);
  }

  return _stats;
};

void PartitionInfo::set_model_empirical_params()
{
  assign(_model, stats());
}

void assign(Model& model, const PartitionStats& stats)
{
  /* either compute empirical P-inv, or set the fixed user-specified value */
  switch (model.param_mode(PLLMOD_OPT_PARAM_PINV))
  {
    case ParamValue::empirical:
      model.pinv(stats.inv_prop);
      break;
    case ParamValue::ML:
      /* use half of empirical pinv as a starting value */
      model.pinv(stats.inv_prop / 2);
      break;
    case ParamValue::user:
    case ParamValue::undefined:
      /* nothing to do here */
      break;
    default:
      assert(0);
  }

   /* assign empirical base frequencies */
  switch (model.param_mode(PLLMOD_OPT_PARAM_FREQUENCIES))
  {
    case ParamValue::empirical:
      assert(stats.emp_base_freqs.size() == model.num_states());
      model.base_freqs(stats.emp_base_freqs);
      break;
    case ParamValue::user:
    case ParamValue::equal:
    case ParamValue::ML:
    case ParamValue::model:
      /* nothing to do here */
      break;
    default:
      assert(0);
  }

  /* assign empirical substitution rates */
  switch (model.param_mode(PLLMOD_OPT_PARAM_SUBST_RATES))
  {
    case ParamValue::empirical:
    {
      assert(stats.emp_subst_rates.size() == pllmod_util_subst_rate_count(model.num_states()));
      model.subst_rates(stats.emp_subst_rates);
      break;
    }
    case ParamValue::equal:
    case ParamValue::user:
    case ParamValue::ML:
    case ParamValue::model:
      /* nothing to do here */
      break;
    default:
      assert(0);
  }
}
