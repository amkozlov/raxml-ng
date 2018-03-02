
# build LIBPLL and LIBPLL-MODULES
add_subdirectory(pll-modules)

#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${RAXML_LOCALDEPS_DIR}/lib)

# build terraphast I
if(USE_TERRAPHAST)
  add_subdirectory(terraphast/terraphastI)
  set(TERRACES_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/terraphast/terraphastI/include PARENT_SCOPE)
  endif()
