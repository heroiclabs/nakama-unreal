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
#include <functional>

using namespace server;

namespace Nakama {

	class NAKAMA_API NMatchmakeFilter {
	};

	class NAKAMA_API NMatchmakeTermFilter : public NMatchmakeFilter {

	public:
		NMatchmakeTermFilter() {}
		NMatchmakeTermFilter(MatchmakeFilter_TermFilter filter)
		{
			matchAllTerms = filter.matchallterms();
			for (size_t i = 0; i < filter.terms_size(); i++) {
				terms.push_back(filter.terms(i));
			}
		}

		~NMatchmakeTermFilter() {}

		std::vector<std::string> GetTerms() { return terms; }
		bool IsMatchAllTerms() { return matchAllTerms; }

	private:
		std::vector<std::string> terms;
		bool matchAllTerms;
	};

	class NAKAMA_API NMatchmakeRangeFilter : public NMatchmakeFilter {

	public:
		NMatchmakeRangeFilter() {}
		NMatchmakeRangeFilter(MatchmakeFilter_RangeFilter filter)
		{
			lowerBound = filter.lower_bound();
			upperBound = filter.upper_bound();
		}

		~NMatchmakeRangeFilter() {}

		int64_t GetLowerBound() { return lowerBound; }
		int64_t GetUpperBound() { return upperBound; }

	private:
		int64_t lowerBound;
		int64_t upperBound;
	};

	class NAKAMA_API NMatchmakeCheckFilter : public NMatchmakeFilter {

	public:
		NMatchmakeCheckFilter() {}
		NMatchmakeCheckFilter(bool filter)
		{
			value = filter;
		}

		~NMatchmakeCheckFilter() {}

		bool GetValue() { return value; }

	private:
		bool value;
	};
}