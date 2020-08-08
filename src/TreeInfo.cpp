#include <algorithm>

#include "TreeInfo.hpp"
#include "ParallelContext.hpp"

using namespace std;

TreeInfo::TreeInfo (const Options &opts, const Tree& tree, const PartitionedMSA& parted_msa,
                    const IDVector& tip_msa_idmap,
                    const PartitionAssignment& part_assign)
{
  init(opts, tree, parted_msa, tip_msa_idmap, part_assign, std::vector<uintVector>());
}

TreeInfo::TreeInfo (const Options &opts, const Tree& tree, const PartitionedMSA& parted_msa,
                    const IDVector& tip_msa_idmap,
                    const PartitionAssignment& part_assign,
                    const std::vector<uintVector>& site_weights)
{
  init(opts, tree, parted_msa, tip_msa_idmap, part_assign, site_weights);
}

void TreeInfo::init(const Options &opts, const Tree& tree, const PartitionedMSA& parted_msa,
                    const IDVector& tip_msa_idmap,
                    const PartitionAssignment& part_assign,
                    const std::vector<uintVector>& site_weights)
{
  _brlen_min = opts.brlen_min;
  _brlen_max = opts.brlen_max;
  _brlen_opt_method = opts.brlen_opt_method;
  _check_lh_impr = opts.safety_checks.isset(SafetyCheck::model_lh_impr);
  _partition_contributions.resize(parted_msa.part_count());
  double total_weight = 0;

  _pll_treeinfo = pllmod_treeinfo_create(pll_utree_graph_clone(&tree.pll_utree_root()),
                                         tree.num_tips(),
                                         parted_msa.part_count(), opts.brlen_linkage);

  libpll_check_error("ERROR creating treeinfo structure");
  assert(_pll_treeinfo);

  pllmod_treeinfo_set_parallel_context(_pll_treeinfo, (void *) nullptr,
                                       ParallelContext::parallel_reduce_cb);

  // init partitions
  int optimize_branches = opts.optimize_brlen ? PLLMOD_OPT_PARAM_BRANCHES_ITERATIVE : 0;

  for (size_t p = 0; p < parted_msa.part_count(); ++p)
  {
    const PartitionInfo& pinfo = parted_msa.part_info(p);
    const auto& weights = site_weights.empty() ? pinfo.msa().weights() : site_weights.at(p);
    int params_to_optimize = opts.optimize_model ? pinfo.model().params_to_optimize() : 0;
    params_to_optimize |= optimize_branches;

    _partition_contributions[p] = std::accumulate(weights.begin(), weights.end(), 0);
    total_weight += _partition_contributions[p];

    PartitionAssignment::const_iterator part_range = part_assign.find(p);
    if (part_range != part_assign.end())
    {
      /* create and init PLL partition structure */
      pll_partition_t * partition = create_pll_partition(opts, pinfo, tip_msa_idmap,
                                                         *part_range, weights);

      int retval = pllmod_treeinfo_init_partition(_pll_treeinfo, p, partition,
                                                  params_to_optimize,
                                                  pinfo.model().gamma_mode(),
                                                  pinfo.model().alpha(),
                                                  pinfo.model().ratecat_submodels().data(),
                                                  pinfo.model().submodel(0).rate_sym().data());

      if (!retval)
      {
        assert(pll_errno);
        libpll_check_error("ERROR adding treeinfo partition");
      }

      // set per-partition branch lengths or scalers
      if (opts.brlen_linkage == PLLMOD_COMMON_BRLEN_SCALED)
      {
        assert (_pll_treeinfo->brlen_scalers);
        _pll_treeinfo->brlen_scalers[p] = pinfo.model().brlen_scaler();
      }
      else if (opts.brlen_linkage == PLLMOD_COMMON_BRLEN_UNLINKED && !tree.partition_brlens().empty())
      {
        assert(_pll_treeinfo->branch_lengths[p]);
        memcpy(_pll_treeinfo->branch_lengths[p], tree.partition_brlens(p).data(),
               tree.num_branches() * sizeof(double));
      }

      if (part_range->master())
        _parts_master.insert(p);
    }
    else
    {
      // this partition will be processed by other threads, but we still need to know
      // which parameters to optimize
      _pll_treeinfo->params_to_optimize[p] = params_to_optimize;
    }
  }

  // finalize partition contribution computation
  for (auto& c: _partition_contributions)
    c /= total_weight;
}

TreeInfo::~TreeInfo ()
{
  if (_pll_treeinfo)
  {
    for (unsigned int i = 0; i < _pll_treeinfo->partition_count; ++i)
    {
      if (_pll_treeinfo->partitions[i])
        pll_partition_destroy(_pll_treeinfo->partitions[i]);
    }

    pll_utree_graph_destroy(_pll_treeinfo->root, NULL);
    pllmod_treeinfo_destroy(_pll_treeinfo);
  }
}

void TreeInfo::assert_lh_improvement(double old_lh, double new_lh, const std::string& where)
{
  if (_check_lh_impr && !(old_lh - new_lh < -new_lh * RAXML_LOGLH_TOLERANCE))
  {
    throw runtime_error((where.empty() ? "" : "[" + where + "] ") +
                        "Worse log-likelihood after optimization!\n" +
                        "Old: " + to_string(old_lh) + "\n"
                        "New: " + to_string(new_lh) + "\n" +
                        "NOTE: You can disable this check with '--force model_lh_impr'");
  }
}


Tree TreeInfo::tree() const
{
  if (!_pll_treeinfo)
    return Tree();

  Tree tree(*_pll_treeinfo->tree);

  if (_pll_treeinfo->brlen_linkage == PLLMOD_COMMON_BRLEN_UNLINKED)
  {
    // set per-partition branch lengths
    for (unsigned int i = 0; i < _pll_treeinfo->partition_count; ++i)
    {
      assert(_pll_treeinfo->branch_lengths[i]);
      doubleVector brlens(_pll_treeinfo->branch_lengths[i],
                          _pll_treeinfo->branch_lengths[i] + tree.num_branches());
      tree.add_partition_brlens(std::move(brlens));
    }

    // compute a weighted average of per-partition brlens
    tree.apply_avg_brlens(_partition_contributions);
  }

  return tree;
}

Tree TreeInfo::tree(size_t partition_id) const
{
  if (!_pll_treeinfo)
    return Tree();

  if (partition_id >= _pll_treeinfo->partition_count)
    throw out_of_range("Partition ID out of range");

  PllUTreeUniquePtr pll_utree(pllmod_treeinfo_get_partition_tree(_pll_treeinfo, partition_id));

  if (!pll_utree)
  {
    assert(pll_errno);
    libpll_check_error("treeinfo: cannot get partition tree");
  }

  return Tree(pll_utree);
}

void TreeInfo::tree(const Tree& tree)
{
  _pll_treeinfo->root = pll_utree_graph_clone(&tree.pll_utree_root());
}

double TreeInfo::loglh(bool incremental)
{
  return pllmod_treeinfo_compute_loglh(_pll_treeinfo, incremental ? 1 : 0);
}

double TreeInfo::persite_loglh(std::vector<double*> part_site_lh, bool incremental)
{
  assert(part_site_lh.size() == _pll_treeinfo->partition_count);
  return pllmod_treeinfo_compute_loglh_persite(_pll_treeinfo, incremental ? 1 : 0,
      part_site_lh.data());
}


void TreeInfo::model(size_t partition_id, const Model& model)
{
  if (partition_id >= _pll_treeinfo->partition_count)
    throw out_of_range("Partition ID out of range");

  if (!_pll_treeinfo->partitions[partition_id])
    return;

  assign(_pll_treeinfo->partitions[partition_id], model);
  _pll_treeinfo->alphas[partition_id] = model.alpha();
  if (_pll_treeinfo->brlen_scalers)
    _pll_treeinfo->brlen_scalers[partition_id] = model.brlen_scaler();
}

//#define DBG printf

double TreeInfo::optimize_branches(double lh_epsilon, double brlen_smooth_factor)
{
  /* update all CLVs and p-matrices before calling BLO */
  double new_loglh = loglh();

  if (_pll_treeinfo->params_to_optimize[0] & PLLMOD_OPT_PARAM_BRANCHES_ITERATIVE)
  {
    int max_iters = brlen_smooth_factor * RAXML_BRLEN_SMOOTHINGS;
    new_loglh = -1 * pllmod_algo_opt_brlen_treeinfo(_pll_treeinfo,
                                                    _brlen_min,
                                                    _brlen_max,
                                                    lh_epsilon,
                                                    max_iters,
                                                    _brlen_opt_method,
                                                    PLLMOD_OPT_BRLEN_OPTIMIZE_ALL
                                                    );

    LOG_DEBUG << "\t - after brlen: logLH = " << new_loglh << endl;

    libpll_check_error("ERROR in branch length optimization");
    assert(isfinite(new_loglh));
  }

  /* optimize brlen scalers, if needed */
  if (_pll_treeinfo->brlen_linkage == PLLMOD_COMMON_BRLEN_SCALED &&
      _pll_treeinfo->partition_count > 1)
  {
    new_loglh = -1 * pllmod_algo_opt_brlen_scalers_treeinfo(_pll_treeinfo,
                                                            RAXML_BRLEN_SCALER_MIN,
                                                            RAXML_BRLEN_SCALER_MAX,
                                                            _brlen_min,
                                                            _brlen_max,
                                                            RAXML_PARAM_EPSILON);

    LOG_DEBUG << "\t - after brlen scalers: logLH = " << new_loglh << endl;

    libpll_check_error("ERROR in brlen scaler optimization");
    assert(isfinite(new_loglh));
  }

  return new_loglh;
}

double TreeInfo::optimize_params(int params_to_optimize, double lh_epsilon)
{
  assert(!pll_errno);

  double
    cur_loglh = loglh(),
    new_loglh = cur_loglh;

  /* optimize SUBSTITUTION RATES */
  if (params_to_optimize & PLLMOD_OPT_PARAM_SUBST_RATES)
  {
    new_loglh = -1 * pllmod_algo_opt_subst_rates_treeinfo(_pll_treeinfo,
                                                          0,
                                                          PLLMOD_OPT_MIN_SUBST_RATE,
                                                          PLLMOD_OPT_MAX_SUBST_RATE,
                                                          RAXML_BFGS_FACTOR,
                                                          RAXML_PARAM_EPSILON);

    LOG_DEBUG << "\t - after rates: logLH = " << new_loglh << endl;

    libpll_check_error("ERROR in substitution rates optimization");
    assert_lh_improvement(cur_loglh, new_loglh, "RATES");
    cur_loglh = new_loglh;
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

    LOG_DEBUG << "\t - after freqs: logLH = " << new_loglh << endl;

    libpll_check_error("ERROR in base frequencies optimization");
    assert_lh_improvement(cur_loglh, new_loglh, "FREQS");
    cur_loglh = new_loglh;
  }

  // TODO: co-optimization of PINV and ALPHA, mb with multiple starting points
  if (0 &&
      (params_to_optimize & PLLMOD_OPT_PARAM_ALPHA) &&
      (params_to_optimize & PLLMOD_OPT_PARAM_PINV))
  {
    new_loglh = -1 * pllmod_algo_opt_alpha_pinv_treeinfo(_pll_treeinfo,
                                                         0,
                                                         PLLMOD_OPT_MIN_ALPHA,
                                                         PLLMOD_OPT_MAX_ALPHA,
                                                         PLLMOD_OPT_MIN_PINV,
                                                         PLLMOD_OPT_MAX_PINV,
                                                         RAXML_BFGS_FACTOR,
                                                         RAXML_PARAM_EPSILON);

    LOG_DEBUG << "\t - after a+i  : logLH = " << new_loglh << endl;

    libpll_check_error("ERROR in alpha/p-inv parameter optimization");
    assert_lh_improvement(cur_loglh, new_loglh, "ALPHA+PINV");
    cur_loglh = new_loglh;
  }
  else
  {
    /* optimize ALPHA */
    if (params_to_optimize & PLLMOD_OPT_PARAM_ALPHA)
    {
      new_loglh = -1 * pllmod_algo_opt_onedim_treeinfo(_pll_treeinfo,
                                                        PLLMOD_OPT_PARAM_ALPHA,
                                                        PLLMOD_OPT_MIN_ALPHA,
                                                        PLLMOD_OPT_MAX_ALPHA,
                                                        RAXML_PARAM_EPSILON);

     LOG_DEBUG << "\t - after alpha: logLH = " << new_loglh << endl;

     libpll_check_error("ERROR in alpha parameter optimization");
     assert_lh_improvement(cur_loglh, new_loglh, "ALPHA");
     cur_loglh = new_loglh;
    }

    /* optimize PINV */
    if (params_to_optimize & PLLMOD_OPT_PARAM_PINV)
    {
      new_loglh = -1 * pllmod_algo_opt_onedim_treeinfo(_pll_treeinfo,
                                                        PLLMOD_OPT_PARAM_PINV,
                                                        PLLMOD_OPT_MIN_PINV,
                                                        PLLMOD_OPT_MAX_PINV,
                                                        RAXML_PARAM_EPSILON);

      LOG_DEBUG << "\t - after p-inv: logLH = " << new_loglh << endl;

      libpll_check_error("ERROR in p-inv optimization");
      assert_lh_improvement(cur_loglh, new_loglh, "PINV");
      cur_loglh = new_loglh;
    }
  }

  /* optimize FREE RATES and WEIGHTS */
  if (params_to_optimize & PLLMOD_OPT_PARAM_FREE_RATES)
  {
    new_loglh = -1 * pllmod_algo_opt_rates_weights_treeinfo (_pll_treeinfo,
                                                          RAXML_FREERATE_MIN,
                                                          RAXML_FREERATE_MAX,
                                                          _brlen_min,
                                                          _brlen_max,
                                                          RAXML_BFGS_FACTOR,
                                                          RAXML_PARAM_EPSILON);

    LOG_DEBUG << "\t - after freeR: logLH = " << new_loglh << endl;
//    LOG_DEBUG << "\t - after freeR/crosscheck: logLH = " << loglh() << endl;

    libpll_check_error("ERROR in FreeRate rates/weights optimization");
    assert_lh_improvement(cur_loglh, new_loglh, "FREE RATES");
    cur_loglh = new_loglh;
  }

  if (params_to_optimize & PLLMOD_OPT_PARAM_BRANCHES_ITERATIVE)
  {
    new_loglh = optimize_branches(lh_epsilon, 0.25);

    assert_lh_improvement(cur_loglh, new_loglh, "BRLEN");
    cur_loglh = new_loglh;
  }

  return new_loglh;
}

double TreeInfo::spr_round(spr_round_params& params)
{
  double loglh = pllmod_algo_spr_round(_pll_treeinfo, params.radius_min, params.radius_max,
                               params.ntopol_keep, params.thorough, _brlen_opt_method,
                               _brlen_min, _brlen_max, RAXML_BRLEN_SMOOTHINGS,
                               0.1,
                               params.subtree_cutoff > 0. ? &params.cutoff_info : nullptr,
                               params.subtree_cutoff);

  libpll_check_error("ERROR in SPR round");

  assert(isfinite(loglh) && loglh);

  return loglh;
}

void TreeInfo::set_topology_constraint(const Tree& cons_tree)
{
  if (!cons_tree.empty())
  {
    int retval = pllmod_treeinfo_set_constraint_tree(_pll_treeinfo, &cons_tree.pll_utree());
    if (!retval)
      libpll_check_error("ERROR: Cannot set topological constraint");
  }
}

void TreeInfo::compute_ancestral(const AncestralStatesSharedPtr& ancestral,
                                 const PartitionAssignment& part_assign)
{
  pllmod_ancestral_t * pll_ancestral = pllmod_treeinfo_compute_ancestral(_pll_treeinfo);

  if (!pll_ancestral)
    libpll_check_error("Unable to compute ancestral states", true);

  assert(pll_ancestral->partition_count > 0 && pll_ancestral->partition_indices);

  if (ParallelContext::master_thread())
    assign_tree(*ancestral, *pll_ancestral);

  assign_probs(*ancestral, *pll_ancestral, part_assign);

  pllmod_treeinfo_destroy_ancestral(pll_ancestral);
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

void build_clv(ProbVector::const_iterator probs, size_t sites, WeightVector::const_iterator weights,
               pll_partition_t* partition, bool normalize, std::vector<double>& clv)
{
  const auto states = partition->states;
  auto clvp = clv.begin();

  for (size_t i = 0; i < sites; ++i)
  {
    if (weights[i] > 0)
    {
      double sum = 0.;
      for (size_t j = 0; j < states; ++j)
        sum += probs[j];

      for (size_t j = 0; j < states; ++j)
      {
        if (sum > 0.)
          clvp[j] =  normalize ? probs[j] / sum : probs[j];
        else
          clvp[j] = 1.0;
      }

      clvp += states;
    }

    /* NB: clv has to be padded, but msa arrays are not! */
    probs += states;
  }

  assert(clvp == clv.end());
}

void set_partition_tips(const Options& opts, const MSA& msa, const IDVector& tip_msa_idmap,
                        const PartitionRange& part_region,
                        pll_partition_t* partition, const pll_state_t * charmap)
{
  /* get "true" sequence offset considering that MSA can be partially loaded */
  auto seq_offset = msa.get_local_offset(part_region.start);

//  printf("\n\n rank %lu, GLOBAL OFFSET %lu, LOCAL OFFSET %lu \n\n", ParallelContext::proc_id(), part_region.start, seq_offset);

  /* set pattern weights */
  if (!msa.weights().empty())
    pll_set_pattern_weights(partition, msa.weights().data() + seq_offset);

  if (opts.use_prob_msa && msa.probabilistic())
  {
    assert(!(partition->attributes & PLL_ATTRIB_PATTERN_TIP));
    assert(partition->states == msa.states());

    auto normalize = !msa.normalized();
    auto weights_start = msa.weights().cbegin() + seq_offset;

    // we need a libpll function for that!
    auto clv_size = partition->sites * partition->states;
    std::vector<double> tmp_clv(clv_size);
    for (size_t tip_id = 0; tip_id < partition->tips; ++tip_id)
    {
      auto seq_id = tip_msa_idmap.empty() ? tip_id : tip_msa_idmap[tip_id];
      auto prob_start = msa.probs(seq_id, seq_offset);
      build_clv(prob_start, partition->sites, weights_start, partition, normalize, tmp_clv);
      pll_set_tip_clv(partition, tip_id, tmp_clv.data(), PLL_FALSE);
    }
  }
  else
  {
    for (size_t tip_id = 0; tip_id < partition->tips; ++tip_id)
    {
      auto seq_id = tip_msa_idmap.empty() ? tip_id : tip_msa_idmap[tip_id];
      pll_set_tip_states(partition, tip_id, charmap, msa.at(seq_id).c_str() + seq_offset);
    }
  }
}

void set_partition_tips(const Options& opts, const MSA& msa, const IDVector& tip_msa_idmap,
                        const PartitionRange& part_region,
                        pll_partition_t* partition, const pll_state_t * charmap,
                        const WeightVector& weights)
{
  assert(!weights.empty());

  const auto pstart = msa.get_local_offset(part_region.start);
  const auto plen = part_region.length;
  const auto pend = pstart + plen;

  /* compress weights array by removing all zero entries */
  uintVector comp_weights;
  for (size_t j = pstart; j < pend; ++j)
  {
    if (weights[j] > 0)
      comp_weights.push_back(weights[j]);
  }

  /* now set tip sequences, ignoring all columns with zero weights */
  if (opts.use_prob_msa && msa.probabilistic())
  {
    assert(!(partition->attributes & PLL_ATTRIB_PATTERN_TIP));
    assert(partition->states == msa.states());

    auto normalize = !msa.normalized();
    auto weights_start = msa.weights().cbegin() + pstart;

    // we need a libpll function for that!
    auto clv_size = plen * partition->states;
    std::vector<double> tmp_clv(clv_size);
    for (size_t tip_id = 0; tip_id < partition->tips; ++tip_id)
    {
      auto seq_id = tip_msa_idmap.empty() ? tip_id : tip_msa_idmap[tip_id];
      auto prob_start = msa.probs(seq_id, pstart);
      build_clv(prob_start, plen, weights_start, partition, normalize, tmp_clv);
      pll_set_tip_clv(partition, tip_id, tmp_clv.data(), PLL_FALSE);
    }
  }
  else
  {
    std::vector<char> bs_seq(plen);
    for (size_t tip_id = 0; tip_id < partition->tips; ++tip_id)
    {
      auto seq_id = tip_msa_idmap.empty() ? tip_id : tip_msa_idmap[tip_id];
      const char * full_seq = msa.at(seq_id).c_str();
      size_t pos = 0;
      for (size_t j = pstart; j < pend; ++j)
      {
        if (weights[j] > 0)
          bs_seq[pos++] = full_seq[j];
      }
      assert(pos == comp_weights.size());

      pll_set_tip_states(partition, tip_id, charmap, bs_seq.data());
    }
  }

  pll_set_pattern_weights(partition, comp_weights.data());
}

pll_partition_t* create_pll_partition(const Options& opts, const PartitionInfo& pinfo,
                                      const IDVector& tip_msa_idmap,
                                      const PartitionRange& part_region, const uintVector& weights)
{
  const MSA& msa = pinfo.msa();
  const Model& model = pinfo.model();
  const auto pstart = msa.get_local_offset(part_region.start);

//  printf("\n\n rank %lu, GLOBAL OFFSET %lu, LOCAL OFFSET %lu \n\n", ParallelContext::proc_id(), part_region.start, pstart);

  /* part_length doesn't include columns with zero weight */
  const size_t part_length = weights.empty() ? part_region.length :
                             std::count_if(weights.begin() + pstart,
                                           weights.begin() + pstart + part_region.length,
                                           [](uintVector::value_type w) -> bool
                                             { return w > 0; }
                                           );

  unsigned int attrs = opts.simd_arch;

  if (opts.use_rate_scalers && model.num_ratecats() > 1)
  {
    attrs |= PLL_ATTRIB_RATE_SCALERS;
  }

  if (opts.use_repeats)
  {
    assert(!(opts.use_prob_msa));
    attrs |= PLL_ATTRIB_SITE_REPEATS;
  }
  else if (opts.use_tip_inner)
  {
    assert(!(opts.use_prob_msa));
    // 1) SSE3 tip-inner kernels are not implemented so far, so generic version will be faster
    // 2) same for state-rich models
    if (opts.simd_arch != PLL_ATTRIB_ARCH_SSE && model.num_states() <= 20)
    {
      // TODO: use proper auto-tuning
      const unsigned long min_len_ti = model.num_states() > 4 ? 40 : 100;
      if ((unsigned long) part_length > min_len_ti)
        attrs |= PLL_ATTRIB_PATTERN_TIP;
    }
  }

  // NOTE: if partition is split among multiple threads, asc. bias correction must be applied only once!
  if (model.ascbias_type() == AscBiasCorrection::lewis ||
      (model.ascbias_type() != AscBiasCorrection::none && part_region.master()))
  {
    attrs |=  PLL_ATTRIB_AB_FLAG;
    attrs |= (unsigned int) model.ascbias_type();
  }

  BasicTree tree(msa.size());
  pll_partition_t * partition = pll_partition_create(
      tree.num_tips(),         /* number of tip sequences */
      tree.num_inner(),        /* number of CLV buffers */
      model.num_states(),      /* number of states in the data */
      part_length,             /* number of alignment sites/patterns */
      model.num_submodels(),   /* number of different substitution models (LG4 = 4) */
      tree.num_branches(),     /* number of probability matrices */
      model.num_ratecats(),    /* number of (GAMMA) rate categories */
      tree.num_inner(),        /* number of scaling buffers */
      attrs                    /* list of flags (SSE3/AVX, TIP-INNER special cases etc.) */
  );

  libpll_check_error("ERROR creating pll_partition");
  assert(partition);

  if (part_region.master() && !model.ascbias_weights().empty())
    pll_set_asc_state_weights(partition, model.ascbias_weights().data());

  if (part_length == part_region.length)
    set_partition_tips(opts, msa, tip_msa_idmap, part_region, partition, model.charmap());
  else
    set_partition_tips(opts, msa, tip_msa_idmap, part_region, partition, model.charmap(), weights);

  assign(partition, model);

  return partition;
}
