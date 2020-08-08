#ifndef RAXML_CONSTANTS_HPP_
#define RAXML_CONSTANTS_HPP_

// defaults
#define RAXML_DOUBLE_TOLERANCE    1e-14

#define DEF_LH_EPSILON            0.1
#define OPT_LH_EPSILON            0.1
#define RAXML_PARAM_EPSILON       0.001  //0.01
#define RAXML_BFGS_FACTOR         1e7

#define RAXML_BRLEN_SMOOTHINGS    32
#define RAXML_BRLEN_DEFAULT       0.1
#define RAXML_BRLEN_MIN           1.0e-6
#define RAXML_BRLEN_MAX           100.
#define RAXML_BRLEN_TOLERANCE     1.0e-7

#define RAXML_PINV_MIN            1.0e-9
#define RAXML_PINV_MAX            0.99

#define RAXML_FREERATE_MIN        0.001
#define RAXML_FREERATE_MAX        100.

#define RAXML_BRLEN_SCALER_MIN    0.01
#define RAXML_BRLEN_SCALER_MAX    100.

#define RAXML_RATESCALERS_TAXA    2000

#define RAXML_DEFAULT_PRECISION   6

#define RAXML_BOOTSTOP_CUTOFF     0.03
#define RAXML_BOOTSTOP_INTERVAL   50
#define RAXML_BOOTSTOP_PERMUTES   1000

// cpu features
#define RAXML_CPU_SSE3  (1<<0)
#define RAXML_CPU_AVX   (1<<1)
#define RAXML_CPU_FMA3  (1<<2)
#define RAXML_CPU_AVX2  (1<<3)


/* 1   = A/A = A  | 2   = C/C = C | 4    = G/G = G | 8   = T/T = T
 * 16  = A/C = M  | 32  = A/G = R | 64   = A/T = W | 128 = C/G = S
 * 256 = C/T = Y  | 512 = G/T = K | 1023 = -/- = N                  */

const pll_state_t pll_map_diploid10[256] =
 {
   0,  0,   0,   0,  0,  0,  0,    0,    0,   0,  0,   0,  0,    0,    0,    0,
   0,  0,   0,   0,  0,  0,  0,    0,    0,   0,  0,   0,  0,    0,    0,    0,
   0,  0,   0,   0,  0,  0,  0,    0,    0,   0,  0,   0,  0, 1023,    0,    0,
   0,  0,   0,   0,  0,  0,  0,    0,    0,   0,  0,   0,  0,    0,    0, 1023,
   0,  1,   0,   2,  0,  0,  0,    4,    0,   0,  0, 512,  0,   16, 1023, 1023,
   0,  0,  32, 128,  8,  8,  0,   64, 1023, 256,  0,   0,  0,    0,    0,    0,
   0,  1,   0,   2,  0,  0,  0,    4,    0,   0,  0, 512,  0,   16, 1023, 1023,
   0,  0,  32, 128,  8,  8,  0,   64, 1023, 256,  0,   0,  0,    0,    0,    0,
   0,  0,   0,   0,  0,  0,  0,    0,    0,   0,  0,   0,  0,    0,    0,    0,
   0,  0,   0,   0,  0,  0,  0,    0,    0,   0,  0,   0,  0,    0,    0,    0,
   0,  0,   0,   0,  0,  0,  0,    0,    0,   0,  0,   0,  0,    0,    0,    0,
   0,  0,   0,   0,  0,  0,  0,    0,    0,   0,  0,   0,  0,    0,    0,    0,
   0,  0,   0,   0,  0,  0,  0,    0,    0,   0,  0,   0,  0,    0,    0,    0,
   0,  0,   0,   0,  0,  0,  0,    0,    0,   0,  0,   0,  0,    0,    0,    0,
   0,  0,   0,   0,  0,  0,  0,    0,    0,   0,  0,   0,  0,    0,    0,    0,
   0,  0,   0,   0,  0,  0,  0,    0,    0,   0,  0,   0,  0,    0,    0,    0
 };


#endif /* RAXML_CONSTANTS_HPP_ */
