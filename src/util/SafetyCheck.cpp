#include "../common.h"
#include "SafetyCheck.hpp"

using namespace std;

SafetyCheck::Flags SafetyCheck::from_string(const string& s)
{
  if (s == "perf")
    return  SafetyCheck::perf;
  else if (s == "perf_threads" || s == "threads")
    return SafetyCheck::perf_threads;
  else if (s == "msa")
    return SafetyCheck::msa;
  else if (s == "msa_names")
    return SafetyCheck::msa_names;
  else if (s == "msa_dups")
    return SafetyCheck::msa_dups;
  else if (s == "msa_allgaps")
    return SafetyCheck::msa_allgaps;
  else if (s == "model")
    return SafetyCheck::model;
  else if (s == "model_zero_freqs")
    return SafetyCheck::model_zero_freqs;
  else if (s == "model_invalid_freqs")
    return SafetyCheck::model_invalid_freqs;
  else if (s == "model_lg4_freqs")
    return SafetyCheck::model_lg4_freqs;
  else if (s == "model_asc_bias")
    return SafetyCheck::model_asc_bias;
  else if (s == "model_overfit")
    return SafetyCheck::model_overfit;
  else if (s == "model_lh_impr")
    return SafetyCheck::model_lh_impr;
  else
    throw runtime_error("Invalid SafetyCheck enum value: " + s);
}

SafetyCheck::Flags SafetyCheck::from_multi_string(const string& s)
{
  auto ss = split_string(s, ',');

  SafetyCheck v;
  for (const string& s: ss)
    v.set(from_string(s));

  return v.flags();
}
