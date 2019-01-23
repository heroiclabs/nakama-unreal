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

#include "NAuthenticateMessage.h"

namespace Nakama {

	NAuthenticateMessage::NAuthenticateMessage(AuthenticateRequest* payload)
	{
		this->payload = payload;
	}

	NAuthenticateMessage::~NAuthenticateMessage()
	{
	}

	NAuthenticateMessage NAuthenticateMessage::Custom(std::string id)
	{
		AuthenticateRequest* payload = new AuthenticateRequest();
		payload->set_custom(id);
		return NAuthenticateMessage(payload);
	}

	NAuthenticateMessage NAuthenticateMessage::Device(std::string id)
	{
		AuthenticateRequest* payload = new AuthenticateRequest();
		payload->set_device(id);
		return NAuthenticateMessage(payload);
	}

	NAuthenticateMessage NAuthenticateMessage::Email(std::string email, std::string password)
	{
		AuthenticateRequest* payload = new AuthenticateRequest();
		AuthenticateRequest_Email* emailObj = new AuthenticateRequest_Email();
		emailObj->set_email(email);
		emailObj->set_password(password);
		payload->set_allocated_email(emailObj);
		return NAuthenticateMessage(payload);
	}

	NAuthenticateMessage NAuthenticateMessage::Facebook(std::string oauthToken)
	{
		AuthenticateRequest* payload = new AuthenticateRequest();
		payload->set_facebook(oauthToken);
		return NAuthenticateMessage(payload);
	}

	NAuthenticateMessage NAuthenticateMessage::GameCenter(std::string playerId, std::string bundleId, int64 timestamp, std::string salt, std::string signature, std::string publicKeyUrl)
	{
		AuthenticateRequest* payload = new AuthenticateRequest();
		AuthenticateRequest_GameCenter* gameCenter = new AuthenticateRequest_GameCenter();
		gameCenter->set_player_id(playerId);
		gameCenter->set_bundle_id(bundleId);
		gameCenter->set_timestamp(timestamp);
		gameCenter->set_salt(salt);
		gameCenter->set_signature(signature);
		gameCenter->set_public_key_url(publicKeyUrl);
		payload->set_allocated_game_center(gameCenter);
		return NAuthenticateMessage(payload);
	}

	NAuthenticateMessage NAuthenticateMessage::Google(std::string oauthToken)
	{
		AuthenticateRequest* payload = new AuthenticateRequest();
		payload->set_google(oauthToken);
		return NAuthenticateMessage(payload);
	}

	NAuthenticateMessage NAuthenticateMessage::Steam(std::string sessionToken)
	{
		AuthenticateRequest* payload = new AuthenticateRequest();
		payload->set_steam(sessionToken);
		return NAuthenticateMessage(payload);
	}
}
