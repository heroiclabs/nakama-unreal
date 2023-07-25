/*
 * Copyright 2023 The Nakama Authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "nakama-cpp/NUtils.h"
#include "nakama-cpp/NPlatformParams.h"
#include "nakama-cpp/ClientFactory.h"

#if defined NAKAMA_TEST_SHARED_LIBRARY && (defined _WIN32 || defined __CYGWIN__  || defined FORCE_DLL_IMPORT_EXPORT)
    #ifdef NAKAMA_TEST_SHARED_LIBRARY_EXPORTS
        #define NAKAMA_TEST_API __declspec(dllexport)
    #else
        #define NAKAMA_TEST_API __declspec(dllimport)
    #endif
#elif defined NAKAMA_TEST_SHARED_LIBRARY && __GNUC__ >= 4
    #ifdef NAKAMA_TEST_SHARED_LIBRARY_EXPORTS
        #define NAKAMA_TEST_API __attribute__((visibility("default")))
    #else
        #define NAKAMA_TEST_API
    #endif
#else
    #define NAKAMA_TEST_API
#endif



namespace Nakama {
namespace Test {

NAKAMA_TEST_API int runAllTests(std::function<NClientPtr(Nakama::NClientParameters)> clientFactory, std::function<NRtClientPtr(Nakama::NClientPtr client)> rtClientFactory, NClientParameters parameters, std::string serverHttpKey);

}
}