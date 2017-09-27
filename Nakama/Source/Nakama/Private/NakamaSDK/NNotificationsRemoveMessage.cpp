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

#include "NNotificationsRemoveMessage.h"

namespace Nakama {

	NNotificationsRemoveMessage::NNotificationsRemoveMessage()
	{
		// set our default
		envelope.mutable_notifications_remove();
	}

	/* Factory Methods */

	NNotificationsRemoveMessage::Builder::Builder(std::string leaderboardId) {
		Remove(leaderboardId);
	}
	
	NNotificationsRemoveMessage::Builder::Builder(std::vector<std::string> leaderboardIds) {
		for (int i = 0, maxI = leaderboardIds.size(); i < maxI; i++)
		{
			Remove(leaderboardIds[i]);
		}
	}

	NNotificationsRemoveMessage::Builder NNotificationsRemoveMessage::Builder::Remove(std::string notificationId)
	{
		message.envelope.mutable_notifications_remove()->add_notification_ids()->assign(notificationId);
		return *this;
	}

	NNotificationsRemoveMessage NNotificationsRemoveMessage::Builder::Build()
	{
		// Clone object so builder now operates on new copy.
		NNotificationsRemoveMessage original = message;
		message = NNotificationsRemoveMessage();
		message.envelope.set_allocated_notifications_remove(new TNotificationsRemove(original.envelope.notifications_remove()));
		return original;
	}
}
