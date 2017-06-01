/**
* Copyright 2017 The Nakama Authors
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#pragma once

#include "Defines.h"

using namespace server;

namespace Nakama {

	class NAKAMA_API NLeaderboardRecord {

	public:
		NLeaderboardRecord() {}
		NLeaderboardRecord(LeaderboardRecord message)
		{
			leaderboardId = message.leaderboard_id();
			ownerId = message.owner_id();
			handle = message.handle();
			lang = message.lang();
			location = message.location();
			timezone = message.timezone();
			rank = message.rank();
			score = message.score();
			numScore = message.num_score();
			metadata = message.metadata();
			rankedAt = message.ranked_at();
			updatedAt = message.updated_at();
			expiresAt = message.expires_at();
		}

		~NLeaderboardRecord() {}

		std::string GetLeaderboardId() { return leaderboardId; }
		std::string GetOwnerId() { return ownerId; }
		std::string GetHandle() { return handle; }
		std::string GetLang() { return lang; }
		std::string GetLocation() { return location; }
		std::string GetTimezone() { return timezone; }
		int64_t GetRank() { return rank; }
		int64_t GetScore() { return score; }
		int64_t GetNumScore() { return numScore; }
		std::string GetMetadata() { return metadata; }
		int64_t GetRankedAt() { return rankedAt; }
		int64_t GetUpdatedAt() { return updatedAt; }
		int64_t GetExpiresAt() { return expiresAt; }

	private:
		std::string leaderboardId;
		std::string ownerId;
		std::string handle;
		std::string lang;
		std::string location;
		std::string timezone;
		int64_t rank;
		int64_t score;
		int64_t numScore;
		std::string metadata;
		int64_t rankedAt;
		int64_t updatedAt;
		int64_t expiresAt;
	};
}