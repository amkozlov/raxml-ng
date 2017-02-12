#include "TreeInfo.hpp"

using namespace std;

TreeInfo::TreeInfo (const Options &opts, const Tree& tree, const PartitionedMSA& parted_msa)
{
  _pll_treeinfo = pllmod_treeinfo_create(tree.pll_utree_start(), tree.num_tips(),
                                         parted_msa.part_count(), opts.brlen_linkage);

  if (!_pll_treeinfo)
    throw runtime_error("ERROR creating treeinfo structure: " + string(pll_errmsg));

#if (defined(_USE_PTHREADS) || defined(_USE_MPI))
  pllmod_treeinfo_set_parallel_context(treeinfo, (void *) useropt, parallel_reduce_cb);
#endif

  // init partitions
  for (size_t p = 0; p < parted_msa.part_count(); ++p)
  {
    const PartitionInfo& pinfo = parted_msa.part_info(p);

    /* create and init PLL partition structure */
    pll_partition_t * partition = create_pll_partition(opts, pinfo, tree);

#ifdef _USE_PTHREADS
    parallel_thread_barrier(useropt);
#endif

    int retval = pllmod_treeinfo_init_partition(_pll_treeinfo, p, partition,
                                                pinfo.model().params_to_optimize(),
                                                pinfo.model().alpha(),
                                                pinfo.model().ratecat_submodels().data(),
                                                pinfo.model().submodel(0)->rate_sym);

    if (!retval)
      throw runtime_error("ERROR adding treeinfo partition: " + string(pll_errmsg));
  }
}

TreeInfo::~TreeInfo ()
{
  if (_pll_treeinfo)
    pllmod_treeinfo_destroy(_pll_treeinfo);
}

double TreeInfo::loglh(bool incremental)
{
  return pllmod_treeinfo_compute_loglh(_pll_treeinfo, incremental ? 1 : 0);
}

void set_partition_tips(PartitionInfo const& pinfo, pll_partition_t* partition,
                        IdNameVector const& clv_label_map)
{
  for (auto const& entry: clv_label_map)
  {
    try
    {
      pll_set_tip_states(partition, entry.first, partition->map,
                         pinfo.msa().at(entry.second).c_str());
    }
    catch (out_of_range const& ex)
    {
      throw runtime_error("Sequence not found in alignment: " + entry.second);
    }
  }
}

pll_partition_t* create_pll_partition(Options const& opts, PartitionInfo const& pinfo,
                                      Tree const& tree)
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
      msa.length(),            /* number of alignment sites/patterns */
      model.num_submodels(),   /* number of different substitution models (LG4 = 4) */
      tree.num_branches(),     /* number of probability matrices */
      model.num_ratecats(),    /* number of (GAMMA) rate categories */
      tree.num_inner(),        /* number of scaling buffers */
      attrs                    /* list of flags (SSE3/AVX, TIP-INNER special cases etc.) */
  );

  partition->map = model.charmap();

  // TODO: exception
  if (!partition)
    throw runtime_error("ERROR creating pll_partition: " + string(pll_errmsg));

  /* set pattern weights */
  if (msa.weights())
    pll_set_pattern_weights(partition, msa.weights());

  assign(partition, model);

  set_partition_tips(pinfo, partition, tree.tip_labels());

  return partition;
}


