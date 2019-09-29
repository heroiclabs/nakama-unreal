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

#include "nakama-c/realtime/rtdata/NUserPresence.h"
#include "nakama-c/NTypes.h"
#include "nakama-c/NStringDoubleMap.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct NAKAMA_API NMatchmakerUser
{
    sNUserPresence presence;                 ///< User info.
    NStringMap stringProperties;             ///< String properties.
    NStringDoubleMap numericProperties;      ///< Numeric properties.
} sNMatchmakerUser;

/// A successful matchmaking result.
typedef struct NAKAMA_API NMatchmakerMatched
{
    const char* ticket;                  ///< The matchmaking ticket that has completed.
                                         ///< The match token or match ID to join.
    const char* matchId;                 ///< Match ID.
    const char* token;                   ///< Match join token.
    sNMatchmakerUser* users;             ///< The users that have been matched together, and information about their matchmaking data.
    uint16_t usersCount;
    sNMatchmakerUser self;               ///< A reference to the current user and their properties.
} sNMatchmakerMatched;

#ifdef __cplusplus
}
#endif

