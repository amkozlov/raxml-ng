#ifndef RAXML_OPTIONS_HPP_
#define RAXML_OPTIONS_HPP_

#include "common.h"
#include "PartitionedMSA.hpp"

struct OutputFileNames
{
  std::string log;
  std::string checkpoint;       /* checkpoint file */
  std::string start_tree;
  std::string best_tree;
  std::string best_model;
  std::string ml_trees;
  std::string bootstrap_trees;
  std::string support_tree;
};

class Options
{
public:
  Options() : cmdline(""), command(Command::none), use_tip_inner(true),
  use_pattern_compression(true), use_prob_msa(false), use_rate_scalers(false),
  optimize_model(true), optimize_brlen(true), redo_mode(false), force_mode(false),
  log_level(LogLevel::progress),
  msa_format(FileFormat::autodetect), data_type(DataType::autodetect),
  random_seed(0), start_tree(StartingTree::random), lh_epsilon(DEF_LH_EPSILON), spr_radius(-1),
  spr_cutoff(1.0), brlen_linkage(PLLMOD_TREE_BRLEN_SCALED), simd_arch(PLL_ATTRIB_ARCH_CPU),
  num_searches(1), num_bootstraps(100),
  tree_file(""), msa_file(""), model_file(""), outfile_prefix(""),
  num_threads(1), num_ranks(1)
  {};

  ~Options() = default;

  std::string cmdline;

  Command command;

  bool use_tip_inner;
  bool use_pattern_compression;
  bool use_prob_msa;
  bool use_rate_scalers;

  bool optimize_model;
  bool optimize_brlen;

  bool redo_mode;
  bool force_mode;

  LogLevel log_level;
  FileFormat msa_format;
  DataType data_type;
  long random_seed;
  StartingTree start_tree;
  double lh_epsilon;
  int spr_radius;
  double spr_cutoff;
  int brlen_linkage;
  unsigned int simd_arch;

  unsigned int num_searches;
  unsigned int num_bootstraps;

  /* I/O */
  std::string tree_file;
  std::string msa_file;
  std::string model_file;     /* could be also model string */
  std::string outfile_prefix;
  OutputFileNames outfile_names;

  /* parallelization stuff */
  unsigned int num_threads;     /* number of threads */
  unsigned int num_ranks;       /* number of MPI ranks */

  std::string simd_arch_name() const;

  std::string output_fname(const std::string& suffix) const;

  const std::string& log_file() const { return outfile_names.log; }
  const std::string& checkp_file() const { return outfile_names.checkpoint; }
  const std::string& start_tree_file() const { return outfile_names.start_tree; }
  const std::string& best_tree_file() const { return outfile_names.best_tree; }
  const std::string& best_model_file() const { return outfile_names.best_model; }
  const std::string& ml_trees_file() const { return outfile_names.ml_trees; }
  const std::string& bootstrap_trees_file() const { return outfile_names.bootstrap_trees; }
  const std::string& support_tree_file() const { return outfile_names.support_tree; }

  void set_default_outfiles();

  bool result_files_exist() const;
  void remove_result_files() const;

private:
  void set_default_outfile(std::string& fname, const std::string& suffix);
};

std::ostream& operator<<(std::ostream& stream, const Options& opts);


#endif /* RAXML_OPTIONS_HPP_ */
