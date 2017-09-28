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
#include "INCollatedMessage.h"
#include "INUncollatedMessage.h"
#include "INTransport.h"
#include "NAuthenticateMessage.h"
#include "NCallbacks.h"
#include "NError.h"
#include "NLogger.h"
#include "INLogSink.h"
#include "NMatchData.h"
#include "NMatchmakeMatched.h"
#include "NMatchmakeTicket.h"
#include "NMatchPresence.h"
#include "NNotification.h"
#include "NRuntimeRpc.h"
#include "NSession.h"
#include "NTopicMessage.h"
#include "NTopicPresence.h"
#include "NUser.h"

#include "NCursor.h"
#include "NFriend.h"
#include "NGroup.h"
#include "NGroupSelf.h"
#include "NGroupUser.h"
#include "NMatch.h"
#include "NResultSet.h"
#include "NSelf.h"
#include "NStorageData.h"
#include "NStorageKey.h"
#include "NTopic.h"
#include "NTopicMessageAck.h"
#include "NLeaderboard.h"
#include "NLeaderboardRecord.h"
#include "NPurchaseRecord.h"

using namespace server;

namespace Nakama {
	class NAKAMA_API NClient
	{
	public:
		~NClient();

		unsigned GetConnectTimeout() { return connectTimeout; }
		std::string GetHost() { return host; }
		std::string GetLang() { return lang; }
		unsigned GetPort() { return port; }
		std::string GetServerKey() { return serverKey; }
		bool IsSSL() { return ssl; }
		unsigned GetTimeout() { return timeout; }

		long GetServerTime();
		void Tick(float DeltaTime);

		void Register(NAuthenticateMessage message,
			const std::function<void(NSession*)> callback,
			const std::function<void(const NError)> errback);
		
		void Login(NAuthenticateMessage message,
			const std::function<void(NSession*)> callback,
			const std::function<void(const NError)> errback);

		void Connect(NSession* session);
		void Connect(NSession* session, std::function<void(const bool)> callback);
		void Logout();
		void Disconnect();

		void Send(INCollatedMessage &message,
			std::function<void(void*)> callback,
			std::function<void(NError)> errback);

		void Send(INUncollatedMessage &message,
			std::function<void()> callback,
			std::function<void(NError)> errback);

		static NClient& Default(std::string serverKey);

		std::vector<std::function<void()>> OnDisconnect;
		std::vector<std::function<void(const NError&)>> OnError;
		std::vector<std::function<void(const NMatchData&)>> OnMatchData;
		std::vector<std::function<void(const NMatchPresence&)>> OnMatchPresence;
		std::vector<std::function<void(const NTopicMessage&)>> OnTopicMessage;
		std::vector<std::function<void(const NTopicPresence&)>> OnTopicPresence;
		std::vector<std::function<void(const NMatchmakeMatched&)>> OnMatchmakeMatched;
		std::vector<std::function<void(const NNotification&)>> OnNotification;

		class Builder;

	private:
		NClient(std::string serverKey);

		unsigned connectTimeout;
		std::string host;
		std::string lang;
		unsigned port;
		std::string serverKey;
		bool ssl;
		unsigned timeout;
		int64_t serverTime;
		INTransport* transport;

		std::map<
			std::string, // Key is collationId
			NCallbacks
		> collationIds;

		std::function<void(const bool)> OnConnected;

		void SetServerTime(long serverTime);
		void Authenticate(std::string path, AuthenticateRequest* payload, std::string langHeader,
			const std::function<void(NSession*)> &callback,
			const std::function<void(const NError &)> &errback);
		std::string GetWebsocketPath(NSession* session);

		void onMessage(Envelope message);

	};

	class NAKAMA_API NClient::Builder
	{
	public:
		Builder(std::string serverKey);

		Builder& ConnectTimeout(unsigned connectTimeout);
		Builder& Host(std::string host);
		Builder& Lang(std::string lang);
		Builder& Port(unsigned port);
		Builder& SSL(bool enable);
		Builder& Timeout(unsigned timeout);

		NClient& Build();
	private:
		NClient* client;
	};
}



template NAKAMA_API class Nakama::NResultSet<Nakama::NFriend>;
template NAKAMA_API class Nakama::NResultSet<Nakama::NGroup>;
template NAKAMA_API class Nakama::NResultSet<Nakama::NGroupSelf>;
template NAKAMA_API class Nakama::NResultSet<Nakama::NGroupUser>;
template NAKAMA_API class Nakama::NResultSet<Nakama::NMatch>;
template NAKAMA_API class Nakama::NResultSet<Nakama::NNotification>;
template NAKAMA_API class Nakama::NResultSet<Nakama::NStorageData>;
template NAKAMA_API class Nakama::NResultSet<Nakama::NStorageKey>;
template NAKAMA_API class Nakama::NResultSet<Nakama::NTopic>;
template NAKAMA_API class Nakama::NResultSet<Nakama::NTopicMessage>;
template NAKAMA_API class Nakama::NResultSet<Nakama::NUser>;
template NAKAMA_API class Nakama::NResultSet<Nakama::NLeaderboard>;
template NAKAMA_API class Nakama::NResultSet<Nakama::NLeaderboardRecord>;

