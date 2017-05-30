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

	class NAKAMA_API NMatchData {

	public:
		NMatchData() {}
		NMatchData(MatchData message) : 
			presence(NUserPresence(message.presence()))
		{
			data = message.data();
			id = message.match_id();
			opCode = message.op_code();
		}

		~NMatchData() {}

		std::string GetData() { return data; }
		std::string GetId() { return id; }
		int64_t GeOpCode() { return opCode; }
		NUserPresence GetPresence() { return presence; }

	private:
		std::string data;
		std::string id;
		int64_t opCode;
		NUserPresence presence;
	};
}