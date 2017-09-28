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

#include "INCollatedMessage.h"

#include "Defines.h"

using namespace server;

namespace Nakama {

	// OnSuccess returns: NResultSet<NStorageKey>*
	class NAKAMA_API NStorageUpdateMessage : public INCollatedMessage
	{
	private:
		Envelope envelope;
		NStorageUpdateMessage();

	public:
		~NStorageUpdateMessage() {}

		virtual Envelope* GetPayload() override { return &envelope; }
		virtual void SetCollationId(std::string id) override { envelope.set_collation_id(id); }

		class Builder;
		class StorageUpdateBuilder;
	};

	class NAKAMA_API NStorageUpdateMessage::Builder
	{
	private:
		NStorageUpdateMessage message;

	public:
		Builder() {}

		Builder Update(std::string bucket, std::string collection, std::string record, std::vector<TStorageUpdate_StorageUpdate_UpdateOp> ops);
		Builder Update(std::string bucket, std::string collection, std::string record, std::string version, StoragePermissionRead readPermission, StoragePermissionWrite writePermission, std::vector<TStorageUpdate_StorageUpdate_UpdateOp> ops);

		NStorageUpdateMessage Build();
	};

	class NAKAMA_API NStorageUpdateMessage::StorageUpdateBuilder
	{
	private:
		std::vector<TStorageUpdate_StorageUpdate_UpdateOp> ops;

	public:
		StorageUpdateBuilder() {}

		static int GetOpCode(TStorageUpdate_StorageUpdate_UpdateOp_UpdateOpCode code);
		StorageUpdateBuilder Add(std::string path, std::string value);
		StorageUpdateBuilder Append(std::string path, std::string value);
		StorageUpdateBuilder Copy(std::string from, std::string path);
		StorageUpdateBuilder Incr(std::string path, int64_t value);
		StorageUpdateBuilder Init(std::string path, std::string value);
		StorageUpdateBuilder Merge(std::string path, std::string value);
		StorageUpdateBuilder Move(std::string path, std::string value);
//		StorageUpdateBuilder Patch(std::string path, std::string value); // TODO
		StorageUpdateBuilder Remove(std::string path);
		StorageUpdateBuilder Replace(std::string path, std::string value);
		StorageUpdateBuilder Test(std::string path, std::string value);
		StorageUpdateBuilder Compare(std::string path, std::string value, int64_t assert);

		std::vector<TStorageUpdate_StorageUpdate_UpdateOp> Build();
	};
}
