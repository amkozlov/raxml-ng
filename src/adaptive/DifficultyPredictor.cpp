#include "DifficultyPredictor.hpp"
#include <memory>
#include <random>

DifficultyPredictor::DifficultyPredictor(const string& _outfile, bool _nofiles_mode){
  rf_dist_calc.reset(new RFDistCalculator());
  outfile = _outfile;
  ckpt = false;
  best_ML = -INFINITY;
  nofiles_mode = _nofiles_mode;
}

DifficultyPredictor::~DifficultyPredictor(){
  
  free(features);
  pars_tree_list.clear();
  
}

void DifficultyPredictor::set_partitioned_msa_ptr(PartitionedMSA* _pmsa){
  
  partitioned_msa_ptr = _pmsa;
  
  size_t weights_size = 0;
  int msa_patterns = 0;

  for (const auto& pinfo: partitioned_msa_ptr->part_list()) msa_patterns += pinfo.length();
  
  //const double msa_patterns   = (double)partitioned_msa_ptr->full_msa().length();
  features->patterns          = msa_patterns;
  features->patterns_per_taxa = (double) msa_patterns / features->taxa;

  features->bollback_multinomial = 0;
  double bollback_multinomial_tmp = 0;
  int number_of_sites = 0;

  for (const auto& pinfo: partitioned_msa_ptr->part_list()){
    
    int cur_num_sites = 0;
    weights_size = pinfo.msa().weights().size();
    assert(pinfo.length() == weights_size);
    
    unsigned int weights[weights_size];
    for (size_t j=0; j < pinfo.msa().weights().size(); j++){
      weights[j] = pinfo.msa().weights().at(j);
      if( weights[j] != 0 ) cur_num_sites += weights[j];
    }

    bollback_multinomial_tmp =
      corax_msa_bollback_multinomial(pinfo.msa().pll_msa_nonconst(), weights, states_map);
    
    bollback_multinomial_tmp += cur_num_sites * log(cur_num_sites);
    features->bollback_multinomial += bollback_multinomial_tmp;
    number_of_sites += cur_num_sites;
  }

  features->bollback_multinomial -= number_of_sites*log(number_of_sites);
}

double DifficultyPredictor::predict_difficulty(unsigned int attrs, int n_trees, bool store_in_file){
  
  map<std::string, unsigned int> labelToId;
  unsigned int score;
  int n_taxa = (int) partitioned_msa_ptr->taxon_count();
  
  for (int i = 0; i < n_trees; ++i)
    pars_tree_list.emplace_back(Tree::buildParsimony(*partitioned_msa_ptr, i, attrs, &score));
  
  // re-label trees
  for (int i = 0; i < n_taxa; ++i)
    labelToId.insert({std::string(pars_tree_list[0].pll_utree().nodes[i]->label), i});

  for(size_t j = 0; j < pars_tree_list.size(); j++)
  {
    const corax_utree_t * tree = &pars_tree_list[j].pll_utree();
    for (int i = 0; i < n_taxa; ++i)
    {
      auto leaf        = tree->nodes[i];
      auto id          = labelToId.at(std::string(leaf->label));
      leaf->node_index = leaf->clv_index = id;
    }
  }

  // calculate rf distances - predict difficulty
  rf_dist_calc->set_tree_list(pars_tree_list);
  rf_dist_calc->recalculate_rf();

  double num_unique = (double) rf_dist_calc->num_uniq_trees() / n_trees;
  // printFeatures(rf_dist_calc->avg_rrf(), num_unique);

  double out_pred = corax_msa_predict_difficulty(features, rf_dist_calc->avg_rrf(), num_unique);
  out_pred = round(out_pred * 100.0) / 100.0;

  difficulty = out_pred;

  labelToId.clear();

  // storing in binary file before return
  if(store_in_file)
    store_difficulty_in_chkpt_file(out_pred, outfile);

  return out_pred;
}

int DifficultyPredictor::numStartTrees(double diff, double amp, double mean, double s){

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

void DifficultyPredictor::compute_msa_features(corax_msa_t* original_msa, bool _is_dna){
  
  features =
      (corax_msa_features *)calloc(1, sizeof(corax_msa_features));

  const double msa_taxa    = (double)original_msa->count;
  const double msa_sites   = (double)original_msa->length;
  features->taxa           = msa_taxa;
  features->sites          = msa_sites;
  features->sites_per_taxa = msa_sites / msa_taxa;

  // new version 
  is_dna = _is_dna;
  states_map = is_dna? corax_map_nt : corax_map_aa;
  states = is_dna? 4 : 20;
  
  corax_msa_stats_t *msa_stats = corax_msa_compute_stats(
      original_msa,
      states,
      states_map,
      NULL,
      CORAX_MSA_STATS_GAP_PROP | CORAX_MSA_STATS_INV_PROP
          | CORAX_MSA_STATS_ENTROPY);
  

  features->proportion_gaps      = msa_stats->gap_prop;
  features->proportion_invariant = msa_stats->inv_prop;
  features->entropy              = msa_stats->entropy;

  corax_msa_destroy_stats(msa_stats);
  
}

void DifficultyPredictor::printFeatures(double avg_rff, double prop_unique){

  cout << "\n======================================================" << endl;
  cout << "Num taxa: " << features->taxa << endl;
  cout << "Num sites: " << features->sites << endl;
  cout << "Patterns: " << features->patterns << endl;
  cout << "Patterns/taxa: " << features->patterns_per_taxa << endl;
  cout << "Sites/taxa: " << features->sites_per_taxa << endl;
  cout << "Gaps proportion: " << features->proportion_gaps << endl;
  cout << "Proportion invariant: " << features->proportion_invariant << endl;
  cout << "Entropy: " << features->entropy << endl;
  cout << "Bollback: " << features->bollback_multinomial << endl;
  cout << "Avg rf dist: " << avg_rff << endl;
  cout << "Proportion of unique topologies: " << prop_unique << endl;
  cout << "======================================================" << endl;

}

void DifficultyPredictor::store_difficulty_in_chkpt_file(double score, const string& out_file){

  if(nofiles_mode) return;

  AdaptiveCheckpoint chpt(score, best_ML);
  ofstream out(out_file, ios::binary);

  if(!out) {
    cout << "WARNING!! Error in storing Pythia's score in binary file with suffix '.adaptiveCkp'. " << endl;
    cout << "There might occur errors when rerunning RAxML-NG from a checkpoint. " << endl;
  } 
  else
  {
    out.write( reinterpret_cast<char*>( &chpt.pythiaScore), sizeof(double));
    out.write( reinterpret_cast<char*>( &chpt.bestML), sizeof(double));
    out.close();
  }
}


double DifficultyPredictor::load_adaptive_chkpt(const string& bin_file){
  
  AdaptiveCheckpoint chpt;
  difficulty = -1;

  ifstream file (bin_file, ios::in | ios::binary);
  if (file.is_open())
  {
      file.read((char*)&chpt.pythiaScore, sizeof(double));
      file.read((char*)&chpt.bestML, sizeof(double));
  
  } else {

    LOG_DEBUG << "Unable to open the binary file with suffix '.adaptiveCkp'" << endl;
    return -1;

  }

  if (chpt.pythiaScore >= 0 && chpt.pythiaScore <= 1)
    difficulty = chpt.pythiaScore;

  best_ML = chpt.bestML;

  return difficulty;
}

void DifficultyPredictor::set_best_ML(double _best_ML){
  if(_best_ML > best_ML){
    best_ML = _best_ML;
    store_difficulty_in_chkpt_file(difficulty, outfile);
  }
}