#ifndef HEURISTICS_HPP_
#define HEURISTICS_HPP_

#include "FreerateHeuristic.hpp"
#include "ModelDefinitions.hpp"
#include "RHASHeuristic.hpp"

/** Since heuristics need to be kept per partition and might optionally be disabled,
 *  we use this class to simplify access.
 */
class Heuristics
{
    public:
        Heuristics(size_t partition_count, HeuristicSelection selection, const std::vector<RateHeterogeneityDescriptor> selected_rhas, const SubstitutionModelDescriptor &reference_model, unsigned int min_freerate_categories, unsigned int max_freerate_categories, double significant_ic_difference, RHASHeuristicMode rhas_mode);
        void update(unsigned int partition, const ModelDescriptor &candidate_model, double score);
        bool can_skip(unsigned int partition, const ModelDescriptor &candidate_model) const;
        ~Heuristics() = default;

        /** Return whether the evaluation of a given candidate was essential or could have been skipped in hindsight. */
        bool evaluation_essential(unsigned int partition, const ModelDescriptor &candidate_model) const;

    private:
        bool enabled(const HeuristicType & heuristic) const;

        const HeuristicSelection selection;
        const SubstitutionModelDescriptor reference_matrix;
        bool invariant_freerate_enabled;
        std::vector<RateHeterogeneityDescriptor> selected_rhas;
        std::vector<RHASHeuristic> rhas_heuristics;
        std::vector<FreerateHeuristic> freerate_heuristics;
        std::vector<FreerateHeuristic> invariant_freerate_heuristics;
};

#endif
