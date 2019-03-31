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

    /// A set of joins and leaves on a particular channel.
    struct NChannelPresenceEvent
    {
        std::string channelId;                   ///< The channel identifier this event is for.
        std::vector<NUserPresence> joins;        ///< Presences joining the channel as part of this event, if any.
        std::vector<NUserPresence> leaves;       ///< Presences leaving the channel as part of this event, if any.
    };
}
