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
#include "NUserPresence.h"
#include "NMatchmakeTicket.h"
#include "NMatchToken.h"
#include "NMatchmakeUserProperty.h"
#include <functional>

using namespace server;

namespace Nakama {

	class NAKAMA_API NMatchmakeMatched {

	public:
		NMatchmakeMatched() {}
		NMatchmakeMatched(MatchmakeMatched message)
		{
			ticket = NMatchmakeTicket(message.ticket());
			token = NMatchToken(message.token());
			for (size_t i = 0; i < message.presences_size(); i++) {
				presence.push_back(NUserPresence(message.presences(i)));
			}
			self = NUserPresence(message.self());
			for (size_t i = 0; i < message.properties_size(); i++) {
				userProperties.push_back(NMatchmakeUserProperty(message.properties(i)));
			}
		}

		~NMatchmakeMatched() {}

		NMatchmakeTicket GetTicket() { return ticket; }
		NMatchToken GetToken() { return token; }
		std::vector<NUserPresence> GetPresence() { return presence; }
		NUserPresence GetSelf() { return self; }
		std::vector<NMatchmakeUserProperty> GetUserProperties() { return userProperties; }

	private:
		NMatchmakeTicket ticket;
		NMatchToken token;
		std::vector<NUserPresence> presence;
		NUserPresence self;
		std::vector<NMatchmakeUserProperty> userProperties;
	};
}