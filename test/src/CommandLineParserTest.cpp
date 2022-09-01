#include "RaxmlTest.hpp"

#include "src/CommandLineParser.hpp"
#include "src/io/binary_io.hpp"

using namespace std;

#define MAX_ARGS 256

::testing::internal::Mutex mutx;

void cmdline_to_argv(char * cmd, int &argc, char** argv)
{
  argc = 0;
  char *saveptr;
  char *p2 = strtok_r(cmd, " ", &saveptr);
  while (p2 && argc <= MAX_ARGS)
    {
      argv[argc++] = p2;
      p2 = strtok_r(0, " ", &saveptr);
    }
  argv[argc] = 0;
}

void parse_options(string &cmd, CommandLineParser &parser, Options &opts,
                   bool except_throw)
{
  int argc;
  char * argv[MAX_ARGS];

  cmdline_to_argv(&cmd[0], argc, argv);
  mutx.Lock();
  try
  {
    parser.parse_options(argc, argv, opts);
    EXPECT_FALSE(except_throw) << "Exception expected but not thrown";
  }
  catch (exception &e)
  {
    EXPECT_TRUE(except_throw) << "Exception: " << e.what() << std::endl;
  }
  mutx.Unlock();
}

void compare_opts(const Options& opts1, const Options& opts2)
{
  EXPECT_EQ(opts1.command, opts2.command);
  EXPECT_EQ(opts1.outfile_prefix, opts2.outfile_prefix);
  EXPECT_EQ(opts1.outfile_prefix, opts2.outfile_prefix);
  EXPECT_EQ(opts1.cmdline, opts2.cmdline);
  EXPECT_EQ(opts1.num_threads, opts2.num_threads);

  std::stringstream s1, s2;

  s1 << opts1;
  s2 << opts2;

  EXPECT_EQ(s1.str(), s2.str());
}

TEST(CommandLineParserTest, help)
{
  // buildup
  CommandLineParser parser;
  Options options;

  // tests
  string cmd = "raxml-ng";
  parse_options(cmd, parser, options, false);
  EXPECT_EQ(Command::help, options.command);
}

TEST(CommandLineParserTest, search_wrong)
{
  // buildup
  CommandLineParser parser;
  Options options;

  // wrong: --msa switsch missing
  string cmd = "raxml-ng --threads 2";
  parse_options(cmd, parser, options, true);
}

TEST(CommandLineParserTest, search_minimal)
{
  // buildup
  CommandLineParser parser;
  Options options;

  // minimal valid command line
  string cmd = "raxml-ng --msa data.fa --model GTR";
  parse_options(cmd, parser, options, false);
  EXPECT_EQ(Command::search, options.command);
  EXPECT_EQ("data.fa", options.msa_file);
  EXPECT_EQ("GTR", options.model_file);
  EXPECT_EQ(2, options.start_trees.size());
  EXPECT_EQ(10, options.start_trees.at(StartingTree::random));
  EXPECT_EQ(10, options.start_trees.at(StartingTree::parsimony));
  EXPECT_EQ(20, options.num_searches);
}

TEST(CommandLineParserTest, search_complex1)
{
  // buildup
  CommandLineParser parser;
  Options options;

  // a more involved example
  string cmd = "raxml-ng --msa data.fa --tree start.tre --model JC69 --threads 4 --seed 9";
  parse_options(cmd, parser, options, false);
  EXPECT_EQ(Command::search, options.command);
  EXPECT_EQ("data.fa", options.msa_file);
  EXPECT_EQ(1, options.start_trees.size());
  EXPECT_EQ(1, options.start_trees.at(StartingTree::user));
  EXPECT_EQ("start.tre", options.tree_file);
  EXPECT_EQ("JC69", options.model_file);
  EXPECT_EQ(4, options.num_threads);
  EXPECT_EQ(9, options.random_seed);
}

TEST(CommandLineParserTest, search_complex2)
{
  // buildup
  CommandLineParser parser;
  Options options;

  // fancy search command
  string cmd = "raxml-ng --search --msa data.fa --tree random --model part.txt "
      "--prefix myRun --prob-msa ON --brlen linked --spr-radius 10 --spr-cutoff 0.5";
  parse_options(cmd, parser, options, false);
  EXPECT_EQ(Command::search, options.command);
  EXPECT_EQ(1, options.start_trees.size());
  EXPECT_EQ(10, options.start_trees.at(StartingTree::random));
  EXPECT_EQ("myRun", options.outfile_prefix);
  EXPECT_TRUE(options.use_prob_msa);
  EXPECT_EQ(CORAX_BRLEN_LINKED, options.brlen_linkage);
  EXPECT_EQ(10, options.spr_radius);
  EXPECT_DOUBLE_EQ(0.5, options.spr_cutoff);
}

TEST(CommandLineParserTest, all_default)
{
  // buildup
  CommandLineParser parser;
  Options options;

  // fancy search command
  string cmd = "raxml-ng --all --msa data.fa --model part.txt ";
  parse_options(cmd, parser, options, false);
  EXPECT_EQ(Command::all, options.command);
  EXPECT_EQ(2, options.start_trees.size());
  EXPECT_EQ(10, options.start_trees.at(StartingTree::random));
  EXPECT_EQ(10, options.start_trees.at(StartingTree::parsimony));
  EXPECT_EQ(20, options.num_searches);
  EXPECT_EQ(1000, options.num_bootstraps);
  EXPECT_EQ(BootstopCriterion::autoMRE, options.bootstop_criterion);
  EXPECT_EQ(CORAX_BRLEN_SCALED, options.brlen_linkage);
}

TEST(CommandLineParserTest, all_complex)
{
  // buildup
  CommandLineParser parser;
  Options options;

  // fancy search command
  string cmd = "raxml-ng --all --msa data.fa --model part.txt --tree rand{30},pars{20},my.tree "
      "--bs-trees 1000 --prefix myBS --brlen unlinked";
  parse_options(cmd, parser, options, false);
  EXPECT_EQ(Command::all, options.command);
  EXPECT_EQ("my.tree", options.tree_file);
  EXPECT_EQ(3, options.start_trees.size());
  EXPECT_EQ(30, options.start_trees.at(StartingTree::random));
  EXPECT_EQ(20, options.start_trees.at(StartingTree::parsimony));
  EXPECT_EQ(1, options.start_trees.at(StartingTree::user));
  EXPECT_EQ(51, options.num_searches);
  EXPECT_EQ(1000, options.num_bootstraps);
  EXPECT_EQ("myBS", options.outfile_prefix);
  EXPECT_EQ(CORAX_BRLEN_UNLINKED, options.brlen_linkage);
}

TEST(CommandLineParserTest, eval_wrong)
{
  // buildup
  CommandLineParser parser;
  Options options;

  // wrong: evaluate without a tree
  string cmd = "raxml-ng --evaluate --msa data.fa";
  parse_options(cmd, parser, options, true);
  EXPECT_EQ(Command::evaluate, options.command);
}

TEST(CommandLineParserTest, eval_minimal)
{
  // buildup
  CommandLineParser parser;
  Options options;

  // valid evaluate command line
  string cmd = "raxml-ng --evaluate --msa data.fa --model GTR --tree start.tre";
  parse_options(cmd, parser, options, false);
  EXPECT_EQ(Command::evaluate, options.command);
  EXPECT_EQ("GTR", options.model_file);
  EXPECT_TRUE(options.optimize_model);
  EXPECT_TRUE(options.optimize_brlen);
}

TEST(CommandLineParserTest, eval_complex)
{
  // buildup
  CommandLineParser parser;
  Options options;

  // evaluate with more settings
  string cmd = "raxml-ng --evaluate --msa data.fa --tree start.tre --opt-model OFF "
      "--opt-branches OFF --lh-epsilon 0.02 --model GTR";
  parse_options(cmd, parser, options, false);
  EXPECT_EQ(Command::evaluate, options.command);
  EXPECT_EQ("GTR", options.model_file);
  EXPECT_FALSE(options.optimize_model);
  EXPECT_FALSE(options.optimize_brlen);
  EXPECT_DOUBLE_EQ(0.02, options.lh_epsilon);
}


TEST(CommandLineParserTest, options_copy)
{
  // buildup
  CommandLineParser parser;
  Options opts;

  string cmd = "raxml-ng --all --msa data.fa --model GTR --tree rand{10},pars{5} --bs-metric fbp,tbe "
      "--outgroup taxon1,taxon2 --prefix test --threads 2";
  parse_options(cmd, parser, opts, false);

  Options opts2 = opts;

  compare_opts(opts, opts2);
}

TEST(CommandLineParserTest, options_serialize)
{
  // buildup
  CommandLineParser parser;
  Options opts, opts2;
  const std::string fname = "tmpfile";

  string cmd = "raxml-ng --all --msa data.fa --model GTR --tree rand{10},pars{5} --bs-metric fbp,tbe "
      "--outgroup taxon1,taxon2 --prefix test --threads 2";
  parse_options(cmd, parser, opts, false);

  {
    BinaryFileStream bos(fname, ios::out);
    bos << opts;
  }

  {
    BinaryFileStream bis(fname, ios::in);
    bis >> opts2;
    sysutil_file_remove(fname);
  }

  compare_opts(opts, opts2);
}


