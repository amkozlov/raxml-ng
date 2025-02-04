#ifndef RAXML_EBG_H
#define RAXML_EBG_H

// important: keep this above the includes
#ifdef __cplusplus
extern "C"
{
#endif

  /**
   * A structure that contains EBG features.
   */
  typedef struct
  {
    /**
     * ID of the tree branch
     */
    unsigned int branch_id;

    /**
     * Parsimony bootstrap support (PBS), range 0.0 - 1.0
     */
    double parsimony_bootstrap_support;

    /**
     * Parsimony support (PS), range 0.0 - 1.0
     */
    double parsimony_support;

    /**
     * Normalized length of the branch (relative to sum of brlens in the tree)
     */
    double norm_branch_length;

    /**
     * Absolute branch length
     */
    double branch_length;

    /**
     * Mean Normalized RF distance between parsimony bootstrap trees
     */
    double mean_norm_rf_distance;

    /**
     * The skewness of the PBS of all inner branches of the input tree
     */
    double skewness_bootstrap_pars_support_tree;
  } ebg_light_features;

  /**
   * Predicts the branch bootstrap support values given its features
   *
   * @param features The features of the branch
   * @return The predicted bootstrap support (value between 0.0 and 1.0)
   */
  double ebg_predict_branch_support(const ebg_light_features *features);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // RAXML_EBG_H
