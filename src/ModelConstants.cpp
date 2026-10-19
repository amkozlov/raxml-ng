#include "ModelConstants.hpp"

#include <algorithm>

std::optional<int> GammaModes::from_string(const std::string &s) {
  if (s.size() == 1) return from_char(s.c_str()[0]);

  auto it = std::find_if(labels.cbegin(), labels.cend(),
  [&s](const label_entry_t &e) {
      return strncasecmp(e.label, s.c_str(), s.size()) == 0;
  });

  if (it == labels.cend()) {
    return {};
  }
  return it->mode;
}

std::optional< int> GammaModes::from_char(int character) {
  const auto c = std::tolower(character);
  auto it = std::find_if(labels.cbegin(), labels.cend(), [c](const label_entry_t &e) { return e.flag == c; });

  if (it == labels.cend()) {
    return {};
  }
  return {it->mode};
}

std::set<int> GammaModes::all() {
  std::set<int> result;
  for (auto &e : labels) {
    result.insert(e.mode);
  }
  return result;
}

std::string GammaModes::all_labels() {
  std::string result;
  for (const auto &e : labels) {
    result += (result.empty() ? "" : ",") + std::string(e.label);
  }

  return result;
}
