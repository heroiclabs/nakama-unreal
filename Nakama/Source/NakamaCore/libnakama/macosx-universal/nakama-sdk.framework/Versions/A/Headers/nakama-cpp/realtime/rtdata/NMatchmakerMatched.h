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

#include <nakama-cpp/realtime/rtdata/NUserPresence.h>
#include <nakama-cpp/NTypes.h>
#include <nakama-cpp/NExport.h>
#include <vector>
#include <memory>

NAKAMA_NAMESPACE_BEGIN

    struct NMatchmakerUser
    {
        NUserPresence presence;                  ///< User info.
        NStringMap stringProperties;             ///< String properties.
        NStringDoubleMap numericProperties;      ///< Numeric properties.
    };

    /// A successful matchmaking result.
    struct NMatchmakerMatched
    {
        std::string ticket;                  ///< The matchmaking ticket that has completed.
                                             ///< The match token or match ID to join.
        std::string matchId;                 ///< Match ID.
        std::string token;                   ///< Match join token.
        std::vector<NMatchmakerUser> users;  ///< The users that have been matched together, and information about their matchmaking data.
        NMatchmakerUser self;                ///< A reference to the current user and their properties.
    };

    using NMatchmakerMatchedPtr = std::shared_ptr<NMatchmakerMatched>;

NAKAMA_NAMESPACE_END
