#ifndef HEURISTICS_HPP_
#define HEURISTICS_HPP_

#include "FreerateHeuristic.hpp"
#include "ModelDefinitions.hpp"
#include "RHASHeuristic.hpp"
#include "../Options.hpp"
#include <unordered_set>



/** Since heuristics need to be kept per partition and might optionally be disabled,
 *  we use this class to simplify access.
 */
class Heuristics
{
    public:
        Heuristics(size_t partition_count, HeuristicSelection selection, const std::vector<rate_heterogeneity_t> &selected_rhas, const substitution_model_t &reference_model, unsigned int min_freerate_categories, unsigned int max_freerate_categories, double significant_ic_difference);
        void update(unsigned int partition, const candidate_model_t &candidate_model, double score);
        bool can_skip(unsigned int partition, const candidate_model_t &candidate_model) const;
        ~Heuristics() = default;

        /** Return whether the evaluation of a given candidate was essential or could have been skipped in hindsight. */
        bool evaluation_essential(unsigned int partition, const candidate_model_t &candidate_model) const;

    private:
        bool enabled(const HeuristicType & heuristic) const;

        const HeuristicSelection selection;
        const substitution_model_t reference_model;
        std::vector<RHASHeuristic> rhas_heuristics;
        std::vector<FreerateHeuristic> freerate_heuristics;
};

#endif
