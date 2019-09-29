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

/// Represents a complete leaderboard record with all scores and associated metadata.
typedef struct NAKAMA_API NLeaderboardRecord
{
    const char* leaderboardId;      ///< The ID of the leaderboard this score belongs to.
    const char* ownerId;            ///< The ID of the score owner, usually a user or group.
    const char* username;           ///< The username of the score owner, if the owner is a user.
    int64_t score;                  ///< The score value.
    int64_t subscore;               ///< An optional subscore value.
    int32_t numScore;               ///< The number of submissions to this score record.
    uint32_t maxNumScore;           ///< The maximum number of score updates allowed by the owner.
    const char* metadata;           ///< Metadata.
    NTimestamp createTime;          ///< The UNIX time when the leaderboard record was created.
    NTimestamp updateTime;          ///< The UNIX time when the leaderboard record was updated.
    NTimestamp expiryTime;          ///< The UNIX time when the leaderboard record expires.
    int64_t rank;                   ///< The rank of this record.
} sNLeaderboardRecord;

#ifdef __cplusplus
}
#endif
