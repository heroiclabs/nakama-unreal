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

	class NAKAMA_API NGroup {

	public:
		NGroup() {}
		NGroup(server::Group message)
		{
			id = message.id();
			private_ = message.private_();
			creatorId = message.creator_id();
			name = message.name();
			description = message.description();
			avatarUrl = message.avatar_url();
			lang = message.lang();
			metadata = message.metadata();
			count = message.count();
			createdAt = message.created_at();
			updatedAt = message.updated_at();
		}

		~NGroup() {}

		std::string GetId() { return id; }
		bool IsPrivate() { return private_; }
		std::string GetCreatorId() { return creatorId; }
		std::string GetName() { return name; }
		std::string GetDescription() { return description; }
		std::string GetAvatarUrl() { return avatarUrl; }
		std::string GetLang() { return lang; }
		std::string GetMetadata() { return metadata; }
		uint64_t GetCount() { return count; }
		uint64_t GetCreatedAt() { return createdAt; }
		uint64_t GetUpdatedAt() { return updatedAt; }

	private:
		std::string id;
		bool private_;
		std::string creatorId;
		std::string name;
		std::string description;
		std::string avatarUrl;
		std::string lang;
		std::string metadata;
		uint64_t count;
		uint64_t createdAt;
		uint64_t updatedAt;
	};

}
