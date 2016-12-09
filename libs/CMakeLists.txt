
message(STATUS "Building dependencies in: ${RAXML_LOCALDEPS_DIR}")

# build LIBPLL and LIBPLL-MODULES
add_custom_command(
    OUTPUT ${RAXML_LOCALDEPS_DIR}/lib/libpll.a
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/pll-modules
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/pll-modules/install-with-libpll.sh ${RAXML_LOCALDEPS_DIR}
)

add_custom_target(libpll ALL
    DEPENDS ${RAXML_LOCALDEPS_DIR}/lib/libpll.a
)
