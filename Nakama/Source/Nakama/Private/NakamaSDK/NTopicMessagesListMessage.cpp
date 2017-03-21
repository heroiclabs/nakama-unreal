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

#ifdef __UNREAL__
#include "Nakama/Private/NakamaPrivatePCH.h"
#endif
#include "NTopicMessagesListMessage.h"

namespace Nakama {

	NTopicMessagesListMessage::NTopicMessagesListMessage()
	{
		// set our default
		envelope.mutable_topic_messages_list();
	}

	/* Factory Methods */
	NTopicMessagesListMessage::Builder NTopicMessagesListMessage::Builder::Forward(bool forward)
	{
		message.envelope.mutable_topic_messages_list()->set_forward(forward);
		return *this;
	}

	NTopicMessagesListMessage::Builder NTopicMessagesListMessage::Builder::Cursor(NCursor cursor)
	{
		message.envelope.mutable_topic_messages_list()->set_cursor(cursor.GetValue());
		return *this;
	}

	NTopicMessagesListMessage::Builder NTopicMessagesListMessage::Builder::Limit(int64_t limit)
	{
		message.envelope.mutable_topic_messages_list()->set_limit(limit);
		return *this;
	}

	NTopicMessagesListMessage::Builder NTopicMessagesListMessage::Builder::TopicDirectMessage(std::string userId)
	{
		message.envelope.mutable_topic_messages_list()->set_user_id(userId);
		return *this;
	}

	NTopicMessagesListMessage::Builder NTopicMessagesListMessage::Builder::TopicRoom(std::string room)
	{
		message.envelope.mutable_topic_messages_list()->set_room(room);
		return *this;
	}

	NTopicMessagesListMessage::Builder NTopicMessagesListMessage::Builder::TopicGroup(std::string groupId)
	{
		message.envelope.mutable_topic_messages_list()->set_group_id(groupId);
		return *this;
	}

	NTopicMessagesListMessage NTopicMessagesListMessage::Builder::Build()
	{
		// Clone object so builder now operates on new copy.
		NTopicMessagesListMessage original = message;
		message = NTopicMessagesListMessage();
		message.envelope.set_allocated_topic_messages_list(new TTopicMessagesList(original.envelope.topic_messages_list()));
		return original;
	}
}
