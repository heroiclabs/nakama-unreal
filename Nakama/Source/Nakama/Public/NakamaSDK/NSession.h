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

#include <string>
#include <chrono>

namespace Nakama {

	class NAKAMA_API NSession {

	public:
		NSession(std::string token, std::chrono::milliseconds createdAt);

		~NSession() {}

		std::chrono::milliseconds GetCreatedAt() { return createdAt; }
		std::chrono::milliseconds GetExpiresAt() { return expiresAt; }
		std::string GetHandle() { return handle; }
		std::string GetToken() { return token; }
		std::string GetId() { return id; }
		bool HasExpired(std::chrono::milliseconds time);

		static NSession Restore(std::string token);

	private:
		std::chrono::milliseconds createdAt;
		std::chrono::milliseconds expiresAt;
		std::string handle;
		std::string token;
		std::string id;
	};

}
