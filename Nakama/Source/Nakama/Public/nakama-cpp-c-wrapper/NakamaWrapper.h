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

///
/// Nakama Wrapper is C++ wrapper to use Nakama C API from shared library (DLL)
///

#define NAKAMA_NAMESPACE        NakamaWrapper
#define NAKAMA_NAMESPACE_BEGIN  namespace NAKAMA_NAMESPACE {
#define NAKAMA_NAMESPACE_END    }
#undef NAKAMA_SHARED_LIBRARY

#include "nakama-cpp/ClientFactory.h"
#include "nakama-cpp/realtime/NRtDefaultClientListener.h"
#include "nakama-cpp/log/NLogger.h"
#include "nakama-cpp/NakamaVersion.h"
