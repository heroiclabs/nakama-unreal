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

#include "NGroupKickUserMessage.h"

namespace Nakama {

	NGroupKickUserMessage::NGroupKickUserMessage(std::string groupId, std::string userId)
	{
		auto payload = envelope.mutable_group_users_kick()->add_group_users();
		payload->set_group_id(groupId);
		payload->set_user_id(userId);
	}

	NGroupKickUserMessage NGroupKickUserMessage::Default(std::string groupId, std::string userId)
	{
		return NGroupKickUserMessage(groupId, userId);
	}
}
