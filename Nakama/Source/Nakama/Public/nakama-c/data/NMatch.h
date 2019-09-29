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
#include "nakama-c/realtime/rtdata/NUserPresence.h"

#ifdef __cplusplus
extern "C" {
#endif

/// Represents a realtime match.
typedef struct NAKAMA_API NMatch
{
    const char* matchId;                  ///< The ID of the match, can be used to join.
    bool authoritative;                   ///< True if it's an server-managed authoritative match, false otherwise.
    const char* label;                    ///< Match label, if any.
    int32_t size;                         ///< Current number of users in the match.
    sNUserPresence* presences;            ///< The users currently in the match.
    uint16_t presencesCount;              ///< The users currently in the match.
    sNUserPresence self;                  ///< A reference to the current user's presence in the match.
} sNMatch;

#ifdef __cplusplus
}
#endif
