

message(STATUS "Building dependencies in: ${RAXML_LOCALDEPS_DIR}")

# build LIBPLL and LIBPLL-MODULES
if (USE_LIBPLL_CMAKE)
  add_subdirectory(pll-modules)

  set(PLLMOD_SRC "${CMAKE_CURRENT_SOURCE_DIR}/pll-modules/src")
  set(LIBPLL_SRC "${CMAKE_CURRENT_SOURCE_DIR}/pll-modules/libs/libpll/src")

  file(COPY ${PLLMOD_SRC}/pllmod_common.h
            ${PLLMOD_SRC}/algorithm/pllmod_algorithm.h
            ${PLLMOD_SRC}/binary/pll_binary.h
            ${PLLMOD_SRC}/msa/pll_msa.h
            ${PLLMOD_SRC}/optimize/pll_optimize.h
            ${PLLMOD_SRC}/tree/pll_tree.h
            ${PLLMOD_SRC}/util/pllmod_util.h
            ${LIBPLL_SRC}/pll.h
            DESTINATION ${RAXML_LOCALDEPS_DIR}/include/libpll)

#target_include_directories(raxml_module PRIVATE ${RAXML_LIBPLL_HEADERS})

else()
  add_custom_command(
    OUTPUT ${RAXML_LOCALDEPS_DIR}/lib/libpll.a
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/pll-modules
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/pll-modules/install-with-libpll.sh ${RAXML_LOCALDEPS_DIR} '' ${PLLMOD_AUTOCONF_ARGS}
  )

  add_custom_target(libpll ALL
    DEPENDS ${RAXML_LOCALDEPS_DIR}/lib/libpll.a
  )
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${RAXML_LOCALDEPS_DIR}/lib)

# build terraphast I
if(USE_TERRAPHAST)
  add_subdirectory(terraphast/terraphastI)
  set(TERRACES_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/terraphast/terraphastI/include PARENT_SCOPE)
endif()
