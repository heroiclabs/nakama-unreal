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

#include <nakama-cpp/config.h>
#include <nakama-cpp/NExport.h>
#include <nonstd/optional.hpp>
#include <cstdint>
#include <string>
#include <vector>
#include <map>

#ifndef NAKAMA_NAMESPACE
    #define NAKAMA_NAMESPACE        Nakama
    #define NAKAMA_NAMESPACE_BEGIN  namespace NAKAMA_NAMESPACE {
    #define NAKAMA_NAMESPACE_END    }
#endif

NAKAMA_NAMESPACE_BEGIN

    /// The group role status.
    enum class NUserGroupState
    {
        SUPERADMIN       = 0,   ///< The user is a superadmin with full control of the group.
        ADMIN            = 1,   ///< The user is an admin with additional privileges.
        MEMBER           = 2,   ///< The user is a regular member.
        JOIN_REQUEST     = 3    ///< The user has requested to join the group
    };

    /// The available channel types on the server.
    enum class NChannelType
    {
        TYPE_UNSPECIFIED = 0,   ///< Default case. Assumed as ROOM type.
        ROOM             = 1,   ///< A chat room which can be created dynamically with a name.
        DIRECT_MESSAGE   = 2,   ///< A private chat between two users.
        GROUP            = 3    ///< A chat within a group on the server.
    };

    /// UNIX time in milliseconds.
    /// Use getUnixTimestampMs() to get current time.
    using NTimestamp = uint64_t;

    /// array of bytes
    using NBytes = std::string;

    using NStringMap = std::map<std::string, std::string>;
    using NStringDoubleMap = std::map<std::string, double>;
    namespace opt = nonstd;

    /// Constant for defaut port.
    /// This is not valid port, actual port will be selected automatically.
    static const int32_t DEFAULT_PORT = -1;

NAKAMA_NAMESPACE_END
