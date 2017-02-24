#include "TreeInfo.hpp"
#include "ParallelContext.hpp"

using namespace std;

TreeInfo::TreeInfo (const Options &opts, const Tree& tree, const PartitionedMSA& parted_msa,
                    const PartitionAssignment& part_assign)
{
  _pll_treeinfo = pllmod_treeinfo_create(tree.pll_utree_copy(), tree.num_tips(),
                                         parted_msa.part_count(), opts.brlen_linkage);

  if (!_pll_treeinfo)
    throw runtime_error("ERROR creating treeinfo structure: " + string(pll_errmsg));

#if (defined(_USE_PTHREADS) || defined(_USE_MPI))
  pllmod_treeinfo_set_parallel_context(_pll_treeinfo, (void *) &ParallelContext::ctx(),
                                       ParallelContext::parallel_reduce_cb);
#endif

  // init partitions
  int optimize_branches = opts.optimize_brlen ? PLLMOD_OPT_PARAM_BRANCHES_ITERATIVE : 0;
  if (opts.optimize_model && opts.brlen_linkage == PLLMOD_TREE_BRLEN_SCALED &&
      parted_msa.part_count() > 1)
  {
    optimize_branches |= PLLMOD_OPT_PARAM_BRANCH_LEN_SCALER;
  }

  for (size_t p = 0; p < parted_msa.part_count(); ++p)
  {
    const PartitionInfo& pinfo = parted_msa.part_info(p);
    int params_to_optimize = opts.optimize_model ? pinfo.model().params_to_optimize() : 0;
    params_to_optimize |= optimize_branches;

    PartitionAssignment::const_iterator part_range = part_assign.find(p);
    if (part_range != part_assign.end())
    {
      /* create and init PLL partition structure */
      pll_partition_t * partition = create_pll_partition(opts, pinfo, tree, *part_range);

      int retval = pllmod_treeinfo_init_partition(_pll_treeinfo, p, partition,
                                                  params_to_optimize,
                                                  pinfo.model().alpha(),
                                                  pinfo.model().ratecat_submodels().data(),
                                                  pinfo.model().submodel(0).rate_sym().data());

      if (!retval)
        throw runtime_error("ERROR adding treeinfo partition: " + string(pll_errmsg));
    }
    else
    {
      // this partition will be processed by other threads, but we still need to know
      // which parameters to optimize
      _pll_treeinfo->params_to_optimize[p] = params_to_optimize;
    }
  }
}

TreeInfo::~TreeInfo ()
{
  if (_pll_treeinfo)
  {
    pll_utree_destroy(_pll_treeinfo->root, NULL);
    pllmod_treeinfo_destroy(_pll_treeinfo);
  }
}

Tree TreeInfo::tree() const
{
  return _pll_treeinfo ? Tree(_pll_treeinfo->tip_count, _pll_treeinfo->root) : Tree();
}

double TreeInfo::loglh(bool incremental)
{
  return pllmod_treeinfo_compute_loglh(_pll_treeinfo, incremental ? 1 : 0);
}

//#define DBG printf

double TreeInfo::optimize_branches(double lh_epsilon, double brlen_smooth_factor)
{
  /* update all CLVs and p-matrices before calling BLO */
  double new_loglh = loglh();

  if (_pll_treeinfo->params_to_optimize[0] & PLLMOD_OPT_PARAM_BRANCHES_ITERATIVE)
  {
    new_loglh = -1 * pllmod_opt_optimize_branch_lengths_local_multi(_pll_treeinfo->partitions,
                                                                    _pll_treeinfo->partition_count,
                                                                    _pll_treeinfo->root,
                                                                    _pll_treeinfo->param_indices,
                                                                    _pll_treeinfo->deriv_precomp,
                                                                    _pll_treeinfo->brlen_scalers,
                                                                    RAXML_BRLEN_MIN,
                                                                    RAXML_BRLEN_MAX,
                                                                    lh_epsilon,
                                                                    brlen_smooth_factor * RAXML_BRLEN_SMOOTHINGS,
                                                                    -1,  /* radius */
                                                                    1,    /* keep_update */
                                                                    _pll_treeinfo->parallel_context,
                                                                    _pll_treeinfo->parallel_reduce_cb
                                                                    );
    DBG("\t - after brlen: logLH = %f\n", new_loglh);

    if (pll_errno)
      throw runtime_error("ERROR in branch lenght optimization: " + string(pll_errmsg));
  }

  /* optimize brlen scalers, if needed */
  if (_pll_treeinfo->brlen_linkage == PLLMOD_TREE_BRLEN_SCALED &&
      _pll_treeinfo->partition_count > 1)
  {
    new_loglh = -1 * pllmod_algo_opt_onedim_treeinfo(_pll_treeinfo,
                                                    PLLMOD_OPT_PARAM_BRANCH_LEN_SCALER,
                                                    RAXML_BRLEN_SCALER_MIN,
                                                    RAXML_BRLEN_SCALER_MAX,
                                                    RAXML_PARAM_EPSILON);

    /* normalize scalers and scale the branches accordingly */
    pllmod_treeinfo_normalize_brlen_scalers(_pll_treeinfo);

    DBG("\t - after brlen scalers: logLH = %f\n", new_loglh);
  }


  return new_loglh;
}

double TreeInfo::optimize_params(int params_to_optimize, double lh_epsilon)
{
  double new_loglh;

  /* optimize SUBSTITUTION RATES */
  if (params_to_optimize & PLLMOD_OPT_PARAM_SUBST_RATES)
  {
    new_loglh = -1 * pllmod_algo_opt_subst_rates_treeinfo(_pll_treeinfo,
                                                          0,
                                                          PLLMOD_OPT_MIN_SUBST_RATE,
                                                          PLLMOD_OPT_MAX_SUBST_RATE,
                                                          RAXML_BFGS_FACTOR,
                                                          RAXML_PARAM_EPSILON);
    DBG("\t - after rates: logLH = %f\n", new_loglh);
  }

  /* optimize BASE FREQS */
  if (params_to_optimize & PLLMOD_OPT_PARAM_FREQUENCIES)
  {
    new_loglh = -1 * pllmod_algo_opt_frequencies_treeinfo(_pll_treeinfo,
                                                          0,
                                                          PLLMOD_OPT_MIN_FREQ,
                                                          PLLMOD_OPT_MAX_FREQ,
                                                          RAXML_BFGS_FACTOR,
                                                          RAXML_PARAM_EPSILON);

    DBG("\t - after freqs: logLH = %f\n", new_loglh);
  }

  /* optimize ALPHA */
  if (params_to_optimize & PLLMOD_OPT_PARAM_ALPHA)
  {
    new_loglh = -1 * pllmod_algo_opt_onedim_treeinfo(_pll_treeinfo,
                                                      PLLMOD_OPT_PARAM_ALPHA,
                                                      PLLMOD_OPT_MIN_ALPHA,
                                                      PLLMOD_OPT_MAX_ALPHA,
                                                      RAXML_PARAM_EPSILON);
    DBG("\t - after alpha: logLH = %f\n", new_loglh);
  }

  if (params_to_optimize & PLLMOD_OPT_PARAM_PINV)
  {
    new_loglh = -1 * pllmod_algo_opt_onedim_treeinfo(_pll_treeinfo,
                                                      PLLMOD_OPT_PARAM_PINV,
                                                      PLLMOD_OPT_MIN_PINV,
                                                      PLLMOD_OPT_MAX_PINV,
                                                      RAXML_PARAM_EPSILON);

    DBG("\t - after p-inv: logLH = %f\n", new_loglh);
  }

  /* optimize FREE RATES and WEIGHTS */
  if (params_to_optimize & PLLMOD_OPT_PARAM_FREE_RATES)
  {
    new_loglh = -1 * pllmod_algo_opt_rates_weights_treeinfo (_pll_treeinfo,
                                                          RAXML_FREERATE_MIN,
                                                          RAXML_FREERATE_MAX,
                                                          RAXML_BFGS_FACTOR,
                                                          RAXML_PARAM_EPSILON);

    /* normalize scalers and scale the branches accordingly */
    if (_pll_treeinfo->brlen_linkage == PLLMOD_TREE_BRLEN_SCALED &&
        _pll_treeinfo->partition_count > 1)
      pllmod_treeinfo_normalize_brlen_scalers(_pll_treeinfo);

    DBG("\t - after freeR: logLH = %f\n", new_loglh);
    DBG("\t - after freeR/crosscheck: logLH = %f\n", loglh());
  }

  if (params_to_optimize & PLLMOD_OPT_PARAM_BRANCHES_ITERATIVE)
  {
    new_loglh = optimize_branches(lh_epsilon, 0.25);
  }

  return new_loglh;
}

double TreeInfo::spr_round(spr_round_params& params)
{
  return pllmod_algo_spr_round(_pll_treeinfo, params.radius_min, params.radius_max,
                               params.ntopol_keep, params.thorough,
                               RAXML_BRLEN_MIN, RAXML_BRLEN_MAX, RAXML_BRLEN_SMOOTHINGS,
                               0.1,
                               params.subtree_cutoff > 0. ? &params.cutoff_info : nullptr,
                               params.subtree_cutoff);
}


void assign(PartitionedMSA& parted_msa, const TreeInfo& treeinfo)
{
  const pllmod_treeinfo_t& pll_treeinfo = treeinfo.pll_treeinfo();

  if (parted_msa.part_count() != pll_treeinfo.partition_count)
    throw runtime_error("Incompatible arguments");

  for (size_t p = 0; p < parted_msa.part_count(); ++p)
  {
    if (!pll_treeinfo.partitions[p])
      continue;

    Model model(parted_msa.model(p));
    assign(model, treeinfo, p);
    parted_msa.model(p, move(model));
  }
}

void assign(Model& model, const TreeInfo& treeinfo, size_t partition_id)
{
  const pllmod_treeinfo_t& pll_treeinfo = treeinfo.pll_treeinfo();

  if (partition_id >= pll_treeinfo.partition_count)
    throw out_of_range("Partition ID out of range");

  if (!pll_treeinfo.partitions[partition_id])
    return;

  assign(model, pll_treeinfo.partitions[partition_id]);
  model.alpha(pll_treeinfo.alphas[partition_id]);
  if (pll_treeinfo.brlen_scalers)
    model.brlen_scaler(pll_treeinfo.brlen_scalers[partition_id]);
}

void set_partition_tips(PartitionInfo const& pinfo, const PartitionRange& part_region,
                        pll_partition_t* partition)
{
  for (size_t i = 0; i < pinfo.msa().size(); ++i)
  {
    pll_set_tip_states(partition, i, partition->map, pinfo.msa().at(i).c_str() + part_region.start);
  }
}

pll_partition_t* create_pll_partition(Options const& opts, PartitionInfo const& pinfo,
                                      Tree const& tree, const PartitionRange& part_region)
{
  const MSA& msa = pinfo.msa();
  const Model& model = pinfo.model();

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
      tree.num_tips(),         /* number of tip sequences */
      tree.num_inner(),        /* number of CLV buffers */
      model.num_states(),      /* number of states in the data */
      part_region.length,      /* number of alignment sites/patterns */
      model.num_submodels(),   /* number of different substitution models (LG4 = 4) */
      tree.num_branches(),     /* number of probability matrices */
      model.num_ratecats(),    /* number of (GAMMA) rate categories */
      tree.num_inner(),        /* number of scaling buffers */
      attrs                    /* list of flags (SSE3/AVX, TIP-INNER special cases etc.) */
  );

  if (!partition)
    throw runtime_error("ERROR creating pll_partition: " + string(pll_errmsg));

  partition->map = model.charmap();

  /* set pattern weights */
  if (!msa.weights().empty())
    pll_set_pattern_weights(partition, msa.weights().data() + part_region.start);

  set_partition_tips(pinfo, part_region, partition);

  assign(partition, model);

  return partition;
}


