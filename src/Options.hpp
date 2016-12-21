#ifndef RAXML_OPTIONS_HPP_
#define RAXML_OPTIONS_HPP_

#include "common.h"
#include "PartitionInfo.hpp"

class Options
{
public:
  Options() : command(Command::none), use_tip_inner(true), use_pattern_compression(true),
  use_prob_msa(false), optimize_model(true),  optimize_brlen(true), data_type(DataType::autodetect),
  random_seed(0), start_tree(StartingTree::random), lh_epsilon(DEF_LH_EPSILON), spr_radius(-1),
  spr_cutoff(1.0), brlen_linkage(PLLMOD_TREE_BRLEN_SCALED), simd_arch(PLL_ATTRIB_ARCH_CPU),
  tree_file(""), msa_file(""), model_file(""), outfile_prefix(""), msa_format(FileFormat::autodetect),
  num_threads(1), thread_id(0), num_processes(1), process_id(0)
  {};

  ~Options() = default;

  Command command;

  bool use_tip_inner;
  bool use_pattern_compression;
  bool use_prob_msa;

  bool optimize_model;
  bool optimize_brlen;

  DataType data_type;
  long random_seed;
  StartingTree start_tree;
  double lh_epsilon;
  int spr_radius;
  double spr_cutoff;
  int brlen_linkage;
  unsigned int simd_arch;

  /* I/O */
  std::string tree_file;
  std::string msa_file;
  std::string model_file;     /* could be also model string */
  std::string outfile_prefix;
  FileFormat msa_format;

  std::vector<PartitionInfo> part_list;
  size_t part_count() const { return part_list.size(); };

  /* parallelization stuff */
  unsigned int num_threads;     /* number of threads */
  unsigned int thread_id;       /* ID of current threads [0..num_threads-1] */
  unsigned int num_processes;   /* number of MPI ranks */
  unsigned int process_id;      /* ID of current rank [0..num_processes-1] */

};

void print_options(const Options &opts);

#endif /* RAXML_OPTIONS_HPP_ */
