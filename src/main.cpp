/*
    Copyright (C) 2017 Alexey Kozlov, Alexandros Stamatakis, Diego Darriba, Tomas Flouri

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Contact: Alexey Kozlov <Alexey.Kozlov@h-its.org>,
    Heidelberg Institute for Theoretical Studies,
    Schloss-Wolfsbrunnenweg 35, D-69118 Heidelberg, Germany
*/
#include <algorithm>
#include <chrono>

#include <memory>

#include "version.h"
#include "common.h"
#include "MSA.hpp"
#include "Options.hpp"
#include "CommandLineParser.hpp"
#include "Optimizer.hpp"
#include "PartitionInfo.hpp"
#include "PartitionedMSAView.hpp"
#include "TreeInfo.hpp"
#include "io/file_io.hpp"
#include "io/binary_io.hpp"
#include "ParallelContext.hpp"
#include "loadbalance/LoadBalancer.hpp"
#include "bootstrap/BootstrapGenerator.hpp"
#include "bootstrap/BootstopCheck.hpp"
#include "autotune/ResourceEstimator.hpp"

#ifdef _RAXML_TERRAPHAST
#include "terraces/TerraceWrapper.hpp"
#endif

using namespace std;

typedef vector<Tree> TreeList;
struct RaxmlInstance
{
  Options opts;
  shared_ptr<PartitionedMSA> parted_msa;
  unique_ptr<PartitionedMSA> parted_msa_parsimony;
  TreeList start_trees;
  BootstrapReplicateList bs_reps;
  TreeList bs_start_trees;
  PartitionAssignmentList proc_part_assign;
  unique_ptr<LoadBalancer> load_balancer;
  unique_ptr<BootstrapTree> bs_tree;

  // bootstopping convergence test, only autoMRE is supported for now
  unique_ptr<BootstopCheckMRE> bootstop_checker;

  // mapping taxon name -> tip_id/clv_id in the tree
  NameIdMap tip_id_map;

  // mapping tip_id in the tree (array index) -> sequence index in MSA
  IDVector tip_msa_idmap;

 // unique_ptr<TerraceWrapper> terrace_wrapper;

//  unique_ptr<RandomGenerator> starttree_seed_gen;
//  unique_ptr<RandomGenerator> bootstrap_seed_gen;

  unique_ptr<NewickStream> start_tree_stream;

  /* this is just a dummy random tree used for convenience, e,g, if we need tip labels or
   * just 'any' valid tree for the alignment at hand */
  Tree random_tree;

  /* topological constraint */
  Tree constraint_tree;
};

void print_banner()
{
  LOG_INFO << endl << "RAxML-NG v. " << RAXML_VERSION << " released on " << RAXML_DATE <<
      " by The Exelixis Lab." << endl;
  LOG_INFO << "Authors: Alexey Kozlov, Alexandros Stamatakis, Diego Darriba, "
              "Tomas Flouri, Benoit Morel." << endl;
  LOG_INFO << "Latest version: https://github.com/amkozlov/raxml-ng" << endl;
  LOG_INFO << "Questions/problems/suggestions? "
              "Please visit: https://groups.google.com/forum/#!forum/raxml" << endl;
  LOG_INFO << endl << "WARNING: This is a BETA release, please use at your own risk!" << endl << endl;
}

void init_part_info(RaxmlInstance& instance)
{
  auto& opts = instance.opts;

  instance.parted_msa = std::make_shared<PartitionedMSA>();
  auto& parted_msa = *instance.parted_msa;

  if (!sysutil_file_exists(opts.msa_file))
  {
    throw runtime_error("Alignment file not found: " + opts.msa_file);
  }

  /* check if we have a binary input file */
  if (opts.msa_format == FileFormat::binary ||
      (opts.msa_format == FileFormat::autodetect && RBAStream::rba_file(opts.msa_file)))
  {
    if (!opts.model_file.empty())
    {
      LOG_WARN <<
          "WARNING: The model you specified on the command line (" << opts.model_file <<
                    ") will be ignored " << endl <<
          "         since the binary MSA file already contains a model definition." << endl <<
          "         If you want to change the model, please re-run RAxML-NG "  << endl <<
          "         with the original PHYLIP/FASTA alignment and --redo option."
          << endl << endl;
    }

    LOG_INFO_TS << "Loading binary alignment from file: " << opts.msa_file << endl;

    RBAStream bs(opts.msa_file);
    bs >> parted_msa;

    // binary probMSAs are not supported yet
    instance.opts.use_prob_msa = false;

    LOG_INFO_TS << "Alignment comprises " << parted_msa.taxon_count() << " taxa, " <<
        parted_msa.part_count() << " partitions and " <<
        parted_msa.total_length() << " patterns\n" << endl;

    LOG_INFO << parted_msa;

    LOG_INFO << endl;
  }
  /* check if model is a file */
  else if (sysutil_file_exists(opts.model_file))
  {
    // read partition definitions from file
    RaxmlPartitionStream partfile(opts.model_file, ios::in);
    partfile >> parted_msa;

//    DBG("partitions found: %d\n", useropt->part_count);
  }
  else if (!opts.model_file.empty())
  {
    // create and init single pseudo-partition
    parted_msa.emplace_part_info("noname", opts.data_type, opts.model_file);
  }
  else
    throw runtime_error("Please specify an evolutionary model with --model switch");

  /* make sure that linked branch length mode is set for unpartitioned alignments */
  if (parted_msa.part_count() == 1)
    opts.brlen_linkage = PLLMOD_COMMON_BRLEN_LINKED;

  /* in the scaled brlen mode, use ML optimization of brlen scalers by default */
  if (opts.brlen_linkage == PLLMOD_COMMON_BRLEN_SCALED)
  {
    for (auto& pinfo: parted_msa.part_list())
      pinfo.model().set_param_mode_default(PLLMOD_OPT_PARAM_BRANCH_LEN_SCALER, ParamValue::ML);
  }

  int freerate_count = 0;

  for (const auto& pinfo: parted_msa.part_list())
  {
    LOG_DEBUG << "|" << pinfo.name() << "|   |" << pinfo.model().to_string() << "|   |" <<
        pinfo.range_string() << "|" << endl;

    if (pinfo.model().ratehet_mode() == PLLMOD_UTIL_MIXTYPE_FREE)
      freerate_count++;
  }

  if (parted_msa.part_count() > 1 && freerate_count > 0 &&
      opts.brlen_linkage == PLLMOD_COMMON_BRLEN_LINKED)
  {
    throw runtime_error("LG4X and FreeRate models are not supported in linked branch length mode.\n"
        "Please use the '--brlen scaled' option to switch into proportional branch length mode.");
  }
}

void print_reduced_msa(const RaxmlInstance& instance, const PartitionedMSAView& reduced_msa_view)
{
  // save reduced MSA and partition files
  auto reduced_msa_fname = instance.opts.output_fname("reduced.phy");
  PhylipStream ps(reduced_msa_fname);

  ps << reduced_msa_view;

  LOG_INFO << "\nNOTE: Reduced alignment (with duplicates and gap-only sites/taxa removed) "
              "\nNOTE: was saved to: ";
  LOG_INFO << sysutil_realpath(reduced_msa_fname) << endl;

  // save reduced partition file
  if (sysutil_file_exists(instance.opts.model_file))
  {
    auto reduced_part_fname = instance.opts.output_fname("reduced.partition");
    RaxmlPartitionStream ps(reduced_part_fname, ios::out);

    ps << reduced_msa_view;

    LOG_INFO << "\nNOTE: The corresponding reduced partition file was saved to:\n";
    LOG_INFO << sysutil_realpath(reduced_part_fname) << endl;
  }
}

bool check_msa(RaxmlInstance& instance)
{
  LOG_VERB_TS << "Checking the alignment...\n";

  auto& parted_msa = *instance.parted_msa;
  const auto& full_msa = parted_msa.full_msa();
  const auto pll_msa = full_msa.pll_msa();
  const auto taxon_count = parted_msa.taxon_count();

  bool msa_valid = true;
  bool msa_corrected = false;
  PartitionedMSAView parted_msa_view(instance.parted_msa);

  vector<pair<size_t,size_t> > dup_taxa;
  vector<pair<size_t,size_t> > dup_seqs;
  std::set<size_t> gap_seqs;

  /* check taxa count */
  if (taxon_count < 4)
  {
    LOG_ERROR << "\nERROR: Your alignment contains less than 4 sequences! " << endl;
    return false;
  }

  /* check taxon names */
  const string invalid_chars = "(),;:' \t\n";
  for (const auto& taxon: parted_msa.taxon_names())
  {
    if (taxon.find_first_of(invalid_chars) != std::string::npos)
    {
      size_t i = 0;
      auto fixed_name = taxon;
      while ((i = fixed_name.find_first_of(invalid_chars, i)) != std::string::npos)
        fixed_name[i++] = '_';
      parted_msa_view.map_taxon_name(taxon, fixed_name);
    }
  }

  msa_valid &= parted_msa_view.taxon_name_map().empty();

  unsigned long stats_mask = PLLMOD_MSA_STATS_DUP_TAXA | PLLMOD_MSA_STATS_DUP_SEQS;

  pllmod_msa_stats_t * stats = pllmod_msa_compute_stats(pll_msa,
                                                        4,
                                                        pll_map_nt, // map is not used here
                                                        NULL,
                                                        stats_mask);

  libpll_check_error("ERROR computing MSA stats");
  assert(stats);

  for (unsigned long c = 0; c < stats->dup_taxa_pairs_count; ++c)
  {
    dup_taxa.emplace_back(stats->dup_taxa_pairs[c*2],
                          stats->dup_taxa_pairs[c*2+1]);
  }

  msa_valid &= dup_taxa.empty();

  for (unsigned long c = 0; c < stats->dup_seqs_pairs_count; ++c)
  {
    dup_seqs.emplace_back(stats->dup_seqs_pairs[c*2],
                          stats->dup_seqs_pairs[c*2+1]);
  }

  pllmod_msa_destroy_stats(stats);

  size_t total_gap_cols = 0;
  size_t part_num = 0;
  for (auto& pinfo: parted_msa.part_list())
  {
    stats_mask = PLLMOD_MSA_STATS_GAP_SEQS | PLLMOD_MSA_STATS_GAP_COLS;

    pllmod_msa_stats_t * stats = pinfo.compute_stats(stats_mask);

    if (stats->gap_cols_count > 0)
    {
      total_gap_cols += stats->gap_cols_count;
      std::vector<size_t> gap_cols(stats->gap_cols, stats->gap_cols + stats->gap_cols_count);
      pinfo.msa().remove_sites(gap_cols);
//      parted_msa_view.exclude_sites(part_num, gap_cols);
    }

    std::set<size_t> cur_gap_seq(stats->gap_seqs, stats->gap_seqs + stats->gap_seqs_count);

    if (!part_num)
    {
      gap_seqs = cur_gap_seq;
    }
    else
    {
      for(auto it = gap_seqs.begin(); it != gap_seqs.end();)
      {
        if(cur_gap_seq.find(*it) == cur_gap_seq.end())
          it = gap_seqs.erase(it);
        else
          ++it;
      }
    }

    pllmod_msa_destroy_stats(stats);

    part_num++;
  }

  if (total_gap_cols > 0)
  {
    LOG_WARN << "\nWARNING: Fully undetermined columns found: " << total_gap_cols << endl;
    msa_corrected = true;
  }

  if (!gap_seqs.empty())
  {
   LOG_WARN << endl;
   for (auto c : gap_seqs)
   {
     parted_msa_view.exclude_taxon(c);
     LOG_VERB << "WARNING: Sequence #" << c+1 << " (" << parted_msa.taxon_names().at(c)
              << ") contains only gaps!" << endl;
   }
   LOG_WARN << "WARNING: Fully undetermined sequences found: " << gap_seqs.size() << endl;
  }

  if (!dup_seqs.empty())
  {
    size_t dup_count = 0;
    LOG_WARN << endl;
    for (const auto& p: dup_seqs)
    {
      /* ignore gap-only sequences */
      if (gap_seqs.count(p.first) || gap_seqs.count(p.second))
        continue;

      ++dup_count;
      parted_msa_view.exclude_taxon(p.second);
      LOG_WARN << "WARNING: Sequences " << parted_msa.taxon_names().at(p.first) << " and " <<
          parted_msa.taxon_names().at(p.second) << " are exactly identical!" << endl;
    }
    if (dup_count > 0)
      LOG_WARN << "WARNING: Duplicate sequences found: " << dup_count << endl;
  }

  if (!instance.opts.nofiles_mode && (msa_corrected || !parted_msa_view.identity()))
  {
    print_reduced_msa(instance, parted_msa_view);
  }

  if (!dup_taxa.empty())
  {
    for (const auto& p: dup_seqs)
    {
      LOG_ERROR << "ERROR: Sequences " << p.first+1 << " and "
                << p.second+1 << " have identical name: "
                << parted_msa.taxon_names().at(p.first) << endl;
    }
    LOG_ERROR << "\nERROR: Duplicate sequence names found: " << dup_taxa.size() << endl;
  }

  if (!parted_msa_view.taxon_name_map().empty())
  {
    LOG_ERROR << endl;
    for (auto it: parted_msa_view.taxon_name_map())
      LOG_ERROR << "ERROR: Following taxon name contains invalid characters: " << it.first << endl;

    LOG_ERROR << endl;
    LOG_INFO << "NOTE: Following symbols are not allowed in taxa names to ensure Newick compatibility:\n"
                "NOTE: \" \" (space), \";\" (semicolon), \":\" (colon), \",\" (comma), "
                       "\"()\" (parentheses), \"'\" (quote). " << endl;
    LOG_INFO << "NOTE: Please either correct the names manually, or use the reduced alignment file\n"
                "NOTE: generated by RAxML-NG (see above).";
    LOG_INFO << endl;
  }

  return msa_valid;
}

void check_models(const RaxmlInstance& instance)
{
  for (const auto& pinfo: instance.parted_msa->part_list())
  {
    auto stats = pinfo.stats();
    auto model = pinfo.model();

    // check for non-recommended model combinations
    if ((model.name() == "LG4X" || model.name() == "LG4M") &&
        model.param_mode(PLLMOD_OPT_PARAM_FREQUENCIES) != ParamValue::model)
    {
      throw runtime_error("Partition \"" + pinfo.name() +
                          "\": You specified LG4M or LG4X model with shared stationary based frequencies (" +
                          model.to_string(false) + ").\n"
                          "Please be warned, that this is against the idea of LG4 models and hence it's not recommended!" + "\n"
                          "If you know what you're doing, you can add --force command line switch to disable this safety check.");
    }

    // check for zero state frequencies
    if (model.param_mode(PLLMOD_OPT_PARAM_FREQUENCIES) == ParamValue::empirical)
    {
      const auto& freqs = stats.emp_base_freqs;
      for (unsigned int i = 0; i < freqs.size(); ++i)
      {
        if (!(freqs[i] > 0.))
        {
          LOG_ERROR << "\nBase frequencies: ";
          for (unsigned int j = 0; j < freqs.size(); ++j)
            LOG_ERROR << freqs[j] <<  " ";
          LOG_ERROR << endl;

          throw runtime_error("Frequency of state " + to_string(i) +
                              " in partition " + pinfo.name() + " is 0!\n"
                              "Please either change your partitioning scheme or "
                              "use model state frequencies for this partition!");
        }
      }
    }

    // check partitions which contain invariant sites and have ascertainment bias enabled
    if (model.ascbias_type() != AscBiasCorrection::none && stats.inv_count > 0)
    {
      throw runtime_error("You enabled ascertainment bias correction for partition " +
                           pinfo.name() + ", but it contains " +
                           to_string(stats.inv_count) + " invariant sites.\n"
                          "This is not allowed! Please either remove invariant sites or "
                          "disable ascertainment bias correction.");
    }
  }
}

void check_tree(const PartitionedMSA& msa, const Tree& tree)
{
  auto missing_taxa = 0;
  auto duplicate_taxa = 0;

  if (msa.taxon_count() > tree.num_tips())
    throw runtime_error("Alignment file contains more sequences than expected");
  else if (msa.taxon_count() != tree.num_tips())
    throw runtime_error("Some taxa are missing from the alignment file");

  unordered_set<string> tree_labels;
  unordered_set<string> msa_labels(msa.taxon_names().cbegin(), msa.taxon_names().cend());

  for (const auto& tip: tree.tip_labels())
  {
    if (!tree_labels.insert(tip.second).second)
    {
      LOG_ERROR << "ERROR: Taxon name appears more than once in the tree: " << tip.second << endl;
      duplicate_taxa++;
    }

    if (msa_labels.count(tip.second) == 0)
    {
      LOG_ERROR << "ERROR: Taxon name not found in the alignment: " << tip.second << endl;
      missing_taxa++;
    }
  }

  if (duplicate_taxa > 0)
    throw runtime_error("Tree contains duplicate taxon names (see above)!");

  if (missing_taxa > 0)
    throw runtime_error("Please check that sequence labels in the alignment and in the tree file are identical!");

  /* check for negative branch length */
  for (const auto& branch: tree.topology())
  {
    if (branch.length < 0.)
      throw runtime_error("Tree file contains negative branch lengths!");
  }
}

void check_options(RaxmlInstance& instance)
{
  const auto& opts = instance.opts;

  /* check that all outgroup taxa are present in the alignment */
  if (!opts.outgroup_taxa.empty())
  {
    NameList missing_taxa;
    for (const auto& ot: opts.outgroup_taxa)
    {
      if (!instance.parted_msa->taxon_id_map().count(ot))
        missing_taxa.push_back(ot);
    }

    if (!missing_taxa.empty())
    {
      LOG_ERROR << "ERROR: Following taxa were specified as an outgroup "
                                                     "but are missing from the alignment:" << endl;
      for (const auto& mt: missing_taxa)
        LOG_ERROR << mt << endl;
      LOG_ERROR << endl;
      throw runtime_error("Outgroup taxon not found.");
    }
  }

  /* following "soft" checks will be ignored in the --force mode */
  if (opts.force_mode)
    return;

  /* check that we have enough patterns per thread */
  if (ParallelContext::master_rank() && ParallelContext::num_procs() > 1)
  {
    StaticResourceEstimator resEstimator(*instance.parted_msa, instance.opts);
    auto res = resEstimator.estimate();
    if (ParallelContext::num_procs() > res.num_threads_response)
    {
      LOG_WARN << endl;
      LOG_WARN << "WARNING: You might be using too many threads (" << ParallelContext::num_procs()
               <<  ") for your alignment with " << instance.parted_msa->total_sites()
               << " unique patterns." << endl;
      LOG_WARN << "NOTE:    For the optimal throughput, please consider using fewer threads " << endl;
      LOG_WARN << "NOTE:    and parallelize across starting trees/bootstrap replicates." << endl;
      LOG_WARN << "NOTE:    As a general rule-of-thumb, please assign at least 200-1000 "
          "alignment patterns per thread." << endl << endl;

      if (ParallelContext::num_procs() > 2 * res.num_threads_response)
      {
        throw runtime_error("Too few patterns per thread! "
                            "RAxML-NG will terminate now to avoid wasting resources.\n"
                            "NOTE:  Please reduce the number of threads (see guidelines above).\n"
                            "NOTE:  This check can be disabled with the '--force' option.");
      }
    }
  }

  if (instance.parted_msa->taxon_count() > RAXML_RATESCALERS_TAXA &&
      !instance.opts.use_rate_scalers)
  {
    LOG_INFO << "\nNOTE: Per-rate scalers were automatically enabled to prevent numerical issues "
        "on taxa-rich alignments." << endl;
    LOG_INFO << "NOTE: You can use --force switch to skip this check "
        "and fall back to per-site scalers." << endl << endl;
    instance.opts.use_rate_scalers = true;
  }
}

void load_msa(RaxmlInstance& instance)
{
  const auto& opts = instance.opts;
  auto& parted_msa = *instance.parted_msa;

  LOG_INFO_TS << "Reading alignment from file: " << opts.msa_file << endl;

  /* load MSA */
  auto msa = msa_load_from_file(opts.msa_file, opts.msa_format);

  LOG_INFO_TS << "Loaded alignment with " << msa.size() << " taxa and " <<
      msa.num_sites() << " sites" << endl;

  if (msa.probabilistic() && opts.use_prob_msa)
  {
    instance.opts.use_pattern_compression = false;
    instance.opts.use_tip_inner = false;

    if (parted_msa.part_count() > 1)
      throw runtime_error("Partitioned probabilistic alignments are not supported yet, sorry...");
  }
  else
    instance.opts.use_prob_msa = false;

  parted_msa.full_msa(std::move(msa));

  LOG_VERB_TS << "Extracting partitions... " << endl;

  parted_msa.split_msa();

  /* check alignment */
  if (!opts.force_mode)
  {
    LOG_VERB_TS << "Validating alignment... " << endl;
    if (!check_msa(instance))
      throw runtime_error("Alignment check failed (see details above)!");
  }

  if (opts.use_pattern_compression)
  {
    LOG_VERB_TS << "Compressing alignment patterns... " << endl;
    parted_msa.compress_patterns();
  }

//  if (parted_msa.part_count() > 1)
//    instance.terrace_wrapper.reset(new TerraceWrapper(parted_msa));

  parted_msa.set_model_empirical_params();

  if (!opts.force_mode)
    check_models(instance);

  LOG_INFO << endl;

  LOG_INFO << "Alignment comprises " << parted_msa.part_count() << " partitions and " <<
      parted_msa.total_length() << " patterns\n" << endl;

  LOG_INFO << parted_msa;

  LOG_INFO << endl;

  if (ParallelContext::master_rank() &&
      !instance.opts.use_prob_msa && !instance.opts.binary_msa_file().empty())
  {
    auto binary_msa_fname = instance.opts.binary_msa_file();
    if (sysutil_file_exists(binary_msa_fname) && !opts.redo_mode &&
        opts.command != Command::parse)
    {
      LOG_INFO << "NOTE: Binary MSA file already exists: " << binary_msa_fname << endl << endl;
    }
    else if (opts.command != Command::check)
    {
      RBAStream bs(binary_msa_fname);
      bs << parted_msa;
      LOG_INFO << "NOTE: Binary MSA file created: " << binary_msa_fname << endl << endl;
    }
  }
}

void load_parted_msa(RaxmlInstance& instance)
{
  init_part_info(instance);

  assert(instance.parted_msa);

  if (instance.parted_msa->part_info(0).msa().empty())
    load_msa(instance);

  // use MSA sequences IDs as "normalized" tip IDs in all trees
  instance.tip_id_map = instance.parted_msa->taxon_id_map();
}

void prepare_tree(const RaxmlInstance& instance, Tree& tree)
{
  /* fix missing branch lengths */
  tree.fix_missing_brlens();

  /* make sure tip indices are consistent between MSA and pll_tree */
  assert(!instance.parted_msa->taxon_id_map().empty());
  tree.reset_tip_ids(instance.tip_id_map);
}

Tree generate_tree(const RaxmlInstance& instance, StartingTree type)
{
  Tree tree;

  const auto& opts = instance.opts;
  const auto& parted_msa = *instance.parted_msa;
  const auto  tree_rand_seed = rand();

  switch (type)
  {
    case StartingTree::user:
    {
      assert(instance.start_tree_stream);

      /* parse the unrooted binary tree in newick format, and store the number
         of tip nodes in tip_nodes_count */
      *instance.start_tree_stream >> tree;

      LOG_DEBUG << "Loaded user starting tree with " << tree.num_tips() << " taxa from: "
                           << opts.tree_file << endl;

      check_tree(parted_msa, tree);

      break;
    }
    case StartingTree::random:
      /* no starting tree provided, generate a random one */

      LOG_DEBUG << "Generating a random starting tree with " << parted_msa.taxon_count()
                << " taxa" << endl;

      if (instance.constraint_tree.empty())
        tree = Tree::buildRandom(parted_msa.taxon_names(), tree_rand_seed);
      else
        tree = Tree::buildRandomConstrained(parted_msa.taxon_names(), tree_rand_seed,
                                            instance.constraint_tree);

      break;
    case StartingTree::parsimony:
    {
      LOG_DEBUG << "Generating a parsimony starting tree with " << parted_msa.taxon_count()
                << " taxa" << endl;

      unsigned int score;
      unsigned int attrs = opts.simd_arch;

      // TODO: check if there is any reason not to use tip-inner
      attrs |= PLL_ATTRIB_PATTERN_TIP;

      const PartitionedMSA& pars_msa = instance.parted_msa_parsimony ?
                                    *instance.parted_msa_parsimony.get() : *instance.parted_msa;
      tree = Tree::buildParsimony(pars_msa, tree_rand_seed, attrs, &score);

      LOG_DEBUG << "Parsimony score of the starting tree: " << score << endl;

      break;
    }
    default:
      sysutil_fatal("Unknown starting tree type: %d\n", type);
  }

  assert(!tree.empty());

  prepare_tree(instance, tree);

  return tree;
}

void load_start_trees(RaxmlInstance& instance, CheckpointManager& cm)
{
  const auto& ckp = cm.checkpoint();

  NewickStream ts(instance.opts.start_tree_file(), std::ios::in);
  size_t i = 0;
  while (ts.peek() != EOF)
  {
    Tree tree;
    ts >> tree;
    i++;

    if (i > ckp.ml_trees.size())
    {
      prepare_tree(instance, tree);
      instance.start_trees.emplace_back(tree);
    }
  }
  if (instance.opts.start_trees.count(StartingTree::user) > 0)
  {
    // in case of user startitng trees, we do not know num_searches
    // until we read trees from the file. that's why we update num_searches here.
    assert(i >= instance.opts.num_searches);
    instance.opts.num_searches = i;
  }
  else
    assert(i == instance.opts.num_searches);
}

void load_checkpoint(RaxmlInstance& instance, CheckpointManager& cm)
{
  /* init checkpoint and set to the manager */
  {
    Checkpoint ckp;
    for (size_t p = 0; p < instance.parted_msa->part_count(); ++p)
      ckp.models[p] = instance.parted_msa->part_info(p).model();

    // this is a "template" tree, which provides tip labels and node ids
    ckp.tree = instance.random_tree;

    cm.checkpoint(move(ckp));
  }

  if (!instance.opts.redo_mode && cm.read())
  {
    const auto& ckp = cm.checkpoint();

    // read start trees from file to avoid re-generation
    // NOTE: doesn't work for constrained tree search
    if (sysutil_file_exists(instance.opts.start_tree_file()) &&
        instance.opts.constraint_tree_file.empty())
    {
      load_start_trees(instance, cm);
    }

    LOG_INFO_TS << "NOTE: Resuming execution from checkpoint " <<
        "(logLH: " << ckp.loglh() <<
        ", ML trees: " << ckp.ml_trees.size() <<
        ", bootstraps: " << ckp.bs_trees.size() <<
        ")"
        << endl;
  }
}

void load_constraint(RaxmlInstance& instance)
{
  const auto& parted_msa = *instance.parted_msa;

  if (!instance.opts.constraint_tree_file.empty())
  {
    NewickStream nw_cons(instance.opts.constraint_tree_file, std::ios::in);
    Tree& cons_tree = instance.constraint_tree;
    nw_cons >> cons_tree;

    LOG_INFO_TS << "Loaded " <<
        (cons_tree.num_tips() == parted_msa.taxon_count() ? "" : "non-") <<
        "comprehensive constraint tree with " << cons_tree.num_tips() << " taxa" << endl;

    // check if taxa names are consistent between contraint tree and MSA
    {
      NameList missing_taxa;
      for (const auto& l: cons_tree.tip_labels())
      {
        if (!parted_msa.taxon_id_map().count(l.second))
          missing_taxa.push_back(l.second);;
      }

      if (!missing_taxa.empty())
      {
        stringstream ss;
        ss << "Following " << missing_taxa.size() <<
            " taxa present in the constraint tree can not be found in the alignment: " << endl;
        for (const auto& taxon: missing_taxa)
          ss << taxon << endl;
        throw runtime_error(ss.str());
      }
    }

    if (cons_tree.num_tips() < parted_msa.taxon_count())
    {
      // incomplete constraint tree -> adjust tip IDs such that all taxa in the constraint tree
      // go before the remaining free taxa
      instance.tip_id_map.clear();
      instance.tip_msa_idmap.resize(parted_msa.taxon_count());
      auto cons_name_map = cons_tree.tip_ids();
      size_t seq_id = 0;
      size_t cons_tip_id = 0;
      size_t free_tip_id = cons_tree.num_tips();
      for (const auto& name: parted_msa.taxon_names())
      {
        auto tip_id = cons_name_map.count(name) ? cons_tip_id++ : free_tip_id++;
        instance.tip_id_map[name] = tip_id;
        instance.tip_msa_idmap[tip_id] = seq_id++;
      }
      assert(cons_tip_id == cons_tree.num_tips());
      assert(free_tip_id == instance.tip_id_map.size());
      assert(instance.tip_id_map.size() == parted_msa.taxon_count());
    }

    /* make sure tip indices are consistent between MSA and pll_tree */
    cons_tree.reset_tip_ids(instance.tip_id_map);

//    pll_utree_show_ascii(&cons_tree.pll_utree_root(), PLL_UTREE_SHOW_LABEL | PLL_UTREE_SHOW_BRANCH_LENGTH |
//                                     PLL_UTREE_SHOW_CLV_INDEX );
  }
}

void build_parsimony_msa(RaxmlInstance& instance)
{
  // create 1 partition per datatype
  const PartitionedMSA& orig_msa = *instance.parted_msa;

  instance.parted_msa_parsimony.reset(new PartitionedMSA(orig_msa.taxon_names()));
  PartitionedMSA& pars_msa = *instance.parted_msa_parsimony.get();

  std::unordered_map<string, PartitionInfo*> datatype_pinfo_map;
  for (const auto& pinfo: orig_msa.part_list())
  {
    const auto& model = pinfo.model();
    auto data_type_name = model.data_type_name();

    auto iter = datatype_pinfo_map.find(data_type_name);
    if (iter == datatype_pinfo_map.end())
    {
      pars_msa.emplace_part_info(data_type_name, model.data_type(), model.name());
      auto& pars_pinfo = pars_msa.part_list().back();
      pars_pinfo.msa(MSA(pinfo.msa().num_sites()));
      datatype_pinfo_map[data_type_name] = &pars_pinfo;
    }
    else
    {
      auto& msa = iter->second->msa();
      msa.num_sites(msa.num_sites() + pinfo.msa().num_sites());
    }
  }

  // set_per-datatype MSA
  for (size_t j = 0; j < orig_msa.taxon_count(); ++j)
  {
    for (auto& pars_pinfo: pars_msa.part_list())
    {
      auto pars_datatype = pars_pinfo.model().data_type_name();
      std::string sequence;
      sequence.resize(pars_pinfo.msa().num_sites());
      size_t offset = 0;

      for (const auto& pinfo: orig_msa.part_list())
      {
        // different datatype -> skip for now
        if (pinfo.model().data_type_name() != pars_datatype)
          continue;

        const auto w = pinfo.msa().weights();
        const auto s = pinfo.msa().at(j);

        for (size_t k = 0; k < w.size(); ++k)
        {
          auto wk = w[k];
          while(wk-- > 0)
            sequence[offset++] = s[k];
        }
      }

      assert(offset == sequence.size());

      pars_pinfo.msa().append(sequence);
    }
  }

  // compress patterns
  if (instance.opts.use_pattern_compression)
  {
    for (auto& pinfo: pars_msa.part_list())
    {
      pinfo.compress_patterns();
    }
  }
}

void build_start_trees(RaxmlInstance& instance, size_t skip_trees)
{
  auto& opts = instance.opts;
  const auto& parted_msa = *instance.parted_msa;

  /* all start trees were already generated/loaded -> return */
  if (skip_trees + instance.start_trees.size() >= instance.opts.num_searches)
    return;

  for (auto& st_tree: opts.start_trees)
  {
    auto st_tree_type = st_tree.first;
    auto& st_tree_count = st_tree.second;
    switch (st_tree_type)
    {
      case StartingTree::user:
        LOG_INFO_TS << "Loading user starting tree(s) from: " << opts.tree_file << endl;
        if (!sysutil_file_exists(opts.tree_file))
          throw runtime_error("File not found: " + opts.tree_file);
        instance.start_tree_stream.reset(new NewickStream(opts.tree_file, std::ios::in));
        break;
      case StartingTree::random:
        LOG_INFO_TS << "Generating " << st_tree_count << " random starting tree(s) with "
                    << parted_msa.taxon_count() << " taxa" << endl;
        break;
      case StartingTree::parsimony:
        if (parted_msa.part_count() > 1)
        {
          LOG_DEBUG_TS << "Generating MSA partitioned by data type for parsimony computation" << endl;
          build_parsimony_msa(instance);
        }
        LOG_INFO_TS << "Generating " << st_tree_count << " parsimony starting tree(s) with "
                    << parted_msa.taxon_count() << " taxa" << endl;
        break;
      default:
        assert(0);
    }

    for (size_t i = 0; i < st_tree_count; ++i)
    {
      auto tree = generate_tree(instance, st_tree_type);

      // TODO use universal starting tree generator
      if (st_tree_type == StartingTree::user)
      {
        if (instance.start_tree_stream->peek() != EOF)
        {
          st_tree_count++;
          opts.num_searches++;
        }
      }

      if (skip_trees > 0)
      {
        skip_trees--;
        continue;
      }

      instance.start_trees.emplace_back(tree);
    }
  }

  // free memory used for parsimony MSA
  instance.parted_msa_parsimony.release();

  if (::ParallelContext::master_rank())
  {
    NewickStream nw_start(opts.start_tree_file());
    for (auto const& tree: instance.start_trees)
      nw_start << tree;
  }
}

void balance_load(RaxmlInstance& instance)
{
  PartitionAssignment part_sizes;

  /* init list of partition sizes */
  size_t i = 0;
  for (auto const& pinfo: instance.parted_msa->part_list())
  {
    part_sizes.assign_sites(i, 0, pinfo.msa().length(), pinfo.model().clv_entry_size());
    ++i;
  }

  instance.proc_part_assign =
      instance.load_balancer->get_all_assignments(part_sizes, ParallelContext::num_procs());

  LOG_INFO_TS << "Data distribution: " << PartitionAssignmentStats(instance.proc_part_assign) << endl;
  LOG_VERB << endl << instance.proc_part_assign;
}

void balance_load(RaxmlInstance& instance, WeightVectorList part_site_weights)
{
  /* This function is used to re-distribute sites across processes for each bootstrap replicate.
   * Since during bootstrapping alignment sites are sampled with replacement, some sites will be
   * absent from BS alignment. Therefore, site distribution computed for original alignment can
   * be suboptimal for BS replicates. Here, we recompute the site distribution, ignoring all sites
   * that are not present in BS replicate (i.e., have weight of 0 in part_site_weights).
   * */

  PartitionAssignment part_sizes;
  WeightVectorList comp_pos_map(part_site_weights.size());

  /* init list of partition sizes */
  size_t i = 0;
  for (auto const& weights: part_site_weights)
  {
    /* build mapping from compressed indices to the original/uncompressed ones */
    comp_pos_map[i].reserve(weights.size());
    for (size_t s = 0; s < weights.size(); ++s)
    {
      if (weights[s] > 0)
      {
        comp_pos_map[i].push_back(s);
      }
    }

    LOG_DEBUG << "Partition #" << i << ": " << comp_pos_map[i].size() << endl;

    /* add compressed partition length to the */
    part_sizes.assign_sites(i, 0, comp_pos_map[i].size(),
                            instance.parted_msa->model(i).clv_entry_size());
    ++i;
  }

  instance.proc_part_assign =
      instance.load_balancer->get_all_assignments(part_sizes, ParallelContext::num_procs());

  LOG_VERB_TS << "Data distribution: " << PartitionAssignmentStats(instance.proc_part_assign) << endl;
  LOG_DEBUG << endl << instance.proc_part_assign;

  // translate partition range coordinates: compressed -> uncompressed
  for (auto& part_assign: instance.proc_part_assign)
  {
    for (auto& part_range: part_assign)
    {
      const auto& pos_map = comp_pos_map[part_range.part_id];
      const auto comp_start = part_range.start;
      const auto comp_end = comp_start + part_range.length - 1;

      part_range.start = (comp_start > 0) ? pos_map[comp_start] : 0;
      part_range.length = pos_map[comp_end] - part_range.start + 1;
    }
  }

//  LOG_VERB_TS << "(uncompressed) Data distribution: " << PartitionAssignmentStats(instance.proc_part_assign) << endl;
//  LOG_DEBUG << endl << instance.proc_part_assign;
}

void generate_bootstraps(RaxmlInstance& instance, const Checkpoint& checkp)
{
  if (instance.opts.command == Command::bootstrap || instance.opts.command == Command::all)
  {
    /* generate replicate alignments */
    BootstrapGenerator bg;
    for (size_t b = 0; b < instance.opts.num_bootstraps; ++b)
    {
      auto seed = rand();

      /* check if this BS was already computed in the previous run and saved in checkpoint */
      if (b < checkp.bs_trees.size())
        continue;

      instance.bs_reps.emplace_back(bg.generate(*instance.parted_msa, seed));
    }

    /* generate starting trees for bootstrap searches */
    for (size_t b = 0; b < instance.opts.num_bootstraps; ++b)
    {
      auto tree = generate_tree(instance, StartingTree::random);

      if (b < checkp.bs_trees.size())
        continue;

      instance.bs_start_trees.emplace_back(move(tree));
    }
  }
}

void reroot_tree_with_outgroup(const Options& opts, Tree& tree, bool add_root_node)
{
  if (!opts.outgroup_taxa.empty())
  {
    try
    {
      tree.reroot(opts.outgroup_taxa, add_root_node);
    }
    catch (std::runtime_error& e)
    {
      if (pll_errno == PLLMOD_TREE_ERROR_POLYPHYL_OUTGROUP)
        LOG_WARN << "WARNING: " << e.what() << endl << endl;
      else
        throw e;
    }
  }
}

void postprocess_tree(const Options& opts, Tree& tree)
{
  reroot_tree_with_outgroup(opts, tree, true);
  // TODO: collapse short branches
  // TODO: regraft previously removed duplicate seqs etc.
}

void draw_bootstrap_support(RaxmlInstance& instance, Tree& ref_tree, const TreeCollection& bs_trees)
{
  reroot_tree_with_outgroup(instance.opts, ref_tree, false);

  instance.bs_tree.reset(new BootstrapTree(ref_tree));

  Tree tree = ref_tree;
  for (auto bs: bs_trees)
  {
    tree.topology(bs.second);
    instance.bs_tree->add_bootstrap_tree(tree);
  }
  instance.bs_tree->calc_support();
}

bool check_bootstop(const RaxmlInstance& instance, const TreeCollection& bs_trees,
                    bool print = false)
{
  if (!instance.bootstop_checker)
    return false;

  const auto& opts       = instance.opts;
  auto& bootstop_checker = instance.bootstop_checker;

  if (!bootstop_checker->max_bs_trees())
    bootstop_checker->max_bs_trees(bs_trees.size());

  if (print)
  {
    LOG_INFO << "Performing bootstrap convergence assessment using autoMRE criterion"
             << endl << endl;

    // # Trees     Avg WRF in %    # Perms: wrf <= 2.00 %
    LOG_INFO << " # trees       "
             << " avg WRF      "
             << " avg WRF in %      "
             << " # perms: wrf <= " << setprecision(2) << opts.bootstop_cutoff * 100 << " %    "
             << " converged?  " << endl;
  }

  assert(!instance.random_tree.empty());

  Tree bs_tree = instance.random_tree;
  size_t bs_num = 0;
  bool converged = false;
  for (auto it: bs_trees)
  {
    bs_tree.topology(it.second);

    bootstop_checker->add_bootstrap_tree(bs_tree);

    bs_num++;

    if (bs_num % opts.bootstop_interval == 0 || bs_num == bs_trees.size())
    {
      converged = bootstop_checker->converged(rand());

      if (print)
      {
        LOG_INFO << setw(8) << bs_num << " "
                 << setw(14) << setprecision(3) << bootstop_checker->avg_wrf() << "   "
                 << setw(16) << setprecision(3) << bootstop_checker->avg_pct() << "   "
                 << setw(26) << bootstop_checker->num_better() << "        "
                 << (converged ? "YES" : "NO") << endl;
      }

      if (converged)
        break;
    }
  }

  if (print)
  {
    LOG_INFO << "Bootstopping test " << (converged ? "converged" : "did not converge")
             << " after " <<  bootstop_checker->num_bs_trees() << " trees" << endl << endl;
  }

  return converged;
}

TreeCollection read_bootstrap_trees(const RaxmlInstance& instance, Tree& ref_tree)
{
  NameIdMap ref_tip_ids;
  const auto& opts = instance.opts;
 NewickStream boots(opts.bootstrap_trees_file(), std::ios::in);
  TreeCollection bs_trees;
  unsigned int bs_num = 0;

  LOG_INFO << "Reading bootstrap trees from file: " << opts.bootstrap_trees_file() << endl;

  while (boots.peek() != EOF)
  {
    Tree tree;
    boots >> tree;

    if (bs_trees.empty())
    {
      if (ref_tree.empty())
        ref_tree = tree;
      ref_tip_ids = ref_tree.tip_ids();
    }

    assert(!ref_tip_ids.empty());

    try
    {
      tree.reset_tip_ids(ref_tip_ids);
    }
    catch (out_of_range& e)
    {
      throw runtime_error("Bootstrap tree #" + to_string(bs_num+1) +
                          " contains incompatible taxon name(s)!");
    }
    catch (invalid_argument& e)
    {
      throw runtime_error("Bootstrap tree #" + to_string(bs_num+1) +
                          " has wrong number of tips: " + to_string(tree.num_tips()));
    }
    bs_trees.push_back(0, tree);
    bs_num++;
  }

  LOG_INFO << "Bootstrap trees found: " << bs_trees.size() << endl << endl;

  if (bs_trees.size() < 2)
  {
    throw runtime_error("You must provide a file with multiple bootstrap trees!");
  }

  return bs_trees;
}

void command_bootstop(RaxmlInstance& instance)
{
  auto bs_trees = read_bootstrap_trees(instance, instance.random_tree);

  check_bootstop(instance, bs_trees, true);
}

void command_support(RaxmlInstance& instance)
{
  const auto& opts = instance.opts;

  LOG_INFO << "Reading reference tree from file: " << opts.tree_file << endl;

  if (!sysutil_file_exists(opts.tree_file))
    throw runtime_error("File not found: " + opts.tree_file);

  Tree ref_tree;
  NewickStream refs(opts.tree_file, std::ios::in);
  refs >> ref_tree;

  LOG_INFO << "Reference tree size: " << to_string(ref_tree.num_tips()) << endl << endl;

  /* read all bootstrap trees from a Newick file */
  auto bs_trees = read_bootstrap_trees(instance, ref_tree);

  draw_bootstrap_support(instance, ref_tree, bs_trees);
  check_bootstop(instance, bs_trees, true);
}

void check_terrace(const RaxmlInstance& instance, const Tree& tree)
{
#ifdef _RAXML_TERRAPHAST
  const auto& parted_msa = *instance.parted_msa;

  if (parted_msa.part_count() > 1)
  {
    try
    {
      TerraceWrapper terrace_wrapper(parted_msa, tree);
      auto terrace_size = terrace_wrapper.terrace_size();
      if (terrace_size > 1)
      {
        LOG_WARN << "WARNING: Best-found ML tree lies on a terrace of size: "
                 << terrace_size << endl << endl;

        if (!instance.opts.terrace_file().empty())
        {
          ofstream fs(instance.opts.terrace_file());
          terrace_wrapper.print_terrace(fs);
          LOG_INFO << "Tree terrace (in compressed Newick format) was saved to: "
              << sysutil_realpath(instance.opts.terrace_file()) << endl << endl;

          // TODO partial prints to multiline newick?
          // if (terrace_size <= instance.opts.terrace_maxsize)
        }
      }
      else
      {
        LOG_INFO << "NOTE: Tree does not lie on a phylogenetic terrace." << endl << endl;
      }
    }
    catch (terraces::no_usable_root_error& e)
    {
      if (instance.opts.command == Command::terrace)
      {
        LOG_ERROR << "ERROR: Cannot check for phylogenetic terraces "
            "since no comprehensive taxon is found." << endl << endl;
      }
      else
      {
        LOG_VERB << "NOTE: Cannot check for phylogenetic terraces "
            "since no comprehensive taxon is found." << endl << endl;
      }
    }
    catch (std::runtime_error& e)
    {
      LOG_ERROR << "ERROR: Unexpected terraphast error: " << e.what() << endl << endl;
    }
  }
#else
  RAXML_UNUSED(instance);
  RAXML_UNUSED(tree);
#endif
}

void save_ml_trees(const Options& opts, const Checkpoint& checkp)
{
  NewickStream nw(opts.ml_trees_file(), std::ios::out);
  for (auto topol: checkp.ml_trees)
  {
    Tree ml_tree = checkp.tree;
    ml_tree.topology(topol.second);
    postprocess_tree(opts, ml_tree);
    nw << ml_tree;
  }
}

void print_final_output(const RaxmlInstance& instance, const Checkpoint& checkp)
{
  auto const& opts = instance.opts;
  const auto& parted_msa = *instance.parted_msa;

  if (opts.command == Command::search || opts.command == Command::all ||
      opts.command == Command::evaluate || opts.command == Command::bootstrap)
  {
    auto model_log_lvl = parted_msa.part_count() > 1 ? LogLevel::verbose : LogLevel::info;

    RAXML_LOG(model_log_lvl) << "\nOptimized model parameters:" << endl;

    for (size_t p = 0; p < parted_msa.part_count(); ++p)
    {
      RAXML_LOG(model_log_lvl) << "\n   Partition " << p << ": " <<
          parted_msa.part_info(p).name().c_str() << endl;
      RAXML_LOG(model_log_lvl) << checkp.models.at(p);
    }
  }

  if (opts.command == Command::evaluate)
  {
    if (!opts.ml_trees_file().empty())
    {
      save_ml_trees(opts, checkp);

      LOG_INFO << "\nAll optimized tree(s) saved to: " << sysutil_realpath(opts.ml_trees_file()) << endl;
    }
  }

  if (opts.command == Command::search || opts.command == Command::all)
  {
    auto best = checkp.ml_trees.best();

    LOG_INFO << "\nFinal LogLikelihood: " << FMT_LH(best->first) << endl << endl;

    Tree best_tree = checkp.tree;

    best_tree.topology(best->second);

    check_terrace(instance, best_tree);

    postprocess_tree(opts, best_tree);

//    pll_utree_show_ascii(&best_tree.pll_utree_root(),
//                         PLL_UTREE_SHOW_LABEL | PLL_UTREE_SHOW_BRANCH_LENGTH | PLL_UTREE_SHOW_CLV_INDEX );
//    printf("\n\n");

    if (checkp.ml_trees.size() > 1 && !opts.ml_trees_file().empty())
    {
      save_ml_trees(opts, checkp);

      LOG_INFO << "All ML trees saved to: " << sysutil_realpath(opts.ml_trees_file()) << endl;
    }

    if (!opts.best_tree_file().empty())
    {
      NewickStream nw_result(opts.best_tree_file());
      nw_result << best_tree;

      LOG_INFO << "Best ML tree saved to: " << sysutil_realpath(opts.best_tree_file()) << endl;
    }

    if (opts.brlen_linkage == PLLMOD_COMMON_BRLEN_UNLINKED && !opts.partition_trees_file().empty())
    {
      NewickStream nw_result(opts.partition_trees_file());

      for (size_t p = 0; p < parted_msa.part_count(); ++p)
      {
        best_tree.apply_partition_brlens(p);
        nw_result << best_tree;
      }

      LOG_INFO << "Best per-partition ML trees saved to: " <<
          sysutil_realpath(opts.partition_trees_file()) << endl;
    }
  }

  if (opts.command == Command::all || opts.command == Command::support)
  {
    assert(instance.bs_tree);

    postprocess_tree(instance.opts, *instance.bs_tree);

    if (!opts.support_tree_file().empty())
    {
      NewickStream nw(opts.support_tree_file(), std::ios::out);
      nw << *instance.bs_tree;

      LOG_INFO << "Best ML tree with bootstrap support values saved to: " <<
          sysutil_realpath(opts.support_tree_file()) << endl;
    }
  }

  if (opts.command == Command::search || opts.command == Command::all ||
      opts.command == Command::evaluate)
  {
    if (!opts.best_model_file().empty())
    {
      RaxmlPartitionStream model_stream(opts.best_model_file(), true);
      model_stream.print_model_params(true);
      model_stream << fixed << setprecision(logger().precision(LogElement::model));
      model_stream << parted_msa;

      LOG_INFO << "Optimized model saved to: " << sysutil_realpath(opts.best_model_file()) << endl;
    }
  }

  if (opts.command == Command::bootstrap || opts.command == Command::all)
  {
    // TODO now only master process writes the output, this will have to change with
    // coarse-grained parallelization scheme (parallel start trees/bootstraps)
    if (!opts.bootstrap_trees_file().empty())
    {
  //    NewickStream nw(opts.bootstrap_trees_file(), std::ios::out | std::ios::app);
      NewickStream nw(opts.bootstrap_trees_file(), std::ios::out);

      for (auto topol: checkp.bs_trees)
      {
        Tree bs_tree = checkp.tree;
        bs_tree.topology(topol.second);
        postprocess_tree(opts, bs_tree);
        nw << bs_tree;
      }

      LOG_INFO << "Bootstrap trees saved to: " << sysutil_realpath(opts.bootstrap_trees_file()) << endl;
    }
  }

  if (!opts.log_file().empty())
      LOG_INFO << "\nExecution log saved to: " << sysutil_realpath(opts.log_file()) << endl;

  LOG_INFO << "\nAnalysis started: " << global_timer().start_time();
  LOG_INFO << " / finished: " << global_timer().current_time() << std::endl;
  LOG_INFO << "\nElapsed time: " << FMT_PREC3(global_timer().elapsed_seconds()) << " seconds";
  if (checkp.elapsed_seconds > 0.)
  {
    LOG_INFO << " (this run) / ";
    LOG_INFO << FMT_PREC3(checkp.elapsed_seconds + global_timer().elapsed_seconds()) <<
        " seconds (total with restarts)";
  }

  LOG_INFO << endl << endl;
}

void print_resources(const RaxmlInstance& instance)
{
  StaticResourceEstimator resEstimator(*instance.parted_msa, instance.opts);
  auto res = resEstimator.estimate();

  LOG_VERB << "* Per-taxon CLV size (elements)                : "
      << res.taxon_clv_size << endl;
  LOG_INFO << "* Estimated memory requirements                : " <<
      (size_t) (((float) res.total_mem_size) / (1024 * 1024) + 1) << " MB" << endl << endl;
  LOG_INFO << "* Recommended number of threads / MPI processes: "
           << res.num_threads_balanced << endl;
  LOG_VERB << "* Maximum     number of threads / MPI processes: "
           << res.num_threads_response << endl;
  LOG_VERB << "* Minimum     number of threads / MPI processes: "
           << res.num_threads_throughput << endl;

  LOG_INFO << endl << "Please note that numbers given above are rough estimates only. " << endl <<
      "Actual memory consumption and parallel performance on your system may differ!"
      << endl << endl;
}

void thread_main(RaxmlInstance& instance, CheckpointManager& cm)
{
  unique_ptr<TreeInfo> treeinfo;

//  printf("thread %lu / %lu\n", ParallelContext::thread_id(), ParallelContext::num_procs());

  /* wait until master thread prepares all global data */
  ParallelContext::thread_barrier();

  auto const& master_msa = *instance.parted_msa;
  auto const& opts = instance.opts;

  /* get partitions assigned to the current thread */
  auto const& part_assign = instance.proc_part_assign.at(ParallelContext::proc_id());

  bool use_ckp_tree = true;
  if ((opts.command == Command::search || opts.command == Command::all ||
      opts.command == Command::evaluate ) && !instance.start_trees.empty())
  {

    if (opts.command == Command::evaluate)
    {
      LOG_INFO << "\nEvaluating " << opts.num_searches <<
          " trees" << endl << endl;
    }
    else
    {
      LOG_INFO << "\nStarting ML tree search with " << opts.num_searches <<
          " distinct starting trees" << endl << endl;
    }

    size_t start_tree_num = cm.checkpoint().ml_trees.size();
    use_ckp_tree = use_ckp_tree && cm.checkpoint().search_state.step != CheckpointStep::start;
    for (const auto& tree: instance.start_trees)
    {
      assert(!tree.empty());

      start_tree_num++;

      if (use_ckp_tree)
      {
        // restore search state from checkpoint (tree + model params)
        treeinfo.reset(new TreeInfo(opts, cm.checkpoint().tree, master_msa,
                                    instance.tip_msa_idmap, part_assign));
        assign_models(*treeinfo, cm.checkpoint());
        use_ckp_tree = false;
      }
      else
      {
        treeinfo.reset(new TreeInfo(opts, tree, master_msa, instance.tip_msa_idmap, part_assign));
      }

      treeinfo->set_topology_constraint(instance.constraint_tree);

      Optimizer optimizer(opts);
      if (opts.command == Command::evaluate)
      {
        // check if we have anything to ooptimize
        LOG_INFO_TS << "Tree #" << start_tree_num <<
            ", initial LogLikelihood: " << FMT_LH(treeinfo->loglh()) << endl;
        if (opts.optimize_brlen || opts.optimize_brlen)
        {
          LOG_PROGR << endl;
          optimizer.evaluate(*treeinfo, cm);
          LOG_PROGR << endl;
          LOG_INFO_TS << "Tree #" << start_tree_num <<
              ", final logLikelihood: " << FMT_LH(cm.checkpoint().loglh()) << endl;
          LOG_PROGR << endl;
        }
      }
      else
      {
        optimizer.optimize_topology(*treeinfo, cm);
        LOG_PROGR << endl;
        LOG_INFO_TS << "ML tree search #" << start_tree_num <<
            ", logLikelihood: " << FMT_LH(cm.checkpoint().loglh()) << endl;
        LOG_PROGR << endl;
      }

      cm.save_ml_tree();
      cm.reset_search_state();
    }
  }

  ParallelContext::thread_barrier();

  if (!instance.bs_reps.empty())
  {
    if (opts.command == Command::all)
    {
      LOG_INFO << endl;
      LOG_INFO_TS << "ML tree search completed, best tree logLH: " <<
          FMT_LH(cm.checkpoint().ml_trees.best_score()) << endl << endl;
    }

    LOG_INFO_TS << "Starting bootstrapping analysis with " << opts.num_bootstraps
             << " replicates." << endl << endl;
  }

  /* infer bootstrap trees if needed */
  size_t bs_num = cm.checkpoint().bs_trees.size();
  auto bs_start_tree = instance.bs_start_trees.cbegin();
  use_ckp_tree = use_ckp_tree && cm.checkpoint().search_state.step != CheckpointStep::start;
  bool bs_converged = false;
  for (const auto& bs: instance.bs_reps)
  {
    ++bs_num;

    // rebalance sites
    if (ParallelContext::master_thread())
    {
      balance_load(instance, bs.site_weights);
    }
    ParallelContext::thread_barrier();

    auto const& bs_part_assign = instance.proc_part_assign.at(ParallelContext::proc_id());

    if (use_ckp_tree)
    {
      // restore search state from checkpoint (tree + model params)
      treeinfo.reset(new TreeInfo(opts, cm.checkpoint().tree, master_msa, instance.tip_msa_idmap,
                                  bs_part_assign, bs.site_weights));
      assign_models(*treeinfo, cm.checkpoint());
      use_ckp_tree = false;
    }
    else
    {
      treeinfo.reset(new TreeInfo(opts, *bs_start_tree, master_msa, instance.tip_msa_idmap,
                                  bs_part_assign, bs.site_weights));
    }

    treeinfo->set_topology_constraint(instance.constraint_tree);

//    size_t sumw = 0;
//    for (auto sw: bs.site_weights)
//      for (auto w: sw)
//      {
//        sumw += w;
//        LOG_INFO << w << "  ";
//      }
//
//    LOG_INFO << "\n\nTotal BS sites: " << sumw << endl;

    Optimizer optimizer(opts);
    optimizer.optimize_topology(*treeinfo, cm);

    LOG_PROGR << endl;
    LOG_INFO_TS << "Bootstrap tree #" << bs_num <<
                ", logLikelihood: " << FMT_LH(cm.checkpoint().loglh()) << endl;
    LOG_PROGR << endl;

    cm.save_bs_tree();
    cm.reset_search_state();
    ++bs_start_tree;

    /* check bootstrapping convergence */
    if (instance.bootstop_checker && ParallelContext::master_thread())
    {
      instance.bootstop_checker->add_bootstrap_tree(cm.checkpoint().tree);

      if (bs_num % opts.bootstop_interval == 0 || bs_num == opts.num_bootstraps)
      {
        bs_converged = instance.bootstop_checker->converged(rand());
      }
    }
    ParallelContext::thread_broadcast(0, &bs_converged, sizeof(bool));
    if (bs_converged)
    {
      LOG_INFO_TS << "Bootstrapping converged after " << bs_num << " replicates." << endl;
      bs_start_tree = instance.bs_start_trees.cend();
      break;
    }
  }

  assert(bs_start_tree == instance.bs_start_trees.cend());

  ParallelContext::thread_barrier();
}

void master_main(RaxmlInstance& instance, CheckpointManager& cm)
{
  auto const& opts = instance.opts;

  /* if resuming from a checkpoint, use binary MSA (if exists) */
  if (!instance.opts.redo_mode &&
      sysutil_file_exists(instance.opts.checkp_file()) &&
      sysutil_file_exists(instance.opts.binary_msa_file()) &&
      RBAStream::rba_file(instance.opts.binary_msa_file(), true))
  {
    instance.opts.msa_file = instance.opts.binary_msa_file();
  }

  load_parted_msa(instance);
  assert(instance.parted_msa);
  auto& parted_msa = *instance.parted_msa;

  load_constraint(instance);

  check_options(instance);

  // temp workaround: since MSA pattern compression calls rand(), it will change all random
  // numbers generated afterwards. so just reset seed to the initial value to ensure that
  // starting trees, BS replicates etc. are the same regardless whether pat.comp is ON or OFF
  srand(opts.random_seed);

  // we need 2 doubles for each partition AND threads to perform parallel reduction,
  // so resize the buffer accordingly
  const size_t reduce_buffer_size = std::max(1024lu, 2 * sizeof(double) *
                                     parted_msa.part_count() * ParallelContext::num_threads());
  LOG_DEBUG << "Parallel reduction buffer size: " << reduce_buffer_size/1024 << " KB\n\n";
  ParallelContext::resize_buffer(reduce_buffer_size);

  /* init template tree */
  instance.random_tree = generate_tree(instance, StartingTree::random);

  /* load checkpoint */
  load_checkpoint(instance, cm);

  /* load/create starting tree if not already loaded from checkpoint */
  if (cm.checkpoint().ml_trees.size() + instance.start_trees.size() < instance.opts.num_searches)
  {
    if (ParallelContext::master_rank() || !instance.opts.constraint_tree_file.empty())
    {
      /* only master MPI rank generates starting trees (doesn't work with constrainted search) */
      build_start_trees(instance, cm.checkpoint().ml_trees.size());
      ParallelContext::mpi_barrier();
    }
    else
    {
      /* non-master ranks load starting trees from a file */
      ParallelContext::mpi_barrier();
      load_start_trees(instance, cm);
    }
  }

  LOG_VERB << endl << "Initial model parameters:" << endl;
  for (size_t p = 0; p < parted_msa.part_count(); ++p)
  {
    LOG_VERB << "   Partition: " << parted_msa.part_info(p).name() << endl <<
        parted_msa.model(p) << endl;
  }

  /* run load balancing algorithm */
  balance_load(instance);

  // TEMP WORKAROUND: here we reset random seed once again to make sure that BS replicates
  // are not affected by the number of ML search starting trees that has been generated before
  srand(instance.opts.random_seed);

  /* generate bootstrap replicates */
  generate_bootstraps(instance, cm.checkpoint());

  if (ParallelContext::master_rank())
    instance.opts.remove_result_files();

  thread_main(instance, cm);

  if (ParallelContext::master_rank())
  {
    if (opts.command == Command::all)
    {
      auto& checkp = cm.checkpoint();
      Tree tree = checkp.tree;
      tree.topology(checkp.ml_trees.best_topology());

      draw_bootstrap_support(instance, tree, checkp.bs_trees);
    }

    assert(cm.checkpoint().models.size() == parted_msa.part_count());
    for (size_t p = 0; p < parted_msa.part_count(); ++p)
    {
      parted_msa.model(p, cm.checkpoint().models.at(p));
    }
  }
}

int clean_exit(int retval)
{
  ParallelContext::finalize(retval != EXIT_SUCCESS);
  return retval;
}

int internal_main(int argc, char** argv, void* comm)
{
  int retval = EXIT_SUCCESS;

  RaxmlInstance instance;
  auto& opts = instance.opts;

  ParallelContext::init_mpi(argc, argv, comm);

  opts.num_ranks = ParallelContext::num_ranks();

  logger().add_log_stream(&cout);

  CommandLineParser cmdline;
  try
  {
    cmdline.parse_options(argc, argv, opts);
  }
  catch (OptionException &e)
  {
    LOG_INFO << "ERROR: " << e.message() << std::endl;
    return clean_exit(EXIT_FAILURE);
  }

  /* handle trivial commands first */
  switch (opts.command)
  {
    case Command::help:
      print_banner();
      cmdline.print_help();
      return clean_exit(EXIT_SUCCESS);
      break;
    case Command::version:
      print_banner();
      return clean_exit(EXIT_SUCCESS);
      break;
    case Command::evaluate:
    case Command::search:
    case Command::bootstrap:
    case Command::all:
    case Command::support:
    case Command::start:
    case Command::terrace:
      if (!opts.redo_mode && opts.result_files_exist())
      {
        LOG_ERROR << endl << "ERROR: Result files for the run with prefix `" <<
                            (opts.outfile_prefix.empty() ? opts.msa_file : opts.outfile_prefix) <<
                            "` already exist!\n" <<
                            "Please either choose a new prefix, remove old files, or add "
                            "--redo command line switch to overwrite them." << endl << endl;
        return clean_exit(EXIT_FAILURE);
      }
      break;
    case Command::bsconverge:
    default:
      break;
  }

  /* now get to the real stuff */
  srand(opts.random_seed);
  logger().log_level(instance.opts.log_level);
  logger().precision(instance.opts.precision, LogElement::all);

  /* only master process writes the log file */
  if (ParallelContext::master() && !instance.opts.log_file().empty())
  {
    auto mode = !instance.opts.redo_mode && sysutil_file_exists(instance.opts.checkp_file()) ?
        ios::app : ios::out;
    logger().set_log_filename(opts.log_file(), mode);
  }

  print_banner();
  LOG_INFO << opts;

  try
  {
    if (!opts.constraint_tree_file.empty() &&
        (opts.start_trees.count(StartingTree::parsimony) > 0 ||
         opts.start_trees.count(StartingTree::user)))
    {
      throw runtime_error(string("") +
          " User and parsimony starting trees are not supported in combination with "
          "constrained tree inference.\n" +
          "       Please use random starting trees instead.");
    }

    if (opts.redo_mode)
    {
      LOG_WARN << "WARNING: Running in REDO mode: existing checkpoints are ignored, "
          "and all result files will be overwritten!" << endl << endl;
    }

    if (opts.force_mode)
    {
      LOG_WARN << "WARNING: Running in FORCE mode: all safety checks are disabled!"
          << endl << endl;
    }

    /* init bootstopping */
    switch (opts.bootstop_criterion)
    {
      case BootstopCriterion::autoMRE:
        instance.bootstop_checker.reset(new BootstopCheckMRE(opts.num_bootstraps,
                                                             opts.bootstop_cutoff,
                                                             opts.bootstop_permutations));
        break;
      case BootstopCriterion::none:
        break;
      default:
        throw runtime_error("Only autoMRE bootstopping criterion is supported for now, sorry!");
    }

    CheckpointManager cm(opts.checkp_file());

    switch (opts.command)
    {
      case Command::evaluate:
      case Command::search:
      case Command::bootstrap:
      case Command::all:
      {
        /* init load balancer */
        switch(opts.load_balance_method)
        {
          case LoadBalancing::naive:
            instance.load_balancer.reset(new SimpleLoadBalancer());
            break;
          case LoadBalancing::kassian:
            instance.load_balancer.reset(new KassianLoadBalancer());
            break;
          case LoadBalancing::benoit:
            instance.load_balancer.reset(new BenoitLoadBalancer());
            break;
          default:
            assert(0);
        }

        ParallelContext::init_pthreads(opts, std::bind(thread_main,
                                                       std::ref(instance),
                                                       std::ref(cm)));

        master_main(instance, cm);
        break;
      }
      case Command::support:
        command_support(instance);
        break;
      case Command::bsconverge:
        command_bootstop(instance);
        break;
#ifdef _RAXML_TERRAPHAST
      case Command::terrace:
      {
        load_parted_msa(instance);
        assert(!opts.tree_file.empty());
        LOG_INFO << "Loading tree from: " << opts.tree_file << endl << endl;
        if (!sysutil_file_exists(opts.tree_file))
          throw runtime_error("File not found: " + opts.tree_file);
        instance.start_tree_stream.reset(new NewickStream(opts.tree_file, std::ios::in));
        Tree tree = generate_tree(instance, StartingTree::user);
        check_terrace(instance, tree);
        break;
      }
#endif
      case Command::check:
        opts.use_pattern_compression = false;
      case Command::parse:
      {
        load_parted_msa(instance);
        if (!opts.tree_file.empty())
        {
          LOG_INFO << "Loading tree from: " << opts.tree_file << endl << endl;
          if (!sysutil_file_exists(opts.tree_file))
            throw runtime_error("File not found: " + opts.tree_file);
          instance.start_tree_stream.reset(new NewickStream(opts.tree_file, std::ios::in));
          Tree tree = generate_tree(instance, StartingTree::user);
        }
        if (opts.command == Command::parse)
          print_resources(instance);

        LOG_INFO << "Alignment can be successfully read by RAxML-NG." << endl << endl;
        break;
      }
      case Command::start:
      {
        load_parted_msa(instance);
        build_start_trees(instance, 0);
        if (!opts.start_tree_file().empty())
        {
          LOG_INFO << "\nAll starting trees saved to: " <<
              sysutil_realpath(opts.start_tree_file()) << endl << endl;
        }
        else
        {
          LOG_INFO << "\nStarting trees have been successfully generated." << endl << endl;
        }
        break;
      }
      case Command::none:
      default:
        LOG_ERROR << "Unknown command!" << endl;
        retval = EXIT_FAILURE;
    }

    /* finalize */
    if (ParallelContext::master_rank())
    {
      print_final_output(instance, cm.checkpoint());

      /* analysis finished successfully, remove checkpoint file */
      cm.remove();
    }
  }
  catch(exception& e)
  {
    LOG_ERROR << endl << "ERROR: " << e.what() << endl << endl;
    retval = EXIT_FAILURE;
  }

  return clean_exit(retval);
}


#ifdef _RAXML_BUILD_AS_LIB

extern "C" int dll_main(int argc, char** argv, void* comm)
{
  return internal_main(argc, argv, comm);
}

#else

int main(int argc, char** argv)
{
  return internal_main(argc, argv, 0);
}

#endif
