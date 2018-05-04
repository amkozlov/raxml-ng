#ifndef RAXML_TERRACES_TERRACEWRAPPER_HPP_
#define RAXML_TERRACES_TERRACEWRAPPER_HPP_

#include <terraces/advanced.hpp>
#include <terraces/parser.hpp>

class PartitionedMSA;

class TerraceWrapper
{
public:
  TerraceWrapper (const PartitionedMSA& part_msa, const std::string& nwk_string);

  std::uint64_t terrace_size();
  void print_terrace(std::ostream& output);

private:
  terraces::bitmatrix _bm;
  terraces::name_map _names;
  terraces::index_map _indices;
  terraces::supertree_data _supertree;
};

#endif /* RAXML_TERRACES_TERRACEWRAPPER_HPP_ */
