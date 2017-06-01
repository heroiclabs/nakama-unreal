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

#include "NLeaderboardRecordsListMessage.h"

namespace Nakama {

	NLeaderboardRecordsListMessage::NLeaderboardRecordsListMessage()
	{
		// set our default
		envelope.mutable_leaderboard_records_list();
	}

	/* Factory Methods */
	NLeaderboardRecordsListMessage::Builder::Builder(std::string leaderboardId) {
		message.envelope.mutable_leaderboard_records_list()->set_leaderboard_id(leaderboardId);
	}

	NLeaderboardRecordsListMessage::Builder NLeaderboardRecordsListMessage::Builder::FilterByPagingToOwnerId(std::string ownerId)
	{
		message.envelope.mutable_leaderboard_records_list()->set_owner_id(ownerId);
		return *this;
	}

	NLeaderboardRecordsListMessage::Builder NLeaderboardRecordsListMessage::Builder::FilterByOwnerIds(std::vector<std::string> ownerIds)
	{
		auto owners = new TLeaderboardRecordsList_Owners();
		for (int i = 0, maxI = ownerIds.size(); i < maxI; i++)
		{
			owners->mutable_owner_ids()->Add()->assign(ownerIds[i]);
		}
		message.envelope.mutable_leaderboard_records_list()->set_allocated_owner_ids(owners);
		return *this;
	}

	NLeaderboardRecordsListMessage::Builder NLeaderboardRecordsListMessage::Builder::FilterByLang(std::string lang)
	{
		message.envelope.mutable_leaderboard_records_list()->set_lang(lang);
		return *this;
	}

	NLeaderboardRecordsListMessage::Builder NLeaderboardRecordsListMessage::Builder::FilterByLocation(std::string location)
	{
		message.envelope.mutable_leaderboard_records_list()->set_location(location);
		return *this;
	}

	NLeaderboardRecordsListMessage::Builder NLeaderboardRecordsListMessage::Builder::FilterByTimezone(std::string timezone)
	{
		message.envelope.mutable_leaderboard_records_list()->set_timezone(timezone);
		return *this;
	}

	NLeaderboardRecordsListMessage::Builder NLeaderboardRecordsListMessage::Builder::Limit(int64_t limit)
	{
		message.envelope.mutable_leaderboard_records_list()->set_limit(limit);
		return *this;
	}

	NLeaderboardRecordsListMessage::Builder NLeaderboardRecordsListMessage::Builder::Cursor(NCursor cursor)
	{
		message.envelope.mutable_leaderboard_records_list()->set_cursor(cursor.GetValue());
		return *this;
	}

	NLeaderboardRecordsListMessage NLeaderboardRecordsListMessage::Builder::Build()
	{
		// Clone object so builder now operates on new copy.
		NLeaderboardRecordsListMessage original = message;
		message = NLeaderboardRecordsListMessage();
		message.envelope.set_allocated_leaderboard_records_list(new TLeaderboardRecordsList(original.envelope.leaderboard_records_list()));
		return original;
	}
}
