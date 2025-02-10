/*
* Copyright 2024 The Nakama Authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <iostream>
#include <string>
#include <memory>

#include "SatoriRestClient.h"
#include "DataHelper.h"
#include "nakama-cpp/NakamaVersion.h"
#include "StrUtil.h"
#include "RapidjsonHelper.h"

#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <google/protobuf/util/time_util.h>


#include "DefaultSession.h"

namespace Satori {

	void AddBoolArg(Nakama::NHttpQueryArgs& args, std::string&& name, bool value) {
		value ? args.emplace(name, "true") : args.emplace(name, "false");
	}

	std::string jsonDocToStr(Nakama::rapidjson::Document& document) {
		Nakama::rapidjson::StringBuffer buffer;
		Nakama::rapidjson::Writer<Nakama::rapidjson::StringBuffer> writer(buffer);
		document.Accept(writer);
		return buffer.GetString();
	}

	void addVarsToJsonDoc(Nakama::rapidjson::Document& document, const Nakama::NStringMap& vars) {
		if (!vars.empty()) {
			Nakama::rapidjson::Value jsonObj;
			jsonObj.SetObject();

			for (auto& p : vars) {
				jsonObj.AddMember(Nakama::rapidjson::Value::StringRefType(p.first.c_str()), p.second, document.GetAllocator());
			}

			document.AddMember("vars", std::move(jsonObj), document.GetAllocator());
		}
	}

	SatoriRestClient::SatoriRestClient(
		const Nakama::NClientParameters& parameters,
		Nakama::NHttpTransportPtr httpClient
	) : _httpClient(std::move(httpClient))
	{
		NLOG(Nakama::NLogLevel::Info, "Created Satori Client. NakamaSdkVersion: %s", Nakama::getNakamaSdkVersion());

		_host = parameters.host;
		_ssl = parameters.ssl;
		_platformParams = parameters.platformParams;
		_port = parameters.port;
		std::string baseUrl;


		if (_port == Nakama::DEFAULT_PORT) {
			_port = parameters.ssl ? 443 : 7450;
			NLOG(Nakama::NLogLevel::Info, "using default port %d", _port);
		}

		_ssl ? baseUrl.append("https") : baseUrl.append("http");
		baseUrl.append("://").append(parameters.host).append(":").append(std::to_string(_port));

		_httpClient->setBaseUri(baseUrl);

		_basicAuthMetadata = "Basic " + Nakama::base64Encode(parameters.serverKey + ":");
	}

	SatoriRestClient::~SatoriRestClient() {
		SatoriRestClient::disconnect();

		if (_reqContexts.size() > 0)
		{
			NLOG(Nakama::NLogLevel::Warn, "Not handled %u request(s) detected.", _reqContexts.size());

			for (RestReqContext* reqContext : _reqContexts)
			{
				delete reqContext;
			}

			_reqContexts.clear();
		}
	}

	void SatoriRestClient::disconnect() {
		_httpClient->cancelAllRequests();
	}

	void SatoriRestClient::tick() {
		_httpClient->tick();
	}

	void SatoriRestClient::authenticate(
		const std::string& id,
		const std::unordered_map<std::string, std::string>& defaultProperties,
		const std::unordered_map<std::string, std::string>& computedProperties,
		std::function<void(SSessionPtr)> successCallback,
		Nakama::ErrorCallback errorCallback
	) {
		try {
			NLOG_INFO("...");

			std::shared_ptr<SInternalSession> sessionData(std::make_shared<SInternalSession>());
			RestReqContext* ctx = createReqContext(sessionData);
			setBasicAuth(ctx);
			ctx->successCallback = [sessionData, successCallback]()
			{
				successCallback(sessionData);
			};
			ctx->errorCallback = std::move(errorCallback);

			Nakama::rapidjson::Document document;
			document.SetObject();

			document.AddMember("id", id, document.GetAllocator());

			std::string body = jsonDocToStr(document);

			sendReq(ctx, Nakama::NHttpReqMethod::POST, "/v1/authenticate", std::move(body));
		} catch (std::exception& e) {
			NLOG_ERROR("exception: " + std::string(e.what()));
		}
	}

	void SatoriRestClient::authenticateRefresh(
		SSessionPtr session,
		std::function<void(SSessionPtr)> successCallback,
		Nakama::ErrorCallback errorCallback
	) {
		try {
			NLOG_INFO("...");

			std::shared_ptr<SInternalSession> sessionData(std::make_shared<SInternalSession>());
			RestReqContext* ctx = createReqContext(sessionData);
			setBasicAuth(ctx);
			ctx->successCallback = [sessionData, successCallback]()
			{
				successCallback(sessionData);
			};
			ctx->errorCallback = std::move(errorCallback);

			Nakama::rapidjson::Document document;
			document.SetObject();

			document.AddMember("refresh_token", session->refresh_token, document.GetAllocator());

			std::string body = jsonDocToStr(document);

			sendReq(ctx, Nakama::NHttpReqMethod::POST, "/v1/authenticate/refresh", std::move(body));
		} catch (std::exception& e) {
			NLOG_ERROR("exception: " + std::string(e.what()));
		}
	}

	void SatoriRestClient::authenticateLogout(
		SSessionPtr session,
		std::function<void()> successCallback,
		Nakama::ErrorCallback errorCallback
	) {
		try {
			NLOG_INFO("...");

			RestReqContext* ctx = createReqContext(nullptr);
			setSessionAuth(ctx, session);
			ctx->successCallback = std::move(successCallback);
			ctx->errorCallback = std::move(errorCallback);

			Nakama::rapidjson::Document document;
			document.SetObject();

			document.AddMember("token", session->token, document.GetAllocator());
			document.AddMember("refresh_token", session->refresh_token, document.GetAllocator());

			std::string body = jsonDocToStr(document);

			sendReq(ctx, Nakama::NHttpReqMethod::POST, "/v1/authenticate/logout", std::move(body));
		} catch (std::exception& e) {
			NLOG_ERROR("exception: " + std::string(e.what()));
		}
	}

	void SatoriRestClient::deleteIdentity(
		SSessionPtr session,
		std::function<void()> successCallback,
		Nakama::ErrorCallback errorCallback
	) {
		try {
			NLOG_INFO("...");

			Nakama::NHttpQueryArgs args;

			RestReqContext* ctx = createReqContext(nullptr);
			setSessionAuth(ctx, session);
			ctx->successCallback = std::move(successCallback);
			ctx->errorCallback = std::move(errorCallback);

			sendReq(ctx, Nakama::NHttpReqMethod::DEL, "/v1/identity", "");
		} catch (std::exception& e) {
			NLOG_ERROR("exception: " + std::string(e.what()));
		}
	}

	void SatoriRestClient::postEvent(
		SSessionPtr session,
		const std::vector<SEvent>& events,
	    std::function<void()> successCallback,
	    Nakama::ErrorCallback errorCallback
	) {
		try {
			NLOG_INFO("...");

			RestReqContext* ctx = createReqContext(nullptr);
			setSessionAuth(ctx, session);
			ctx->successCallback = std::move(successCallback);
			ctx->errorCallback = std::move(errorCallback);

			Nakama::rapidjson::Document document;
			document.SetObject();
			Nakama::rapidjson::Value jsonEvents;
			jsonEvents.SetArray();
			for (const SEvent& event: events)
			{
				Nakama::rapidjson::Value jsonEvent;
				jsonEvent.SetObject();

				jsonEvent.AddMember("name", event.name, document.GetAllocator());
				jsonEvent.AddMember("id", event.id, document.GetAllocator());
				jsonEvent.AddMember("value", event.value, document.GetAllocator());
				google::protobuf::Timestamp timeProto = google::protobuf::util::TimeUtil::MillisecondsToTimestamp(
					static_cast<int64_t>(event.timestamp));
				std::string timeString = google::protobuf::util::TimeUtil::ToString(timeProto);
				jsonEvent.AddMember("timestamp", std::move(timeString), document.GetAllocator());
				Nakama::rapidjson::Value jsonMetadata;
				jsonMetadata.SetObject();
				for (auto& p : event.metadata) {
					jsonMetadata.AddMember(Nakama::rapidjson::Value::StringRefType(p.first.c_str()), p.second, document.GetAllocator());
				}
				jsonEvent.AddMember("metadata", std::move(jsonMetadata), document.GetAllocator());

				jsonEvents.PushBack(std::move(jsonEvent), document.GetAllocator());
			}
			document.AddMember("events", std::move(jsonEvents), document.GetAllocator());

			std::string body = jsonDocToStr(document);

			sendReq(ctx, Nakama::NHttpReqMethod::POST, "/v1/event", std::move(body));
		} catch (std::exception& e) {
			NLOG_ERROR("exception: " + std::string(e.what()));
		}
	}

	void SatoriRestClient::getExperiments(
		SSessionPtr session,
		const std::vector<std::string>& names,
		std::function<void(SExperimentList)> successCallback,
		Nakama::ErrorCallback errorCallback
	) {
		try {
			NLOG_INFO("...");

			Nakama::NHttpQueryArgs args;

			for (auto& name : names) {
				args.emplace("names", name);
			}

			std::shared_ptr<SInternalExperimentList> experimentsData(std::make_shared<SInternalExperimentList>());
			RestReqContext* ctx(createReqContext(experimentsData));
			setSessionAuth(ctx, session);
			ctx->successCallback = [experimentsData, successCallback]()
			{
				successCallback(static_cast<SExperimentList>(*experimentsData));
			};
			ctx->errorCallback = std::move(errorCallback);

			sendReq(ctx, Nakama::NHttpReqMethod::GET, "/v1/experiment", "", std::move(args));
		} catch (std::exception& e) {
			NLOG_ERROR("exception: " + std::string(e.what()));
		}
	}

	void SatoriRestClient::getFlags(
		SSessionPtr session,
		const std::vector<std::string>& names,
		std::function<void(SFlagList)> successCallback,
		Nakama::ErrorCallback errorCallback
	) {
		try {
			NLOG_INFO("...");

			Nakama::NHttpQueryArgs args;

			for (auto& name : names) {
				args.emplace("names", name);
			}

			std::shared_ptr<SInternalFlagList> flagsData(std::make_shared<SInternalFlagList>());
			RestReqContext* ctx(createReqContext(flagsData));
			setSessionAuth(ctx, session);
			ctx->successCallback = [flagsData, successCallback]()
			{
				successCallback(static_cast<SFlagList>(*flagsData));
			};
			ctx->errorCallback = std::move(errorCallback);

			sendReq(ctx, Nakama::NHttpReqMethod::GET, "/v1/flag", "", std::move(args));
		} catch (std::exception& e) {
			NLOG_ERROR("exception: " + std::string(e.what()));
		}
	}

	void SatoriRestClient::getLiveEvents(
		SSessionPtr session,
		const std::vector<std::string>& liveEventNames,
		std::function<void(SLiveEventList)> successCallback,
		Nakama::ErrorCallback errorCallback
	) {
		try {
			NLOG_INFO("...");

			Nakama::NHttpQueryArgs args;

			for (auto& liveEventName : liveEventNames) {
				args.emplace("names", liveEventName);
			}

			std::shared_ptr<SInternalLiveEventList> liveEventsData(std::make_shared<SInternalLiveEventList>());
			RestReqContext* ctx(createReqContext(liveEventsData));
			setSessionAuth(ctx, session);
			ctx->successCallback = [liveEventsData, successCallback]()
			{
				successCallback(static_cast<SLiveEventList>(*liveEventsData));
			};
			ctx->errorCallback = std::move(errorCallback);

			sendReq(ctx, Nakama::NHttpReqMethod::GET, "/v1/live-event", "", std::move(args));
		} catch (std::exception& e) {
			NLOG_ERROR("exception: " + std::string(e.what()));
		}
	}

	void SatoriRestClient::identify(
		SSessionPtr session,
		const std::string& id,
		const std::unordered_map<std::string, std::string>& defaultProperties,
		const std::unordered_map<std::string, std::string>& customProperties,
		std::function<void(SSessionPtr)> successCallback,
		Nakama::ErrorCallback errorCallback
	) {
		try {
			NLOG_INFO("...");

			std::shared_ptr<SInternalSession> sessionData(std::make_shared<SInternalSession>());
			RestReqContext* ctx = createReqContext(sessionData);
			setSessionAuth(ctx, session);
			ctx->successCallback = [sessionData, successCallback]()
			{
				successCallback(sessionData);
			};
			ctx->errorCallback = std::move(errorCallback);

			Nakama::rapidjson::Document document;
			document.SetObject();

			document.AddMember("id", id, document.GetAllocator());

			Nakama::rapidjson::Value jsonDefaultProperties;
			jsonDefaultProperties.SetObject();
			for (auto& obj : defaultProperties)
			{
				jsonDefaultProperties.AddMember(
					Nakama::rapidjson::Value(obj.first,document.GetAllocator()).Move(),
					Nakama::rapidjson::Value(obj.second, document.GetAllocator()).Move(),
					document.GetAllocator()
				);
			}
			document.AddMember("default", std::move(jsonDefaultProperties), document.GetAllocator());

			Nakama::rapidjson::Value jsonCustomProperties;
			jsonCustomProperties.SetObject();
			for (auto& obj : customProperties)
			{
				jsonCustomProperties.AddMember(
					Nakama::rapidjson::Value(obj.first,document.GetAllocator()).Move(),
					Nakama::rapidjson::Value(obj.second, document.GetAllocator()).Move(),
					document.GetAllocator()
				);
			}
			document.AddMember("custom", std::move(jsonCustomProperties), document.GetAllocator());

			std::string body = jsonDocToStr(document);

			sendReq(ctx, Nakama::NHttpReqMethod::PUT, "/v1/identify", std::move(body));
		} catch (std::exception& e) {
			NLOG_ERROR("exception: " + std::string(e.what()));
		}
	}

	void SatoriRestClient::listIdentityProperties(
		SSessionPtr session,
		std::function<void(SProperties)> successCallback,
		Nakama::ErrorCallback errorCallback
	) {
		try {
			NLOG_INFO("...");

			Nakama::NHttpQueryArgs args;

			std::shared_ptr<SInternalProperties> propertiesData(std::make_shared<SInternalProperties>());
			RestReqContext* ctx(createReqContext(propertiesData));
			setSessionAuth(ctx, session);
			ctx->successCallback = [propertiesData, successCallback]()
			{
				successCallback(static_cast<SProperties>(*propertiesData));
			};
			ctx->errorCallback = std::move(errorCallback);

			sendReq(ctx, Nakama::NHttpReqMethod::GET, "/v1/properties", "", std::move(args));
		} catch (std::exception& e) {
			NLOG_ERROR("exception: " + std::string(e.what()));
		}
	}

	void SatoriRestClient::updateProperties(
		SSessionPtr session,
		const std::unordered_map<std::string, std::string>& defaultProperties,
		const std::unordered_map<std::string, std::string>& customProperties,
		const bool recompute,
		std::function<void()> successCallback,
		Nakama::ErrorCallback errorCallback
	) {
		try {
			NLOG_INFO("...");

			RestReqContext* ctx = createReqContext(nullptr);
			setSessionAuth(ctx, session);
			ctx->successCallback = std::move(successCallback);
			ctx->errorCallback = std::move(errorCallback);

			Nakama::rapidjson::Document document;
			document.SetObject();

			Nakama::rapidjson::Value jsonDefaultProperties;
			jsonDefaultProperties.SetObject();
			for (auto& obj : defaultProperties)
			{
				jsonDefaultProperties.AddMember(
					Nakama::rapidjson::Value(obj.first,document.GetAllocator()).Move(),
					Nakama::rapidjson::Value(obj.second, document.GetAllocator()).Move(),
					document.GetAllocator()
				);
			}
			document.AddMember("default", std::move(jsonDefaultProperties), document.GetAllocator());

			Nakama::rapidjson::Value jsonCustomProperties;
			jsonCustomProperties.SetObject();
			for (auto& obj : customProperties)
			{
				jsonCustomProperties.AddMember(
					Nakama::rapidjson::Value(obj.first,document.GetAllocator()).Move(),
					Nakama::rapidjson::Value(obj.second, document.GetAllocator()).Move(),
					document.GetAllocator()
				);
			}
			document.AddMember("custom", std::move(jsonCustomProperties), document.GetAllocator());
			document.AddMember("recompute", recompute, document.GetAllocator());

			std::string body = jsonDocToStr(document);

			sendReq(ctx, Nakama::NHttpReqMethod::PUT, "/v1/properties", std::move(body));
		} catch (std::exception& e) {
			NLOG_ERROR("exception: " + std::string(e.what()));
		}
	}

	void SatoriRestClient::getMessages(
		SSessionPtr session,
		int32_t limit,
		bool forward,
		const std::string& cursor,
		std::function<void(SGetMessageListResponse)> successCallback,
		Nakama::ErrorCallback errorCallback
	) {
		try {
			NLOG_INFO("...");

			Nakama::NHttpQueryArgs args;

			args.emplace("limit", std::to_string(limit));
			args.emplace("forward", forward? "true" : "false");
			if (!cursor.empty()) {args.emplace("cursor", Nakama::encodeURIComponent(cursor));}

			std::shared_ptr<SInternalGetMessageListResponse> messagesData(std::make_shared<SInternalGetMessageListResponse>());
			RestReqContext* ctx(createReqContext(messagesData));
			setSessionAuth(ctx, session);
			ctx->successCallback = [messagesData, successCallback]()
			{
				successCallback(static_cast<SGetMessageListResponse>(*messagesData));
			};
			ctx->errorCallback = std::move(errorCallback);

			sendReq(ctx, Nakama::NHttpReqMethod::GET, "/v1/message", "", std::move(args));
		} catch (std::exception& e) {
			NLOG_ERROR("exception: " + std::string(e.what()));
		}
	}

	void SatoriRestClient::updateMessage(
		SSessionPtr session,
		const std::string& messageId,
		const Nakama::NTimestamp readTime,
		const Nakama::NTimestamp consumeTime,
		std::function<void()> successCallback,
		Nakama::ErrorCallback errorCallback
	) {
		try {
			NLOG_INFO("...");

			RestReqContext* ctx = createReqContext(nullptr);
			setSessionAuth(ctx, session);
			ctx->successCallback = std::move(successCallback);
			ctx->errorCallback = std::move(errorCallback);

			Nakama::rapidjson::Document document;
			document.SetObject();

			document.AddMember("read_time", readTime, document.GetAllocator());
			document.AddMember("consume_time", consumeTime, document.GetAllocator());

			std::string body = jsonDocToStr(document);

			sendReq(ctx, Nakama::NHttpReqMethod::PUT, "/v1/message/" + Nakama::encodeURIComponent(messageId), std::move(body));
		} catch (std::exception& e) {
			NLOG_ERROR("exception: " + std::string(e.what()));
		}
	}

	void SatoriRestClient::deleteMessage(
		SSessionPtr session,
		const std::string& messageId,
		std::function<void()> successCallback,
		Nakama::ErrorCallback errorCallback
	) {
		try {
			NLOG_INFO("...");

			Nakama::NHttpQueryArgs args;

			RestReqContext* ctx = createReqContext(nullptr);
			setSessionAuth(ctx, session);
			ctx->successCallback = std::move(successCallback);
			ctx->errorCallback = std::move(errorCallback);

			sendReq(ctx, Nakama::NHttpReqMethod::DEL, "/v1/message/" + Nakama::encodeURIComponent(messageId), "");
		} catch (std::exception& e) {
			NLOG_ERROR("exception: " + std::string(e.what()));
		}
	}

	RestReqContext* SatoriRestClient::createReqContext(std::shared_ptr<SFromJsonInterface> data) {
		RestReqContext* ctx = new RestReqContext();
		ctx->data = data;
		_reqContexts.emplace(ctx);
		return ctx;
	}

	void SatoriRestClient::setBasicAuth(RestReqContext* ctx) {
		ctx->auth.append(_basicAuthMetadata);
	}

	void SatoriRestClient::setSessionAuth(RestReqContext* ctx, const SSessionPtr session) {
		ctx->auth.append("Bearer ").append(session->token);
	}

	void SatoriRestClient::sendReq(
		RestReqContext* ctx,
		Nakama::NHttpReqMethod method,
		std::string&& path,
		std::string&& body,
		Nakama::NHttpQueryArgs &&args
	) {
		if(ctx == nullptr) {
			reqError(nullptr, Nakama::NError("Satori request context not found.", Nakama::ErrorCode::InternalError));
			return;
		}
		Nakama::NHttpRequest req;

		req.method    = method;
		req.path      = std::move(path);
		req.body      = std::move(body);
		req.queryArgs = std::move(args);

		req.headers.emplace("Accept", "application/json");
		req.headers.emplace("Content-Type", "application/json");
		if (!ctx->auth.empty()) {
			req.headers.emplace("Authorization", std::move(ctx->auth));
		}

		_httpClient->request(req, [this, ctx](Nakama::NHttpResponsePtr response) {
			// TODO: Convert this boilerplate lambda back into a function that can be used from within Satori cpp. Boilerplate begins here	============
			[&]()//void RestClient::onResponse(RestReqContext* reqContext, NHttpResponsePtr response)
			{
				auto it = _reqContexts.find(ctx);
				if (it != _reqContexts.end()) {
					if (response->statusCode == 200) {// OK
						if (ctx && ctx->successCallback) {
							bool ok = true;
							if (ctx->data) {
								ok = ctx->data->fromJson(response->body);
								if (!ok) {
									reqError(ctx, Nakama::NError("Parse JSON failed for Satori. HTTP body: <<" + response->body + ">>", Nakama::ErrorCode::InternalError));
								}
							}

							if (ok) {
								ctx->successCallback();
							}
						}
					} else {
						std::string errMessage;
						Nakama::ErrorCode code = Nakama::ErrorCode::Unknown;

						if (response->statusCode == Nakama::InternalStatusCodes::CONNECTION_ERROR) {
							code = Nakama::ErrorCode::ConnectionError;
							errMessage.append("message: ").append(response->errorMessage);
						} else if (response->statusCode == Nakama::InternalStatusCodes::CANCELLED_BY_USER) {
							code = Nakama::ErrorCode::CancelledByUser;
							errMessage.append("message: ").append(response->errorMessage);
						} else if (response->statusCode == Nakama::InternalStatusCodes::INTERNAL_TRANSPORT_ERROR) {
							code = Nakama::ErrorCode::InternalError;
							errMessage.append("message: ").append(response->errorMessage);
						} else if (!response->body.empty() && response->body[0] == '{') {// have to be JSON
							/*
							 try {
								rapidjson::Document document;

								if (document.Parse(response->body).HasParseError()) {
									errMessage = "Parse JSON failed: " + response->body;
									code = Nakama::ErrorCode::InternalError;
								} else {
									auto& jsonMessage = document["message"];
									auto& jsonCode    = document["code"];

									if (jsonMessage.IsString()) {
										errMessage.append("message: ").append(jsonMessage.GetString());
									}

									if (jsonCode.IsNumber()) {
										int serverErrCode = jsonCode.GetInt();

										switch (serverErrCode) {
										case grpc::StatusCode::UNAVAILABLE      : code = ErrorCode::ConnectionError; break;
										case grpc::StatusCode::INTERNAL         : code = ErrorCode::InternalError; break;
										case grpc::StatusCode::NOT_FOUND        : code = ErrorCode::NotFound; break;
										case grpc::StatusCode::ALREADY_EXISTS   : code = ErrorCode::AlreadyExists; break;
										case grpc::StatusCode::INVALID_ARGUMENT : code = ErrorCode::InvalidArgument; break;
										case grpc::StatusCode::UNAUTHENTICATED  : code = ErrorCode::Unauthenticated; break;
										case grpc::StatusCode::PERMISSION_DENIED: code = ErrorCode::PermissionDenied; break;

										default:
											errMessage.append("\ncode: ").append(std::to_string(serverErrCode));
											break;
										}
									}
								}
							} catch (std::exception& e) {
								NLOG_ERROR("exception: " + std::string(e.what()));
							}
							*/
						}

						if (errMessage.empty()) {
							errMessage.append("message: ").append(response->errorMessage);
							errMessage.append("\nHTTP status: ").append(std::to_string(response->statusCode));
							errMessage.append("\nbody: ").append(response->body);
						}

						reqError(ctx, Nakama::NError(std::move(errMessage), code));
					}

					delete ctx;
					_reqContexts.erase(it);
				} else {
					reqError(nullptr, Nakama::NError("Not found satori request context.", Nakama::ErrorCode::InternalError));
					delete ctx;
				}
			}();
			// TODO: Convert this boilerplate lambda back into a function that can be used from within Satori cpp. Boilerplate ends here	============
		});
	}

	void SatoriRestClient::reqError(RestReqContext* ctx, const Nakama::NError& error) const {
		NLOG_ERROR(error);

		if (ctx && ctx->errorCallback) {
			ctx->errorCallback(error);
		} else if (_defaultErrorCallback) {
			_defaultErrorCallback(error);
		} else {
			NLOG_WARN("^ error not handled");
		}
	}
}
