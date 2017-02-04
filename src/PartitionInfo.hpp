#ifndef RAXML_PARTITIONINFO_HPP_
#define RAXML_PARTITIONINFO_HPP_

#include "common.h"
#include "Model.hpp"
#include "MSA.hpp"

class Options;

class PartitionInfo
{
public:
  PartitionInfo (const std::string &name, DataType data_type,
                 const std::string &model_string, const std::string &range_string = "") :
    _name(name), _range_string(range_string), _model(data_type, model_string), _msa(),
    _stats(nullptr) {};
  virtual
  ~PartitionInfo ();

  PartitionInfo (PartitionInfo&& other)
  {
    _name = std::move(other._name);
    _range_string = std::move(other._range_string);
    _model = std::move(other._model);
    _msa = std::move(_msa);
    _stats = other._stats;
    other._stats = nullptr;
  }

  // getters
  const std::string& name() const { return _name; };
  const Model& model() const { return _model; };
  const std::string& range_string() const { return _range_string; };
  const MSA& msa() const { return _msa; };
  const pllmod_msa_stats_t * stats() const { return _stats ?_stats : compute_stats(); };

  // setters
  void msa(MSA&& msa) { _msa = std::move(msa); };

  // operations
  size_t mark_partition_sites(unsigned int part_num, std::vector<unsigned int>& site_part);
  void compress_patterns();

private:
  std::string _name;
  std::string _range_string;
  Model _model;
  MSA _msa;
  mutable pllmod_msa_stats_t * _stats;

  pllmod_msa_stats_t * compute_stats() const;
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

  virtual const std::string message() const
  {
    return format_message("Alignment site %u assigned to multiple partitions: \"%s\" and \"%s\"!",
                          _site, part1_name.c_str(), part2_name.c_str());
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

  virtual const std::string message() const
  {
    return format_message("Found %u site(s) which are not assigned to any partition.\n"
        "Please fix your data!", _unassigned_sites.size());
  };

private:
  std::vector<size_t> _unassigned_sites;
};

pll_partition_t* create_pll_partition(const Options& opts, const PartitionInfo& pinfo,
                                      pll_utree_t* tree);



#endif /* RAXML_PARTITIONINFO_HPP_ */
