#include "TerraceWrapper.hpp"

#include "../PartitionedMSA.hpp"
#include "../io/file_io.hpp"

#include <terraces/errors.hpp>
#include <terraces/rooting.hpp>

using namespace terraces;

LogStream& operator<<(LogStream& s,
                      const std::pair<const terraces::bitmatrix&, const terraces::name_map&>& nbm)
{
  auto bm = nbm.first;
  auto names = nbm.second;
  s << bm.rows() << " " << bm.cols() << std::endl;
  for (auto row = terraces::index_t{}; row < bm.rows(); ++row)
  {
    for (auto col = terraces::index_t{}; col < bm.cols(); ++col)
      s << bm.get(row, col) << " ";
    s << names.at(row) <<  std::endl;
  }

  return s;
}

void set(terraces::bitmatrix& bm, bool val)
{
  for (auto row = terraces::index_t{}; row < bm.rows(); ++row)
    for (auto col = terraces::index_t{}; col < bm.cols(); ++col)
      bm.set(row, col, val);
}

void set(terraces::bitmatrix& bm, terraces::index_map indices, bool val)
{
  for (auto& it: indices)
    for (auto col = terraces::index_t{}; col < bm.cols(); ++col)
      bm.set(it.second, col, val);
}

TerraceWrapper::TerraceWrapper (const PartitionedMSA& parted_msa, const Tree& tree) :
    _bm(parted_msa.taxon_count(), parted_msa.part_count())
{
  /* init index<->name maps */
  _names.resize(parted_msa.taxon_count());
  for (size_t i = 0; i < parted_msa.taxon_count(); ++i)
  {
    auto label = parted_msa.taxon_names().at(i);
    _indices[label] = i;
    _names[i] = label;
  }

  /* init partition presence/absence matrix */
  set(_bm, true);
  for (size_t p = 0; p < _bm.cols(); ++p)
  {
    auto& pinfo = parted_msa.part_info(p);
    for (size_t i = 0; i < pinfo.stats().gap_seq_count(); ++i)
    {
      auto seq_id = pinfo.stats().gap_seqs[i];
      _bm.set(seq_id, p, false);
    }
  }

  LOG_DEBUG << std::endl << "Binary matrix:" << std::endl
            << std::make_pair(std::cref(_bm), std::cref(_names)) << std::endl;

  auto newick_str = to_newick_string_rooted(tree);
  LOG_DEBUG << "Tree: " << newick_str << std::endl << std::endl;

  auto terra_tree = parse_nwk(newick_str, _indices);

  LOG_DEBUG << "Names:" << std::endl;
  for (const auto& n: _names)
    LOG_DEBUG << n << std::endl;
  LOG_DEBUG << std::endl;

//  reroot_at_taxon_inplace(terra_tree, root_index);
  _supertree = create_supertree_data(terra_tree, _bm);
}

std::uint64_t TerraceWrapper::terrace_size()
{
  return count_terrace(_supertree);
}

void TerraceWrapper::print_terrace_newick(std::ostream& output)
{
  auto result = terraces::print_terrace(_supertree, _names, output);
  RAXML_UNUSED(result);
}

void TerraceWrapper::print_terrace_compressed(std::ostream& output)
{
  auto result = terraces::print_terrace_compressed(_supertree, _names, output);
  RAXML_UNUSED(result);
}

void TerraceWrapper::print_terrace(std::ostream& output)
{
  return print_terrace_compressed(output);
}
