#include "CommandLineParser.hpp"

#include <getopt.h>

#ifdef _RAXML_PTHREADS
#include <thread>
#endif

using namespace std;

static struct option long_options[] =
{
  {"help",               no_argument,       0, 0 },  /*  0 */
  {"version",            no_argument,       0, 0 },  /*  1 */
  {"evaluate",           no_argument,       0, 0 },  /*  2 */
  {"search",             no_argument,       0, 0 },  /*  3 */

  {"msa",                required_argument, 0, 0 },  /*  4 */
  {"tree",               required_argument, 0, 0 },  /*  5 */
  {"prefix",             required_argument, 0, 0 },  /*  6 */
  {"model",              required_argument, 0, 0 },  /*  7 */
  {"data-type",          required_argument, 0, 0 },  /*  8 */

  {"opt-model",          required_argument, 0, 0 },  /*  9 */
  {"opt-branches",       required_argument, 0, 0 },  /*  10 */
  {"prob-msa",           required_argument, 0, 0 },  /*  11 */
  {"pat-comp",           required_argument, 0, 0 },  /*  12 */
  {"tip-inner",          required_argument, 0, 0 },  /*  13 */
  {"brlen",              required_argument, 0, 0 },  /*  14 */
  {"spr-radius",         required_argument, 0, 0 },  /*  15 */
  {"spr-cutoff",         required_argument, 0, 0 },  /*  16 */
  {"lh-epsilon",         required_argument, 0, 0 },  /*  17 */

  {"seed",               required_argument, 0, 0 },  /*  18 */
  {"threads",            required_argument, 0, 0 },  /*  19 */
  {"simd",               required_argument, 0, 0 },  /*  20 */

  {"msa-format",         required_argument, 0, 0 },  /*  21 */
  {"rate-scalers",       required_argument, 0, 0 },  /*  22 */
  {"log",                required_argument, 0, 0 },  /*  23 */

  {"bootstrap",          no_argument,       0, 0 },  /*  24 */
  {"all",                no_argument,       0, 0 },  /*  25 */
  {"bs-trees",           required_argument, 0, 0 },  /*  26 */
  {"redo",               no_argument,       0, 0 },  /*  27 */
  {"force",              optional_argument, 0, 0 },  /*  28 */

  {"site-repeats",       required_argument, 0, 0 },  /*  29 */
  {"support",            no_argument,       0, 0 },  /*  30 */
  {"terrace",            no_argument,       0, 0 },  /*  31 */
  {"terrace-maxsize",    required_argument, 0, 0 },  /*  32 */
  {"check",              no_argument,       0, 0 },  /*  33 */
  {"parse",              no_argument,       0, 0 },  /*  34 */

  {"blopt",              required_argument, 0, 0 },  /*  35 */
  {"blmin",              required_argument, 0, 0 },  /*  36 */
  {"blmax",              required_argument, 0, 0 },  /*  37 */

  {"tree-constraint",    required_argument, 0, 0 },  /*  38 */
  {"nofiles",            optional_argument, 0, 0 },  /*  39 */
  {"start",              no_argument,       0, 0 },  /*  40 */
  {"loglh",              no_argument,       0, 0 },  /*  41 */
  {"precision",          required_argument, 0, 0 },  /*  42 */
  {"outgroup",           required_argument, 0, 0 },  /*  43 */

  {"bs-cutoff",          required_argument, 0, 0 },  /*  44 */
  {"bsconverge",         no_argument,       0, 0 },  /*  45 */
  {"extra",              required_argument, 0, 0 },  /*  46 */
  {"bs-metric",          required_argument, 0, 0 },  /*  47 */

  {"search1",            no_argument, 0, 0 },        /*  48 */
  {"bsmsa",              no_argument, 0, 0 },        /*  49 */
  {"rfdist",             optional_argument, 0, 0 },  /*  50 */
  {"rf",                 optional_argument, 0, 0 },  /*  51 */
  {"consense",           optional_argument, 0, 0 },  /*  52 */
  {"ancestral",          optional_argument, 0, 0 },  /*  53 */

  {"workers",            required_argument, 0, 0 },  /*  54 */
  {"sitelh",             no_argument, 0, 0 },        /*  55 */
  {"site-weights",       required_argument, 0, 0 },  /*  56 */

  { 0, 0, 0, 0 }
};

static std::string get_cmdline(int argc, char** argv)
{
  ostringstream s;
  for (int i = 0; i < argc; ++i)
    s << argv[i] << (i < argc-1 ? " " : "");
  return s.str();
}

void CommandLineParser::check_options(Options &opts)
{
  /* check for mandatory options for each command */
  if (opts.command == Command::evaluate || opts.command == Command::search ||
      opts.command == Command::bootstrap || opts.command == Command::all ||
      opts.command == Command::terrace || opts.command == Command::check ||
      opts.command == Command::parse || opts.command == Command::start ||
      opts.command == Command::ancestral)
  {
    if (opts.msa_file.empty())
      throw OptionException("You must specify a multiple alignment file with --msa switch");
  }

  if (opts.command == Command::evaluate || opts.command == Command::support ||
      opts.command == Command::terrace || opts.command == Command::rfdist ||
      opts.command == Command::sitelh || opts.command == Command::ancestral)
  {
    if (opts.tree_file.empty())
      throw OptionException("Please provide a valid Newick file as an argument of --tree option.");
  }

  if (opts.command == Command::start && !opts.tree_file.empty())
  {
    throw OptionException("You specified a user starting tree) for the starting tree generation "
        "command, which does not make any sense!\n"
        "Please choose whether you want to generate parsimony or random starting trees!");
  }

  if (opts.command == Command::support || opts.command == Command::bsconverge)
  {
    if (opts.outfile_names.bootstrap_trees.empty())
    {
      throw OptionException("You must specify a Newick file with replicate trees, e.g., "
          "--bs-trees bootstrap.nw");
    }
  }

  if (opts.command == Command::support || opts.command == Command::rfdist)
  {
    assert(!opts.tree_file.empty());

    if (opts.outfile_prefix.empty())
      opts.outfile_prefix = opts.tree_file;
  }

  if (opts.command == Command::bsconverge)
  {
    assert(!opts.outfile_names.bootstrap_trees.empty());

    if (opts.bootstop_criterion == BootstopCriterion::none)
      opts.bootstop_criterion = BootstopCriterion::autoMRE;

    if (opts.outfile_prefix.empty())
      opts.outfile_prefix = opts.outfile_names.bootstrap_trees;
  }

  if (opts.command == Command::bsmsa)
  {
    if (!opts.num_bootstraps)
    {
      throw OptionException("You must specify the desired number of replicate MSAs, e.g., "
          "--bs-trees 100");
    }
  }

  if (opts.num_bootstraps > 0 && opts.command != Command::bsmsa &&
      opts.command != Command::bootstrap && opts.command != Command::all)
  {
    throw OptionException("You specified the number of bootstrap replicates with --bs-trees option, "
        "but the current command does not perform bootstrapping.\n"
        "Did you forget --all option?");
  }

  if (opts.simd_arch > sysutil_simd_autodetect())
  {
    if (opts.force_mode)
      pll_hardware_ignore();
    else
    {
      throw OptionException("Cannot detect " + opts.simd_arch_name() +
                            " instruction set on your system. If you are absolutely sure "
                            "it is supported, please use --force option to disable this check.");
    }
  }
}

void CommandLineParser::compute_num_searches(Options &opts)
{
  if (opts.command == Command::search || opts.command == Command::all ||
      opts.command == Command::evaluate || opts.command == Command::start ||
      opts.command == Command::ancestral || opts.command == Command::sitelh)
  {
    if (opts.start_trees.empty())
    {
      /* parsimony starting trees are not supported with topological constraint! */
      if (opts.constraint_tree_file.empty())
      {
        opts.start_trees[StartingTree::random] = 10;
        opts.start_trees[StartingTree::parsimony] = 10;
      }
      else
        opts.start_trees[StartingTree::random] = 20;
    }
    else
    {
      auto def_tree_count = 10;
      for (auto& it: opts.start_trees)
      {
        if (it.first == StartingTree::user)
          it.second = 1;
        else
          it.second = it.second > 0 ? it.second : def_tree_count;
      }
    }

    for (const auto& it: opts.start_trees)
      opts.num_searches += it.second;
  }
}

void CommandLineParser::parse_start_trees(Options &opts, const string& arg)
{
  auto start_trees = split_string(arg, ',');
  for (const auto& st_tree: start_trees)
  {
    StartingTree st_tree_type;
    unsigned int num_searches = 0;
    if (st_tree == "rand" || st_tree == "random" ||
        sscanf(st_tree.c_str(), "rand{%u}", &num_searches) == 1 ||
        sscanf(st_tree.c_str(), "random{%u}", &num_searches) == 1)
    {
      st_tree_type = StartingTree::random;
    }
    else if (st_tree ==  "pars" || st_tree == "parsimony" ||
        sscanf(st_tree.c_str(), "pars{%u}", &num_searches) == 1 ||
        sscanf(st_tree.c_str(), "parsimony{%u}", &num_searches) == 1)
    {
      st_tree_type = StartingTree::parsimony;
    }
    else
    {
      opts.tree_file += (opts.tree_file.empty() ? "" : ",") + st_tree;
      st_tree_type = StartingTree::user;
    }
    if (!opts.start_trees.count(st_tree_type) || num_searches > 0)
      opts.start_trees[st_tree_type] = num_searches;
  }
}

void CommandLineParser::parse_options(int argc, char** argv, Options &opts)
{
  opts.cmdline = get_cmdline(argc, argv);

  /* if no command specified, default to --search (or --help if no args were given) */
  opts.command = (argc > 1) ? Command::search : Command::help;
  opts.start_trees.clear();
  opts.random_seed = (long)time(NULL);

  /* compress alignment patterns by default */
  opts.use_pattern_compression = true;

  /* do not use tip-inner case optimization by default */
  opts.use_tip_inner = false;
  /* use site repeats */
  opts.use_repeats = true;

  /* do not use per-rate-category CLV scalers */
  opts.use_rate_scalers = false;

  /* use probabilistic MSA _if available_ (e.g. CATG file was provided) */
  opts.use_prob_msa = true;

  /* use RBA partial loading whenever appropriate/possible */
  opts.use_rba_partload = true;

  /* optimize model and branch lengths */
  opts.optimize_model = true;
  opts.optimize_brlen = true;

  /* initialize LH epsilon with default value */
  opts.lh_epsilon = DEF_LH_EPSILON;

  /* default: autodetect best SPR radius */
  opts.spr_radius = -1;
  opts.spr_cutoff = 1.0;

  /* bootstrapping / bootstopping */
  opts.bs_metrics.push_back(BranchSupportMetric::fbp);
  opts.bootstop_criterion = BootstopCriterion::autoMRE;
  opts.bootstop_cutoff = RAXML_BOOTSTOP_CUTOFF;
  opts.bootstop_interval = RAXML_BOOTSTOP_INTERVAL;
  opts.bootstop_permutations = RAXML_BOOTSTOP_PERMUTES;

  /* default: linked branch lengths */
  opts.brlen_linkage = PLLMOD_COMMON_BRLEN_SCALED;
  opts.brlen_min = RAXML_BRLEN_MIN;
  opts.brlen_max = RAXML_BRLEN_MAX;

  /* by default, autodetect optimal number of threads and workers for the dataset */
  opts.num_threads = 0;
  opts.num_workers = 0;

  /* max #threads = # available CPU cores */
#if !defined(_RAXML_PTHREADS)
  opts.num_threads = 1;
#elif !defined(_RAXML_MPI)
  opts.num_threads_max = std::max(1u, sysutil_get_cpu_cores());
#else
  opts.num_threads_max = std::max(1u, (unsigned int) (sysutil_get_cpu_cores() / ParallelContext::ranks_per_node()));
#endif

#if defined(_RAXML_MPI)
  opts.thread_pinning = ParallelContext::ranks_per_node() == 1 ? true : false;
#else
  opts.thread_pinning = false;
#endif

  opts.model_file = "";
  opts.tree_file = "";

  // autodetect CPU instruction set and use respective SIMD kernels
  opts.simd_arch = sysutil_simd_autodetect();
  opts.load_balance_method = LoadBalancing::benoit;

  opts.num_searches = 0;
  opts.num_bootstraps = 0;

  opts.force_mode = false;
  opts.safety_checks = SafetyCheck::all;

  opts.redo_mode = false;
  opts.nofiles_mode = false;

  opts.tbe_naive = false;

  bool log_level_set = false;

  int option_index = 0;
  int c;
  int num_commands = 0;

  /* getopt_long_only() uses this global variable to track progress;
   * need this re-initialization to make function re-enterable... */
  optind = 0;

  while ((c = getopt_long_only(argc, argv, "", long_options, &option_index)) == 0)
  {
    /* optional arguments in getopt() are broken, this hack is needed fix them... */
    if (!optarg
        && optind < argc // make sure optind is valid
        && long_options[option_index].has_arg == optional_argument // and has optional argument
        && NULL != argv[optind] // make sure it's not a null string
        && '\0' != argv[optind][0] // ... or an empty string
        && '-' != argv[optind][0] // ... or another option
       )
    {
      // update optind so the next getopt_long invocation skips argv[optind]
      optarg = argv[optind++];
    }

    switch (option_index)
    {
      case 0:
        opts.command = Command::help;
        num_commands++;
        break;

      case 1:
        opts.command = Command::version;
        num_commands++;
        break;

      case 2:
        opts.command = Command::evaluate;
        num_commands++;
        break;

      case 3:
        opts.command = Command::search;
        num_commands++;
        break;

      case 4: /* alignment file */
        opts.msa_file = optarg;
        break;

      case 5: /* starting tree */
        parse_start_trees(opts, optarg);
        break;

      case 6: /* set prefix for output files */
        opts.outfile_prefix = optarg;
        break;

      case 7:  /* model */
        opts.model_file = optarg;
        break;

      case 8:  /* data-type */
        if (strcasecmp(optarg, "dna") == 0)
          opts.data_type = DataType::dna;
        else if (strcasecmp(optarg, "aa") == 0)
          opts.data_type = DataType::protein;
        else if (strcasecmp(optarg, "binary") == 0 || strcasecmp(optarg, "bin") == 0)
          opts.data_type = DataType::binary;
        else if (strcasecmp(optarg, "diploid10") == 0)
          opts.data_type = DataType::genotype10;
        else if (strcasecmp(optarg, "multi") == 0)
          opts.data_type = DataType::multistate;
        else if (strcasecmp(optarg, "auto") == 0)
          opts.data_type = DataType::autodetect;
        else
          throw InvalidOptionValueException("Unknown data type: " + string(optarg));
        break;

      case 9: /* optimize model */
        opts.optimize_model = !optarg || (strcasecmp(optarg, "off") != 0);
        break;

      case 10: /* optimize branches */
        opts.optimize_brlen = !optarg || (strcasecmp(optarg, "off") != 0);
        break;

      case 11:  /* prob-msa = use probabilitic MSA */
        if (!optarg || (strcasecmp(optarg, "off") != 0))
        {
          opts.use_prob_msa = true;
          opts.use_pattern_compression = false;
          opts.use_tip_inner = false;
          opts.use_repeats = false;
        }
        else
          opts.use_prob_msa = false;
        break;

      case 12: /* disable pattern compression */
        opts.use_pattern_compression = !optarg || (strcasecmp(optarg, "off") != 0);
        break;

      case 13: /* disable tip-inner optimization */
        opts.use_tip_inner = !optarg || (strcasecmp(optarg, "off") != 0);
        if (opts.use_tip_inner)
          opts.use_repeats = false;
        break;

      case 14: /* branch length linkage mode */
        if (strcasecmp(optarg, "scaled") == 0 || strcasecmp(optarg, "proportional") == 0)
          opts.brlen_linkage = PLLMOD_COMMON_BRLEN_SCALED;
        else if (strcasecmp(optarg, "linked") == 0)
          opts.brlen_linkage = PLLMOD_COMMON_BRLEN_LINKED;
        else if (strcasecmp(optarg, "unlinked") == 0)
          opts.brlen_linkage = PLLMOD_COMMON_BRLEN_UNLINKED;
        else
          throw InvalidOptionValueException("Unknown branch linkage mode: " + string(optarg));
        break;

      case 15:  /* spr-radius = maximum radius for fast SPRs */
        if (sscanf(optarg, "%d", &opts.spr_radius) != 1 || opts.spr_radius <= 0)
        {
          throw InvalidOptionValueException("Invalid SPR radius: " + string(optarg) +
                                            ", please provide a positive integer!");
        }
        break;
      case 16:  /* spr-cutoff = relative LH cutoff to discard subtrees */
        if (strcasecmp(optarg, "off") == 0)
        {
          opts.spr_cutoff = 0.;
        }
        else if (sscanf(optarg, "%lf", &opts.spr_cutoff) != 1)
        {
          throw InvalidOptionValueException("Invalid SPR cutoff: " + string(optarg) +
                                            ", please provide a real number!");
        }
        break;

      case 17: /* LH epsilon */
        if(sscanf(optarg, "%lf", &opts.lh_epsilon) != 1 || opts.lh_epsilon < 0.)
          throw InvalidOptionValueException("Invalid LH epsilon parameter value: " +
                                            string(optarg) +
                                            ", please provide a positive real number.");
        break;

      case 18: /* random seed */
        opts.random_seed = atol(optarg);
        break;

      case 19:  /* number of threads */
        if (strncasecmp(optarg, "auto", 4) == 0)
        {
          opts.num_threads = 0;
          sscanf(optarg, "auto{%u}", &opts.num_threads_max);
        }
        else if (sscanf(optarg, "%u", &opts.num_threads) != 1 || opts.num_threads == 0)
        {
          throw InvalidOptionValueException("Invalid number of threads: %s " + string(optarg) +
                                            ", please provide a positive integer number or `auto`!");
        }
        break;
      case 20: /* SIMD instruction set */
        if (strcasecmp(optarg, "none") == 0 || strcasecmp(optarg, "scalar") == 0)
        {
          opts.simd_arch = PLL_ATTRIB_ARCH_CPU;
        }
        else if (strcasecmp(optarg, "sse3") == 0 || strcasecmp(optarg, "sse") == 0)
        {
          opts.simd_arch = PLL_ATTRIB_ARCH_SSE;
        }
        else if (strcasecmp(optarg, "avx") == 0)
        {
          opts.simd_arch = PLL_ATTRIB_ARCH_AVX;
        }
        else if (strcasecmp(optarg, "avx2") == 0)
        {
          opts.simd_arch = PLL_ATTRIB_ARCH_AVX2;
        }
        else
        {
          throw InvalidOptionValueException("Unknown SIMD instruction set: " + string(optarg));
        }
        break;
      case 21: /* MSA file format */
        if (strcasecmp(optarg, "auto") == 0 )
        {
          opts.msa_format = FileFormat::autodetect;
        }
        else if (strcasecmp(optarg, "fasta") == 0)
        {
          opts.msa_format = FileFormat::fasta;
        }
        else if (strcasecmp(optarg, "phylip") == 0)
        {
          opts.msa_format = FileFormat::phylip;
        }
        else if (strcasecmp(optarg, "vcf") == 0)
        {
          opts.msa_format = FileFormat::vcf;
        }
        else if (strcasecmp(optarg, "catg") == 0)
        {
          opts.msa_format = FileFormat::catg;
        }
        else if (strcasecmp(optarg, "binary") == 0)
        {
          opts.msa_format = FileFormat::binary;
        }
        else
        {
          throw InvalidOptionValueException("Unknown MSA file format: " + string(optarg));
        }
        break;
      case 22: /* enable per-rate scalers */
        opts.use_rate_scalers = !optarg || (strcasecmp(optarg, "off") != 0);
        break;
      case 23: /* log level */
        log_level_set = true;
        if (strcasecmp(optarg, "error") == 0 )
          opts.log_level = LogLevel::error;
        else if (strcasecmp(optarg, "warning") == 0)
          opts.log_level = LogLevel::warning;
        else if (strcasecmp(optarg, "result") == 0)
          opts.log_level = LogLevel::result;
        else if (strcasecmp(optarg, "info") == 0)
          opts.log_level = LogLevel::info;
        else if (strcasecmp(optarg, "progress") == 0)
          opts.log_level = LogLevel::progress;
        else if (strcasecmp(optarg, "verbose") == 0)
          opts.log_level = LogLevel::verbose;
        else if (strcasecmp(optarg, "debug") == 0)
          opts.log_level = LogLevel::debug;
        else
          throw InvalidOptionValueException("Unknown log level: " + string(optarg));
        break;
      case 24:
        opts.command = Command::bootstrap;
        num_commands++;
        break;
      case 25:
        opts.command = Command::all;
        num_commands++;
        break;
      case 26:  /* number of bootstrap replicates */
        opts.bootstop_criterion = BootstopCriterion::none;
        if (sysutil_file_exists(optarg) && !sysutil_isnumber(optarg))
        {
          opts.outfile_names.bootstrap_trees = optarg;
        }
        else if (strncasecmp(optarg, "autoMRE", 7) == 0)
        {
          string optstr = optarg;
          std::transform(optstr.begin(), optstr.end(), optstr.begin(), ::tolower);
          opts.bootstop_criterion = BootstopCriterion::autoMRE;
          if (sscanf(optstr.c_str(), "automre{%u}", &opts.num_bootstraps) != 1)
            opts.num_bootstraps = 1000;
        }
        else if (sscanf(optarg, "%u", &opts.num_bootstraps) != 1 || opts.num_bootstraps == 0)
        {
          throw InvalidOptionValueException("Invalid number of num_bootstraps: " + string(optarg) +
              ", please provide a positive integer number!");
        }
        break;
      case 27:
        opts.redo_mode = true;
        break;
      case 28:
        opts.force_mode = true;
        if (!optarg || strlen(optarg) == 0)
        {
          opts.safety_checks = SafetyCheck::none;
        }
        else
        {
          try
          {
            opts.safety_checks.unset(optarg);
          }
          catch(runtime_error& e)
          {
            throw InvalidOptionValueException("Invalid --force option: " + string(optarg));
          }
        }
        break;
      case 29:  /* site repeats */
        if (!optarg || (strcasecmp(optarg, "off") != 0))
        {
          opts.use_repeats = true;
          opts.use_tip_inner = false;
        }
        else
          opts.use_repeats = false;
        break;
      case 30: /* support */
        opts.command = Command::support;
        num_commands++;
        break;
      case 31: /* terrace */
#ifdef _RAXML_TERRAPHAST
        opts.command = Command::terrace;
        opts.brlen_linkage = PLLMOD_COMMON_BRLEN_UNLINKED;
        num_commands++;
#else
        throw  OptionException("Unsupported command: --terrace.\n"
            "Please build RAxML-NG with TERRAPHAST support.");
#endif
        break;
      case 32:  /* maximum number of terrace trees to output */
        if (sscanf(optarg, "%llu", &opts.terrace_maxsize) != 1 || opts.terrace_maxsize == 0)
        {
          throw InvalidOptionValueException("Invalid number of terrace trees to output: "
              + string(optarg) + ", please provide a positive integer number!");
        }
        break;
      case 33: /* check */
        opts.command = Command::check;
        num_commands++;
        break;
      case 34: /* parse */
        opts.command = Command::parse;
        num_commands++;
        break;
      case 35: /* branch length optimization method */
        if (strcasecmp(optarg, "nr_fast") == 0)
          opts.brlen_opt_method = PLLMOD_OPT_BLO_NEWTON_FAST;
        else if (strcasecmp(optarg, "nr_oldfast") == 0)
          opts.brlen_opt_method = PLLMOD_OPT_BLO_NEWTON_OLDFAST;
        else if (strcasecmp(optarg, "nr_safe") == 0)
          opts.brlen_opt_method = PLLMOD_OPT_BLO_NEWTON_SAFE;
        else if (strcasecmp(optarg, "nr_oldsafe") == 0)
          opts.brlen_opt_method = PLLMOD_OPT_BLO_NEWTON_OLDSAFE;
        else if (strcasecmp(optarg, "nr_fallback") == 0)
          opts.brlen_opt_method = PLLMOD_OPT_BLO_NEWTON_FALLBACK;
        else if (strcasecmp(optarg, "nr_global") == 0)
          opts.brlen_opt_method = PLLMOD_OPT_BLO_NEWTON_GLOBAL;
        else if (strcasecmp(optarg, "off") == 0 || strcasecmp(optarg, "none") == 0)
          opts.optimize_brlen = false;
        else
          throw InvalidOptionValueException("Unknown branch length optimization method: " + string(optarg));
        break;
      case 36: /* min brlen */
        if(sscanf(optarg, "%lf", &opts.brlen_min) != 1 || opts.brlen_min <= 0.)
        {
          throw InvalidOptionValueException("Invalid minimum branch length value: " +
                                            string(optarg) +
                                            ", please provide a positive real number.");
        }
        if (opts.precision.empty() && opts.brlen_min < 1.)
          opts.precision[LogElement::brlen] = ceil(-1 * log10(opts.brlen_min));
        break;
      case 37: /* max brlen */
        if(sscanf(optarg, "%lf", &opts.brlen_max) != 1 || opts.brlen_max <= 0.)
        {
          throw InvalidOptionValueException("Invalid maximum branch length value: " +
                                            string(optarg) +
                                            ", please provide a positive real number.");
        }
        break;
      case 38: /* constraint tree */
        opts.constraint_tree_file = optarg;
        break;
      case 39: /* no output files (only console output) */
        if (!optarg || strlen(optarg) == 0)
        {
          opts.nofiles_mode = true;
          opts.write_interim_results = false;
        }
        else
        {
          auto files = split_string(optarg, ',');
          for (const auto& f: files)
          {
            if (f == "interim")
              opts.write_interim_results = false;
            else
              throw InvalidOptionValueException("Invalid --nofiles option: " + f);
          }
        }
        break;
      case 40: /* start tree generation */
        opts.command = Command::start;
        num_commands++;
        break;
      case 41: /* compute tree logLH w/o optimization */
        opts.command = Command::evaluate;
        opts.optimize_model = false;
        opts.optimize_brlen = false;
        opts.nofiles_mode = true;
        opts.log_level = LogLevel::result;
        log_level_set = true;
        num_commands++;
        break;
      case 42:  /* precision */
        {
          unsigned int prec = 0;
          if (sscanf(optarg, "%u", &prec) != 1 || prec == 0)
          {
            throw InvalidOptionValueException("Invalid precision: " + string(optarg) +
                                              ", please provide a positive integer number!");
          }
          else
          {
            opts.precision.clear();
            opts.precision[LogElement::all] = prec;
          }
        }
        break;
      case 43:  /* outgroup */
        opts.outgroup_taxa = split_string(optarg, ',');
        if (opts.outgroup_taxa.empty())
        {
          throw InvalidOptionValueException("Invalid outgroup: %s " + string(optarg));
        }
        break;
      case 44: /* bootstopping cutoff */
        if(sscanf(optarg, "%lf", &opts.bootstop_cutoff) == 1 &&
           opts.bootstop_cutoff >= 0. && opts.bootstop_cutoff <= 1.0)
        {
          if (opts.bootstop_criterion == BootstopCriterion::none)
            opts.bootstop_criterion = BootstopCriterion::autoMRE;
        }
        else
        {
          throw InvalidOptionValueException("Invalid bootstopping cutoff value: " +
                                            string(optarg) +
                                            ", please provide a number between 0.0 and 1.0.");
        }
        break;
      case 45: /* bootstrap convergence test */
        opts.command = Command::bsconverge;
        num_commands++;
        if (opts.bootstop_criterion == BootstopCriterion::none)
          opts.bootstop_criterion = BootstopCriterion::autoMRE;
        break;
      case 46: /* extra options */
        {
          auto extra_opts = split_string(optarg, ',');
          for (auto& eopt: extra_opts)
          {
            if (eopt == "lb-naive")
              opts.load_balance_method = LoadBalancing::naive;
            else if (eopt == "lb-kassian")
              opts.load_balance_method = LoadBalancing::kassian;
            else if (eopt == "lb-benoit")
              opts.load_balance_method = LoadBalancing::benoit;
            else if (eopt == "thread-pin")
              opts.thread_pinning = true;
            else if (eopt == "thread-nopin")
              opts.thread_pinning = false;
            else if (eopt == "tbe-naive")
              opts.tbe_naive = true;
            else if (eopt == "tbe-nature")
              opts.tbe_naive = false;
            else if (eopt == "rba-nopartload")
              opts.use_rba_partload = false;
            else if (eopt == "energy-off")
              opts.use_energy_monitor = false;
            else
              throw InvalidOptionValueException("Unknown extra option: " + string(eopt));
          }
        }
        break;

      case 47: /* branch support metric */
        {
          opts.bs_metrics.clear();
          auto methods = split_string(optarg, ',');
          for (const auto& m: methods)
          {
            if (strncasecmp(m.c_str(), "fbp", 3) == 0)
            {
              opts.bs_metrics.push_back(BranchSupportMetric::fbp);
            }
            else if (strncasecmp(m.c_str(), "tbe", 3) == 0)
            {
              opts.bs_metrics.push_back(BranchSupportMetric::tbe);
            }
            else
            {
              throw InvalidOptionValueException("Unknown branch support metric: " + string(optarg));
            }
          }
        }
        break;

      case 48: /* search from a single starting tree */
        opts.command = Command::search;
        if (opts.start_trees.empty())
          opts.start_trees[StartingTree::random] = 1;
        else
        {
          if (opts.start_trees.count(StartingTree::random))
            opts.start_trees[StartingTree::random] = 1;
          if (opts.start_trees.count(StartingTree::parsimony))
            opts.start_trees[StartingTree::parsimony] = 1;
        }
        num_commands++;
        break;
      case 49: /* generate bootstrap replicate MSAs */
        opts.command = Command::bsmsa;
        num_commands++;
        break;

      case 50: /* compute RF distance */
        opts.command = Command::rfdist;
        num_commands++;
        if (optarg)
          parse_start_trees(opts, optarg);
        break;

      case 51: /* compute and print average RF distance w/o noise */
        opts.command = Command::rfdist;
        opts.nofiles_mode = true;
        opts.log_level = LogLevel::result;
        log_level_set = true;
        num_commands++;
        if (optarg)
          parse_start_trees(opts, optarg);
        break;

      case 52: /* build consensus tree */
        opts.command = Command::consense;
        num_commands++;
        if (optarg)
        {
          if (strcasecmp(optarg, "mr") == 0)
            opts.consense_cutoff = ConsenseCutoff::MR;
          else if (strcasecmp(optarg, "mre") == 0)
            opts.consense_cutoff = ConsenseCutoff::MRE;
          else if (strcasecmp(optarg, "strict") == 0)
            opts.consense_cutoff = ConsenseCutoff::strict;
          else if (sscanf(optarg, "%*[Mm]%*[Rr]%u", &opts.consense_cutoff) != 1 ||
                   opts.consense_cutoff < 50 || opts.consense_cutoff > 100)
          {
            auto errmsg = "Invalid consensus type or threshold value: " +
                          string(optarg) + "\n" +
                          "Allowed values: MR, MRE, STRICT or MR<n>, where 50 <= n <= 100.";
            throw  InvalidOptionValueException(errmsg);
          }
        }
        else
          opts.consense_cutoff = ConsenseCutoff::MR;
        break;

      case 53: /* ancestral state reconstruction */
        opts.command = Command::ancestral;
        opts.use_pattern_compression = false;
        opts.use_repeats = false;
        opts.use_tip_inner = true;
        if (opts.precision.empty())
          opts.precision[LogElement::other] = 5;
        num_commands++;
        break;

      case 54:  /* number of workers (=parallel tree searches) */
        if (strncasecmp(optarg, "auto", 4) == 0)
        {
          opts.num_workers = 0;
          sscanf(optarg, "auto{%u}", &opts.num_workers_max);
        }
        else if (sscanf(optarg, "%u", &opts.num_workers) != 1 || opts.num_workers == 0)
        {
          throw InvalidOptionValueException("Invalid number of workers: " + string(optarg) +
                                            ", please provide a positive integer number or 'auto'!");
        }
        break;

      case 55: /* per-site log-likelihoods */
        opts.command = Command::sitelh;
        num_commands++;
        break;

      case 56: /* site weights */
        opts.weights_file = optarg;
        break;


      default:
        throw  OptionException("Internal error in option parsing");
    }
  }

  if (c != -1)
    exit(EXIT_FAILURE);

  /* if more than one independent command, fail */
  if (num_commands > 1)
    throw OptionException("More than one command specified");

  check_options(opts);

  if ((opts.command == Command::bootstrap || opts.command == Command::all) &&
      opts.num_bootstraps == 0)
  {
    opts.num_bootstraps = (opts.bootstop_criterion == BootstopCriterion::none) ? 100 : 1000;
  }

  compute_num_searches(opts);

  /* set default log output level  */
  if (!log_level_set)
  {
    opts.log_level = (opts.num_searches > 20 || opts.num_bootstraps > 1) ?
        LogLevel::info : LogLevel::progress;
  }

  /* set default  names for output files */
  opts.set_default_outfiles();
}

void CommandLineParser::print_help()
{
  cout << "Usage: raxml-ng [OPTIONS]\n";

  cout << "\n"
            "Commands (mutually exclusive):\n"
            "  --help                                     display help information\n"
            "  --version                                  display version information\n"
            "  --evaluate                                 evaluate the likelihood of a tree (with model+brlen optimization)\n"
            "  --search                                   ML tree search (default: 10 parsimony + 10 random starting trees)\n"
            "  --bootstrap                                bootstrapping (default: use bootstopping to auto-detect #replicates)\n"
            "  --all                                      all-in-one (ML search + bootstrapping)\n"
            "  --support                                  compute bipartition support for a given reference tree (e.g., best ML tree)\n"
            "                                             and a set of replicate trees (e.g., from a bootstrap analysis)\n"
            "  --bsconverge                               test for bootstrapping convergence using autoMRE criterion\n"
            "  --bsmsa                                    generate bootstrap replicate MSAs\n"
#ifdef _RAXML_TERRAPHAST
            "  --terrace                                  check whether a tree lies on a phylogenetic terrace \n"
#endif
            "  --check                                    check alignment correctness and remove empty columns/rows\n"
            "  --parse                                    parse alignment, compress patterns and create binary MSA file\n"
            "  --start                                    generate parsimony/random starting trees and exit\n"
            "  --rfdist                                   compute pair-wise Robinson-Foulds (RF) distances between trees\n"
            "  --consense [ STRICT | MR | MR<n> | MRE ]   build strict, majority-rule (MR) or extended MR (MRE) consensus tree (default: MR)\n"
            "                                             eg: --consense MR75 --tree bsrep.nw\n"
            "  --ancestral                                ancestral state reconstruction at all inner nodes\n"
            "  --sitelh                                   print per-site log-likelihood values\n"
            "\n"
            "Command shortcuts (mutually exclusive):\n"
            "  --search1                                  Alias for: --search --tree rand{1}\n"
            "  --loglh                                    Alias for: --evaluate --opt-model off --opt-branches off --nofiles --log result\n"
            "  --rf                                       Alias for: --rfdist --nofiles --log result\n"
            "\n"
            "Input and output options:\n"
            "  --tree            rand{N} | pars{N} | FILE starting tree: rand(om), pars(imony) or user-specified (newick file)\n"
            "                                             N = number of trees (default: rand{10},pars{10})\n"
            "  --msa             FILE                     alignment file\n"
            "  --msa-format      VALUE                    alignment file format: FASTA, PHYLIP, CATG or AUTO-detect (default)\n"
            "  --data-type       VALUE                    data type: DNA, AA, BIN(ary) or AUTO-detect (default)\n"
            "  --tree-constraint FILE                     constraint tree\n"
            "  --prefix          STRING                   prefix for output files (default: MSA file name)\n"
            "  --log             VALUE                    log verbosity: ERROR,WARNING,RESULT,INFO,PROGRESS,DEBUG (default: PROGRESS)\n"
            "  --redo                                     overwrite existing result files and ignore checkpoints (default: OFF)\n"
            "  --nofiles                                  do not create any output files, print results to the terminal only\n"
            "  --precision       VALUE                    number of decimal places to print (default: 6)\n"
            "  --outgroup        o1,o2,..,oN              comma-separated list of outgroup taxon names (it's just a drawing option!)\n"
            "  --site-weights    FILE                     file with MSA column weights (positive integers only!)  \n"
            "\n"
            "General options:\n"
            "  --seed         VALUE                       seed for pseudo-random number generator (default: current time)\n"
            "  --pat-comp     on | off                    alignment pattern compression (default: ON)\n"
            "  --tip-inner    on | off                    tip-inner case optimization (default: OFF)\n"
            "  --site-repeats on | off                    use site repeats optimization, 10%-60% faster than tip-inner (default: ON)\n" <<
            "  --threads      VALUE                       number of parallel threads to use (default: " << sysutil_get_cpu_cores() << ")\n" <<
            "  --workers      VALUE                       number of tree searches to run in parallel (default: 1)\n" <<
            "  --simd         none | sse3 | avx | avx2    vector instruction set to use (default: auto-detect).\n"
            "  --rate-scalers on | off                    use individual CLV scalers for each rate category (default: ON for >2000 taxa)\n"
            "  --force        [ <CHECKS> ]                disable safety checks (please think twice!)\n"
            "\n"
            "Model options:\n"
            "  --model        <name>+G[n]+<Freqs> | FILE  model specification OR partition file\n"
            "  --brlen        linked | scaled | unlinked  branch length linkage between partitions (default: scaled)\n"
            "  --blmin        VALUE                       minimum branch length (default: 1e-6)\n"
            "  --blmax        VALUE                       maximum branch length (default: 100)\n"
            "  --blopt        nr_fast    | nr_safe        branch length optimization method (default: nr_fast)\n"
            "                 nr_oldfast | nr_oldsafe     \n"
            "  --opt-model    on | off                    ML optimization of all model parameters (default: ON)\n"
            "  --opt-branches on | off                    ML optimization of all branch lengths (default: ON)\n"
            "  --prob-msa     on | off                    use probabilistic alignment (works with CATG and VCF)\n"
            "  --lh-epsilon   VALUE                       log-likelihood epsilon for optimization/tree search (default: 0.1)\n"
            "\n"
            "Topology search options:\n"
            "  --spr-radius   VALUE                       SPR re-insertion radius for fast iterations (default: AUTO)\n"
            "  --spr-cutoff   VALUE | off                 relative LH cutoff for descending into subtrees (default: 1.0)\n"
            "\n"
            "Bootstrapping options:\n"
            "  --bs-trees     VALUE                       number of bootstraps replicates\n"
            "  --bs-trees     autoMRE{N}                  use MRE-based bootstrap convergence criterion, up to N replicates (default: 1000)\n"
            "  --bs-trees     FILE                        Newick file containing set of bootstrap replicate trees (with --support)\n"
            "  --bs-cutoff    VALUE                       cutoff threshold for the MRE-based bootstopping criteria (default: 0.03)\n"
            "  --bs-metric    fbp | tbe                   branch support metric: fbp = Felsenstein bootstrap (default), tbe = transfer distance\n";

  cout << "\n"
            "EXAMPLES:\n"
            "  1. Perform tree inference on DNA alignment \n"
            "     (10 random + 10 parsimony starting trees, general time-reversible model, ML estimate of substitution rates and\n"
            "      nucleotide frequencies, discrete GAMMA model of rate heterogeneity with 4 categories):\n"
            "\n"
            "     ./raxml-ng --msa testDNA.fa --model GTR+G\n"
            "\n";

  cout << "\n"
            "  2. Perform an all-in-one analysis (ML tree search + non-parametric bootstrap) \n"
            "     (10 randomized parsimony starting trees, fixed empirical substitution matrix (LG),\n"
            "      empirical aminoacid frequencies from alignment, 8 discrete GAMMA categories,\n"
            "      200 bootstrap replicates):\n"
            "\n"
            "     ./raxml-ng --all --msa testAA.fa --model LG+G8+F --tree pars{10} --bs-trees 200\n"
            "\n";

  cout << "\n"
            "  3. Optimize branch lengths and free model parameters on a fixed topology\n"
            "     (using multiple partitions with proportional branch lengths)\n"
            "\n"
            "     ./raxml-ng --evaluate --msa testAA.fa --model partitions.txt --tree test.tree --brlen scaled\n"
            "\n";

}

