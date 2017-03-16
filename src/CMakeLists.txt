file (GLOB_RECURSE raxml_sources ${PROJECT_SOURCE_DIR}/src/*.cpp)

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# enable static linking
if (STATIC_BUILD)
  SET(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
  SET(BUILD_SHARED_LIBRARIES OFF)
  SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

  if(ENABLE_PTHREADS)
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--whole-archive -lpthread -Wl,--no-whole-archive")
  endif()
endif()

add_executable        (raxml_module ${raxml_sources})

target_link_libraries (raxml_module ${RAXML_LOCALDEPS_DIR}/lib/libpll_algorithm.a)
target_link_libraries (raxml_module ${RAXML_LOCALDEPS_DIR}/lib/libpll_binary.a)
target_link_libraries (raxml_module ${RAXML_LOCALDEPS_DIR}/lib/libpll_optimize.a)
target_link_libraries (raxml_module ${RAXML_LOCALDEPS_DIR}/lib/libpll_msa.a)
target_link_libraries (raxml_module ${RAXML_LOCALDEPS_DIR}/lib/libpll_tree.a)
target_link_libraries (raxml_module ${RAXML_LOCALDEPS_DIR}/lib/libpll_util.a)
target_link_libraries (raxml_module ${RAXML_LOCALDEPS_DIR}/lib/libpll.a)
target_link_libraries (raxml_module m)

if(MPI_FOUND)
target_link_libraries (raxml_module ${MPI_CXX_LIBRARIES})
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
  set_target_properties (raxml_module PROPERTIES OUTPUT_NAME raxml-ng-mpi)
else()
  set_target_properties (raxml_module PROPERTIES OUTPUT_NAME raxml-ng)
endif()

set_target_properties (raxml_module PROPERTIES PREFIX "")
