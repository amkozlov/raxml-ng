#ifndef RAXML_ERRORMODEL_HPP_
#define RAXML_ERRORMODEL_HPP_

#include "common.h"

class ErrorModel
{
public:
  ErrorModel(unsigned int states) : _states(states) {};
  virtual ~ErrorModel() {};

  virtual intVector param_ids() const = 0;
  virtual NameVector param_names() const = 0;
  virtual doubleVector params() const = 0;
  virtual void params(const doubleVector& pv) = 0;

  void state_probs(unsigned int state, doubleVector::iterator &clvp) const
  { compute_state_probs(state, clvp); }

protected:
  unsigned int _states;

  virtual void compute_state_probs(unsigned int state, doubleVector::iterator &clvp) const = 0;
};

class UniformErrorModel: public ErrorModel
{
public:
  UniformErrorModel(unsigned int states) :
    ErrorModel(states), _seq_error_rate(RAXML_SEQ_ERROR_MIN) {};
  UniformErrorModel(unsigned int states, double error_rate) :
    ErrorModel(states), _seq_error_rate(error_rate) {};

  intVector param_ids() const override;
  NameVector param_names() const override;
  doubleVector params() const override;
  void params(const doubleVector& pv) override;

protected:
  double _seq_error_rate;

private:
  void compute_state_probs(unsigned int state, doubleVector::iterator &clvp) const override;
};

class GenotypeErrorModel: public ErrorModel
{
public:
  GenotypeErrorModel() :
    ErrorModel(10), _seq_error_rate(RAXML_SEQ_ERROR_MIN), _dropout_rate(RAXML_ADO_RATE_MIN),
    _freqs() {}

  void freqs(const doubleVector& fv) { _freqs = fv; };
  doubleVector freqs() const { return _freqs; };

  intVector param_ids() const override;
  doubleVector params() const override;
  NameVector param_names() const override;
  void params(const doubleVector& pv) override;

protected:
  double _seq_error_rate;
  double _dropout_rate;
  doubleVector _freqs;

private:
  virtual void compute_state_probs(unsigned int state, doubleVector::iterator &clvp) const override;
};

LogStream& operator<<(LogStream& stream, const ErrorModel& m);


#endif /* RAXML_ERRORMODEL_HPP_ */
