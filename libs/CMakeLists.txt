message(STATUS "Building dependencies in: ${RAXML_LOCALDEPS_DIR}")

# build LIBPLL and LIBPLL-MODULES
if (USE_CORAXLIB_CMAKE)
  add_subdirectory(coraxlib)
  set(CORAXLIB_SRC "${CMAKE_CURRENT_SOURCE_DIR}/coraxlib/src")
endif()

#target_include_directories(raxml_module PRIVATE ${RAXML_LIBPLL_HEADERS})

#else()
#  add_custom_command(
#    OUTPUT ${RAXML_LOCALDEPS_DIR}/lib/libpll.a
#    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/pll-modules
#    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/pll-modules/install-with-libpll.sh ${RAXML_LOCALDEPS_DIR} '' ${PLLMOD_AUTOCONF_ARGS}
#  )

#  add_custom_target(libpll ALL
#    DEPENDS ${RAXML_LOCALDEPS_DIR}/lib/libpll.a
#  )
# endif()

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

  add_subdirectory(terraphast)
  set(TERRACES_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/terraphast/include PARENT_SCOPE)
endif()
