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

#include "NMatchmakeAddMessage.h"

namespace Nakama {

	NMatchmakeAddMessage NMatchmakeAddMessage::Default(int64_t requiredCount)
	{
		return Builder(requiredCount).Build();
	}


	/* Factory Methods */
	NMatchmakeAddMessage::Builder::Builder(int64_t requiredCount) {
		message.envelope.mutable_matchmake_add()->set_required_count(requiredCount);
	}

	NMatchmakeAddMessage::Builder NMatchmakeAddMessage::Builder::AddTermFilter(std::string name, std::vector<std::string> terms, bool matchAllTerms)
	{
		auto filter = message.envelope.mutable_matchmake_add()->mutable_filters()->Add();
		filter->set_name(name);
		filter->mutable_term()->set_matchallterms(matchAllTerms);
		for (size_t i = 0, maxI = terms.size(); i < maxI; i++) filter->mutable_term()->mutable_terms()->Add()->assign(terms[i]);
		return *this;
	}

	NMatchmakeAddMessage::Builder NMatchmakeAddMessage::Builder::AddRangeFilter(std::string name, int64_t lowerbound, int64_t upperbound)
	{
		auto filter = message.envelope.mutable_matchmake_add()->mutable_filters()->Add();
		filter->set_name(name);
		filter->mutable_range()->set_lower_bound(lowerbound);
		filter->mutable_range()->set_upper_bound(upperbound);
		return *this;
	}

	NMatchmakeAddMessage::Builder NMatchmakeAddMessage::Builder::AddCheckFilter(std::string name, bool value)
	{
		auto filter = message.envelope.mutable_matchmake_add()->mutable_filters()->Add();
		filter->set_name(name);
		filter->set_check(value);
		return *this;
	}

	NMatchmakeAddMessage::Builder NMatchmakeAddMessage::Builder::AddProperty(std::string key, bool value)
	{
		auto prop = message.envelope.mutable_matchmake_add()->mutable_properties()->Add();
		prop->set_key(key);
		prop->set_boolvalue(value);
		return *this;
	}

	NMatchmakeAddMessage::Builder NMatchmakeAddMessage::Builder::AddProperty(std::string key, int64_t value)
	{
		auto prop = message.envelope.mutable_matchmake_add()->mutable_properties()->Add();
		prop->set_key(key);
		prop->set_intvalue(value);
		return *this;
	}

	NMatchmakeAddMessage::Builder NMatchmakeAddMessage::Builder::AddProperty(std::string key, std::vector<std::string> values)
	{
		auto prop = message.envelope.mutable_matchmake_add()->mutable_properties()->Add();
		prop->set_key(key);
		for (size_t i = 0, maxI = values.size(); i < maxI; i++) prop->mutable_stringset()->mutable_values()->Add()->assign(values[i]);
		return *this;
	}

	NMatchmakeAddMessage NMatchmakeAddMessage::Builder::Build()
	{
		// Clone object so builder now operates on new copy.
		NMatchmakeAddMessage original = message;
		message = NMatchmakeAddMessage();
		message.envelope.set_allocated_matchmake_add(new TMatchmakeAdd(original.envelope.matchmake_add()));
		return original;
	}
}
