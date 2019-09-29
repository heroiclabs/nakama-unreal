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

/// A user session associated to a stream, usually through a list operation or a join/leave event.
typedef struct NAKAMA_API NUserPresence
{
    const char* userId;             ///< The user this presence belongs to.
    const char* sessionId;          ///< A unique session ID identifying the particular connection, because the user may have many.
    const char* username;           ///< The username for display purposes.
    bool persistence;               ///< Whether this presence generates persistent data/messages, if applicable for the stream type.
    const char* status;             ///< A user-set status message for this stream, if applicable.
} sNUserPresence;

#ifdef __cplusplus
}
#endif

