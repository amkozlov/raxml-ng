file(GLOB RAXML_SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp 
                        ${PROJECT_SOURCE_DIR}/src/io/*.cpp
                        ${PROJECT_SOURCE_DIR}/src/bootstrap/*.cpp
                        ${PROJECT_SOURCE_DIR}/src/autotune/*.cpp
                        ${PROJECT_SOURCE_DIR}/src/loadbalance/*.cpp
                        )

if(USE_TERRAPHAST)
  file (GLOB TERRACE_SOURCES ${PROJECT_SOURCE_DIR}/src/terraces/*.cpp)

  set(RAXML_SOURCES ${RAXML_SOURCES} ${TERRACE_SOURCES})
endif()

# export to the parent dir to use in GTest makefile
set(RAXML_SOURCES ${RAXML_SOURCES} PARENT_SCOPE)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# enable static linking
if(STATIC_BUILD)
  set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
  set(BUILD_SHARED_LIBRARIES OFF)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

  if(ENABLE_PTHREADS)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--whole-archive -lpthread -Wl,--no-whole-archive")
  endif()
endif()

if (BUILD_AS_LIBRARY)
  message(STATUS "RAxML-NG will be built as a library.")
  add_library(raxml_module MODULE ${RAXML_SOURCES})
else()
  add_executable(raxml_module ${RAXML_SOURCES})
endif()


if (USE_LIBPLL_CMAKE)
  target_include_directories(raxml_module PRIVATE ${PLLMOD_EXPORTED_INCLUDE_PATH})
  set(LIBPLL_LIBS  ${PLLMODULES_LIBRARIES} ${PLL_LIBRARIES})
else()
  set(LIBPLL_LIBS ${RAXML_LOCALDEPS_DIR}/lib/libpll_algorithm.a
                  ${RAXML_LOCALDEPS_DIR}/lib/libpll_binary.a
                  ${RAXML_LOCALDEPS_DIR}/lib/libpll_optimize.a
                  ${RAXML_LOCALDEPS_DIR}/lib/libpll_msa.a
                  ${RAXML_LOCALDEPS_DIR}/lib/libpll_tree.a
                  ${RAXML_LOCALDEPS_DIR}/lib/libpll_util.a
                  ${RAXML_LOCALDEPS_DIR}/lib/libpll.a
                  )
endif()


set(RAXML_LIBS ${LIBPLL_LIBS} m)

if(USE_TERRAPHAST)
  set(RAXML_LIBS ${RAXML_LOCALDEPS_DIR}/lib/libterraces.a ${RAXML_LIBS})
endif()

# export to the parent dir to use in GTest makefile
set(RAXML_LIBS ${RAXML_LIBS} PARENT_SCOPE)

#message(STATUS "Libs: ${RAXML_LIBS}")

target_link_libraries(raxml_module ${RAXML_LIBS})

if (BUILD_AS_LIBRARY AND NOT APPLE)
  target_link_libraries(raxml_module gcc_s gcc)
endif()

if(GMP_FOUND)
  target_link_libraries(raxml_module ${GMP_LIBRARIES})
endif()

if(MPI_FOUND)
  target_link_libraries(raxml_module ${MPI_CXX_LIBRARIES})
endif()

if(MPI_COMPILE_FLAGS)
  set_target_properties(raxml_module PROPERTIES
                          COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")
endif()

if(MPI_LINK_FLAGS)
  set_target_properties(raxml_module PROPERTIES
                          LINK_FLAGS "${MPI_LINK_FLAGS}")
endif()

if(MPI_FOUND)
  set_target_properties(raxml_module PROPERTIES OUTPUT_NAME raxml-ng-mpi)
elseif(STATIC_BUILD)
  set_target_properties(raxml_module PROPERTIES OUTPUT_NAME raxml-ng-static)
else()
  set_target_properties(raxml_module PROPERTIES OUTPUT_NAME raxml-ng)
endif()

set_target_properties(raxml_module PROPERTIES PREFIX "")
