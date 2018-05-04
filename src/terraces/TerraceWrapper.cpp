#include "TerraceWrapper.hpp"

#include "../PartitionedMSA.hpp"

#include <terraces/errors.hpp>
#include <terraces/rooting.hpp>

using namespace terraces;

LogStream& operator<<(LogStream& s, const terraces::bitmatrix& bm)
{

  for (auto row = terraces::index{}; row < bm.rows(); ++row)
  {
    for (auto col = terraces::index{}; col < bm.cols(); ++col)
      s << bm.get(row, col) << " ";
    s << std::endl;
  }

  return s;
}

terraces::index find_root(const terraces::bitmatrix& bm)
{
  terraces::index root = terraces::none;
  for (auto row = terraces::index{}; row < bm.rows(); ++row)
  {
    auto all_known = true;
    for (auto col = terraces::index{}; col < bm.cols(); ++col)
    {
      if (!bm.get(row, col))
      {
        all_known = false;
        break;
      }
    }
    if (all_known)
    {
      root = row;
      break;
    }
  }

  return root;
}

void set(terraces::bitmatrix& bm, bool val)
{
  for (auto row = terraces::index{}; row < bm.rows(); ++row)
    for (auto col = terraces::index{}; col < bm.cols(); ++col)
      bm.set(row, col, val);
}

void set(terraces::bitmatrix& bm, terraces::index_map indices, bool val)
{
  for (auto it: indices)
    for (auto col = terraces::index{}; col < bm.cols(); ++col)
      bm.set(it.second, col, val);
}

TerraceWrapper::TerraceWrapper (const PartitionedMSA& parted_msa, const std::string& nwk_string) :
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

  LOG_DEBUG << _bm << std::endl;

  auto root_index = find_root(_bm);

  if (root_index == terraces::none)
    throw terraces::no_usable_root_error("Cannot find any taxon with data in all partitions!");

  auto tree = parse_nwk(nwk_string, _indices);
//  assert(_bm.rows() == tree.size());

  LOG_DEBUG << "root:" << root_index << ": ";
  LOG_DEBUG << _names.at(root_index) <<  std::endl;

  LOG_DEBUG << "Names:" << std::endl;
  for (auto n: _names)
    LOG_DEBUG << n << std::endl;
  LOG_DEBUG << std::endl;

  reroot_at_taxon_inplace(tree, root_index);
  _supertree = prepare_constraints(tree, _bm, root_index);
}

std::uint64_t TerraceWrapper::terrace_size()
{
  return count_terrace(_supertree);
}

void TerraceWrapper::print_terrace(std::ostream& output)
{
  auto result = terraces::print_terrace(_supertree, _names, output);
  RAXML_UNUSED(result);
}

