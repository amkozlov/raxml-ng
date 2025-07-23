#pragma once

#include "ModelDefinitions.hpp"
#include <limits>
#include <unordered_map>
#include <vector>


/**
 * Heuristically stop freerate computation if IC score worsens after increasing
 * the number of categories. The rationale behind this is that the penalty for
 * the increased number of parameters will probably outweigh any improvements
 * of the likelihood score.
 * The heuristic tracks the scores for each substitution matrix individually,
 * since the optimal number of categories might depend on the matrix.
 *
 * This implementation does not make any assumptions on the order of arrival of
 * results to give more flexibility to the scheduling algorithm. This complicates
 * things a little bit, though. Given the following situation, we know that we
 * surely do not need to evaluate seven categories, since the BIC score already
 * worsened (increased) when going from five to six categories:
 *
 * BIC                          
 *  ▲                           
 *  │x                          
 *  │                           
 *  │                           
 *  │                           
 *  │          x                
 *  │        x                  
 *  │                           
 *  └──────────────► #Categories
 *   1 2 3 4 5 6 7              
 * 
 * However, the increase might happen earlier (e.g. when going from three to
 * four categories), and in this case we would choose three categories as the
 * optimal fit. Therefore, we must keep evaluating until we see an increase after
 * a steady decrease from the minimum number of categories, like so:
 *
 * BIC                          
 *  ▲                           
 *  │x                          
 *  │                           
 *  │                           
 *  │  x                        
 *  │          x                
 *  │      x x                  
 *  │    x                      
 *  └──────────────► #Categories
 *   1 2 3 4 5 6 7              
 *
 * In this case the scores have converged, and the optimal category count is three.
 */
class FreerateHeuristic {
    public:
        FreerateHeuristic(unsigned int min_cats, unsigned int max_cats);

        void update(const candidate_model_t &candidate_model, double score);

        bool can_skip(const candidate_model_t &candidate_model) const;

		/**
		 * If all required scores are present, return the number of rate categories that yielded the best (lowest) score. If not enough results are present to make that statement, return -1.
		 */
		int optimal_category_count(const substitution_model_t &substitution_model) const;

        void clear();


    private:
        constexpr static double NO_SCORE_PRESENT = std::numeric_limits<double>::lowest();

        struct score_entry {
            unsigned int skip_start_index;
            std::vector<double> scores;
            bool converged;

            score_entry(unsigned int min_categories, unsigned int max_categories)
                : skip_start_index(std::numeric_limits<unsigned int>::max()),
                scores(std::max(0, static_cast<int>(max_categories) - static_cast<int>(min_categories) + 1), NO_SCORE_PRESENT),
                converged(false)
            {}
        };

        unsigned int min_categories;
        unsigned int max_categories;
        std::unordered_map<substitution_model_t, score_entry> score_map;

        /** Helper function to map number of rate categories to index in
         * score_entry vector. E.g. if the minimum number of categories is 4,
         * we do not store values for categories 1 through 3 --> offset index
         * by -4.
         */
        inline uint64_t index(unsigned int rate_categories) const {
            assert(rate_categories >= min_categories);
            return rate_categories - min_categories;
        }

        inline bool has_score_improved(double &score1, double &score2) const {
            return score1 > score2;
        }
};
