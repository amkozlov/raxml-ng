#include "RHASHeuristic.hpp"
#include "ModelDefinitions.hpp"
#include <algorithm>
#include <unordered_map>
#include "../log.hpp"

std::unordered_map<RateHeterogeneityDescriptor, bool> initialize_skip(const std::vector<RateHeterogeneityDescriptor> &selected_rhas)
{
    std::unordered_map<RateHeterogeneityDescriptor, bool>  skip;

    for (const auto &rhas : selected_rhas) {
        skip[rhas] = false;
    }

    return skip;
}


std::unordered_map<RateHeterogeneityType, unsigned int> initialize_missing_model_counts(const std::vector<RateHeterogeneityDescriptor> &selected_rhas)
{
    std::unordered_map<RateHeterogeneityType, unsigned int> missing_model_counts;

    for (const auto &rhas : selected_rhas) {
        auto it = missing_model_counts.emplace(rhas.type, 0).first;

        ++it->second;
    }

    return missing_model_counts;
}

RHASHeuristic::RHASHeuristic(SubstitutionModelDescriptor reference_matrix,
                             const std::vector<RateHeterogeneityDescriptor> &selected_rhas,
                             double delta_bic,
                             RHASHeuristicMode mode,
                             size_t partition_index)
    : mode{mode},
      reference_matrix{reference_matrix},
      delta_ic{delta_bic},
      observed_ic_score{},
      skip{initialize_skip(selected_rhas)},
      missing_model_counts{initialize_missing_model_counts(selected_rhas)},
      selected_rhas{selected_rhas},
      partition_index(partition_index)
{
}

void RHASHeuristic::drop_one(const RateHeterogeneityDescriptor &rhas)
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

void RHASHeuristic::update(const ModelDescriptor &candidate_model, double score) {
    if (candidate_model.substitution_model != reference_matrix) {
        return;
    }

    const auto rate_het = candidate_model.rate_heterogeneity;
    observed_ic_score[rate_het] = score;
    drop_one(rate_het);
    
    if (missing_model_counts.empty()) {
        reference_complete();
    }
}

void RHASHeuristic::reference_complete() {
    using map_type = decltype(observed_ic_score)::value_type;
    double bic_min = std::min_element(observed_ic_score.cbegin(), observed_ic_score.cend(),
            [](const map_type &a, const map_type &b) {
            return a.second < b.second;
    })->second;

    for (auto it = observed_ic_score.cbegin(); it != observed_ic_score.cend(); ++it) {
        const auto &rhas = it->first;

        const bool exceeding_bic_limit = it->second - bic_min > delta_ic;
        skip[rhas] = exceeding_bic_limit;
    }

    logger().logstream(LogLevel::debug, LogScope::thread)  << RAXML_LOG_TIMESTAMP << "Heuristically restricting partition " << partition_index << " to rate heterogeneity models ";
    for (const auto &e : skip)
    {
        if (e.second == true) continue;

        logger().logstream(LogLevel::debug, LogScope::thread) << "'" << e.first.label() << "' ";
    }
    logger().logstream(LogLevel::debug, LogScope::thread) << "\n";
}

void RHASHeuristic::set_optimal_category_count(RateHeterogeneityType type, unsigned int c) {
    auto it = optimal_category_count.find(type);
    if (it != optimal_category_count.cend()) return;

    optimal_category_count[type] = c;
    missing_model_counts.erase(type);

    if (missing_model_counts.empty()) {
        reference_complete();
    }
    
    // Skip all unobserved models with same RHAS type, since optimal category
    // count has been discovered the FreerateHeuristic must have converged.
    for (const auto &rhas : selected_rhas)
    {
        if (rhas.type != type) continue;

        const bool category_count_unobserved = observed_ic_score.find(rhas) == observed_ic_score.cend();

        if (category_count_unobserved)
        {
            skip[rhas] = true;
        }
    }

    if (mode == RHASHeuristicMode::OnlyOptimalCategoryCount) {
        for (auto &e : skip) {
            if (e.first.type != type) continue;

            e.second |= (e.first.category_count != c);
        }
    }
}

bool RHASHeuristic::can_skip(const ModelDescriptor &candidate) const {
    if (skip.empty())
        return false;

    const auto it = skip.find(candidate.rate_heterogeneity);
    if (it == skip.end()) {
        return false;
    }

    return it->second;
}

void RHASHeuristic::set_partition_index(size_t partition_index)
{
    this->partition_index = partition_index;
}
