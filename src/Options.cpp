#include "Options.hpp"

using namespace std;

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

void print_options(const Options &opts)
{
  LOG_INFO << "Analysis options:" << endl;

  LOG_INFO << "  run mode: ";
  switch(opts.command)
  {
    case Command::search:
      LOG_INFO << "Tree search";
      break;
    case Command::evaluate:
      LOG_INFO << "Evaluate tree likelihood";
      break;
    default:
      break;
  }
  LOG_INFO << endl;

  LOG_INFO << "  start tree: ";
  switch(opts.start_tree)
  {
    case StartingTree::random:
      LOG_INFO << "random";
      break;
    case StartingTree::parsimony:
      LOG_INFO << "parsimony";
      break;
    case StartingTree::user:
      LOG_INFO << "user";
      break;
  }
  LOG_INFO << endl;

  LOG_INFO << "  random seed: " << opts.random_seed << endl;
  LOG_INFO << "  tip-inner: " << (opts.use_tip_inner ? "ON" : "OFF") << endl;
  LOG_INFO << "  pattern compression: " << (opts.use_pattern_compression ? "ON" : "OFF") << endl;

  if (opts.command == Command::search)
  {
    if (opts.spr_radius > 0)
      LOG_INFO << "  fast spr radius: " << opts.spr_radius << endl;
    else
      LOG_INFO << "  fast spr radius: AUTO" << endl;

    if (opts.spr_cutoff > 0.)
      LOG_INFO << "  spr subtree cutoff: " << opts.spr_cutoff << endl;
    else
      LOG_INFO << "  spr subtree cutoff: OFF" << endl;
  }

  LOG_INFO << "  SIMD kernels: " << get_simd_arch_name(opts.simd_arch) << endl;

  LOG_INFO << "  parallelization: ";
  if (opts.num_processes > 1 && opts.num_threads > 1)
  {
    LOG_INFO << "hybrid MPI+PTHREADS (" << opts.num_processes <<  "ranks x " <<
        opts.num_threads <<  " threads)" << endl;
  }
  else if (opts.num_processes > 1)
    LOG_INFO <<  "MPI (" << opts.num_processes << " ranks)" << endl;
  else if (opts.num_threads > 1)
    LOG_INFO << "PTHREADS (" << opts.num_threads << " threads)" << endl;
  else
    LOG_INFO << "NONE/sequential" << endl;

  LOG_INFO << endl;
}



