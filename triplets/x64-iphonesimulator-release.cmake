set(VCPKG_TARGET_ARCHITECTURE x64)
set(VCPKG_CRT_LINKAGE dynamic)

if (${PORT} MATCHES "nakama-sdk")
    set(VCPKG_LIBRARY_LINKAGE dynamic)
else()
    set(VCPKG_LIBRARY_LINKAGE static)
endif()

set(VCPKG_CMAKE_SYSTEM_NAME iOS)

# HeroicLabs additions to standard triplets:
set(VCPKG_BUILD_TYPE release)
set(VCPKG_OSX_DEPLOYMENT_TARGET "11")
set(VCPKG_OSX_ARCHITECTURES "x86_64")
set(VCPKG_OSX_SYSROOT iphonesimulator)

include(${CMAKE_CURRENT_LIST_DIR}/feature-visibility-hidden.cmake)
