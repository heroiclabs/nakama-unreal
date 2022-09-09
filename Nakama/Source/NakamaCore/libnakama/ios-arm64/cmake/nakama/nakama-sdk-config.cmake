
####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was nakama-sdk-config.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

####################################################################################

####################################################################################

# we could not install optional-lite because it's a third-party dependency
# so we need to tell the config file how to find it:
include(CMakeFindDependencyMacro)
set(optional-lite_DIR ${CMAKE_CURRENT_LIST_DIR})
find_dependency(optional-lite REQUIRED CONFIG)

get_filename_component(_OPTIONAL_LITE_IMPORT_PREFIX "${CMAKE_CURRENT_LIST_FILE}" PATH)
get_filename_component(_OPTIONAL_LITE_IMPORT_PREFIX "${_OPTIONAL_LITE_IMPORT_PREFIX}" PATH)
get_filename_component(_OPTIONAL_LITE_IMPORT_PREFIX "${_OPTIONAL_LITE_IMPORT_PREFIX}" PATH)
get_filename_component(_OPTIONAL_LITE_IMPORT_PREFIX "${_OPTIONAL_LITE_IMPORT_PREFIX}" PATH)


if(_OPTIONAL_LITE_IMPORT_PREFIX STREQUAL "/")
  set(_OPTIONAL_LITE_IMPORT_PREFIX "")
endif()

set_target_properties(nonstd::optional-lite PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES ${_OPTIONAL_LITE_IMPORT_PREFIX}/ios-arm64/nakama-sdk.framework/Headers
)

include ( ${CMAKE_CURRENT_LIST_DIR}/nakama-export.cmake )
