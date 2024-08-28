#include "DifficultyPredictor.hpp"
#include <memory>
#include <random>

DifficultyPredictor::DifficultyPredictor() : _difficulty(-1), _parsimony_msa_ptr(nullptr),
_features(nullptr), _prop_uniq(-1), _avg_rrf(-1)
{
  _rf_dist_calc.reset(new RFDistCalculator());
}

DifficultyPredictor::~DifficultyPredictor()
{
  free(_features);
  _pars_tree_list.clear();
}

void DifficultyPredictor::compute_msa_features(ParsimonyMSA* _pmsa)
{
  _parsimony_msa_ptr = _pmsa;
  const PartitionedMSA& part_msa = _parsimony_msa_ptr->part_msa();
  
  _features                    = (corax_msa_features *) calloc(1, sizeof(corax_msa_features));
  _features->taxa              = part_msa.taxon_count();
  _features->sites             = part_msa.total_sites();
  _features->sites_per_taxa    = _features->sites / _features->taxa;
  _features->patterns          = part_msa.total_patterns();
  _features->patterns_per_taxa = (double) _features->patterns / _features->taxa;

  _features->proportion_gaps      = 0.;
  _features->proportion_invariant = 0.;
  _features->entropy              = 0.;
  _features->bollback_multinomial = 0;

  double bollback_multinomial_tmp = 0;
  int number_of_sites = 0;

  for (const PartitionInfo& pinfo: part_msa.part_list())
  {
    auto& msa_stats = pinfo.stats();
    size_t cur_num_sites = msa_stats.site_count;
    double part_prop = cur_num_sites / _features->sites;

    assert(pinfo.length() == pinfo.msa().weights().size());

    _features->proportion_gaps      += part_prop * msa_stats.gap_prop;
    _features->proportion_invariant += part_prop * msa_stats.inv_prop;
    _features->entropy              += part_prop * msa_stats.mean_column_entropy;

    bollback_multinomial_tmp = corax_msa_bollback_multinomial(pinfo.msa().pll_msa(),
                                                              pinfo.msa().weights().data(),
                                                              pinfo.model().charmap());
    
    bollback_multinomial_tmp += cur_num_sites * log(cur_num_sites);
    _features->bollback_multinomial += bollback_multinomial_tmp;
    number_of_sites += cur_num_sites;
  }
  assert(number_of_sites == _features->sites);

  _features->bollback_multinomial -= number_of_sites * log(number_of_sites);
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

  labelToId.clear();

  return predict_difficulty(_pars_tree_list);
}

double DifficultyPredictor::predict_difficulty(const TreeList& pars_trees)
{
  // calculate rf distances - predict difficulty
  _rf_dist_calc->set_tree_list(pars_trees);
  _rf_dist_calc->recalculate_rf();

  _prop_uniq = (double) _rf_dist_calc->num_uniq_trees() / _rf_dist_calc->num_trees();
  _avg_rrf = _rf_dist_calc->avg_rrf();

  double out_pred = corax_msa_predict_difficulty(_features, _rf_dist_calc->avg_rrf(), _prop_uniq);
  out_pred = round(out_pred * 100.0) / 100.0;

  _difficulty = out_pred;

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

void DifficultyPredictor::print_features()
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
  cout << "Avg rf dist: " << _avg_rrf << endl;
  cout << "Proportion of unique topologies: " << _prop_uniq << endl;
  cout << "======================================================" << endl;

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

LogStream& operator<<(LogStream& stream, const DifficultyPredictor& dp)
{
  auto feat = dp.features();

  if (feat)
  {
    stream << "Pythia features: " << endl;
    stream << "  Num taxa: " << feat->taxa << endl;
    stream << "  Num sites: " << feat->sites << endl;
    stream << "  Patterns: " << feat->patterns << endl;
    stream << "  Patterns/taxa: " << FMT_PREC2(feat->patterns_per_taxa) << endl;
    stream << "  Sites/taxa: " << FMT_PREC2(feat->sites_per_taxa) << endl;
    stream << "  Gaps proportion: " << FMT_PREC2(feat->proportion_gaps) << endl;
    stream << "  Invariant proportion: " << FMT_PREC2(feat->proportion_invariant) << endl;
    stream << "  Entropy: " << FMT_LH(feat->entropy) << endl;
    stream << "  Bollback: " << FMT_LH(feat->bollback_multinomial) << endl;
    stream << "  Avg rf dist: " << FMT_LH(dp.avg_rrf()) << endl;
    stream << "  Proportion of unique topologies: " << FMT_PREC2(dp.prop_uniq()) << endl;
    stream << endl;
  }
  stream << "Pythia difficulty score: " << FMT_PREC2(dp.difficulty()) << endl;

  return stream;
}

