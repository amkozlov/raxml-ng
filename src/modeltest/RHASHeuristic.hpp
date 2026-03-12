#pragma once

#include "ModelDefinitions.hpp"
#include <unordered_map>

enum class RHASHeuristicMode
{
  OnlyOptimalCategoryCount,
  AllSignficantCategoryCounts
};

/** Heuristically disable RHAS models based on performance of reference matrix.
 * All RHAS models that yield a BIC score worse than a specified delta (default value 10) from the best observed value
 * on the reference matrix are skipped.
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
class RHASHeuristic
{
public:
  RHASHeuristic(SubstitutionModelDescriptor reference_matrix,
                const std::vector<RateHeterogeneityDescriptor> &selected_rhas, double delta_bic, RHASHeuristicMode mode,
                size_t partition_index = 0);

  RHASHeuristic(const RHASHeuristic &) = default;

  /** Add model testing result that this heuristic should consider.
   *  If the model matrix does not coincide with the reference matrix specified
   *  in the constructor, the new finding will be ignored
   */
  void update(const ModelDescriptor &candidate_model, double score);

  /** Signals the optimal category count for a certain RHAS type.
   * This prevents RHASHeuristic from waiting on freerate candidates that will never be computed. */
  void set_optimal_category_count(RateHeterogeneityType rhas_type, unsigned int optimal_category_count);

  /** Check whether a given candidate model can be skipped because of poor expectations of its RHAS model
   */
  bool can_skip(const ModelDescriptor &candidate_model) const;

  void set_partition_index(size_t partition_index);

private:
  RHASHeuristicMode mode;

  /** Signals that all reference RHAS variants have been computed and that evaluation of heuristic can start now. */
  void reference_complete();

  void drop_one(const RateHeterogeneityDescriptor &rhas);

  SubstitutionModelDescriptor reference_matrix;
  double delta_ic;

  std::unordered_map<RateHeterogeneityDescriptor, double> observed_ic_score;

  std::unordered_map<RateHeterogeneityDescriptor, bool> skip;

  /** Maps from a rate heterogeneity type to the number of outstanding
   * results with that type. The latter is typically 1 (e.g. for +E, +I where
   * we don't vary the category count) but for freerate it is the number of
   * category counts to be tested (e.g. 5 if we consider +R2,...,+R6) */
  std::unordered_map<RateHeterogeneityType, unsigned int> missing_model_counts;

  std::unordered_map<RateHeterogeneityType, unsigned int> optimal_category_count;

  const std::vector<RateHeterogeneityDescriptor> &selected_rhas;
  size_t partition_index;
};
