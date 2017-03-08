#ifndef RAXML_OPTIONS_HPP_
#define RAXML_OPTIONS_HPP_

#include "common.h"
#include "PartitionedMSA.hpp"

class Options
{
public:
  Options() : cmdline(""), command(Command::none), use_tip_inner(true),
  use_pattern_compression(true), use_prob_msa(false), use_rate_scalers(false),
  optimize_model(true), optimize_brlen(true), data_type(DataType::autodetect),
  random_seed(0), start_tree(StartingTree::random), lh_epsilon(DEF_LH_EPSILON), spr_radius(-1),
  spr_cutoff(1.0), brlen_linkage(PLLMOD_TREE_BRLEN_SCALED), simd_arch(PLL_ATTRIB_ARCH_CPU),
  tree_file(""), msa_file(""), model_file(""), outfile_prefix(""), checkp_file(""), log_file(""),
  log_level(LogLevel::progress), msa_format(FileFormat::autodetect), num_threads(1), num_ranks(1)
  {};

  ~Options() = default;

  std::string output_fname(const std::string& suffix) const;

  std::string cmdline;

  Command command;

  bool use_tip_inner;
  bool use_pattern_compression;
  bool use_prob_msa;
  bool use_rate_scalers;

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
  std::string checkp_file;       /* checkpoint file */
  std::string log_file;
  LogLevel log_level;
  FileFormat msa_format;

  /* parallelization stuff */
  unsigned int num_threads;     /* number of threads */
  unsigned int num_ranks;       /* number of MPI ranks */
};

std::ostream& operator<<(std::ostream& stream, const Options& opts);


#endif /* RAXML_OPTIONS_HPP_ */
