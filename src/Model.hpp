#ifndef RAXML_MODEL_H_
#define RAXML_MODEL_H_

#include <algorithm>

#include "common.h"

typedef std::unordered_map<pll_state_t,std::string> StateNameMap;

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
  const doubleVector& base_freqs() const { return _base_freqs; }
  const doubleVector& subst_rates() const { return _subst_rates; }
  const intVector& rate_sym() const { return _rate_sym; }
  const intVector& freq_sym() const { return _freq_sym; }

  unsigned int num_rates() const  { return _states*(_states-1)/2; }
  unsigned int num_uniq_rates() const
  {
    if (_rate_sym.empty())
      return num_rates();
    else
      return *std::max_element(_rate_sym.cbegin(), _rate_sym.cend()) + 1;
  }

  doubleVector uniq_subst_rates() const
  {
    if (!_rate_sym.empty())
    {
      doubleVector uniq_rates(num_uniq_rates());
      for (size_t i = 0; i < _subst_rates.size(); ++i)
        uniq_rates[_rate_sym[i]] = _subst_rates[i];
      return uniq_rates;
    }
    else
      return _subst_rates;
  };


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
    if (v.size() != num_rates())
      throw std::invalid_argument("Invalid size of subst_rates vector!");

    _subst_rates = v;
  };

  void uniq_subst_rates(const doubleVector& v)
  {
    if (!_rate_sym.empty())
    {
      if (v.size() != num_uniq_rates())
        throw std::invalid_argument("Invalid size of subst_rates vector!");

      _subst_rates.resize(num_rates());
      for (size_t i = 0; i < _subst_rates.size(); ++i)
        _subst_rates[i] = v[_rate_sym[i]];
    }
    else
      subst_rates(v);
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
  typedef std::unordered_map<int,ParamValue> ParamModeMap;

  Model (DataType data_type = DataType::autodetect, const std::string &model_string = "GTR");
  Model (const std::string &model_string) : Model(DataType::autodetect, model_string) {};

  Model(const Model&) = default;

  /* getters */
  DataType data_type() const { return _data_type; };
  std::string data_type_name() const;
  unsigned int num_states() const { return _num_states; };
  std::string name() const { return _name; };

  const pll_state_t* charmap() const;
  const NameList& state_names() const;            // non-ambiguous states only, eg A C G T
  const StateNameMap& full_state_namemap() const; // + ambiguous states, eg A C G T M R W S Y K -

  const SubstitutionModel submodel(size_t i) const { return _submodels.at(i); };

  unsigned int ratehet_mode() const { return _rate_het; };
  unsigned int num_ratecats() const { return _num_ratecats; };
  unsigned int num_submodels() const { return _num_submodels; };
  const doubleVector& ratecat_rates() const { return _ratecat_rates; };
  const doubleVector& ratecat_weights() const { return _ratecat_weights; };
  const std::vector<unsigned int>& ratecat_submodels() const { return _ratecat_submodels; };
  int gamma_mode() const { return _gamma_mode; };

  double alpha() const { return _alpha; };
  double pinv() const { return _pinv; };
  double brlen_scaler() const { return _brlen_scaler; };
  const doubleVector& base_freqs(unsigned int i) const { return _submodels.at(i).base_freqs(); };
  const doubleVector& subst_rates(unsigned int i) const { return _submodels.at(i).subst_rates(); };

  std::string to_string(bool print_params = false, unsigned int precision = 0) const;
  int params_to_optimize() const;
  const ParamModeMap& param_mode() const { return _param_mode; }
  ParamValue param_mode(int param) const { return _param_mode.at(param); };
  bool param_estimated(int param) const;

  AscBiasCorrection ascbias_type() const { return _ascbias_type; }
  const WeightVector& ascbias_weights() const { return _ascbias_weights; }

  /* per alignment site, given in elements (NOT in bytes) */
  size_t clv_entry_size() const { return _num_states * _num_ratecats; }

  unsigned int  num_free_params() const;

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

  void param_mode(int param, ParamValue mode) { _param_mode[param] = mode; };
  void set_param_mode_default(int param, ParamValue mode)
  {
    if (param_mode(param) == ParamValue::undefined)
      _param_mode[param] = mode;
  };

  /* initialization */
  void init_from_string(const std::string& model_string);

private:
  std::string _name;
  DataType _data_type;
  unsigned int _num_states;

  std::string _custom_states;
  std::string _custom_gaps;
  bool _custom_case_sensitive;
  std::shared_ptr<pll_state_t> _custom_charmap;
  mutable NameList _state_names;
  mutable StateNameMap _full_state_namemap;

  unsigned int _rate_het;
  unsigned int _num_ratecats;
  unsigned int _num_submodels;
  doubleVector _ratecat_rates;
  doubleVector _ratecat_weights;
  std::vector<unsigned int> _ratecat_submodels;
  int _gamma_mode;

  double _alpha;
  double _pinv;
  double _brlen_scaler;

  AscBiasCorrection _ascbias_type;
  WeightVector _ascbias_weights;

  std::vector<SubstitutionModel> _submodels;

  ParamModeMap _param_mode;

  void autodetect_data_type(const std::string& model_name);
  pllmod_mixture_model_t * init_mix_model(const std::string& model_name);
  void init_model_opts(const std::string& model_opts, const pllmod_mixture_model_t& mix_model);
  void init_state_names() const;
  void set_user_srates(doubleVector& srates, bool normalize = true);
  void set_user_freqs(doubleVector& freqs);
};

typedef std::unordered_map<size_t, Model> ModelMap;
typedef std::unordered_map<size_t, Model&> ModelRefMap;
typedef std::unordered_map<size_t, const Model&> ModelCRefMap;

void assign(Model& model, const pll_partition_t * partition);
void assign(pll_partition_t * partition, const Model& model);

LogStream& operator<<(LogStream& stream, const Model& m);

#endif /* RAXML_MODEL_H_ */
