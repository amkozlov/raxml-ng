#ifndef RAXML_PARTITIONINFO_HPP_
#define RAXML_PARTITIONINFO_HPP_

#include "common.h"
#include "Model.hpp"
#include "MSA.hpp"

class PartitionInfo
{
public:
  PartitionInfo (const std::string &name, DataType data_type,
                 const std::string &model_string, const std::string &range_string = "") :
    _name(name), _range_string(range_string), _model(data_type, model_string) {};
  virtual
  ~PartitionInfo ();

  // getters
  const std::string& name() const { return _name; };
  const Model& model() const { return _model; };
  const std::string& range_string() const { return _range_string; };

private:
  std::string _name;
  std::string _range_string;
  Model _model;
  MSA _msa;
};

#endif /* RAXML_PARTITIONINFO_HPP_ */
