message(STATUS "Building dependencies in: ${RAXML_LOCALDEPS_DIR}")

# build CORAXLIB
if (USE_CORAXLIB_CMAKE)
  set(CORAX_BUILD_PORTABLE ${PORTABLE_BUILD} CACHE BOOL "" FORCE)

  add_subdirectory(coraxlib)
  set(CORAXLIB_SRC "${CMAKE_CURRENT_SOURCE_DIR}/coraxlib/src")
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${RAXML_LOCALDEPS_DIR}/lib)

# build terraphast-one
if(USE_TERRAPHAST)
  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/terraphast/cmake)

  set(TERRAPHAST_USE_GMP OFF CACHE BOOL "terraphast: Use GMP")
  set(TERRAPHAST_USE_THREADS OFF CACHE BOOL "terraphast: Use multi-threading")
  set(TERRAPHAST_BUILD_CLIB OFF CACHE BOOL "terraphast: Build the C library")
  set(TERRAPHAST_BUILD_APPS OFF CACHE BOOL "terraphast: Build the tools")
  set(TERRAPHAST_BUILD_TESTS OFF CACHE BOOL "terraphast: Build the tests")
  set(TERRAPHAST_ARCH_NATIVE OFF CACHE BOOL "terraphast: Use non-portable compiler optimizations")

  if(NOT PORTABLE_BUILD)
    set(TERRAPHAST_ARCH_NATIVE ON)
  endif()

  add_subdirectory(terraphast)
  set(TERRACES_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/terraphast/include PARENT_SCOPE)
endif()

if(USE_EBG)
  add_subdirectory(ebg)
endif()				
