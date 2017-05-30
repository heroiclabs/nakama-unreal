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

#include "NMatchJoinMessage.h"

namespace Nakama {

	NMatchJoinMessage::NMatchJoinMessage(std::string matchId)
	{
		// set our default
		auto payload = envelope.mutable_match_join();
		payload->set_match_id(matchId);
	}

	NMatchJoinMessage NMatchJoinMessage::Default(std::string matchId)
	{
		return NMatchJoinMessage(matchId);
	}
}
