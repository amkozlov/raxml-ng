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
};

//struct TreeWithParams
//{
//  Tree tree;
//  double loglh;
//  std::unordered_map<size_t, Model> models;
//};

void print_banner()
{
  LOG_INFO << "RAxML-NG v. 0.1alpha (c) 2017 The Exelixis Lab" << endl;
  LOG_INFO << endl <<
      "WARNING: This is an EXPERIMENTAL version of RAxML which has not been released yet!"
      << endl << endl;
}

void build_start_trees(RaxmlInstance& instance)
{
  Tree tree;

  const auto& opts = instance.opts;
  const auto& parted_msa = instance.parted_msa;
  const auto& msa = parted_msa.full_msa();

  switch (opts.start_tree)
  {
    case StartingTree::user:
    {
      assert(!opts.tree_file.empty());

      /* parse the unrooted binary tree in newick format, and store the number
         of tip nodes in tip_nodes_count */
      tree = Tree::loadFromFile(opts.tree_file);

      if (msa.size() > tree.num_tips())
        sysutil_fatal("Alignment file contains more sequences than expected");
      else if (msa.size() != tree.num_tips())
        sysutil_fatal("Some taxa are missing from the alignment file");

      LOG_INFO << "Loaded user starting tree with " << tree.num_tips() << " taxa from: "
                     << opts.tree_file << endl;
      break;
    }
    case StartingTree::random:
      /* no starting tree provided, generate a random one */
      assert(opts.command != Command::evaluate);

      LOG_INFO << "Generating a random starting tree with " << msa.size() << " taxa" << endl;

      tree = Tree::buildRandom(msa);

      break;
    case StartingTree::parsimony:
    {
      LOG_INFO << "Generating a parsimony starting tree with " << msa.size() << " taxa" << endl;

      unsigned int score;
      tree = Tree::buildParsimony(parted_msa, opts.random_seed, opts.simd_arch, &score);

      LOG_INFO << "Parsimony score of the starting tree: " << score << endl;

      break;
    }
    default:
      sysutil_fatal("Unknown starting tree type: %d\n", opts.start_tree);
  }

  assert(!tree.empty());

  /* fix missing branch lengths */
  tree.fix_missing_brlens();

  /* make sure tip indices are consistent between MSA and pll_tree */
  tree.reset_tip_ids(msa.label_id_map());

  instance.start_trees.emplace_back(move(tree));
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

void load_checkpoint(RaxmlInstance& instance, CheckpointManager& cm)
{
  /* init checkpoint and set to th manager */
  {
    Checkpoint ckp;
    for (size_t p = 0; p < instance.parted_msa.part_count(); ++p)
      ckp.models[p] = instance.parted_msa.part_info(p).model();
    ckp.tree = instance.start_trees.at(0);

    cm.checkpoint(move(ckp));
  }

  if (cm.read())
  {
    const auto& ckp = cm.checkpoint();
    for (const auto& m: ckp.models)
      instance.parted_msa.model(m.first, m.second);

    instance.start_trees.at(0) = ckp.tree;

    LOG_INFO << "\nCheckpoint file found, execution will be resumed " <<
        "(logLH: " << ckp.loglh() << ")" << endl;
  }
}

void generate_bootstraps(RaxmlInstance& instance)
{
  if (instance.opts.command == Command::bootstrap || instance.opts.command == Command::all)
  {
    BootstrapGenerator bg;
    for (size_t b = 0; b < instance.opts.num_bootstraps; ++b)
    {
      auto seed = rand();
      instance.bs_reps.emplace_back(bg.generate(instance.parted_msa, seed));
    }
  }
}

void print_final_output(const RaxmlInstance& instance, const Checkpoint& bestTree)
{
  auto const& opts = instance.opts;

  LOG_INFO << "\nOptimized model parameters:" << endl;

  assert(bestTree.models.size() == instance.parted_msa.part_count());

  for (size_t p = 0; p < instance.parted_msa.part_count(); ++p)
  {
    LOG_INFO << "\n   Partition " << p << ": " << instance.parted_msa.part_info(p).name().c_str() << endl;
    LOG_INFO << bestTree.models.at(p);
  }

  LOG_INFO << "\nFinal LogLikelihood: " << setprecision(6) << bestTree.loglh() << endl;

  NewickStream nw_result(opts.best_tree_file());
  nw_result << bestTree.tree;

  LOG_INFO << "\nElapsed time: " << setprecision(3) << sysutil_elapsed_seconds() << " seconds\n\n";

  if (opts.command == Command::search || opts.command == Command::all)
  {
    if (instance.start_trees.size() > 1)
      LOG_INFO << "All ML trees saved to: " << sysutil_realpath(opts.ml_trees_file()) << endl;
    LOG_INFO << "Best ML tree saved to: " << sysutil_realpath(opts.best_tree_file()) << endl;
  }

  if (opts.command == Command::bootstrap || opts.command == Command::all)
  {
    LOG_INFO << "Bootstrap trees saved to: " << sysutil_realpath(opts.bootstrap_trees_file()) << endl;
  }

  LOG_INFO << "\nExecution log saved to: " << sysutil_realpath(opts.log_file()) << endl << endl;
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

  size_t start_tree_num = 0;
  for (auto const& tree: instance.start_trees)
  {
    assert(!tree.empty());

    if (!treeinfo)
      treeinfo.reset(new TreeInfo(opts, tree, master_msa, part_assign));
    else
      treeinfo->tree(tree);

    Optimizer optimizer(opts);
    if (opts.command == Command::search || opts.command == Command::all)
    {
      LOG_INFO << "\nRunning ML search from starting tree #" << start_tree_num+1 << endl << endl;
      optimizer.optimize_topology(*treeinfo, cm);
    }
    else
    {
      LOG_INFO << "\nInitial LogLikelihood: " << treeinfo->loglh() << endl << endl;
      optimizer.optimize(*treeinfo);
    }

    start_tree_num++;
  }

  ParallelContext::thread_barrier();

  if (!instance.bs_reps.empty())
  {
    if (opts.command == Command::all)
    {
      LOG_INFO << "ML tree search completed, best tree logLH: " << cm.checkpoint().loglh()
               << endl << endl;
    }

    LOG_INFO << "Starting bootstrapping analysis with " << instance.bs_reps.size()
             << " replicates." << endl << endl;
  }

  // TODO: implement checkpointing for bootstraps
  cm.disable();

  /* infer bootstrap trees if needed */
  size_t bs_num = 0;
  for (const auto bs: instance.bs_reps)
  {
    /* for now, use the same starting tree as for the tree search */
//    Tree tree = Tree::buildRandom(master_msa.full_msa());
    const Tree& tree = instance.start_trees.at(0);
    treeinfo.reset(new TreeInfo(opts, tree, master_msa, part_assign, bs.site_weights));

//    checkp.reset_search_state();

    Optimizer optimizer(opts);
    optimizer.optimize_topology(*treeinfo, cm);

    if (ParallelContext::master())
    {
      NewickStream nw(opts.bootstrap_trees_file(), std::ios::out | std::ios::app);
      nw << treeinfo->pll_utree_root();
    }

    LOG_PROGR << endl;
    LOG_INFO << "Bootstrap tree #" << ++bs_num <<
                ", logLikelihood: " << treeinfo->loglh(true) << endl;
    LOG_PROGR << endl;
  }

  ParallelContext::thread_barrier();
}

void search_evaluate(RaxmlInstance& instance, CheckpointManager& cm)
{
  auto const& opts = instance.opts;
  auto& parted_msa = instance.parted_msa;

  init_part_info(instance);

  load_msa(instance);

  /* load/create starting tree */
  build_start_trees(instance);

  if (::ParallelContext::master_rank())
  {
    const std::string start_fname = opts.output_fname("startTree");
    NewickStream nw_start(start_fname);
    for (auto const& tree: instance.start_trees)
      nw_start << tree;
  }

  /* load checkpoint */
  load_checkpoint(instance, cm);

  LOG_DEBUG << "Initial model parameters:" << endl;
  for (size_t p = 0; p < parted_msa.part_count(); ++p)
  {
    LOG_DEBUG << "   Partition: " << parted_msa.part_info(p).name() << endl <<
        parted_msa.model(p) << endl;
  }

  /* run load balancing algorithm */
  balance_load(instance);

  /* generate bootstrap replicates */
  generate_bootstraps(instance);

  search_evaluate_thread(instance, cm);

  if (ParallelContext::master_rank())
  {
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
