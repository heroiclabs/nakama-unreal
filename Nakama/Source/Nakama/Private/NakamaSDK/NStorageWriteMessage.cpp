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

#include "NStorageWriteMessage.h"

namespace Nakama {

	NStorageWriteMessage::NStorageWriteMessage()
	{
		// set our default
		envelope.mutable_storage_write();
	}

	/* Factory Methods */
	NStorageWriteMessage::Builder NStorageWriteMessage::Builder::Write(std::string bucket, std::string collection, std::string record, std::string value, StoragePermissionRead readPermission, StoragePermissionWrite writePermission, std::string version)
	{
		TStorageWrite* storage_write = message.envelope.mutable_storage_write();
		TStorageWrite_StorageData* data = storage_write->add_data();
		data->set_bucket(bucket);
		data->set_collection(collection);
		data->set_record(record);
		data->set_value(value);
		data->set_permission_read(readPermission);
		data->set_permission_write(writePermission);
		if (!version.empty()) data->set_version(version);

		return *this;
	}

	NStorageWriteMessage NStorageWriteMessage::Builder::Build()
	{
		// Clone object so builder now operates on new copy.
		NStorageWriteMessage original = message;
		message = NStorageWriteMessage();
		message.envelope.set_allocated_storage_write(new TStorageWrite(original.envelope.storage_write()));
		return original;
	}
}
