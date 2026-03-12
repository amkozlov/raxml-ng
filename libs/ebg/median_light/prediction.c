
#include "header.h"

static const int32_t num_class[] = {  1, };

int32_t ebg_get_num_target(void) {
  return N_TARGET;
}

void ebg_get_num_class(int32_t* out) {
  for (int i = 0; i < N_TARGET; ++i) {
    out[i] = num_class[i];
  }
}

const char* ebg_get_threshold_type(void) {
  return "float64";
}
const char* ebg_get_leaf_output_type(void) {
  return "float64";
}


int32_t ebg_get_num_feature(void) {
  return 5;
}

void ebg_predict(union Entry* data, int pred_margin, double* result) {
//  unsigned int tmp;

  predict_unit0(data, result);
  predict_unit1(data, result);
  predict_unit2(data, result);
  predict_unit3(data, result);
  predict_unit4(data, result);
  predict_unit5(data, result);
  predict_unit6(data, result);
  predict_unit7(data, result);
  predict_unit8(data, result);
  predict_unit9(data, result);
  predict_unit10(data, result);
  predict_unit11(data, result);
  predict_unit12(data, result);
  predict_unit13(data, result);
  predict_unit14(data, result);
  predict_unit15(data, result);
  
  // Apply base_scores
  result[0] += 0;
  
  // Apply postprocessor
  if (!pred_margin) { ebg_postprocess(result); }
}

void ebg_postprocess(double* result) {
  // Do nothing
}
