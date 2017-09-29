#include "TerraceWrapper.hpp"

#include "../PartitionedMSA.hpp"

#include <terraces/errors.hpp>

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
    bm_(parted_msa.full_msa().size() * 2 - 1, parted_msa.part_count())
{
  auto tree = parse_nwk(nwk_string);

  /* init partition presence/absence matrix */
  assert(bm_.rows() == tree.tree.size());
  set(bm_, tree.indices, true);
  for (size_t p = 0; p < bm_.cols(); ++p)
  {
    auto& pinfo = parted_msa.part_info(p);
    for (size_t i = 0; i < pinfo.stats()->gap_seqs_count; ++i)
    {
      auto seq_id = pinfo.stats()->gap_seqs[i];
      auto label = parted_msa.full_msa().label(seq_id);
      auto row = tree.indices[label];
      bm_.set(row, p, false);
    }
  }

  LOG_DEBUG << bm_ << std::endl;

  auto root_index = find_root(bm_);

  if (root_index == terraces::none)
    throw terraces::no_usable_root_error("Cannot find any taxon with data in all partitions!");

  LOG_DEBUG << "root:" << root_index << ": ";
  LOG_DEBUG << tree.names.at(root_index) <<  std::endl;

  LOG_DEBUG << "Names:" << std::endl;
  for (auto n: tree.names)
    LOG_DEBUG << n << std::endl;
  LOG_DEBUG << std::endl;

  names_ = tree.names;
  reroot_inplace(tree.tree, root_index);
  supertree_ = prepare_constraints(tree.tree, bm_, tree.names, root_index);
}

std::uint64_t TerraceWrapper::terrace_size()
{
  return count_terrace(supertree_);
}

void TerraceWrapper::print_terrace(std::ostream& output)
{
  auto result = terraces::print_terrace(supertree_, names_, output);
}

