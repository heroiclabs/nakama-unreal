# see https://forums.unrealengine.com/t/compiling-libraries-in-linux/400275
# see https://forums.unrealengine.com/t/ue4-linux-use-libcxx-0-fails-to-compile/478297
# see https://forums.unrealengine.com/t/using-bundled-libc-in-thirdparty/427863

set(VCPKG_TARGET_ARCHITECTURE x64)
set(VCPKG_CRT_LINKAGE dynamic)

if (${PORT} MATCHES "nakama-")
    set(VCPKG_LIBRARY_LINKAGE dynamic)
else()
    set(VCPKG_LIBRARY_LINKAGE static)
endif()

set(VCPKG_CMAKE_SYSTEM_NAME Linux)
set(VCPKG_BUILD_TYPE release)
