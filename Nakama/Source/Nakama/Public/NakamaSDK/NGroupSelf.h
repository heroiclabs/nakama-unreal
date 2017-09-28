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
#include "NGroup.h"

namespace Nakama {
	
	enum class NAKAMA_API GroupState : uint8 { Admin = 0, Member, Join };

	class NAKAMA_API NGroupSelf : public NGroup {

	public:
		NGroupSelf() {}
		NGroupSelf(server::TGroupsSelf_GroupSelf message) : NGroup(message.group()) {
			switch (message.state())
			{
			case 0:
				state = GroupState::Admin;
				break;
			case 1:
				state = GroupState::Member;
				break;
			case 2:
				state = GroupState::Join;
				break;
			}
		}

		~NGroupSelf() {}

		GroupState GetState() { return state; }

	private:
		GroupState state;
	};

}
