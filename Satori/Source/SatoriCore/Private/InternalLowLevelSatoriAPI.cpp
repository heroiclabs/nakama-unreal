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

#include "InternalLowLevelSatoriAPI.h"
#include "nakama-cpp/NError.h"
#include "nakama-cpp/log/NLogger.h"
#include "rapidjson/document.h"
#include "rapidjson/error/en.h"

namespace Satori{
	bool jsonValueToStringVector(const rapidjson::Value& input, std::vector<std::string>& output) {
		for (rapidjson::Value::ConstMemberIterator iter = input.MemberBegin(); iter != input.MemberEnd(); ++iter){
			output.emplace_back(iter->value.GetString());
		}
		return true;
	}

	bool jsonValueToStringMap(const rapidjson::Value& input, std::unordered_map<std::string, std::string>& output) {
		for (rapidjson::Value::ConstMemberIterator iter = input.MemberBegin(); iter != input.MemberEnd(); ++iter){
			output[iter->name.GetString()] = iter->value.GetString();
		}
		return true;
	}

	bool SInternalAuthenticateLogoutRequest::fromJson(std::string jsonString) {

		return false;
	}

	bool SInternalAuthenticateRefreshRequest::fromJson(std::string jsonString) {

		return false;
	}

	bool SInternalAuthenticateRequest::fromJson(std::string jsonString) {

		return false;
	}

	bool jsonValueToSEvent(const rapidjson::Value& input, SEvent& output){
		if(input.HasMember("name") && !input["name"].IsString()) {
			return false;
		}
		output.name = input["name"].GetString();
		if(input.HasMember("id") && !input["id"].IsString()) {
			return false;
		}
		output.id = input["id"].GetString();
		if(input.HasMember("metadata") && !jsonValueToStringMap(input["metadata"], output.metadata)) {
			return false;
		}
		if(input.HasMember("value") && !input["value"].IsString()) {
			return false;
		}
		output.value = input["value"].GetString();
		if(input.HasMember("timestamp") && !input["timestamp"].IsInt64()) {
			return false;
		}
		output.timestamp = input["timestamp"].GetInt64();
		return true;
	}

	bool SInternalEvent::fromJson(std::string jsonString) {
		rapidjson::Document d;
		if(d.ParseInsitu(jsonString.data()).HasParseError()) {
			NLOG_ERROR(Nakama::NError("Parse SEvent JSON failed. Error at " + std::to_string(d.GetErrorOffset()) + ": " + std::string(GetParseError_En(d.GetParseError())) + " HTTP body:<< " + jsonString + " >>.", Nakama::ErrorCode::InternalError));
			return false;
		}
		return jsonValueToSEvent(d, *this);
	}

	bool SInternalEventRequest::fromJson(std::string jsonString) {

		return false;
	}

	bool jsonValueToSExperiment(const rapidjson::Value& input, SExperiment& output){
		if(input.HasMember("name") && !input["name"].IsString()) {
			return false;
		}
		output.name = input["name"].GetString();
		if(input.HasMember("value") && !input["value"].IsString()) {
			return false;
		}
		output.value = input["value"].GetString();
		return true;
	}

	bool SInternalExperiment::fromJson(std::string jsonString) {
		rapidjson::Document d;
		if(d.ParseInsitu(jsonString.data()).HasParseError()) {
			NLOG_ERROR(Nakama::NError("Parse SExperiment JSON failed. Error at " + std::to_string(d.GetErrorOffset()) + ": " + std::string(GetParseError_En(d.GetParseError())) + " HTTP body:<< " + jsonString + " >>.", Nakama::ErrorCode::InternalError));
			return false;
		}
		return jsonValueToSExperiment(d, *this);
	}

	bool SInternalExperimentList::fromJson(std::string jsonString) {
		rapidjson::Document d;
		if(d.ParseInsitu(jsonString.data()).HasParseError()) {
			NLOG_ERROR(Nakama::NError("Parse SExperimentList JSON failed. Error at " + std::to_string(d.GetErrorOffset()) + ": " + std::string(GetParseError_En(d.GetParseError())) + " HTTP body:<< " + jsonString + " >>.", Nakama::ErrorCode::InternalError));
			return false;
		}

		if(d.HasMember("experiments")) {
			if(!d["experiments"].IsArray()) {
				return false;
			}
			for (auto& jsonExperiment : d["experiments"].GetArray()) {
				SExperiment experiment;
				if(!jsonValueToSExperiment(jsonExperiment, experiment)) {
					return false;
				}
				this->experiments.emplace_back(experiment);
			}
		}
		return true;
	}

	bool jsonValueToSFlag(const rapidjson::Value& input, SFlag& output){
		if(input.HasMember("name") && !input["name"].IsString()) {
			return false;
		}
		output.name = input["name"].GetString();
		if(input.HasMember("value") && !input["value"].IsString()) {
			return false;
		}
		output.value = input["value"].GetString();
		// TODO: Figure out how to obtain this value and set it here if it can be obtained from the json we have
		output.condition_changed = false;
		return true;
	}

	bool SInternalFlag::fromJson(std::string jsonString) {
		rapidjson::Document d;
		if(d.ParseInsitu(jsonString.data()).HasParseError()) {
			NLOG_ERROR(Nakama::NError("Parse SFlag JSON failed. Error at " + std::to_string(d.GetErrorOffset()) + ": " + std::string(GetParseError_En(d.GetParseError())) + " HTTP body:<< " + jsonString + " >>.", Nakama::ErrorCode::InternalError));
			return false;
		}
		return jsonValueToSFlag(d, *this);
	}

	bool SInternalFlagList::fromJson(std::string jsonString) {
		rapidjson::Document d;
		if(d.ParseInsitu(jsonString.data()).HasParseError()) {
			NLOG_ERROR(Nakama::NError("Parse SFlagList JSON failed. Error at " + std::to_string(d.GetErrorOffset()) + ": " + std::string(GetParseError_En(d.GetParseError())) + " HTTP body:<< " + jsonString + " >>.", Nakama::ErrorCode::InternalError));
			return false;
		}

		if(d.HasMember("flags")) {
			if(!d["flags"].IsArray()) {
				return false;
			}
			for (auto& jsonFlag : d["flags"].GetArray()) {
				SFlag flag;
				if(!jsonValueToSFlag(jsonFlag, flag)) {
					return false;
				}
				this->flags.emplace_back(flag);
			}
		}

		return true;
	}

	bool SInternalGetExperimentsRequest::fromJson(std::string jsonString) {

		return false;
	}

	bool SInternalGetFlagsRequest::fromJson(std::string jsonString) {

		return false;
	}

	bool SInternalGetLiveEventsRequest::fromJson(std::string jsonString) {

		return false;
	}

	bool SInternalIdentifyRequest::fromJson(std::string jsonString) {

		return false;
	}

	bool jsonValueToSLiveEvent(const rapidjson::Value& input, SLiveEvent& output){
		if(input.HasMember("name") && !input["name"].IsString()) {
			return false;
		}
		output.name = input["name"].GetString();
		if(input.HasMember("description") && !input["description"].IsString()) {
			return false;
		}
		output.description = input["description"].GetString();
		if(input.HasMember("value") && !input["value"].IsString()) {
			return false;
		}
		output.value = input["value"].GetString();
		if(input.HasMember("active_start_time_sec") && !input["active_start_time_sec"].IsInt64()) {
			return false;
		}
		output.active_start_time_sec = input["active_start_time_sec"].GetInt64();
		if(input.HasMember("active_end_time_sec") && !input["active_end_time_sec"].IsInt64()) {
			return false;
		}
		output.active_end_time_sec = input["active_end_time_sec"].GetInt64();
		if(input.HasMember("id") && !input["id"].IsString()) {
			return false;
		}
		output.id = input["id"].GetString();
		if(input.HasMember("start_time_sec") && !input["start_time_sec"].IsInt64()) {
			return false;
		}
		output.start_time_sec = input["start_time_sec"].GetInt64();
		if(input.HasMember("end_time_sec") && !input["end_time_sec"].IsInt64()) {
			return false;
		}
		output.end_time_sec = input["end_time_sec"].GetInt64();
		if(input.HasMember("duration_sec") && !input["duration_sec"].IsInt64()) {
			return false;
		}
		output.duration_sec = input["duration_sec"].GetInt64();
		if(input.HasMember("reset_cron") && !input["reset_cron"].IsString()) {
			return false;
		}
		output.reset_cron = input["reset_cron"].GetString();
		return true;
	}

	bool SInternalLiveEvent::fromJson(std::string jsonString) {
		rapidjson::Document d;
		if(d.ParseInsitu(jsonString.data()).HasParseError()) {
			NLOG_ERROR(Nakama::NError("Parse SLiveEvent JSON failed. Error at " + std::to_string(d.GetErrorOffset()) + ": " + std::string(GetParseError_En(d.GetParseError())) + " HTTP body:<< " + jsonString + " >>.", Nakama::ErrorCode::InternalError));
			return false;
		}
		return jsonValueToSLiveEvent(d, *this);
	}

	bool SInternalLiveEventList::fromJson(std::string jsonString) {
		rapidjson::Document d;
		if(d.ParseInsitu(jsonString.data()).HasParseError()) {
			NLOG_ERROR(Nakama::NError("Parse SLiveEventList JSON failed. Error at " + std::to_string(d.GetErrorOffset()) + ": " + std::string(GetParseError_En(d.GetParseError())) + " HTTP body:<< " + jsonString + " >>.", Nakama::ErrorCode::InternalError));
			return false;
		}

		if(d.HasMember("live_events")) {
			if(!d["live_events"].IsArray()) {
				return false;
			}
			for (auto& jsonLiveEvent : d["live_events"].GetArray()) {
				SLiveEvent liveEvent;
				if(!jsonValueToSLiveEvent(jsonLiveEvent, liveEvent)) {
					return false;
				}
				this->live_events.emplace_back(liveEvent);
			}
		}
		return true;
	}

	bool jsonValueToSProperties(const rapidjson::Value& input, SProperties& output){
		if(input.HasMember("default") && !jsonValueToStringMap(input["default"], output.default_properties)) {
			return false;
		}
		if(input.HasMember("computed") && !jsonValueToStringMap(input["computed"], output.computed_properties)) {
			return false;
		}
		if(input.HasMember("custom") && !jsonValueToStringMap(input["custom"], output.custom_properties)) {
			return false;
		}
		return true;
	}

	bool SInternalProperties::fromJson(std::string jsonString) {
		rapidjson::Document d;
		if(d.ParseInsitu(jsonString.data()).HasParseError()) {
			NLOG_ERROR(Nakama::NError("Parse SProperties JSON failed. Error at " + std::to_string(d.GetErrorOffset()) + ": " + std::string(GetParseError_En(d.GetParseError())) + " HTTP body:<< " + jsonString + " >>.", Nakama::ErrorCode::InternalError));
			return false;
		}
		return jsonValueToSProperties(d, *this);
	}

	bool SInternalSession::fromJson(std::string jsonString) {
		rapidjson::Document d;
		if(d.ParseInsitu(jsonString.data()).HasParseError()) {
			NLOG_ERROR(Nakama::NError("Parse SSession JSON failed. Error at " + std::to_string(d.GetErrorOffset()) + ": " + std::string(GetParseError_En(d.GetParseError())) + " HTTP body:<< " + jsonString + " >>.", Nakama::ErrorCode::InternalError));
			return false;
		}
		// TODO: Error handling! Now if some field is not as expected, it just crashes. Example at: https://github.com/Tencent/rapidjson/blob/master/example/tutorial/tutorial.cpp
		this->token = d["token"].GetString();
		this->refresh_token = d["refresh_token"].GetString();
		return jsonValueToSProperties(d["properties"], this->properties);
	}

	bool SInternalUpdatePropertiesRequest::fromJson(std::string jsonString) {

		return false;
	}

	bool SInternalGetMessageListRequest::fromJson(std::string jsonString) {

		return false;
	}

	bool jsonValueToSMessage(const rapidjson::Value& input, SMessage& output){
		if(input.HasMember("schedule_id") && !input["schedule_id"].IsString()) {
			return false;
		}
		output.schedule_id = input["schedule_id"].GetString();
		if(input.HasMember("send_time") && !input["send_time"].IsInt64()) {
			return false;
		}
		output.send_time = input["send_time"].GetInt64();
		if(input.HasMember("metadata") && !jsonValueToStringMap(input["metadata"], output.metadata)) {
			return false;
		}
		if(input.HasMember("create_time") && !input["create_time"].IsInt64()) {
			return false;
		}
		output.create_time = input["create_time"].GetInt64();
		if(input.HasMember("update_time") && !input["update_time"].IsInt64()) {
			return false;
		}
		output.update_time = input["update_time"].GetInt64();
		if(input.HasMember("read_time") && !input["read_time"].IsInt64()) {
			return false;
		}
		output.read_time = input["read_time"].GetInt64();
		if(input.HasMember("consume_time") && !input["consume_time"].IsInt64()) {
			return false;
		}
		output.consume_time = input["consume_time"].GetInt64();
		if(input.HasMember("text") && !input["text"].IsString()) {
			return false;
		}
		output.text = input["text"].GetString();
		if(input.HasMember("id") && !input["id"].IsString()) {
			return false;
		}
		output.id = input["id"].GetString();
		if(input.HasMember("title") && !input["title"].IsString()) {
			return false;
		}
		output.title = input["title"].GetString();
		if(input.HasMember("image_url") && !input["image_url"].IsString()) {
			return false;
		}
		output.image_url = input["image_url"].GetString();
		return true;
	}

	bool SInternalMessage::fromJson(std::string jsonString) {
		rapidjson::Document d;
		if(d.ParseInsitu(jsonString.data()).HasParseError()) {
			NLOG_ERROR(Nakama::NError("Parse SMessage JSON failed. Error at " + std::to_string(d.GetErrorOffset()) + ": " + std::string(GetParseError_En(d.GetParseError())) + " HTTP body:<< " + jsonString + " >>.", Nakama::ErrorCode::InternalError));
			return false;
		}
		return jsonValueToSMessage(d, *this);
	}

	bool SInternalGetMessageListResponse::fromJson(std::string jsonString) {
		rapidjson::Document d;
		if(d.ParseInsitu(jsonString.data()).HasParseError()) {
			NLOG_ERROR(Nakama::NError("Parse SGetMessageListResponse JSON failed. Error at " + std::to_string(d.GetErrorOffset()) + ": " + std::string(GetParseError_En(d.GetParseError())) + " HTTP body:<< " + jsonString + " >>.", Nakama::ErrorCode::InternalError));
			return false;
		}
		if(d.HasMember("messages")) {
			if(!d["messages"].IsArray()) {
				return false;
			}
			for (auto& jsonMessage : d["messages"].GetArray()) {
				SMessage message;
				if(!jsonValueToSMessage(jsonMessage, message)) {
					return false;
				}
				this->messages.emplace_back(message);
			}
		}
		if(d.HasMember("next_cursor") && !d["next_cursor"].IsString()) {
			return false;
		}
		this->next_cursor = d["next_cursor"].GetString();
		if(d.HasMember("prev_cursor") && !d["prev_cursor"].IsString()) {
			return false;
		}
		this->prev_cursor = d["prev_cursor"].GetString();
		if(d.HasMember("cacheable_cursor") && !d["cacheable_cursor"].IsString()) {
			return false;
		}
		this->cacheable_cursor = d["cacheable_cursor"].GetString();
		return true;
	}

	bool SInternalUpdateMessageRequest::fromJson(std::string jsonString) {

		return false;
	}

	bool SInternalDeleteMessageRequest::fromJson(std::string jsonString) {

		return false;
	}
}
