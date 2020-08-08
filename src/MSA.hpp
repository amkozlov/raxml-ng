#ifndef RAXML_MSA_HPP_
#define RAXML_MSA_HPP_

#include "common.h"

typedef std::vector<double> ProbVector;
typedef std::vector<ProbVector> ProbVectorList;

struct Range
{
  size_t start;
  size_t length;

  Range(size_t s, size_t l) : start(s), length(l) {}
};

typedef std::vector<Range> RangeList;

class MSA
{
public:
//  typedef std::unordered_map<std::string, std::string> container;
  typedef std::vector<std::string> container;
  typedef typename container::iterator        iterator;
  typedef typename container::const_iterator  const_iterator;

  MSA() : _length(0), _num_sites(0), _states(0), _pll_msa(NULL), _dirty(false) {};
  MSA(const unsigned int num_sites) : _length(0), _num_sites(num_sites),
      _states(0), _pll_msa(nullptr), _dirty(false) {};
  MSA(const RangeList& rl);

  MSA(const pll_msa_t * pll_msa);
  MSA(MSA&& other);
  MSA(const MSA& other) = delete;

  ~MSA();

  MSA& operator=(MSA&& other);
  MSA& operator=(const MSA& other) = delete;

  void append(const std::string& sequence, const std::string& header = "");
  void compress_patterns(const pll_state_t * charmap, bool store_backmap = false);

  bool empty() const { return _sequences.empty(); }
  size_t size() const { return _sequences.size(); }
  size_t length() const { return _length; }
  size_t num_sites() const { return _num_sites; }
  size_t num_patterns() const { return _weights.size(); }
  const WeightVector& weights() const {return _weights; }
  const NameIdMap& label_id_map() const { return _label_id_map; }
  const WeightVector site_pattern_map() const { return _site_pattern_map; }
  const pll_msa_t * pll_msa() const;

  const container& labels() const { return _labels; };
  const std::string& label(size_t index) const { return _labels.at(index); }
  const std::string& at(const std::string& label) const
  { return _sequences.at(_label_id_map.at(label)); }
  const std::string& at(size_t index) const { return _sequences.at(index); }
  const std::string& operator[](const std::string& label) const { return at(label); }
  const std::string& operator[](size_t index) const { return at(index); }
  std::string& operator[](size_t index) { return _sequences.at(index); }

  bool probabilistic() const { return _states > 0; }
  bool normalized() const;
  size_t states() const { return _states; }
  void states(size_t states);
  const ProbVector& probs(size_t index) const { return _probs.at(index); }
  ProbVector::const_iterator probs(size_t index, size_t site) const;
  ProbVector::iterator probs(size_t index, size_t site);

  doubleVector state_freqs() const;

  void num_sites(const unsigned int sites) { _num_sites = sites; }
  void weights(const WeightVector& v);
  void weights(WeightVector&& v);

  void remove_sites(const std::vector<size_t>& site_indices);

  const RangeList& local_seq_ranges() const;
  size_t get_local_offset(size_t global_offset) const;

  //Iterator Compatibility
  iterator begin() { return _sequences.begin(); }
  iterator end() { return _sequences.end(); }
  const_iterator begin() const { return _sequences.cbegin(); }
  const_iterator end() const { return _sequences.cend(); }
  const_iterator cbegin() { return _sequences.cbegin(); }
  const_iterator cend() { return _sequences.cend(); }

  const_iterator label_cbegin() const { return _labels.cbegin(); }
  const_iterator label_cend() const { return _labels.cend(); }

private:
  // Data Members
  size_t _length;
  size_t _num_sites;
  container _sequences;
  container _labels;
  NameIdMap _label_id_map;
  WeightVector _weights;
  WeightVector _site_pattern_map;
  ProbVectorList _probs;
  RangeList _local_seq_ranges;
  size_t _states;
  mutable pll_msa_t * _pll_msa;
  mutable bool _dirty;

  void update_pll_msa() const;
  void free_pll_msa() noexcept;

  void update_num_sites();

  void local_seq_ranges(const RangeList& rl);
};

#endif /* RAXML_MSA_HPP_ */
