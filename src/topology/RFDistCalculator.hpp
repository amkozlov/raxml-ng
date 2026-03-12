#ifndef RAXML_TOPOLOGY_RFDISTCALCULATOR_HPP_
#define RAXML_TOPOLOGY_RFDISTCALCULATOR_HPP_

#include "../Tree.hpp"
#include <map>

typedef std::vector<bool> bitVector;
//typedef std::vector<double> doubleVector;

class RFDistCalculator
{
public:
  RFDistCalculator();
  RFDistCalculator (const TreeList& trees, bool lowmem = false);
  virtual
  ~RFDistCalculator ();

public:
  size_t num_trees() const;
  size_t num_tips() const;
  size_t rf(size_t i, size_t j) const;
  double rrf(size_t i, size_t j) const;

  double avg_rf() const;
  double avg_rrf() const;
  size_t num_uniq_trees() const;

  /* get frequency of topology */
  unsigned int get_frequency_of_topology(unsigned int topology_index);

  /* In case thre treelist is updated */
  void set_tree_list(const TreeList& trees) { tree_list = &trees; }
  void recalculate_rf(bool lowmem = false);

  // returns to which topology a tree is mapped into
  unsigned int map_tree_into_topology(size_t i);

  // returns the index of topology with the highest frequency
  unsigned int get_topology_with_highest_freq();

private:
  size_t _num_trees;
  size_t _num_tips;
  uintVector _rfdist_mat;
  std::vector<bitVector> _split_occurence;
  
  // e.g. Num of unique topologues == 3
  // so topology 0 has frequency 1
  // topology 1 has frequency 5
  // topology 2 has frequency 4
  std::vector<unsigned int> unique_topology_frequences;
  
  /* unordered mapping of each tree in tree_list to its topology
     For example, if we have 5 trees and 3 distinct topologies, this mapping
     will tell us that trees 0, 2 are mapped into topology 0, trees 1 and 4 are mapped into
     topology 1 and tree 3 in mapped into topology 2.
  */
  intVector tree_topology_mapping;
  std::map<unsigned int, unsigned int> tree_to_topology;
  
  // pointer to the tree list
  const TreeList* tree_list;

  double _avg_rf;
  double _avg_rrf;
  size_t _num_uniq_trees;

  void calc_rfdist(const TreeList& trees);
  void calc_rfdist_lowmem(const TreeList& trees);
  void add_tree_splits(size_t tree_idx, const Tree& tree,
                       bitv_hashtable_t * splits_hash);
  double maxrf() const;

  /* create the tree-topology mapping */
  void map_trees_into_topologies();

};

std::fstream& operator<<(std::fstream& stream, const RFDistCalculator& rfcalc);

#endif /* RAXML_TOPOLOGY_RFDISTCALCULATOR_HPP_ */
