#ifndef RAXML_BINARY_IO_HPP_
#define RAXML_BINARY_IO_HPP_

#include "../Model.hpp"
#include "../Tree.hpp"

enum class ModelBinaryFmt
{
  full = 0,
  def,
  params,
  paramsML
};

typedef std::tuple<const Model&, ModelBinaryFmt> BinaryModel;

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

public:
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

public:
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
  BinaryFileStream(const std::string& fname, std::ios_base::openmode mode) :
    _fstream(fname, std::ios::binary | mode) {}

public:
  void write(const void *data, size_t size) { _fstream.write((char*) data, size); }
  void read(void *data, size_t size) { _fstream.read((char*) data, size); }

private:
  std::fstream _fstream;
};

BasicBinaryStream& operator<<(BasicBinaryStream& stream, const std::string& s);

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

template<typename T1, typename T2>
BasicBinaryStream& operator<<(BasicBinaryStream& stream, const std::unordered_map<T1,T2>& map)
{
  stream << map.size();
  for (auto const& e: map)
    stream << e.first << e.second;

  return stream;
}

template<typename T1, typename T2>
BasicBinaryStream& operator<<(BasicBinaryStream& stream, const std::map<T1,T2>& map)
{
  stream << map.size();
  for (auto const& e: map)
    stream << e.first << e.second;

  return stream;
}

/**
 *  Reading
 */
BasicBinaryStream& operator>>(BasicBinaryStream& stream, std::string& s);

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

template<typename T1, typename T2>
BasicBinaryStream& operator>>(BasicBinaryStream& stream, std::unordered_map<T1,T2>& map)
{
  size_t map_size;
  stream >> map_size;

  map.clear();

  T1 key;
  T2 val;
  for (size_t i = 0; i < map_size; ++i)
  {
    stream >> key >> val;
    map.emplace(key, val);
  }

  return stream;
}

template<typename T1, typename T2>
BasicBinaryStream& operator>>(BasicBinaryStream& stream, std::map<T1,T2>& map)
{
  size_t map_size;
  stream >> map_size;

  map.clear();

  T1 key;
  T2 val;
  for (size_t i = 0; i < map_size; ++i)
  {
    stream >> key >> val;
    map.emplace(key, val);
  }

  return stream;
}

/**
 * Model I/O
 */
BasicBinaryStream& operator<<(BasicBinaryStream& stream, const SubstitutionModel& sm);
BasicBinaryStream& operator<<(BasicBinaryStream& stream, const Model& m);
BasicBinaryStream& operator<<(BasicBinaryStream& stream, std::tuple<const Model&, ModelBinaryFmt> bm);

BasicBinaryStream& operator>>(BasicBinaryStream& stream, Model& m);
BasicBinaryStream& operator>>(BasicBinaryStream& stream, std::tuple<Model&, ModelBinaryFmt> bm);
BasicBinaryStream& operator>>(BasicBinaryStream& stream, ModelMap& m);

/**
 * Partition I/O
 */

BasicBinaryStream& operator<<(BasicBinaryStream& stream, const PartitionStats& ps);
BasicBinaryStream& operator>>(BasicBinaryStream& stream, PartitionStats& ps);

/**
 * MSA I/O
 */
BasicBinaryStream& operator<<(BasicBinaryStream& stream, const MSA& m);
BasicBinaryStream& operator>>(BasicBinaryStream& stream, MSA& m);

/**
 * TreeTopology I/O
 */
BasicBinaryStream& operator<<(BasicBinaryStream& stream, const TreeTopology& t);
BasicBinaryStream& operator>>(BasicBinaryStream& stream, TreeTopology& t);

/**
 * TreeCollection I/O
 */
BasicBinaryStream& operator<<(BasicBinaryStream& stream, const ScoredTopologyMap& c);
BasicBinaryStream& operator>>(BasicBinaryStream& stream, ScoredTopologyMap& c);

/**
 * Options I/O
 */
BasicBinaryStream& operator<<(BasicBinaryStream& stream, const Options& o);
BasicBinaryStream& operator>>(BasicBinaryStream& stream, Options& o);

#endif


