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

//
// Wrapper around libwebsocket - modified from Unreal's WebSocket.h
//

#pragma once

#include "NakamaPrivatePCH.h"

#include "Defines.h"
#include "NLogger.h"

#include <functional>
#include <string>

namespace Nakama {

	class NWebSocket
	{

	public:
		// Initialize with given url
		NWebSocket(const std::string& host, const unsigned port, const std::string& path, const bool ssl, NLogger* logger);

		// clean up.
		~NWebSocket();

		/************************************************************************/
		/* Set various callbacks for Socket Events                              */
		/************************************************************************/
		void SetConnectedCallBack(NConnUpdateCallback callBack) { ConnectedCallBack = callBack; }
		void SetErrorCallBack(NErrorCallback callBack) { ErrorCallBack = callBack; }
		void SetReceiveCallBack(NDataRcvdCallback callBack) { ReceivedCallBack = callBack; }
		void SetClosedCallBack(NConnUpdateCallback callBack) { ClosedCallBack = callBack; }

		/** Send raw data to remote end point. */
		bool Send(uint8* Data, uint32 Size);

		/** service libwebsocket.			   */
		void Tick();

		/** service libwebsocket until outgoing buffer is empty */
		void Flush();

		/** initiate the websocket connection using the currently set connection info and callbacks */
		void Connect();

		/** Close the websocket                */
		void Close();

		// Fugly! But we are using a static pointer to the logger to get around needing a static method
		// to pass into lws_set_log_level.  I'm guessing a better C++ programmer could do something clever instead.
		static NLogger* logger;

	private:
		static void lwsLogger(int level, const char *line);

		bool isConnecting;

		void HandlePacket();
		void OnRawReceive(void* Data, uint32 Size, uint32 Remaining);
		void OnWebSocketWritable();
		void SetLWSLogLevel();

		std::string Host;
		unsigned Port;
		std::string Path;
		bool UseSSL;

		/************************************************************************/
		/*	Various Socket callbacks											*/
		/************************************************************************/
		NConnUpdateCallback ConnectedCallBack;
		NErrorCallback ErrorCallBack;
		NDataRcvdCallback ReceivedCallBack;
		NConnUpdateCallback ClosedCallBack;

		/**  Recv and Send Buffers, serviced during the Tick */
		std::vector<uint8> ReceivedBuffer;
		TArray<TArray<uint8>> OutgoingBuffer;

		/** libwebsocket internal context*/
		WebSocketInternalContext* Context = nullptr;

		/** libwebsocket web socket */
		WebSocketInternal* LwsConnection = nullptr;

		/** libwebsocket Protocols that can be serviced by this implemenation*/
		WebSocketInternalProtocol* Protocols = nullptr;

		static int unreal_networking_client(WebSocketInternal *Instance, WebSocketInternalCallback reason, void *user, void *in, size_t len);
	};

}
