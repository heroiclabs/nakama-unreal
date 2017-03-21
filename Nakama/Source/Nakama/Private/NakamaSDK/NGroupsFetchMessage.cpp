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
#include "NGroupsFetchMessage.h"

namespace Nakama {

	NGroupsFetchMessage::NGroupsFetchMessage()
	{
		// set our default
		envelope.mutable_groups_fetch();
	}

	/* Factory Methods */
	NGroupsFetchMessage::Builder::Builder(std::string groupId)
	{
		Add(groupId);
	}

	NGroupsFetchMessage::Builder NGroupsFetchMessage::Builder::Add(std::string groupId)
	{
		message.envelope.mutable_groups_fetch()->mutable_group_ids()->Add()->assign(groupId);
		return *this;
	}

	NGroupsFetchMessage::Builder NGroupsFetchMessage::Builder::Add(std::vector<std::string> groupIds)
	{
		auto container = message.envelope.mutable_groups_fetch()->mutable_group_ids();
		for (size_t i = 0; i < groupIds.size(); i++)
		{
			container->Add()->assign(groupIds[i]);
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
