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

using namespace server;

namespace Nakama {

	class NAKAMA_API NMatchPresence {

	public:
		NMatchPresence(MatchPresence message)
		{
			id = message.match_id();
			for (size_t i = 0; i < message.joins_size(); i++) {
				join.push_back(NUserPresence(message.joins(i)));
			}
			for (size_t i = 0; i < message.leaves_size(); i++) {
				leave.push_back(NUserPresence(message.leaves(i)));
			}
		}

		~NMatchPresence() {}

		std::string GetId() { return id; }
		std::vector<NUserPresence> GetJoin() { return join; }
		std::vector<NUserPresence> GetLeave() { return leave; }

	private:
		std::string id;
		std::vector<NUserPresence> join;
		std::vector<NUserPresence> leave;
	};
}