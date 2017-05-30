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

#include "NSelfUpdateMessage.h"

namespace Nakama {

	NSelfUpdateMessage::NSelfUpdateMessage()
	{
		// set our default
		envelope.mutable_self_update();
	}


	/* Factory Methods */
	NSelfUpdateMessage::Builder NSelfUpdateMessage::Builder::AvatarUrl(std::string avatarUrl)
	{
		message.envelope.mutable_self_update()->set_avatar_url(avatarUrl);
		return *this;
	}

	NSelfUpdateMessage::Builder NSelfUpdateMessage::Builder::Handle(std::string handle)
	{
		message.envelope.mutable_self_update()->set_handle(handle);
		return *this;
	}

	NSelfUpdateMessage::Builder NSelfUpdateMessage::Builder::Fullname(std::string fullname)
	{
		message.envelope.mutable_self_update()->set_fullname(fullname);
		return *this;
	}

	NSelfUpdateMessage::Builder NSelfUpdateMessage::Builder::Lang(std::string lang)
	{
		message.envelope.mutable_self_update()->set_lang(lang);
		return *this;
	}

	NSelfUpdateMessage::Builder NSelfUpdateMessage::Builder::Location(std::string location)
	{
		message.envelope.mutable_self_update()->set_location(location);
		return *this;
	}

	NSelfUpdateMessage::Builder NSelfUpdateMessage::Builder::Metadata(std::string metadata)
	{
		message.envelope.mutable_self_update()->set_metadata(metadata);
		return *this;
	}

	NSelfUpdateMessage::Builder NSelfUpdateMessage::Builder::Timezone(std::string timezone)
	{
		message.envelope.mutable_self_update()->set_timezone(timezone);
		return *this;
	}

	NSelfUpdateMessage NSelfUpdateMessage::Builder::Build()
	{
		// Clone object so builder now operates on new copy.
		NSelfUpdateMessage original = message;
		message = NSelfUpdateMessage();
		message.envelope.set_allocated_self_update(new TSelfUpdate(original.envelope.self_update()));
		return original;
	}
}
