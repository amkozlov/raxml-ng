#ifndef RAXML_MSA_HPP_
#define RAXML_MSA_HPP_

#include "common.h"

typedef std::vector<double> ProbVector;
typedef std::vector<ProbVector> ProbVectorList;

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
  MSA(const pll_msa_t * pll_msa);
  MSA(MSA&& other);
  MSA(const MSA& other) = delete;

  ~MSA();

  MSA& operator=(MSA&& other);
  MSA& operator=(const MSA& other) = delete;

  void append(const std::string& sequence, const std::string& header = "");
  void compress_patterns(const pll_state_t * charmap);

  bool empty() const { return _sequences.empty(); }
  size_t size() const { return _sequences.size(); }
  size_t length() const { return _length; }
  size_t num_sites() const { return _num_sites; }
  size_t num_patterns() const { return _weights.size(); }
  const WeightVector& weights() const {return _weights; }
  const NameIdMap& label_id_map() const { return _label_id_map; }
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

  void site_name(size_t index, const std::string& name);
  const NameList& site_names() const { return _site_names; }

  void num_sites(const unsigned int sites) { _num_sites = sites; }
  void weights(const WeightVector& v) { _weights = v; update_num_sites(); }
  void weights(WeightVector&& v) { _weights = std::move(v); update_num_sites(); }

  void remove_sites(const std::vector<size_t>& site_indices);

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
  NameList _site_names;
  WeightVector _weights;
  ProbVectorList _probs;
  size_t _states;
  mutable pll_msa_t * _pll_msa;
  mutable bool _dirty;

  void update_pll_msa() const;
  void free_pll_msa() noexcept;

  void update_num_sites();
};

#endif /* RAXML_MSA_HPP_ */
