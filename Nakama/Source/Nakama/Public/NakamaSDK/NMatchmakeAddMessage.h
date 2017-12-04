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

	// OnSuccess returns: NMatchmakeTicket*
	class NAKAMA_API NMatchmakeAddMessage : public INCollatedMessage
	{

	private:
		Envelope envelope;
		NMatchmakeAddMessage() {}

	public:
		~NMatchmakeAddMessage() {}

		virtual Envelope* GetPayload() override { return &envelope; }
		virtual void SetCollationId(std::string id) override { envelope.set_collation_id(id); }

		static NMatchmakeAddMessage Default(int64_t requiredCount);

		class Builder;
	};

	class NAKAMA_API NMatchmakeAddMessage::Builder
	{
	private:
		NMatchmakeAddMessage message;

	public:
		Builder(int64_t requiredCount);

		Builder AddTermFilter(std::string name, std::vector<std::string> terms, bool matchAllTerms);
		Builder AddRangeFilter(std::string name, int64_t lowerbound, int64_t upperbound);
		Builder AddCheckFilter(std::string name, bool value);

		Builder AddProperty(std::string key, bool value);
		Builder AddProperty(std::string key, int64_t value);
		Builder AddProperty(std::string key, std::vector<std::string> values);

		NMatchmakeAddMessage Build();
	};
}
