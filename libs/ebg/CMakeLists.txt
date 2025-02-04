# to prevent numerical stability issues with GCC 12+
add_compile_options(-O1)

file(GLOB EBG_SOURCE_FILES ebg.c median_light/prediction.c median_light/tu*.c)

add_library(
        ebg
        STATIC
        ${EBG_SOURCE_FILES}
)

target_include_directories(
  ebg PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)


# Alternative solution to deal with symbol name conflicts 
# from multiple LightGBM models: use objcopy to add prefix

#find_program(CMAKE_OBJCOPY objcopy)

# Define the output file name for objcopy
#set(OBJCOPY_OUTPUT ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/libebg.a)

# Add a custom command to run objcopy on the static library
#add_custom_command(
#    TARGET ebg POST_BUILD
#    COMMAND ${CMAKE_OBJCOPY} --prefix-symbols=ebg_ $<TARGET_FILE:ebg>
#)

