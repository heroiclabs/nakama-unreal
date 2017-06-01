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

using namespace server;

namespace Nakama {

	class NAKAMA_API NUserPresence {

	public:
		NUserPresence() {}
		NUserPresence(server::UserPresence message)
		{
			userId = message.user_id();
			sessionId = message.session_id();
			handle = message.handle();
		}

		~NUserPresence() {}

		std::string GetUserId() { return userId; }
		std::string GetSessionId() { return sessionId; }
		std::string GetHandle() { return handle; }

	private:
		std::string userId;
		std::string sessionId;
		std::string handle;

	};

}
