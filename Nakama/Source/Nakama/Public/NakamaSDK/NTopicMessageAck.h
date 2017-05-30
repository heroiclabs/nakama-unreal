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

	class NAKAMA_API NTopicMessageAck {

	public:
		NTopicMessageAck() {}
		NTopicMessageAck(TTopicMessageAck message)
		{
			messageId = message.message_id();
			createdAt = message.created_at();
			expiresAt = message.expires_at();
			handle = message.handle();
		}

		~NTopicMessageAck() {}

		std::string GetMessageId() { return messageId; }
		int64_t GetCreatedAt() { return createdAt; }
		int64_t GetExpiresAt() { return expiresAt; }
		std::string GetHandle() { return handle; }

	private:
		std::string messageId;
		uint64_t createdAt;
		uint64_t expiresAt;
		std::string handle;
	};
}