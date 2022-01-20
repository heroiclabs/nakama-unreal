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

#include <string>
#include <vector>
#include "nakama-cpp/NTypes.h"
#include "nakama-cpp/realtime/rtdata/NUserPresence.h"

NAKAMA_NAMESPACE_BEGIN

    /// Presence update for a particular party.
    struct NAKAMA_API NPartyPresenceEvent
    {
        /// The ID of the party.
        std::string partyId;

        /// The user presences that have just joined the party.
        std::vector<NUserPresence> joins;

        /// The user presences that have just left the party.
        std::vector<NUserPresence> leaves;
    };

NAKAMA_NAMESPACE_END