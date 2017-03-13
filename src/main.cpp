/*
    Copyright (C) 2016 Alexey Kozlov, Alexandros Stamatakis, Diego Darriba, Tomas Flouri

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

  /* this is just a dummy random tree used for convenience, e,g, if we need tip labels or
   * just 'any' valid tree for the alignment at hand */
  Tree random_tree;
};

void print_banner()
{
  LOG_INFO << "RAxML-NG v. 0.1.0 BETA (c) 2017 The Exelixis Lab" << endl;
  LOG_INFO << endl <<
      "WARNING: This is an EXPERIMENTAL version of RAxML which has not been released yet!"
      << endl << endl;
}

void init_part_info(RaxmlInstance& instance)
{
  auto& opts = instance.opts;
  auto& parted_msa = instance.parted_msa;

  /* check if model is a file */
  if (sysutil_file_exists(opts.model_file))
  {
    // read partition definitions from file
    RaxmlPartitionFileStream partfile(opts.model_file);
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

void load_msa(RaxmlInstance& instance)
{
  const auto& opts = instance.opts;
  auto& parted_msa = instance.parted_msa;

  LOG_INFO << "Reading alignment from file: " << opts.msa_file << endl;

  /* load MSA */
  auto msa = msa_load_from_file(opts.msa_file, opts.msa_format);

  LOG_INFO << "Loaded alignment with " << msa.size() << " taxa and " <<
      msa.num_sites() << " sites" << endl;

  /* check alignment */
//  check_msa(useropt, msa);

  parted_msa.full_msa(std::move(msa));

//  LOG_INFO << "Splitting MSA... " << endl;

  parted_msa.split_msa();

  if (opts.use_pattern_compression)
    parted_msa.compress_patterns();

  parted_msa.set_model_empirical_params();

  // TODO: check empirical params (e.g. zero state freqs)

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
      assert(!opts.tree_file.empty());

      /* parse the unrooted binary tree in newick format, and store the number
         of tip nodes in tip_nodes_count */
      tree = Tree::loadFromFile(opts.tree_file);

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
      assert(opts.command != Command::evaluate);

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
  /* init checkpoint and set to th manager */
  {
    Checkpoint ckp;
    for (size_t p = 0; p < instance.parted_msa.part_count(); ++p)
      ckp.models[p] = instance.parted_msa.part_info(p).model();

    // this is a "template" tree, which provides tip labels and node ids
    ckp.tree = instance.random_tree;

    cm.checkpoint(move(ckp));
  }

  if (cm.read())
  {
    const auto& ckp = cm.checkpoint();
    for (const auto& m: ckp.models)
      instance.parted_msa.model(m.first, m.second);

    LOG_INFO << "\nCheckpoint file found, execution will be resumed " <<
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
      LOG_INFO << "Loading user starting tree(s) from: " << opts.tree_file << endl;
      break;
    case StartingTree::random:
      LOG_INFO << "Generating random starting tree(s) with " << msa.size() << " taxa" << endl;
      break;
    case StartingTree::parsimony:
      LOG_INFO << "Generating parsimony starting tree(s) with " << msa.size() << " taxa" << endl;
      break;
    default:
      assert(0);
  }

  for (size_t i = 0; i < opts.num_searches; ++i)
  {
    auto tree = generate_tree(instance, opts.start_tree);

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

//  SimpleLoadBalancer balancer;
  KassianLoadBalancer balancer;

  instance.proc_part_assign = balancer.get_all_assignments(part_sizes, ParallelContext::num_procs());

  LOG_INFO << "\nData distribution:\n" << instance.proc_part_assign;
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
      NewickStream nw(opts.ml_trees_file(), std::ios::out);
      Tree ml_tree = checkp.tree;
      for (auto topol: checkp.ml_trees)
      {
        ml_tree.topology(topol.second);
        nw << ml_tree;
      }

      LOG_INFO << "All ML trees saved to: " << sysutil_realpath(opts.ml_trees_file()) << endl;
    }

    LOG_INFO << "Best ML tree saved to: " << sysutil_realpath(opts.best_tree_file()) << endl;
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

  LOG_INFO << "\nElapsed time: " << setprecision(3) << sysutil_elapsed_seconds() << " seconds\n\n";
}

void search_evaluate_thread(const RaxmlInstance& instance, CheckpointManager& cm)
{
  unique_ptr<TreeInfo> treeinfo;

//  printf("thread %lu / %lu\n", ParallelContext::thread_id(), ParallelContext::num_procs());

  /* wait until master thread prepares all global data */
  ParallelContext::thread_barrier();

  auto const& master_msa = instance.parted_msa;
  auto const& opts = instance.opts;

  /* get partitions assigned to the current thread */
  auto const& part_assign = instance.proc_part_assign.at(ParallelContext::proc_id());

  if ((opts.command == Command::search || opts.command == Command::all) &&
      !instance.start_trees.empty())
  {

    LOG_INFO << "\nStarting ML tree search with " << opts.num_searches <<
        " distinct starting trees" << endl << endl;

    size_t start_tree_num = cm.checkpoint().ml_trees.size();
    bool use_ckp_tree = (start_tree_num > 0);
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

  //    if (!treeinfo)
  //      treeinfo.reset(new TreeInfo(opts, tree, master_msa, part_assign));
  //    else
  //      treeinfo->tree(tree);

      Optimizer optimizer(opts);
      if (opts.command == Command::search || opts.command == Command::all)
      {
        optimizer.optimize_topology(*treeinfo, cm);
      }
      else
      {
        LOG_INFO << "\nInitial LogLikelihood: " << FMT_LH(treeinfo->loglh()) << endl << endl;
        optimizer.optimize(*treeinfo);
      }

      LOG_PROGR << endl;
      LOG_INFO << "ML tree search #" << start_tree_num <<
          ", logLikelihood: " << FMT_LH(cm.checkpoint().loglh()) << endl;
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
      LOG_INFO << endl << "ML tree search completed, best tree logLH: " <<
          FMT_LH(cm.checkpoint().ml_trees.best_score()) << endl << endl;
    }

    LOG_INFO << "Starting bootstrapping analysis with " << opts.num_bootstraps
             << " replicates." << endl << endl;
  }

  /* infer bootstrap trees if needed */
  size_t bs_num = cm.checkpoint().bs_trees.size();
  for (const auto bs: instance.bs_reps)
  {
    ++bs_num;

//    Tree tree = Tree::buildRandom(master_msa.full_msa());
    /* for now, use the same random tree for all bootstraps */
    const Tree& tree = instance.random_tree;
    treeinfo.reset(new TreeInfo(opts, tree, master_msa, part_assign, bs.site_weights));

    Optimizer optimizer(opts);
    optimizer.optimize_topology(*treeinfo, cm);

    LOG_PROGR << endl;
    LOG_INFO << "Bootstrap tree #" << bs_num <<
                ", logLikelihood: " << FMT_LH(cm.checkpoint().loglh()) << endl;
    LOG_PROGR << endl;

    cm.save_bs_tree();
    cm.reset_search_state();
  }

  ParallelContext::thread_barrier();
}

void search_evaluate(RaxmlInstance& instance, CheckpointManager& cm)
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

  LOG_DEBUG << "Initial model parameters:" << endl;
  for (size_t p = 0; p < parted_msa.part_count(); ++p)
  {
    LOG_DEBUG << "   Partition: " << parted_msa.part_info(p).name() << endl <<
        parted_msa.model(p) << endl;
  }

  /* run load balancing algorithm */
  balance_load(instance);

  /* generate bootstrap replicates */
  generate_bootstraps(instance, cm.checkpoint());

  search_evaluate_thread(instance, cm);

  if (ParallelContext::master_rank())
  {
    if (opts.command == Command::all)
    {
      // TODO: draw BS support on the best ML tree

    }

    print_final_output(instance, cm.checkpoint());

    /* analysis finished successfully, remove checkpoint */
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
    default:
      break;
  }

  /* now get to the real stuff */
  srand(instance.opts.random_seed);
  logger().set_log_level(instance.opts.log_level);
  logger().set_log_filename(instance.opts.log_file());

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
        CheckpointManager cm(instance.opts.checkp_file());
        ParallelContext::init_pthreads(instance.opts, std::bind(search_evaluate_thread,
                                                                std::cref(instance),
                                                                std::ref(cm)));

        search_evaluate(instance, cm);
      }
      catch(exception& e)
      {
        LOG_ERROR << "ERROR:" << e.what() << endl << endl;
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
