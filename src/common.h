#ifndef RAXML_COMMON_H_
#define RAXML_COMMON_H_

#include <unistd.h>

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <array>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>
#include <random>

extern "C" {
//#include <libpll/pll.h>
#include <libpll/pll_optimize.h>
#include <libpll/pll_msa.h>
#include <libpll/pll_tree.h>
#include <libpll/pllmod_util.h>
#include <libpll/pllmod_algorithm.h>
}

#include "types.hpp"
#include "constants.hpp"
#include "ParallelContext.hpp"
#include "log.hpp"
#include "SystemTimer.hpp"

#define RAXML_DOUBLE_TOLERANCE    1e-14

// defaults
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

/* used to supress compiler warnings about unused args */
#define UNUSED(expr) while (0) { (void)(expr); }

// cpu features
#define RAXML_CPU_SSE3  (1<<0)
#define RAXML_CPU_AVX   (1<<1)
#define RAXML_CPU_FMA3  (1<<2)
#define RAXML_CPU_AVX2  (1<<3)

/* system utils */
void sysutil_fatal(const char * format, ...);
void sysutil_fatal_libpll();
void libpll_check_error(const std::string& errmsg);
void libpll_reset_error();

double sysutil_gettime();
void sysutil_show_rusage();
unsigned long sysutil_get_memused();
unsigned long sysutil_get_memtotal();

unsigned long sysutil_get_cpu_features();
unsigned int sysutil_simd_autodetect();

const SystemTimer& global_timer();

std::string sysutil_realpath(const std::string& path);
bool sysutil_file_exists(const std::string& fname, int access_mode = F_OK);

#endif /* RAXML_COMMON_H_ */
