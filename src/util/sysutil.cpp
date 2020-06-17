#ifndef _WIN32
#include <cpuid.h>
#endif
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/stat.h>
#if defined __APPLE__
#include <sys/sysctl.h>
#endif
#include <stdarg.h>
#include <limits.h>

#include <chrono>
#include <thread>

#include "../common.h"

using namespace std;

SystemTimer systimer;

void sysutil_fatal(const char * format, ...)
{
  va_list argptr;
  va_start(argptr, format);
  vfprintf(stderr, format, argptr);
  va_end(argptr);
  fprintf(stderr, "\n");
  exit(EXIT_FAILURE);
}

void sysutil_fatal_libpll()
{
  sysutil_fatal("ERROR(%d): %s\n", pll_errno, pll_errmsg);
}

void libpll_check_error(const std::string& errmsg, bool force)
{
  if (pll_errno)
    throw runtime_error(errmsg +  " (LIBPLL-" + to_string(pll_errno) + "): " + string(pll_errmsg));
  else if (force)
    throw runtime_error("Unknown LIBPLL error.");
}

void libpll_reset_error()
{
  pll_errno = 0;
  strcpy(pll_errmsg, "");
}

void * xmemalign(size_t size, size_t alignment)
{
  void * t = NULL;
  int err = posix_memalign(& t, alignment, size);

  if (err || !t)
    sysutil_fatal("Unable to allocate enough memory.");

  return t;
}

double sysutil_gettime()
{
#ifdef WIN32 // WINDOWS build
        FILETIME tm;
        ULONGLONG t;
#if defined(NTDDI_WIN8) && NTDDI_VERSION >= NTDDI_WIN8 // >= WIN8
        GetSystemTimePreciseAsFileTime( &tm );
#else // < WIN8
        GetSystemTimeAsFileTime( &tm );
#endif
        t = ((ULONGLONG)tm.dwHighDateTime << 32) | (ULONGLONG)tm.dwLowDateTime;
        return (double)t / 10000000.0;
#else // Unixoid build
  struct timeval ttime;
  gettimeofday(&ttime , NULL);
  return ttime.tv_sec + ttime.tv_usec * 0.000001;
#endif
}

void sysutil_show_rusage()
{
  struct rusage r_usage;
  getrusage(RUSAGE_SELF, & r_usage);
  
  fprintf(stderr,
          "Time: %.3fs (user)", 
          r_usage.ru_utime.tv_sec * 1.0 + (double)r_usage.ru_utime.tv_usec * 1.0e-6);
  fprintf(stderr,
          " %.3fs (sys)",
          r_usage.ru_stime.tv_sec * 1.0 + r_usage.ru_stime.tv_usec * 1.0e-6);

#if defined __APPLE__
  /* Mac: ru_maxrss gives the size in bytes */
  fprintf(stderr, " Memory: %.0fMB\n", r_usage.ru_maxrss * 1.0e-6);
#else
  /* Linux: ru_maxrss gives the size in kilobytes  */
  fprintf(stderr, " Memory: %.0fMB\n", r_usage.ru_maxrss * 1.0e-3);
#endif
}

unsigned long sysutil_get_memused()
{
  struct rusage r_usage;
  getrusage(RUSAGE_SELF, & r_usage);

#if defined __APPLE__
  /* Mac: ru_maxrss gives the size in bytes */
  return (unsigned long)(r_usage.ru_maxrss);
#else
  /* Linux: ru_maxrss gives the size in kilobytes  */
  return (unsigned long)r_usage.ru_maxrss * 1024;
#endif
}

unsigned long sysutil_get_memtotal(bool ignore_errors)
{
#if defined(_SC_PHYS_PAGES) && defined(_SC_PAGESIZE)

  long phys_pages = sysconf(_SC_PHYS_PAGES);
  long pagesize = sysconf(_SC_PAGESIZE);

  if ((phys_pages == -1) || (pagesize == -1))
  {
    if (ignore_errors)
      return 0;
    else
      throw runtime_error("Cannot determine amount of RAM");
  }

  // sysconf(3) notes that pagesize * phys_pages can overflow, such as
  // when long is 32-bits and there's more than 4GB RAM.  Since vsearch
  // apparently targets LP64 systems like x86_64 linux, this will not
  // arise in practice on the intended platform.

  if (pagesize > LONG_MAX / phys_pages)
    return LONG_MAX;
  else
    return (unsigned long)pagesize * (unsigned long)phys_pages;

#elif defined(__APPLE__)

  int mib [] = { CTL_HW, HW_MEMSIZE };
  int64_t ram = 0;
  size_t length = sizeof(ram);
  if(-1 == sysctl(mib, 2, &ram, &length, NULL, 0))
  {
    if (ignore_errors)
      return 0;
    else
      throw runtime_error("Cannot determine amount of RAM");
  }
  return ram;

#else

  struct sysinfo si;
  if (sysinfo(&si))
  {
    if (ignore_errors)
      return 0;
    else
      throw runtime_error("Cannot determine amount of RAM");
  }
  return si.totalram * si.mem_unit;

#endif
}

static void get_cpuid(int32_t out[4], int32_t x)
{
#ifdef _WIN32
  __cpuid(out, x);
#else
  __cpuid_count(x, 0, out[0], out[1], out[2], out[3]);
#endif
}

size_t read_id_from_file(const std::string &filename)
{
  ifstream f(filename);
  if (f.good())
  {
    size_t id;
    f >> id;
    return id;
  }
  else
    throw runtime_error("couldn't open sys files");
}

size_t get_numa_node_id(const std::string &cpu_path)
{
  // this is ugly, but should be reliable -> please blame Linux kernel developers & Intel!
  string node_path = cpu_path + "../node";
  for (size_t i = 0; i < 1000; ++i)
  {
    if (sysutil_dir_exists(node_path + to_string(i)))
      return i;
  }

  // fallback solution: return socket_id which is often identical to numa id
  return read_id_from_file(cpu_path + "physical_package_id");
}

size_t get_core_id(const std::string &cpu_path)
{
  return read_id_from_file(cpu_path + "core_id");
}

int get_physical_core_count(size_t n_cpu)
{
#if defined(__linux__)
  unordered_set<size_t> cores;
  for (size_t i = 0; i < n_cpu; ++i)
  {
    string cpu_path = "/sys/devices/system/cpu/cpu" + to_string(i) + "/topology/";
    size_t core_id = get_core_id(cpu_path);
    size_t node_id = get_numa_node_id(cpu_path);
    size_t uniq_core_id = (node_id << 16) + core_id;
    cores.insert(uniq_core_id);
  }
  return cores.size();
#else
  RAXML_UNUSED(n_cpu);
  throw std::runtime_error("This function only supports linux");
#endif
}

static bool ht_enabled()
{
  int32_t info[4];

  get_cpuid(info, 1);

  return (bool) (info[3] & (0x1 << 28));
}

unsigned int sysutil_get_cpu_cores()
{
  auto lcores = std::thread::hardware_concurrency();
  try
  {
    return get_physical_core_count(lcores);
  }
  catch (const std::runtime_error&)
  {
    auto threads_per_core = ht_enabled() ? 2 : 1;

    return lcores / threads_per_core;
  }
}

unsigned long sysutil_get_cpu_features()
{
  unsigned long features = 0;

  // adapted from: https://github.com/Mysticial/FeatureDetector

  //  OS Features
//  OS_x64 = detect_OS_x64();
//  OS_AVX = detect_OS_AVX();
//  OS_AVX512 = detect_OS_AVX512();

  int info[4];
  get_cpuid(info, 0);
  int nIds = info[0];

  get_cpuid(info, 0x80000000);
  u_int32_t nExIds = info[0];

  //  Detect Features
  if (nIds >= 0x00000001)
  {
    get_cpuid(info, 0x00000001);

//      HW_MMX    = (info[3] & ((int)1 << 23)) != 0;
//      HW_SSE    = (info[3] & ((int)1 << 25)) != 0;
//      HW_SSE2   = (info[3] & ((int)1 << 26)) != 0;

    if (info[2] & ((int)1 <<  0))
      features |= RAXML_CPU_SSE3;

//      HW_SSSE3  = (info[2] & ((int)1 <<  9)) != 0;
//      HW_SSE41  = (info[2] & ((int)1 << 19)) != 0;
//      HW_SSE42  = (info[2] & ((int)1 << 20)) != 0;
//      HW_AES    = (info[2] & ((int)1 << 25)) != 0;

    if (info[2] & ((int)1 << 28))
      features |= RAXML_CPU_AVX;

    if (info[2] & ((int)1 << 12))
      features |= RAXML_CPU_FMA3;

//      HW_RDRAND = (info[2] & ((int)1 << 30)) != 0;
  }

  if (nIds >= 0x00000007)
  {
    get_cpuid(info, 0x00000007);

    if (info[1] & ((int)1 << 5))
      features |= RAXML_CPU_AVX2;

//      HW_BMI1         = (info[1] & ((int)1 <<  3)) != 0;
//      HW_BMI2         = (info[1] & ((int)1 <<  8)) != 0;
//      HW_ADX          = (info[1] & ((int)1 << 19)) != 0;
//      HW_MPX          = (info[1] & ((int)1 << 14)) != 0;
//      HW_SHA          = (info[1] & ((int)1 << 29)) != 0;
//      HW_PREFETCHWT1  = (info[2] & ((int)1 <<  0)) != 0;
//
//      HW_AVX512_F     = (info[1] & ((int)1 << 16)) != 0;
//      HW_AVX512_CD    = (info[1] & ((int)1 << 28)) != 0;
//      HW_AVX512_PF    = (info[1] & ((int)1 << 26)) != 0;
//      HW_AVX512_ER    = (info[1] & ((int)1 << 27)) != 0;
//      HW_AVX512_VL    = (info[1] & ((int)1 << 31)) != 0;
//      HW_AVX512_BW    = (info[1] & ((int)1 << 30)) != 0;
//      HW_AVX512_DQ    = (info[1] & ((int)1 << 17)) != 0;
//      HW_AVX512_IFMA  = (info[1] & ((int)1 << 21)) != 0;
//      HW_AVX512_VBMI  = (info[2] & ((int)1 <<  1)) != 0;
  }

  if (nExIds >= 0x80000001)
  {
    get_cpuid(info, 0x80000001);
//      HW_x64   = (info[3] & ((int)1 << 29)) != 0;
//      HW_ABM   = (info[2] & ((int)1 <<  5)) != 0;
//      HW_SSE4a = (info[2] & ((int)1 <<  6)) != 0;
//      HW_FMA4  = (info[2] & ((int)1 << 16)) != 0;
//      HW_XOP   = (info[2] & ((int)1 << 11)) != 0;
  }

  return features;
}

unsigned int sysutil_simd_autodetect()
{
//  unsigned long features = sysutil_get_cpu_features();
  if (PLL_STAT(avx2_present))
    return PLL_ATTRIB_ARCH_AVX2;
  else if (PLL_STAT(avx_present))
    return PLL_ATTRIB_ARCH_AVX;
  else if (PLL_STAT(sse3_present))
    return PLL_ATTRIB_ARCH_SSE;
  else
    return PLL_ATTRIB_ARCH_CPU;
}

#if defined(__linux__)
static string get_cpuinfo_linux(const string& key)
{
  string value = "(not found)";
  ifstream fs("/proc/cpuinfo");
  if (fs.good())
  {
    string line;
    while (!fs.eof())
    {
      std::getline(fs, line, '\n');
      if (strncmp(line.c_str(), key.c_str(), key.length()) == 0)
      {
        size_t offset = key.length();
        while ((isspace(line[offset]) || line[offset] == ':') && offset < line.length())
          offset++;
        value = line.c_str() + offset;
        break;
      }
    }
  }

  return value;
}
#endif

string sysutil_get_cpu_model()
{
  string model = "unknown CPU";
#if defined(__linux__)
  model = get_cpuinfo_linux("model name");
#elif defined(__APPLE__)
  char str[256];
  size_t len = 256;
  if (sysctlbyname("machdep.cpu.brand_string", &str, &len, NULL, 0) == 0)
    model = str;
#endif
  return model;
}

double sysutil_get_energy()
{
  double energy = 0;
  size_t max_packages = 32;
  try
  {
    for(size_t i = 0; i < max_packages; i++)
    {
      double pkg_energy;
      auto fname = "/sys/class/powercap/intel-rapl/intel-rapl:" + to_string(i) + "/energy_uj";
      if (!sysutil_file_exists(fname))
        break;
      ifstream fs(fname);
      fs >> pkg_energy;
      energy += pkg_energy;
    }
    energy /= 1e6; // convert to Joules
    energy /= 3600; // convert to Wh
    return energy;
  }
  catch(const std::runtime_error& e)
  {
    printf("Error getting energy: %s\n", e.what());
    return 0;
  }
}


std::string sysutil_realpath(const std::string& path)
{
  char * real_path = realpath(path.c_str(), NULL);
  if (real_path)
  {
    const string result(real_path);
    free(real_path);
    return result;
  }
  else
  {
    switch(errno)
    {
      case EACCES:
        throw ios_base::failure("Can't access file: " + path);
        break;
      case ENOENT:
        throw ios_base::failure("File doesn't exist: " + path);
        break;
      case ELOOP:
      case ENAMETOOLONG:
        throw ios_base::failure("Path too long or too many symlinks: " + path);
        break;
      default:
        throw ios_base::failure("Unknown I/O error: " + path);
    }
  }
}

bool sysutil_file_exists(const std::string& fname, int access_mode)
{
  return !sysutil_dir_exists(fname) && access(fname.c_str(), access_mode) == 0;
}

bool sysutil_dir_exists(const std::string& dname)
{
  struct stat info;

  if( stat( dname.c_str(), &info ) != 0 )
    return false;
  else if( info.st_mode & S_IFDIR )
    return true;
  else
    return false;
}

void sysutil_file_remove(const std::string& fname, bool must_exist)
{
  if (sysutil_file_exists(fname))
    std::remove(fname.c_str());
  else if (must_exist)
    throw runtime_error("File does not exist: " + fname);
}


const SystemTimer& global_timer()
{
  return systimer;
}

string sysutil_fmt_time(const time_t& t)
{
  std::array<char, 128> buffer;
  const auto timeinfo = std::localtime(&t);
  strftime(buffer.data(), sizeof(buffer), "%d-%b-%Y %H:%M:%S", timeinfo);
  return buffer.data();
}

bool sysutil_isnumber(const std::string& str)
{
  if (str.empty())
    return false;
  else
  {
    const char* s = str.c_str();
    while (*s)
      if (!isdigit(*s++)) return false;

    return true;
  }
}

