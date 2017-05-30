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

#include "NTopicMessageSendMessage.h"

namespace Nakama {

	NTopicMessageSendMessage::NTopicMessageSendMessage(NTopicId topic, std::string data)
	{
		// set our default
		auto payload = envelope.mutable_topic_message_send();
		auto myTopic = payload->mutable_topic();
		switch (topic.GetType()) {
		case DirectMessage:
			myTopic->set_dm(topic.GetId());
			break;
		case Room:
			myTopic->set_room(topic.GetId());
			break;
		case Group:
			myTopic->set_group_id(topic.GetId());
			break;
		}
		payload->set_data(data);
	}

	NTopicMessageSendMessage NTopicMessageSendMessage::Default(NTopicId topic, std::string data)
	{
		return NTopicMessageSendMessage(topic, data);
	}
}
