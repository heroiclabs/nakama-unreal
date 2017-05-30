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
	
	enum NAKAMA_API UserType { Admin = 0, Member, Join };

	class NAKAMA_API NGroupUser {

	public:
		NGroupUser() {}
		NGroupUser(server::GroupUser message) : 
			userInfo(message.user()) {

			switch (message.type())
			{
			case 0:
				type = UserType::Admin;
				break;
			case 1:
				type = UserType::Member;
				break;
			case 2:
				type = UserType::Join;
				break;
			default:
				// FIXME: Should handle this...
				break;
			}
		}

		~NGroupUser() {}

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

		UserType GetState() { return type; }

	private:
		NUser userInfo;
		UserType type;
	};

}
