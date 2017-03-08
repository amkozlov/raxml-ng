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

using namespace std;

typedef vector<Tree> TreeList;
struct RaxmlInstance
{
  Options opts;
  PartitionedMSA parted_msa;
  TreeList start_trees;
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

TreeList get_start_tree(const Options &opts, const PartitionedMSA& part_msa)
{
  Tree tree;
  TreeList tree_list;

  const MSA& msa = part_msa.full_msa();

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

      tree = Tree::buildRandom(msa.size(), (const char * const*) msa.pll_msa()->label);

      break;
    case StartingTree::parsimony:
    {
      LOG_INFO << "Generating a parsimony starting tree with " << msa.size() << " taxa" << endl;

      unsigned int score;
      tree = Tree::buildParsimony(part_msa, opts.random_seed, opts.simd_arch, &score);

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

  tree_list.emplace_back(move(tree));

  return tree_list;
}

PartitionedMSA init_part_info(Options &opts)
{
  PartitionedMSA part_msa;

  /* check if model is a file */
  if (sysutil_file_exists(opts.model_file))
  {
    // read partition definitions from file
    RaxmlPartitionFileStream partfile(opts.model_file);
    partfile >> part_msa;

//    DBG("partitions found: %d\n", useropt->part_count);
  }
  else
  {
    // create and init single pseudo-partition
    part_msa.emplace_part_info("noname", opts.data_type, opts.model_file);
  }

  /* make sure that linked branch length mode is set for unpartitioned alignments */
  if (part_msa.part_count() == 1)
    opts.brlen_linkage = PLLMOD_TREE_BRLEN_LINKED;

  int lg4x_count = 0;

  for (const auto& pinfo: part_msa.part_list())
  {
//    LOG_INFO << "|" << pinfo.name() << "|   |" << pinfo.model().to_string() << "|   |" <<
//        pinfo.range_string() << "|" << endl;

    if (pinfo.model().name() == "LG4X")
      lg4x_count++;
  }

  if (part_msa.part_count() > 1 && lg4x_count > 0 && opts.brlen_linkage == PLLMOD_TREE_BRLEN_LINKED)
  {
    throw runtime_error("LG4X model is not supported in linked branch length mode, sorry :(");
  }

  return part_msa;
}

void balance_load(RaxmlInstance& instance)
{
  PartitionAssignment part_sizes;

  /* init list of partition sizes */
  size_t i = 0;
  for (auto const& pinfo: instance.parted_msa.part_list())
  {
    part_sizes.assign_sites(i, 0, pinfo.msa().num_patterns());
    ++i;
  }

//  SimpleLoadBalancer balancer;
  KassianLoadBalancer balancer;

  instance.proc_part_assign = balancer.get_all_assignments(part_sizes, ParallelContext::num_procs());

  LOG_INFO << "\nData distribution:\n" << instance.proc_part_assign;
}

void load_msa(const Options& opts, PartitionedMSA& part_msa)
{
  LOG_INFO << "Reading alignment from file: " << opts.msa_file << endl;

  /* load MSA */
  auto msa = msa_load_from_file(opts.msa_file, opts.msa_format);

  LOG_INFO << "Loaded alignment with " << msa.size() << " taxa and " <<
      msa.num_sites() << " sites" << endl;

  /* check alignment */
//  check_msa(useropt, msa);

  part_msa.full_msa(std::move(msa));

//  LOG_INFO << "Splitting MSA... " << endl;

  part_msa.split_msa();

  if (opts.use_pattern_compression)
    part_msa.compress_patterns();

  part_msa.set_model_empirical_params();

  // TODO: check empirical params (e.g. zero state freqs)

  LOG_INFO << endl;

  LOG_INFO << "Alignment comprises " << part_msa.part_count() << " partitions and " <<
      part_msa.total_length() << " patterns\n" << endl;

  LOG_INFO << part_msa;

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

void print_final_output(const RaxmlInstance& instance, const Checkpoint& bestTree)
{
  auto const& opts = instance.opts;
  auto const& tree_fname = opts.output_fname("bestTree");

  LOG_INFO << "\nOptimized model parameters:" << endl;

  assert(bestTree.models.size() == instance.parted_msa.part_count());

  for (size_t p = 0; p < instance.parted_msa.part_count(); ++p)
  {
    LOG_INFO << "\n   Partition " << p << ": " << instance.parted_msa.part_info(p).name().c_str() << endl;
    LOG_INFO << bestTree.models.at(p);
  }

  LOG_INFO << "\nFinal LogLikelihood: " << setprecision(6) << bestTree.loglh() << endl;

  NewickStream nw_result(tree_fname);
  nw_result << bestTree.tree;

  LOG_INFO << "\nElapsed time: " << setprecision(3) << sysutil_elapsed_seconds() << " seconds\n";

  LOG_INFO << "\nFinal tree saved to: " << sysutil_realpath(tree_fname) << endl;
  LOG_INFO << "\nExecution log saved to: " << sysutil_realpath(opts.log_file) << endl << endl;
}

void search_evaluate_thread(const RaxmlInstance& instance, CheckpointManager& checkp)
{
  unique_ptr<TreeInfo> treeinfo;
  auto const& ctx = ParallelContext::ctx();

  //  printf("thread %lu / %lu\n", ParallelContext::ctx().thread_id(), ParallelContext::num_procs());

  /* wait until master thread prepares all global data */
  ctx.thread_barrier();

  auto const& master_msa = instance.parted_msa;
  auto const& opts = instance.opts;

  /* get partitions assigned to the current thread */
  auto const& part_assign = instance.proc_part_assign.at(ctx.proc_id());

//  size_t start_tree_num = 0;

  for (auto const& tree: instance.start_trees)
  {
    assert(!tree.empty());

    if (!treeinfo)
      treeinfo.reset(new TreeInfo(opts, tree, master_msa, part_assign));
    else
      treeinfo->tree(tree);

    LOG_INFO << "\nInitial LogLikelihood: " << treeinfo->loglh() << endl;

    Optimizer optimizer(opts);
    if (opts.command == Command::search)
      optimizer.optimize_topology(*treeinfo, checkp);
    else
      optimizer.optimize(*treeinfo);
  }

  ctx.thread_barrier();
}

void search_evaluate(RaxmlInstance& instance, CheckpointManager& checkp)
{
  auto const& opts = instance.opts;
  auto& parted_msa = instance.parted_msa;

  instance.parted_msa = init_part_info(instance.opts);

  load_msa(opts, instance.parted_msa);

  /* load/create starting tree */
  instance.start_trees = get_start_tree(opts, parted_msa);

  if (::ParallelContext::master_rank())
  {
    const std::string start_fname = opts.output_fname("startTree");
    NewickStream nw_start(start_fname);
    for (auto const& tree: instance.start_trees)
      nw_start << tree;
  }

  /* load checkpoint */
  load_checkpoint(instance, checkp);

  LOG_DEBUG << "Initial model parameters:" << endl;
  for (size_t p = 0; p < parted_msa.part_count(); ++p)
  {
    LOG_DEBUG << "   Partition: " << parted_msa.part_info(p).name() << endl <<
        parted_msa.model(p) << endl;
  }

  /* run load balancing algorithm */
  balance_load(instance);

  search_evaluate_thread(instance, checkp);

  if (ParallelContext::master_rank())
    print_final_output(instance, checkp.checkpoint());
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
  logger().set_log_level(instance.opts.log_level);
  logger().set_log_filename(instance.opts.log_file);

  print_banner();
  LOG_INFO << instance.opts;

  switch (instance.opts.command)
  {
    case Command::evaluate:
    case Command::search:
    {
      try
      {
        CheckpointManager checkp(instance.opts.checkp_file);
        ParallelContext::init_pthreads(instance.opts, std::bind(search_evaluate_thread,
                                                                std::cref(instance),
                                                                std::ref(checkp)));

        search_evaluate(instance, checkp);
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
