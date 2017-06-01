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

#include "NLeaderboardRecordsFetchMessage.h"

namespace Nakama {

	NLeaderboardRecordsFetchMessage::NLeaderboardRecordsFetchMessage()
	{
		// set our default
		envelope.mutable_leaderboard_records_fetch();
	}

	/* Factory Methods */
	NLeaderboardRecordsFetchMessage::Builder::Builder(std::string leaderboardId) {
		Fetch(leaderboardId);
	}

	NLeaderboardRecordsFetchMessage::Builder NLeaderboardRecordsFetchMessage::Builder::Fetch(std::string leaderboardId)
	{
		message.envelope.mutable_leaderboard_records_fetch()->mutable_leaderboard_ids()->Add()->assign(leaderboardId);
		return *this;
	}

	NLeaderboardRecordsFetchMessage::Builder NLeaderboardRecordsFetchMessage::Builder::Limit(int64_t limit)
	{
		message.envelope.mutable_leaderboard_records_fetch()->set_limit(limit);
		return *this;
	}

	NLeaderboardRecordsFetchMessage::Builder NLeaderboardRecordsFetchMessage::Builder::Cursor(NCursor cursor)
	{
		message.envelope.mutable_leaderboard_records_fetch()->set_cursor(cursor.GetValue());
		return *this;
	}

	NLeaderboardRecordsFetchMessage NLeaderboardRecordsFetchMessage::Builder::Build()
	{
		// Clone object so builder now operates on new copy.
		NLeaderboardRecordsFetchMessage original = message;
		message = NLeaderboardRecordsFetchMessage();
		message.envelope.set_allocated_leaderboard_records_fetch(new TLeaderboardRecordsFetch(original.envelope.leaderboard_records_fetch()));
		return original;
	}
}
