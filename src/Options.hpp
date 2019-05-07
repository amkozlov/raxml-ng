#ifndef RAXML_OPTIONS_HPP_
#define RAXML_OPTIONS_HPP_

#include "common.h"
#include "PartitionedMSA.hpp"
#include "util/SafetyCheck.hpp"

struct OutputFileNames
{
  std::string log;
  std::string checkpoint;       /* checkpoint file */
  std::string start_tree;
  std::string best_tree;
  std::string best_model;
  std::string partition_trees;
  std::string ml_trees;
  std::string bootstrap_trees;
  std::string support_tree;
  std::string tbe_support_tree;
  std::string fbp_support_tree;
  std::string terrace;
  std::string binary_msa;
  std::string bootstrap_msa;
  std::string rfdist;
  std::string cons_tree;
  std::string asr_tree;
  std::string asr_probs;
  std::string asr_states;
};

class Options
{
public:
  Options() : cmdline(""), command(Command::none), use_tip_inner(true),
  use_pattern_compression(true), use_prob_msa(false), use_rate_scalers(false), use_repeats(true),
  optimize_model(true), optimize_brlen(true), force_mode(false), safety_checks(SafetyCheck::all),
  redo_mode(false), nofiles_mode(false), log_level(LogLevel::progress),
  msa_format(FileFormat::autodetect), data_type(DataType::autodetect),
  random_seed(0), start_trees(), lh_epsilon(DEF_LH_EPSILON), spr_radius(-1),
  spr_cutoff(1.0),
  brlen_linkage(PLLMOD_COMMON_BRLEN_SCALED), brlen_opt_method(PLLMOD_OPT_BLO_NEWTON_FAST),
  brlen_min(RAXML_BRLEN_MIN), brlen_max(RAXML_BRLEN_MAX),
  num_searches(1), terrace_maxsize(100),
  num_bootstraps(1000), bootstop_criterion(BootstopCriterion::none), bootstop_cutoff(0.03),
  bootstop_interval(RAXML_BOOTSTOP_INTERVAL), bootstop_permutations(RAXML_BOOTSTOP_PERMUTES),
  tbe_naive(false), consense_cutoff(ConsenseCutoff::MR),
  tree_file(""), constraint_tree_file(""), msa_file(""), model_file(""), outfile_prefix(""),
  num_threads(1), num_ranks(1), simd_set(false), simd_arch(PLL_ATTRIB_ARCH_CPU), thread_pinning(false),
  load_balance_method(LoadBalancing::benoit), dks_off(false)
  {};

  ~Options() = default;

  std::string cmdline;

  Command command;

  bool use_tip_inner;
  bool use_pattern_compression;
  bool use_prob_msa;
  bool use_rate_scalers;
  bool use_repeats;

  bool optimize_model;
  bool optimize_brlen;

  bool force_mode;
  SafetyCheck safety_checks;

  bool redo_mode;
  bool nofiles_mode;

  LogLevel log_level;
  FileFormat msa_format;
  DataType data_type;
  long random_seed;
  StartingTreeMap start_trees;
  double lh_epsilon;
  int spr_radius;
  double spr_cutoff;
  int brlen_linkage;
  int brlen_opt_method;
  double brlen_min;
  double brlen_max;

  unsigned int num_searches;
  unsigned long long terrace_maxsize;

  unsigned int num_bootstraps;
  std::vector<BranchSupportMetric> bs_metrics;
  BootstopCriterion bootstop_criterion;
  double bootstop_cutoff;
  unsigned int bootstop_interval;
  unsigned int bootstop_permutations;

  LogElementMap precision;
  NameList outgroup_taxa;

  bool tbe_naive;

  unsigned int consense_cutoff;

  /* I/O */
  std::string tree_file;
  std::string constraint_tree_file;
  std::string msa_file;
  std::string model_file;     /* could be also model string */
  std::string outfile_prefix;
  OutputFileNames outfile_names;

  /* parallelization stuff */
  unsigned int num_threads;             /* number of threads */
  unsigned int num_ranks;               /* number of MPI ranks */
  bool simd_set;                        /* did the user specify the simd flag*/
  unsigned int simd_arch;               /* vector instruction set */
  bool thread_pinning;                     /* pin threads to cores */
  LoadBalancing load_balance_method;
  bool dks_off;

  std::string simd_arch_name() const;
  std::string consense_type_name() const;

  std::string output_fname(const std::string& suffix) const;

  const std::string& log_file() const { return outfile_names.log; }
  const std::string& checkp_file() const { return outfile_names.checkpoint; }
  const std::string& start_tree_file() const { return outfile_names.start_tree; }
  const std::string& best_tree_file() const { return outfile_names.best_tree; }
  const std::string& best_model_file() const { return outfile_names.best_model; }
  const std::string& partition_trees_file() const { return outfile_names.partition_trees; }
  const std::string& ml_trees_file() const { return outfile_names.ml_trees; }
  const std::string& bootstrap_trees_file() const { return outfile_names.bootstrap_trees; }
  const std::string& support_tree_file(BranchSupportMetric bsm = BranchSupportMetric::fbp) const;
  const std::string& terrace_file() const { return outfile_names.terrace; }
  const std::string& binary_msa_file() const { return outfile_names.binary_msa; }
  std::string bootstrap_msa_file(size_t bsnum) const;
  std::string bootstrap_partition_file() const;
  const std::string rfdist_file() const { return outfile_names.rfdist; }
  const std::string cons_tree_file() const { return outfile_names.cons_tree + consense_type_name(); }

  const std::string asr_tree_file() const { return outfile_names.asr_tree; }
  const std::string asr_probs_file() const { return outfile_names.asr_probs; }
  const std::string asr_states_file() const { return outfile_names.asr_states; }

  void set_default_outfiles();

  bool result_files_exist() const;
  void remove_result_files() const;

private:
  void set_default_outfile(std::string& fname, const std::string& suffix);
};

std::ostream& operator<<(std::ostream& stream, const Options& opts);


#endif /* RAXML_OPTIONS_HPP_ */
