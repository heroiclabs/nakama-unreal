/*
 * Copyright 2019 The Nakama Authors
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

#ifdef NAKAMA_SHARED_LIBRARY

#if defined _WIN32 || defined __CYGWIN__
    #ifdef NAKAMA_SHARED_LIBRARY_EXPORTS
        #define NAKAMA_API __declspec(dllexport)
    #else
        #define NAKAMA_API __declspec(dllimport)
    #endif
#elif __GNUC__ >= 4
    #ifdef NAKAMA_SHARED_LIBRARY_EXPORTS
        #define NAKAMA_API __attribute__((visibility("default")))
    #else
        #define NAKAMA_API
    #endif
#else
    #error "Not supported compiler"
#endif

#else
    #define NAKAMA_API
#endif

#define EXPORT_VECTOR(T)
