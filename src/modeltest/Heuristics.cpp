#include "Heuristics.hpp"
#include "ModelDefinitions.hpp"
#include "RHASHeuristic.hpp"

Heuristics::Heuristics(unsigned int partition_count, unsigned int selection, const std::vector<rate_heterogeneity_t> &selected_rhas, const substitution_model_t &reference_model, const Options &options)
    : selection{selection},
      reference_model{reference_model}
{
    if (enabled(HeuristicSelection::FREERATE)) {
        freerate_heuristics.resize(partition_count, 
                FreerateHeuristic(options.free_rate_min_categories, options.free_rate_max_categories));
    }

    if (enabled(HeuristicSelection::RHAS)) {
        rhas_heuristics.resize(partition_count, RHASHeuristic(reference_model, selected_rhas));
    }
}

void Heuristics::update(unsigned int partition, const candidate_model_t &candidate_model, double score)
{
    if (enabled(HeuristicSelection::FREERATE)) {
        freerate_heuristics.at(partition).update(candidate_model, score);
    }

    if (enabled(HeuristicSelection::RHAS)) {
        rhas_heuristics.at(partition).update(candidate_model, score);
    }

    if (enabled(HeuristicSelection::FREERATE) && 
        enabled(HeuristicSelection::RHAS)) {
        const int optimal_category_count = freerate_heuristics.at(partition).optimal_category_count(reference_model);

        if (optimal_category_count > 0) {
            rhas_heuristics.at(partition).freerate_complete(optimal_category_count);
        }
    }
}

bool Heuristics::can_skip(unsigned int partition, const candidate_model_t &candidate_model) const
{
    if (enabled(HeuristicSelection::FREERATE) &&
            freerate_heuristics.at(partition).can_skip(candidate_model)) {
        return true;
    }

    if (enabled(HeuristicSelection::RHAS) &&
            rhas_heuristics.at(partition).can_skip(candidate_model)) {
        return true;
    }

    return false;
}

bool Heuristics::enabled(const HeuristicSelection &heuristic) const {
    return selection & static_cast<unsigned int>(heuristic);
}
