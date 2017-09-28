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

	NNotificationsRemoveMessage NNotificationsRemoveMessage::Default(std::string notificationId) {
		NNotificationsRemoveMessage message;
		message.envelope.mutable_notifications_remove()->add_notification_ids()->assign(notificationId);
		return message;
	}

	NNotificationsRemoveMessage NNotificationsRemoveMessage::Default(std::vector<std::string> notificationIds) {
		NNotificationsRemoveMessage message;
		for (int i = 0, maxI = notificationIds.size(); i < maxI; i++)
		{
			message.envelope.mutable_notifications_remove()->add_notification_ids()->assign(notificationIds[i]);
		}
		return message;
	}
}
