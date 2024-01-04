#ifndef RAXML_CONSTANTS_HPP_
#define RAXML_CONSTANTS_HPP_

// defaults
#define RAXML_LOGLH_TOLERANCE     1e-12

#define DEF_LH_EPSILON            10
#define OPT_LH_EPSILON            0.1
#define RAXML_PARAM_EPSILON       0.001  //0.01
#define RAXML_BFGS_FACTOR         1e7

#define DEF_LH_EPSILON_BRLEN_TRIPLET   1000

#define DEF_LH_EPSILON_V11         0.1

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

#define RAXML_CPYTHIA_TREES_NUM   100

// cpu features
#define RAXML_CPU_SSE3  (1<<0)
#define RAXML_CPU_AVX   (1<<1)
#define RAXML_CPU_FMA3  (1<<2)
#define RAXML_CPU_AVX2  (1<<3)

#endif /* RAXML_CONSTANTS_HPP_ */
