#include "PartitionedMSAView.hpp"

using namespace std;

PartitionedMSAView::PartitionedMSAView (std::shared_ptr<const PartitionedMSA> parted_msa):
  _parted_msa(parted_msa.get()), _parted_msa_sptr(parted_msa)
{
}

PartitionedMSAView::PartitionedMSAView (const PartitionedMSA& parted_msa):
  _parted_msa(&parted_msa), _parted_msa_sptr(0)
{
}

PartitionedMSAView::~PartitionedMSAView ()
{
}

bool PartitionedMSAView::identity() const
{
  return excluded_site_count() == 0 && _excluded_taxa.empty() && _taxon_name_map.empty();
}

size_t PartitionedMSAView::taxon_count() const
{
  return _parted_msa->taxon_count() - _excluded_taxa.size();
};

string PartitionedMSAView::taxon_name(size_t taxon_id) const
{
  auto orig_id = orig_taxon_id(taxon_id);
  auto orig_name = _parted_msa->taxon_names().at(orig_id);
  auto it = _taxon_name_map.find(orig_name);
  return it != _taxon_name_map.end() ? it->second : orig_name;
}

const NameMap& PartitionedMSAView::taxon_name_map() const
{
  return _taxon_name_map;
}

void PartitionedMSAView::exclude_taxon(size_t taxon_id)
{
  if (taxon_id < _parted_msa->taxon_count())
  {
    _excluded_taxa.insert(taxon_id);
    _orig_taxon_ids.clear();
  }
  else
    throw std::out_of_range("PartitionedMSAView::exclude_taxon(): Taxon ID out of range");
}

void PartitionedMSAView::exclude_site(size_t part_id, size_t site_id)
{
  if (_excluded_sites.empty())
    _excluded_sites.resize(part_count());

  _excluded_sites.at(part_id).insert(site_id);
}

void PartitionedMSAView::exclude_sites(size_t part_id, IDVector site_ids)
{
  if (_excluded_sites.empty())
    _excluded_sites.resize(part_count());

  _excluded_sites.at(part_id).insert(site_ids.begin(), site_ids.end());
}

void PartitionedMSAView::map_taxon_name(std::string orig_name, std::string new_name)
{
  _taxon_name_map[orig_name] = new_name;
}

size_t PartitionedMSAView::part_count() const
{
  return _parted_msa->part_count();
}

size_t PartitionedMSAView::excluded_site_count() const
{
  size_t count = 0;

  for (const auto& v: _excluded_sites)
    count += v.size();

  return count;
}

size_t PartitionedMSAView::total_length() const
{
  return _parted_msa->total_length() - excluded_site_count();
}

const Model& PartitionedMSAView::part_model(size_t part_id) const
{
  return _parted_msa->model(part_id);
}

string PartitionedMSAView::part_name(size_t part_id) const
{
  return _parted_msa->part_info(part_id).name();
}

size_t PartitionedMSAView::part_length(size_t part_id) const
{
  if (_excluded_sites.empty() || _excluded_sites[part_id].empty())
    return _parted_msa->part_info(part_id).msa().length();
  else
    return _parted_msa->part_info(part_id).msa().length() - _excluded_sites[part_id].size();
}

string PartitionedMSAView::part_sequence(size_t taxon_id, size_t part_id) const
{
  auto orig_id = orig_taxon_id(taxon_id);

  if (_excluded_sites.empty() || _excluded_sites[part_id].empty())
    return _parted_msa->part_info(part_id).msa().at(orig_id);
  else
  {
    auto part_len = part_length(part_id);
    auto orig_seq = _parted_msa->part_info(part_id).msa().at(orig_id);
    string seq;
    seq.reserve(part_len);
    auto pos = 0;
    auto ex = _excluded_sites[part_id].begin();
    while (ex != _excluded_sites[part_id].end())
    {
      auto len = *ex - pos;
      if (len)
        seq.append(orig_seq, pos, len);
      pos += len+1;
      ex++;
    }
    seq.append(orig_seq, pos, string::npos);

    assert(seq.size() == part_len);
    return seq;
  }
}

size_t PartitionedMSAView::orig_taxon_id(size_t taxon_id) const
{
  if (_excluded_taxa.empty())
   return taxon_id;
  else
  {
    if (_orig_taxon_ids.empty())
    {
      _orig_taxon_ids.reserve(taxon_count());
      for (size_t i = 0; i < _parted_msa->taxon_count(); ++i)
      {
        if (!_excluded_taxa.count(i))
          _orig_taxon_ids.push_back(i);
      }
    }
    return _orig_taxon_ids.at(taxon_id);
  }
}
