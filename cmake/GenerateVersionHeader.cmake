find_package(Git QUIET)

execute_process(
    COMMAND ${GIT_EXECUTABLE} rev-parse --short=12 HEAD
    WORKING_DIRECTORY ${SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_STRIP_TRAILING_WHITESPACE
    RESULT_VARIABLE GIT_COMMAND_RESULT
    ERROR_VARIABLE GIT_COMMAND_ERROR
)

if (${GIT_COMMAND_RESULT} EQUAL 0)

set(VERSION_H_CONTENT
"#pragma once
#define RAXML_COMMIT_HASH \"${GIT_COMMIT_HASH}\"
")

else()

set(VERSION_H_CONTENT "#pragma once")
message(DEBUG "Could not retrieve commit hash via git, version output will not contain commit (error: ${GIT_COMMAND_ERROR})")

endif()

file(MAKE_DIRECTORY ${BINARY_DIR}/generated)

# Only write if content changed, to avoid unnecessary recompiles
if(EXISTS ${BINARY_DIR}/generated/git_version.h)
    file(READ ${BINARY_DIR}/generated/git_version.h EXISTING_CONTENT)
else()
    set(EXISTING_CONTENT "")
endif()

if(NOT "${VERSION_H_CONTENT}" STREQUAL "${EXISTING_CONTENT}")
    file(WRITE ${BINARY_DIR}/generated/git_version.h "${VERSION_H_CONTENT}")
endif()
