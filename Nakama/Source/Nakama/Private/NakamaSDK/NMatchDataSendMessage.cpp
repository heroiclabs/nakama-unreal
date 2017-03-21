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

#ifdef __UNREAL__
#include "Nakama/Private/NakamaPrivatePCH.h"
#endif
#include "NMatchDataSendMessage.h"

namespace Nakama {

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
}
