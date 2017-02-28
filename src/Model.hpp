#ifndef RAXML_MODEL_H_
#define RAXML_MODEL_H_

#include "common.h"

class SubstitutionModel
{
public:
  SubstitutionModel(const pllmod_subst_model_t& sm) :
    _states(sm.states), _name(sm.name)
  {
    if (sm.freqs)
      _base_freqs.assign(sm.freqs, sm.freqs + sm.states);
    if (sm.rates)
      _subst_rates.assign(sm.rates, sm.rates + sm.states*(sm.states-1)/2);
    if (sm.rate_sym)
      _rate_sym.assign(sm.rate_sym, sm.rate_sym + sm.states*(sm.states-1)/2);
    if (sm.freq_sym)
      _freq_sym.assign(sm.freq_sym, sm.freq_sym + sm.states);
  };

  // getters
  unsigned int states() const;
  std::string name() const;
  const doubleVector& base_freqs() const { return _base_freqs; };
  const doubleVector& subst_rates() const { return _subst_rates; };
  const intVector& rate_sym() const { return _rate_sym; };
  const intVector& freq_sym() const { return _freq_sym; };

  // setters
  void base_freqs(const doubleVector& v)
  {
//    std::cout << "expected: " << _states << ", got: " << v.size() << std::endl;
    if (v.size() != _states)
      throw std::invalid_argument("Invalid size of base_freqs vector!");

    _base_freqs = v;
  };

  void subst_rates(const doubleVector& v)
  {
    if (v.size() != _states * (_states - 1) / 2)
      throw std::invalid_argument("Invalid size of subst_rates vector!");

    _subst_rates = v;
  };

private:
  unsigned int _states;
  std::string _name;
  doubleVector _base_freqs;
  doubleVector _subst_rates;
  intVector _rate_sym;
  intVector _freq_sym;
};

class Model
{
public:
  Model (DataType data_type = DataType::autodetect, const std::string &model_string = "GTR");
  Model (const std::string &model_string) : Model(DataType::autodetect, model_string) {};

  Model(const Model& other) = default;

  /* getters */
  DataType data_type() const { return _data_type; };
  unsigned int num_states() const { return _num_states; };
  std::string name() const { return _name; };

  const unsigned int* charmap() const;
  const SubstitutionModel submodel(size_t i) const { return _submodels.at(i); };

  unsigned int ratehet_mode() const { return _rate_het; };
  unsigned int num_ratecats() const { return _num_ratecats; };
  unsigned int num_submodels() const { return _num_submodels; };
  const doubleVector& ratecat_rates() const { return _ratecat_rates; };
  const doubleVector& ratecat_weights() const { return _ratecat_weights; };
  const std::vector<unsigned int>& ratecat_submodels() const { return _ratecat_submodels; };

  double alpha() const { return _alpha; };
  double pinv() const { return _pinv; };
  double brlen_scaler() const { return _brlen_scaler; };
  const doubleVector& base_freqs(unsigned int i) const { return _submodels.at(i).base_freqs(); };
  const doubleVector& subst_rates(unsigned int i) const { return _submodels.at(i).subst_rates(); };

  std::string to_string() const;
  int params_to_optimize() const;
  ParamValue param_mode(int param) const { return _param_mode.at(param); };

  /* setters */
  void alpha(double value) { _alpha = value; };
  void pinv(double value) { _pinv = value; };
  void brlen_scaler(double value) { _brlen_scaler = value; };
  void base_freqs(size_t i, const doubleVector& value) { _submodels.at(i).base_freqs(value); };
  void subst_rates(size_t i, const doubleVector& value) { _submodels.at(i).subst_rates(value); };
  void base_freqs(const doubleVector& value) { for (SubstitutionModel& s: _submodels) s.base_freqs(value); };
  void subst_rates(const doubleVector& value) { for (SubstitutionModel& s: _submodels) s.subst_rates(value); };
  void ratecat_rates(doubleVector const& value) { _ratecat_rates = value; };
  void ratecat_weights(doubleVector const& value) { _ratecat_weights = value; };

  /* initialization */
  void init_from_string(const std::string& model_string);

private:
  std::string _name;
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
  double _brlen_scaler;

  std::vector<SubstitutionModel> _submodels;

  std::unordered_map<int,ParamValue> _param_mode;

  void autodetect_data_type(const std::string& model_name);
  pllmod_mixture_model_t * init_mix_model(const std::string& model_name);
  void init_model_opts(const std::string& model_opts, const pllmod_mixture_model_t& mix_model);
};

void assign(Model& model, const pllmod_msa_stats_t * stats);
void assign(Model& model, const pll_partition_t * partition);
void assign(pll_partition_t * partition, const Model& model);

LogStream& operator<<(LogStream& stream, const Model& m);

#endif /* RAXML_MODEL_H_ */
