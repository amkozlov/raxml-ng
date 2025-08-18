#include "RHASHeuristic.hpp"
#include "ModelDefinitions.hpp"
#include <algorithm>
#include <unordered_map>
#include "../log.hpp"

std::unordered_map<rate_heterogeneity_t, bool> initialize_skip(const std::vector<rate_heterogeneity_t> &selected_rhas)
{
    std::unordered_map<rate_heterogeneity_t, bool>  skip;

    for (const auto &rhas : selected_rhas) {
        skip[rhas] = false;
    }

    return skip;
}


std::unordered_map<rate_heterogeneity_type, unsigned int> initialize_missing_model_counts(const std::vector<rate_heterogeneity_t> &selected_rhas)
{
    std::unordered_map<rate_heterogeneity_type, unsigned int> missing_model_counts;

    for (const auto &rhas : selected_rhas) {
        auto it = missing_model_counts.emplace(rhas.type, 0).first;

        ++it->second;
    }

    return missing_model_counts;
}

RHASHeuristic::RHASHeuristic(substitution_model_t reference_model,
                             const std::vector<rate_heterogeneity_t> &selected_rhas,
                             double delta_bic)
    : reference_model{reference_model},
      delta_bic{delta_bic},
      observed_bic_score{},
      skip{initialize_skip(selected_rhas)},
      missing_model_counts{initialize_missing_model_counts(selected_rhas)},
      freerate_optimal_category_count{-1}
{
}

void RHASHeuristic::drop_one(const rate_heterogeneity_t &rhas)
{
    const auto type = rhas.type;
    auto it = missing_model_counts.find(type);
    if (it == missing_model_counts.end() || it->second <= 0) {
        /* In some cases, freerate converges while a higher category count is
         * still in-flight. In this case freerate will already be removed from
         * the missing_model_counts and we do not need to worry about it. */
        return;
    }
    assert(it != missing_model_counts.end());
    assert(it->second > 0);
    auto remaining_outstanding_scores = --it->second;

    if (remaining_outstanding_scores == 0)
        missing_model_counts.erase(it);
}

void RHASHeuristic::update(const candidate_model_t &candidate_model, double score) {
    if (candidate_model.substitution_model != reference_model) {
        return;
    }

    const auto rate_het = candidate_model.rate_heterogeneity;
    observed_bic_score[rate_het] = score;
    drop_one(rate_het);
    
    if (missing_model_counts.empty()) {
        reference_complete();
    }
}

void RHASHeuristic::reference_complete() {
    using map_type = decltype(observed_bic_score)::value_type;
    double bic_min = std::min_element(observed_bic_score.cbegin(), observed_bic_score.cend(),
            [](const map_type &a, const map_type &b) {
            return a.second < b.second;
    })->second;

    for (auto it = observed_bic_score.cbegin(); it != observed_bic_score.cend(); ++it) {
        const auto &rhas = it->first;

        const bool exceeding_bic_limit = it->second - bic_min > delta_bic;
        skip[rhas] = exceeding_bic_limit;

        /** One could argue that the following check rather belongs into FreerateHeuristic, but by placing 
         * it here we keep FreerateHeuristic free from assumption that the optimal category count holds
         * across different model matrices.
         */
        if (rhas.type == rate_heterogeneity_type::FREE_RATE && freerate_optimal_category_count > -1) {
            skip[rhas] |= (rhas.category_count != static_cast<unsigned int>(freerate_optimal_category_count));
        }

        if (skip[rhas]) {
        }
    }

    logger().logstream(LogLevel::debug, LogScope::thread)  << RAXML_LOG_TIMESTAMP << "Heuristically restricting to rate heterogeneity models ";
    for (const auto &e : skip)
    {
        if (e.second == true) continue;

        logger().logstream(LogLevel::debug, LogScope::thread) << "'" << e.first.label() << "' ";
    }
    logger().logstream(LogLevel::debug, LogScope::thread) << "\n";
}

void RHASHeuristic::freerate_complete(int optimal_category_count) {
    if (freerate_optimal_category_count > -1) {
        return;
    }

    missing_model_counts.erase(rate_heterogeneity_type::FREE_RATE);
    freerate_optimal_category_count = optimal_category_count;

    if (missing_model_counts.empty()) {
        reference_complete();
    }
}

bool RHASHeuristic::can_skip(const candidate_model_t &candidate) const {
    if (skip.empty())
        return false;

    const auto it = skip.find(candidate.rate_heterogeneity);
    if (it == skip.end()) {
        return true;
    }

    return it->second;
}
