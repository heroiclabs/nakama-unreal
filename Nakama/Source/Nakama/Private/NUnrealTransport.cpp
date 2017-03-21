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

#include "NakamaPrivatePCH.h"
#include "NUnrealTransport.h"
#include "NUnrealLogSink.h"

#include "App.h"

namespace Nakama {
	NUnrealTransport::NUnrealTransport(NLogger* logger)
	{
		this->logger = logger;
	}

	NUnrealTransport::~NUnrealTransport()
	{
		if (socket) delete socket;
	}

	void NUnrealTransport::Post(std::string uri, AuthenticateRequest* payload, std::string authHeader, std::string langHeader, unsigned timeout, unsigned connectTimeout,
		const std::function<void(const std::vector<uint8_t> &)> &successAction,
		const std::function<void(const int32 &)> &errorAction)
	{
		logger->Format(Info, "Nakama::NTransport->Post() - '%s'", uri.c_str());
		HttpRequest->SetURL(uri.c_str());
		HttpRequest->SetVerb(TEXT("POST"));
		HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/octet-stream;"));
		HttpRequest->SetHeader(TEXT("Accept"), TEXT("application/octet-stream;"));

		// Add Headers
		FString agent = TEXT("nakama-unrealsdk/");
		agent += FApp::GetBuildVersion();
		HttpRequest->SetHeader(TEXT("User-Agent"), agent);
		HttpRequest->SetHeader(TEXT("Authorization"), authHeader.c_str());
		HttpRequest->SetHeader(TEXT("Accept-Language"), langHeader.c_str());

		// Optimise request
		//HttpRequest->Timeout = unchecked((int)connectTimeout);
		//HttpRequest->ReadWriteTimeout = unchecked((int)timeout);
		//HttpRequest->KeepAlive = true;
		//HttpRequest->Proxy = null;

		// Pack payload
		HttpRequest->SetContentAsString(payload->SerializeAsString().c_str());

		// Set up callback for response
		HttpRequest->OnProcessRequestComplete().BindLambda(
			[successAction, errorAction](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
			if (bWasSuccessful)
			{
				if (successAction) {
					// alas, we have to convert our Unreal array to a std::vector. :(
					TArray<uint8> content = Response->GetContent();
					int32 contentLength = content.Num();
					std::vector<uint8_t> rVal = std::vector<uint8_t>(contentLength);
					for (size_t i = 0; i < contentLength; i++)
					{
						rVal[i] = content[i];
					}
					successAction(rVal);
				}
			}
			else
			{
				if (errorAction) errorAction(Response.IsValid() ? Response->GetResponseCode() : -1);
			}
		});

		// Kick off processing
		HttpRequest->ProcessRequest();
	}

	void NUnrealTransport::CreateWebSocket(const std::string host, const unsigned port, const std::string& path, const bool ssl)
	{
		socket = new NWebSocket(host, port, path, ssl, logger);

		// OnConnect callback
		socket->SetConnectedCallBack([=]() { 
			if (ConnectCallback) ConnectCallback(); 
		});

		// OnClosed callback + cleanup
		socket->SetClosedCallBack([=]() { 
			// Release socket handle
			if (socket) {
				delete socket;
				socket = nullptr;
			}
			logger->Trace("Socket Closed.");
			if (CloseCallback) CloseCallback(); 
		});

		// OnError callback
		socket->SetErrorCallBack([=](const std::string &msg) { if (ErrorCallback) ErrorCallback(msg); });
		
		// OnMessageReceived callback
		socket->SetReceiveCallBack([=](const std::vector<uint8> data) {
			if (MessageReceiveCallback) MessageReceiveCallback(data); 
		});

		// Now that we're all setup, connect!
		socket->Connect();
	}

	void NUnrealTransport::Tick(float DeltaTime) {
		if (socket != nullptr) {
			socket->Tick();
		}
	}

	void NUnrealTransport::Connect(const std::string host, const unsigned port, const std::string& path, const bool ssl)
	{
		if (socket == nullptr) {
			CreateWebSocket(host, port, path, ssl);
		}
	}

	void NUnrealTransport::Close()
	{
		if (socket) {
			socket->Close();
		}
	}

	void NUnrealTransport::Send(std::string data)
	{
		if (socket) {
			socket->Send((uint8*)data.data(), data.size());
		}
	}
}