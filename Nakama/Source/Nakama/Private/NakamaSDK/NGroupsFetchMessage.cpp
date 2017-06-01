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

	NGroupsFetchMessage NGroupsFetchMessage::Default(std::vector<std::string> groupIds)
	{
		return NGroupsFetchMessage::Builder().SetGroupIds(groupIds).Build();
	}

	/* Factory Methods */

	NGroupsFetchMessage::Builder NGroupsFetchMessage::Builder::SetGroupIds(std::vector<std::string> groupIds)
	{
		auto container = new TGroupsFetch_GroupIds();
		for (size_t i = 0; i < groupIds.size(); i++)
		{
			container->mutable_group_ids()->Add()->assign(groupIds[i]);
		}

		message.envelope.mutable_groups_fetch()->set_allocated_group_ids(container);
		return *this;
	}

	NGroupsFetchMessage::Builder NGroupsFetchMessage::Builder::SetNames(std::vector<std::string> names)
	{
		auto container = new TGroupsFetch_Names();
		for (size_t i = 0; i < names.size(); i++)
		{
			container->mutable_names()->Add()->assign(names[i]);
		}

		message.envelope.mutable_groups_fetch()->set_allocated_names(container);
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
