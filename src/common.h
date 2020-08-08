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
#include "util/SystemTimer.hpp"

/* used to suppress compiler warnings about unused args */
#define RAXML_UNUSED(expr) (void)(expr)

/* system utils */
void sysutil_fatal(const char * format, ...);
void sysutil_fatal_libpll();
void libpll_check_error(const std::string& errmsg = "ERROR in libpll", bool force = false);
void libpll_reset_error();

double sysutil_gettime();
void sysutil_show_rusage();
unsigned long sysutil_get_memused();
unsigned long sysutil_get_memtotal(bool ignore_errors = true);

std::string sysutil_get_cpu_model();
unsigned int sysutil_get_cpu_cores();
unsigned long sysutil_get_cpu_features();
unsigned int sysutil_simd_autodetect();

double sysutil_get_energy();

const SystemTimer& global_timer();
std::string sysutil_fmt_time(const time_t& t);

std::string sysutil_realpath(const std::string& path);
bool sysutil_file_exists(const std::string& fname, int access_mode = F_OK);
bool sysutil_dir_exists(const std::string& dname);
void sysutil_file_remove(const std::string& fname, bool must_exist = false);

bool sysutil_isnumber(const std::string& s);

/* parsing utils */
std::vector<std::string> split_string(const std::string& s, char delim);
bool isprefix(const std::string& s, const std::string& prefix);

#endif /* RAXML_COMMON_H_ */
