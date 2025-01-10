#include "RHASHeuristic.hpp"
#include "ModelDefinitions.hpp"
#include <algorithm>
#include "../log.hpp"

RHASHeuristic::RHASHeuristic(substitution_model_t reference_model,
                             double delta_bic)
    : reference_model{reference_model},
      delta_bic{delta_bic} {
}

void RHASHeuristic::update(const candidate_model_t &candidate_model, double score) {
    if (candidate_model.substitution_model != reference_model) {
        return;
    }

    const auto rate_het = candidate_model.rate_heterogeneity;
    observed_bic_score[rate_het] = score;
}

void RHASHeuristic::reference_complete() {
    if (!skip.empty()) {
        return;
    }

    using map_type = decltype(observed_bic_score)::value_type;
    double bic_min = std::min_element(observed_bic_score.cbegin(), observed_bic_score.cend(),
            [](const map_type &a, const map_type &b) {
            return a.second < b.second;
    })->second;

    for (auto it = observed_bic_score.cbegin(); it != observed_bic_score.cend(); ++it) {
        bool exceeding_bic_limit = it->second - bic_min > delta_bic;

        if (exceeding_bic_limit) {
            LOG_DEBUG << "Skipping rate heterogeneity model '" << it->first.label() << "'\n";
        }
        skip[it->first] = exceeding_bic_limit;
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

void RHASHeuristic::clear() {
    observed_bic_score.clear();
    skip.clear();
}
