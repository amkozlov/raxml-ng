find_package (GTest)

if(NOT GTEST_FOUND)
    message (STATUS "GTest not found")
    message (WARNING "Skipping building tests.")
    return()
endif()

message (STATUS "Building tests")

file (GLOB_RECURSE RAXML_TEST_SOURCES ${PROJECT_SOURCE_DIR}/test/src/*.cpp ${RAXML_SOURCES})

# sources list now has 2 Main.cpp, old has to be removed
list(REMOVE_ITEM RAXML_TEST_SOURCES "${PROJECT_SOURCE_DIR}/src/main.cpp")

include_directories (${PROJECT_SOURCE_DIR})
include_directories (${GTEST_INCLUDE_DIRS})

add_executable        (raxml_test_module ${RAXML_TEST_SOURCES})

target_link_libraries (raxml_test_module ${RAXML_LIBS})

if(GMP_FOUND)
  target_link_libraries(raxml_test_module ${GMP_LIBRARIES})
endif()

if(USE_TERRAPHAST)
  target_link_libraries(raxml_test_module ${RAXML_LOCALDEPS_DIR}/lib/libterraces.a)
  add_dependencies(raxml_test_module terraces)
endif()

target_link_libraries (raxml_test_module ${GTEST_BOTH_LIBRARIES} -pthread)

target_link_libraries (raxml_test_module ${MPI_CXX_LIBRARIES})

if(MPI_COMPILE_FLAGS)
  set_target_properties(raxml_test_module PROPERTIES
  COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")
endif()

if(MPI_LINK_FLAGS)
  set_target_properties(raxml_test_module PROPERTIES
    LINK_FLAGS "${MPI_LINK_FLAGS}")
endif()

set_target_properties (raxml_test_module PROPERTIES OUTPUT_NAME raxml_test)
set_target_properties (raxml_test_module PROPERTIES PREFIX "")

add_test (raxml_test raxml_test --gtest_output=xml:${CMAKE_BINARY_DIR}/test/RAxMLTest.xml)
