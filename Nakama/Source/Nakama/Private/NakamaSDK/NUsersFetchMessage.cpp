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

#include "NUsersFetchMessage.h"

namespace Nakama {

	NUsersFetchMessage::NUsersFetchMessage()
	{
		// set our default
		envelope.mutable_users_fetch();
	}

	NUsersFetchMessage NUsersFetchMessage::Ids(std::vector<std::string> ids)
	{
		return NUsersFetchMessage::Builder().SetUserIds(ids).Build();
	}

	NUsersFetchMessage NUsersFetchMessage::Handles(std::vector<std::string> handles)
	{
		return NUsersFetchMessage::Builder().SetHandles(handles).Build();
	}

	/* Factory Methods */

	NUsersFetchMessage::Builder NUsersFetchMessage::Builder::SetUserIds(std::vector<std::string> ids)
	{
		auto container = new TUsersFetch_UserIds();
		for (size_t i = 0; i < ids.size(); i++)
		{
			container->mutable_user_ids()->Add()->assign(ids[i]);
		}

		message.envelope.mutable_users_fetch()->set_allocated_user_ids(container);
		return *this;
	}

	NUsersFetchMessage::Builder NUsersFetchMessage::Builder::SetHandles(std::vector<std::string> handles)
	{
		auto container = new TUsersFetch_Handles();
		for (size_t i = 0; i < handles.size(); i++)
		{
			container->mutable_handles()->Add()->assign(handles[i]);
		}

		message.envelope.mutable_users_fetch()->set_allocated_handles(container);
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
