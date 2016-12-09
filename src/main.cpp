#include <iostream>
#include <string>
#include <algorithm>
#include <chrono>

//#include <cxxopts.hpp>
//
//#include "mpihead.hpp"
//#include "Log.hpp"
//#include "epa.hpp"

using namespace std;

int main(int argc, char** argv)
{
  cout <<  "raxml-ng started!" << endl;
  return EXIT_SUCCESS;
}

/*
Log lgr;

int main(int argc, char** argv)
{
  string invocation("");
  string sequence_type("DNA");
  string model_id("GTR");
  string sub_matrix("");
  Options options;
  for (int i = 0; i < argc; ++i)
  {
    invocation += argv[i];
    invocation += " ";
  }

  string query_file("");
  string work_dir("");
  string tree_file("");
  string reference_file("");
  string binary_file("");

  std::string banner;

  banner +=   " _____        ______ _____        ";
  banner += "\n|  __ \\      |  ____|  __ \\ /\\    ";
  banner += "\n| |__) |_____| |__  | |__) /  \\   ";
  banner += "\n|  ___/______|  __| |  ___/ /\\ \\  ";
  banner += "\n| |          | |____| |  / ____ \\";
  banner += "\n|_|          |______|_| /_/    \\_\\ \n";

  lgr << banner << std::endl;

  try
  {
  cxxopts::Options cli(argv[0], "Massively-Parallel Evolutionary Placement Algorithm");

  cli.add_options()
    ("help", "Display help.")
    ("version", "Display version.")
    ;
  cli.add_options("Input")
    ("t,tree", "Path to Reference Tree file.", cxxopts::value<std::string>())
    ("s,ref-msa", "Path to Reference MSA file.", cxxopts::value<std::string>())
    ("q,query", "Path to Query MSA file.", cxxopts::value<std::string>())
    ("b,binary", "Path to Binary file.", cxxopts::value<std::string>())
    ;
  cli.add_options("Output")
    ("w,outdir", "Path to output directory.", 
      cxxopts::value<std::string>()->default_value("./"))
    ("B,dump-binary", 
      "Binary Dump mode: write ref. tree in binary format then exit.")
    ("l,discard-min-lwr", 
      "Minimum likelihood weight below which a placement is discarded.",
      cxxopts::value<double>()->default_value("0.01")->implicit_value("0.01"))
    ("L,discard-acc-lwr", 
      "Accumulated likelihood weight after which further placements are discarded.",
      cxxopts::value<double>()->implicit_value("0.01"))
    ;
  cli.add_options("Compute")
    ("O,opt-ref-tree", "Optimize reference tree and model parameters.")
    ("raxml-blo", 
      "Employ old style of branch length optimization during thorough insertion as opposed to sliding approach."
      "WARNING: may significantly slow down computation.")
    ("g,dyn-heur", 
      "Two-phase heuristic, determination of candidate edges using accumulative threshold.",
      cxxopts::value<double>()->implicit_value("0.99"))
    ("G,fix-heur",
      "Two-phase heuristic, determination of candidate edges by specified percentage of total edges.",
      cxxopts::value<double>()->implicit_value("0.1"))
    ("m,model",
      "Description string of the model to be used. Format: "
      "<type>-<symmetries>-<rate/frequency model> Examples: -m DNA-GTR-EMPIRICAL, -m AA-GTR-BLOSUM62",
      cxxopts::value<std::string>()->default_value("DNA-GTR-EMPIRICAL"))
    ;

  cli.parse(argc, argv);

  if (cli.count("help"))
  {
    lgr << cli.help({"", "Input", "Output", "Compute"}) << std::endl;
    exit(EXIT_SUCCESS);
  }

  // check for valid input combinations
  if (not(
        ( cli.count("tree") and cli.count("ref-msa") ) 
    or  ( cli.count("binary") and (cli.count("query") or cli.count("ref-msa")) )
    ))
  {
    lgr << "Must supply reference tree/msa either directly or as precomputed binary." << std::endl;
    exit(EXIT_FAILURE);
  }
  
  if (cli.count("query")) query_file = cli["query"].as<std::string>();
  if (cli.count("outdir")) work_dir = cli["outdir"].as<std::string>();
  if (cli.count("tree")) tree_file = cli["tree"].as<std::string>();
  if (cli.count("ref-msa")) reference_file = cli["ref-msa"].as<std::string>();
  if (cli.count("binary")) 
  {
    binary_file = cli["binary"].as<std::string>();
    options.load_binary_mode = true;
  }
  if (cli.count("discard-min-lwr")) options.support_threshold = cli["discard-min-lwr"].as<double>();
  if (cli.count("discard-acc-lwr")) 
  { 
    options.support_threshold = cli["discard-acc-lwr"].as<double>(); 
    options.acc_threshold = true; 
  }
  if (cli.count("fix-heur")) 
  {
    options.prescoring_threshold = cli["fix-heur"].as<double>(); 
    options.prescoring = options.prescoring_by_percentage = true; 
  }
  if (cli.count("dyn-heur")) 
  {
    options.prescoring_threshold = cli["dyn-heur"].as<double>();
    if (options.prescoring) lgr << "Cannot use -G and -g concurrently! Running with -g " << options.prescoring_threshold <<  std::endl;
    options.prescoring = true;
    options.prescoring_by_percentage = false;
  }
  if (cli.count("opt-ref-tree")) options.opt_branches = options.opt_model = true;
  if (cli.count("raxml-blo")) options.sliding_blo = false;
  if (cli.count("dump-binary")) options.dump_binary_mode =  true;
  if (cli.count("model"))
  {
    auto parts = split_by_delimiter(cli["model"].as<std::string>(), "-");
    auto s = parts.size();
    if (s > 3)
      throw runtime_error{"Supplied too many model arguments! Must be 3 or less."};
    else 
    {
      if (s >=1)
        sequence_type = parts[0];
      if (s >= 2)
        model_id = parts[1];
      if (s >= 3)
        sub_matrix = parts[2];

      lgr.dbg() << "Model descriptor: " << sequence_type << " "
      << model_id << " " << sub_matrix << " " << std::endl;
    }

  }

  } catch (const cxxopts::OptionException& e)
  {
    std::cout << "error parsing options: " << e.what() << std::endl;
    exit(EXIT_FAILURE);
  }

  // start the placement process and write to file
  auto start = chrono::high_resolution_clock::now();
  process(tree, queries, work_dir, options, invocation);
  auto end = chrono::high_resolution_clock::now();
  auto runtime = chrono::duration_cast<chrono::seconds>(end - start).count();

  lgr << "\nTime spent placing: " << runtime << "s" << endl;

  MPI_FINALIZE();
	return EXIT_SUCCESS;
}

*/
