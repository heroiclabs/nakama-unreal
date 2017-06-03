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

#include "NMatchDataSendMessage.h"

namespace Nakama {
	NMatchDataSendMessage::NMatchDataSendMessage()
	{
		// set our default
		envelope.mutable_match_data_send();
	}

	NMatchDataSendMessage::NMatchDataSendMessage(std::string matchId, int64_t opCode, std::string data)
	{
		// set our default
		auto payload = envelope.mutable_match_data_send();
		payload->set_match_id(matchId);
		payload->set_op_code(opCode);
		payload->set_data(data);
	}

	NMatchDataSendMessage NMatchDataSendMessage::Default(std::string matchId, int64_t opCode, std::string data)
	{
		return NMatchDataSendMessage(matchId, opCode, data);
	}

	/* Factory Methods */
	NMatchDataSendMessage::Builder::Builder() {
		message = NMatchDataSendMessage();
	}

	NMatchDataSendMessage::Builder::Builder(std::string matchId, int64_t opCode, std::string data) {
		message = NMatchDataSendMessage(matchId, opCode, data);
	}

	NMatchDataSendMessage::Builder NMatchDataSendMessage::Builder::MatchId(std::string matchId)
	{
		message.envelope.mutable_match_data_send()->set_match_id(matchId);
		return *this;
	}

	NMatchDataSendMessage::Builder NMatchDataSendMessage::Builder::OpCode(int64_t opCode)
	{
		message.envelope.mutable_match_data_send()->set_op_code(opCode);
		return *this;
	}

	NMatchDataSendMessage::Builder NMatchDataSendMessage::Builder::Data(std::string data)
	{
		message.envelope.mutable_match_data_send()->set_data(data);
		return *this;
	}

	NMatchDataSendMessage::Builder NMatchDataSendMessage::Builder::Presences(std::vector<NUserPresence> presences)
	{
		message.envelope.mutable_match_data_send()->mutable_presences()->Clear();
		for (int i = 0, maxI = presences.size(); i < maxI; i++)
		{
			auto pres = message.envelope.mutable_match_data_send()->mutable_presences()->Add();
			pres->set_user_id(presences[i].GetUserId());
			pres->set_session_id(presences[i].GetSessionId());
		}
		return *this;
	}

	NMatchDataSendMessage NMatchDataSendMessage::Builder::Build()
	{
		// Clone object so builder now operates on new copy.
		NMatchDataSendMessage original = message;
		message = NMatchDataSendMessage();
		message.envelope.set_allocated_match_data_send(new MatchDataSend(original.envelope.match_data_send()));
		return original;
	}
}
