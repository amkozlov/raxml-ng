#include "binary_io.hpp"

BasicBinaryStream& operator<<(BasicBinaryStream& stream, const SubstitutionModel& sm)
{
  stream << sm.base_freqs();
  stream << sm.subst_rates();

  return stream;
}

BasicBinaryStream& operator<<(BasicBinaryStream& stream, const Model& m)
{
//  if (m.param_mode(PLLMOD_OPT_PARAM_BRANCH_LEN_SCALER) != ParamValue::undefined)
  stream << m.brlen_scaler();

//  if (m.param_mode(PLLMOD_OPT_PARAM_PINV) != ParamValue::undefined)
    stream << m.pinv();

  stream << m.num_ratecats();

  if (m.num_ratecats() > 1)
  {
    stream << m.ratehet_mode();
    if (m.ratehet_mode() == PLLMOD_UTIL_MIXTYPE_GAMMA)
      stream << m.alpha();

    stream << m.ratecat_weights();
    stream << m.ratecat_rates();
  }

  /* store subst model parameters only if they were estimated */
  if (m.param_mode(PLLMOD_OPT_PARAM_FREQUENCIES) == ParamValue::ML ||
      m.param_mode(PLLMOD_OPT_PARAM_SUBST_RATES) == ParamValue::ML)
  {
    stream << m.num_submodels();
    for (size_t i = 0; i < m.num_submodels(); ++i)
    {
      stream << m.submodel(i);
    }
  }

  return stream;
}

BasicBinaryStream& operator>>(BasicBinaryStream& stream, Model& m)
{
//  if (m.param_mode(PLLMOD_OPT_PARAM_BRANCH_LEN_SCALER) != ParamValue::undefined)
  m.brlen_scaler(stream.get<double>());

//  if (m.param_mode(PLLMOD_OPT_PARAM_PINV) != ParamValue::undefined)

  m.pinv(stream.get<double>());

  auto num_ratecats = stream.get<unsigned int>();

  assert(num_ratecats == m.num_ratecats());

  if (m.num_ratecats() > 1)
  {
    auto ratehet_mode = stream.get<unsigned int>();
    assert(ratehet_mode == m.ratehet_mode());

    if (m.ratehet_mode() == PLLMOD_UTIL_MIXTYPE_GAMMA)
      m.alpha(stream.get<double>());

    m.ratecat_weights(stream.get<doubleVector>());
    m.ratecat_rates(stream.get<doubleVector>());
  }

  if (m.param_mode(PLLMOD_OPT_PARAM_FREQUENCIES) == ParamValue::ML ||
      m.param_mode(PLLMOD_OPT_PARAM_SUBST_RATES) == ParamValue::ML)
  {
    auto num_submodels = stream.get<unsigned int>();
    assert(num_submodels == m.num_submodels());
    for (size_t i = 0; i < m.num_submodels(); ++i)
    {
      m.base_freqs(i, stream.get<doubleVector>());
      m.subst_rates(i, stream.get<doubleVector>());
    }
  }

  return stream;
}


