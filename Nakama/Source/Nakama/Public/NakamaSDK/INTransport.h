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
#include "NLogger.h"

#include <functional>

using namespace server;

namespace Nakama {

	class INTransport
	{

	public:

		/************************************************************************/
		/* Set various callbacks for Events										*/
		/************************************************************************/
		void SetOnConnectCallBack(NConnUpdateCallback callBack) { ConnectCallback = callBack; }
		void SetOnCloseCallBack(NConnUpdateCallback callBack) { CloseCallback = callBack; }
		void SetOnErrorCallBack(NErrorCallback callBack) { ErrorCallback = callBack; }
		void SetOnMessageCallBack(NDataRcvdCallback callBack) { MessageReceiveCallback = callBack; }

		virtual void Post(std::string uri,
			AuthenticateRequest* payload,
			std::string authHeader,
			std::string langHeader,
			unsigned timeout,
			unsigned connectTimeout,
			const std::function<void(const std::vector<uint8_t> &)> &successAction,
			const std::function<void(const int32 &)> &errorAction) = 0;

		virtual void Connect(const std::string host, const unsigned port, const std::string& path, const bool ssl) = 0;
		virtual void Close() = 0;
		virtual void Send(std::string data) = 0;
		virtual void Tick(float DeltaTime) = 0;
	
	protected:
		NLogger* logger;

		/************************************************************************/
		/*	Various callbacks													*/
		/************************************************************************/
		NConnUpdateCallback ConnectCallback;
		NConnUpdateCallback CloseCallback;
		NErrorCallback ErrorCallback;
		NDataRcvdCallback MessageReceiveCallback;

	};

}
