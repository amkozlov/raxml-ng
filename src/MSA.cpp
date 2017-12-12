#include <stdexcept>
#include <algorithm>

#include "MSA.hpp"

using namespace std;

MSA::MSA(const pll_msa_t *pll_msa) :
    _length(0), _num_sites(pll_msa->length), _states(0), _pll_msa(nullptr)
{
  for (auto i = 0; i < pll_msa->count; ++i)
  {
    append(string(pll_msa->sequence[i], pll_msa->length), pll_msa->label ? pll_msa->label[i] : "");
  }

  update_pll_msa();
}

MSA::MSA(MSA&& other) : _length(other._length), _num_sites(other._num_sites),
    _sequences(move(other._sequences)), _labels(move(other._labels)),
    _label_id_map(move(other._label_id_map)), _weights(move(other._weights)),
    _probs(move(other._probs)), _states(other._states), _pll_msa(other._pll_msa),
    _dirty(other._dirty)
{
  other._length = other._num_sites = 0;
  other._pll_msa = nullptr;
  other._dirty = false;
};

MSA::~MSA()
{
  free_pll_msa();
}

MSA& MSA::operator=(MSA&& other)
{
  if (this != &other)
  {
    // release the current object’s resources
    free_pll_msa();
    _weights.clear();
    _sequences.clear();
    _labels.clear();
    _label_id_map.clear();

    // steal other’s resource
    _length = other._length;
    _num_sites = other._num_sites;
    _pll_msa = other._pll_msa;
    _weights = std::move(other._weights);
    _sequences = std::move(other._sequences);
    _labels = std::move(other._labels);
    _label_id_map = std::move(other._label_id_map);
    _probs = std::move(other._probs);
    _states = other._states;
    _dirty = other._dirty;

    // reset other
    other._length = other._num_sites = other._states = 0;
    other._pll_msa = nullptr;
    other._dirty = false;
  }
  return *this;
}

void MSA::free_pll_msa() noexcept
{
  if (_pll_msa)
  {
    free(_pll_msa->sequence);
    if (_pll_msa->label)
      free(_pll_msa->label);
    free(_pll_msa);
    _pll_msa = nullptr;
  }
}

void MSA::append(const string& sequence, const string& header)
{
  if(_length && sequence.length() != (size_t) _length)
    throw runtime_error{string("Tried to insert sequence to MSA of unequal length: ") + sequence};

  _sequences.push_back(sequence);

  if (!header.empty())
  {
    _labels.push_back(header);
    _label_id_map[header] = _labels.size() - 1;
  }

  if (!_length)
  {
    _length = sequence.length();
    if (!_num_sites)
      _num_sites = _length;
    if (_weights.empty())
      _weights.assign(_length, 1.);
  }

  _dirty = true;
}

void MSA::compress_patterns(const unsigned int * charmap)
{
  update_pll_msa();

  assert(_pll_msa->count && _pll_msa->length);

  const unsigned int * w = pll_compress_site_patterns(_pll_msa->sequence,
                                                      charmap,
                                                      _pll_msa->count,
                                                      &(_pll_msa->length));

  if (!w)
    throw runtime_error("Pattern compression failed!");

  _length = _pll_msa->length;
  _weights = WeightVector(w, w + _pll_msa->length);

  for (auto& entry : _sequences)
  {
    entry.resize(_length);
  }

  _dirty = false;
}


const pll_msa_t * MSA::pll_msa() const
{
  update_pll_msa();
  return _pll_msa;
}

void MSA::update_pll_msa() const
{
  if (!_pll_msa)
  {
    _pll_msa = (pll_msa_t *) calloc(1, sizeof(pll_msa_t));
    _dirty = true;
  }

  assert(_labels.empty() || _labels.size() == _sequences.size());

  if (_dirty)
  {
    _pll_msa->count = size();
    _pll_msa->length = length();

    size_t i = 0;
    _pll_msa->sequence = (char **) calloc(_pll_msa->count, sizeof(char *));
    for (const auto& entry : _sequences)
    {
      _pll_msa->sequence[i] = (char *) entry.c_str();
      ++i;
    }
    assert(i == size());

    if (!_labels.empty())
    {
      i = 0;
      _pll_msa->label = (char **) calloc(_pll_msa->count, sizeof(char *));
      for (const auto& entry : _labels)
      {
        _pll_msa->label[i] = (char *) entry.c_str();
        ++i;
      }
      assert(i == size());
    }

    _dirty = false;
  }
}

void MSA::states(size_t states)
{
  _states = states;
  if (size() > 0)
  {
    _probs.resize(size());
    for (auto& v: _probs)
    {
      v.resize(_length * _states);
    }
  }
}

ProbVector::const_iterator MSA::probs(size_t index, size_t site) const
{
  return _probs.at(index).cbegin() + site * _states;
}

ProbVector::iterator MSA::probs(size_t index, size_t site)
{
  return _probs.at(index).begin() + site * _states;
}

bool MSA::normalized() const
{
  if (!probabilistic())
    return true;

  for (const auto& pv: _probs)
  {
    for (auto p: pv)
    {
      if (p > 1.)
        return false;
    }
  }

  return true;
}

doubleVector MSA::state_freqs() const
{
  assert(_states > 0);

  double sum = 0;
  doubleVector freqs(_states, 0.);
  for (const auto& pv: _probs)
  {
    for (auto p = pv.cbegin(); p != pv.cend();)
    {
      for (size_t i = 0; i < _states; ++i, ++p)
      {
        freqs[i] += *p;
        sum += *p;
      }
    }
  }

  assert(sum > 0.);

//  double total_bases = _length * size();
  for (size_t i = 0; i < _states; ++i)
    freqs[i] /= sum;

  return freqs;
}

void MSA::remove_sites(const std::vector<size_t>& site_indices)
{
  if (site_indices.empty())
    return;

  assert(_length);

  auto sorted_indicies = site_indices;

  std::sort(sorted_indicies.begin(), sorted_indicies.end());

  if (sorted_indicies.back() >= _length)
    throw out_of_range("Invalid site index");

  auto new_length = _length - sorted_indicies.size();
  for (auto& s: _sequences)
  {
    size_t pos = 0;
    auto ignore = sorted_indicies.cbegin();
    for (size_t i = 0; i < s.size(); ++i)
    {
      if (ignore == sorted_indicies.cend() || i != *ignore)
      {
        s[pos++] = s[i];
      }
      else
        ignore++;
    }
    assert(pos == new_length);
    s.resize(new_length);
  }

  if (!_weights.empty())
  {
    assert(_weights.size() == _length);
    size_t pos = 0;
    auto ignore = sorted_indicies.cbegin();
    for (size_t i = 0; i < _weights.size(); ++i)
    {
      if (ignore == sorted_indicies.cend() || i != *ignore)
      {
        _weights[pos++] = _weights[i];
      }
      else
        ignore++;
    }
    assert(pos == new_length);
    _weights.resize(new_length);
  }

  _length = new_length;
  _dirty = true;
}

