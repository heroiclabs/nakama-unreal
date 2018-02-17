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

	class NAKAMA_API NLeaderboard {

	public:
		NLeaderboard() {}
		NLeaderboard(Leaderboard message)
		{
			id = message.id();
			authoritative = message.authoritative();
			sort = message.sort();
			count = message.count();
			resetSchedule = message.reset_schedule();
			metadata = message.metadata();
		}

		~NLeaderboard() {}

		std::string GetId() { return id; }
		bool IsAuthoritative() { return authoritative; }
		int64_t GetSort() { return sort; }
		int64_t GetCount() { return count; }
		std::string GetResetSchedule() { return resetSchedule; }
		std::string GetMetadata() { return metadata; }


	private:
		std::string id;
		bool authoritative;
		int64_t sort;
		int64_t count;
		std::string resetSchedule;
		std::string metadata;
	};
}