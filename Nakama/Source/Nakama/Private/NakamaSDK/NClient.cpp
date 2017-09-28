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

#include "NClient.h"

#ifdef __UNREAL__
#include "Nakama/Private/NUnrealTransport.h"
#endif

#include "NibbleAndAHalf/base64.h"

#include <string>

using namespace server;

namespace Nakama {
	NClient::NClient(std::string serverKey)
	{
		this->connectTimeout = 3000;
		this->host = "127.0.0.1";
		this->port = 7350;
		this->serverKey = serverKey;
		this->ssl = false;
		this->timeout = 5000;
		this->lang = "en";

#ifdef __UNREAL__
		transport = new NUnrealTransport();
#else
		// TODO: Could use another transport here?
		//transport = new SomeGenericTransport()?
#endif

		transport->SetOnConnectCallBack([=]() {
			if (OnConnected) OnConnected(true);
		});

		transport->SetOnCloseCallBack([=]() {
			collationIds.clear();
			for (size_t i = 0; i < OnDisconnect.size(); i++) OnDisconnect[i]();
		});

		transport->SetOnMessageCallBack([=](const std::vector<uint8> data) {
			Envelope message;
			message.ParseFromArray(data.data(), data.size());
			NLogger::Format(Trace, "NClient->RcvdMessage: %d", (int)message.payload_case());
			onMessage(message);
		});
	}

	NClient::~NClient()
	{
		delete transport;
		transport = nullptr;
	}

	NClient& NClient::Default(std::string serverKey)
	{
		return NClient::Builder(serverKey).Build();
	}

	void NClient::SetServerTime(long value)
	{
		// Dont let server time go backwards.
		if ((value - serverTime) > 0)
		{
			serverTime = value;
		}
	}

	void NClient::Authenticate(std::string path, AuthenticateRequest* payload, std::string langHeader,
		const std::function<void(NSession*)> &callback,
		const std::function<void(const NError &)> &errback)
	{

		// Add a collation ID for logs
		payload->set_collationid(TCHAR_TO_UTF8(*FGuid::NewGuid().ToString()));

		std::string uri;
		uri.append(ssl ? "https://" : "http://").append(host).append(":").append(std::to_string(port)).append(path);

		//Logger.TraceFormatIf(Trace, "Url={0}, Payload={1}", uri.str(), payload);

		int rLen = 0;
		char* auth = base64((serverKey + ":").c_str(), serverKey.length() + 1, &rLen);
		std::string authHeader = "Basic " + std::string(auth);

		int64 span = FDateTime::UtcNow().ToUnixTimestamp();
		transport->Post(uri, payload, authHeader, langHeader, timeout, connectTimeout,
			[=](std::vector<uint8_t> data) {
			AuthenticateResponse authResponse;
			authResponse.ParseFromArray(&data[0], data.size());

			//Logger.TraceFormatIf(Trace, "DecodedResponse={0}", authResponse);

			switch (authResponse.id_case())
			{
			case AuthenticateResponse::IdCase::kSession:
				if (callback) callback(new NSession(authResponse.session().token().c_str(), std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::seconds(span))));
				break;
			case AuthenticateResponse::IdCase::kError:
				if (errback) errback(NError(authResponse.error()));
				break;
			default:
				NLogger::Error("Received invalid response from server");
				break;
			}
		},
			[errback](int32 e) {
			if (errback != NULL) errback(NError("Error: " + std::to_string(e)));
		}
		);
	}

	long NClient::GetServerTime()
	{
		if (serverTime < 1)
		{
			// Time has not been set via socket yet.
			return FDateTime::UtcNow().ToUnixTimestamp();
		}
		return serverTime;
	}


	inline void NClient::Tick(float DeltaTime) {
		if (transport) {
			transport->Tick(DeltaTime);
		}
	}

	inline void NClient::Register(NAuthenticateMessage message,
		const std::function<void(NSession*)> callback,
		const std::function<void(const NError)> errback)
	{
		Authenticate("/user/register", message.GetPayload(), lang, callback, errback);
	}

	inline void NClient::Login(NAuthenticateMessage message,
		const std::function<void(NSession*)> callback,
		const std::function<void(const NError)> errback)
	{
		Authenticate("/user/login", message.GetPayload(), lang, callback, errback);
	}

	void NClient::Connect(NSession* session, std::function<void(const bool)> callback)
	{
		NLogger::Info("Nakama::Client->Connect() - Connecting to API");
		OnConnected = callback;
		transport->Connect(host, port, GetWebsocketPath(session), ssl);
	}

	void NClient::Logout()
	{
		Envelope* payload = new Envelope();
		payload->set_allocated_logout(new server::Logout());
		std::string str = payload->SerializeAsString();
		transport->Send(str.c_str(), [](bool comp) {});
	}

	void NClient::Disconnect()
	{
		NLogger::Info("Nakama::Client->Disconnect()");
		transport->Close();
		transport = nullptr;
	}

	void NClient::Send(INCollatedMessage& message, std::function<void(void*)> callback, std::function<void(NError)> errback)
	{
		// Set a collation ID to dispatch callbacks on receive
		std::string collationId = TCHAR_TO_UTF8(*FGuid::NewGuid().ToString());
		message.SetCollationId(collationId);

		// Track callbacks for message
		NCallbacks callbacks = NCallbacks(callback, errback);
		collationIds.insert(std::make_pair(collationId, callbacks));

		std::string str = message.GetPayload()->SerializeAsString();

		Envelope e = Envelope();
		e.ParseFromString(str);

		transport->Send(str, [=](bool completed) mutable {
			if (!completed)
			{
				// The write may have failed; don't track it
				collationIds.erase(collationId);
				if (errback) errback(NError("Message send error"));
			}
		});
	}

	void NClient::Send(INUncollatedMessage& message, std::function<void()> callback, std::function<void(NError)> errback)
	{
		std::string str = message.GetPayload()->SerializeAsString();

		Envelope e = Envelope();
		e.ParseFromString(str);

		transport->Send(str, [=](bool completed) mutable {
			if (completed)
			{
				if (callback) callback();
			}
			else
			{
				if (errback) errback(NError("Message send error"));
			}
		});
	}

	inline std::string NClient::GetWebsocketPath(NSession* session)
	{
		std::string path;
		path.append("/api?serverkey=").append(serverKey);
		path.append("&token=").append(session ? session->GetToken() : "");
		path.append("&lang=").append(lang);
		return path;
	}

	void NClient::onMessage(Envelope message) {
		// Handle realtime messages
		switch (message.payload_case())
		{
		case Envelope::PayloadCase::kHeartbeat:
			serverTime = message.heartbeat().timestamp();
			return;
		case Envelope::PayloadCase::kMatchmakeMatched:
			for (size_t i = 0; i < OnMatchmakeMatched.size(); i++) OnMatchmakeMatched[i](NMatchmakeMatched(message.matchmake_matched()));
			return;
		case Envelope::PayloadCase::kMatchData:
			for (size_t i = 0; i < OnMatchData.size(); i++) OnMatchData[i](NMatchData(message.match_data()));
			return;
		case Envelope::PayloadCase::kMatchPresence:
			for (size_t i = 0; i < OnMatchPresence.size(); i++) OnMatchPresence[i](NMatchPresence(message.match_presence()));
			return;
		case Envelope::PayloadCase::kTopicMessage:
			for (size_t i = 0; i < OnTopicMessage.size(); i++) OnTopicMessage[i](NTopicMessage(message.topic_message()));
			return;
		case Envelope::PayloadCase::kTopicPresence:
			for (size_t i = 0; i < OnTopicPresence.size(); i++) OnTopicPresence[i](NTopicPresence(message.topic_presence()));
			return;
		case Envelope::PayloadCase::kLiveNotifications:
			for (size_t i = 0; i < OnNotification.size(); i++) 
				for (size_t j = 0; j < message.live_notifications().notifications_size(); i++)
					OnNotification[i](NNotification(message.live_notifications().notifications().Get(j)));
			return;
		}

		std::string collationId = message.collation_id();
		auto pair = collationIds.find(collationId);
		NCallbacks* callbacks = pair != collationIds.end() ? &pair->second : nullptr;

		switch (message.payload_case())
		{

		case Envelope::PayloadCase::PAYLOAD_NOT_SET: {
			if (callbacks) {
				callbacks->OnSuccess(nullptr);
			}
			break;
		}

		case Envelope::PayloadCase::kError: {
			NError error = NError(message.error());
			if (callbacks) {
				callbacks->OnError(error);
			}
			else {
				for (size_t i = 0; i < OnError.size(); i++) OnError[i](error);
			}
			break;
		}

		case Envelope::PayloadCase::kFriends: {
			if (callbacks) {
				auto msgFriends = message.friends().friends();
				auto friends = std::vector<NFriend>();
				for (size_t i = 0, maxI = msgFriends.size(); i < maxI; i++) {
					friends.push_back(NFriend(msgFriends[i]));
				}
				callbacks->OnSuccess(new NResultSet<NFriend>(friends, NCursor()));
			}
			break;
		}

		case Envelope::PayloadCase::kGroupUsers: {
			if (callbacks) {
				auto msgGroupUsers = message.group_users().users();
				auto groupUsers = std::vector<NGroupUser>();
				for (size_t i = 0, maxI = msgGroupUsers.size(); i < maxI; i++) {
					groupUsers.push_back(NGroupUser(msgGroupUsers[i]));
				}
				callbacks->OnSuccess(new NResultSet<NGroupUser>(groupUsers, NCursor()));
			}
			break;
		}

		case Envelope::PayloadCase::kGroups: {
			if (callbacks) {
				auto msgGroups = message.groups().groups();
				auto groups = std::vector<NGroup>();
				for (size_t i = 0, maxI = msgGroups.size(); i < maxI; i++) {
					groups.push_back(NGroup(msgGroups[i]));
				}
				NCursor cursor = NCursor(message.groups().cursor());
				callbacks->OnSuccess(new NResultSet<NGroup>(groups, cursor));
			}
			break;
		}

		case Envelope::PayloadCase::kGroupsSelf: {
			if (callbacks) {
				auto msgGroupsSelf = message.groups_self().groups_self();
				auto groupsSelf = std::vector<NGroupSelf>();
				for (size_t i = 0, maxI = msgGroupsSelf.size(); i < maxI; i++) {
					groupsSelf.push_back(NGroupSelf(msgGroupsSelf[i]));
				}
				callbacks->OnSuccess(new NResultSet<NGroupSelf>(groupsSelf, NCursor()));
			}
			break;
		}

		case Envelope::PayloadCase::kMatchmakeTicket: {
			if (callbacks) callbacks->OnSuccess(new NMatchmakeTicket(message.matchmake_ticket()));
			break;
		}

		case Envelope::PayloadCase::kMatch: {
			if (callbacks) callbacks->OnSuccess(new NMatch(message.match()));
			break;
		}

		case Envelope::PayloadCase::kMatches: {
			if (callbacks) {
				auto msgMatches = message.matches().matches();
				auto matches = std::vector<NMatch>();
				for (size_t i = 0, maxI = msgMatches.size(); i < maxI; i++) {
					matches.push_back(NMatch(msgMatches[i]));
				}
				callbacks->OnSuccess(new NResultSet<NMatch>(matches, NCursor()));
			}
			break;
		}

		case Envelope::PayloadCase::kSelf: {
			if (callbacks) callbacks->OnSuccess(new NSelf(message.self().self()));
			break;
		}

		case Envelope::PayloadCase::kStorageKeys: {
			if (callbacks) {
				auto msgKeys = message.storage_keys().keys();
				auto keys = std::vector<NStorageKey>();
				for (size_t i = 0, maxI = msgKeys.size(); i < maxI; i++) {
					keys.push_back(NStorageKey(msgKeys[i]));
				}
				callbacks->OnSuccess(new NResultSet<NStorageKey>(keys, NCursor()));
			}
			break;
		}

		case Envelope::PayloadCase::kStorageData: {
			if (callbacks) {
				auto msgData = message.storage_data().data();
				auto data = std::vector<NStorageData>();
				for (size_t i = 0, maxI = msgData.size(); i < maxI; i++) {
					data.push_back(NStorageData(msgData[i]));
				}
				callbacks->OnSuccess(new NResultSet<NStorageData>(data, NCursor()));
			}
			break;
		}

		case Envelope::PayloadCase::kTopics: {
			if (callbacks) {
				auto msgTopics = message.topics().topics();
				auto topics = std::vector<NTopic>();
				for (size_t i = 0, maxI = msgTopics.size(); i < maxI; i++) {
					topics.push_back(NTopic(msgTopics[i]));
				}
				callbacks->OnSuccess(new NResultSet<NTopic>(topics, NCursor()));
			}
			break;
		}

		case Envelope::PayloadCase::kTopicMessageAck: {
			if (callbacks) callbacks->OnSuccess(new NTopicMessageAck(message.topic_message_ack()));
			break;
		}

		case Envelope::PayloadCase::kTopicMessages: {
			if (callbacks) {
				auto msgMsgs = message.topic_messages().messages();
				auto msgs = std::vector<NTopicMessage>();
				for (size_t i = 0, maxI = msgMsgs.size(); i < maxI; i++) {
					msgs.push_back(NTopicMessage(msgMsgs[i]));
				}
				NCursor cursor = NCursor(message.topic_messages().cursor());
				callbacks->OnSuccess(new NResultSet<NTopicMessage>(msgs, cursor));
			}
			break;
		}

		case Envelope::PayloadCase::kUsers: {
			if (callbacks) {
				auto msgUsers = message.users().users();
				auto users = std::vector<NUser>();
				for (size_t i = 0, maxI = msgUsers.size(); i < maxI; i++) {
					users.push_back(NUser(msgUsers[i]));
				}
				callbacks->OnSuccess(new NResultSet<NUser>(users, NCursor()));
			}
			break;
		}

		case Envelope::PayloadCase::kLeaderboards: {
			if (callbacks) {
				auto msgLeaderboards = message.leaderboards().leaderboards();
				auto leaderboards = std::vector<NLeaderboard>();
				for (size_t i = 0, maxI = msgLeaderboards.size(); i < maxI; i++) {
					leaderboards.push_back(NLeaderboard(msgLeaderboards[i]));
				}
				NCursor cursor = NCursor(message.leaderboards().cursor());
				callbacks->OnSuccess(new NResultSet<NLeaderboard>(leaderboards, cursor));
			}
			break;
		}

		case Envelope::PayloadCase::kLeaderboardRecords: {
			if (callbacks) {
				auto msgRecords = message.leaderboard_records().records();
				auto records = std::vector<NLeaderboardRecord>();
				for (size_t i = 0, maxI = msgRecords.size(); i < maxI; i++) {
					records.push_back(NLeaderboardRecord(msgRecords[i]));
				}
				NCursor cursor = NCursor(message.leaderboard_records().cursor());
				callbacks->OnSuccess(new NResultSet<NLeaderboardRecord>(records, cursor));
			}
			break;
		}

		case Envelope::PayloadCase::kRpc: {
			if (callbacks) callbacks->OnSuccess(new NRuntimeRpc(message.rpc()));
			break;
		}

		case Envelope::PayloadCase::kNotifications: {
			if (callbacks) {
				auto msgNotifs = message.notifications().notifications();
				auto notifs = std::vector<NNotification>();
				for (size_t i = 0, maxI = msgNotifs.size(); i < maxI; i++) {
					notifs.push_back(NNotification(msgNotifs[i]));
				}
				callbacks->OnSuccess(new NResultSet<NNotification>(notifs, NCursor()));
			}
			break;
		}

		default:
			NLogger::Format(Trace, "Unrecognized message: %d", (int)message.payload_case());
			break;
		}

		// clean up
		if (callbacks) {
			collationIds.erase(collationId);
		}
	}

	/* Factory Methods */
	NClient::Builder::Builder(std::string serverKey)
	{
		client = new NClient(serverKey);
	}

	NClient::Builder& NClient::Builder::ConnectTimeout(unsigned connectTimeout)
	{
		client->connectTimeout = connectTimeout;
		return *this;
	}

	NClient::Builder& NClient::Builder::Host(std::string host)
	{
		client->host = host;
		return *this;
	}

	NClient::Builder& NClient::Builder::Lang(std::string lang)
	{
		client->lang = lang;
		return *this;
	}

	NClient::Builder& NClient::Builder::Port(unsigned port)
	{
		client->port = port;
		return *this;
	}


	NClient::Builder& NClient::Builder::SSL(bool ssl)
	{
		client->ssl = ssl;
		return *this;
	}

	NClient::Builder& NClient::Builder::Timeout(unsigned timeout)
	{
		client->timeout = timeout;
		return *this;
	}

	NClient& NClient::Builder::Build()
	{
		// Clone object so builder now operates on new copy.
		NClient* original = client;
		client = new NClient(original->serverKey);
		client->connectTimeout = original->connectTimeout;
		client->host = original->host;
		client->lang = original->lang;
		client->port = original->port;
		client->ssl = original->ssl;
		client->timeout = original->timeout;
		return *original;
	}
}
