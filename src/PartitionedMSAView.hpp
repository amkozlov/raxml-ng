#ifndef RAXML_PARTITIONEDMSAVIEW_HPP_
#define RAXML_PARTITIONEDMSAVIEW_HPP_

#include "PartitionedMSA.hpp"

class PartitionedMSAView
{
public:
  PartitionedMSAView (std::shared_ptr<const PartitionedMSA> parted_msa);
  PartitionedMSAView (const PartitionedMSA& parted_msa);
  virtual
  ~PartitionedMSAView ();

  bool identity() const;
  bool unweighted(size_t part_id) const;
  size_t taxon_count() const;
  size_t part_count() const;
  size_t excluded_site_count() const;
  size_t total_length() const;
  size_t total_sites() const;

  std::string taxon_name(size_t taxon_id) const;
  std::string orig_taxon_name(size_t taxon_id) const;
  const NameMap& taxon_name_map() const;

  const Model& part_model(size_t part_id) const;
  std::string part_name(size_t part_id) const;
  size_t part_length(size_t part_id) const;
  size_t part_sites(size_t part_id) const;
  std::string part_sequence(size_t taxon_id, size_t part_id, bool uncompress = false) const;

  void map_taxon_name(const std::string& orig_name, const std::string& new_name);
  void exclude_taxon(size_t taxon_id);

  void exclude_site(size_t part_id, size_t site_id);
  void exclude_sites(size_t part_id, IDVector site_ids);
  const IDSet& exclude_sites(size_t part_id) const;

  void site_weights(const WeightVectorList& site_weights);
  void site_weights(size_t part_id, const WeightVector& site_weights);

private:
  const PartitionedMSA * _parted_msa;
  std::shared_ptr<const PartitionedMSA> _parted_msa_sptr;
  NameMap _taxon_name_map;
  IDSet _excluded_taxa;
  std::vector<IDSet> _excluded_sites;
  WeightVectorList _site_weights;

  mutable IDVector _orig_taxon_ids;

  size_t orig_taxon_id(size_t taxon_id) const;
  IDQueue get_exclude_queue(size_t part_id) const;
};

#endif /* RAXML_PARTITIONEDMSAVIEW_HPP_ */
