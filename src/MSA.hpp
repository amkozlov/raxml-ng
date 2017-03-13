#ifndef RAXML_MSA_HPP_
#define RAXML_MSA_HPP_

#include "common.h"

typedef unsigned int WeightType;
typedef std::vector<WeightType> WeightVector;
typedef std::vector<WeightVector> WeightVectorList;
typedef std::unordered_map<size_t, WeightVector> WeightVectorMap;

class MSA
{
public:
//  typedef std::unordered_map<std::string, std::string> container;
  typedef std::vector<std::string> container;
  typedef typename container::iterator        iterator;
  typedef typename container::const_iterator  const_iterator;

  MSA() : _length(0), _num_sites(0), _pll_msa(NULL), _dirty(false) {};
  MSA(const unsigned int num_sites) : _length(0), _num_sites(num_sites),
      _pll_msa(nullptr), _dirty(false) {};
  MSA(const pll_msa_t * pll_msa);
  MSA(MSA&& other);
  MSA(const MSA& other) = delete;

  ~MSA();

  MSA& operator=(MSA&& other);
  MSA& operator=(const MSA& other) = delete;

  void append(const std::string& sequence, const std::string& header = "");
//  void erase(iterator begin, iterator end) { _sequence_map.erase(begin, end); };
  void compress_patterns(const unsigned int * charmap);

  // getters
  unsigned int size() const { return _sequences.size(); };
  unsigned int length() const { return _length; };
  unsigned int num_sites() const { return _num_sites; };
  unsigned int num_patterns() const { return _weights.size(); };
  const WeightVector& weights() const {return _weights; };
  const NameIdMap& label_id_map() const { return _label_id_map; };
  const pll_msa_t * pll_msa() const;
  const std::string& at(const std::string& label) const { return _sequences.at(_label_id_map.at(label)); };
  const std::string& at(size_t index) const { return _sequences.at(index); };
  const std::string& operator[](const std::string& name);

  // setters
  void num_sites(const unsigned int sites) {_num_sites = sites;};

  //Iterator Compatibility
  iterator begin() { return _sequences.begin(); };
  iterator end() { return _sequences.end(); };
  const_iterator begin() const { return _sequences.cbegin(); };
  const_iterator end() const { return _sequences.cend(); };
  const_iterator cbegin() { return _sequences.cbegin(); };
  const_iterator cend() { return _sequences.cend(); };

private:
  // Data Members
  unsigned int _length;
  unsigned int _num_sites;
  container _sequences;
  container _labels;
  NameIdMap _label_id_map;
  WeightVector _weights;
  mutable pll_msa_t * _pll_msa;
  mutable bool _dirty;

  void update_pll_msa() const;
  void free_pll_msa() noexcept;
};

MSA msa_load_from_file(const std::string &filename, const FileFormat format = FileFormat::autodetect);

#endif /* RAXML_MSA_HPP_ */
