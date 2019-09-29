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

#include "nakama-c/NTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/// A user in the server.
typedef struct NAKAMA_API NUser
{
    const char* id;            ///< The id of the user's account.
    const char* username;      ///< The username of the user's account.
    const char* displayName;   ///< The display name of the user.
    const char* avatarUrl;     ///< A URL for an avatar image.
    const char* lang;          ///< The language expected to be a tag which follows the BCP-47 spec.
    const char* location;      ///< The location set by the user.
    const char* timeZone;      ///< The timezone set by the user.
    const char* metadata;      ///< Additional information stored as a JSON object.
    const char* facebookId;    ///< The Facebook id in the user's account.
    const char* googleId;      ///< The Google id in the user's account.
    const char* gameCenterId;  ///< The Apple Game Center in of the user's account.
    const char* steamId;       ///< The Steam id in the user's account.
    bool online;               ///< Indicates whether the user is currently online.
    int32_t edgeCount;         ///< Number of related edges to this user (friends).
    NTimestamp createdAt;      ///< The UNIX time when the user was created.
    NTimestamp updatedAt;      ///< The UNIX time when the user was last updated.
} sNUser;

#ifdef __cplusplus
}
#endif
