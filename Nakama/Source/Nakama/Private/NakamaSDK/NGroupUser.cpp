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

#include "NGroupUser.h"

namespace Nakama {

	std::string NGroupUser::GetAvatarUrl() { return userInfo.GetAvatarUrl(); }
	uint64_t NGroupUser::GetCreatedAt() { return userInfo.GetCreatedAt(); }
	std::string NGroupUser::GetFullname() { return userInfo.GetFullname(); }
	std::string NGroupUser::GetHandle() { return userInfo.GetHandle(); }
	std::string NGroupUser::GetId() { return userInfo.GetId(); }
	std::string NGroupUser::GetLang() { return userInfo.GetLang(); }
	uint64_t NGroupUser::GetLastOnlineAt() { return userInfo.GetLastOnlineAt(); }
	std::string NGroupUser::GetLocation() { return userInfo.GetLocation(); }
	std::string NGroupUser::GetMetadata() { return userInfo.GetMetadata(); }
	std::string NGroupUser::GetTimezone() { return userInfo.GetTimezone(); }
	uint64_t NGroupUser::GetUpdatedAt() { return userInfo.GetUpdatedAt(); }

}
