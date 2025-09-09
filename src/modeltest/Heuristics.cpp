#include "Heuristics.hpp"
#include "FreerateHeuristic.hpp"
#include "ModelDefinitions.hpp"
#include "RHASHeuristic.hpp"



Heuristics::Heuristics(size_t partition_count, HeuristicSelection selection, const std::vector<RateHeterogeneityDescriptor> selected_rhas, const SubstitutionModelDescriptor &reference_matrix, unsigned int min_freerate_categories, unsigned int max_freerate_categories, double significant_ic_difference, RHASHeuristicMode rhas_mode)
    : selection{selection},
      reference_matrix{reference_matrix},
      selected_rhas{selected_rhas},
      rhas_heuristics{enabled(HeuristicType::RHAS) ? partition_count : 0 ,
                RHASHeuristic(reference_matrix, this->selected_rhas, significant_ic_difference, rhas_mode)},
      freerate_heuristics{enabled(HeuristicType::FREERATE) ? partition_count : 0,
                FreerateHeuristic(min_freerate_categories, max_freerate_categories)},
      invariant_freerate_heuristics{enabled(HeuristicType::FREERATE) ? partition_count : 0,
                FreerateHeuristic(min_freerate_categories, max_freerate_categories, RateHeterogeneityType::INVARIANT_FREE_RATE)}
{

    for (auto p = 0UL; p < rhas_heuristics.size(); ++p)
    {
        rhas_heuristics.at(p).set_partition_index(p);
    }

}

void Heuristics::update(unsigned int partition, const ModelDescriptor &candidate_model, double score)
{
    if (enabled(HeuristicType::FREERATE)) {
        freerate_heuristics.at(partition).update(candidate_model, score);
        invariant_freerate_heuristics.at(partition).update(candidate_model, score);
    }

    if (enabled(HeuristicType::RHAS)) {
        rhas_heuristics.at(partition).update(candidate_model, score);
    }

    if (enabled(HeuristicType::FREERATE) && 
        enabled(HeuristicType::RHAS)) {
        // Need to notify RHASHeuristic when FreerateHeuristic converges
        const int freerate_optimal_category_count = freerate_heuristics.at(partition).optimal_category_count(reference_matrix);
        if (freerate_optimal_category_count > 0) {
            rhas_heuristics.at(partition).set_optimal_category_count(RateHeterogeneityType::FREE_RATE, 
                    freerate_optimal_category_count);
        }

        const int inv_freerate_optimal_category_count = invariant_freerate_heuristics.at(partition).optimal_category_count(reference_matrix);
        if (inv_freerate_optimal_category_count > 0) {
            rhas_heuristics.at(partition).set_optimal_category_count(RateHeterogeneityType::INVARIANT_FREE_RATE, 
                    inv_freerate_optimal_category_count);
        }
    }
}

bool Heuristics::can_skip(unsigned int partition, const ModelDescriptor &candidate_model) const
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

bool Heuristics::evaluation_essential(unsigned int partition, const ModelDescriptor &c) const {
    bool essential = false;

    // Need to compute all RHAS variants of the reference substition matrix
    essential |= (c.substitution_model == reference_matrix && c.rate_heterogeneity.type != RateHeterogeneityType::FREE_RATE);

    // For freerate, only the categories up until the score worsens again are required
    essential |= (c.substitution_model == reference_matrix && \
                            c.rate_heterogeneity.type == RateHeterogeneityType::FREE_RATE && \
                            (!enabled(HeuristicType::FREERATE) || \
                             static_cast<int>(c.rate_heterogeneity.category_count) <= freerate_heuristics.at(partition).optimal_category_count(c.substitution_model) + 1));

    // For all other models, one of the enabled heuristics must deem the candidate "unskippable"
    essential |= (c.substitution_model != reference_matrix) && \
                  ((enabled(HeuristicType::FREERATE) && enabled(HeuristicType::RHAS) && \
                    (!freerate_heuristics.at(partition).can_skip(c) || !rhas_heuristics.at(partition).can_skip(c))) || \
                  (enabled(HeuristicType::FREERATE) && !freerate_heuristics.at(partition).can_skip(c) ) || \
                  (enabled(HeuristicType::RHAS) && !rhas_heuristics.at(partition).can_skip(c)));


    return essential;

}
