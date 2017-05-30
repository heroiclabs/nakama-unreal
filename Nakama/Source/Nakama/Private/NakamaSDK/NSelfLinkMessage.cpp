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

#include "NSelfLinkMessage.h"

namespace Nakama {

	NSelfLinkMessage::NSelfLinkMessage(Envelope request)
	{
		envelope = request;
	}

	NSelfLinkMessage NSelfLinkMessage::Custom(std::string id)
	{
		auto newEnvelope = Envelope();
		newEnvelope.mutable_link()->set_custom(id);
		return NSelfLinkMessage(newEnvelope);
	}

	NSelfLinkMessage NSelfLinkMessage::Device(std::string id)
	{
		auto newEnvelope = Envelope();
		newEnvelope.mutable_link()->set_device(id);
		return NSelfLinkMessage(newEnvelope);
	}

	NSelfLinkMessage NSelfLinkMessage::Email(std::string email, std::string password)
	{
		auto newEnvelope = Envelope();
		auto emPass = newEnvelope.mutable_link()->mutable_email();
		emPass->set_email(email);
		emPass->set_password(password);
		return NSelfLinkMessage(newEnvelope);
	}

	NSelfLinkMessage NSelfLinkMessage::Facebook(std::string oauthToken)
	{
		auto newEnvelope = Envelope();
		newEnvelope.mutable_link()->set_facebook(oauthToken);
		return NSelfLinkMessage(newEnvelope);
	}

	NSelfLinkMessage NSelfLinkMessage::GameCenter(std::string playerId,
		std::string bundleId,
		int64_t timestamp,
		std::string salt,
		std::string signature,
		std::string publicKeyUrl)
	{
		auto newEnvelope = Envelope();
		auto gamecenter = newEnvelope.mutable_link()->mutable_game_center();
		gamecenter->set_bundle_id(bundleId);
		gamecenter->set_timestamp(timestamp);
		gamecenter->set_salt(salt);
		gamecenter->set_signature(signature);
		gamecenter->set_public_key_url(publicKeyUrl);
		return NSelfLinkMessage(newEnvelope);
	}

	NSelfLinkMessage NSelfLinkMessage::Google(std::string oauthToken)
	{
		auto newEnvelope = Envelope();
		newEnvelope.mutable_link()->set_google(oauthToken);
		return NSelfLinkMessage(newEnvelope);
	}

	NSelfLinkMessage NSelfLinkMessage::Steam(std::string sessionToken)
	{
		auto newEnvelope = Envelope();
		newEnvelope.mutable_link()->set_steam(sessionToken);
		return NSelfLinkMessage(newEnvelope);
	}

}
