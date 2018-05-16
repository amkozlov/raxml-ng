#include "Options.hpp"
//#include <stdlib.h>

using namespace std;

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
  set_default_outfile(outfile_names.best_model, "bestModel");
  set_default_outfile(outfile_names.ml_trees, "mlTrees");
  set_default_outfile(outfile_names.bootstrap_trees, "bootstraps");
  set_default_outfile(outfile_names.support_tree, "support");
  set_default_outfile(outfile_names.terrace, "terrace");
  set_default_outfile(outfile_names.binary_msa, "rba");
}

bool Options::result_files_exist() const
{
  if (nofiles_mode)
    return false;

  switch (command)
  {
    case Command::evaluate:
    case Command::search:
      return sysutil_file_exists(best_tree_file()) || sysutil_file_exists(best_model_file());
    case Command::bootstrap:
      return sysutil_file_exists(bootstrap_trees_file());
    case Command::all:
      return sysutil_file_exists(best_tree_file()) || sysutil_file_exists(bootstrap_trees_file()) ||
             sysutil_file_exists(support_tree_file()) || sysutil_file_exists(best_model_file());
    case Command::support:
      return sysutil_file_exists(support_tree_file());
    case Command::terrace:
      return sysutil_file_exists(terrace_file());
    case Command::start:
      return sysutil_file_exists(start_tree_file());
    default:
      return false;
  }
}

void Options::remove_result_files() const
{
  if (command == Command::search || command == Command::all ||
      command == Command::evaluate)
  {
    if (sysutil_file_exists(best_tree_file()))
      std::remove(best_tree_file().c_str());
    if (sysutil_file_exists(best_model_file()))
      std::remove(best_model_file().c_str());
  }

  if (command == Command::bootstrap || command == Command::all)
  {
    if (sysutil_file_exists(bootstrap_trees_file()))
      std::remove(bootstrap_trees_file().c_str());
  }
  if (command == Command::support || command == Command::all)
  {
    if (sysutil_file_exists(support_tree_file()))
      std::remove(support_tree_file().c_str());
  }

  if (command == Command::terrace)
  {
    if (sysutil_file_exists(terrace_file()))
      std::remove(terrace_file().c_str());
  }

  if (command == Command::start)
  {
    if (sysutil_file_exists(start_tree_file()))
      std::remove(start_tree_file().c_str());
  }
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

std::ostream& operator<<(std::ostream& stream, const Options& opts)
{
  stream << "RAxML-NG was called as follows:" << endl << endl << opts.cmdline << endl << endl;

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
    case Command::terrace:
      stream << "Count/enumerate trees on a phylogenetic terrace";
      break;
    case Command::check:
      stream << "Alignment validation";
      break;
    case Command::start:
      stream << "Starting tree generation";
      break;
    default:
      break;
  }
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

  if (!opts.constraint_tree_file.empty())
    stream << "  topological constraint: " << opts.constraint_tree_file << endl;

  stream << "  random seed: " << opts.random_seed << endl;
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

  stream << "  SIMD kernels: " << opts.simd_arch_name() << endl;

  stream << "  parallelization: ";
  if (opts.num_ranks > 1 && opts.num_threads > 1)
  {
    stream << "hybrid MPI+PTHREADS (" << opts.num_ranks <<  " ranks x " <<
        opts.num_threads <<  " threads)" << endl;
  }
  else if (opts.num_ranks > 1)
    stream <<  "MPI (" << opts.num_ranks << " ranks)" << endl;
  else if (opts.num_threads > 1)
    stream << "PTHREADS (" << opts.num_threads << " threads)" << endl;
  else
    stream << "NONE/sequential" << endl;

  stream << endl;

  return stream;
}




