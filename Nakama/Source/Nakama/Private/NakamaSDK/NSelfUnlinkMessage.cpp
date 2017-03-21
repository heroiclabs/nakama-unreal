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
#include "NSelfUnlinkMessage.h"

namespace Nakama {

	NSelfUnlinkMessage::NSelfUnlinkMessage(Envelope request)
	{
		envelope = request;
	}

	NSelfUnlinkMessage NSelfUnlinkMessage::Custom(std::string id)
	{
		auto newEnvelope = Envelope();
		newEnvelope.mutable_unlink()->set_custom(id);
		return NSelfUnlinkMessage(newEnvelope);
	}

	NSelfUnlinkMessage NSelfUnlinkMessage::Device(std::string id)
	{
		auto newEnvelope = Envelope();
		newEnvelope.mutable_unlink()->set_device(id);
		return NSelfUnlinkMessage(newEnvelope);
	}

	NSelfUnlinkMessage NSelfUnlinkMessage::Email(std::string email)
	{
		auto newEnvelope = Envelope();
		newEnvelope.mutable_unlink()->set_email(email);
		return NSelfUnlinkMessage(newEnvelope);
	}

	NSelfUnlinkMessage NSelfUnlinkMessage::Facebook(std::string id)
	{
		auto newEnvelope = Envelope();
		newEnvelope.mutable_unlink()->set_facebook(id);
		return NSelfUnlinkMessage(newEnvelope);
	}

	NSelfUnlinkMessage NSelfUnlinkMessage::GameCenter(std::string id)
	{
		auto newEnvelope = Envelope();
		newEnvelope.mutable_unlink()->set_game_center(id);
		return NSelfUnlinkMessage(newEnvelope);
	}

	NSelfUnlinkMessage NSelfUnlinkMessage::Google(std::string id)
	{
		auto newEnvelope = Envelope();
		newEnvelope.mutable_unlink()->set_google(id);
		return NSelfUnlinkMessage(newEnvelope);
	}

	NSelfUnlinkMessage NSelfUnlinkMessage::Steam(std::string id)
	{
		auto newEnvelope = Envelope();
		newEnvelope.mutable_unlink()->set_steam(id);
		return NSelfUnlinkMessage(newEnvelope);
	}
}
