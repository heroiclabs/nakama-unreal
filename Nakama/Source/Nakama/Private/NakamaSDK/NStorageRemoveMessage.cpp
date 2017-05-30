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

#include "NStorageRemoveMessage.h"

namespace Nakama {

	NStorageRemoveMessage::NStorageRemoveMessage()
	{
		// set our default
		envelope.mutable_storage_remove();
	}

	/* Factory Methods */
	NStorageRemoveMessage::Builder NStorageRemoveMessage::Builder::Remove(std::string bucket, std::string collection, std::string record)
	{
		TStorageRemove* storage_write = message.envelope.mutable_storage_remove();
		TStorageRemove_StorageKey* keys = storage_write->add_keys();
		keys->set_bucket(bucket);
		keys->set_collection(collection);
		keys->set_record(record);

		return *this;
	}

	NStorageRemoveMessage::Builder NStorageRemoveMessage::Builder::Remove(std::string bucket, std::string collection, std::string record, std::string version)
	{
		TStorageRemove* storage_write = message.envelope.mutable_storage_remove();
		TStorageRemove_StorageKey* keys = storage_write->add_keys();
		keys->set_bucket(bucket);
		keys->set_collection(collection);
		keys->set_record(record);
		keys->set_version(version);

		return *this;
	}

	NStorageRemoveMessage NStorageRemoveMessage::Builder::Build()
	{
		// Clone object so builder now operates on new copy.
		NStorageRemoveMessage original = message;
		message = NStorageRemoveMessage();
		message.envelope.set_allocated_storage_remove(new TStorageRemove(original.envelope.storage_remove()));
		return original;
	}
}
