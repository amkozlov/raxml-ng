#ifndef RAXML_PARTITIONEDMSA_HPP_
#define RAXML_PARTITIONEDMSA_HPP_

#include "PartitionInfo.hpp"

class PartitionedMSA
{
public:
  PartitionedMSA() {};
  PartitionedMSA(const NameList& taxon_names);

  // copy/move constructors and assignments
  PartitionedMSA (PartitionedMSA&& other) = default;
  PartitionedMSA& operator=(PartitionedMSA&& other);

  // getters
  const MSA& full_msa() const { return (part_count() == 1) ? _part_list.at(0).msa() : _full_msa; };
  const MSA& part_msa(size_t index) const { return _part_list.at(index).msa(); };
  const PartitionInfo& part_info(size_t index) const { return _part_list.at(index); };
  const Model& model(size_t index) const { return _part_list.at(index).model(); };
  ModelCRefMap models() const;
  const std::vector<PartitionInfo>& part_list() const { return _part_list; };
  std::vector<PartitionInfo>& part_list() { return _part_list; };
  const NameList& taxon_names()  const { return _taxon_names; };
  const NameIdMap& taxon_id_map() const { return _taxon_id_map; }

  size_t full_msa_site(size_t index, size_t site) const;
  const uintVector& site_part_map() const;
  IdPairVector full_to_parted_sitemap() const;

  size_t taxon_count() const { return _taxon_names.size(); };
  size_t part_count() const { return _part_list.size(); };
  size_t total_sites() const;
  size_t total_patterns() const;
  size_t total_length() const;

  size_t total_free_model_params() const;

  /* given in elements (NOT in bytes) */
  size_t taxon_clv_size() const;

  // setters
  void full_msa(MSA&& msa);
  void part_msa(size_t index, MSA&& msa) { _part_list.at(index).msa(std::move(msa)); };
  void part_msa(size_t index, const pll_msa_t * pll_msa)
  {
    _part_list.at(index).msa(MSA(pll_msa));
  };
  void model(size_t index, Model&& m) { return _part_list.at(index).model(std::move(m)); };
  void model(size_t index, const Model& m) { return _part_list.at(index).model(m); };

  // operations
  void append_part_info(PartitionInfo&& part_info) { _part_list.push_back(std::move(part_info)); };

  template <class... Args>
  void emplace_part_info (Args&&... args)
  {
    _part_list.emplace_back(std::forward<Args>(args)...);
  }

  void split_msa();
  void compress_patterns(bool store_backmap = false);
  void set_model_empirical_params();

private:
  std::vector<PartitionInfo> _part_list;
  MSA _full_msa;
  NameList _taxon_names;
  NameIdMap _taxon_id_map;
  mutable uintVector _site_part_map;

  uintVector get_site_part_assignment() const;
  void set_taxon_names(const NameList& taxon_names);
};

std::ostream& operator<<(std::ostream& stream, const PartitionedMSA& part_msa);

#endif /* RAXML_PARTITIONEDMSA_HPP_ */
