#ifndef HEURISTICS_HPP_
#define HEURISTICS_HPP_

#include "FreerateHeuristic.hpp"
#include "ModelDefinitions.hpp"
#include "RHASHeuristic.hpp"
#include "../Options.hpp"


/** Used as flags to enable/disable certain heuristics. */
enum class HeuristicSelection
{
    FREERATE = 1,
    RHAS = 2,
};

/** Since heuristics need to be kept per partition and might optionally be disabled,
 *  we use this class to simplify access.
 */
class Heuristics
{
    public:
        Heuristics(unsigned int partition_count, unsigned int selection, const std::vector<rate_heterogeneity_t> &selected_rhas, const substitution_model_t &reference_model, const Options &options);
        void update(unsigned int partition, const candidate_model_t &candidate_model, double score);
        bool can_skip(unsigned int partition, const candidate_model_t &candidate_model) const;
        ~Heuristics() = default;

    private:
        bool enabled(const HeuristicSelection & heuristic) const;

        unsigned int selection;
        substitution_model_t reference_model;
        std::vector<RHASHeuristic> rhas_heuristics;
        std::vector<FreerateHeuristic> freerate_heuristics;
};

#endif
