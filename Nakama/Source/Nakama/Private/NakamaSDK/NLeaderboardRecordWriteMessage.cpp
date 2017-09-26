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

#include "NLeaderboardRecordWriteMessage.h"

namespace Nakama {

	NLeaderboardRecordWriteMessage::NLeaderboardRecordWriteMessage()
	{
		// set our default
		envelope.mutable_leaderboard_records_write();
	}

	/* Factory Methods */
	NLeaderboardRecordWriteMessage::Builder::Builder(std::string leaderboardId) {
		message.envelope.mutable_leaderboard_records_write()->add_records()->set_leaderboard_id(leaderboardId);
	}

	NLeaderboardRecordWriteMessage::Builder NLeaderboardRecordWriteMessage::Builder::Location(std::string location)
	{
		message.envelope.mutable_leaderboard_records_write()->mutable_records()->mutable_data()[0]->set_location(location);
		return *this;
	}

	NLeaderboardRecordWriteMessage::Builder NLeaderboardRecordWriteMessage::Builder::Timezone(std::string timezone)
	{
		message.envelope.mutable_leaderboard_records_write()->mutable_records()->mutable_data()[0]->set_timezone(timezone);
		return *this;
	}

	NLeaderboardRecordWriteMessage::Builder NLeaderboardRecordWriteMessage::Builder::Metadata(std::string metadata)
	{
		message.envelope.mutable_leaderboard_records_write()->mutable_records()->mutable_data()[0]->set_metadata(metadata);
		return *this;
	}

	NLeaderboardRecordWriteMessage::Builder NLeaderboardRecordWriteMessage::Builder::Increment(int64_t value)
	{
		message.envelope.mutable_leaderboard_records_write()->mutable_records()->mutable_data()[0]->set_incr(value);
		return *this;
	}

	NLeaderboardRecordWriteMessage::Builder NLeaderboardRecordWriteMessage::Builder::Decrement(int64_t value)
	{
		message.envelope.mutable_leaderboard_records_write()->mutable_records()->mutable_data()[0]->set_decr(value);
		return *this;
	}

	NLeaderboardRecordWriteMessage::Builder NLeaderboardRecordWriteMessage::Builder::Set(int64_t value)
	{
		message.envelope.mutable_leaderboard_records_write()->mutable_records()->mutable_data()[0]->set_set(value);
		return *this;
	}

	NLeaderboardRecordWriteMessage::Builder NLeaderboardRecordWriteMessage::Builder::Best(int64_t value)
	{
		message.envelope.mutable_leaderboard_records_write()->mutable_records()->mutable_data()[0]->set_best(value);
		return *this;
	}

	NLeaderboardRecordWriteMessage NLeaderboardRecordWriteMessage::Builder::Build()
	{
		// Clone object so builder now operates on new copy.
		NLeaderboardRecordWriteMessage original = message;
		message = NLeaderboardRecordWriteMessage();
		message.envelope.set_allocated_leaderboard_records_write(new TLeaderboardRecordsWrite(original.envelope.leaderboard_records_write()));
		return original;
	}
}