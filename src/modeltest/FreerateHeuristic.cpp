#include "FreerateHeuristic.hpp"
#include "ModelDefinitions.hpp"
#include <algorithm>
#include <utility>

constexpr double FreerateHeuristic::NO_SCORE_PRESENT; /* Required in C++14, remove when upgrading to C++17 */

FreerateHeuristic::FreerateHeuristic(unsigned int min_cats, unsigned int max_cats, RateHeterogeneityType type)
    : type{type}, min_categories{min_cats}, max_categories{max_cats}, score_map{}
{
  assert(min_categories <= max_categories);
}

void FreerateHeuristic::update(const ModelDescriptor &candidate_model, double score)
{
  if (candidate_model.rate_heterogeneity.type != type) {
    return;
  }

  auto it = score_map.find(candidate_model.substitution_model);
  if (it == score_map.end()) {
    it = score_map.emplace(candidate_model.substitution_model, score_entry(min_categories, max_categories)).first;
  }

  const auto c = candidate_model.rate_heterogeneity.category_count;
  const auto i = index(c);
  auto &entry = it->second;
  entry.scores.at(i) = score;

  if (i > 0) {
    double previous_score = entry.scores.at(i - 1);

    if (previous_score != NO_SCORE_PRESENT && !has_score_improved(previous_score, score)) {
      entry.ncat_skip_threshold = std::min(entry.ncat_skip_threshold, c);
    }
  }

  if (i < entry.scores.size() - 1) {
    double next_score = entry.scores.at(i + 1);

    if (next_score != NO_SCORE_PRESENT && !has_score_improved(score, next_score)) {
      entry.ncat_skip_threshold = std::min(entry.ncat_skip_threshold, c + 1);
    }
  }

  const bool observed_score_increase = entry.ncat_skip_threshold <= max_categories;
  if (observed_score_increase) {
    const bool all_previous_scores_present =
        std::all_of(entry.scores.cbegin(), entry.scores.cbegin() + index(entry.ncat_skip_threshold),
                    [](const double &score) { return score != NO_SCORE_PRESENT; });

    entry.converged = all_previous_scores_present;
  }
}

bool FreerateHeuristic::can_skip(const score_entry &entry, unsigned int c) const
{
  if (entry.converged) {
    const auto category_count_optimum = entry.ncat_skip_threshold - 1;
    return c != category_count_optimum;
  }

  return c >= entry.ncat_skip_threshold;
}

bool FreerateHeuristic::can_skip(const ModelDescriptor &candidate_model) const
{
  if (candidate_model.rate_heterogeneity.type != type) {
    return false;
  }

  const auto c = candidate_model.rate_heterogeneity.category_count;

  auto it = score_map.find(candidate_model.substitution_model);
  if (it != score_map.cend() && can_skip(it->second, c))
    return true;

  return false;
}

int FreerateHeuristic::optimal_category_count(const SubstitutionModelDescriptor &substitution_model) const
{
  const auto it = score_map.find(substitution_model);

  if (it == score_map.cend() || !it->second.converged)
    return -1;

  return it->second.ncat_skip_threshold - 1;
}

void FreerateHeuristic::clear() { score_map.clear(); }
