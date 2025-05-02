#ifndef RAXML_ADAPTIVE_NORMALDISTRIBUTION_HPP_
#define RAXML_ADAPTIVE_NORMALDISTRIBUTION_HPP_

#include <cmath>
#include <vector>
#include <corax/corax.h>

class StatisticalDistribution {
 public:
  StatisticalDistribution();
  virtual ~StatisticalDistribution();

  // Distribution functions
  virtual double pdf(const double& x) const = 0;
  virtual double cdf(const double& x) const = 0;

  // Inverse cumulative distribution functions (aka the quantile function)
  virtual double inv_cdf(const double& quantile) const = 0;
  
  // Descriptive stats
  virtual double mean() const = 0;
  virtual double var() const = 0;
  virtual double stdev() const = 0;

  // Obtain a sequence of random draws from this distribution
  virtual void random_draws(const std::vector<double>& uniform_draws,
                            std::vector<double>& dist_draws) = 0;
};



class StandardNormalDistribution : public StatisticalDistribution {
 public:
  StandardNormalDistribution();
  virtual ~StandardNormalDistribution();

  // Distribution functions
  virtual double pdf(const double& x) const;
  virtual double cdf(const double& x) const;

  // Inverse cumulative distribution function (aka the probit function)
  virtual double inv_cdf(const double& quantile) const;
  
  // Descriptive stats
  virtual double mean() const;   // equal to 0
  virtual double var() const;    // equal to 1 
  virtual double stdev() const;  // equal to 1

  // Obtain a sequence of random draws from the standard normal distribution
  virtual void random_draws(const std::vector<double>& uniform_draws,
                            std::vector<double>& dist_draws);
};

#endif /* RAXML_ADAPTIVE_NORMALDISTRIBUTION_HPP_ */