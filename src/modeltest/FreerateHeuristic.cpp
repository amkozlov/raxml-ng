#include "FreerateHeuristic.hpp"
#include "ModelDefinitions.hpp"
#include <algorithm>
#include <utility>

FreerateHeuristic::FreerateHeuristic(unsigned int min_cats, unsigned int max_cats)
    : min_categories{min_cats}, max_categories{max_cats} {}

void FreerateHeuristic::update(const candidate_model_t &candidate_model, double score) {
    if (candidate_model.rate_heterogeneity.type != rate_heterogeneity_type::FREE_RATE) {
        return;
    }

    auto it = score_map.find(candidate_model.substitution_model);
    if (it == score_map.end()) {
        it = score_map.emplace(
            candidate_model.substitution_model,
            score_entry(min_categories, max_categories)
        ).first;
    }

    const auto c = candidate_model.rate_heterogeneity.category_count;
    const auto i = index(c);
    auto &entry = it->second;
    entry.scores.at(i) = score;

    if (i > 0) {
        double previous_score = entry.scores.at(i - 1);

        if (previous_score != NO_SCORE_PRESENT && !has_score_improved(previous_score, score)) {
            entry.skip_start_index = std::min(entry.skip_start_index, c);
        }
    }

    if (i < entry.scores.size() - 1) {
        double next_score = entry.scores.at(i + 1);

        if (next_score != NO_SCORE_PRESENT && !has_score_improved(score, next_score)) {
            entry.skip_start_index = std::min(entry.skip_start_index, c + 1);
        }
    }

    const bool observed_score_increase = entry.skip_start_index <= max_categories;
    if (observed_score_increase) {
        const bool all_previous_scores_present = std::all_of(
                entry.scores.cbegin(),
                entry.scores.cbegin() + index(entry.skip_start_index),
                [](const auto &score ) { return score != NO_SCORE_PRESENT; });

        entry.converged = all_previous_scores_present;
    }
}

bool FreerateHeuristic::can_skip(const candidate_model_t &candidate_model) const {
    if (candidate_model.rate_heterogeneity.type != rate_heterogeneity_type::FREE_RATE) {
        return false;
    }

    auto it = score_map.find(candidate_model.substitution_model);

    if (it == score_map.end())
        return false;

    return candidate_model.rate_heterogeneity.category_count >= it->second.skip_start_index;
}

int FreerateHeuristic::optimal_category_count(const substitution_model_t &substitution_model) const {
    const auto it = score_map.find(substitution_model);

    if (it == score_map.cend() || !it->second.converged)
        return -1;

    return it->second.skip_start_index - 1;
}

void FreerateHeuristic::clear() {
    score_map.clear();
}
