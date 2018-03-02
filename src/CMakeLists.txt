file(GLOB RAXML_SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp 
                        ${PROJECT_SOURCE_DIR}/src/io/*.cpp
                        ${PROJECT_SOURCE_DIR}/src/bootstrap/*.cpp
                        )
list(REMOVE_ITEM RAXML_SOURCES ${PROJECT_SOURCE_DIR}/src/main.cpp)

if(USE_TERRAPHAST)
  file (GLOB TERRACE_SOURCES ${PROJECT_SOURCE_DIR}/src/terraces/*.cpp)

  set(RAXML_SOURCES ${RAXML_SOURCES} ${TERRACE_SOURCES})
endif()

# export to the parent dir to use in GTest makefile
set(RAXML_SOURCES ${RAXML_SOURCES} PARENT_SCOPE)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# enable static linking
if(STATIC_BUILD)
  set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
  set(BUILD_SHARED_LIBRARIES OFF)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

  if(ENABLE_PTHREADS)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--whole-archive -lpthread -Wl,--no-whole-archive")
  endif()
endif()

set(RAXML_LIBPLL_HEADERS ${RAXML_LOCALDEPS_DIR}/include/libpll/)
set(PLLMOD_SRC "${PROJECT_SOURCE_DIR}/libs/pll-modules/src/")
set(LIBPLL_SRC "${PROJECT_SOURCE_DIR}/libs/pll-modules/libs/libpll/src/")

add_library(raxml_module MODULE ${RAXML_SOURCES})

#add_executable(raxml_module ${RAXML_SOURCES})

file(COPY ${PLLMOD_SRC}/pllmod_common.h
          ${PLLMOD_SRC}/algorithm/pllmod_algorithm.h
          ${PLLMOD_SRC}/binary/pll_binary.h
          ${PLLMOD_SRC}/msa/pll_msa.h
          ${PLLMOD_SRC}/optimize/pll_optimize.h
          ${PLLMOD_SRC}/tree/pll_tree.h
          ${PLLMOD_SRC}/util/pllmod_util.h
          ${LIBPLL_SRC}/pll.h
          DESTINATION ${RAXML_LIBPLL_HEADERS})
target_include_directories(raxml_module PRIVATE ${RAXML_LIBPLL_HEADERS})



set(RAXML_LIBS 
  pllmodalgorithm_static
  pllmodbinary_static
  pllmodmsa_static
  pllmodoptimize_static
  pllmodtree_static
  pllmodutil_static
  pll_static
               m
               )

if(USE_TERRAPHAST)
  set(RAXML_LIBS ${RAXML_LOCALDEPS_DIR}/lib/libterraces.a ${RAXML_LIBS})
endif()

# export to the parent dir to use in GTest makefile
set(RAXML_LIBS ${RAXML_LIBS} PARENT_SCOPE)

#message(STATUS "Libs: ${RAXML_LIBS}")

target_link_libraries(raxml_module  ${RAXML_LIBS} gcc_s gcc)

if(GMP_FOUND)
  target_link_libraries(raxml_module ${GMP_LIBRARIES})
endif()

if(MPI_FOUND)
  target_link_libraries(raxml_module ${MPI_CXX_LIBRARIES})
endif()

if(MPI_COMPILE_FLAGS)
  set_target_properties(raxml_module PROPERTIES
    COMPILE_FLAGS "${MPI_COMPILE_FLAGS} -fPIC")
endif()

if(MPI_LINK_FLAGS)
  set_target_properties(raxml_module PROPERTIES
    LINK_FLAGS "${MPI_LINK_FLAGS} -fPIC")
endif()

if(MPI_FOUND)
  set_target_properties(raxml_module PROPERTIES OUTPUT_NAME raxml-ng-mpi)
elseif(STATIC_BUILD)
  set_target_properties(raxml_module PROPERTIES OUTPUT_NAME raxml-ng-static)
else()
  set_target_properties(raxml_module PROPERTIES OUTPUT_NAME raxml-ng)
endif()

set_target_properties(raxml_module PROPERTIES PREFIX "")
