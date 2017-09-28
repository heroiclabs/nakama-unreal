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

#include "NStorageUpdateMessage.h"

namespace Nakama {

	NStorageUpdateMessage::NStorageUpdateMessage()
	{
		// set our default
		envelope.mutable_storage_update();
	}

	/* Factory Methods */

	NStorageUpdateMessage::Builder NStorageUpdateMessage::Builder::Update(std::string bucket, std::string collection, std::string record, std::vector<TStorageUpdate_StorageUpdate_UpdateOp> ops)
	{
		auto update = message.envelope.mutable_storage_update()->add_updates();
		update->mutable_key()->set_bucket(bucket);
		update->mutable_key()->set_collection(collection);
		update->mutable_key()->set_record(record);
		for (int i = 0, maxI = ops.size(); i < maxI; i++)
		{
			update->mutable_ops()->Add()->MergeFrom(ops[i]);
		}

		return *this;
	}

	NStorageUpdateMessage::Builder NStorageUpdateMessage::Builder::Update(std::string bucket, std::string collection, std::string record, std::string version, StoragePermissionRead readPermission, StoragePermissionWrite writePermission, std::vector<TStorageUpdate_StorageUpdate_UpdateOp> ops)
	{
		auto update = message.envelope.mutable_storage_update()->add_updates();
		update->mutable_key()->set_bucket(bucket);
		update->mutable_key()->set_collection(collection);
		update->mutable_key()->set_record(record);
		update->mutable_key()->set_version(version);
		for (int i = 0, maxI = ops.size(); i < maxI; i++)
		{
			update->mutable_ops()->Add()->MergeFrom(ops[i]);
		}
		update->set_permission_read(readPermission);
		update->set_permission_write(writePermission);

		return *this;
	}

	NStorageUpdateMessage NStorageUpdateMessage::Builder::Build()
	{
		// Clone object so builder now operates on new copy.
		NStorageUpdateMessage original = message;
		message = NStorageUpdateMessage();
		message.envelope.set_allocated_storage_update(new TStorageUpdate(original.envelope.storage_update()));
		return original;
	}


	int NStorageUpdateMessage::StorageUpdateBuilder::GetOpCode(TStorageUpdate_StorageUpdate_UpdateOp_UpdateOpCode code)
	{
		switch (code)
		{
		case TStorageUpdate_StorageUpdate_UpdateOp_UpdateOpCode::TStorageUpdate_StorageUpdate_UpdateOp_UpdateOpCode_ADD:
			return 0;
		case TStorageUpdate_StorageUpdate_UpdateOp_UpdateOpCode::TStorageUpdate_StorageUpdate_UpdateOp_UpdateOpCode_APPEND:
			return 1;
		case TStorageUpdate_StorageUpdate_UpdateOp_UpdateOpCode::TStorageUpdate_StorageUpdate_UpdateOp_UpdateOpCode_COPY:
			return 2;
		case TStorageUpdate_StorageUpdate_UpdateOp_UpdateOpCode::TStorageUpdate_StorageUpdate_UpdateOp_UpdateOpCode_INCR:
			return 3;
		case TStorageUpdate_StorageUpdate_UpdateOp_UpdateOpCode::TStorageUpdate_StorageUpdate_UpdateOp_UpdateOpCode_INIT:
			return 4;
		case TStorageUpdate_StorageUpdate_UpdateOp_UpdateOpCode::TStorageUpdate_StorageUpdate_UpdateOp_UpdateOpCode_MERGE:
			return 5;
		case TStorageUpdate_StorageUpdate_UpdateOp_UpdateOpCode::TStorageUpdate_StorageUpdate_UpdateOp_UpdateOpCode_MOVE:
			return 6;
		case TStorageUpdate_StorageUpdate_UpdateOp_UpdateOpCode::TStorageUpdate_StorageUpdate_UpdateOp_UpdateOpCode_PATCH:
			return 7;
		case TStorageUpdate_StorageUpdate_UpdateOp_UpdateOpCode::TStorageUpdate_StorageUpdate_UpdateOp_UpdateOpCode_REMOVE:
			return 8;
		case TStorageUpdate_StorageUpdate_UpdateOp_UpdateOpCode::TStorageUpdate_StorageUpdate_UpdateOp_UpdateOpCode_REPLACE:
			return 9;
		case TStorageUpdate_StorageUpdate_UpdateOp_UpdateOpCode::TStorageUpdate_StorageUpdate_UpdateOp_UpdateOpCode_TEST:
			return 10;
		case TStorageUpdate_StorageUpdate_UpdateOp_UpdateOpCode::TStorageUpdate_StorageUpdate_UpdateOp_UpdateOpCode_COMPARE:
			return 11;
		default:
			return -1; // make sure server rejects it
		}
	}

	NStorageUpdateMessage::StorageUpdateBuilder NStorageUpdateMessage::StorageUpdateBuilder::Add(std::string path, std::string value)
	{
		TStorageUpdate_StorageUpdate_UpdateOp op;
		op.set_op(GetOpCode(TStorageUpdate_StorageUpdate_UpdateOp_UpdateOpCode_ADD));
		op.set_path(path);
		op.set_value(value);
		ops.push_back(op);
		return *this;
	}

	NStorageUpdateMessage::StorageUpdateBuilder NStorageUpdateMessage::StorageUpdateBuilder::Append(std::string path, std::string value)
	{
		TStorageUpdate_StorageUpdate_UpdateOp op;
		op.set_op(GetOpCode(TStorageUpdate_StorageUpdate_UpdateOp_UpdateOpCode_APPEND));
		op.set_path(path);
		op.set_value(value);
		ops.push_back(op);
		return *this;
	}

	NStorageUpdateMessage::StorageUpdateBuilder NStorageUpdateMessage::StorageUpdateBuilder::Copy(std::string from, std::string path)
	{
		TStorageUpdate_StorageUpdate_UpdateOp op;
		op.set_op(GetOpCode(TStorageUpdate_StorageUpdate_UpdateOp_UpdateOpCode_COPY));
		op.set_from(from);
		op.set_path(path);
		ops.push_back(op);
		return *this;
	}

	NStorageUpdateMessage::StorageUpdateBuilder NStorageUpdateMessage::StorageUpdateBuilder::Incr(std::string path, int64_t value)
	{
		TStorageUpdate_StorageUpdate_UpdateOp op;
		op.set_op(GetOpCode(TStorageUpdate_StorageUpdate_UpdateOp_UpdateOpCode_INCR));
		op.set_path(path);
		op.set_value(std::to_string(value));
		ops.push_back(op);
		return *this;
	}

	NStorageUpdateMessage::StorageUpdateBuilder NStorageUpdateMessage::StorageUpdateBuilder::Init(std::string path, std::string value)
	{
		TStorageUpdate_StorageUpdate_UpdateOp op;
		op.set_op(GetOpCode(TStorageUpdate_StorageUpdate_UpdateOp_UpdateOpCode_INIT));
		op.set_path(path);
		op.set_value(value);
		ops.push_back(op);
		return *this;
	}

	NStorageUpdateMessage::StorageUpdateBuilder NStorageUpdateMessage::StorageUpdateBuilder::Merge(std::string path, std::string value)
	{
		TStorageUpdate_StorageUpdate_UpdateOp op;
		op.set_op(GetOpCode(TStorageUpdate_StorageUpdate_UpdateOp_UpdateOpCode_MERGE));
		op.set_path(path);
		op.set_value(value);
		ops.push_back(op);
		return *this;
	}

	NStorageUpdateMessage::StorageUpdateBuilder NStorageUpdateMessage::StorageUpdateBuilder::Move(std::string from, std::string path)
	{
		TStorageUpdate_StorageUpdate_UpdateOp op;
		op.set_op(GetOpCode(TStorageUpdate_StorageUpdate_UpdateOp_UpdateOpCode_MOVE));
		op.set_from(from);
		op.set_path(path);
		ops.push_back(op);
		return *this;
	}

	NStorageUpdateMessage::StorageUpdateBuilder NStorageUpdateMessage::StorageUpdateBuilder::Remove(std::string path)
	{
		TStorageUpdate_StorageUpdate_UpdateOp op;
		op.set_op(GetOpCode(TStorageUpdate_StorageUpdate_UpdateOp_UpdateOpCode_REMOVE));
		op.set_path(path);
		ops.push_back(op);
		return *this;
	}

	NStorageUpdateMessage::StorageUpdateBuilder NStorageUpdateMessage::StorageUpdateBuilder::Replace(std::string path, std::string value)
	{
		TStorageUpdate_StorageUpdate_UpdateOp op;
		op.set_op(GetOpCode(TStorageUpdate_StorageUpdate_UpdateOp_UpdateOpCode_REPLACE));
		op.set_path(path);
		op.set_value(value);
		ops.push_back(op);
		return *this;
	}

	NStorageUpdateMessage::StorageUpdateBuilder NStorageUpdateMessage::StorageUpdateBuilder::Test(std::string path, std::string value)
	{
		TStorageUpdate_StorageUpdate_UpdateOp op;
		op.set_op(GetOpCode(TStorageUpdate_StorageUpdate_UpdateOp_UpdateOpCode_TEST));
		op.set_path(path);
		op.set_value(value);
		ops.push_back(op);
		return *this;
	}

	NStorageUpdateMessage::StorageUpdateBuilder NStorageUpdateMessage::StorageUpdateBuilder::Compare(std::string path, std::string value, int64_t assert)
	{
		TStorageUpdate_StorageUpdate_UpdateOp op;
		op.set_op(GetOpCode(TStorageUpdate_StorageUpdate_UpdateOp_UpdateOpCode_COMPARE));
		op.set_path(path);
		op.set_value(value);
		op.set_assert(assert);
		ops.push_back(op);
		return *this;
	}

	std::vector<TStorageUpdate_StorageUpdate_UpdateOp> NStorageUpdateMessage::StorageUpdateBuilder::Build()
	{
		return ops;
	}
}
