#ifndef RAXML_PARTITIONINFO_HPP_
#define RAXML_PARTITIONINFO_HPP_

#include "common.h"
#include "Model.hpp"
#include "MSA.hpp"

class Options;

struct PartitionStats
{
  size_t site_count;
  size_t pattern_count;
  double inv_prop;
  double gap_prop;
  IDVector gap_seqs;
  doubleVector emp_base_freqs;
  doubleVector emp_subst_rates;

  bool empty() const { return site_count == 0; }
  size_t gap_seq_count() const { return gap_seqs.size(); }
  size_t inv_count() const { return (size_t) site_count * inv_prop; }

  PartitionStats() : site_count(0), pattern_count(0), inv_prop(0.), gap_prop(0.), gap_seqs(),
      emp_base_freqs(), emp_subst_rates() {}

  friend void swap(PartitionStats& first, PartitionStats& second)
  {
    std::swap(first.site_count, second.site_count);
    std::swap(first.pattern_count, second.pattern_count);
    std::swap(first.inv_prop, second.inv_prop);
    std::swap(first.gap_prop, second.gap_prop);
    std::swap(first.gap_seqs, second.gap_seqs);
    std::swap(first.emp_base_freqs, second.emp_base_freqs);
    std::swap(first.emp_subst_rates, second.emp_subst_rates);
  }

  PartitionStats(const PartitionStats& other) : site_count(other.site_count),
      pattern_count(other.pattern_count),
      inv_prop(other.inv_prop), gap_prop(other.gap_prop), gap_seqs(other.gap_seqs),
      emp_base_freqs(other.emp_base_freqs), emp_subst_rates(other.emp_subst_rates) {}

  PartitionStats& operator=(PartitionStats other)
  {
    swap(*this, other);
    return *this;
  }
};

class PartitionInfo
{
public:
  PartitionInfo () :
    _name(""), _range_string(""), _model(), _msa(), _stats() {};

  PartitionInfo (const std::string &name, DataType data_type,
                 const std::string &model_string, const std::string &range_string = "") :
    _name(name), _range_string(range_string), _model(data_type, model_string), _msa(),
    _stats() {};

  PartitionInfo (const std::string &name, const PartitionStats &stats,
                 const Model &model, const std::string &range_string = "") :
    _name(name), _range_string(range_string), _model(model), _msa(),
    _stats(stats) {};

  virtual ~PartitionInfo ();

  PartitionInfo (PartitionInfo&& other) : _name(std::move(other._name)),
      _range_string(std::move(other._range_string)),  _model(std::move(other._model)),
      _msa(std::move(other._msa)), _stats(std::move(other._stats))
  {
    other._stats = PartitionStats();
  }

  // getters
  const std::string& name() const { return _name; };
  const Model& model() const { return _model; };
  Model& model() { return _model; };
  const std::string& range_string() const { return _range_string; };
  const MSA& msa() const { return _msa; };
  MSA& msa() { return _msa; };
  const PartitionStats& stats() const;
  pllmod_msa_stats_t * compute_stats(unsigned long stats_mask) const;

  size_t length() const;

  /* given in elements (NOT in bytes) */
  size_t taxon_clv_size(bool partial = false) const;

  // setters
  void msa(MSA&& msa) { _msa = std::move(msa); };
  void model(Model&& model) { _model = std::move(model); };
  void model(const Model& model) { _model = model; };
  void name(const std::string& value) { _name = value; };
  void range_string(const std::string& value) { _range_string = value; };

  // operations
  size_t mark_partition_sites(unsigned int part_num, std::vector<unsigned int>& site_part) const;
  void compress_patterns(bool store_backmap = false);
  void set_model_empirical_params();

private:
  std::string _name;
  std::string _range_string;
  Model _model;
  MSA _msa;
  mutable PartitionStats _stats;
};


class InvalidPartitionRangeException : public RaxmlException
{
public:
  InvalidPartitionRangeException(const PartitionInfo& pinfo) :
    RaxmlException("")
  {
    _message = format_message("Invalid range in partition %s: %s",
                              pinfo.name().c_str(), pinfo.range_string().c_str());
  }
};

class MultiplePartitionForSiteException : public RaxmlException
{
public:
  MultiplePartitionForSiteException(const PartitionInfo& pinfo1, size_t site) :
    RaxmlException(""), _site(site), part1_name(pinfo1.name())
  { }

  size_t site() const { return _site; };

  void pinfo2(const PartitionInfo& pinfo2) { part2_name = pinfo2.name(); }

  virtual void update_message() const
  {
    _message = format_message("Alignment site %u assigned to multiple partitions: "
        "\"%s\" and \"%s\"!", _site, part1_name.c_str(), part2_name.c_str());
  };

private:
  size_t _site;
  std::string part1_name;
  std::string part2_name;
};

class MissingPartitionForSiteException : public RaxmlException
{
public:
  MissingPartitionForSiteException() : RaxmlException("")
  { }

  size_t count() const { return _unassigned_sites.size(); }
  const std::vector<size_t>& sites() const { return _unassigned_sites; }

  void add_unassigned_site(size_t site) { _unassigned_sites.push_back(site); }

  virtual void update_message() const
  {
    std::stringstream ss;
    ss << "Found " << _unassigned_sites.size() <<
        " alignment site(s) which are not assigned to any partition:" << std::endl;
    for (auto s: _unassigned_sites)
      ss << s << " ";

    ss << std::endl << "Please fix your data!";
    _message = ss.str();
  };

private:
  std::vector<size_t> _unassigned_sites;
};

void assign(Model& model, const PartitionStats& stats);


#endif /* RAXML_PARTITIONINFO_HPP_ */
