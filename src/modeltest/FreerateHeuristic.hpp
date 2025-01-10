#pragma once

#include "ModelDefinitions.hpp"
#include <limits>
#include <unordered_map>
#include <vector>

constexpr double NO_SCORE_PRESENT = std::numeric_limits<double>::lowest();

struct score_entry {
    unsigned int skip_start_index;
    std::vector<double> scores;

    score_entry(unsigned int min_categories, unsigned int max_categories)
        : skip_start_index(std::numeric_limits<unsigned int>::max()),
          scores(std::max(0, static_cast<int>(max_categories) - static_cast<int>(min_categories) + 1), NO_SCORE_PRESENT)
    {}
};

/**
 * Heuristically stop freerate computation if IC score worsens after increasing
 * the number of categories. The rationale behind this is that the penalty for
 * the increased number of parameters will probably outweigh any improvements
 * of the likelihood score.
 *
 * This implementation does not require the category count to be increased 
 */
// TODO: add 
class FreerateHeuristic {
    public:
        FreerateHeuristic(unsigned int min_cats, unsigned int max_cats);

        void update(const candidate_model_t &candidate_model, double score);

        bool can_skip(const candidate_model_t &candidate_model) const;

        void clear();


    private:
        unsigned int min_categories;
        unsigned int max_categories;
        std::unordered_map<substitution_model_t, score_entry> score_map;

        inline uint64_t index(unsigned int rate_categories) const {
            assert(rate_categories >= min_categories);
            return rate_categories - min_categories;
        }

        inline bool has_score_improved(double &score1, double &score2) const {
            return score1 > score2;
        }

};
