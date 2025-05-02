
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include <stdint.h>

#if defined(__clang__) || defined(__GNUC__)
#define LIKELY(x)   __builtin_expect(!!(x), 1)
#define UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
#define LIKELY(x)   (x)
#define UNLIKELY(x) (x)
#endif

#define N_TARGET 1
#define MAX_N_CLASS 1

// hack to prevent symbol name conflicts when multiple LightGBM models are linked statically
#define predict_unit0 ebg_predict_unit0
#define predict_unit1 ebg_predict_unit1
#define predict_unit2 ebg_predict_unit2
#define predict_unit3 ebg_predict_unit3
#define predict_unit4 ebg_predict_unit4
#define predict_unit5 ebg_predict_unit5
#define predict_unit6 ebg_predict_unit6
#define predict_unit7 ebg_predict_unit7
#define predict_unit8 ebg_predict_unit8
#define predict_unit9 ebg_predict_unit9
#define predict_unit10 ebg_predict_unit10
#define predict_unit11 ebg_predict_unit11
#define predict_unit12 ebg_predict_unit12
#define predict_unit13 ebg_predict_unit13
#define predict_unit14 ebg_predict_unit14
#define predict_unit15 ebg_predict_unit15
#define Entry ebg_Entry

union Entry {
  int missing;
  double fvalue;
  int qvalue;
};

int32_t ebg_get_num_target(void);
void ebg_get_num_class(int32_t* out);
int32_t ebg_get_num_feature(void);
const char* ebg_get_threshold_type(void);
const char* ebg_get_leaf_output_type(void);
void ebg_predict(union Entry* data, int pred_margin, double* result);
void ebg_postprocess(double* result);

void predict_unit0(union Entry* data, double* result);
void predict_unit1(union Entry* data, double* result);
void predict_unit2(union Entry* data, double* result);
void predict_unit3(union Entry* data, double* result);
void predict_unit4(union Entry* data, double* result);
void predict_unit5(union Entry* data, double* result);
void predict_unit6(union Entry* data, double* result);
void predict_unit7(union Entry* data, double* result);
void predict_unit8(union Entry* data, double* result);
void predict_unit9(union Entry* data, double* result);
void predict_unit10(union Entry* data, double* result);
void predict_unit11(union Entry* data, double* result);
void predict_unit12(union Entry* data, double* result);
void predict_unit13(union Entry* data, double* result);
void predict_unit14(union Entry* data, double* result);
void predict_unit15(union Entry* data, double* result);

