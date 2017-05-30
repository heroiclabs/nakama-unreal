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

#include "NGroupCreateMessage.h"

namespace Nakama {

	NGroupCreateMessage::NGroupCreateMessage()
	{
		// set our default
		envelope.mutable_group_create();
	}

	/* Factory Methods */
	NGroupCreateMessage::Builder::Builder(std::string name) {
		message.envelope.mutable_group_create()->set_name(name);
	}

	NGroupCreateMessage::Builder NGroupCreateMessage::Builder::Description(std::string description)
	{
		message.envelope.mutable_group_create()->set_description(description);
		return *this;
	}

	NGroupCreateMessage::Builder NGroupCreateMessage::Builder::AvatarUrl(std::string avatarUrl)
	{
		message.envelope.mutable_group_create()->set_avatar_url(avatarUrl);
		return *this;
	}

	NGroupCreateMessage::Builder NGroupCreateMessage::Builder::Lang(std::string lang)
	{
		message.envelope.mutable_group_create()->set_lang(lang);
		return *this;
	}

	NGroupCreateMessage::Builder NGroupCreateMessage::Builder::Metadata(std::string metadata)
	{
		message.envelope.mutable_group_create()->set_metadata(metadata);
		return *this;
	}

	NGroupCreateMessage::Builder NGroupCreateMessage::Builder::Private(bool privateGroup)
	{
		message.envelope.mutable_group_create()->set_private_(privateGroup);
		return *this;
	}

	NGroupCreateMessage NGroupCreateMessage::Builder::Build()
	{
		// Clone object so builder now operates on new copy.
		NGroupCreateMessage original = message;
		message = NGroupCreateMessage();
		message.envelope.set_allocated_group_create(new TGroupCreate(original.envelope.group_create()));
		return original;
	}
}
