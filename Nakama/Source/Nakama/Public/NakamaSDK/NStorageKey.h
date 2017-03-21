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

	class NAKAMA_API NStorageKey {

	public:
		NStorageKey(TStorageKey::StorageKey &message) {
			bucket = message.bucket();
			collection = message.collection();
			record = message.record();
			version = message.version();
		}

		~NStorageKey() {}

		std::string GetBucket() { return bucket; }
		std::string GetCollection() { return collection; }
		std::string GetRecord() { return record; }
		std::string GetVersion() { return version; }

	private:
		std::string bucket;
		std::string collection;
		std::string record;
		std::string version;

	};

}