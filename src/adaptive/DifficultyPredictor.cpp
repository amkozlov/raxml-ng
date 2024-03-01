#include "DifficultyPredictor.hpp"
#include <memory>
#include <random>

DifficultyPredictor::DifficultyPredictor(const string& outfile)
{
  _rf_dist_calc.reset(new RFDistCalculator());
  _outfile = outfile;
  _difficulty = -1;
  _states = 0;
  _states_map = nullptr;
  _parsimony_msa_ptr = nullptr;
  _features = nullptr;
}

DifficultyPredictor::~DifficultyPredictor()
{
  free(_features);
  _pars_tree_list.clear();
}

void DifficultyPredictor::set_parsimony_msa_ptr(ParsimonyMSA* _pmsa)
{
  _parsimony_msa_ptr = _pmsa;
  const PartitionedMSA& part_msa = _parsimony_msa_ptr->part_msa();
  
  size_t weights_size = 0;
  int msa_patterns = 0;

  for (const auto& pinfo: part_msa.part_list()) msa_patterns += pinfo.length();
  
  //const double msa_patterns   = (double)partitioned_msa_ptr->full_msa().length();
  _features->patterns          = msa_patterns;
  _features->patterns_per_taxa = (double) msa_patterns / _features->taxa;

  _features->bollback_multinomial = 0;
  double bollback_multinomial_tmp = 0;
  int number_of_sites = 0;

  for (const auto& pinfo: part_msa.part_list())
  {
    int cur_num_sites = 0;
    weights_size = pinfo.msa().weights().size();
    if(weights_size > 0) assert(pinfo.length() == weights_size);
    
    unsigned int weights[pinfo.length()];
    for (size_t j=0; j < pinfo.msa().weights().size(); j++)
    {
      weights[j] = weights_size > 0 ? pinfo.msa().weights().at(j) : 1;
      if( weights[j] != 0 ) cur_num_sites += weights[j];
    }

    bollback_multinomial_tmp =
      corax_msa_bollback_multinomial(pinfo.msa().pll_msa_nonconst(), weights, _states_map);
    
    bollback_multinomial_tmp += cur_num_sites * log(cur_num_sites);
    _features->bollback_multinomial += bollback_multinomial_tmp;
    number_of_sites += cur_num_sites;
  }

  _features->bollback_multinomial -= number_of_sites*log(number_of_sites);
}

double DifficultyPredictor::predict_difficulty(int n_trees)
{
  map<std::string, unsigned int> labelToId;
  unsigned int score;
  int n_taxa = (int) _parsimony_msa_ptr->part_msa().taxon_count();
  
  // init seeds
  intVector seeds(n_trees);
  for (int i = 0; i < n_trees; ++i)
    seeds[i] = rand();

  // TODO parallelization
  for (int i = 0; i < n_trees; ++i)
    _pars_tree_list.emplace_back(Tree::buildParsimony(*_parsimony_msa_ptr, seeds[i], &score));
  
  // re-label trees
  for (int i = 0; i < n_taxa; ++i)
    labelToId.insert({std::string(_pars_tree_list[0].pll_utree().nodes[i]->label), i});

  for(size_t j = 0; j < _pars_tree_list.size(); j++)
  {
    const corax_utree_t * tree = &_pars_tree_list[j].pll_utree();
    for (int i = 0; i < n_taxa; ++i)
    {
      auto leaf        = tree->nodes[i];
      auto id          = labelToId.at(std::string(leaf->label));
      leaf->node_index = leaf->clv_index = id;
    }
  }

  // calculate rf distances - predict difficulty
  _rf_dist_calc->set_tree_list(_pars_tree_list);
  _rf_dist_calc->recalculate_rf();

  double num_unique = (double) _rf_dist_calc->num_uniq_trees() / n_trees;
  // printFeatures(rf_dist_calc->avg_rrf(), num_unique);

  double out_pred = corax_msa_predict_difficulty(_features, _rf_dist_calc->avg_rrf(), num_unique);
  out_pred = round(out_pred * 100.0) / 100.0;

  _difficulty = out_pred;

  labelToId.clear();

  // storing in binary file if configured
  write_adaptive_chkpt();

  return out_pred;
}

int DifficultyPredictor::num_start_trees(double diff, double amp, double mean, double s)
{
  int num_trees;

  num_trees = (int) (amp * normal_pdf(diff, mean, s));
  num_trees = min(num_trees, 10);
  num_trees = !num_trees ? 1 : num_trees;

  return num_trees;
}

double DifficultyPredictor::normal_pdf(double x, double m, double s)
{
  static const double inv_sqrt_2pi = 0.3989422804014327;
  double a = (x - m) / s;

  return inv_sqrt_2pi / s * std::exp(-0.5f * a * a);
}

void DifficultyPredictor::compute_msa_features(corax_msa_t* original_msa, size_t states,
                                               const corax_state_t *states_map)
{
  _features = (corax_msa_features *) calloc(1, sizeof(corax_msa_features));

  const double msa_taxa    = (double) original_msa->count;
  const double msa_sites   = (double) original_msa->length;
  _features->taxa           = msa_taxa;
  _features->sites          = msa_sites;
  _features->sites_per_taxa = msa_sites / msa_taxa;

  // new version 
  _states = states;
  _states_map = states_map;
  
  corax_msa_stats_t *msa_stats = corax_msa_compute_stats(
      original_msa,
      _states,
      _states_map,
      NULL,
      CORAX_MSA_STATS_GAP_PROP | CORAX_MSA_STATS_INV_PROP
          | CORAX_MSA_STATS_ENTROPY);

  libpll_check_error("ERROR computing MSA stats");
  assert(msa_stats);

  _features->proportion_gaps      = msa_stats->gap_prop;
  _features->proportion_invariant = msa_stats->inv_prop;
  _features->entropy              = msa_stats->entropy;

  corax_msa_destroy_stats(msa_stats);
}

void DifficultyPredictor::print_features(double avg_rff, double prop_unique)
{
  cout << "\n======================================================" << endl;
  cout << "Num taxa: " << _features->taxa << endl;
  cout << "Num sites: " << _features->sites << endl;
  cout << "Patterns: " << _features->patterns << endl;
  cout << "Patterns/taxa: " << _features->patterns_per_taxa << endl;
  cout << "Sites/taxa: " << _features->sites_per_taxa << endl;
  cout << "Gaps proportion: " << _features->proportion_gaps << endl;
  cout << "Proportion invariant: " << _features->proportion_invariant << endl;
  cout << "Entropy: " << _features->entropy << endl;
  cout << "Bollback: " << _features->bollback_multinomial << endl;
  cout << "Avg rf dist: " << avg_rff << endl;
  cout << "Proportion of unique topologies: " << prop_unique << endl;
  cout << "======================================================" << endl;

}

void DifficultyPredictor::write_adaptive_chkpt()
{
  if (_outfile.empty()) return;

  AdaptiveCheckpoint chpt(_difficulty);
  ofstream out(_outfile, ios::binary);

  if (!out)
  {
    cout << "WARNING!! Error in storing Pythia's score in binary file with suffix '.adaptiveCkp'. " << endl;
    cout << "There might occur errors when rerunning RAxML-NG from a checkpoint. " << endl;
  } 
  else
  {
    out.write( reinterpret_cast<char*>( &chpt.pythiaScore), sizeof(double));
    out.close();
  }
}


double DifficultyPredictor::load_adaptive_chkpt()
{
  AdaptiveCheckpoint chpt;
  _difficulty = -1;

  if (!_outfile.empty())
  {
    ifstream file (_outfile, ios::in | ios::binary);
    if (file.is_open())
    {
      file.read((char*)&chpt.pythiaScore, sizeof(double));
    } else
    {
      LOG_DEBUG << "Unable to open the binary file with suffix '.adaptiveCkp'" << endl;
      return -1;
    }

    if (chpt.pythiaScore >= 0 && chpt.pythiaScore <= 1)
      _difficulty = chpt.pythiaScore;
  }

  return _difficulty;
}

double DifficultyPredictor::load_pythia_score_from_log_file(const string& old_log_file)
{
  LOG_DEBUG << "Trying to load pythia score from log file " << endl;

  ifstream fileInput;
  string line;
  string query_line = "Predicted difficulty:"; // search in log files
  double pythia_score = -1;

  // open file to search
  fileInput.open(old_log_file.c_str());

  if(fileInput.is_open())
  {
    for(unsigned int curLine = 0; getline(fileInput, line); curLine++)
    {
      size_t pos = line.find(query_line);
      if (pos != string::npos)
      {
        string score_string = line.substr(pos+22); // position of pythia score
        pythia_score = std::stod(score_string);
      }
    }
    fileInput.close();
  }
  else
    cout << "WARNING! Unable to open the log file to search for the pythia score." << endl;

  return pythia_score;
}

