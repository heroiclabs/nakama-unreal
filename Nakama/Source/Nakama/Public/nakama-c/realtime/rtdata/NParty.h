/*
 * Copyright 2021 The Nakama Authors
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

#ifdef __cplusplus
extern "C" {
#endif

/// A set of joins and leaves on a particular realtime match.
typedef struct NAKAMA_API NParty
{
    /// The unique party identifier.
    const char* id;

    /// True, if the party is open to join.
    bool open;

    /// The maximum number of party members.
    int maxSize;

    /// The current user in this party. i.e. Yourself.
    sNUserPresence self;

    /// The current party leader.
    sNUserPresence leader;

    /// All members currently in the party.
    sNUserPresence* presences;

    /// The number of members currently in the party.
    uint16_t presencesCount;
} sNParty;

#ifdef __cplusplus
}
#endif