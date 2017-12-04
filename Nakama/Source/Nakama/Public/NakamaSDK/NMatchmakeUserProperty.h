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
#include "NMatchmakeFilter.h"
#include <functional>

#pragma push_macro("check")
#undef check

using namespace server;

namespace Nakama {

	class NAKAMA_API NMatchmakeUserProperty {

	public:
		NMatchmakeUserProperty() {}
		NMatchmakeUserProperty(MatchmakeMatched_UserProperty message)
		{
			id = message.user_id();
			auto msgProperties = message.properties();
			for (size_t i = 0, maxI = msgProperties.size(); i < maxI; i++) {
				auto item = msgProperties.Get(i);
				switch (item.value_case()) {
				case PropertyPair::ValueCase::kStringSet: {
					std::vector<std::string> terms;
					auto stringset = item.stringset();
					for (size_t j = 0, maxJ = stringset.values_size(); j < maxJ; j++) {
						terms.push_back(stringset.values().Get(j));
					}
					stringSetProperties[item.key()] = terms;
					break;
				}
				case PropertyPair::ValueCase::kIntValue: {
					intProperties[item.key()] = item.intvalue();
					break;
				}
				case PropertyPair::ValueCase::kBoolValue: {
					boolProperties[item.key()] = item.boolvalue();
					break;
				}
				}
			}

			auto msgFilters = message.filters();
			for (size_t i = 0, maxI = msgFilters.size(); i < maxI; i++) {
				auto item = msgFilters.Get(i);
				switch (item.value_case()) {
				case MatchmakeFilter::ValueCase::kTerm:
					filters[item.name()] = new NMatchmakeTermFilter(item.term());
					break;
				case MatchmakeFilter::ValueCase::kRange:
					filters[item.name()] = new NMatchmakeRangeFilter(item.range());
					break;
				case MatchmakeFilter::ValueCase::kCheck:
					filters[item.name()] = new NMatchmakeCheckFilter(item.check());
					break;
				}
			}
		}

		~NMatchmakeUserProperty() {}

		std::string GetId() { return id; }
		std::map<std::string, std::vector<std::string>> GetStringSetProperties() { return stringSetProperties; }
		std::map<std::string, int64_t> GetIntProperties() { return intProperties; }
		std::map<std::string, bool> GetBoolProperties() { return boolProperties; }
		std::map<std::string, NMatchmakeFilter*> GetFilters() { return filters; }

	private:
		std::string id;

		std::map<std::string, std::vector<std::string>> stringSetProperties;
		std::map<std::string, int64_t> intProperties;
		std::map<std::string, bool> boolProperties;

		std::map<std::string, NMatchmakeFilter*> filters;
	};
}

#pragma pop_macro("check")