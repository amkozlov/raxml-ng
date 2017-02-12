#ifndef RAXML_MODEL_H_
#define RAXML_MODEL_H_

#include "common.h"

class Model
{
public:
  typedef std::vector<double> doubleVector;

  Model (DataType data_type = DataType::autodetect, const std::string &model_string = "GTR+G+F");
  virtual
  ~Model ();

  /* getters */
  DataType data_type() const { return _data_type; };
  unsigned int num_states() const { return _num_states; };
  std::string name() const { return _mix_model ? _mix_model->name : ""; };

  const unsigned int* charmap() const;
  const pllmod_subst_model_t* submodel(size_t i) const
  { return (_mix_model && i < _mix_model->ncomp) ? _mix_model->models[i] : nullptr; };

  unsigned int ratehet_mode() const { return _rate_het; };
  unsigned int num_ratecats() const { return _num_ratecats; };
  unsigned int num_submodels() const { return _num_submodels; };
  const doubleVector& ratecat_rates() const { return _ratecat_rates; };
  const doubleVector& ratecat_weights() const { return _ratecat_weights; };
  const std::vector<unsigned int>& ratecat_submodels() const { return _ratecat_submodels; };

  double alpha() const { return _alpha; };
  double pinv() const { return _pinv; };
  const doubleVector& base_freqs(unsigned int i) const { return _base_freqs.at(i); };
  const doubleVector& subst_rates(unsigned int i) const { return _subst_rates.at(i); };

  std::string to_string() const;
  int params_to_optimize() const;
  ParamValue param_mode(int param) const { return _param_mode.at(param); };

  /* setters */
  void alpha(double value) { _alpha = value; };
  void pinv(double value) { _pinv = value; };
  void base_freqs(unsigned int i, const doubleVector& value) { _base_freqs.at(i) = value; };
  void subst_rates(unsigned int i, const doubleVector& value) { _subst_rates.at(i) = value; };
  void base_freqs(const doubleVector& value) { for (doubleVector& v: _base_freqs) v = value; };
  void subst_rates(const doubleVector& value) { for (doubleVector& v: _subst_rates) v = value; };
  void ratecat_rates(doubleVector const& value) { _ratecat_rates = value; };
  void ratecat_weights(doubleVector const& value) { _ratecat_weights = value; };

  /* initialization */
  void init_from_string(const std::string& model_string);

private:
  DataType _data_type;
  unsigned int _num_states;

  unsigned int _rate_het;
  unsigned int _num_ratecats;
  unsigned int _num_submodels;
  doubleVector _ratecat_rates;
  doubleVector _ratecat_weights;
  std::vector<unsigned int> _ratecat_submodels;

  double _alpha;
  double _pinv;
  std::vector<doubleVector> _base_freqs;
  std::vector<doubleVector> _subst_rates;

  pllmod_mixture_model_t* _mix_model;
  std::unordered_map<int,ParamValue> _param_mode;

  void autodetect_data_type(const std::string& model_name);
  void init_mix_model(const std::string& model_name);
  void init_model_opts(const std::string& model_opts);
};

void print_model_info(const Model& m);

void assign(Model& model, const pllmod_msa_stats_t * stats);
void assign(Model& model, const pll_partition_t * partition);
void assign(pll_partition_t * partition, const Model& model);

#endif /* RAXML_MODEL_H_ */
