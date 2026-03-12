#include "RFDistCalculator.hpp"

using namespace std;

RFDistCalculator::RFDistCalculator() : _num_trees(0), _num_tips(0), _avg_rf(0.0), _avg_rrf(0.0), _num_uniq_trees(0) {}

RFDistCalculator::RFDistCalculator (const TreeList& trees, bool lowmem) :
    _num_trees(0), _num_tips(0), _avg_rf(0.0), _avg_rrf(0.0), _num_uniq_trees(0)
{ 
  tree_list = &trees;
  recalculate_rf(lowmem);
}

RFDistCalculator::~RFDistCalculator ()
{
}

void RFDistCalculator::recalculate_rf(bool lowmem){
  
  _rfdist_mat.clear();
  _split_occurence.clear();
  
  if (tree_list->size() > 1)
  { 
    _num_trees = tree_list->size();
    _num_tips = tree_list->at(0).num_tips();
    if (lowmem)
      calc_rfdist_lowmem(*tree_list);
    else
      calc_rfdist(*tree_list);
    
    // create the mapping of trees into topologies
    map_trees_into_topologies();
    
  } else
    throw runtime_error("Need at least 2 trees to compute RF distances! "
                        "Given: " + to_string(tree_list->size()));
  
}

unsigned int RFDistCalculator::get_frequency_of_topology(unsigned int topology_index){
  
  assert(_num_uniq_trees > 0); // we need to have at least one unique topology
  
  if(topology_index <= _num_uniq_trees - 1){
    return unique_topology_frequences.at(topology_index);
  } else
    throw runtime_error("The topology_index should be an unsigned int "
                          "between on the interval [0, num_uniq_trees()-1] \n");
} 

void RFDistCalculator::add_tree_splits(size_t tree_idx, const Tree& tree,
                                       bitv_hashtable_t * splits_hash)
{
  assert(splits_hash);
  assert(tree.num_tips() == _num_tips);
  assert(tree_idx < _num_trees);

  corax_split_t * splits = corax_utree_split_create(&tree.pll_utree_root(),
                                                 tree.num_tips(),
                                                 nullptr);

  for (size_t i = 0; i < tree.num_splits(); ++i)
  {
    bitv_hash_entry_t * e = corax_utree_split_hashtable_insert_single(splits_hash,
                                                                       splits[i],
                                                                       1.0);
    if (!e)
      libpll_check_error("Cannot add a split into hashtable: ", true);

    assert(e->bip_number <= _split_occurence.size());

    /* new split -> create bit vector with tree occurrence flags */
    if (e->bip_number ==_split_occurence.size())
      _split_occurence.emplace_back(bitVector(_num_trees));

    _split_occurence[e->bip_number][tree_idx] = true;
  }

  corax_utree_split_destroy(splits);
}

void RFDistCalculator::calc_rfdist(const TreeList& trees)
{
  bitv_hashtable_t * splits_hash = corax_utree_split_hashtable_create(_num_tips, 0);

  if (!splits_hash)
  {
    assert(corax_errno);
    libpll_check_error("Cannot create split hashtable");
  }

  /* add splits from all trees into a hashtable */
  for (size_t i = 0; i < _num_trees; ++i)
  {
    add_tree_splits(i, trees.at(i), splits_hash);
  }

  assert(_split_occurence.size() == splits_hash->entry_count);

  /* now compute all pairwise RF distances using hashtable */
  _rfdist_mat.resize(_num_trees * _num_trees, 0.);

  /* iterate over all splits in the hashtable */
  for (size_t i = 0; i < splits_hash->table_size; ++i)
  {
    bitv_hash_entry_t * e =  splits_hash->table[i];
    while (e != NULL)
    {
      assert(e->bip_number < splits_hash->entry_count);

      const auto& occ = _split_occurence[e->bip_number];
      for(size_t j = 0; j < _num_trees; j++)
      {
        if (occ[j])
        {
          for(size_t k = 0; k < _num_trees; k++)
          {
            if (j == k)
              continue;

            if (!occ[k])
            {
              _rfdist_mat[j * _num_trees + k]++;
            }
          }
        }
      }
      e = e->next;
    }
  }

  corax_utree_split_hashtable_destroy(splits_hash);

  /* compute averages */
  _avg_rf = std::accumulate(_rfdist_mat.begin(), _rfdist_mat.end(), 0);
  _num_uniq_trees = 1;
  for(size_t j = 0; j < _num_trees-1; j++)
  {
    bool uniq = true;
    for(size_t k = j+1; k < _num_trees; k++)
    {
      auto rf = _rfdist_mat[j * _num_trees + k] + _rfdist_mat[k * _num_trees + j];
      _rfdist_mat[j * _num_trees + k] = _rfdist_mat[k * _num_trees + j] = rf;
      uniq &= (rf > 0);
    }

    if (uniq)
      _num_uniq_trees++;
  }

  auto num_pairs = _num_trees * (_num_trees - 1) / 2;
  _avg_rf /= num_pairs;
  _avg_rrf = _avg_rf / maxrf();
}

void RFDistCalculator::calc_rfdist_lowmem(const TreeList& trees)
{
  assert(trees.size() > 0);

  /* extract splits from all trees */
  std::vector<corax_split_t *> splits(_num_trees);
  for (size_t i = 0; i < _num_trees; ++i)
  {
    const auto& tree = trees.at(i);
    splits[i] = corax_utree_split_create(&tree.pll_utree_root(),
                                          tree.num_tips(),
                                          nullptr);
  }

  _avg_rf = 0.0;
  _avg_rrf = 0.0;
  _num_uniq_trees = 1;
  size_t num_pairs = 0;

  for (size_t i = 0; i < _num_trees-1; ++i)
  {
    bool uniq = true;
    for (size_t j = i+1; j < _num_trees; ++j)
    {
      auto rf = corax_utree_split_rf_distance(splits[i], splits[j], _num_tips);
      _avg_rf += rf;

      // TODO: maxrf will be different for multifurcating trees
      double rrf = ((double) rf) / maxrf();
      _avg_rrf += rrf;

      uniq &= (rf > 0);
      num_pairs++;
    }

    if (uniq)
      _num_uniq_trees++;
  }

  for (auto s: splits)
    corax_utree_split_destroy(s);

  _avg_rf /= num_pairs;
  _avg_rrf /= num_pairs;
}

double RFDistCalculator::avg_rf() const
{
  return _avg_rf;
}

double RFDistCalculator::avg_rrf() const
{
  return _avg_rrf;
}

size_t RFDistCalculator::num_uniq_trees() const
{
  return _num_uniq_trees;
}

double RFDistCalculator::maxrf() const
{
  return (double) 2 * (_num_tips - 3);
}

size_t RFDistCalculator::num_trees() const
{
  return _num_trees;
}

size_t RFDistCalculator::num_tips() const
{
  return _num_tips;
}

size_t RFDistCalculator::rf(size_t i, size_t j) const
{
  return _rfdist_mat.empty() ? 0 :_rfdist_mat[i * _num_trees + j];
}

double RFDistCalculator::rrf(size_t i, size_t j) const
{
 // TODO: maxrf will be different for multifurcating trees
 return rf(i, j) / maxrf();
}

void RFDistCalculator::map_trees_into_topologies(){
  
  // number of trees in treelist
  size_t num_trees = tree_list->size();
  tree_to_topology.clear();
  unique_topology_frequences.clear();
  
  // clear - resize and initialize mapping
  tree_topology_mapping.clear();
  tree_topology_mapping.resize(num_trees);
  for (size_t i=0; i < num_trees; i++) tree_topology_mapping[i] = -2; // initialize: set all elements to -2

  // based on the pre-calculated rf distances, create the unordered mapping
  unsigned int topology_counter = 0;
  for (size_t i=0; i < num_trees; i++){
    
    tree_topology_mapping[i] = (tree_topology_mapping[i] == -2) ? -1 : tree_topology_mapping[i];
    unsigned int freq = 1;

    if(tree_topology_mapping[i] == -1){
      
      for(size_t j = i+1; j < num_trees; j++){
        
        if(tree_topology_mapping[j] == -2){
          
          auto tmp_rf = rf(i, j);
          if(tmp_rf == 0){
            freq += 1;
            tree_topology_mapping[j] = i; 
          }

        }
      }

      // setting up the frequencies and topologies table
      tree_to_topology.insert({(unsigned int)i, topology_counter});
      unique_topology_frequences.push_back(freq);
      topology_counter++;
    }
  }

  assert(topology_counter == num_uniq_trees() && 
          tree_to_topology.size() == num_uniq_trees() &&
          unique_topology_frequences.size() == num_uniq_trees());
  
}

unsigned int RFDistCalculator::get_topology_with_highest_freq(){

  unsigned int max_freq_i = -1;
  unsigned int max_freq = 0;

  for(size_t i = 0; i<_num_uniq_trees; i++){
    unsigned int cur_freq = get_frequency_of_topology((unsigned int) i );
    if(cur_freq > max_freq){
      max_freq_i = i;
      max_freq = cur_freq;
    }
  }

  for(size_t i = 0; i<_num_uniq_trees; i++){
    if(i != max_freq_i){
      unsigned int cur_freq = get_frequency_of_topology((unsigned int) i );
      assert(cur_freq <= max_freq);
      if (cur_freq == max_freq)
        cout << "WARNING: Topologies " << max_freq_i << " and " << i <<
             " have equal frequency = " << cur_freq << ".\nHowever, only index " << max_freq_i << " is returned\n" << endl;
      
    }
  }

  return max_freq_i;

}

unsigned int RFDistCalculator::map_tree_into_topology(size_t i){

  if(tree_topology_mapping[i] == -1){
    return tree_to_topology.at( (unsigned int) i);
  } else
    return map_tree_into_topology(tree_topology_mapping[i]);
}

std::fstream& operator<<(std::fstream& stream, const RFDistCalculator& rfcalc)
{
  auto num_trees = rfcalc.num_trees();
  const string delim = "\t";
  if (num_trees > 0)
  {
    stream << fixed;
    for (size_t i = 0; i < num_trees-1; ++i)
    {
      for (size_t j = i+1; j < num_trees; ++j)
      {
        stream << i << delim << j << delim
               << rfcalc.rf(i, j) << delim << FMT_BL(rfcalc.rrf(i, j)) << endl;
      }
    }
  }
  return stream;
}
