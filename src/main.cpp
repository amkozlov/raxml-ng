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

//#include <cxxopts.hpp>
//
//#include "mpihead.hpp"

#include <memory>

#include "common.h"
#include "MSA.hpp"
#include "Options.hpp"
#include "CommandLineParser.hpp"
#include "Optimizer.hpp"
#include "PartitionInfo.hpp"
#include "TreeInfo.hpp"
#include "file_io.hpp"
#include "ParallelContext.hpp"
#include "LoadBalancer.hpp"

using namespace std;

typedef vector<Tree> TreeList;
struct RaxmlInstance
{
  Options opts;
  PartitionedMSA parted_msa;
  TreeList start_trees;
};

struct TreeWithParams
{
  Tree tree;
  double loglh;
  std::vector<Model> models;
};

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
//  return ParallelContext::master_broadcast(tree);
}

PartitionedMSA init_part_info(Options &opts)
{
  PartitionedMSA part_msa;

  /* check if model is a file */
  if (access(opts.model_file.c_str(), F_OK) != -1)
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

PartitionAssignment get_part_assign(const PartitionedMSA& parted_msa,
                                      size_t num_procs, size_t proc_id)
{
  PartitionAssignment part_sizes;

  /* init list of partition sizes */
  size_t i = 0;
  for (auto const& pinfo: parted_msa.part_list())
  {
    part_sizes.assign_sites(i, 0, pinfo.msa().num_patterns());
    ++i;
  }

//  SimpleLoadBalancer balancer;
  KassianLoadBalancer balancer;

  if (ParallelContext::is_master())
  {
    auto part_assign = balancer.get_all_assignments(part_sizes, num_procs);

    LOG_INFO << part_assign;

    return part_assign[proc_id];
  }
  else
    return balancer.get_proc_assignments(part_sizes, num_procs, proc_id);
}

void load_msa(const Options& opts, PartitionedMSA& part_msa)
{
  LOG_INFO << "Loading alignment from file: " << opts.msa_file << endl;

  /* load MSA */
  auto msa = msa_load_from_file(opts.msa_file, opts.msa_format);

  LOG_INFO << "Taxa: " << msa.size() << ", sites: " << msa.num_sites() << endl;

  /* check alignment */
//  check_msa(useropt, msa);

  part_msa.full_msa(std::move(msa));

//  LOG_INFO << "Splitting MSA... " << endl;

  part_msa.split_msa();

  if (opts.use_pattern_compression)
    part_msa.compress_patterns();

  part_msa.set_model_empirical_params();

  LOG_INFO << endl;

  print_partition_info(part_msa);

  LOG_INFO << endl;
}

void search_evaluate_thread(const RaxmlInstance& instance, TreeWithParams& bestTree)
{
  unique_ptr<TreeInfo> treeinfo;

  auto const& master_msa = instance.parted_msa;
  auto const& opts = instance.opts;

//  printf("thread %lu / %lu\n", ParallelContext::ctx().thread_id(), ParallelContext::num_procs());

#ifdef _USE_PTHREADS
  ParallelContext::ctx().barrier();
#endif

  /* run load balancing */
  auto part_assign = get_part_assign(master_msa, ParallelContext::num_procs(),
                                     ParallelContext::ctx().thread_id());

#ifdef _USE_PTHREADS
  ParallelContext::ctx().barrier();
#endif

//  size_t start_tree_num = 0;

  for (auto const& tree: instance.start_trees)
  {
    assert(!tree.empty());

    if (!treeinfo)
      treeinfo.reset(new TreeInfo(opts, tree, master_msa, part_assign));
    else
      treeinfo->tree(tree);

  //  LOG_INFO << "\nInitial LogLikelihood: " << treeinfo.loglh() << endl;

    Optimizer optimizer(opts);
    if (opts.command == Command::search)
      optimizer.optimize_topology(*treeinfo);
    else
      optimizer.optimize(*treeinfo);
  }

#ifdef _USE_PTHREADS
  ParallelContext::ctx().barrier();
#endif

  const double final_loglh = treeinfo->loglh();

  if (ParallelContext::is_master())
  {
    bestTree.loglh = final_loglh;
    bestTree.tree = treeinfo->tree();
    for (size_t p = 0; p < master_msa.part_count(); ++p)
      bestTree.models.push_back(master_msa.model(p));
  }

#ifdef _USE_PTHREADS
  ParallelContext::ctx().barrier();
#endif

  // collect model params: quite dirty so far, and also pthreads-specific
  // TODO: adapt for MPI
  for (auto const& prange: part_assign)
  {
    if (prange.start == 0)
    {
      assign(bestTree.models.at(prange.part_id), *treeinfo, prange.part_id);
    }
  }

#ifdef _USE_PTHREADS
  ParallelContext::ctx().barrier();
#endif
}

void search_evaluate(RaxmlInstance& instance, TreeWithParams& bestTree)
{
  auto const& opts = instance.opts;
  const string tree_fname = opts.output_fname("bestTree");

  instance.parted_msa = init_part_info(instance.opts);

  load_msa(opts, instance.parted_msa);

  /* load/create starting tree */
  instance.start_trees = get_start_tree(opts, instance.parted_msa);

  search_evaluate_thread(instance, bestTree);

  assert(bestTree.models.size() == instance.parted_msa.part_count());

  size_t p = 0;
  for (auto const& model: bestTree.models)
  {
    LOG_INFO << "\n   Partition " << p << ": " << instance.parted_msa.part_info(p).name().c_str() << endl;
    print_model_info(model);
    p++;
  }

  LOG_INFO << "\nFinal LogLikelihood: " << setprecision(6) << bestTree.loglh << endl;

  NewickStream nw_result(tree_fname);
  nw_result << bestTree.tree;

  LOG_INFO << "\nElapsed time: " << setprecision(3) << sysutil_elapsed_seconds() << " seconds\n";

  LOG_INFO << "\nFinal tree saved to: " << sysutil_realpath(tree_fname) << endl;
  LOG_INFO << "\nExecution log saved to: " << sysutil_realpath(opts.log_file) << endl << endl;
}

int main(int argc, char** argv)
{
  int retval = EXIT_SUCCESS;

  logger().add_log_stream(&cout);
  logger().set_log_level(LogLevel::progress);

  print_banner();

  RaxmlInstance instance;

  CommandLineParser cmdline;

  try
  {
    cmdline.parse_options(argc, argv, instance.opts);
  }
  catch (OptionException &e)
  {
    LOG_INFO << "ERROR: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  switch (instance.opts.command)
  {
    case Command::help:
      cmdline.print_help();
    case Command::version:
      retval = EXIT_SUCCESS;
      break;
    case Command::evaluate:
    case Command::search:
    {
      logger().set_log_filename(instance.opts.log_file);

      LOG_INFO << instance.opts;

      try
      {
        TreeWithParams bestTree;
        ParallelContext::init(instance.opts, std::bind(search_evaluate_thread,
                                                       std::cref(instance),
                                                       std::ref(bestTree)));

        search_evaluate(instance, bestTree);
      }
      catch(exception& e)
      {
        LOG_INFO << e.what() << endl;
        retval = EXIT_FAILURE;
      }

      ParallelContext::finalize();

      break;
    }
    case Command::none:
    default:
      LOG_INFO << "Unknown command!" << endl;
      retval = EXIT_FAILURE;
  }

  return retval;
}
