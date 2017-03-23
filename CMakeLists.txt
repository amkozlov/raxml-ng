cmake_minimum_required (VERSION 2.8.10 FATAL_ERROR)

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES  ON)

set (USE_PTHREADS ON CACHE BOOL "Enable multi-threading support (PTHREADS)")
set (USE_MPI ON CACHE BOOL "Enable MPI support")
set (USE_VCF OFF)

# leave this disabled to build a portable binary 
# (don't worry, libpll will still have full SIMD support!)
set (ENABLE_RAXML_SIMD OFF)

# build a portable static binary
set(STATIC_BUILD ON)

set(ENABLE_PTHREADS ${USE_PTHREADS})

project (raxml-ng C CXX)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  # no support for static linking on Mac
  set(STATIC_BUILD OFF)
  # MPI support on Macs seems to be tricky (and unnecessary)
  set(ENABLE_MPI OFF)
else()
  set(ENABLE_MPI ${USE_MPI})
endif()

#check for minimum compiler versions
message(STATUS "Compier: ${CMAKE_CXX_COMPILER_ID}")

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(RAXML_COMPILER_TARGET_VERSION "4.8")
  if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS RAXML_COMPILER_TARGET_VERSION)
    message (FATAL_ERROR "${CMAKE_CXX_COMPILER_ID} compiler too old! Minimum required: ${RAXML_COMPILER_TARGET_VERSION}")
  endif()
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  set(RAXML_COMPILER_TARGET_VERSION "3.8")
  if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS RAXML_COMPILER_TARGET_VERSION)
    message (FATAL_ERROR "${CMAKE_CXX_COMPILER_ID} compiler too old! Minimum required: ${RAXML_COMPILER_TARGET_VERSION}")
  endif()
endif()

set (raxml-ng_VERSION_MAJOR 0)
set (raxml-ng_VERSION_MINOR 1)

set (CMAKE_BUILD_TYPE DEBUG)
# set (CMAKE_BUILD_TYPE RELEASE)
# set (CMAKE_VERBOSE_MAKEFILE ON)

message (STATUS "Building ${CMAKE_BUILD_TYPE}")

set (WARN_FLAGS               "-Wall -Wextra")
set (CMAKE_CXX_FLAGS          "-std=c++11 ${WARN_FLAGS}")

set (CMAKE_CXX_FLAGS_DEBUG    "-g")
set (CMAKE_CXX_FLAGS_RELEASE  "-O3 -DNDEBUG")

if (ENABLE_RAXML_SIMD)
  include(CheckCXXCompilerFlag)
  CHECK_CXX_COMPILER_FLAG(-mavx HAS_AVX)
  CHECK_CXX_COMPILER_FLAG(-msse3 HAS_SSE3)
  if(HAS_AVX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx -D__AVX")
  elseif(HAS_SSE3)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse3 -D__SSE3")
  endif()
endif()

if(ENABLE_PTHREADS)
  find_package(Threads REQUIRED)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_RAXML_PTHREADS -pthread")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_RAXML_PTHREADS -pthread")
endif()

if(ENABLE_MPI)
  find_package(MPI)
  if(MPI_CXX_FOUND)
    # set( ENV{OMPI_CXX}            "clang++" PARENT_SCOPE )
    set(CMAKE_CXX_COMPILER "${MPI_CXX_COMPILER}")
    include_directories(${MPI_CXX_INCLUDE_PATH})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MPI_CXX_COMPILER_FLAGS} -D_RAXML_MPI")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${MPI_CXX_LINK_FLAGS}")

    # disable static build for MPI
    set(STATIC_BUILD OFF)
  endif()
endif()

message(STATUS "Using flags: ${CMAKE_CXX_FLAGS}")

#include_directories(${PROJECT_SOURCE_DIR}/libs/cereal/include)
#include_directories(${PROJECT_SOURCE_DIR}/libs/cxxopts/src)
#include_directories(${PROJECT_SOURCE_DIR}/libs/include/libpll)


set(pll_dir ${PROJECT_SOURCE_DIR}/libs/pll-modules/libs/libpll/src)
set(pll_binary_dir ${PROJECT_SOURCE_DIR}/libs/pll-modules/src/binary)
set(pll_optimize_dir ${PROJECT_SOURCE_DIR}/libs/pll-modules/src/optimize)
set(pll_msa_dir ${PROJECT_SOURCE_DIR}/libs/pll-modules/src/msa)

# build dependencies
set(RAXML_LOCALDEPS_DIR ${PROJECT_BINARY_DIR}/localdeps)
add_subdirectory(${PROJECT_SOURCE_DIR}/libs)

include_directories(${RAXML_LOCALDEPS_DIR}/include)

add_subdirectory(${PROJECT_SOURCE_DIR}/src)

enable_testing()
add_subdirectory(${PROJECT_SOURCE_DIR}/test/src)
