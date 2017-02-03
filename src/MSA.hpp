#ifndef RAXML_MSA_HPP_
#define RAXML_MSA_HPP_

#include "common.h"

class MSA
{
public:
  typedef std::unordered_map<std::string, std::string> container;
  typedef typename container::iterator        iterator;
  typedef typename container::const_iterator  const_iterator;

  MSA() : _length(0), _num_sites(0), _pll_msa(nullptr), _dirty(false) {};
  MSA(const unsigned int num_sites) : _length(0), _num_sites(num_sites),
      _pll_msa(nullptr), _dirty(false) {};
  MSA(const pll_msa_t * pll_msa);
  MSA(MSA&& other) = default;
  ~MSA();

  MSA& operator=(MSA&& other);

  void append(const std::string& header, const std::string& sequence);
  void erase(iterator begin, iterator end) {_sequence_map.erase(begin, end);};
  void compress_patterns(const unsigned int * charmap);

  // getters
  unsigned int size() const { return _sequence_map.size(); };
  unsigned int length() const { return _length; };
  unsigned int num_sites() const { return _num_sites; };
  unsigned int num_patterns() const { return _weights.size(); };
  const unsigned int * weights() const {return _weights.empty() ? nullptr : _weights.data(); };
  const pll_msa_t * pll_msa() const;
  const std::string& at(const std::string& name) const { return _sequence_map.at(name); };
  const std::string& operator[](const std::string& name);

  // setters
  void num_sites(const unsigned int sites) {_num_sites = sites;};

  //Iterator Compatability
  iterator begin() { return _sequence_map.begin(); };
  iterator end() { return _sequence_map.end(); };
  const_iterator begin() const { return _sequence_map.cbegin(); };
  const_iterator end() const { return _sequence_map.cend(); };
  const_iterator cbegin() { return _sequence_map.cbegin(); };
  const_iterator cend() { return _sequence_map.cend(); };

private:
  // Data Members
  unsigned int _length;
  unsigned int _num_sites;
  container _sequence_map;
  std::vector<unsigned int> _weights;
  mutable pll_msa_t * _pll_msa;
  mutable bool _dirty;

  void update_pll_msa() const;
  void free_pll_msa() noexcept;
};

MSA msa_load_from_file(const std::string &filename, const FileFormat format = FileFormat::autodetect);

#endif /* RAXML_MSA_HPP_ */
