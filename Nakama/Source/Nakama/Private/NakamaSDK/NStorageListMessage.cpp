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

#include "NStorageListMessage.h"

namespace Nakama {


	NStorageListMessage::NStorageListMessage()
	{
		// set our default
		envelope.mutable_storage_list();
	}

	/* Factory Methods */

	NStorageListMessage::Builder NStorageListMessage::Builder::Bucket(std::string bucket)
	{
		message.envelope.mutable_storage_list()->set_bucket(bucket);
		return *this;
	}

	NStorageListMessage::Builder NStorageListMessage::Builder::Collection(std::string collection)
	{
		message.envelope.mutable_storage_list()->set_collection(collection);
		return *this;
	}

	NStorageListMessage::Builder NStorageListMessage::Builder::UserId(std::string userId)
	{
		message.envelope.mutable_storage_list()->set_user_id(userId);
		return *this;
	}

	NStorageListMessage::Builder NStorageListMessage::Builder::Limit(int64_t limit)
	{
		message.envelope.mutable_storage_list()->set_limit(limit);
		return *this;
	}

	NStorageListMessage::Builder NStorageListMessage::Builder::Cursor(NCursor cursor)
	{
		message.envelope.mutable_storage_list()->set_cursor(cursor.GetValue());
		return *this;
	}

	NStorageListMessage NStorageListMessage::Builder::Build()
	{
		// Clone object so builder now operates on new copy.
		NStorageListMessage original = message;
		message = NStorageListMessage();
		message.envelope.set_allocated_storage_list(new TStorageList(original.envelope.storage_list()));
		return original;
	}
}
