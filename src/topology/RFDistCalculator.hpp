#ifndef RAXML_TOPOLOGY_RFDISTCALCULATOR_HPP_
#define RAXML_TOPOLOGY_RFDISTCALCULATOR_HPP_

#include "../Tree.hpp"

typedef std::vector<bool> bitVector;

class RFDistCalculator
{
public:
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

private:
  size_t _num_trees;
  size_t _num_tips;
  uintVector _rfdist_mat;
  std::vector<bitVector> _split_occurence;

  double _avg_rf;
  double _avg_rrf;
  size_t _num_uniq_trees;

  void calc_rfdist(const TreeList& trees);
  void calc_rfdist_lowmem(const TreeList& trees);
  void add_tree_splits(size_t tree_idx, const Tree& tree,
                       bitv_hashtable_t * splits_hash);
  double maxrf() const;
};

std::fstream& operator<<(std::fstream& stream, const RFDistCalculator& rfcalc);

#endif /* RAXML_TOPOLOGY_RFDISTCALCULATOR_HPP_ */
