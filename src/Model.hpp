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

  const unsigned int * charmap() const;
  const pllmod_subst_model_t * submodel(size_t i) const
  { return (_mix_model && i < _mix_model->ncomp) ? _mix_model->models[i] : nullptr; };

  unsigned int ratehet_mode() const { return _rate_het; };
  unsigned int num_ratecats() const { return _num_ratecats; };
  unsigned int num_submodels() const { return _mix_model ? _mix_model->ncomp : 1; };
  const std::vector<double>& ratecat_rates() const { return _ratecat_rates; };
  const std::vector<double>& ratecat_weights() const { return _ratecat_weights; };
  const std::vector<unsigned int>& ratecat_submodels() const { return _ratecat_submodels; };

  double alpha() const { return _alpha; };
  double pinv() const { return _pinv; };
  const std::vector<double>& base_freqs() const { return _base_freqs; };
  const std::vector<double>& subst_rates() const { return _subst_rates; };

  std::string name() const { return _mix_model ? _mix_model->name : ""; };
  std::string to_string() const;
  int params_to_optimize() const;
  ParamValue param_mode(int param) const { return _param_mode.at(param); };

private:
  DataType _data_type;
  unsigned int _num_states;

  unsigned int _rate_het;
  unsigned int _num_ratecats;
  std::vector<double> _ratecat_rates;
  std::vector<double> _ratecat_weights;
  std::vector<unsigned int> _ratecat_submodels;

  double _alpha;
  double _pinv;
  std::vector<double> _base_freqs;
  std::vector<double> _subst_rates;

  pllmod_mixture_model_t * _mix_model;
  std::unordered_map<int,ParamValue> _param_mode;

  void autodetect_data_type(const std::string &model_name);
  void init_mix_model(const std::string &model_name);
  void init_model_opts(const std::string &model_opts);
};

#endif /* RAXML_MODEL_H_ */
