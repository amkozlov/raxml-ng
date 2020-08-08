#include "Options.hpp"
//#include <stdlib.h>
#include <climits>

using namespace std;

Options::Options() : opt_version(RAXML_OPT_VERSION), cmdline(""), command(Command::none),
use_tip_inner(true), use_pattern_compression(true), use_prob_msa(false), use_rate_scalers(false),
use_repeats(true), use_rba_partload(true), use_energy_monitor(true),
optimize_model(true), optimize_brlen(true), force_mode(false), safety_checks(SafetyCheck::all),
redo_mode(false), nofiles_mode(false), write_interim_results(true), log_level(LogLevel::progress),
msa_format(FileFormat::autodetect), data_type(DataType::autodetect),
random_seed(0), start_trees(), lh_epsilon(DEF_LH_EPSILON), spr_radius(-1),
spr_cutoff(1.0),
brlen_linkage(PLLMOD_COMMON_BRLEN_SCALED), brlen_opt_method(PLLMOD_OPT_BLO_NEWTON_FAST),
brlen_min(RAXML_BRLEN_MIN), brlen_max(RAXML_BRLEN_MAX),
num_searches(1), terrace_maxsize(100),
num_bootstraps(1000), bootstop_criterion(BootstopCriterion::none), bootstop_cutoff(0.03),
bootstop_interval(RAXML_BOOTSTOP_INTERVAL), bootstop_permutations(RAXML_BOOTSTOP_PERMUTES),
tbe_naive(false), consense_cutoff(ConsenseCutoff::MR), tree_file(""), constraint_tree_file(""),
msa_file(""), model_file(""), weights_file(""), outfile_prefix(""),
num_threads(1), num_threads_max(1), num_ranks(1), num_workers(1), num_workers_max(UINT_MAX),
simd_arch(PLL_ATTRIB_ARCH_CPU), thread_pinning(false), load_balance_method(LoadBalancing::benoit)
{}

string Options::output_fname(const string& suffix) const
{
  if (nofiles_mode)
    return "";
  else
    return (outfile_prefix.empty() ? msa_file : outfile_prefix) + ".raxml." + suffix;
}

void Options::set_default_outfile(std::string& fname, const std::string& suffix)
{
  if (fname.empty())
    fname = output_fname(suffix);
}

void Options::set_default_outfiles()
{
  set_default_outfile(outfile_names.log, "log");
  set_default_outfile(outfile_names.checkpoint, "ckp");
  set_default_outfile(outfile_names.start_tree, "startTree");
  set_default_outfile(outfile_names.best_tree, "bestTree");
  set_default_outfile(outfile_names.best_tree_collapsed, "bestTreeCollapsed");
  set_default_outfile(outfile_names.best_model, "bestModel");
  set_default_outfile(outfile_names.partition_trees, "bestPartitionTrees");
  set_default_outfile(outfile_names.ml_trees, "mlTrees");
  set_default_outfile(outfile_names.bootstrap_trees, "bootstraps");
  set_default_outfile(outfile_names.support_tree, "support");
  set_default_outfile(outfile_names.fbp_support_tree, "supportFBP");
  set_default_outfile(outfile_names.tbe_support_tree, "supportTBE");
  set_default_outfile(outfile_names.terrace, "terrace");
  set_default_outfile(outfile_names.binary_msa, "rba");
  set_default_outfile(outfile_names.bootstrap_msa, "bootstrapMSA");
  set_default_outfile(outfile_names.rfdist, "rfDistances");
  set_default_outfile(outfile_names.cons_tree, "consensusTree");
  set_default_outfile(outfile_names.asr_tree, "ancestralTree");
  set_default_outfile(outfile_names.asr_probs, "ancestralProbs");
  set_default_outfile(outfile_names.asr_states, "ancestralStates");
  set_default_outfile(outfile_names.site_loglh, "siteLH");
  set_default_outfile(outfile_names.tmp_best_tree, "lastTree.TMP");
  set_default_outfile(outfile_names.tmp_ml_trees, "mlTrees.TMP");
  set_default_outfile(outfile_names.tmp_bs_trees, "bootstraps.TMP");
}

std::string Options::checkp_file() const
{
  if (coarse() && ParallelContext::num_ranks() > 1)
    return outfile_names.checkpoint + "." + to_string(ParallelContext::rank_id());
  else
    return outfile_names.checkpoint;
}


const std::string& Options::support_tree_file(BranchSupportMetric bsm) const
{
  if (bs_metrics.size() < 2)
    return outfile_names.support_tree;
  else
  {
    if (bsm == BranchSupportMetric::fbp)
      return outfile_names.fbp_support_tree;
    else if (bsm == BranchSupportMetric::tbe)
      return outfile_names.tbe_support_tree;
    else
      return outfile_names.support_tree;
  }
}

std::string Options::bootstrap_msa_file(size_t bsnum) const
{
  return outfile_names.bootstrap_msa.empty() ? "" :
             outfile_names.bootstrap_msa + "." + to_string(bsnum) + ".phy";
}

std::string Options::bootstrap_partition_file() const
{
  return outfile_names.bootstrap_msa.empty() ? "" :
             outfile_names.bootstrap_msa + ".partition";
}

bool Options::result_files_exist() const
{
  if (nofiles_mode)
    return false;

  switch (command)
  {
    case Command::evaluate:
    case Command::search:
      return sysutil_file_exists(best_tree_file()) || sysutil_file_exists(best_tree_collapsed_file()) ||
             sysutil_file_exists(best_model_file()) ||sysutil_file_exists(partition_trees_file());
    case Command::bootstrap:
      return sysutil_file_exists(bootstrap_trees_file());
    case Command::all:
      return sysutil_file_exists(best_tree_file()) || sysutil_file_exists(bootstrap_trees_file()) ||
             sysutil_file_exists(support_tree_file()) || sysutil_file_exists(best_model_file()) ||
             sysutil_file_exists(partition_trees_file()) || sysutil_file_exists(best_tree_collapsed_file());
    case Command::support:
      return sysutil_file_exists(support_tree_file());
    case Command::terrace:
      return sysutil_file_exists(terrace_file());
    case Command::start:
      return sysutil_file_exists(start_tree_file());
    case Command::bsmsa:
      return sysutil_file_exists(bootstrap_msa_file(1)) ||
             sysutil_file_exists(bootstrap_partition_file());
    case Command::rfdist:
      return sysutil_file_exists(rfdist_file());
    case Command::consense:
      return sysutil_file_exists(cons_tree_file());
    case Command::ancestral:
      return sysutil_file_exists(asr_tree_file()) || sysutil_file_exists(asr_probs_file()) ||
             sysutil_file_exists(asr_states_file());
    case Command::sitelh:
      return sysutil_file_exists(sitelh_file());
    default:
      return false;
  }
}

void Options::remove_result_files() const
{
  if (command == Command::search || command == Command::all ||
      command == Command::evaluate)
  {
    sysutil_file_remove(best_tree_file());
    sysutil_file_remove(best_tree_collapsed_file());
    sysutil_file_remove(best_model_file());
    sysutil_file_remove(partition_trees_file());
    sysutil_file_remove(ml_trees_file());
  }

  if (command == Command::bootstrap || command == Command::all)
    sysutil_file_remove(bootstrap_trees_file());

  if (command == Command::support || command == Command::all)
    sysutil_file_remove(support_tree_file());

  if (command == Command::terrace)
    sysutil_file_remove(terrace_file());

  if (command == Command::start)
    sysutil_file_remove(start_tree_file());

  if (command == Command::bsmsa)
  {
    size_t bsnum = 1;
    while (sysutil_file_exists(bootstrap_msa_file(bsnum)))
    {
      std::remove(bootstrap_msa_file(bsnum).c_str());
      bsnum++;
    }
    sysutil_file_remove(bootstrap_partition_file());
  }

  if (command == Command::rfdist)
    sysutil_file_remove(rfdist_file());

  if (command == Command::consense)
    sysutil_file_remove(cons_tree_file());

  if (command == Command::sitelh)
    sysutil_file_remove(sitelh_file());

  if (command == Command::ancestral)
  {
    sysutil_file_remove(asr_tree_file());
    sysutil_file_remove(asr_probs_file());
    sysutil_file_remove(asr_states_file());
  }
}

void Options::remove_tmp_files() const
{
  sysutil_file_remove(tmp_best_tree_file());
  sysutil_file_remove(tmp_ml_trees_file());
  sysutil_file_remove(tmp_bs_trees_file());
}

string Options::simd_arch_name() const
{
  switch(simd_arch)
  {
    case PLL_ATTRIB_ARCH_CPU:
      return "NONE";
      break;
    case PLL_ATTRIB_ARCH_SSE:
      return "SSE3";
      break;
    case PLL_ATTRIB_ARCH_AVX:
      return "AVX";
      break;
    case PLL_ATTRIB_ARCH_AVX2:
      return "AVX2";
      break;
    case PLL_ATTRIB_ARCH_AVX512:
      return "AVX512";
      break;
    default:
      return "UNKNOWN";
  }
}

string Options::consense_type_name() const
{
  switch(consense_cutoff)
  {
    case 0:
      return "MRE";
      break;
    case 50:
      return "MR";
      break;
    case 100:
      return "STRICT";
      break;
    default:
      return "MR" + to_string(consense_cutoff);
  }
}

std::ostream& operator<<(std::ostream& stream, const Options& opts)
{
  stream << "RAxML-NG was called at " << sysutil_fmt_time(global_timer().start_time())
         << " as follows:" << endl << endl << opts.cmdline << endl << endl;

  stream << "Analysis options:" << endl;

  stream << "  run mode: ";
  switch(opts.command)
  {
    case Command::search:
      stream << "ML tree search";
      break;
    case Command::evaluate:
      stream << "Evaluate tree likelihood";
      break;
    case Command::bootstrap:
      stream << "Bootstrapping";
      break;
    case Command::all:
      stream << "ML tree search + bootstrapping";
      break;
    case Command::support:
      stream << "Compute bipartition support";
      break;
    case Command::bsconverge:
      stream << "A posteriori bootstrap convergence test";
      break;
    case Command::bsmsa:
      stream << "Generate bootstrap replicate MSAs";
      break;
    case Command::terrace:
      stream << "Count/enumerate trees on a phylogenetic terrace";
      break;
    case Command::check:
      stream << "Alignment validation";
      break;
    case Command::parse:
      stream << "Alignment parsing and compression";
      break;
    case Command::start:
      stream << "Starting tree generation";
      break;
    case Command::rfdist:
      stream << "RF distance computation";
      break;
    case Command::consense:
      stream << "Build consensus tree";
      break;
    case Command::ancestral:
      stream << "Ancestral state reconstruction";
      break;
    case Command::sitelh:
      stream << "Per-site likelihood computation";
      break;
    default:
      break;
  }

  if (opts.command == Command::all || opts.command == Command::support)
  {
    stream << " (";
    for (auto it = opts.bs_metrics.cbegin(); it != opts.bs_metrics.cend(); ++it)
    {
      if (it != opts.bs_metrics.cbegin())
        stream << " + ";

      switch (*it)
      {
        case BranchSupportMetric::fbp:
          stream << "Felsenstein Bootstrap";
          break;
        case BranchSupportMetric::tbe:
          stream << "Transfer Bootstrap";
          break;
      }
    }
    stream << ")";
  }

  if (opts.command == Command::consense)
  {
    stream << " (" << opts.consense_type_name() << ")";
  }

  /* end of run mode line */
  stream << endl;

  stream << "  start tree(s): ";
  for (auto it = opts.start_trees.cbegin(); it != opts.start_trees.cend(); ++it)
  {
    if (it != opts.start_trees.cbegin())
      stream << " + ";

    switch(it->first)
    {
      case StartingTree::random:
        stream << "random" << " (" << it->second << ")";
        break;
      case StartingTree::parsimony:
        stream << "parsimony" << " (" << it->second << ")";
        break;
      case StartingTree::user:
        stream << "user";
        break;
    }
  }
  stream << endl;

  if (opts.command == Command::bootstrap || opts.command == Command::all ||
      opts.command == Command::bsmsa)
  {
    stream << "  bootstrap replicates: ";
    if (opts.bootstop_criterion == BootstopCriterion::none)
      stream << opts.num_bootstraps;
    else
    {
      stream << "max: " << opts.num_bootstraps << " + bootstopping (";
      switch(opts.bootstop_criterion)
      {
        case BootstopCriterion::autoFC:
          stream << "autoFC";
          break;
        case BootstopCriterion::autoMR:
          stream << "autoMR";
          break;
        case BootstopCriterion::autoMRE:
          stream << "autoMRE";
          break;
        default:
          assert(0);
      }
      stream << ", cutoff: " << opts.bootstop_cutoff << ")";
    }
    stream << endl;
  }

  if (!opts.constraint_tree_file.empty())
    stream << "  topological constraint: " << opts.constraint_tree_file << endl;

  if (!opts.weights_file.empty())
    stream << "  site weights: " << opts.weights_file << endl;

  if (!opts.outgroup_taxa.empty())
  {
    stream << "  outgroup taxa: ";
    for (auto it = opts.outgroup_taxa.cbegin(); it != opts.outgroup_taxa.cend(); ++it)
    {
      if (it != opts.outgroup_taxa.cbegin())
        stream << ",";
      stream << *it;
    }
    stream << endl;
  }

  stream << "  random seed: " << opts.random_seed << endl;

  if (opts.command == Command::bootstrap || opts.command == Command::all ||
      opts.command == Command::search || opts.command == Command::evaluate ||
      opts.command == Command::parse || opts.command == Command::ancestral)
  {
    stream << "  tip-inner: " << (opts.use_tip_inner ? "ON" : "OFF") << endl;
    stream << "  pattern compression: " << (opts.use_pattern_compression ? "ON" : "OFF") << endl;
    stream << "  per-rate scalers: " << (opts.use_rate_scalers ? "ON" : "OFF") << endl;
    stream << "  site repeats: " << (opts.use_repeats ? "ON" : "OFF") << endl;

    if (opts.command == Command::search)
    {
      if (opts.spr_radius > 0)
        stream << "  fast spr radius: " << opts.spr_radius << endl;
      else
        stream << "  fast spr radius: AUTO" << endl;

      if (opts.spr_cutoff > 0.)
        stream << "  spr subtree cutoff: " << opts.spr_cutoff << endl;
      else
        stream << "  spr subtree cutoff: OFF" << endl;
    }

    stream << "  branch lengths: ";
    if (opts.brlen_linkage == PLLMOD_COMMON_BRLEN_SCALED)
      stream << "proportional";
    else if (opts.brlen_linkage == PLLMOD_COMMON_BRLEN_UNLINKED)
      stream << "unlinked";
    else
      stream << "linked";

    stream << " (";

    if (opts.optimize_brlen)
    {
      stream << "ML estimate, algorithm: ";
      switch(opts.brlen_opt_method)
      {
        case PLLMOD_OPT_BLO_NEWTON_FAST:
          stream << "NR-FAST";
          break;
        case PLLMOD_OPT_BLO_NEWTON_SAFE:
          stream << "NR-SAFE";
          break;
        case PLLMOD_OPT_BLO_NEWTON_GLOBAL:
          stream << "NR-GLOBAL";
          break;
        case PLLMOD_OPT_BLO_NEWTON_OLDFAST:
          stream << "legacy NR-FAST";
          break;
        case PLLMOD_OPT_BLO_NEWTON_OLDSAFE:
          stream << "legacy NR-SAFE";
          break;
      }
    }
    else
      stream << "user-specified";
    stream << ")" << endl;
  }

  stream << "  SIMD kernels: " << opts.simd_arch_name() << endl;

  stream << "  parallelization: ";
  if (opts.coarse())
    stream << "coarse-grained (" << opts.num_workers << " workers), " ;
  else if (opts.num_workers_max > 1 && opts.num_workers == 0)
    stream << "coarse-grained (auto), ";

  if (opts.num_ranks > 1 && opts.num_threads > 1)
  {
    stream << "hybrid MPI+PTHREADS (" << opts.num_ranks <<  " ranks x " <<
        opts.num_threads <<  " threads)";
  }
  else if (opts.num_ranks > 1 && opts.num_threads_max > 1 && opts.num_threads == 0)
  {
    stream << "hybrid MPI (" << opts.num_ranks <<  " ranks) + PTHREADS (auto)";
  }
  else if (opts.num_ranks > 1)
    stream <<  "MPI (" << opts.num_ranks << " ranks)";
  else if (opts.num_threads > 1)
    stream << "PTHREADS (" << opts.num_threads << " threads)" ;
  else if (opts.num_threads == 0 && opts.num_threads_max > 1)
    stream << "PTHREADS (auto)" ;
  else
    stream << "NONE/sequential";

  if (opts.num_threads > 1)
    stream << ", thread pinning: " << (opts.thread_pinning ? "ON" : "OFF");
  stream << endl;

  stream << endl;

  return stream;
}




