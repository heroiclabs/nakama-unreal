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

	enum NAKAMA_API TopicType { DirectMessage = 0, Room, Group };

	class NAKAMA_API NTopicId {

	public:
		NTopicId() {}
		NTopicId(TopicId message)
		{
			switch (message.id_case())
			{
			case TopicId::IdCase::kDm:
				id = message.dm();
				type = TopicType::DirectMessage;
				break;
			case TopicId::IdCase::kRoom:
				id = message.room();
				type = TopicType::Room;
				break;
			case TopicId::IdCase::kGroupId:
				id = message.group_id();
				type = TopicType::Group;
				break;
			default:
				// TODO log a warning?
				break;
			}
		}

		~NTopicId() {}

		std::string GetId() { return id; }
		TopicType GetType() { return type; }

	private:
		std::string id;
		TopicType type;

	};

}