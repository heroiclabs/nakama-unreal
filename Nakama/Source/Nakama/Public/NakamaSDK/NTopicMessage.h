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
#include "NTopicId.h"

using namespace server;

namespace Nakama {

	enum NAKAMA_API TopicMessageType { Chat = 0, GroupJoin, GroupAdd, GroupLeave, GroupKick, GroupPromoted };

	class NAKAMA_API NTopicMessage {

	public:
		NTopicMessage() {}
		NTopicMessage(TopicMessage message) : 
			topic(NTopicId(message.topic()))
		{
			userId = message.user_id();
			messageId = message.message_id();
			createdAt = message.created_at();
			expiresAt = message.expires_at();
			handle = message.handle();

			switch (message.type())
			{
			case 0:
				type = TopicMessageType::Chat;
				break;
			case 1:
				type = TopicMessageType::GroupJoin;
				break;
			case 2:
				type = TopicMessageType::GroupAdd;
				break;
			case 3:
				type = TopicMessageType::GroupLeave;
				break;
			case 4:
				type = TopicMessageType::GroupKick;
				break;
			case 5:
				type = TopicMessageType::GroupPromoted;
				break;
			}

			data = message.data();
		}

		~NTopicMessage() {}

		NTopicId GetTopic() { return topic; }
		std::string GetUserId() { return userId; }
		std::string GetMessageId() { return messageId; }
		int64_t GetCreatedAt() { return createdAt; }
		int64_t GetExpiresAt() { return expiresAt; }
		std::string GetHandle() { return handle; }
		TopicMessageType GetType() { return type; }
		std::string GetData() { return data; }

	private:
		NTopicId topic;
		std::string userId;
		std::string messageId;
		int64_t createdAt;
		int64_t expiresAt;
		std::string handle;
		TopicMessageType type;
		std::string data;
	};
}