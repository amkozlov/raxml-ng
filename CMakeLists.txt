cmake_minimum_required (VERSION 3.0.2 FATAL_ERROR)

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES  ON)

set(RAXML_BINARY_NAME "raxml-ng-2" CACHE STRING "Custom RAxML-NG binary name")
set(USE_CORAXLIB_CMAKE ON CACHE BOOL "Use CMake to build Coraxlib")
set(BUILD_AS_LIBRARY OFF CACHE BOOL "Build RAxML-NG as shared library (instead of stand-alone executable)")
set(PLLMOD_DEBUG OFF CACHE BOOL "Debug pll-modules (tons of console output!)")

set (USE_PTHREADS ON CACHE BOOL "Enable multi-threading support (PTHREADS)")
set (USE_MPI OFF CACHE BOOL "Enable MPI support")
set (USE_VCF OFF)

# build a static binary
set(STATIC_BUILD OFF CACHE BOOL "Build static binary")
set(PORTABLE_BUILD OFF CACHE BOOL "Build a portable RAxML-NG binary (slightly slower)")

set(USE_TERRAPHAST OFF CACHE BOOL "Use phylogentic terraces library (terraphast) ")
set(USE_GMP OFF CACHE BOOL "Use GNU Multiple precision (GMP) library ")

set(ENABLE_PTHREADS ${USE_PTHREADS})

if(USE_TERRAPHAST)
  set(GCC_MIN_VERSION "5.4")
  set(CLANG_MIN_VERSION "3.8")
  set(ENABLE_GMP ${USE_GMP})
else()
  set(GCC_MIN_VERSION "4.8")
  set(CLANG_MIN_VERSION "3.8")
  set(ENABLE_GMP OFF)
endif()

#set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_EXTENSIONS OFF)

# set these flags globally for all subprojects (libpll etc.)
set (CMAKE_CXX_FLAGS_DEBUG    "-O3 -g" CACHE INTERNAL "")
set (CMAKE_CXX_FLAGS_RELEASE  "-O3"    CACHE INTERNAL "")
set (CMAKE_C_FLAGS_DEBUG    "-O3 -g" CACHE INTERNAL "")
set (CMAKE_C_FLAGS_RELEASE  "-O3"    CACHE INTERNAL "")

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
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION} => ${CMAKE_CXX_COMPILER}")

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(RAXML_COMPILER_TARGET_VERSION ${GCC_MIN_VERSION})
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  set(RAXML_COMPILER_TARGET_VERSION ${CLANG_MIN_VERSION})
endif()


if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS RAXML_COMPILER_TARGET_VERSION)
  message (FATAL_ERROR "${CMAKE_CXX_COMPILER_ID} compiler too old! Minimum required: ${RAXML_COMPILER_TARGET_VERSION}")
endif()


set (raxml-ng_VERSION_MAJOR 2)
set (raxml-ng_VERSION_MINOR 0)

#set (CMAKE_BUILD_TYPE DEBUG)
#set (CMAKE_BUILD_TYPE RELEASE)
# set (CMAKE_VERBOSE_MAKEFILE ON)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "RELEASE")
endif()

message (STATUS "Building ${CMAKE_BUILD_TYPE}")

set (WARN_FLAGS               "-Wall -Wextra")
set (CMAKE_CXX_FLAGS          "-std=c++11 ${WARN_FLAGS}")

if (ENABLE_GMP)
#find_package(GMP REQUIRED)
  set(GMP_FOUND ON)
  set(GMP_LIBRARIES gmpxx gmp)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_RAXML_GMP")
endif()

if(ENABLE_PTHREADS)
  find_package(Threads REQUIRED)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_RAXML_PTHREADS -pthread")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_RAXML_PTHREADS -pthread")
endif()

if(BUILD_AS_LIBRARY)
  # building shared library only works with CMake!
  set(USE_CORAXLIB_CMAKE ON)

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_RAXML_BUILD_AS_LIB -fPIC")
endif()

if(USE_TERRAPHAST)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_RAXML_TERRAPHAST")
endif()

message(STATUS "Using flags: ${CMAKE_CXX_FLAGS}")

# build dependencies
set(RAXML_LOCALDEPS_DIR ${PROJECT_BINARY_DIR}/localdeps)
set(CORAX_BUILD_DIFFICULTY_PREDICTION ON CACHE BOOL "Build difficulty prediction module")
add_subdirectory(${PROJECT_SOURCE_DIR}/libs)
# set(CORAX_BUILD_DIFFICULTY_PREDICTION ON)


include_directories(${RAXML_LOCALDEPS_DIR}/include ${TERRACES_INCLUDE_DIR} ${PROJECT_SOURCE_DIR}/libs/coraxlib/src)

if(ENABLE_MPI)
  find_package(MPI)
  if(MPI_CXX_FOUND)
    # set( ENV{OMPI_CXX}            "clang++" PARENT_SCOPE )
    set(CMAKE_CXX_COMPILER "${MPI_CXX_COMPILER}")
    include_directories(${MPI_CXX_INCLUDE_PATH})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MPI_CXX_COMPILER_FLAGS} -D_RAXML_MPI -DOMPI_SKIP_MPICXX")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${MPI_CXX_LINK_FLAGS}")

    # disable static build for MPI
    set(STATIC_BUILD OFF)
  endif()
endif()

add_subdirectory(${PROJECT_SOURCE_DIR}/src)

enable_testing()
add_subdirectory(${PROJECT_SOURCE_DIR}/test/src)
