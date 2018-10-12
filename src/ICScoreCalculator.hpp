#ifndef RAXML_ICCALCULATOR_HPP_
#define RAXML_ICCALCULATOR_HPP_

#include "common.h"

class ICScoreCalculator
{
public:
  ICScoreCalculator(size_t free_params, size_t sample_size);
  virtual ~ICScoreCalculator();

  double aic(double loglh) const;
  double aicc(double loglh) const;
  double bic(double loglh) const;

  std::map<InformationCriterion,double> all(double loglh) const;

private:
  size_t _free_params;
  size_t _sample_size;
};

#endif /* RAXML_ICCALCULATOR_HPP_ */
