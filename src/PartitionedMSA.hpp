#ifndef RAXML_PARTITIONEDMSA_HPP_
#define RAXML_PARTITIONEDMSA_HPP_

#include "PartitionInfo.hpp"

class PartitionedMSA
{
public:
  PartitionedMSA () {};
  virtual
  ~PartitionedMSA ();

  // copy/move constructors and assignments
  PartitionedMSA (PartitionedMSA&& other) = default;
  PartitionedMSA& operator=(PartitionedMSA&& other);

  // getters
  const MSA& full_msa() const { return _full_msa; };
  size_t part_count() const { return _part_list.size(); };
  const PartitionInfo& part_info(size_t index) const { return _part_list.at(index); };
  const Model& model(size_t index) const { return _part_list.at(index).model(); };
  const std::vector<PartitionInfo>& part_list() const { return _part_list; };

  // setters
  void full_msa(MSA&& msa) { _full_msa = std::move(msa); };
  void part_msa(size_t index, MSA&& msa) { _part_list.at(index).msa(std::move(msa)); };
  void part_msa(size_t index, const pll_msa_t * pll_msa)
  {
    _part_list.at(index).msa(MSA(pll_msa));
  };
  void model(size_t index, Model&& m) { return _part_list.at(index).model(std::move(m)); };

  // operations
  void append_part_info(PartitionInfo&& part_info) { _part_list.push_back(std::move(part_info)); };

  template <class... Args>
  void emplace_part_info (Args&&... args)
  {
    _part_list.emplace_back(std::forward<Args>(args)...);
  }

  void split_msa();
  void compress_patterns();
  void set_model_empirical_params();

private:
  std::vector<PartitionInfo> _part_list;
  MSA _full_msa;

  std::vector<unsigned int> get_site_part_assignment();
};

void print_partition_info(const PartitionedMSA& part_msa);

#endif /* RAXML_PARTITIONEDMSA_HPP_ */
