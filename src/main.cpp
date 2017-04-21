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
#include "TreeInfo.hpp"
#include "io/file_io.hpp"
#include "io/binary_io.hpp"
#include "ParallelContext.hpp"
#include "LoadBalancer.hpp"
#include "bootstrap/BootstrapGenerator.hpp"

using namespace std;

typedef vector<Tree> TreeList;
struct RaxmlInstance
{
  Options opts;
  PartitionedMSA parted_msa;
  TreeList start_trees;
  BootstrapReplicateList bs_reps;
  PartitionAssignmentList proc_part_assign;
  unique_ptr<LoadBalancer> load_balancer;
  unique_ptr<BootstrapTree> bs_tree;

  unique_ptr<NewickStream> start_tree_stream;

  /* this is just a dummy random tree used for convenience, e,g, if we need tip labels or
   * just 'any' valid tree for the alignment at hand */
  Tree random_tree;
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
  auto& parted_msa = instance.parted_msa;

  /* check if model is a file */
  if (sysutil_file_exists(opts.model_file))
  {
    // read partition definitions from file
    RaxmlPartitionStream partfile(opts.model_file, ios::in);
    partfile >> parted_msa;

//    DBG("partitions found: %d\n", useropt->part_count);
  }
  else
  {
    // create and init single pseudo-partition
    parted_msa.emplace_part_info("noname", opts.data_type, opts.model_file);
  }

  /* make sure that linked branch length mode is set for unpartitioned alignments */
  if (parted_msa.part_count() == 1)
    opts.brlen_linkage = PLLMOD_TREE_BRLEN_LINKED;

  int lg4x_count = 0;

  for (const auto& pinfo: parted_msa.part_list())
  {
//    LOG_INFO << "|" << pinfo.name() << "|   |" << pinfo.model().to_string() << "|   |" <<
//        pinfo.range_string() << "|" << endl;

    if (pinfo.model().name() == "LG4X")
      lg4x_count++;
  }

  if (parted_msa.part_count() > 1 && lg4x_count > 0 && opts.brlen_linkage == PLLMOD_TREE_BRLEN_LINKED)
  {
    throw runtime_error("LG4X model is not supported in linked branch length mode, sorry :(");
  }
}

void check_msa(RaxmlInstance& instance)
{
  LOG_VERB_TS << "Checking the alignment...\n";

  const auto& full_msa = instance.parted_msa.full_msa();
  const auto pll_msa = full_msa.pll_msa();

  unsigned long stats_mask = PLLMOD_MSA_STATS_DUP_TAXA | PLLMOD_MSA_STATS_DUP_SEQS;

  pllmod_msa_stats_t * stats = pllmod_msa_compute_stats(pll_msa,
                                                        4,
                                                        pll_map_nt, // map is not used here
                                                        NULL,
                                                        stats_mask);

  if (!stats)
    throw runtime_error(pll_errmsg);

  if (stats->dup_taxa_pairs_count > 0)
  {
    LOG_ERROR << "\nERROR: Duplicate sequence names found: " << stats->dup_taxa_pairs_count << endl;
    for (unsigned long c = 0; c < stats->dup_taxa_pairs_count; ++c)
    {
      const unsigned long idx1 = stats->dup_taxa_pairs[c*2];
      const unsigned long idx2 = stats->dup_taxa_pairs[c*2+1];
      LOG_ERROR << "ERROR: Sequences " << idx1 << " and " << idx2 << " have identical name: " <<
          pll_msa->label[idx1] << endl;
    }
    throw runtime_error("Please fix your alignment!");
  }

  if (stats->dup_seqs_pairs_count > 0)
  {
    LOG_WARN << "\nWARNING: Duplicate sequences found: " << stats->dup_seqs_pairs_count << endl;
    for (unsigned long c = 0; c < stats->dup_seqs_pairs_count; ++c)
    {
      const unsigned long idx1 = stats->dup_seqs_pairs[c*2];
      const unsigned long idx2 = stats->dup_seqs_pairs[c*2+1];
      LOG_WARN << "WARNING: Sequences " << pll_msa->label[idx1] << " and " <<
          pll_msa->label[idx2] << " are exactly identical!" << endl;
    }
  }

  pllmod_msa_destroy_stats(stats);

  std::set<size_t> gap_seqs;
  size_t total_gap_cols = 0;
  size_t part_num = 0;
  for (auto& pinfo: instance.parted_msa.part_list())
  {
    stats_mask = PLLMOD_MSA_STATS_GAP_SEQS | PLLMOD_MSA_STATS_GAP_COLS;

    pllmod_msa_stats_t * stats = pinfo.compute_stats(stats_mask);

    if (stats->gap_cols_count > 0)
    {
      total_gap_cols += stats->gap_cols_count;
      std::vector<size_t> gap_cols(stats->gap_cols, stats->gap_cols + stats->gap_cols_count);
      pinfo.msa().remove_sites(gap_cols);
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
//    for (unsigned long c = 0; c < stats->gap_cols_count; ++c)
//      LOG_VERB << "WARNING: Column " << stats->gap_cols[c]+1 << " contains only gaps!" << endl;
  }

  if (!gap_seqs.empty())
  {
   LOG_WARN << "\nWARNING: Fully undetermined sequences found: " << gap_seqs.size() << endl;
   for (auto c : gap_seqs)
     LOG_VERB << "WARNING: Sequence " << c << " " << pll_msa->label[c] << " contains only gaps!" << endl;
  }


  if (total_gap_cols > 0 || !gap_seqs.empty() > 0)
  {
    // save reduced MSA and partition files
    auto reduced_msa_fname = instance.opts.output_fname("reduced.phy");
    PhylipStream ps(reduced_msa_fname);

    ps << instance.parted_msa;

    LOG_INFO << "\nNOTE: Reduced alignment (with gap-only columns removed) was printed to:\n";
    LOG_INFO << sysutil_realpath(reduced_msa_fname) << endl;

    // save reduced partition file
    if (sysutil_file_exists(instance.opts.model_file))
    {
      auto reduced_part_fname = instance.opts.output_fname("reduced.partition");
      RaxmlPartitionStream ps(reduced_part_fname, ios::out);

      ps << instance.parted_msa;

      LOG_INFO << "\nNOTE: The corresponding reduced partition file was printed to:\n";
      LOG_INFO << sysutil_realpath(reduced_part_fname) << endl;
    }
  }

}

void load_msa(RaxmlInstance& instance)
{
  const auto& opts = instance.opts;
  auto& parted_msa = instance.parted_msa;

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
  check_msa(instance);

  if (opts.use_pattern_compression)
    parted_msa.compress_patterns();

  parted_msa.set_model_empirical_params();

  LOG_INFO << endl;

  LOG_INFO << "Alignment comprises " << parted_msa.part_count() << " partitions and " <<
      parted_msa.total_length() << " patterns\n" << endl;

  LOG_INFO << parted_msa;

  LOG_INFO << endl;
}

Tree generate_tree(const RaxmlInstance& instance, StartingTree type)
{
  Tree tree;

  const auto& opts = instance.opts;
  const auto& parted_msa = instance.parted_msa;
  const auto& msa = parted_msa.full_msa();

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

      if (msa.size() > tree.num_tips())
        sysutil_fatal("Alignment file contains more sequences than expected");
      else if (msa.size() != tree.num_tips())
        sysutil_fatal("Some taxa are missing from the alignment file");

      break;
    }
    case StartingTree::random:
      /* no starting tree provided, generate a random one */

      LOG_DEBUG << "Generating a random starting tree with " << msa.size() << " taxa" << endl;

      tree = Tree::buildRandom(msa);

      break;
    case StartingTree::parsimony:
    {
      LOG_DEBUG << "Generating a parsimony starting tree with " << msa.size() << " taxa" << endl;

      unsigned int score;
      tree = Tree::buildParsimony(parted_msa, rand(), opts.simd_arch, &score);

      LOG_DEBUG << "Parsimony score of the starting tree: " << score << endl;

      break;
    }
    default:
      sysutil_fatal("Unknown starting tree type: %d\n", opts.start_tree);
  }

  assert(!tree.empty());

  return tree;
}

void load_checkpoint(RaxmlInstance& instance, CheckpointManager& cm)
{
  /* init checkpoint and set to the manager */
  {
    Checkpoint ckp;
    for (size_t p = 0; p < instance.parted_msa.part_count(); ++p)
      ckp.models[p] = instance.parted_msa.part_info(p).model();

    // this is a "template" tree, which provides tip labels and node ids
    ckp.tree = instance.random_tree;

    cm.checkpoint(move(ckp));
  }

  if (!instance.opts.redo_mode && cm.read())
  {
    const auto& ckp = cm.checkpoint();
    for (const auto& m: ckp.models)
      instance.parted_msa.model(m.first, m.second);

    LOG_INFO_TS << "NOTE: Resuming execution from checkpoint " <<
        "(logLH: " << ckp.loglh() <<
        ", ML trees: " << ckp.ml_trees.size() <<
        ", bootstraps: " << ckp.bs_trees.size() <<
        ")"
        << endl;
  }
}

void build_start_trees(RaxmlInstance& instance, CheckpointManager& cm)
{
  const auto& opts = instance.opts;
  const auto& parted_msa = instance.parted_msa;
  const auto& msa = parted_msa.full_msa();

  switch (opts.start_tree)
  {
    case StartingTree::user:
      LOG_INFO_TS << "Loading user starting tree(s) from: " << opts.tree_file << endl;
      if (!sysutil_file_exists(opts.tree_file))
        throw runtime_error("File not found: " + opts.tree_file);
      instance.start_tree_stream.reset(new NewickStream(opts.tree_file, std::ios::in));
      break;
    case StartingTree::random:
      LOG_INFO_TS << "Generating random starting tree(s) with " << msa.size() << " taxa" << endl;
      break;
    case StartingTree::parsimony:
      LOG_INFO_TS << "Generating parsimony starting tree(s) with " << msa.size() << " taxa" << endl;
      break;
    default:
      assert(0);
  }

  for (size_t i = 0; i < opts.num_searches; ++i)
  {
    auto tree = generate_tree(instance, opts.start_tree);

    // TODO use universal starting tree generator
    if (opts.start_tree == StartingTree::user)
    {
      if (instance.start_tree_stream->peek() != EOF)
        instance.opts.num_searches++;
    }

    // TODO: skip generation
    if (i < cm.checkpoint().ml_trees.size())
      continue;

    /* fix missing branch lengths */
    tree.fix_missing_brlens();

    /* make sure tip indices are consistent between MSA and pll_tree */
    tree.reset_tip_ids(msa.label_id_map());

    instance.start_trees.emplace_back(move(tree));
  }

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
  for (auto const& pinfo: instance.parted_msa.part_list())
  {
    part_sizes.assign_sites(i, 0, pinfo.msa().length());
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
    part_sizes.assign_sites(i, 0, comp_pos_map[i].size());
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
      part_range.start = comp_start > 0 ? pos_map[comp_start] : 0;
      part_range.length = pos_map[comp_start + part_range.length - 1] - part_range.start + 1;
    }
  }

//  LOG_VERB_TS << "(uncompressed) Data distribution: " << PartitionAssignmentStats(instance.proc_part_assign) << endl;
//  LOG_DEBUG << endl << instance.proc_part_assign;
}

void generate_bootstraps(RaxmlInstance& instance, const Checkpoint& checkp)
{
  if (instance.opts.command == Command::bootstrap || instance.opts.command == Command::all)
  {
    BootstrapGenerator bg;
    for (size_t b = 0; b < instance.opts.num_bootstraps; ++b)
    {
      auto seed = rand();

      /* check if this BS was already computed in the previous run and saved in checkpoint */
      if (b < checkp.bs_trees.size())
        continue;

      instance.bs_reps.emplace_back(bg.generate(instance.parted_msa, seed));
    }
  }
}

void draw_bootstrap_support(RaxmlInstance& instance, const Checkpoint& checkp)
{
  Tree tree = checkp.tree;
  tree.topology(checkp.ml_trees.best_topology());

  instance.bs_tree.reset(new BootstrapTree(tree));

  for (auto bs: checkp.bs_trees)
  {
    tree.topology(bs.second);
    instance.bs_tree->add_bootstrap_tree(tree);
  }
  instance.bs_tree->calc_support();
}

void save_ml_trees(const Options& opts, const Checkpoint& checkp)
{
  NewickStream nw(opts.ml_trees_file(), std::ios::out);
  Tree ml_tree = checkp.tree;
  for (auto topol: checkp.ml_trees)
  {
    ml_tree.topology(topol.second);
    nw << ml_tree;
  }
}

void print_final_output(const RaxmlInstance& instance, const Checkpoint& checkp)
{
  auto const& opts = instance.opts;

  LOG_INFO << "\nOptimized model parameters:" << endl;

  assert(checkp.models.size() == instance.parted_msa.part_count());

  for (size_t p = 0; p < instance.parted_msa.part_count(); ++p)
  {
    LOG_INFO << "\n   Partition " << p << ": " << instance.parted_msa.part_info(p).name().c_str() << endl;
    LOG_INFO << checkp.models.at(p);
  }

  if (opts.command == Command::evaluate)
  {
    save_ml_trees(opts, checkp);

    LOG_INFO << "\nAll optimized tree(s) saved to: " << sysutil_realpath(opts.ml_trees_file()) << endl;
  }

  if (opts.command == Command::search || opts.command == Command::all)
  {
    auto best = checkp.ml_trees.best();

    LOG_INFO << "\nFinal LogLikelihood: " << FMT_LH(best->first) << endl << endl;

    Tree best_tree = checkp.tree;

    best_tree.topology(best->second);

    NewickStream nw_result(opts.best_tree_file());
    nw_result << best_tree;

    if (checkp.ml_trees.size() > 1)
    {
      save_ml_trees(opts, checkp);

      LOG_INFO << "All ML trees saved to: " << sysutil_realpath(opts.ml_trees_file()) << endl;
    }

    LOG_INFO << "Best ML tree saved to: " << sysutil_realpath(opts.best_tree_file()) << endl;

    if (opts.command == Command::all)
    {
      assert(instance.bs_tree);

      NewickStream nw(opts.support_tree_file(), std::ios::out);
      nw << *instance.bs_tree;

      LOG_INFO << "Best ML tree with bootstrap support values saved to: " <<
          sysutil_realpath(opts.support_tree_file()) << endl;
    }
  }

  if (opts.command == Command::bootstrap || opts.command == Command::all)
  {
    // TODO now only master process writes the output, this will have to change with
    // coarse-grained parallelization scheme (parallel start trees/bootstraps)
//    NewickStream nw(opts.bootstrap_trees_file(), std::ios::out | std::ios::app);
    NewickStream nw(opts.bootstrap_trees_file(), std::ios::out);

    Tree bs_tree = checkp.tree;
    for (auto topol: checkp.bs_trees)
    {
      bs_tree.topology(topol.second);
      nw << bs_tree;
    }

    LOG_INFO << "Bootstrap trees saved to: " << sysutil_realpath(opts.bootstrap_trees_file()) << endl;
  }

  LOG_INFO << "\nExecution log saved to: " << sysutil_realpath(opts.log_file()) << endl;

  LOG_INFO << "\nElapsed time: " << FMT_PREC3(sysutil_elapsed_seconds()) << " seconds\n";
  if (checkp.elapsed_seconds > 0.)
  {
    LOG_INFO << "Total analysis time: " <<
                FMT_PREC3(checkp.elapsed_seconds + sysutil_elapsed_seconds()) << " seconds\n";
  }
  LOG_INFO << endl;
}

void thread_main(RaxmlInstance& instance, CheckpointManager& cm)
{
  unique_ptr<TreeInfo> treeinfo;

//  printf("thread %lu / %lu\n", ParallelContext::thread_id(), ParallelContext::num_procs());

  /* wait until master thread prepares all global data */
  ParallelContext::thread_barrier();

  auto const& master_msa = instance.parted_msa;
  auto const& opts = instance.opts;

  /* get partitions assigned to the current thread */
  auto const& part_assign = instance.proc_part_assign.at(ParallelContext::proc_id());

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
    bool use_ckp_tree = cm.checkpoint().search_state.step != CheckpointStep::start;
    for (const auto& tree: instance.start_trees)
    {
      assert(!tree.empty());

      start_tree_num++;

      if (use_ckp_tree)
      {
        treeinfo.reset(new TreeInfo(opts, cm.checkpoint().tree, master_msa, part_assign));
        use_ckp_tree = false;
      }
      else
        treeinfo.reset(new TreeInfo(opts, tree, master_msa, part_assign));

      Optimizer optimizer(opts);
      if (opts.command == Command::evaluate)
      {
        LOG_INFO_TS << "Tree #" << start_tree_num <<
            ", initial LogLikelihood: " << FMT_LH(treeinfo->loglh()) << endl;
        cm.search_state().loglh = optimizer.optimize(*treeinfo);
        cm.update_and_write(*treeinfo);
      }
      else
      {
        optimizer.optimize_topology(*treeinfo, cm);
      }

      LOG_PROGR << endl;
      if (opts.command == Command::evaluate)
      {
        LOG_INFO_TS << "Tree #" << start_tree_num <<
            ", final logLikelihood: " << FMT_LH(cm.checkpoint().loglh()) << endl;
      }
      else
      {
        LOG_INFO_TS << "ML tree search #" << start_tree_num <<
            ", logLikelihood: " << FMT_LH(cm.checkpoint().loglh()) << endl;
      }
      LOG_PROGR << endl;

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
  for (const auto bs: instance.bs_reps)
  {
    ++bs_num;

    // rebalance sites
    if (ParallelContext::master_thread())
    {
      balance_load(instance, bs.site_weights);
    }
    ParallelContext::thread_barrier();

    auto const& bs_part_assign = instance.proc_part_assign.at(ParallelContext::proc_id());

//    Tree tree = Tree::buildRandom(master_msa.full_msa());
    /* for now, use the same random tree for all bootstraps */
    const Tree& tree = instance.random_tree;
    treeinfo.reset(new TreeInfo(opts, tree, master_msa, bs_part_assign, bs.site_weights));

    Optimizer optimizer(opts);
    optimizer.optimize_topology(*treeinfo, cm);

    LOG_PROGR << endl;
    LOG_INFO_TS << "Bootstrap tree #" << bs_num <<
                ", logLikelihood: " << FMT_LH(cm.checkpoint().loglh()) << endl;
    LOG_PROGR << endl;

    cm.save_bs_tree();
    cm.reset_search_state();
  }

  ParallelContext::thread_barrier();
}

void master_main(RaxmlInstance& instance, CheckpointManager& cm)
{
  auto const& opts = instance.opts;
  auto& parted_msa = instance.parted_msa;

  init_part_info(instance);

  load_msa(instance);

  /* init template tree */
  instance.random_tree = generate_tree(instance, StartingTree::random);

  /* load checkpoint */
  load_checkpoint(instance, cm);

  /* load/create starting tree */
  build_start_trees(instance, cm);

  LOG_VERB << endl << "Initial model parameters:" << endl;
  for (size_t p = 0; p < parted_msa.part_count(); ++p)
  {
    LOG_VERB << "   Partition: " << parted_msa.part_info(p).name() << endl <<
        parted_msa.model(p) << endl;
  }

  /* run load balancing algorithm */
  balance_load(instance);

  /* generate bootstrap replicates */
  generate_bootstraps(instance, cm.checkpoint());

  thread_main(instance, cm);

  if (ParallelContext::master_rank())
  {
    if (opts.command == Command::all)
      draw_bootstrap_support(instance, cm.checkpoint());

    print_final_output(instance, cm.checkpoint());

    /* analysis finished successfully, remove checkpoint file */
    cm.remove();
  }
}

void clean_exit(int retval)
{
  ParallelContext::finalize(retval != EXIT_SUCCESS);
  exit(retval);
}

int main(int argc, char** argv)
{
  int retval = EXIT_SUCCESS;

  RaxmlInstance instance;

  ParallelContext::init_mpi(argc, argv);

  instance.opts.num_ranks = ParallelContext::num_ranks();

  logger().add_log_stream(&cout);

  CommandLineParser cmdline;
  try
  {
    cmdline.parse_options(argc, argv, instance.opts);
  }
  catch (OptionException &e)
  {
    LOG_INFO << "ERROR: " << e.what() << std::endl;
    clean_exit(EXIT_FAILURE);
  }

  /* handle trivial commands first */
  switch (instance.opts.command)
  {
    case Command::help:
      print_banner();
      cmdline.print_help();
      clean_exit(EXIT_SUCCESS);
      break;
    case Command::version:
      print_banner();
      clean_exit(EXIT_SUCCESS);
      break;
    case Command::evaluate:
    case Command::search:
    case Command::bootstrap:
    case Command::all:
      if (!instance.opts.redo_mode && instance.opts.result_files_exist())
      {
        LOG_ERROR << endl << "ERROR: Result files for the run with prefix `" <<
                            (instance.opts.outfile_prefix.empty() ?
                                instance.opts.msa_file : instance.opts.outfile_prefix) <<
                            "` already exist!\n" <<
                            "Please either choose a new prefix, remove old files, or add "
                            "--redo command line switch to overwrite them." << endl << endl;
        clean_exit(EXIT_FAILURE);
      }
      break;
    default:
      break;
  }

  /* now get to the real stuff */
  srand(instance.opts.random_seed);
  logger().set_log_level(instance.opts.log_level);

  /* only master process writes the log file */
  if (ParallelContext::master())
  {
    auto mode = !instance.opts.redo_mode && sysutil_file_exists(instance.opts.checkp_file()) ?
        ios::app : ios::out;
    logger().set_log_filename(instance.opts.log_file(), mode);
  }

  print_banner();
  LOG_INFO << instance.opts;

  switch (instance.opts.command)
  {
    case Command::evaluate:
    case Command::search:
    case Command::bootstrap:
    case Command::all:
    {
      try
      {
        if (instance.opts.redo_mode)
        {
          LOG_WARN << "WARNING: Running in REDO mode: existing checkpoints are ignored, "
              "and all result files will be overwritten!" << endl << endl;
          instance.opts.remove_result_files();
        }

        /* init load balancer */
        instance.load_balancer.reset(new KassianLoadBalancer());

        CheckpointManager cm(instance.opts.checkp_file());
        ParallelContext::init_pthreads(instance.opts, std::bind(thread_main,
                                                                std::ref(instance),
                                                                std::ref(cm)));

        master_main(instance, cm);
      }
      catch(exception& e)
      {
        LOG_ERROR << endl << "ERROR: " << e.what() << endl << endl;
        retval = EXIT_FAILURE;
      }
      break;
    }
    case Command::none:
    default:
      LOG_ERROR << "Unknown command!" << endl;
      retval = EXIT_FAILURE;
  }

  clean_exit(retval);
  return retval;
}
