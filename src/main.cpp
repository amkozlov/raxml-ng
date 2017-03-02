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
#include "file_io.hpp"
#include "binary_io.hpp"
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
//  std::vector<Model> models;
  std::unordered_map<size_t, Model> models;
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

  LOG_INFO << endl;

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

PartitionAssignment get_part_assign(const PartitionedMSA& parted_msa, const ParallelContext& ctx)
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

  if (ctx.master())
  {
    auto part_assign = balancer.get_all_assignments(part_sizes, ctx.num_procs());

    LOG_INFO << "Data distribution:\n" << part_assign;

    return part_assign[ctx.proc_id()];
  }
  else
    return balancer.get_proc_assignments(part_sizes, ctx.num_procs(), ctx.proc_id());
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

  LOG_DEBUG << "Initial model parameters:" << endl;
  for (size_t p = 0; p < part_msa.part_count(); ++p)
  {
    LOG_DEBUG << "   Partition: " << part_msa.part_info(p).name() << endl <<
                 part_msa.model(p) << endl;
  }
}

void gather_model_params(const RaxmlInstance& instance, TreeWithParams& bestTree)
{
  ParallelContext::mpi_gather_custom(
       /* send callback -> worker ranks */
       [&bestTree](void * buf, size_t buf_size) -> int
       {
         BinaryStream bs((char*) buf, buf_size);
         bs << bestTree.models.size();
         for (auto const& entry: bestTree.models)
         {
           bs << entry.first << entry.second;
         }
         return (int) bs.pos();
       },
       /* receive callback -> master rank */
       [&bestTree,&instance](void * buf, size_t buf_size)
       {
         BinaryStream bs((char*) buf, buf_size);
         auto model_count = bs.get<size_t>();
         for (size_t m = 0; m < model_count; ++m)
         {
           size_t part_id;
           bs >> part_id;

           // initialize basic info
           bestTree.models[part_id] = instance.parted_msa.model(part_id);

           // read parameter estimates from binary stream
           bs >> bestTree.models[part_id];
         }
       }
   );
}

void print_final_output(const RaxmlInstance& instance, const TreeWithParams& bestTree)
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

  LOG_INFO << "\nFinal LogLikelihood: " << setprecision(6) << bestTree.loglh << endl;

  NewickStream nw_result(tree_fname);
  nw_result << bestTree.tree;

  LOG_INFO << "\nElapsed time: " << setprecision(3) << sysutil_elapsed_seconds() << " seconds\n";

  LOG_INFO << "\nFinal tree saved to: " << sysutil_realpath(tree_fname) << endl;
  LOG_INFO << "\nExecution log saved to: " << sysutil_realpath(opts.log_file) << endl << endl;
}

void search_evaluate_thread(const RaxmlInstance& instance, TreeWithParams& bestTree)
{
  unique_ptr<TreeInfo> treeinfo;

  auto const& master_msa = instance.parted_msa;
  auto const& opts = instance.opts;
  auto const& ctx = ParallelContext::ctx();

//  printf("thread %lu / %lu\n", ParallelContext::ctx().thread_id(), ParallelContext::num_procs());

  ctx.thread_barrier();

  /* run load balancing */
  auto part_assign = get_part_assign(master_msa, ctx);

  ctx.thread_barrier();

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

  ctx.thread_barrier();

  const double final_loglh = treeinfo->loglh();

  if (ctx.master())
  {
    bestTree.loglh = final_loglh;
    bestTree.tree = treeinfo->tree();
  }

  ctx.thread_barrier();

  for (auto const& prange: part_assign)
  {
    if (prange.start == 0)
    {
      /* we will modify a global map -> define critical section */
      ParallelContext::UniqueLock lock;

      /* thread processing the first chunk of a partition stores its model parameters -> there is
       * always *exactly* one such thread per partition (or load balancing is broken) */
      assert(bestTree.models.count(prange.part_id) == 0);
      bestTree.models[prange.part_id] = master_msa.model(prange.part_id);
      assign(bestTree.models.at(prange.part_id), *treeinfo, prange.part_id);
    }
  }

  ctx.thread_barrier();
}

void search_evaluate(RaxmlInstance& instance, TreeWithParams& bestTree)
{
  auto const& opts = instance.opts;

  instance.parted_msa = init_part_info(instance.opts);

  load_msa(opts, instance.parted_msa);

  /* load/create starting tree */
  instance.start_trees = get_start_tree(opts, instance.parted_msa);

  if (::ParallelContext::master_rank())
  {
    const std::string start_fname = opts.output_fname("startTree");
    NewickStream nw_start(start_fname);
    for (auto const& tree: instance.start_trees)
      nw_start << tree;
  }

  search_evaluate_thread(instance, bestTree);

  if (ParallelContext::num_ranks() > 1)
    gather_model_params(instance, bestTree);

  if (ParallelContext::master_rank())
    print_final_output(instance, bestTree);
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
        TreeWithParams bestTree;
        ParallelContext::init_pthreads(instance.opts, std::bind(search_evaluate_thread,
                                                                std::cref(instance),
                                                                std::ref(bestTree)));

        search_evaluate(instance, bestTree);
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
