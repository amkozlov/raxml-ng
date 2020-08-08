#include "ICScoreCalculator.hpp"

ICScoreCalculator::ICScoreCalculator(size_t free_params, size_t sample_size):
    _free_params(free_params), _sample_size(sample_size)
{
}

ICScoreCalculator::~ICScoreCalculator()
{
}

double ICScoreCalculator::aic(double loglh) const
{
  return 2.0 * _free_params - 2.0 * loglh;
}

double ICScoreCalculator::aicc(double loglh) const
{
  return aic(loglh) + 2.0 * _free_params * (_free_params + 1) /
                     std::max((double)_sample_size - _free_params - 1, 1.);
}

double ICScoreCalculator::bic(double loglh) const
{
  return log(_sample_size) * _free_params - 2.0 * loglh;
}

std::map<InformationCriterion,double> ICScoreCalculator::all(double loglh) const
{
  std::map<InformationCriterion,double> m;

  m[InformationCriterion::aic] = aic(loglh);
  m[InformationCriterion::aicc] = aicc(loglh);
  m[InformationCriterion::bic] = bic(loglh);

  return m;
}
