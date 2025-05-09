#include "CommandLineParser.hpp"
#include "version.h"

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
  {"bs-write-msa",       no_argument, 0, 0 },        /*  57 */
  {"lh-epsilon-triplet", required_argument, 0, 0 },  /* 58 */
  {"adaptive",           optional_argument, 0, 0 },  /*  59 */
  {"diff_pred_trees",    required_argument, 0, 0},   /*  60 */
  {"nni-tolerance",      required_argument, 0, 0 },  /*  61 */
  {"nni-epsilon",        required_argument, 0, 0 },  /*  62 */
  {"pythia",             optional_argument, 0, 0 },  /*  63 */
  {"pt",                 optional_argument, 0, 0 },  /*  64 */
  {"sh",                 optional_argument, 0, 0 },  /*  65 */
  {"sh-reps",            required_argument, 0, 0 },  /*  66 */
  {"sh-epsilon",         required_argument, 0, 0 },  /*  67 */
  {"opt-topology",       required_argument, 0, 0 },  /*  68 */
  {"stop-rule",          required_argument, 0, 0 },  /*  69 */
  {"ebg",                no_argument,       0, 0 },  /*  70 */
  {"fast",               no_argument,       0, 0 },  /*  71 */
  {"modeltest",          no_argument,       0, 0 },  /*  72 */

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
      opts.command == Command::ancestral || opts.command == Command::modeltest)
  {
    if (opts.msa_file.empty())
      throw OptionException("You must specify a multiple alignment file with --msa switch");
  }

  if (opts.command == Command::evaluate || opts.command == Command::support ||
      opts.command == Command::terrace || opts.command == Command::rfdist ||
      opts.command == Command::sitelh || opts.command == Command::ancestral ||
      opts.command == Command::consense)
  {
    if (opts.tree_file.empty() && opts.start_trees.count(StartingTree::user))
      throw OptionException("Please provide a valid Newick file as an argument of --tree option.");
  }

  if (opts.command == Command::start && !opts.tree_file.empty())
  {
    throw OptionException("You specified a user starting tree) for the starting tree generation "
        "command, which does not make any sense!\n"
        "Please choose whether you want to generate parsimony or random starting trees!");
  }

  if (opts.command == Command::support)
  {
    /* only FBP, TBE and IC1/ICA are allowed in support mapping mode; other values are ignored */
    opts.bs_metrics.erase(BranchSupportMetric::rbs);
    opts.bs_metrics.erase(BranchSupportMetric::ps);
    opts.bs_metrics.erase(BranchSupportMetric::pbs);
    opts.bs_metrics.erase(BranchSupportMetric::ebg);
    opts.bs_metrics.erase(BranchSupportMetric::sh_alrt);
    if (opts.bs_metrics.empty())
      opts.bs_metrics.insert(BranchSupportMetric::fbp);
  }

  if (opts.command == Command::bootstrap)
  {
    if (opts.bs_metrics.empty())
      opts.bs_metrics.insert(BranchSupportMetric::fbp);
    else if (opts.bs_metrics.size() > 1)
      throw OptionException("Please provide a single value for the --bs-metric option.");
    else if (!opts.bs_metrics.count(BranchSupportMetric::fbp) &&
             !opts.bs_metrics.count(BranchSupportMetric::rbs) &&
             !opts.bs_metrics.count(BranchSupportMetric::ps) &&
             !opts.bs_metrics.count(BranchSupportMetric::pbs))
    {
      throw OptionException("Invalid --bs-metric value! Only FBP, RBS, PS or PBS are supported.");
    }

    /* only FBP, TBE and IC1/ICA are allowed in support mapping mode; other values are ignored */
    opts.bs_metrics.erase(BranchSupportMetric::rbs);
    opts.bs_metrics.erase(BranchSupportMetric::ps);
    opts.bs_metrics.erase(BranchSupportMetric::pbs);
    opts.bs_metrics.erase(BranchSupportMetric::ebg);
    opts.bs_metrics.erase(BranchSupportMetric::sh_alrt);
    if (opts.bs_metrics.empty())
      opts.bs_metrics.insert(BranchSupportMetric::fbp);
  }

  if (opts.command == Command::support || opts.command == Command::bsconverge)
  {
    if (opts.outfile_names.bootstrap_trees.empty())
    {
      throw OptionException("You must specify a Newick file with replicate trees, e.g., "
          "--bs-trees bootstrap.nw");
    }
  }

  if (opts.command == Command::support || opts.command == Command::rfdist ||
      opts.command == Command::consense)
  {
    assert(!opts.tree_file.empty() || !opts.outfile_names.bootstrap_trees.empty());

    if (opts.outfile_prefix.empty())
    {
      opts.outfile_prefix = !opts.tree_file.empty() ? opts.tree_file :
                                                      opts.outfile_names.bootstrap_trees;
    }
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
    
  if (opts.write_bs_msa && opts.command != Command::bsmsa &&
      opts.command != Command::bootstrap && opts.command != Command::all)
  {
    throw OptionException("You specified to write out boostrap alignments with --bs-write-msa option, "
      "but the current command does not perform bootstrapping.\n"
      "Did you forget --all option?");
  }

  if (opts.simd_arch > sysutil_simd_autodetect())
  {
    if (opts.force_mode)
      corax_hardware_ignore();
    else
    {
      throw OptionException("Cannot detect " + opts.simd_arch_name() +
                            " instruction set on your system. If you are absolutely sure "
                            "it is supported, please use --force option to disable this check.");
    }
  }

  if (opts.command == Command::modeltest && opts.num_workers > 1)
  {
    throw OptionException("Model testing currently does not work with parallel tree searches. "
        "Please use only a single worker.");
  }

  if (opts.command == Command::modeltest || opts.model_file == "auto" || opts.model_file == "AUTO" ||
      opts.model_file == "DNA"  || opts.model_file == "AA")
  {
    if (opts.num_ranks > 1)
      throw OptionException("Model testing currently does not support MPI, sorry.");
  }
}

void CommandLineParser::compute_num_searches(Options &opts)
{
  if (opts.command == Command::search || opts.command == Command::all ||
      opts.command == Command::evaluate || opts.command == Command::start ||
      opts.command == Command::ancestral || opts.command == Command::sitelh ||
      opts.command == Command::modeltest)
  {
    assert(!opts.start_trees.empty());

    auto def_tree_count = 10;
    for (auto& it: opts.start_trees)
    {
      if (it.first == StartingTree::user)
        it.second = 1;
      else if (it.first == StartingTree::adaptive)
        it.second = 0;
      else
        it.second = it.second != RAXML_UINT32_NONE ? it.second : def_tree_count;
    }

    for (const auto& it: opts.start_trees)
      opts.num_searches += it.second;
  }
  else if (opts.command == Command::parse || opts.command == Command::check)
  {
    /* ignore random and parsimony starting trees in check/parse mode */
    opts.start_trees.clear();
    if (!opts.tree_file.empty())
      opts.num_searches = opts.start_trees[StartingTree::user] = 1;
  }
}

void CommandLineParser::parse_start_trees(Options &opts, const string& arg)
{
  auto start_trees = split_string(arg, ',');
  char strarg[11];
  for (const auto& st_tree: start_trees)
  {
    StartingTree st_tree_type;
    unsigned int num_searches = RAXML_UINT32_NONE;
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
    else if (st_tree ==  "auto" || st_tree == "adaptive")
    {
      st_tree_type = StartingTree::adaptive;
    }
    else if (sscanf(st_tree.c_str(), "cons:%10s", strarg) == 1)
    {
      parse_consense_cutoff(opts, strarg);
      st_tree_type = StartingTree::consensus;
    }
    else
    {
      opts.tree_file += (opts.tree_file.empty() ? "" : ",") + st_tree;
      st_tree_type = StartingTree::user;
    }
    if (num_searches == 0)
      throw InvalidOptionValueException("Number of starting trees must be positive!");
    if (!opts.start_trees.count(st_tree_type) || num_searches != RAXML_UINT32_NONE)
      opts.start_trees[st_tree_type] = num_searches;
  }
}

void CommandLineParser::parse_bs_trees(Options &opts, const string& arg)
{
  if (sysutil_file_exists(arg) && !sysutil_isnumber(arg))
  {
    opts.outfile_names.bootstrap_trees = arg;
  }
  else
  {
    string optstr = arg;
    std::transform(optstr.begin(), optstr.end(), optstr.begin(), ::tolower);
    auto metrics = split_string(optstr, ',');
    opts.bs_replicate_counts.clear();
    for (const auto& m: metrics)
    {
      unsigned int num;
      if (sscanf(m.c_str(), "fbp{%u}", &num) == 1)
      {
        opts.bs_replicate_counts[BranchSupportMetric::fbp] = num;
      }
      else if (sscanf(m.c_str(), "rbs{%u}", &num) == 1)
      {
        opts.bs_replicate_counts[BranchSupportMetric::rbs] = num;
      }
      else if (sscanf(m.c_str(), "tbe{%u}", &num) == 1)
      {
        opts.bs_replicate_counts[BranchSupportMetric::tbe] = num;
      }
      else if (sscanf(m.c_str(), "ebg{%u}", &num) == 1)
      {
        opts.bs_replicate_counts[BranchSupportMetric::ebg] = num;
      }
      else if (sscanf(m.c_str(), "ps{%u}", &num) == 1)
      {
        opts.bs_replicate_counts[BranchSupportMetric::ps] = num;
      }
      else if (sscanf(m.c_str(), "pbs{%u}", &num) == 1)
      {
        opts.bs_replicate_counts[BranchSupportMetric::pbs] = num;
      }
      else if (sscanf(m.c_str(), "sh{%u}", &num) == 1)
      {
        opts.bs_replicate_counts[BranchSupportMetric::sh_alrt] = num;
        opts.num_sh_reps = num;
      }
      else if (strncasecmp(m.c_str(), "autoMRE", 7) == 0)
      {
        opts.bootstop_criterion = BootstopCriterion::autoMRE;
        if (sscanf(m.c_str(), "automre{%u}", &opts.num_bootstraps) != 1)
          opts.num_bootstraps = 1000;
      }
      else if (sscanf(m.c_str(), "%u", &opts.num_bootstraps) != 1 || opts.num_bootstraps == 0)
      {
        throw InvalidOptionValueException("Invalid number of bootstrap replicates: " + string(arg));
      }
    }
  }

  if (opts.command == Command::bootstrap || opts.command == Command::all ||
      opts.command == Command::bsmsa)
  {
    // apply defaults
    for (auto m: opts.bs_metrics)
    {
      if (!opts.bs_replicate_counts.count(m))
      {
        if (opts.bs_metrics.size() == 1 && opts.num_bootstraps > 0)
          opts.bs_replicate_counts[m] = opts.num_bootstraps;
        else if (m == BranchSupportMetric::ebg)
        {
          opts.bs_replicate_counts[m] = RAXML_EBG_PBS_TREES_NUM;
        }
        else if (m == BranchSupportMetric::ps || m == BranchSupportMetric::pbs)
        {
          opts.bs_replicate_counts[m] = RAXML_PS_PBS_TREES_NUM;
        }
        else if (m == BranchSupportMetric::sh_alrt)
          opts.bs_replicate_counts[m] = opts.num_sh_reps ? opts.num_sh_reps : RAXML_SH_ALRT_REPS;
        else
        {
          if (opts.num_bootstraps)
            opts.bs_replicate_counts[m] = opts.num_bootstraps;
          else
            opts.bs_replicate_counts[m] = (opts.bootstop_criterion == BootstopCriterion::none) ? 100 : 1000;
        }
      }
    }
  }

  /* special case: EBG requires parsimony trees, so set default count for them */
  if (opts.bs_replicate_counts.count(BranchSupportMetric::ebg) &&
      !opts.bs_replicate_counts.count(BranchSupportMetric::ps))
  {
    opts.bs_replicate_counts[BranchSupportMetric::ps] = RAXML_EBG_PS_TREES_NUM;
  }

  if ((opts.command == Command::bootstrap || opts.command == Command::all) &&
      opts.num_bootstraps == 0)
  {
    opts.num_bootstraps = opts.num_bootstrap_ml_trees();
  }
}

void CommandLineParser::parse_consense_cutoff(Options &opts, const char* optarg)
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

void CommandLineParser::parse_options(int argc, char** argv, Options &opts)
{

  opts.cmdline = get_cmdline(argc, argv);

  /* if no command specified, default to --adaptive (or --help if no args were given) */
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

  /* use new split-based constraint checking method -> slightly slower, but more reliable */
  opts.use_old_constraint = false;
  
  /* enable incremental CLV updates across pruned subtrees in SPR rounds */
  opts.use_spr_fastclv = true;

  /* optimize model and branch lengths */
  opts.optimize_model = true;
  opts.optimize_brlen = true;

  /* initialize LH epsilon with default value */
  opts.lh_epsilon = DEF_LH_EPSILON;
  opts.lh_epsilon_brlen_triplet = DEF_LH_EPSILON_BRLEN_TRIPLET;

  /* default: autodetect best SPR radius */
  opts.spr_radius = -1;
  opts.spr_cutoff = 1.0;

  /* default: nni parameters */
  opts.nni_tolerance = DEF_NNI_TOLERANCE;
  opts.nni_epsilon = DEF_NNI_BR_LEN_EPSILON;

  /* Stopping criteria */
  opts.stopping_rule = StoppingRule::kh; // by default, we use the KH-simple as a stopping rule

  /* default: SH parameters */
  opts.num_sh_reps = RAXML_SH_ALRT_REPS;
  opts.sh_epsilon = RAXML_SH_ALRT_EPSILON;

  /* bootstrapping / bootstopping */
  opts.bs_metrics.insert(BranchSupportMetric::fbp);
  opts.bootstop_criterion = BootstopCriterion::autoMRE;
  opts.bootstop_cutoff = RAXML_BOOTSTOP_CUTOFF;
  opts.bootstop_interval = RAXML_BOOTSTOP_INTERVAL;
  opts.bootstop_permutations = RAXML_BOOTSTOP_PERMUTES;

  /* default: linked branch lengths */
  opts.brlen_linkage = CORAX_BRLEN_SCALED;
  opts.brlen_min = RAXML_BRLEN_MIN;
  opts.brlen_max = RAXML_BRLEN_MAX;

  /* by default, autodetect optimal number of threads and workers for the dataset */
  opts.num_threads = 0;
  opts.num_workers = 0;

  /* Difficulty preditction num trees */
  opts.diff_pred_pars_trees = RAXML_CPYTHIA_TREES_NUM;

  bool use_adaptive_search = true;
  opts.topology_opt_method = TopologyOptMethod::adaptive;

  /* max #threads = # available CPU cores */
#if !defined(_RAXML_PTHREADS)
  opts.num_threads = 1;
#else
  if (ParallelContext::ranks_per_node() == 1)
    opts.num_threads_max = std::max(1u, sysutil_task_cpu_cores(true));
  else
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
  opts.write_bs_msa = false;

  opts.force_mode = false;
  opts.safety_checks = SafetyCheck::all;

  opts.redo_mode = false;
  opts.nofiles_mode = false;

  opts.tbe_naive = false;

  int compat_ver = RAXML_INTVER;
  bool log_level_set = false;
  bool lh_epsilon_set = false;
  bool optarg_tree_required = false;
  string optarg_tree = "";
  string optarg_bs_trees = "";

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
        if (optarg_tree.empty())
          optarg_tree = strdup(optarg);
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
          opts.use_pythia = false;
          opts.stopping_rule = StoppingRule::none;
          use_adaptive_search = false;
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
          opts.brlen_linkage = CORAX_BRLEN_SCALED;
        else if (strcasecmp(optarg, "linked") == 0)
          opts.brlen_linkage = CORAX_BRLEN_LINKED;
        else if (strcasecmp(optarg, "unlinked") == 0)
          opts.brlen_linkage = CORAX_BRLEN_UNLINKED;
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
        lh_epsilon_set = true;
        opts.stopping_rule = StoppingRule::none;
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
#ifdef HAVE_AUTOVEC
          throw InvalidOptionValueException("Non-vectorized kernels not available!\n"
              "Please recompile RAxML-NG in portable mode, or use '--simd native' for auto-vectorized kernels.");
#else
          opts.simd_arch = CORAX_ATTRIB_ARCH_CPU;
#endif
        }
        else if (strcasecmp(optarg, "native") == 0 || strcasecmp(optarg, "autovec") == 0)
        {
#ifdef HAVE_AUTOVEC
          opts.simd_arch = CORAX_ATTRIB_ARCH_CPU;
#else
          throw InvalidOptionValueException("Auto-vectorized kernels not available!\n"
              "Please recompile RAxML-NG in native mode, or use '--simd none' for non-vectorized kernels.");
#endif
        }
        else if (strcasecmp(optarg, "sse3") == 0 || strcasecmp(optarg, "sse") == 0)
        {
          opts.simd_arch = CORAX_ATTRIB_ARCH_SSE;
        }
        else if (strcasecmp(optarg, "avx") == 0)
        {
          opts.simd_arch = CORAX_ATTRIB_ARCH_AVX;
        }
        else if (strcasecmp(optarg, "avx2") == 0)
        {
          opts.simd_arch = CORAX_ATTRIB_ARCH_AVX2;
        }
        else if (strcasecmp(optarg, "auto") != 0)
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
        else if (strcasecmp(optarg, "fasta_longlabels") == 0)
        {
          opts.msa_format = FileFormat::fasta_longlabels;
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
        /* quickfix: TBE-nature implementation requires traversal-based CLV IDs assignment! */
        opts.tbe_naive = true;
        num_commands++;
        break;
      case 26:  /* number of bootstrap replicates */
        opts.bootstop_criterion = BootstopCriterion::none;
        optarg_bs_trees = optarg;
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
        opts.brlen_linkage = CORAX_BRLEN_UNLINKED;
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
          opts.brlen_opt_method = CORAX_OPT_BLO_NEWTON_FAST;
        else if (strcasecmp(optarg, "nr_oldfast") == 0)
          opts.brlen_opt_method = CORAX_OPT_BLO_NEWTON_OLDFAST;
        else if (strcasecmp(optarg, "nr_safe") == 0)
          opts.brlen_opt_method = CORAX_OPT_BLO_NEWTON_SAFE;
        else if (strcasecmp(optarg, "nr_oldsafe") == 0)
          opts.brlen_opt_method = CORAX_OPT_BLO_NEWTON_OLDSAFE;
        else if (strcasecmp(optarg, "nr_fallback") == 0)
          opts.brlen_opt_method = CORAX_OPT_BLO_NEWTON_FALLBACK;
        else if (strcasecmp(optarg, "nr_global") == 0)
          opts.brlen_opt_method = CORAX_OPT_BLO_NEWTON_GLOBAL;
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
            else if (eopt == "constraint-old")
              opts.use_old_constraint = true;
            else if (eopt == "constraint-new")
              opts.use_old_constraint = false;
            else if (eopt == "fastclv-on")
              opts.use_spr_fastclv = true;
            else if (eopt == "fastclv-off")
              opts.use_spr_fastclv = false;
            else if (eopt == "bs-start-pars")
              opts.use_bs_pars = true;
            else if (eopt == "bs-start-rand")
              opts.use_bs_pars = false;
            else if (eopt == "pars-par")
              opts.use_par_pars = true;
            else if (eopt == "pars-seq")
              opts.use_par_pars = false;
            else if (eopt == "pythia-on")
              opts.use_pythia = true;
            else if (eopt == "pythia-off")
              opts.use_pythia = false;
            else if (eopt == "compat-v11")
            {
              compat_ver = 110;
              opts.use_spr_fastclv = false;
              opts.use_bs_pars = false;
              opts.use_par_pars = false;
              opts.use_pythia = false;
              opts.stopping_rule = StoppingRule::none;
              opts.topology_opt_method = TopologyOptMethod::classic;
              if (!lh_epsilon_set)
                opts.lh_epsilon = DEF_LH_EPSILON_V11;
              opts.lh_epsilon_brlen_triplet = DEF_LH_EPSILON_V11;
            }
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
              opts.bs_metrics.insert(BranchSupportMetric::fbp);
            }
            else if (strncasecmp(m.c_str(), "rbs", 3) == 0)
            {
              opts.bs_metrics.insert(BranchSupportMetric::rbs);
            }
            else if (strncasecmp(m.c_str(), "tbe", 3) == 0)
            {
              opts.bs_metrics.insert(BranchSupportMetric::tbe);
            }
            else if (strncasecmp(m.c_str(), "ebg", 3) == 0)
            {
              opts.bs_metrics.insert(BranchSupportMetric::ebg);
            }
            else if (strncasecmp(m.c_str(), "ps", 2) == 0)
            {
              opts.bs_metrics.insert(BranchSupportMetric::ps);
            }
            else if (strncasecmp(m.c_str(), "pbs", 3) == 0)
            {
              opts.bs_metrics.insert(BranchSupportMetric::pbs);
            }
            else if (strncasecmp(m.c_str(), "sh", 2) == 0 || strncasecmp(m.c_str(), "alrt", 4) == 0)
            {
              opts.bs_metrics.insert(BranchSupportMetric::sh_alrt);
            }
            else if (strncasecmp(m.c_str(), "ic1", 3) == 0)
            {
              opts.bs_metrics.insert(BranchSupportMetric::ic1);
            }
            else if (strncasecmp(m.c_str(), "ica", 3) == 0)
            {
              opts.bs_metrics.insert(BranchSupportMetric::ica);
            }
            else
            {
              throw InvalidOptionValueException("Unknown branch support metric: " + string(optarg));
            }
            if (opts.bs_metrics.count(BranchSupportMetric::fbp) && opts.bs_metrics.count(BranchSupportMetric::rbs))
            {
              throw OptionException("Invalid branch support metric: FBP and RBS can not be used together!");
            }
          }
        }
        break;

      case 48: /* search1: search from a single starting tree */
        opts.command = Command::search;
        optarg_tree = "default1";
        num_commands++;
        break;
      case 49: /* generate bootstrap replicate MSAs */
        opts.command = Command::bsmsa;
        opts.use_par_pars = false;
        num_commands++;
        break;

      case 50: /* compute RF distance */
        opts.command = Command::rfdist;
        num_commands++;
        if (optarg)
          optarg_tree = optarg;
        break;

      case 51: /* compute and print average RF distance w/o noise */
        opts.command = Command::rfdist;
        opts.nofiles_mode = true;
        opts.log_level = LogLevel::result;
        log_level_set = true;
        num_commands++;
        if (optarg)
          optarg_tree = optarg;
        break;

      case 52: /* build consensus tree */
        opts.command = Command::consense;
        num_commands++;
        if (optarg)
          parse_consense_cutoff(opts, optarg);
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

      case 57: /* write bootstrap alignments*/
        opts.write_bs_msa = true;
        break;
      
      case 58: /* LH epsilon triplet */
        if(sscanf(optarg, "%lf", &opts.lh_epsilon_brlen_triplet) != 1 || opts.lh_epsilon_brlen_triplet < 0.)
          throw InvalidOptionValueException("Invalid triplet LH epsilon parameter value: " +
                                            string(optarg) +
                                            ", please provide a positive real number.");
        break;
      
      case 59: /* Adaptive RAxML-ng analysis with difficulty prediction */
        if (!optarg || (strcasecmp(optarg, "on") == 0))
        {
          use_adaptive_search = true;
          opts.use_pythia = true;
          opts.stopping_rule = StoppingRule::kh;
        }
        else if (strcasecmp(optarg, "start") == 0)
        {
          use_adaptive_search = false;
          opts.use_pythia = true;
          optarg_tree = "adaptive";
          opts.stopping_rule = StoppingRule::none;
        }
        else if (strcasecmp(optarg, "off") == 0)
        {
          use_adaptive_search = false;
          opts.use_pythia = false;
          opts.stopping_rule = StoppingRule::none;
        }
        else
        {
          throw InvalidOptionValueException("Invalid --adaptive  mode: " + string(optarg));
        }
        break;
      
      case 60: /* Number of parsimony trees in difficulty prediction */
        
        if (sscanf(optarg, "%d", &opts.diff_pred_pars_trees) != 1 || opts.diff_pred_pars_trees <= 0)
        {
          throw InvalidOptionValueException("Invalid number of parsimony trees for difficulty prediction: " + string(optarg) +
                                            ", please provide a positive integer!");
        }
        break;

      case 61: /* NNI tolerance */
        if(sscanf(optarg, "%lf", &opts.nni_tolerance) != 1 || opts.nni_tolerance <= 0.)
        {
          throw InvalidOptionValueException("Invalid NNI tolerance: " + string(optarg) +
                                            ", please provide a positive real number!\n");
        }
        break;
      
      case 62: /* NNI epsilon */
        if(sscanf(optarg, "%lf", &opts.nni_epsilon) != 1 || opts.nni_epsilon <= 0.)
        {
          throw InvalidOptionValueException("Invalid NNI epsilon  : " + string(optarg) +
                                            ", please provide a positive real number!\n");
        }
        break;

      case 63: /* pythia: msa difficulty prediction */
        opts.command = Command::pythia;
        num_commands++;
        break;

      case 64: /* pythia quiet */
        opts.command = Command::pythia;
        num_commands++;
        opts.nofiles_mode = true;
        opts.log_level = LogLevel::result;
        log_level_set = true;
        break;

      case 65: /* sh: compute SH-like ALRT branch supports for a given tree */
        opts.command = Command::all;
        opts.bs_metrics.clear();
        opts.bs_metrics.insert(BranchSupportMetric::sh_alrt);
        opts.topology_opt_method = TopologyOptMethod::nniRound;
        opts.use_pythia = false;
        optarg_tree_required = true;
        num_commands++;
        /* fall through */
      case 66: /* number of SH replicates */
        if (optarg)
        {
          if (sscanf(optarg, "%u", &opts.num_sh_reps) != 1 || opts.num_sh_reps == 0)
          {
            throw InvalidOptionValueException("Invalid number of SH replicates: " + string(optarg) +
                ", please provide a positive integer number!");
          }
        }
        break;
      case 67: /* SH epsilon */
        if(sscanf(optarg, "%lf", &opts.sh_epsilon) != 1 || opts.sh_epsilon <= 0.)
        {
          throw InvalidOptionValueException("Invalid SH epsilon  : " + string(optarg) +
                                            ", please provide a positive real number!\n");
        }
        break;
      case 68: /* topology optimization method */
        if (strcasecmp(optarg, "off") == 0 || strcasecmp(optarg, "none") == 0)
          opts.topology_opt_method = TopologyOptMethod::none;
        else if (strcasecmp(optarg, "classic") == 0 || strcasecmp(optarg, "v1") == 0)
          opts.topology_opt_method = TopologyOptMethod::classic;
        else if (strcasecmp(optarg, "adaptive") == 0)
          opts.topology_opt_method = TopologyOptMethod::adaptive;
        else if (strcasecmp(optarg, "rapidbs") == 0 || strcasecmp(optarg, "rbs") == 0)
          opts.topology_opt_method = TopologyOptMethod::rapidBS;
        else if (strcasecmp(optarg, "nni-round") == 0 || strcasecmp(optarg, "nni") == 0)
          opts.topology_opt_method = TopologyOptMethod::nniRound;
        else if (strcasecmp(optarg, "simplified") == 0 || strcasecmp(optarg, "sRAxML-NG") == 0){
          opts.topology_opt_method = TopologyOptMethod::simplified;
          opts.stopping_rule = StoppingRule::none;
          opts.use_pythia = false;
        } else if (strcasecmp(optarg, "fast") == 0) {
          opts.topology_opt_method = TopologyOptMethod::fast;
          opts.stopping_rule = StoppingRule::kh_mult;
          opts.use_pythia = true;
        } 
        else
          throw InvalidOptionValueException("Unknown topology optimization method: " + string(optarg));
        break;
      
      case 69: /* Stopping criterion */
        if (strcasecmp(optarg, "sn-rell") == 0) {
          opts.stopping_rule = StoppingRule::sn_rell;
        } else if (strcasecmp(optarg, "sn-normal") == 0) {
          opts.stopping_rule = StoppingRule::sn_normal;
        } else if (strcasecmp(optarg, "KH") == 0) {
          opts.stopping_rule = StoppingRule::kh;
        } else if (strcasecmp(optarg, "KH-mult") == 0) {
          opts.stopping_rule = StoppingRule::kh_mult;
        } else if (strcasecmp(optarg, "off") == 0) {
          opts.stopping_rule = StoppingRule::none;
        } else {
          throw InvalidOptionValueException("Invalid stopping criterion: " + string(optarg) +
                                            ", please provide one of the following options: \n" +
                                            "- sn-rell : Sampling Noise RELL apporach\n" +
                                            "- sn-normal : Sampling Noise Normal apporach\n" + 
                                            "- KH : KH test\n" +
                                            "- KH-mult : KH test with multiple correction\n"  +
                                            "- off : To turn off stopping rules\n");
        }
        break;
      
      case 70: /* ebg: use educated bootstrap guesser to estimate branch support */
        opts.command = Command::all;
        opts.bs_metrics.clear();
        opts.bs_metrics.insert(BranchSupportMetric::ebg);
        opts.topology_opt_method = TopologyOptMethod::none;
        opts.use_pythia = false;
        optarg_tree_required = true;
        num_commands++;
        break;
      /* --fast (shortcut): equivalent to --opt-topology fast */
      case 71:
        opts.topology_opt_method = TopologyOptMethod::fast;
        opts.stopping_rule = StoppingRule::kh_mult;
        opts.use_pythia = true;
        break;
      case 72: /* model test */
        opts.command = Command::modeltest;
        if (optarg_tree.empty())
          optarg_tree = "pars{1}";
        num_commands++;
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

  if (optarg_tree.empty() && optarg_tree_required)
    throw OptionException("This command requires a reference tree, please use --tree option!");

  if (!use_adaptive_search && opts.topology_opt_method == TopologyOptMethod::adaptive)
    opts.topology_opt_method = TopologyOptMethod::classic;

  /* process start tree defaults */
  if (opts.command == Command::search || opts.command == Command::all ||
      opts.command == Command::start)
  {
    if (optarg_tree.empty())
    {
      if (use_adaptive_search)
        optarg_tree = "adaptive";
      else
        optarg_tree = opts.use_old_constraint ? "rand{20}" : RAXML_DEF_START_TREE;
    }
    else if (optarg_tree == "default1")
      optarg_tree = compat_ver < 120 ? RAXML_DEF_START_TREE1_V11 : RAXML_DEF_START_TREE1;
  }
  parse_start_trees(opts, optarg_tree);

  /* process LH epsilon defaults */
  if (opts.command == Command::search || opts.command == Command::bootstrap ||
      opts.command == Command::all)
  {
    if (!lh_epsilon_set)
      opts.lh_epsilon = compat_ver < 120 ? DEF_LH_EPSILON_V11 : DEF_LH_EPSILON;
  }
  else
  {
    /* Always use old lower LH epsilon (0.1) for commands without tree search (--evaluate etc.)! */
    if (!lh_epsilon_set)
      opts.lh_epsilon = DEF_LH_EPSILON_V11;
  }

  parse_bs_trees(opts, optarg_bs_trees);

  check_options(opts);

  compute_num_searches(opts); // FOR ADAPTIVE RAXML

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
            "  --pythia                                   compute and print Pythia MSA difficulty score\n"
            "\n"
            "Command shortcuts (mutually exclusive):\n"
            "  --search1                                  Alias for: --search --tree pars{1}\n"
            "  --fast                                     Alias for: --search --opt-topology fast\n"
            "  --loglh                                    Alias for: --evaluate --opt-model off --opt-branches off --nofiles --log result\n"
            "  --rf                                       Alias for: --rfdist --nofiles --log result\n"
            "  --pt                                       Alias for: --pythia --nofiles --log result\n"
            "  --sh [ REPS ]                              Alias for: --all --opt-topology nni --bs-metric sh [ --sh-reps REPS ]\n"
            "  --ebg                                      Alias for: --all --opt-topology off --bs-metric ebg\n"
            "\n"
            "Input and output options:\n"
            "  --tree            rand{N} | pars{N} |      starting tree: rand(om), pars(imony) or user-specified (newick file)\n"
            "                    FILE | auto              N = number of trees (default: auto-detect based on MSA difficulty)\n"
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
#ifdef HAVE_AUTOVEC
            "  --simd         native | sse3 | avx | avx2  "
#else
            "  --simd         none | sse3 | avx | avx2    "
#endif
                                                      << "vector instruction set to use (default: auto-detect).\n"
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
            "  --lh-epsilon   VALUE                       log-likelihood epsilon for optimization/tree search (default: 10)\n"
            "\n"
            "Topology search options:\n"
            "  --opt-topology        classic | adaptive   topology optimization method (default: adaptive)\n"
            "                        nni | rbs | off      \n"
            "  --adaptive            [ on | off | start ] adaptive ML tree search (start = starting trees only)\n"
            "  --spr-radius          VALUE                SPR re-insertion radius for fast iterations (default: AUTO)\n"
            "  --spr-cutoff          VALUE | off          relative LH cutoff for descending into subtrees (default: 1.0)\n"
            "  --lh-epsilon-triplet  VALUE                log-likelihood epsilon for branch length triplet optimization (default: 1000)\n"
            "  --stop-rule           sn-rell | sn-nprmal  stopping criterion for SPR rounds (default: kh)\n"
            "                        kh | kh-mult | off   \n"
            "\n"
            "Bootstrapping and branch support options:\n"
            "  --bs-trees     N | fbp{N1},sh{N2},...      number of bootstrap replicates N, can be global or per-metric (see below)\n"
            "  --bs-trees     autoMRE{N}                  use MRE-based bootstrap convergence criterion, up to N replicates (default: 1000)\n"
            "  --bs-trees     FILE                        Newick file containing set of bootstrap replicate trees (with --support)\n"
            "  --bs-cutoff    VALUE                       cutoff threshold for the MRE-based bootstopping criteria (default: 0.03)\n"
            "  --bs-metric    fbp | rbs |                 branch support metric: fbp = Felsenstein bootstrap (default), rbs = Rapid bootstrap\n"
            "                 ebg | tbe | sh              ebg = Educated bootstrap guesser, tbe = Transfer bootstrap estimate, sh = SH-like aLRT\n"
            "                 ps  | pbs |                 ps = Parsimony support, pbs = Parsimony bootstrap support\n"
            "                 ic1 | ica                   ic1 = Internode certainty (most prevalent), ica = Internode certainty (all)\n"
            "  --bs-write-msa on | off                    write all bootstrap alignments (default: OFF)\n"
            "\n"
            "SH-like test options:\n"
            "  --sh-reps      VALUE                       number of bootstrap replicates for SH-aLRT test (default: 1000)\n"
            "  --sh-epsilon   VALUE                       log-likelihood epsilon for SH-aLRT test (default: 0.1)\n";

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

