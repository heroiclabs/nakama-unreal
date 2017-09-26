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

#include "NGroupUpdateMessage.h"

namespace Nakama {

	NGroupUpdateMessage::NGroupUpdateMessage()
	{
		// set our default
		envelope.mutable_groups_update();
	}

	/* Factory Methods */
	NGroupUpdateMessage::Builder::Builder(std::string groupId) {

		message.envelope.mutable_groups_update()->add_groups()->set_group_id(groupId);
	}

	NGroupUpdateMessage::Builder NGroupUpdateMessage::Builder::Name(std::string name)
	{
		message.envelope.mutable_groups_update()->mutable_groups()->mutable_data()[0]->set_name(name);
		return *this;
	}

	NGroupUpdateMessage::Builder NGroupUpdateMessage::Builder::Description(std::string description)
	{
		message.envelope.mutable_groups_update()->mutable_groups()->mutable_data()[0]->set_description(description);
		return *this;
	}

	NGroupUpdateMessage::Builder NGroupUpdateMessage::Builder::AvatarUrl(std::string avatarUrl)
	{
		message.envelope.mutable_groups_update()->mutable_groups()->mutable_data()[0]->set_avatar_url(avatarUrl);
		return *this;
	}

	NGroupUpdateMessage::Builder NGroupUpdateMessage::Builder::Lang(std::string lang)
	{
		message.envelope.mutable_groups_update()->mutable_groups()->mutable_data()[0]->set_lang(lang);
		return *this;
	}

	NGroupUpdateMessage::Builder NGroupUpdateMessage::Builder::Metadata(std::string metadata)
	{
		message.envelope.mutable_groups_update()->mutable_groups()->mutable_data()[0]->set_metadata(metadata);
		return *this;
	}

	NGroupUpdateMessage::Builder NGroupUpdateMessage::Builder::Private(bool privateGroup)
	{
		message.envelope.mutable_groups_update()->mutable_groups()->mutable_data()[0]->set_private_(privateGroup);
		return *this;
	}

	NGroupUpdateMessage NGroupUpdateMessage::Builder::Build()
	{
		// Clone object so builder now operates on new copy.
		NGroupUpdateMessage original = message;
		message = NGroupUpdateMessage();
		message.envelope.set_allocated_groups_update(new TGroupsUpdate(original.envelope.groups_update()));
		return original;
	}
}
