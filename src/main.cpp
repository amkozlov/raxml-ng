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

using namespace std;

void print_banner()
{
  LOG_INFO << "RAxML-NG v. 0.1alpha (c) 2017 The Exelixis Lab" << endl;
  LOG_INFO << endl <<
      "WARNING: This is an EXPERIMENTAL version of RAxML which has not been released yet!"
      << endl << endl;
}

Tree get_start_tree(const Options &opts, const PartitionedMSA& part_msa)
{
  Tree tree;

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

  return tree;
}

PartitionedMSA init_part_info(const Options &opts)
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
//  if (opts.part_count == 1)
//    opts.brlen_linkage = PLLMOD_TREE_BRLEN_LINKED;

  int lg4x_count = 0;

  for (const auto& pinfo: part_msa.part_list())
  {
    LOG_INFO << "|" << pinfo.name() << "|   |" << pinfo.model().to_string() << "|   |" <<
        pinfo.range_string() << "|" << endl;

    if (pinfo.model().name() == "LG4X")
      lg4x_count++;
  }

  if (part_msa.part_count() > 1 && lg4x_count > 0 && opts.brlen_linkage == PLLMOD_TREE_BRLEN_LINKED)
  {
    throw runtime_error("LG4X model is not supported in linked branch length mode, sorry :(");
  }

  return part_msa;
}

PartitionedAssignment get_part_assign(const PartitionedMSA& parted_msa,
                                      size_t num_procs, size_t proc_id)
{
  PartitionedAssignment part_assign;

  // TODO: Kassian/Benoit load balancing algorithm
  for (auto const& pinfo: parted_msa.part_list())
  {
    PartitionRegion range;
    const size_t total_sites = pinfo.msa().num_patterns();
    const size_t proc_sites = total_sites / num_procs;
    range.start = proc_id * proc_sites;
    range.length = proc_id == num_procs-1 ? total_sites - range.start : proc_sites;
    part_assign.push_back(range);
  }

  return part_assign;
}

TreeInfo load_msa_and_tree(const Options& opts, PartitionedMSA& part_msa)
{
  PartitionedMSA* p_parted_msa = nullptr;
  Tree* p_tree = nullptr;
  Tree tree;

  if (ParallelContext::ctx().master())
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

    part_msa.set_modeL_empirical_params();

    LOG_INFO << endl;

    print_partition_info(part_msa);

    LOG_INFO << endl;

    /* load/create starting tree */
    tree = get_start_tree(opts, part_msa);

    p_tree = &tree;
    p_parted_msa = &part_msa;
  }

#ifdef _USE_PTHREADS
  ParallelContext::ctx().thread_broadcast(0, &p_parted_msa, sizeof(PartitionedMSA*));
  ParallelContext::ctx().thread_broadcast(0, &p_tree, sizeof(Tree *));
#endif

  assert(!p_tree->empty());

  auto part_assign = get_part_assign(*p_parted_msa, ParallelContext::num_procs(),
                                     ParallelContext::ctx().thread_id());

  TreeInfo treeinfo(opts, *p_tree, *p_parted_msa, part_assign);

  return treeinfo;
}

void search_evaluate(const Options& opts)
{
  const string tree_fname = opts.output_fname("raxml.bestTree");

  printf("thread %u / %u\n", ParallelContext::ctx().thread_id(), ParallelContext::num_procs());

  auto part_msa = init_part_info(opts);
  auto treeinfo = load_msa_and_tree(opts, part_msa);
  LOG_INFO << "\nInitial LogLikelihood: " << treeinfo.loglh() << endl;

  Optimizer optimizer(opts);
  if (opts.command == Command::search)
    optimizer.optimize_topology(treeinfo);
  else
    optimizer.optimize(treeinfo);

  const double final_loglh = treeinfo.loglh();

  if (ParallelContext::is_master())
  {
    assign(part_msa, treeinfo);
    for (auto const& pinfo: part_msa.part_list())
      print_model_info(pinfo.model());

    LOG_INFO << "\nFinal LogLikelihood: " << setprecision(6) << final_loglh << endl;

    NewickStream nw_result(tree_fname);
    nw_result << *treeinfo.pll_treeinfo().root;

    LOG_INFO << "\nElapsed time: " << setprecision(3) << sysutil_elapsed_seconds() << " seconds\n";

    LOG_INFO << "\nFinal tree saved to: " << sysutil_realpath(tree_fname) << endl;
  }
}

int main(int argc, char** argv)
{
  print_banner();

  Options opts;
  CommandLineParser cmdline;

  try
  {
    cmdline.parse_options(argc, argv, opts);
  }
  catch (OptionException &e)
  {
    LOG_INFO << "ERROR: " << e.what() << std::endl;
    exit(EXIT_FAILURE);
  }

  switch (opts.command)
  {
    case Command::help:
      cmdline.print_help();
      return EXIT_SUCCESS;
    case Command::version:
      return EXIT_SUCCESS;
    case Command::evaluate:
    case Command::search:
    {
      // parse model string & init partitions
      print_options(opts);

      ParallelContext::init(opts, std::bind(search_evaluate, opts));

      search_evaluate(opts);

      ParallelContext::finalize();

      return EXIT_SUCCESS;
    }
    case Command::none:
    default:
      LOG_INFO << "Unknown command!" << endl;
      return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
