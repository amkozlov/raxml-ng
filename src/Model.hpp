#ifndef RAXML_MODEL_H_
#define RAXML_MODEL_H_

#include "common.h"

class Model
{
public:
  Model (DataType data_type = DataType::autodetect, const std::string &model_string = "GTR+G+F");
  virtual
  ~Model ();

  void init_from_string(const std::string &model_string);

  /* getters */
  DataType data_type() const { return _data_type; };
  unsigned int num_states() const { return _num_states; };
  unsigned int ratehet_mode() const { return _rate_het; };
  unsigned int num_ratecats() const { return _num_ratecats; };
  double alpha() const { return _alpha; };
  double pinv() const { return _pinv; };

  std::string name() const { return _mix_model ? _mix_model->name : ""; };
  std::string to_string() const;
  int params_to_optimize() const;

private:
  DataType _data_type;
  unsigned int _num_states;

  unsigned int _rate_het;
  unsigned int _num_ratecats;
  double _alpha;
  double _pinv;

  pllmod_mixture_model_t * _mix_model;
  std::unordered_map<int,ParamValue> _param_mode;

  void autodetect_data_type(const std::string &model_name);
  void init_mix_model(const std::string &model_name);
  void init_model_opts(const std::string &model_opts);
};

#endif /* RAXML_MODEL_H_ */
