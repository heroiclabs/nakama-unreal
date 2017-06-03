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

#include "NLeaderboardsListMessage.h"

namespace Nakama {

	NLeaderboardsListMessage::NLeaderboardsListMessage()
	{
		// set our default
		envelope.mutable_leaderboards_list();
	}

	/* Factory Methods */
	NLeaderboardsListMessage::Builder::Builder() {
	}

	NLeaderboardsListMessage::Builder NLeaderboardsListMessage::Builder::Limit(int64_t limit)
	{
		message.envelope.mutable_leaderboards_list()->set_limit(limit);
		return *this;
	}

	NLeaderboardsListMessage::Builder NLeaderboardsListMessage::Builder::Cursor(NCursor cursor)
	{
		message.envelope.mutable_leaderboards_list()->set_cursor(cursor.GetValue());
		return *this;
	}

	NLeaderboardsListMessage::Builder NLeaderboardsListMessage::Builder::Add(std::string id)
	{
		message.envelope.mutable_leaderboards_list()->mutable_filter_leaderboard_id()->Add()->assign(id);
		return *this;
	}

	NLeaderboardsListMessage::Builder NLeaderboardsListMessage::Builder::Add(std::vector<std::string> ids)
	{
		for (int i = 0, maxI = ids.size(); i < maxI; i++)
		{
			message.envelope.mutable_leaderboards_list()->mutable_filter_leaderboard_id()->Add()->assign(ids[i]);
		}
		return *this;
	}

	NLeaderboardsListMessage NLeaderboardsListMessage::Builder::Build()
	{
		// Clone object so builder now operates on new copy.
		NLeaderboardsListMessage original = message;
		message = NLeaderboardsListMessage();
		message.envelope.set_allocated_leaderboards_list(new TLeaderboardsList(original.envelope.leaderboards_list()));
		return original;
	}
}
