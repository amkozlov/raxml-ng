#include <cpuid.h>
#include <stdarg.h>
#include <limits.h>

#if defined __MINGW32__
#include <windows.h>
#include <psapi.h>
#include <stdint.h>
#include <stdlib.h>
typedef uint32_t u_int32_t;
#define posix_memalign(p, a, s) (((*(p)) = _aligned_malloc((s), (a))), *(p) ?0 :errno)
#else
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/sysinfo.h>
#endif

#include <chrono>

#include "common.h"

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

void libpll_check_error(const std::string& errmsg = "ERROR in libpll")
{
  if (pll_errno)
    throw runtime_error(errmsg +  " (LIBPLL-" + to_string(pll_errno) + "): " + string(pll_errmsg));
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
#if defined __MINGW32__ // WINDOWS build
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
#if defined __MINGW32__
  LARGE_INTEGER time, freq;

  QueryPerformanceCounter(&time);
  QueryPerformanceFrequency(&freq);

  fprintf(stderr,
          "Time: %.3fs (user)", 
          static_cast<double>(time.QuadPart) / freq.QuadPart);

  PROCESS_MEMORY_COUNTERS info;

  GetProcessMemoryInfo(GetCurrentProcess(), &info, sizeof(info));

  fprintf(stderr, " Memory: %.0fMB\n", (size_t)info.PeakWorkingSetSize * 1.0e-6);
#else
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
#endif
}

unsigned long sysutil_get_memused()
{
#if defined __MINGW32__
  PROCESS_MEMORY_COUNTERS info;

  GetProcessMemoryInfo(GetCurrentProcess(), &info, sizeof(info));

  return (unsigned long)(info.PeakWorkingSetSize);
#else
  struct rusage r_usage;
  getrusage(RUSAGE_SELF, & r_usage);

#if defined __APPLE__
  /* Mac: ru_maxrss gives the size in bytes */
  return (unsigned long)(r_usage.ru_maxrss);
#else
  /* Linux: ru_maxrss gives the size in kilobytes  */
  return (unsigned long)r_usage.ru_maxrss * 1024;
#endif
#endif
}

unsigned long sysutil_get_memtotal()
{
#if defined(_SC_PHYS_PAGES) && defined(_SC_PAGESIZE)

  long phys_pages = sysconf(_SC_PHYS_PAGES);
  long pagesize = sysconf(_SC_PAGESIZE);

  if ((phys_pages == -1) || (pagesize == -1))
    sysutil_fatal("Cannot determine amount of RAM");

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
    sysutil_fatal("Cannot determine amount of RAM");
  return ram;

#elif defined __MINGW32__

  MEMORYSTATUSEX memory_status;

  memory_status.dwLength = sizeof(MEMORYSTATUSEX);
  if (GlobalMemoryStatusEx(&memory_status))
    return memory_status.ullTotalPhys;
  else
    sysutil_fatal("Cannot determine amount of RAM");

#else

  struct sysinfo si;
  if (sysinfo(&si))
    sysutil_fatal("Cannot determine amount of RAM");
  return si.totalram * si.mem_unit;

#endif
}

static void get_cpuid(int32_t out[4], int32_t x)
{
  __cpuid_count(x, 0, out[0], out[1], out[2], out[3]);
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

std::string sysutil_realpath(const std::string& path)
{
#if defined __MINGW32__
  char * real_path = _fullpath(NULL, path.c_str(), PATH_MAX);
#else
  char * real_path = realpath(path.c_str(), NULL);
#endif
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
  return access(fname.c_str(), access_mode) == 0;
}

const SystemTimer& global_timer()
{
  return systimer;
}


