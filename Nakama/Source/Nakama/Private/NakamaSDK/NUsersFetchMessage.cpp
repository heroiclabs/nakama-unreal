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
#include "NUsersFetchMessage.h"

namespace Nakama {

	NUsersFetchMessage::NUsersFetchMessage()
	{
		// set our default
		envelope.mutable_users_fetch();
	}

	/* Factory Methods */
	NUsersFetchMessage::Builder::Builder(std::string userId)
	{
		Add(userId);
	}

	NUsersFetchMessage::Builder NUsersFetchMessage::Builder::Add(std::string userId)
	{
		message.envelope.mutable_users_fetch()->mutable_user_ids()->Add()->assign(userId);
		return *this;
	}

	NUsersFetchMessage::Builder NUsersFetchMessage::Builder::Add(std::vector<std::string> userIds)
	{
		auto container = message.envelope.mutable_users_fetch()->mutable_user_ids();
		for (size_t i = 0; i < userIds.size(); i++)
		{
			container->Add()->assign(userIds[i]);
		}
		return *this;
	}

	NUsersFetchMessage NUsersFetchMessage::Builder::Build()
	{
		// Clone object so builder now operates on new copy.
		NUsersFetchMessage original = message;
		message = NUsersFetchMessage();
		message.envelope.set_allocated_users_fetch(new TUsersFetch(original.envelope.users_fetch()));
		return original;
	}
}
