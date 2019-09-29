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

/// Represents identifying information for a stream.
typedef struct NAKAMA_API NStream
{
    int32_t mode;                   ///< Mode identifies the type of stream.
    const char* subject;            ///< Subject is the primary identifier, if any.
    const char* subcontext;         ///< Subcontext is a secondary identifier, if any.
    const char* label;              ///< The label is an arbitrary identifying string, if the stream has one.
} sNStream;

#ifdef __cplusplus
}
#endif

