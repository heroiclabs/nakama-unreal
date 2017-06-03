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

namespace Nakama {

	class NAKAMA_API NRuntimeRpc {

	public:
		NRuntimeRpc() {}
		NRuntimeRpc(TRpc message)
		{
			id = message.id();
			payload = message.payload();
		}

		~NRuntimeRpc() {}

		std::string GetId() { return id; }
		std::string GetPayload() { return payload; }

	private:
		std::string id;
		std::string payload;
	};
}