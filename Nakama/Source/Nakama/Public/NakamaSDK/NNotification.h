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
#include <functional>

using namespace server;

namespace Nakama {

	class NAKAMA_API NNotification {

	public:
		NNotification() {}
		NNotification(Notification n)
		{
			id = n.id();
			subject = n.subject();
			content = n.content();
			code = n.code();
			senderId = n.sender_id();
			createdAt = n.created_at();
			expiresAt = n.expires_at();
			persistent = n.persistent();
		}

		~NNotification() {}

		std::string GetId() { return id; }
		std::string GetSubject() { return subject; }
		std::string GetContent() { return content; }
		uint64_t GetCode() { return code; }
		std::string GetSenderId() { return senderId; }
		uint64_t GetCreatedAt() { return createdAt; }
		uint64_t GetExpiresAt() { return expiresAt; }
		bool IsPersistent() { return persistent; }

	private:
		std::string id;
		std::string subject;
		std::string content;
		uint64_t code;
		std::string senderId;
		uint64_t createdAt;
		uint64_t expiresAt;
		bool persistent;
	};
}