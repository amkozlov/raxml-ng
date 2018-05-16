#ifndef RAXML_COMMON_H_
#define RAXML_COMMON_H_

#include <unistd.h>

#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>

extern "C" {
//#include <libpll/pll.h>
#include <libpll/pllmod_common.h>
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

/* used to supress compiler warnings about unused args */
#define RAXML_UNUSED(expr) PLLMOD_UNUSED(expr)

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
