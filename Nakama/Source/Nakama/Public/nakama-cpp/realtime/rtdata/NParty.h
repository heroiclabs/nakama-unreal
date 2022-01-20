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

#include <vector>
#include "nakama-cpp/NTypes.h"
#include "nakama-cpp/realtime/rtdata/NUserPresence.h"

NAKAMA_NAMESPACE_BEGIN

    /// Information about a party.
    struct NAKAMA_API NParty
    {
        std::string id; /// The unique party identifier.

        bool open; /// True, if the party is open to join.

        int maxSize; /// The maximum number of party members.

        NUserPresence self;  /// The current user in this party. i.e. Yourself.

        NUserPresence leader; /// The current party leader.

        std::vector<NUserPresence> presences; /// All members currently in the party.
    };

NAKAMA_NAMESPACE_END