#ifndef RAXML_TERRACES_TERRACEWRAPPER_HPP_
#define RAXML_TERRACES_TERRACEWRAPPER_HPP_

#include <terraces/advanced.hpp>

class PartitionedMSA;

class TerraceWrapper
{
public:
  TerraceWrapper (const PartitionedMSA& part_msa, const std::string& nwk_string);

  std::uint64_t terrace_size();
  void print_terrace(std::ostream& output);

private:
  terraces::bitmatrix bm_;
  terraces::name_map names_;
  terraces::supertree_data supertree_;
};

#endif /* RAXML_TERRACES_TERRACEWRAPPER_HPP_ */
