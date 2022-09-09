#----------------------------------------------------------------
# Generated CMake target import file for configuration "MinSizeRel".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "nakama-sdk" for configuration "MinSizeRel"
set_property(TARGET nakama-sdk APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(nakama-sdk PROPERTIES
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/macosx-x64/nakama-sdk.framework/Versions/A/nakama-sdk"
  IMPORTED_SONAME_MINSIZEREL "@rpath/nakama-sdk.framework/Versions/A/nakama-sdk"
  )

list(APPEND _IMPORT_CHECK_TARGETS nakama-sdk )
list(APPEND _IMPORT_CHECK_FILES_FOR_nakama-sdk "${_IMPORT_PREFIX}/macosx-x64/nakama-sdk.framework/Versions/A/nakama-sdk" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
