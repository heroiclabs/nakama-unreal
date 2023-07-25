# see https://forums.unrealengine.com/t/compiling-libraries-in-linux/400275
# see https://forums.unrealengine.com/t/ue4-linux-use-libcxx-0-fails-to-compile/478297
# see https://forums.unrealengine.com/t/using-bundled-libc-in-thirdparty/427863

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_FLAGS "-nostdinc++ -nodefaultlibs -I$ENV{UNREAL_ENGINE}/Engine/Source/ThirdParty/Unix/LibCxx/include/ -I$ENV{UNREAL_ENGINE}/Engine/Source/ThirdParty/Unix/LibCxx/include/c++/v1 ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_STANDARD_LIBRARIES "-lpthread -lm -lc -lgcc_s -lgcc $ENV{UNREAL_ENGINE}/Engine/Source/ThirdParty/Unix/LibCxx/lib/Unix/x86_64-unknown-linux-gnu/libc++.a $ENV{UNREAL_ENGINE}/Engine/Source/ThirdParty/Unix/LibCxx/lib/Unix/x86_64-unknown-linux-gnu/libc++.a")
