#pragma once

#include "corax/model/gamma.h"
#include "types.hpp"
#include <string>
#include <strings.h>
#include <set>
#include <array>
#include <optional>

/**
 * Class to resolve from and to labels for different Gamma modes (mean, median, star, ...)
 */
class GammaModes
{
public:
  /** Try to get coraxlib attribute for gamma mode from supplied string. */
  [[nodiscard]]
  static std::optional<int> from_string(const std::string &s); 

  /** Try to get coraxlib attribute for gamma mode from supplied character. */
  static std::optional<int> from_char(int character);

  /** Get short flag for gamma mode */
  [[nodiscard]]
  inline static char flag(int mode) {
    return labels.at(mode).flag;
  }

  /** Get human readable label for gamma mode */
  [[nodiscard]]
  inline static std::string label(int mode) {
    return {labels.at(mode).label};
  }
  
  /** Get set of all gamma modes */
  [[nodiscard]]
  static std::set<int> all();

  /* Get a comma-separated list of allowed gamma mode labels for use in help texts*/
  [[nodiscard]]
  static std::string all_labels();


private:
  struct label_entry_t {
    int mode;
    const char *label;
    char flag;
  };

  static constexpr std::array<label_entry_t, 3> labels {{
    {CORAX_GAMMA_RATES_MEAN, "mean", 'm'},
    {CORAX_GAMMA_RATES_MEDIAN, "median", 'a'},
    {CORAX_GAMMA_RATES_WEIGHTS_LLOYD_MAX, "star", 's'}
  }};


  static_assert(labels.front().mode == 0 && labels.back().mode == labels.size() - 1,
      "list of labels must be indexable by mode");
};
