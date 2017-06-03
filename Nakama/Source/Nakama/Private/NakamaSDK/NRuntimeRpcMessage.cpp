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

#include "NRuntimeRpcMessage.h"

namespace Nakama {

	NRuntimeRpcMessage::NRuntimeRpcMessage()
	{
		// set our default
		envelope.mutable_rpc();
	}

	/* Factory Methods */
	NRuntimeRpcMessage::Builder::Builder(std::string id) {
		message.envelope.mutable_rpc()->set_id(id);
	}

	NRuntimeRpcMessage::Builder NRuntimeRpcMessage::Builder::Payload(std::string payload)
	{
		message.envelope.mutable_rpc()->set_payload(payload);
		return *this;
	}

	NRuntimeRpcMessage NRuntimeRpcMessage::Builder::Build()
	{
		// Clone object so builder now operates on new copy.
		NRuntimeRpcMessage original = message;
		message = NRuntimeRpcMessage();
		message.envelope.set_allocated_rpc(new TRpc(original.envelope.rpc()));
		return original;
	}
}