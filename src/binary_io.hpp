#ifndef RAXML_BINARY_IO_HPP_
#define RAXML_BINARY_IO_HPP_

#include "Model.hpp"

class BinaryStream
{
public:
  BinaryStream(char * buf, size_t size)
  {
//    _buf = (void *) new char[4096];
    _buf = buf;
    _ptr = buf;
    _size = size;
  }

  ~BinaryStream()
  {
//    delete[] buf;
  }

  void put(const void *data, size_t size)
  {
    if (_ptr + size > _buf + _size)
      throw std::out_of_range("BinaryStream::put");

    memcpy(_ptr, data, size);
    _ptr += size;
  }

  void get(void *data, size_t size)
  {
    if (_ptr + size > _buf + _size)
      throw std::out_of_range("BinaryStream::get");

    memcpy(data, _ptr, size);
    _ptr += size;
  }

  template<typename T>
  T get()
  {
    T tmp;
    *this >> tmp;
    return tmp;
  }

  const char* buf() { return _buf; }
  size_t size() const { return _size; }
  size_t pos() const { return _ptr - _buf;}
  char* reset() { _ptr = _buf; return _buf; }

private:
  char * _buf;
  char * _ptr;
  size_t _size;
};

template<typename T>
BinaryStream& operator<<(BinaryStream& stream, T v)
{
  stream.put(&v, sizeof(T));

  return stream;
}

template<typename T>
BinaryStream& operator<<(BinaryStream& stream, const std::vector<T>& vec)
{
  stream << vec.size();
  for (auto const& v: vec)
    stream << v;

  return stream;
}

BinaryStream& operator<<(BinaryStream& stream, const SubstitutionModel& sm)
{
  stream << sm.base_freqs();
  stream << sm.subst_rates();

  return stream;
}

BinaryStream& operator<<(BinaryStream& stream, const Model& m)
{
//  if (m.param_mode(PLLMOD_OPT_PARAM_BRANCH_LEN_SCALER) != ParamValue::undefined)
  stream << m.brlen_scaler();

//  if (m.param_mode(PLLMOD_OPT_PARAM_PINV) != ParamValue::undefined)
    stream << m.pinv();

  stream << m.num_ratecats();

  if (m.num_ratecats() > 1)
  {
    stream << m.ratehet_mode();
    if (m.ratehet_mode() == PLLMOD_UTIL_MIXTYPE_GAMMA)
      stream << m.alpha();

    stream << m.ratecat_weights();
    stream << m.ratecat_rates();
  }

  /* store subst model parameters only if they were estimated */
  if (m.param_mode(PLLMOD_OPT_PARAM_FREQUENCIES) == ParamValue::ML ||
      m.param_mode(PLLMOD_OPT_PARAM_SUBST_RATES) == ParamValue::ML)
  {
    stream << m.num_submodels();
    for (size_t i = 0; i < m.num_submodels(); ++i)
    {
      stream << m.submodel(i);
    }
  }

  return stream;
}

/**
 *  Reading
 */

template<typename T>
BinaryStream& operator>>(BinaryStream& stream, T& v)
{
  stream.get(&v, sizeof(T));

//  std::cout << "read value: " << v << std::endl;

  return stream;
}

template<typename T>
BinaryStream& operator>>(BinaryStream& stream, std::vector<T>& vec)
{
  size_t vec_size;
  stream >> vec_size;
  vec.resize(vec_size);

  for (auto& v: vec)
    stream >> v;

  return stream;
}

//BinaryStream& operator>>(BinaryStream& stream, SubstitutionModel& sm)
//{
//  stream >> sm.base_freqs();
//  stream >> sm.subst_rates();
//
//  return stream;
//}

BinaryStream& operator>>(BinaryStream& stream, Model& m)
{
//  if (m.param_mode(PLLMOD_OPT_PARAM_BRANCH_LEN_SCALER) != ParamValue::undefined)
  m.brlen_scaler(stream.get<double>());

//  if (m.param_mode(PLLMOD_OPT_PARAM_PINV) != ParamValue::undefined)

  m.pinv(stream.get<double>());

  auto num_ratecats = stream.get<unsigned int>();

  assert(num_ratecats == m.num_ratecats());

  if (m.num_ratecats() > 1)
  {
    auto ratehet_mode = stream.get<unsigned int>();
    assert(ratehet_mode == m.ratehet_mode());

    if (m.ratehet_mode() == PLLMOD_UTIL_MIXTYPE_GAMMA)
      m.alpha(stream.get<double>());

    m.ratecat_weights(stream.get<doubleVector>());
    m.ratecat_rates(stream.get<doubleVector>());
  }

  if (m.param_mode(PLLMOD_OPT_PARAM_FREQUENCIES) == ParamValue::ML ||
      m.param_mode(PLLMOD_OPT_PARAM_SUBST_RATES) == ParamValue::ML)
  {
    auto num_submodels = stream.get<unsigned int>();
    assert(num_submodels == m.num_submodels());
    for (size_t i = 0; i < m.num_submodels(); ++i)
    {
      m.base_freqs(i, stream.get<doubleVector>());
      m.subst_rates(i, stream.get<doubleVector>());
    }
  }

  return stream;
}


#endif


