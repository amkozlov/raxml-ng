#include "PartitionedMSA.hpp"

using namespace std;

PartitionedMSA::~PartitionedMSA ()
{
  // TODO Auto-generated destructor stub
}

PartitionedMSA& PartitionedMSA::operator=(PartitionedMSA&& other)
{
  _part_list = std::move(other._part_list);
  _full_msa = std::move(other._full_msa);
   return *this;
}

std::vector<unsigned int> PartitionedMSA::get_site_part_assignment()
{
  const size_t full_len = _full_msa.num_sites();

  std::vector<unsigned int> spa(full_len);

  size_t p = 0;
  for (auto& pinfo: _part_list)
  {
    try
    {
      pinfo.mark_partition_sites(p+1, spa);
    }
    catch (MultiplePartitionForSiteException& e)
    {
      e.pinfo2(_part_list.at(spa[e.site()-1]-1));
      throw e;
    }
    p++;
  }

  /* check if all sites were assigned to partitions */
  MissingPartitionForSiteException e_unassinged;
  for (size_t i = 0; i < full_len; ++i)
  {
    if (!spa[i])
    {
      LOG_INFO << "ERROR: Alignment site " << i+1 << " is not assigned to any partition!" << endl;
      e_unassinged.add_unassigned_site(i+1);
    }
  }

  if (e_unassinged.count() > 0)
    throw e_unassinged;

  return spa;
}

void PartitionedMSA::split_msa()
{
  if (part_count() > 1)
  {
    auto site_part = get_site_part_assignment();

    /* split MSA into partitions */
    pll_msa_t ** part_msa_list =
        pllmod_msa_split(_full_msa.pll_msa(), site_part.data(), part_count());

    for (size_t p = 0; p < part_count(); ++p)
    {
      part_msa(p, part_msa_list[p]);
      pll_msa_destroy(part_msa_list[p]);
    }
    free(part_msa_list);
  }
  else
  {
    if (_part_list[0].range_string().empty())
      _part_list[0].range_string("1-" + to_string(_full_msa.num_sites()));
    part_msa(0, std::move(_full_msa));
  }
}

void PartitionedMSA::compress_patterns()
{
  for (PartitionInfo& pinfo: _part_list)
  {
    pinfo.compress_patterns();
  }
}

size_t PartitionedMSA::total_length() const
{
  size_t sum = 0;

  for (const auto& pinfo: _part_list)
  {
    sum += pinfo.msa().length();
  }

  return sum;
}

void PartitionedMSA::set_model_empirical_params()
{
  for (PartitionInfo& pinfo: _part_list)
  {
    pinfo.set_modeL_empirical_params();
  }
}

std::ostream& operator<<(std::ostream& stream, const PartitionedMSA& part_msa)
{
  for (size_t p = 0; p < part_msa.part_count(); ++p)
  {
    const PartitionInfo& pinfo = part_msa.part_info(p);
    stream << "Partition " << p << ": " << pinfo.name() << endl;
    stream << "Model: " << pinfo.model().to_string() << endl;
    if (pinfo.msa().num_patterns())
    {
      stream << "Alignment sites / patterns: " << pinfo.msa().num_sites() <<
          " / " << pinfo.msa().num_patterns() << endl;
    }
    else
      stream << "Alignment sites: " << pinfo.msa().num_sites() << endl;

//    stream << fixed;
    stream << "Gaps: " << setprecision(2) << (pinfo.stats()->gap_prop * 100) << " %" << endl;
    stream << "Invariant sites: " << setprecision(2) << (pinfo.stats()->inv_prop * 100) << " %" << endl;
    stream << endl;
  }

  return stream;
}


