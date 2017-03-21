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
#include "NGroupsListMessage.h"

namespace Nakama {

	NGroupsListMessage::NGroupsListMessage()
	{
		// set our default
		envelope.mutable_groups_list();
	}

	/* Factory Methods */
	NGroupsListMessage::Builder NGroupsListMessage::Builder::PageLimit(int64_t pageLimit) {
		message.envelope.mutable_groups_list()->set_page_limit(pageLimit);
		return *this;
	}

	NGroupsListMessage::Builder NGroupsListMessage::Builder::OrderByAsc(bool orderByAsc)
	{
		message.envelope.mutable_groups_list()->set_order_by_asc(orderByAsc);
		return *this;
	}

	NGroupsListMessage::Builder NGroupsListMessage::Builder::Cursor(NCursor cursor)
	{
		message.envelope.mutable_groups_list()->set_cursor(cursor.GetValue());
		return *this;
	}

	NGroupsListMessage::Builder NGroupsListMessage::Builder::FilterByLang(std::string lang)
	{
		message.envelope.mutable_groups_list()->set_lang(lang);
		return *this;
	}

	NGroupsListMessage::Builder NGroupsListMessage::Builder::FilterByCreatedAt(int64_t createdAt)
	{
		message.envelope.mutable_groups_list()->set_created_at(createdAt);
		return *this;
	}

	NGroupsListMessage::Builder NGroupsListMessage::Builder::FilterByCount(int64_t count)
	{
		message.envelope.mutable_groups_list()->set_count(count);
		return *this;
	}

	NGroupsListMessage NGroupsListMessage::Builder::Build()
	{
		// Clone object so builder now operates on new copy.
		NGroupsListMessage original = message;
		message = NGroupsListMessage();
		message.envelope.set_allocated_groups_list(new TGroupsList(original.envelope.groups_list()));
		return original;
	}
}
