#ifndef RAXML_OPTIONS_HPP_
#define RAXML_OPTIONS_HPP_

#include "common.h"
#include "PartitionedMSA.hpp"
#include "util/SafetyCheck.hpp"

constexpr int RAXML_OPT_VERSION = 1;

struct OutputFileNames
{
  std::string log;
  std::string checkpoint;       /* checkpoint file */
  std::string start_tree;
  std::string best_tree;
  std::string best_tree_collapsed;
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
  std::string site_loglh;
  std::string asr_tree;
  std::string asr_probs;
  std::string asr_states;
  std::string tmp_best_tree;
  std::string tmp_ml_trees;
  std::string tmp_bs_trees;
};

class Options
{
public:
  Options();

  Options(const Options& other) = default;
  Options& operator=(const Options& other) = default;

  ~Options() = default;

  int opt_version;  /* version of Options struct, for serialization */

  std::string cmdline;

  Command command;

  bool use_tip_inner;
  bool use_pattern_compression;
  bool use_prob_msa;
  bool use_rate_scalers;
  bool use_repeats;
  bool use_rba_partload;
  bool use_energy_monitor;

  bool optimize_model;
  bool optimize_brlen;

  bool force_mode;
  SafetyCheck safety_checks;

  bool redo_mode;
  bool nofiles_mode;
  bool write_interim_results;

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
  std::string weights_file;   /* MSA column weights / per-site LH scalers */
  std::string outfile_prefix;
  OutputFileNames outfile_names;

  /* parallelization stuff */
  unsigned int num_threads;             /* number of threads */
  unsigned int num_threads_max;         /* maximum number of threads (for auto-tuning) */
  unsigned int num_ranks;               /* number of MPI ranks */
  unsigned int num_workers;             /* number of parallel tree searches */
  unsigned int num_workers_max;         /* maximum number of parallel tree searches (for autotuning) */
  unsigned int simd_arch;               /* vector instruction set */
  bool thread_pinning;                  /* pin threads to cores */
  LoadBalancing load_balance_method;

  bool coarse() const { return num_workers > 1; };

  std::string simd_arch_name() const;
  std::string consense_type_name() const;

  std::string output_fname(const std::string& suffix) const;

  const std::string& log_file() const { return outfile_names.log; }
  std::string checkp_file() const;
  const std::string& start_tree_file() const { return outfile_names.start_tree; }
  const std::string& best_tree_file() const { return outfile_names.best_tree; }
  const std::string& best_tree_collapsed_file() const { return outfile_names.best_tree_collapsed; }
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
  const std::string sitelh_file() const { return outfile_names.site_loglh; }

  const std::string asr_tree_file() const { return outfile_names.asr_tree; }
  const std::string asr_probs_file() const { return outfile_names.asr_probs; }
  const std::string asr_states_file() const { return outfile_names.asr_states; }

  const std::string tmp_best_tree_file() const { return outfile_names.tmp_best_tree; }
  const std::string tmp_ml_trees_file() const { return outfile_names.tmp_ml_trees; }
  const std::string tmp_bs_trees_file() const { return outfile_names.tmp_bs_trees; }

  void set_default_outfiles();

  bool result_files_exist() const;
  void remove_result_files() const;
  void remove_tmp_files() const;

private:
  void set_default_outfile(std::string& fname, const std::string& suffix);
};

std::ostream& operator<<(std::ostream& stream, const Options& opts);


#endif /* RAXML_OPTIONS_HPP_ */
