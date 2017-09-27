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

#include "NNotificationsListMessage.h"

namespace Nakama {

	NNotificationsListMessage::NNotificationsListMessage()
	{
		// set our default
		envelope.mutable_notifications_list();
	}

	/* Factory Methods */
	NNotificationsListMessage::Builder NNotificationsListMessage::Builder::Limit(int64_t limit)
	{
		message.envelope.mutable_notifications_list()->set_limit(limit);
		return *this;
	}

	NNotificationsListMessage::Builder NNotificationsListMessage::Builder::ResumableCursor(std::string resumableCursor)
	{
		message.envelope.mutable_notifications_list()->set_resumable_cursor(resumableCursor);
		return *this;
	}

	NNotificationsListMessage NNotificationsListMessage::Builder::Build()
	{
		// Clone object so builder now operates on new copy.
		NNotificationsListMessage original = message;
		message = NNotificationsListMessage();
		message.envelope.set_allocated_notifications_list(new TNotificationsList(original.envelope.notifications_list()));
		return original;
	}
}
