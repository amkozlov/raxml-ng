#include "RHASHeuristic.hpp"
#include "ModelDefinitions.hpp"
#include <algorithm>
#include "../log.hpp"

constexpr unsigned int NUM_RATEHET_MODELS = 5; // E, I, G, I+G, R

RHASHeuristic::RHASHeuristic(std::string reference_matrix, double delta_bic) : reference_matrix(reference_matrix), delta_bic{delta_bic} {

}

void RHASHeuristic::update(const candidate_model_t &candidate_model, double score) {
    if (candidate_model.matrix_name != reference_matrix ||
            candidate_model.rate_heterogeneity == rate_heterogeneity_t::FREE_RATE) {
        return;
    }

    const auto rate_het = candidate_model.rate_heterogeneity;
    observed_bic_score[rate_het] = score;

    bool contains_all_but_freerate = (observed_bic_score.size() == NUM_RATEHET_MODELS - 1
            && observed_bic_score.find(rate_heterogeneity_t::FREE_RATE) == observed_bic_score.end());

    if (contains_all_but_freerate && skip.size() == 0) {
        populate_skip();
    }
}

void RHASHeuristic::populate_skip() {
    LOG_INFO << "RHAS Heuristic engaged" << std::endl;
    using map_type = decltype(observed_bic_score)::value_type;
    double bic_min = std::min_element(observed_bic_score.cbegin(), observed_bic_score.cend(),
            [](const map_type &a, const map_type &b) {
            return a.second < b.second;
    })->second;

    for (auto it = observed_bic_score.cbegin(); it != observed_bic_score.cend(); ++it) {
        bool exceeding_bic_limit = it->second - bic_min > delta_bic;

        if (exceeding_bic_limit) {
            LOG_INFO << "Skipping rate het " << static_cast<int>(it->first) << "\n";
        }
        skip[it->first] = exceeding_bic_limit;
    }
}

bool RHASHeuristic::can_skip(const candidate_model_t &candidate) {
    if (skip.size() == 0)
        return false;

    auto it = skip.find(candidate.rate_heterogeneity);
    if (it == skip.end()) {
        return false;
    }

    return it->second;
}

void RHASHeuristic::clear() {
    observed_bic_score.clear();
    skip.clear();
}
