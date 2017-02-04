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

  _stats = pllmod_msa_compute_stats(_msa.pll_msa(), _model.num_states(), _model.charmap(),
                                   _msa.weights(), stats_mask);

  assert(_stats);

  return _stats;
}


void set_partition_tips(const PartitionInfo& pinfo, pll_partition_t * partition,
                           pll_utree_t * tree)
{
  unsigned int tip_nodes_count = partition->tips;
  pll_utree_t ** tipnodes = NULL;

  if (1 /*useropt->thread_id == 0*/)
  {
    /*  obtain an array of pointers to tip nodes */
    tipnodes = (pll_utree_t  **)calloc(tip_nodes_count,
                                                      sizeof(pll_utree_t *));
    pll_utree_query_tipnodes(tree, tipnodes);

//    assert(partition->map != NULL || msa->msa_type != RAXML_MSA_DISCRETE);
  }

//  parallel_thread_barrier(useropt);

  for (size_t i = 0; i < tip_nodes_count; ++i)
  {
    try
    {
      pll_set_tip_states(partition, tipnodes[i]->clv_index, partition->map,
                         pinfo.msa().at(tipnodes[i]->label).c_str());
    }
    catch (out_of_range const& ex)
    {
      throw runtime_error("Sequence not found in alignment: " + string(tipnodes[i]->label));
    }
  }

  /* wait until all threads are done before destroying hashtable */
//  parallel_thread_barrier(useropt);

  if (1 /*useropt->thread_id == 0*/)
  {
    /* we no longer need these two arrays (keys and values of hash table... */
    free(tipnodes);
  }
}

void set_partition_model(const PartitionInfo& pinfo, pll_partition_t* partition)
{
  const Model& model = pinfo.model();
  const pllmod_msa_stats_t * stats = pinfo.stats();

  /* either compute empirical P-inv, or set the fixed user-specified value */
  double pinv = 0;
  switch (model.param_mode(PLLMOD_OPT_PARAM_PINV))
  {
    case ParamValue::user:
      pinv = model.pinv();
      break;
    case ParamValue::empirical:
//      pinv = pllmod_msa_empirical_invariant_sites(partition);
      pinv = stats->inv_prop;
      break;
    case ParamValue::ML:
      /* use half of empirical pinv as a starting value */
      pinv = stats->inv_prop / 2;
      break;
    case ParamValue::undefined:
      /* nothing to do here */
      break;
    default:
      assert(0);
  }

  /* either compute empirical base frequencies, or set the fixed user-specified values */
  const double *base_freqs = NULL;
  double *alloc_freqs = NULL;
  switch (model.param_mode(PLLMOD_OPT_PARAM_FREQUENCIES))
  {
    case ParamValue::user:
      base_freqs = model.base_freqs().data();
      break;
    case ParamValue::empirical:
//      if (_model.data_type == DataType::diploid10)
//        /* for now, use a separate function to compute emp. freqs for diploid10 data*/
//        alloc_freqs = base_freqs = get_diploid10_empirircal_freqs(msa);
//      else
      {
//        base_freqs = pllmod_msa_empirical_frequencies(partition);
        assert(stats->freqs && stats->states == partition->states);
        base_freqs = stats->freqs;
      }
      break;
    case ParamValue::equal:
    case ParamValue::ML:
      /* use equal frequencies as s a starting value for ML optimization */
      base_freqs = alloc_freqs = pllmod_util_get_equal_freqs(partition->states);
      break;
    case ParamValue::model:
      /* nothing to do here, model freqs will be set later */
      break;
    default:
      assert(0);
  }

  assert(base_freqs || model.param_mode(PLLMOD_OPT_PARAM_FREQUENCIES) == ParamValue::model);

  /* either compute empirical substitution rates, or set the fixed user-specified values */
  const double *subst_rates = NULL;
  double *alloc_rates = NULL;
  switch (model.param_mode(PLLMOD_OPT_PARAM_SUBST_RATES))
  {
    case ParamValue::user:
      subst_rates = model.subst_rates().data();
      break;
    case ParamValue::empirical:
      subst_rates = alloc_rates = pllmod_msa_empirical_subst_rates(partition);
      break;
    case ParamValue::equal:
      subst_rates = alloc_rates = pllmod_util_get_equal_rates(partition->states);
      break;
    case ParamValue::ML:
      /* use equal rates as s a starting value for ML optimization */
      subst_rates = alloc_rates = pllmod_util_get_equal_rates(partition->states);
//        subst_rates = pllmod_msa_empirical_subst_rates(partition);
      break;
    case ParamValue::model:
      /* nothing to do here, model freqs will be set later */
      break;
    default:
      assert(0);
  }

  assert(subst_rates || model.param_mode(PLLMOD_OPT_PARAM_SUBST_RATES) == ParamValue::model);

  assert(model.num_submodels() == partition->rate_matrices);

  /* now iterate over rate matrices and set all params */
  for (unsigned int i = 0; i < partition->rate_matrices; ++i)
  {
    const pllmod_subst_model_t * submodel = model.submodel(i);

    /* set base frequencies */
    const double * cur_freqs = (base_freqs) ? base_freqs : submodel->freqs;
    pll_set_frequencies(partition, i, cur_freqs);

    /* set substitution rates */
    const double * cur_rates = (subst_rates) ? subst_rates : submodel->rates;
    pll_set_subst_params(partition, i, cur_rates);

    /* set p-inv value */
    pll_update_invariant_sites_proportion (partition, i, pinv);
  }

  if (alloc_freqs)
    free(alloc_freqs);

  if (alloc_rates)
    free(alloc_rates);
}

pll_partition_t* create_pll_partition(const Options& opts, const PartitionInfo& pinfo,
                                      pll_utree_t* tree)
{
  const MSA& msa = pinfo.msa();
  const Model& model = pinfo.model();

  /* compute node count information */
  int tip_nodes_count = msa.size();
  unsigned int inner_nodes_count = tip_nodes_count - 2;
  unsigned int nodes_count = inner_nodes_count + tip_nodes_count;
  unsigned int branch_count = nodes_count - 1;

  unsigned int attrs = opts.simd_arch;

//  if (opts.use && pinfo.model().num_ratecats() > 1)
//  {
//    attrs |= PLL_ATTRIB_RATE_SCALERS;
//
//    if (pinfo.model().num_states() != 4 ||
//        (opts.simd_arch != PLL_ATTRIB_ARCH_AVX && opts.simd_arch != PLL_ATTRIB_ARCH_AVX2))
//    {
//      throw runtime_error("ERROR: Per-rate scalers are implemented for DNA with AVX/AVX2 vectorization only!\n");
//    }
//  }

  if (opts.use_tip_inner)
  {
    assert(!(opts.use_prob_msa));
    // TODO: use proper auto-tuning
    const unsigned long min_len_ti = 100;
    if ((unsigned long) msa.length() > min_len_ti)
      attrs |= PLL_ATTRIB_PATTERN_TIP;
  }

  pll_partition_t * partition = pll_partition_create(
      tip_nodes_count,         /* number of tip sequences */
      inner_nodes_count,       /* number of CLV buffers */
      model.num_states(),      /* number of states in the data */
      msa.length(),            /* number of alignment sites/patterns */
      model.num_submodels(),     /* number of different substitution models (LG4 = 4) */
      branch_count,            /* number of probability matrices */
      model.num_ratecats(),    /* number of (GAMMA) rate categories */
      inner_nodes_count,       /* number of scaling buffers */
      attrs                    /* list of flags (SSE3/AVX, TIP-INNER special cases etc.) */
  );

  partition->map = model.charmap();

  // TODO: exception
  if (!partition)
    sysutil_fatal_libpll();

  /* set rate categories & weights */
  pll_set_category_rates(partition, model.ratecat_rates().data());
  pll_set_category_weights(partition, model.ratecat_weights().data());

  /* set pattern weights */
  if (msa.weights())
    pll_set_pattern_weights(partition, msa.weights());

  set_partition_tips(pinfo, partition, tree);

  set_partition_model(pinfo, partition);

  return partition;
}
