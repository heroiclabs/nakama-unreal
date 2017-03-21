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

using namespace server;

namespace Nakama {

	class NAKAMA_API NAuthenticateMessage
	{
	private:
		AuthenticateRequest* payload;

	public:
		NAuthenticateMessage(AuthenticateRequest* payload);
		~NAuthenticateMessage();

		AuthenticateRequest* GetPayload() { return payload; }

		static NAuthenticateMessage Custom(std::string id);
		static NAuthenticateMessage Device(std::string id);
		static NAuthenticateMessage Email(std::string email, std::string password);
		static NAuthenticateMessage Facebook(std::string oauthToken);
		static NAuthenticateMessage GameCenter(std::string playerId,
			std::string bundleId,
			int64 timestamp,
			std::string salt,
			std::string signature,
			std::string publicKeyUrl);
		static NAuthenticateMessage Google(std::string oauthToken);
		static NAuthenticateMessage Steam(std::string sessionToken);
	};
}
