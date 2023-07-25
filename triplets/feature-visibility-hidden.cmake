# vcpkg dependencies are built statically and then linked into our shared lib.
# There is no way to reliably hide symbols from static lib dependencies in the shared lib.
# So instead of hiding symbols when linking, we build dependencies such that there is no public
# symbols in them in the first place.
# See following issues for context:
# - https://gitlab.kitware.com/cmake/cmake/-/issues/22177#note_983766
# - https://gitlab.kitware.com/cmake/cmake/-/issues/16977
string(APPEND VCPKG_C_FLAGS " -fvisibility=hidden -fvisibility-inlines-hidden")
string(APPEND VCPKG_CXX_FLAGS " -fvisibility=hidden -fvisibility-inlines-hidden")
