#include "binary_io.hpp"

BasicBinaryStream& operator<<(BasicBinaryStream& stream, const std::string& s)
{
  stream << s.length();
  stream.put(s.c_str(), s.length() * sizeof(char));

  return stream;
}

BasicBinaryStream& operator>>(BasicBinaryStream& stream, std::string& s)
{
  size_t len;
  stream >> len;
  s.resize(len);
  stream.get(&s[0], len * sizeof(char));

  return stream;
}

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

static bool save_modparam(const Model& m, ModelBinaryFmt fmt, unsigned int param)
{
  auto pmode = m.param_mode(param);
  switch (pmode)
  {
    case ParamValue::model:
    case ParamValue::undefined:
      return false;
    case ParamValue::user:
      return (fmt == ModelBinaryFmt::full || fmt == ModelBinaryFmt::def);
    case ParamValue::empirical:
      return (fmt == ModelBinaryFmt::full || fmt == ModelBinaryFmt::params);
    case ParamValue::ML:
      return (fmt != ModelBinaryFmt::def);
    default:
      assert(0);
  }

  return true;
}

BasicBinaryStream& operator<<(BasicBinaryStream& stream, std::tuple<const Model&, ModelBinaryFmt> bm)
{
  auto m = std::get<0>(bm);
  auto fmt = std::get<1>(bm);

  stream << fmt;

  if (fmt == ModelBinaryFmt::full || fmt == ModelBinaryFmt::def)
  {
    auto s = m.to_string(false);
    stream << s;
  }

  if (save_modparam(m, fmt, PLLMOD_OPT_PARAM_BRANCH_LEN_SCALER))
    stream << m.brlen_scaler();

  if (save_modparam(m, fmt, PLLMOD_OPT_PARAM_PINV))
      stream << m.pinv();

  if (m.num_ratecats() > 1)
  {
    if (m.ratehet_mode() == PLLMOD_UTIL_MIXTYPE_GAMMA)
    {
      if (save_modparam(m, fmt, PLLMOD_OPT_PARAM_ALPHA))
        stream << m.alpha();
    }
    else
    {
      if (save_modparam(m, fmt, PLLMOD_OPT_PARAM_RATE_WEIGHTS))
        stream << m.ratecat_weights();
      if (save_modparam(m, fmt, PLLMOD_OPT_PARAM_FREE_RATES))
        stream << m.ratecat_rates();
    }
  }

  for (size_t i = 0; i < m.num_submodels(); ++i)
  {
    if (save_modparam(m, fmt, PLLMOD_OPT_PARAM_FREQUENCIES))
      stream << m.submodel(i).base_freqs();
    if (save_modparam(m, fmt, PLLMOD_OPT_PARAM_SUBST_RATES))
      stream << m.submodel(i).subst_rates();
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

BasicBinaryStream& operator>>(BasicBinaryStream& stream, std::tuple<Model&, ModelBinaryFmt> bm)
{
  auto& m = std::get<0>(bm);
  auto fmt = std::get<1>(bm);

  if (stream.get<ModelBinaryFmt>() != fmt)
    throw std::runtime_error("Invalid binary model format!");

  if (fmt == ModelBinaryFmt::full || fmt == ModelBinaryFmt::def)
  {
    std::string s = stream.get<std::string>();
//    printf("\n%s\n", s.c_str());
    m = Model(DataType::autodetect, s);
  }

  if (save_modparam(m, fmt, PLLMOD_OPT_PARAM_BRANCH_LEN_SCALER))
    m.brlen_scaler(stream.get<double>());

  if (save_modparam(m, fmt, PLLMOD_OPT_PARAM_PINV))
    m.pinv(stream.get<double>());

  if (m.num_ratecats() > 1)
  {
    if (m.ratehet_mode() == PLLMOD_UTIL_MIXTYPE_GAMMA)
    {
      if (save_modparam(m, fmt, PLLMOD_OPT_PARAM_ALPHA))
        m.alpha(stream.get<double>());
    }
    else
    {
      if (save_modparam(m, fmt, PLLMOD_OPT_PARAM_RATE_WEIGHTS))
        m.ratecat_weights(stream.get<doubleVector>());
      if (save_modparam(m, fmt, PLLMOD_OPT_PARAM_FREE_RATES))
        m.ratecat_rates(stream.get<doubleVector>());
    }
  }

  for (size_t i = 0; i < m.num_submodels(); ++i)
  {
    if (save_modparam(m, fmt, PLLMOD_OPT_PARAM_FREQUENCIES))
      m.base_freqs(i, stream.get<doubleVector>());
    if (save_modparam(m, fmt, PLLMOD_OPT_PARAM_SUBST_RATES))
      m.subst_rates(i, stream.get<doubleVector>());
  }

  return stream;
}

BasicBinaryStream& operator<<(BasicBinaryStream& stream, const TreeCollection& c)
{
  stream << c.size();
  for (const auto tree: c)
    stream << tree.first << tree.second;
  return stream;
}

BasicBinaryStream& operator>>(BasicBinaryStream& stream, TreeCollection& c)
{
  auto size = stream.get<size_t>();
  for (size_t i = 0; i < size; ++i)
  {
    auto score = stream.get<double>();
    c.push_back(score, stream.get<TreeTopology>());
  }
  return stream;
}

BasicBinaryStream& operator<<(BasicBinaryStream& stream, const MSA& m)
{
  stream << m.size();
  stream << m.length();

  stream << m.weights();

  for (size_t i = 0; i < m.size(); ++i)
  {
    auto seq = m.at(i);
    assert(seq.length() == m.length());
    stream.write(seq.c_str(), m.length());
  }

  return stream;
}


BasicBinaryStream& operator>>(BasicBinaryStream& stream, MSA& m)
{
  auto taxa_count = stream.get<size_t>();
  auto pat_count = stream.get<size_t>();

  m = MSA(pat_count);

  m.weights(stream.get<WeightVector>());

  std::string seq(pat_count, 0);
  for (size_t i = 0; i < taxa_count; ++i)
  {
    stream.read(&seq[0], pat_count);
    m.append(seq);
  }

  return stream;
}


BasicBinaryStream& operator<<(BasicBinaryStream& stream, const PartitionStats& ps)
{
  stream << ps.site_count;
  stream << ps.pattern_count;
  stream << ps.inv_count;
  stream << ps.gap_prop;
  stream << ps.emp_base_freqs;
  stream << ps.emp_subst_rates;

  return stream;
}

BasicBinaryStream& operator>>(BasicBinaryStream& stream, PartitionStats& ps)
{
  stream >> ps.site_count;
  stream >> ps.pattern_count;
  stream >> ps.inv_count;
  stream >> ps.gap_prop;
  stream >> ps.emp_base_freqs;
  stream >> ps.emp_subst_rates;

  return stream;
}
