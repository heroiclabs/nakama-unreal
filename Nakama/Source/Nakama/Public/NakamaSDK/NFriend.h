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
#include "NUser.h"

namespace Nakama {

	enum NAKAMA_API FriendState { Friend = 0, Invite, Invited, Blocked };

	class NAKAMA_API NFriend {

	public:
		NFriend(server::Friend message) :
			userInfo(message.user()) {

			switch (message.type())
			{
			case 0:
				state = FriendState::Friend;
				break;
			case 1:
				state = FriendState::Invite;
				break;
			case 2:
				state = FriendState::Invited;
				break;
			case 3:
				state = FriendState::Blocked;
				break;
			default:
				// FIXME: Should handle this...
				break;
			}
		}

		~NFriend() {}

		std::string GetAvatarUrl();
		uint64_t GetCreatedAt();
		std::string GetFullname();
		std::string GetHandle();
		std::string GetId();
		std::string GetLang();
		uint64_t GetLastOnlineAt();
		std::string GetLocation();
		std::string GetMetadata();
		std::string GetTimezone();
		uint64_t GetUpdatedAt();

		FriendState GetState() { return state; }

	private:
		NUser userInfo;
		FriendState state;
	};

}
