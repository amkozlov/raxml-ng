#include "Options.hpp"
//#include <stdlib.h>

using namespace std;

string Options::output_fname(const string& suffix) const
{
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
  set_default_outfile(outfile_names.ml_trees, "mlTrees");
  set_default_outfile(outfile_names.bootstrap_trees, "bootstraps");
}

static string get_simd_arch_name(unsigned int simd_arch)
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
    default:
      break;
  }
  stream << endl;

  stream << "  start tree: ";
  switch(opts.start_tree)
  {
    case StartingTree::random:
      stream << "random";
      break;
    case StartingTree::parsimony:
      stream << "parsimony";
      break;
    case StartingTree::user:
      stream << "user";
      break;
  }
  stream << endl;

  stream << "  random seed: " << opts.random_seed << endl;
  stream << "  tip-inner: " << (opts.use_tip_inner ? "ON" : "OFF") << endl;
  stream << "  pattern compression: " << (opts.use_pattern_compression ? "ON" : "OFF") << endl;

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
  stream << (opts.optimize_brlen ? "ML estimate" : "user-specified") << " (";
  if (opts.brlen_linkage == PLLMOD_TREE_BRLEN_SCALED)
    stream << "proportional";
  else if (opts.brlen_linkage == PLLMOD_TREE_BRLEN_UNLINKED)
    stream << "unlinked";
  else
    stream << "linked";

  stream << ")" << endl;


  stream << "  SIMD kernels: " << get_simd_arch_name(opts.simd_arch) << endl;

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




