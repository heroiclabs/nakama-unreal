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

#include "nakama-cpp/NExport.h"
#include "nonstd/optional.hpp"
#include <cstdint>
#include <string>
#include <vector>
#include <map>

namespace Nakama {

    /// The group role status.
    enum class NAKAMA_API NUserGroupState
    {
        SUPERADMIN       = 0,   ///< The user is a superadmin with full control of the group.
        ADMIN            = 1,   ///< The user is an admin with additional privileges.
        MEMBER           = 2,   ///< The user is a regular member.
        JOIN_REQUEST     = 3    ///< The user has requested to join the group
    };

    /// The available channel types on the server.
    enum class NAKAMA_API NChannelType
    {
        ROOM             = 0,   ///< A chat room which can be created dynamically with a name.
        DIRECT_MESSAGE   = 1,   ///< A private chat between two users.
        GROUP            = 2    ///< A chat within a group on the server.
    };

    /// UNIX time in milliseconds.
    /// Use getUnixTimestampMs() to get current time.
    using NTimestamp = uint64_t;

    /// array of bytes
    using NBytes = std::string;

    using NStringMap = std::map<std::string, std::string>;
    using NStringDoubleMap = std::map<std::string, double>;
    namespace opt = nonstd;

}
