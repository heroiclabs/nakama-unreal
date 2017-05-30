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

namespace Nakama {

	class NAKAMA_API NUser {

	public:
		NUser() {}
		NUser(server::User user) {
			avatarUrl = user.avatar_url();
			createdAt = user.created_at();
			fullname = user.fullname();
			handle = user.handle();
			id = user.id();
			lang = user.lang();
			lastOnlineAt = user.last_online_at();
			location = user.location();
			metadata = user.metadata();
			timezone = user.timezone();
			updatedAt = user.updated_at();
		}

		~NUser() {}

		std::string GetAvatarUrl() { return avatarUrl; }
		uint64_t GetCreatedAt() { return createdAt; }
		std::string GetFullname() { return fullname; }
		std::string GetHandle() { return handle; }
		std::string GetId() { return id; }
		std::string GetLang() { return lang; }
		uint64_t GetLastOnlineAt() { return lastOnlineAt; }
		std::string GetLocation() { return location; }
		std::string GetMetadata() { return metadata; }
		std::string GetTimezone() { return timezone; }
		uint64_t GetUpdatedAt() { return updatedAt; }

	private:
		std::string avatarUrl;
		uint64_t createdAt;
		std::string fullname;
		std::string handle;
		std::string id;
		std::string lang;
		uint64_t lastOnlineAt;
		std::string location;
		std::string metadata;
		std::string timezone;
		uint64_t updatedAt;
	};

}
