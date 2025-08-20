#include "Heuristics.hpp"
#include "FreerateHeuristic.hpp"
#include "ModelDefinitions.hpp"
#include "RHASHeuristic.hpp"

Heuristics::Heuristics(size_t partition_count, HeuristicSelection selection, const std::vector<rate_heterogeneity_t> &selected_rhas, const substitution_model_t &reference_model, unsigned int min_freerate_categories, unsigned int max_freerate_categories, double significant_ic_difference)
    : selection{selection},
      reference_model{reference_model},
      rhas_heuristics{enabled(HeuristicType::RHAS) ? partition_count : 0 ,
                RHASHeuristic(reference_model, selected_rhas, significant_ic_difference)},
      freerate_heuristics{enabled(HeuristicType::FREERATE) ? partition_count : 0,
                FreerateHeuristic(min_freerate_categories, max_freerate_categories)}
{

    for (auto p = 0UL; p < rhas_heuristics.size(); ++p)
    {
        rhas_heuristics.at(p).set_partition_index(p);
    }

}

void Heuristics::update(unsigned int partition, const candidate_model_t &candidate_model, double score)
{
    if (enabled(HeuristicType::FREERATE)) {
        freerate_heuristics.at(partition).update(candidate_model, score);
    }

    if (enabled(HeuristicType::RHAS)) {
        rhas_heuristics.at(partition).update(candidate_model, score);
    }

    if (enabled(HeuristicType::FREERATE) && 
        enabled(HeuristicType::RHAS)) {
        const int optimal_category_count = freerate_heuristics.at(partition).optimal_category_count(reference_model);

        if (optimal_category_count > 0) {
            rhas_heuristics.at(partition).freerate_complete(optimal_category_count);
        }
    }
}

bool Heuristics::can_skip(unsigned int partition, const candidate_model_t &candidate_model) const
{
    if (enabled(HeuristicType::FREERATE) &&
            freerate_heuristics.at(partition).can_skip(candidate_model)) {
        return true;
    }

    if (enabled(HeuristicType::RHAS) &&
            rhas_heuristics.at(partition).can_skip(candidate_model)) {
        return true;
    }

    return false;
}

bool Heuristics::enabled(const HeuristicType &heuristic) const {
    return selection.find(heuristic) != selection.cend();
}

bool Heuristics::evaluation_essential(unsigned int partition, const candidate_model_t &c) const {
    bool essential = false;

    // Need to compute all RHAS variants of the reference substition matrix
    essential |= (c.substitution_model == reference_model && c.rate_heterogeneity.type != rate_heterogeneity_type::FREE_RATE);

    // For freerate, only the categories up until the score worsens again are required
    essential |= (c.substitution_model == reference_model && \
                            c.rate_heterogeneity.type == rate_heterogeneity_type::FREE_RATE && \
                            (!enabled(HeuristicType::FREERATE) || \
                             static_cast<int>(c.rate_heterogeneity.category_count) <= freerate_heuristics.at(partition).optimal_category_count(c.substitution_model) + 1));

    // For all other models, one of the enabled heuristics must deem the candidate "unskippable"
    essential |= (c.substitution_model != reference_model) && \
                  ((enabled(HeuristicType::FREERATE) && enabled(HeuristicType::RHAS) && \
                    (!freerate_heuristics.at(partition).can_skip(c) || !rhas_heuristics.at(partition).can_skip(c))) || \
                  (enabled(HeuristicType::FREERATE) && !freerate_heuristics.at(partition).can_skip(c) ) || \
                  (enabled(HeuristicType::RHAS) && !rhas_heuristics.at(partition).can_skip(c)));


    return essential;

}
