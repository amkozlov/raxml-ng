#ifndef RAXML_BINARY_IO_HPP_
#define RAXML_BINARY_IO_HPP_

#include "../Model.hpp"
#include "../Tree.hpp"

class BasicBinaryStream
{
public:
  virtual ~BasicBinaryStream() {}

  template<typename T>
  T get()
  {
    T tmp;
    *this >> tmp;
//    get(&tmp, sizeof(T));
    return tmp;
  }

  void get(void *data, size_t size) { read(data, size); };
  void put(const void *data, size_t size) { write(data, size); };

protected:
  virtual void read(void *data, size_t size) = 0;
  virtual void write(const void *data, size_t size) = 0;
};

class BinaryStream : public BasicBinaryStream
{
public:
  BinaryStream(char * buf, size_t size)
  {
    _buf = buf;
    _ptr = buf;
    _size = size;
  }

  ~BinaryStream() {}

//  template<typename T>
//  T get()
//  {
//    T tmp;
//    *this >> tmp;
//    return tmp;
//  }

  const char* buf() { return _buf; }
  size_t size() const { return _size; }
  size_t pos() const { return _ptr - _buf;}
  char* reset() { _ptr = _buf; return _buf; }

protected:
  void write(const void *data, size_t size)
  {
    if (_ptr + size > _buf + _size)
      throw std::out_of_range("BinaryStream::put");

    memcpy(_ptr, data, size);
    _ptr += size;
  }

  void read(void *data, size_t size)
  {
    if (_ptr + size > _buf + _size)
      throw std::out_of_range("BinaryStream::get");

    memcpy(data, _ptr, size);
    _ptr += size;
  }

private:
  char * _buf;
  char * _ptr;
  size_t _size;
};

class BinaryFileStream : public BasicBinaryStream
{
public:
  BinaryFileStream(const std::string fname, std::ios_base::openmode mode) :
    _fstream(fname, std::ios::binary | mode) {}

protected:
  void write(const void *data, size_t size) { _fstream.write((char*) data, size); }
  void read(void *data, size_t size) { _fstream.read((char*) data, size); }

private:
  std::fstream _fstream;
};

template<typename T>
BasicBinaryStream& operator<<(BasicBinaryStream& stream, T v)
{
  stream.put(&v, sizeof(T));

  return stream;
}

template<typename T>
BasicBinaryStream& operator<<(BasicBinaryStream& stream, const std::vector<T>& vec)
{
  stream << vec.size();
  for (auto const& v: vec)
    stream << v;

  return stream;
}

/**
 *  Reading
 */

template<typename T>
BasicBinaryStream& operator>>(BasicBinaryStream& stream, T& v)
{
  stream.get(&v, sizeof(T));

//  std::cout << "read value: " << v << std::endl;

  return stream;
}

template<typename T>
BasicBinaryStream& operator>>(BasicBinaryStream& stream, std::vector<T>& vec)
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

/**
 * Model I/O
 */
BasicBinaryStream& operator<<(BasicBinaryStream& stream, const SubstitutionModel& sm);
BasicBinaryStream& operator<<(BasicBinaryStream& stream, const Model& m);

BasicBinaryStream& operator>>(BasicBinaryStream& stream, Model& m);

/**
 * TreeCollection I/O
 */
BasicBinaryStream& operator<<(BasicBinaryStream& stream, const TreeCollection& c);
BasicBinaryStream& operator>>(BasicBinaryStream& stream, TreeCollection& c);

#endif


