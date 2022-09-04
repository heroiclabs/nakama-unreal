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

#include <string>
#include <memory>

#include <nakama-cpp/NTypes.h>
#include <nakama-cpp/NExport.h>

NAKAMA_NAMESPACE_BEGIN

    /// Represents a complete leaderboard record with all scores and associated metadata.
    struct NLeaderboardRecord
    {
        std::string leaderboardId;      ///< The ID of the leaderboard this score belongs to.
        std::string ownerId;            ///< The ID of the score owner, usually a user or group.
        std::string username;           ///< The username of the score owner, if the owner is a user.
        int64_t score = 0;              ///< The score value.
        int64_t subscore = 0;           ///< An optional subscore value.
        int32_t numScore = 0;           ///< The number of submissions to this score record.
        uint32_t maxNumScore = 0;       ///< The maximum number of score updates allowed by the owner.
        std::string metadata;           ///< Metadata.
        NTimestamp createTime = 0;      ///< The UNIX time when the leaderboard record was created.
        NTimestamp updateTime = 0;      ///< The UNIX time when the leaderboard record was updated.
        NTimestamp expiryTime = 0;      ///< The UNIX time when the leaderboard record expires.
        int64_t rank = 0;               ///< The rank of this record.
    };

NAKAMA_NAMESPACE_END
