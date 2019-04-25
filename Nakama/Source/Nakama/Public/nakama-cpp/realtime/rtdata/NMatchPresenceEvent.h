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

#include "nakama-cpp/realtime/rtdata/NUserPresence.h"
#include <vector>

namespace Nakama {

    EXPORT_VECTOR(NUserPresence);

    /// A set of joins and leaves on a particular realtime match.
    struct NAKAMA_API NMatchPresenceEvent
    {
        std::string matchId;                 /// The match unique ID.
        std::vector<NUserPresence> joins;    /// User presences that have just joined the match.
        std::vector<NUserPresence> leaves;   /// User presences that have just left the match.
    };
}
