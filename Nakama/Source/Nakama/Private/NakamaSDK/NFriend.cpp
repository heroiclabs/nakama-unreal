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

#include "NFriend.h"

namespace Nakama {

	std::string NFriend::GetAvatarUrl() { return userInfo.GetAvatarUrl(); }
	uint64_t NFriend::GetCreatedAt() { return userInfo.GetCreatedAt(); }
	std::string NFriend::GetFullname() { return userInfo.GetFullname(); }
	std::string NFriend::GetHandle() { return userInfo.GetHandle(); }
	std::string NFriend::GetId() { return userInfo.GetId(); }
	std::string NFriend::GetLang() { return userInfo.GetLang(); }
	uint64_t NFriend::GetLastOnlineAt() { return userInfo.GetLastOnlineAt(); }
	std::string NFriend::GetLocation() { return userInfo.GetLocation(); }
	std::string NFriend::GetMetadata() { return userInfo.GetMetadata(); }
	std::string NFriend::GetTimezone() { return userInfo.GetTimezone(); }
	uint64_t NFriend::GetUpdatedAt() { return userInfo.GetUpdatedAt(); }

}
