#ifndef RAXML_PARTITIONEDMSA_HPP_
#define RAXML_PARTITIONEDMSA_HPP_

#include "PartitionInfo.hpp"

class AutoPartitioner;

class PartitionedMSA
{
public:
  PartitionedMSA();
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
  void part_msa(size_t index, const corax_msa_t * pll_msa)
  {
    _part_list.at(index).msa(MSA(pll_msa));
  };
  void model(size_t index, Model&& m) { _part_list.at(index).model(std::move(m)); };
  void model(size_t index, const Model& m) { _part_list.at(index).model(m); };

  double difficulty_score() const { return _difficulty_score; }
  void difficulty_score(double score) { _difficulty_score = score; }

  const uintVector& subst_linkage() const { return _subst_linkage; }
  const uintVector& freqs_linkage() const { return _freqs_linkage; }

  void subst_linkage(const uintVector& v) { _subst_linkage = v; }
  void freqs_linkage(const uintVector& v) { _freqs_linkage = v; }

  // operations
  void init_single_model(DataType data_type, const std::string &model_string);
  void append_part_info(PartitionInfo&& part_info) { _part_list.push_back(std::move(part_info)); };

  template <class... Args>
  void emplace_part_info (Args&&... args)
  {
    _part_list.emplace_back(std::forward<Args>(args)...);
  }

  void split_msa();
  void compress_patterns(bool store_backmap = false);
  void set_model_empirical_params();
  //void predict_difficulty(int n_trees){ _difficuly = (part_count() == 1) ? _part_list.at(0).msa().predictDifficulty(n_trees) : _full_msa.predictDifficulty(n_trees); };

private:
  std::vector<PartitionInfo> _part_list;
  std::shared_ptr<AutoPartitioner> _auto_part;
  MSA _full_msa;
  NameList _taxon_names;
  NameIdMap _taxon_id_map;
  mutable uintVector _site_part_map;
  double _difficulty_score;
  uintVector _subst_linkage;
  uintVector _freqs_linkage;

  uintVector get_site_part_assignment() const;
  void set_taxon_names(const NameList& taxon_names);
};

class AutoPartitioner
{
public:
  void init_from_string(PartitionedMSA& part_msa, DataType data_type, const std::string &model_string);
  void update_partition_ranges(PartitionedMSA& part_msa);

private:
  doubleVector get_column_entropies(const PartitionedMSA& part_msa);
  std::string resolve_auto_range(const doubleVector& col_entropies, size_t part_num, double binw);
};

std::ostream& operator<<(std::ostream& stream, const PartitionedMSA& part_msa);

#endif /* RAXML_PARTITIONEDMSA_HPP_ */
