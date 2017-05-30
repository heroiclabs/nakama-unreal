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
#include "NTopicId.h"
#include "NUserPresence.h"

using namespace server;

namespace Nakama {

	class NAKAMA_API NTopic {

	public:
		NTopic() {}
		NTopic(server::TTopic message) : 
			topic(NTopicId(message.topic())),
			self(NUserPresence(message.self()))
		{
			auto msgPresences = message.presences();
			for (size_t i = 0, maxI = msgPresences.size(); i < maxI; i++) {
				presence.push_back(NUserPresence(msgPresences[i]));
			}
		}

		~NTopic() {}

		NTopicId GetTopic() { return topic; }
		std::vector<NUserPresence> GetPresence() { return presence; }
		NUserPresence GetSelf() { return self; }

	private:
		NTopicId topic;
		std::vector<NUserPresence> presence;
		NUserPresence self;

	};

}
