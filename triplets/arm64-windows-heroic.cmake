set(VCPKG_TARGET_ARCHITECTURE arm64)
set(VCPKG_CRT_LINKAGE dynamic)

if (${PORT} MATCHES "nakama-")
    set(VCPKG_LIBRARY_LINKAGE dynamic)
else()
    set(VCPKG_LIBRARY_LINKAGE static)
endif()

set(CMAKE_GENERATOR Visual Studio 17 2022)

string(APPEND VCPKG_C_FLAGS_RELEASE " /O1 /Ob2 /Gw /Gy")
string(APPEND VCPKG_CXX_FLAGS_RELEASE " /O1 /Ob2 /Gw /Gy")

list(APPEND VCPKG_KEEP_ENV_VARS "PATH" "Path" "VCPKG_ROOT")
set(VCPKG_ENV_PASSTHROUGH "PATH;Path;VCPKG_ROOT;")
