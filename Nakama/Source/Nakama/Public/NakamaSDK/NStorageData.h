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

using namespace server;

// Implementation inlined
namespace Nakama {

	class NAKAMA_API NStorageData {

	public:
		NStorageData(TStorageData::StorageData &message) {
			bucket = message.bucket();
			collection = message.collection();
			record = message.record();
			userId = message.user_id();
			value = message.value();
			version = message.version();
			permissionRead = message.permission_read();
			permissionWrite = message.permission_write();
			createdAt = message.created_at();
			updatedAt = message.updated_at();
			expiresAt = message.expires_at();
		}

		~NStorageData() {}

		std::string GetBucket() { return bucket; }
		std::string GetCollection() { return collection; }
		std::string GetRecord() { return record; }
		std::string GetUserId() { return userId; }
		std::string GetValue() { return value; }
		std::string GetVersion() { return version; }
		int64_t GetPermissionRead() { return permissionRead; }
		int64_t GetPermissionWrite() { return permissionWrite; }
		int64_t GetCreatedAt() { return createdAt; }
		int64_t GetUpdatedAt() { return updatedAt; }
		int64_t GetExpiresAt() { return expiresAt; }

	private:
		std::string bucket;
		std::string collection;
		std::string record;
		std::string userId;
		std::string value;
		std::string version;
		int64_t permissionRead;
		int64_t permissionWrite;
		int64_t createdAt;
		int64_t updatedAt;
		int64_t expiresAt;
	};

}