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
#include "PartitionInfo.hpp"

using namespace std;

void print_banner()
{
  LOG_INFO << "RAxML-NG v. 0.1alpha (c) 2017 The Exelixis Lab" << endl;
  LOG_INFO << endl <<
      "WARNING: This is an EXPERIMENTAL version of RAxML which has not been released yet!"
      << endl << endl;
}

pll_utree_t * load_unrooted_tree(const char * filename,
                                 unsigned int * tip_count)
{
  pll_utree_t * utree;
  pll_rtree_t * rtree;

  if (!(rtree = pll_rtree_parse_newick(filename, tip_count)))
  {
    if (!(utree = pll_utree_parse_newick(filename, tip_count)))
    {
      return NULL;
    }
  }
  else
  {
    LOG_INFO << "NOTE: You provided a rooted tree; it will be automatically unrooted." << endl;
    utree = pll_rtree_unroot(rtree);

    /* optional step if using default PLL clv/pmatrix index assignments */
    pll_utree_reset_template_indices(utree, *tip_count);
  }

  return utree;
}

pll_utree_t * get_start_tree(const Options &opts, PartitionedMSA& part_msa)
{
  unsigned int tip_nodes_count;
  pll_utree_t * tree = NULL;

  const MSA& msa = part_msa.full_msa();

  switch (opts.start_tree)
  {
    case StartingTree::user:
      assert(!opts.tree_file.empty());

      /* parse the unrooted binary tree in newick format, and store the number
         of tip nodes in tip_nodes_count */
      tree = load_unrooted_tree(opts.tree_file.c_str(), &tip_nodes_count);
      if (!tree)
        sysutil_fatal("ERROR reading tree file: %s\n", pll_errmsg);

      if (msa.size() > tip_nodes_count)
        sysutil_fatal("Alignment file contains more sequences than expected");
      else if (msa.size() != tip_nodes_count)
        sysutil_fatal("Some taxa are missing from the alignment file");

      LOG_INFO << "Loaded user starting tree with " << tip_nodes_count << " taxa from: "
                     << opts.tree_file << endl;
      break;

    case StartingTree::random:
      /* no starting tree provided, generate a random one */
      assert(opts.command != Command::evaluate);

      LOG_INFO << "Generating a random starting tree with " << msa.size() << " taxa" << endl;

      tree = pllmod_utree_create_random(msa.size(), (const char * const*) msa.pll_msa()->label);
      break;

    case StartingTree::parsimony:
    {
      LOG_INFO << "Generating a parsimony starting tree with " << msa.size() << " taxa" << endl;

      // temporary workaround
      unsigned int num_states = part_msa.model(0).num_states();
      const unsigned int * map = part_msa.model(0).charmap();

      unsigned int score;

      tree = pllmod_utree_create_parsimony(msa.size(),
                                           msa.length(),
                                           msa.pll_msa()->label,
                                           msa.pll_msa()->sequence,
                                           msa.weights(),
                                           map,
                                           num_states,
                                           opts.simd_arch,
                                           opts.random_seed,
                                           &score);

      if (tree)
        LOG_INFO << "Parsimony score of the starting tree: " << score << endl;
      else
        sysutil_fatal_libpll();

      break;
    }
    default:
      sysutil_fatal("Unknown starting tree type: %d\n", opts.start_tree);
  }

  assert(tree != NULL);

  /* fix missing branch lengths */
  pllmod_utree_set_length_recursive(tree, RAXML_BRLEN_DEFAULT, 1);

  return tree;
}

PartitionedMSA init_part_info(const Options &opts)
{
  PartitionedMSA part_msa;

  /* check if model is a file */
  if (access(opts.model_file.c_str(), F_OK) != -1)
  {
    // read partition definitions from file
//    int retval = pll_msa_load_raxml_partfile(model_string, &useropt->part_count, &useropt->part_info);
//    if (!retval)
//      fatal_libpll();
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

  if (opts.part_count() > 1 && lg4x_count > 0 && opts.brlen_linkage == PLLMOD_TREE_BRLEN_LINKED)
  {
    throw runtime_error("LG4X model is not supported in linked branch length mode, sorry :(");
  }

  return part_msa;
}

#ifdef aaa
void PartitionedMSA::split_msa()
{
  pll_msa_t ** part_msa_list = NULL;
  if (opts.part_count() > 1)
  {
    unsigned int * site_part = get_site_part_assignment(opts.part_msa);

    /* split MSA into partitions */
    part_msa_list = pllmod_msa_split(msa.pll_msa(), site_part, opts.part_count());
  }

  /* compute per-partition stats & compress patterns if needed */
  unsigned int ** pattern_weights = NULL;
  pllmod_msa_stats_t ** stats = NULL;

  stats = (pllmod_msa_stats_t **) calloc(useropt->part_count, sizeof(pllmod_msa_stats_t *));
  if (opts.use_pattern_compression)
    pattern_weights = (unsigned int **) calloc(useropt->part_count, sizeof(unsigned int *));

  for (p = 0; p < useropt->part_count; ++p)
  {
    const partition_info_t * part_info = useropt->part_info[p];
    pll_msa_t * part_msa = part_msa_list ? part_msa_list[p] : &pll_msa;
    const unsigned int * map = get_datatype_map(part_info->data_type);
    const long num_sites = part_msa->length;

    if (!map)
      fatal("Datatype not supported: %d", part_info->data_type);

    assert(map != NULL);
    assert(msa->msa_type == RAXML_MSA_DISCRETE);

    if (opts.use_pattern_compression)
    {
      //      print_progress(0, "Compressing site patterns...\n");
      pattern_weights[p] = pll_compress_site_patterns(part_msa->sequence,
                                                      map,
                                                      part_msa->count,
                                                      &part_msa->length);
      if (!pattern_weights[p])
        fatal_libpll();
    }

    stats[p] = compute_partition_stats(part_msa, part_info->num_states, map,
                                       pattern_weights ? pattern_weights[p] : NULL);

    validate_partition_stats(useropt, part_info, stats[p]);

    /* print partition info */
    print_info("\nPartition %d: %s\n", p, part_info->part_name);
    print_info("Model: %s\n", part_info->model_str);
    print_info("Alignment sites / patterns: %ld / %ld\n", num_sites, part_msa->length);
    print_info("Gaps: %.2f %%\n", stats[p]->gap_prop * 100);
    print_info("Invariant sites: %.2f %%\n", stats[p]->inv_prop * 100);

//      print_progress(0, "Unique site patterns: %d\n", part_msa->length);
  }
}
#endif

pllmod_treeinfo_t * load_msa_and_tree(const Options &opts, PartitionedMSA& part_msa)
{
  LOG_INFO << "Loading alignment from file: " << opts.msa_file << endl;

  /* load MSA */
  auto msa = msa_load_from_file(opts.msa_file, opts.msa_format);

//  auto msa = std::make_shared<MSA>( msa_load_from_file(opts.msa_file, opts.msa_format));

  LOG_INFO << "Taxa: " << msa.size() << ", sites: " << msa.num_sites() << endl;

  /* check alignment */
//  check_msa(useropt, msa);

  part_msa.full_msa(std::move(msa));

//  LOG_INFO << "Splitting MSA... " << endl;

  part_msa.split_msa();

  if (opts.use_pattern_compression)
    part_msa.compress_patterns();

  LOG_INFO << endl;

  print_partition_info(part_msa);

  LOG_INFO << endl;

  /* load/create starting tree */
  pll_utree_t * tree = get_start_tree(opts, part_msa);

#ifdef _USE_PTHREADS
  parallel_thread_broadcast(useropt, 0, &msa, sizeof(msa_data_t *));
  parallel_thread_broadcast(useropt, 0, &tree, sizeof(pll_utree_t *));
#endif

  assert(tree != NULL);

  pll_utree_t * local_tree = opts.thread_id == 0 ? tree : pll_utree_clone(tree);

//
//  assert(msa != NULL && local_tree != NULL);
//

  pllmod_treeinfo_t * treeinfo = pllmod_treeinfo_create(local_tree, part_msa.full_msa().size(),
                                                        opts.part_count(),
                                                        opts.brlen_linkage);

  if (!treeinfo)
    sysutil_fatal("ERROR creating treeinfo structure: %s\n", pll_errmsg);

#if (defined(_USE_PTHREADS) || defined(_USE_MPI))
  pllmod_treeinfo_set_parallel_context(treeinfo, (void *) useropt, parallel_reduce_cb);
#endif

  // init partitions

  // TODO: set BRLEN and BRLEN scaler opt. flags!

  return treeinfo;
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
      auto part_msa = init_part_info(opts);
      load_msa_and_tree(opts, part_msa);
      return EXIT_SUCCESS;
    }
    case Command::none:
    default:
      LOG_INFO << "Unknown command!" << endl;
      return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
