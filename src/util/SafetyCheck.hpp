#ifndef RAXML_SAFETYCHECK_HPP_
#define RAXML_SAFETYCHECK_HPP_

#include <cinttypes>
#include <string>

struct SafetyCheck
{
  typedef uint64_t enum_type;

  enum Flags: enum_type
  {
    none                 = 0,
    all                  = ~0u,
    perf_threads         = 1 << 0,
    perf                 = perf_threads,
    msa_names            = 1 << 10,
    msa_dups             = 1 << 11,
    msa_allgaps          = 1 << 12,
    msa                  = msa_names | msa_dups | msa_allgaps,
    model_zero_freqs     = 1 << 21,
    model_invalid_freqs  = 1 << 22,
    model_lg4_freqs      = 1 << 23,
    model_asc_bias       = 1 << 24,
    model_overfit        = 1 << 25,
    model_lh_impr        = 1 << 26,
    model                = model_zero_freqs | model_invalid_freqs | model_lg4_freqs |
                           model_asc_bias | model_overfit | model_lh_impr
  };


    // Constructors, copy assignment etc as needed. Rule of five.
  SafetyCheck(SafetyCheck const&) = default;

  SafetyCheck(Flags v = Flags::none) : value(v)
    {}

  SafetyCheck& operator= (Flags v)
  {
    value = v;
    return *this;
  }

  static Flags from_string(const std::string& s);
  static Flags from_multi_string(const std::string& s);

  void set(Flags v) { value |= static_cast<enum_type>(v); }
  void unset(Flags v) { value &= ~static_cast<enum_type>(v); }

  void set(const std::string& s) { set(from_multi_string(s)); }
  void unset(const std::string& s) { unset(from_multi_string(s)); }

  Flags flags() const { return static_cast<Flags>(value); }
  bool isset(Flags v) const { enum_type b = static_cast<enum_type>(v); return (value & b) == b; }
  bool isall() const { return value == Flags::all; }
  bool isnone() const { return value == Flags::none; }
  bool isany() const { return !isnone(); }

private:
  enum_type value;
};

#endif /* RAXML_SAFETYCHECK_HPP_ */
