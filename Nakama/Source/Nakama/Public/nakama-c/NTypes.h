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
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/// The group role status.
typedef enum NAKAMA_API NUserGroupState
{
    NUserGroupState_SUPERADMIN       = 0,   ///< The user is a superadmin with full control of the group.
    NUserGroupState_ADMIN            = 1,   ///< The user is an admin with additional privileges.
    NUserGroupState_MEMBER           = 2,   ///< The user is a regular member.
    NUserGroupState_JOIN_REQUEST     = 3    ///< The user has requested to join the group
} eNUserGroupState;

/// The available channel types on the server.
typedef enum NAKAMA_API NChannelType
{
    NChannelType_ROOM             = 0,   ///< A chat room which can be created dynamically with a name.
    NChannelType_DIRECT_MESSAGE   = 1,   ///< A private chat between two users.
    NChannelType_GROUP            = 2    ///< A chat within a group on the server.
} eNChannelType;

/// UNIX time in milliseconds.
/// Use getUnixTimestampMs() to get current time.
typedef uint64_t NTimestamp;

#ifndef __cplusplus
    typedef uint8_t bool;
    #define true    1
    #define false   0
#endif

/// array of bytes
typedef struct NBytes
{
    uint8_t* bytes;
    uint32_t size;
} sNBytes;

/// Constant for defaut port.
/// This is not valid port, actual port will be selected automatically.
#define NDEFAULT_PORT   -1

#ifdef __cplusplus
}
#endif
