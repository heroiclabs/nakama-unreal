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

#include "NCursor.h"

// Implementation inlined
namespace Nakama {

	template <class T>
	class NAKAMA_API NResultSet {

	public:
		NResultSet(std::vector<T> &res, NCursor cur) :
			results(res),
			cursor(cur) {}

		~NResultSet() {}

		std::vector<T> GetResults() { return results; }
		NCursor GetCursor() { return cursor; }
		int32 Size() { return results.size(); }

		T operator [](int i)
		{
			return results[i];
		}

	private:
		std::vector<T> results;
		NCursor cursor;

	};
}