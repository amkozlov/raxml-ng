#pragma once

#include <vector>
#include <unordered_map>
#include "ModelDefinitions.hpp"

/** Heuristically disable RHAS models based on performance of reference matrix.
 * All RHAS models that yield a BIC score worse than a specified delta (default value 10) from the best observed value on the reference matrix are skipped.
 *
 * For DNA data, our reference matrix typically would be GTR.
 * For example, we compute the BIC score with uniform RHAS, invariant sites,
 * gamma model and invariant + gamma.  If uniform RHAS and invariant sites
 * yield a much worse BIC score, we assume that there is strong evidence for
 * using a gamma distribution to model the RHAS, and that this fact does not
 * change if we use a different model matrix.  Therefore we could skip models
 * that use uniform RHAS or invariant sites and concentrate on models with
 * gamma RHAS.
 *
 * Equivalent to IQTree's autodetection of rate heterogeneity:
 * https://github.com/iqtree/iqtree2/blob/a00094e03d1ae984e1497e16738f91514df8c366/main/phylotesting.cpp#L2648-L2649
 */
class RHASHeuristic {
    public:
        RHASHeuristic(std::string reference_matrix = "GTR", double delta_bic = 10.0);

        /** Add model testing result that this heuristic should consider.
         *  If the model matrix does not coincide with the reference matrix specified
         *  in the constructor, the new finding will be ignored
         */
        void update(const candidate_model_t &candidate_model, double score);
        
        /** Check whether a given candidate model can be skipped because of poor expectations of its RHAS model
         */
        bool can_skip(const candidate_model_t &candidate_model);

        /** Reset previously recorded BIC scores */
        void clear();


    private:
        void populate_skip();

        std::string reference_matrix;
        std::unordered_map<rate_heterogeneity_t, double> observed_bic_score;
        std::unordered_map<rate_heterogeneity_t, bool> skip;
        double delta_bic;

};
