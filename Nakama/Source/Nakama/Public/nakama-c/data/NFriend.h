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

#include "nakama-c/data/NUser.h"

#ifdef __cplusplus
extern "C" {
#endif

/// The friendship status.
typedef enum FriendState {
    STATE_FRIEND = 0,                 ///< The user is a friend of the current user.
    STATE_INVITE_SENT = 1,            ///< The current user has sent an invite to the user.
    STATE_INVITE_RECEIVED = 2,        ///< The current user has received an invite from this user.
    STATE_BLOCKED = 3                 ///< The current user has blocked this user.
} eFriendState;

/// A friend of a user.
typedef struct NAKAMA_API NFriend
{
    sNUser user;                      ///< The user object.
    eFriendState state;               ///< The friend status.
    NTimestamp updateTime;            ///< Time of the latest relationship update.
} sNFriend;

#ifdef __cplusplus
}
#endif
