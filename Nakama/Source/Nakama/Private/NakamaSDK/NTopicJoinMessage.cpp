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
#include "NTopicJoinMessage.h"

namespace Nakama {

	NTopicJoinMessage::NTopicJoinMessage()
	{
		// set our default
		envelope.mutable_topic_join();
	}

	/* Factory Methods */
	NTopicJoinMessage::Builder NTopicJoinMessage::Builder::TopicDirectMessage(std::string userId)
	{
		message.envelope.mutable_topic_join()->set_user_id(userId);
		return *this;
	}

	NTopicJoinMessage::Builder NTopicJoinMessage::Builder::TopicRoom(std::string room)
	{
		message.envelope.mutable_topic_join()->set_room(room);
		return *this;
	}

	NTopicJoinMessage::Builder NTopicJoinMessage::Builder::TopicGroup(std::string groupId)
	{
		message.envelope.mutable_topic_join()->set_group_id(groupId);
		return *this;
	}

	NTopicJoinMessage NTopicJoinMessage::Builder::Build()
	{
		// Clone object so builder now operates on new copy.
		NTopicJoinMessage original = message;
		message = NTopicJoinMessage();
		message.envelope.set_allocated_storage_remove(new TStorageRemove(original.envelope.storage_remove()));
		return original;
	}
}
