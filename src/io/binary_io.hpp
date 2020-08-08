#ifndef RAXML_BINARY_IO_HPP_
#define RAXML_BINARY_IO_HPP_

#include "BinaryStream.hpp"
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

struct NullMSA {};

typedef std::pair<MSA&,RangeList&> MSARange;

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

template<typename T>
BasicBinaryStream& operator<<(BasicBinaryStream& stream, const std::set<T>& s)
{
  stream << s.size();
  for (auto const& v: s)
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

template<typename T>
BasicBinaryStream& operator>>(BasicBinaryStream& stream, std::set<T>& s)
{
  size_t set_size;
  stream >> set_size;

  for (size_t i = 0; i < set_size; ++i)
    s.insert(stream.get<T>());

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
BasicBinaryStream& operator>>(BasicBinaryStream& stream, MSARange mr);
BasicBinaryStream& operator>>(BasicBinaryStream& stream, NullMSA);

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


