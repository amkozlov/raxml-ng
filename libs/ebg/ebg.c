#include "ebg.h"

#include "median_light/header.h"

double ebg_predict_branch_support(const ebg_light_features *features)
{
  int num_features = ebg_get_num_feature();
  union Entry *feat = (union Entry *)calloc(num_features, sizeof(union Entry));

  double prediction_features[] = {
//      (double) features->branch_id,  // not used for regression (?)
      features->parsimony_bootstrap_support,
      features->parsimony_support,
//      features->norm_branch_length,
      features->branch_length,
      features->mean_norm_rf_distance,
      features->skewness_bootstrap_pars_support_tree
  };

  for (int i = 0; i < num_features; ++i)
  {
    feat[i].fvalue = prediction_features[i];
  }

  int prediction_margin = 0;
  double prediction;
  ebg_predict(feat, prediction_margin, &prediction);
  free(feat);

  // LightGBM may produce results lower than 0.0 or higher than 1.0
  // -> clip the difficulty to [0.0, 1.0]
  if (prediction < 0.0) prediction = 0.0;
  if (prediction > 1.0) prediction = 1.0;

  return prediction;
}
