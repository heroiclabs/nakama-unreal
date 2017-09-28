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
	
	enum class NAKAMA_API UserState : uint8 { Admin = 0, Member, Join };

	class NAKAMA_API NGroupUser {

	public:
		NGroupUser() {}
		NGroupUser(server::GroupUser message) : 
			userInfo(message.user()) {

			switch (message.state())
			{
			case 0:
				state = UserState::Admin;
				break;
			case 1:
				state = UserState::Member;
				break;
			case 2:
				state = UserState::Join;
				break;
			default:
				// FIXME: Should handle this...
				break;
			}
		}

		~NGroupUser() {}

		std::string GetAvatarUrl() { return userInfo.GetAvatarUrl(); }
		uint64_t GetCreatedAt() { return userInfo.GetCreatedAt(); }
		std::string GetFullname() { return userInfo.GetFullname(); }
		std::string GetHandle() { return userInfo.GetHandle(); }
		std::string GetId() { return userInfo.GetId(); }
		std::string GetLang() { return userInfo.GetLang(); }
		uint64_t GetLastOnlineAt() { return userInfo.GetLastOnlineAt(); }
		std::string GetLocation() { return userInfo.GetLocation(); }
		std::string GetMetadata() { return userInfo.GetMetadata(); }
		std::string GetTimezone() { return userInfo.GetTimezone(); }
		uint64_t GetUpdatedAt() { return userInfo.GetUpdatedAt(); }

		UserState GetState() { return state; }

	private:
		NUser userInfo;
		UserState state;
	};

}
