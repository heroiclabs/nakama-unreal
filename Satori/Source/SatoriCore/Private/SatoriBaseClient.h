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

#pragma once

#include <string>

#include "nakama-cpp/satori/SClientInterface.h"
#include "nakama-cpp/satori/SatoriClientFactory.h"
#include "nakama-cpp/satori/HardcodedLowLevelSatoriAPI.h"

namespace Satori {
	class SatoriBaseClient : public SClientInterface {
	public:
		std::future<SSessionPtr> authenticateAsync(
			const std::string& id,
			const std::unordered_map<std::string,std::string>& defaultProperties,
			const std::unordered_map<std::string,std::string>& customProperties
		) override;

		std::future<SSessionPtr> authenticateRefreshAsync(
			SSessionPtr session
		) override;

		std::future<void> authenticateLogoutAsync(
			SSessionPtr session
		) override;

		std::future<void> deleteIdentityAsync(
			SSessionPtr session
		) override;

		std::future<void> postEventAsync(
			SSessionPtr session,
			const std::vector<SEvent>& events
		) override;

		std::future<SExperimentList> getExperimentsAsync(
			SSessionPtr session,
			const std::vector<std::string>& names
		) override;

		std::future<SFlagList> getFlagsAsync(
			SSessionPtr session,
			const std::vector<std::string>& names
		) override;

		std::future<SLiveEventList> getLiveEventsAsync(
			SSessionPtr session,
			const std::vector<std::string>& liveEventNames
		) override;

		std::future<SSessionPtr> identifyAsync(
			SSessionPtr session,
			const std::string& id,
			const std::unordered_map<std::string,std::string>& defaultProperties,
			const std::unordered_map<std::string,std::string>& customProperties
		) override;

		std::future<SProperties> listIdentityPropertiesAsync(
			SSessionPtr session
		) override;

		std::future<void> updatePropertiesAsync(
			SSessionPtr session,
			const std::unordered_map<std::string, std::string> &defaultProperties,
			const std::unordered_map<std::string, std::string> &customProperties,
			const bool recompute
		) override;

		std::future<SGetMessageListResponse> getMessagesAsync(
			SSessionPtr session,
			int32_t limit,
			bool forward,
			const std::string& cursor
		) override;

		std::future<void> updateMessageAsync(
			SSessionPtr session,
			const std::string& messageId,
			const Nakama::NTimestamp readTime,
			const Nakama::NTimestamp consumeTime
		) override;

		std::future<void> deleteMessageAsync(
			SSessionPtr session,
			const std::string& messageId
		) override;

	protected:
		int _port = 0;
		std::string _host;
		bool _ssl = false;
		std::string _basicAuthMetadata;
		Nakama::ErrorCallback _defaultErrorCallback;
		void* _userData = nullptr;
		Nakama::NPlatformParameters _platformParams;
	};
}
