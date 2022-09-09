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

#include <nakama-cpp/NTypes.h>
#include <nakama-cpp/NExport.h>
#include <nakama-cpp/realtime/rtdata/NUserPresence.h>

NAKAMA_NAMESPACE_BEGIN

    /// Represents a realtime match.
    struct NMatch
    {
        std::string matchId;                     ///< The ID of the match, can be used to join.
        bool authoritative = false;              ///< True if it's an server-managed authoritative match, false otherwise.
        std::string label;                       ///< Match label, if any.
        int32_t size = 0;                        ///< Current number of users in the match.
        std::vector<NUserPresence> presences;    ///< The users currently in the match.
        NUserPresence self;                      ///< A reference to the current user's presence in the match.
    };

NAKAMA_NAMESPACE_END
