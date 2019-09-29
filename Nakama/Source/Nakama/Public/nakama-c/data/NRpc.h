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

#include "nakama-c/NTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/// Execute an Lua function on the server.
typedef struct NAKAMA_API NRpc
{
    const char* id;            ///< The identifier of the function.
    const char* payload;       ///< The payload of the function which must be a JSON object.
    const char* httpKey;       ///< The authentication key used when executed as a non-client HTTP request.
} sNRpc;

#ifdef __cplusplus
}
#endif
