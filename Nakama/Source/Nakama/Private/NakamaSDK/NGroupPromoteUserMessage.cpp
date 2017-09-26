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

#include "NGroupPromoteUserMessage.h"

namespace Nakama {

	NGroupPromoteUserMessage::NGroupPromoteUserMessage(std::string groupId, std::string userId)
	{
		auto payload = envelope.mutable_group_users_promote()->add_group_users();
		payload->set_group_id(groupId);
		payload->set_user_id(userId);
	}

	NGroupPromoteUserMessage NGroupPromoteUserMessage::Default(std::string groupId, std::string userId)
	{
		return NGroupPromoteUserMessage(groupId, userId);
	}
}
