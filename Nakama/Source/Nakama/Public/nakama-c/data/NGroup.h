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

/// A group in the server.
typedef struct NAKAMA_API NGroup
{
    const char* id;              ///< The id of a group.
    const char* creatorId;       ///< The id of the user who created the group.
    const char* name;            ///< The unique name of the group.
    const char* description;     ///< A description for the group.
    const char* lang;            ///< The language expected to be a tag which follows the BCP-47 spec.
    const char* metadata;        ///< Additional information stored as a JSON object.
    const char* avatarUrl;       ///< A URL for an avatar image.
    bool open;                   ///< Anyone can join open groups, otherwise only admins can accept members.
    int32_t edgeCount;           ///< The current count of all members in the group.
    int32_t maxCount;            ///< The maximum number of members allowed.
    NTimestamp createTime;       ///< The UNIX time when the group was created.
    NTimestamp updateTime;       ///< The UNIX time when the group was last updated.
} sNGroup;

#ifdef __cplusplus
}
#endif
