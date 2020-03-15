#
# Copyright 2019 The Nakama Authors
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

'''
All platforms
'''
# Build REST (HTTP/1.1) client
BUILD_REST_CLIENT = True

# Build gRPC client
BUILD_GRPC_CLIENT = False

# Build HTTP transport using C++ REST SDK
BUILD_HTTP_CPPREST = True

# Build Websocket transport using C++ REST SDK
BUILD_WEBSOCKET_CPPREST = True

# Build C API (support for C language)
BUILD_C_API = True

# Build static libs
BUILD_NAKAMA_STATIC = False

# Build shared libs (DLL)
BUILD_NAKAMA_SHARED = True

# Build tests
BUILD_NAKAMA_TESTS = False

'''
iOS
'''
IOS_UNIVERSAL_SHARED_LIB = True
IOS_RPATH_ENABLE = True

'''
Mac
'''
MAC_RPATH_ENABLE = True
