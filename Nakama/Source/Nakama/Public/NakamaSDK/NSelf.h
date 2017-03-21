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

#pragma once

#include "Defines.h"
#include "NUser.h"

namespace Nakama {

	class NAKAMA_API NSelf {

	public:
		NSelf(server::Self message) :
			userInfo(message.user()) {

			customId = message.custom_id();
			email = message.email();
			facebookId = message.facebook_id();
			gameCenterId = message.gamecenter_id();
			steamId = message.steam_id();
			verified = message.verified();

			auto msgDevices = message.device_id();
			for (size_t i = 0, maxI = msgDevices.size(); i < maxI; i++) {
				deviceIds.push_back(msgDevices[i]);
			}
		}

		~NSelf() {}

		std::string GetAvatarUrl();
		uint64_t GetCreatedAt();
		std::string GetFullname();
		std::string GetHandle();
		std::string GetId();
		std::string GetLang();
		uint64_t GetLastOnlineAt();
		std::string GetLocation();
		std::string GetMetadata();
		std::string GetTimezone();
		uint64_t GetUpdatedAt();

		std::string GetCustomId() { return customId; }
		std::vector<std::string> GetDeviceIds() { return deviceIds; }
		std::string GetEmail() { return email; }
		std::string GetFacebookId() { return facebookId; }
		std::string GetGameCenterId() { return gameCenterId; }
		std::string GetSteamId() { return steamId; }
		bool IsVerified() { return verified; }

	private:
		NUser userInfo;
		std::string customId;
		std::vector<std::string> deviceIds;
		std::string email;
		std::string facebookId;
		std::string gameCenterId;
		std::string steamId;
		bool verified;
	};

}
