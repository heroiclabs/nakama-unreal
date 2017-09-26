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

#include "NGroupsFetchMessage.h"

namespace Nakama {

	NGroupsFetchMessage::NGroupsFetchMessage()
	{
		// set our default
		envelope.mutable_groups_fetch();
	}

	NGroupsFetchMessage NGroupsFetchMessage::Ids(std::vector<std::string> ids)
	{
		return NGroupsFetchMessage::Builder().SetGroupIds(ids).Build();
	}

	NGroupsFetchMessage NGroupsFetchMessage::Names(std::vector<std::string> names)
	{
		return NGroupsFetchMessage::Builder().SetNames(names).Build();
	}

	/* Factory Methods */

	NGroupsFetchMessage::Builder NGroupsFetchMessage::Builder::SetGroupIds(std::vector<std::string> ids)
	{
		for (size_t i = 0; i < ids.size(); i++)
		{
			message.envelope.mutable_groups_fetch()->add_groups()->set_group_id(ids[i]);
		}
		return *this;
	}

	NGroupsFetchMessage::Builder NGroupsFetchMessage::Builder::SetNames(std::vector<std::string> names)
	{
		for (size_t i = 0; i < names.size(); i++)
		{
			message.envelope.mutable_groups_fetch()->add_groups()->set_name(names[i]);
		}
		return *this;
	}

	NGroupsFetchMessage NGroupsFetchMessage::Builder::Build()
	{
		// Clone object so builder now operates on new copy.
		NGroupsFetchMessage original = message;
		message = NGroupsFetchMessage();
		message.envelope.set_allocated_groups_fetch(new TGroupsFetch(original.envelope.groups_fetch()));
		return original;
	}
}
