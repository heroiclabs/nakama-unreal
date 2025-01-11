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

#include "SatoriBaseClient.h"
#include "nakama-cpp/NException.h"

namespace Satori {
	std::future<SSessionPtr> SatoriBaseClient::authenticateAsync(
		const std::string& id,
		const std::unordered_map<std::string,std::string>& defaultProperties,
		const std::unordered_map<std::string,std::string>& customProperties
	) {
		auto promise = std::make_shared<std::promise<SSessionPtr>>();

		authenticate(id, defaultProperties, customProperties,
			[=](const SSessionPtr& session) {
				promise->set_value(session);
			},
			[=](const Nakama::NError& error) {
				promise->set_exception(std::make_exception_ptr<Nakama::NException>(error));
			});

		return promise->get_future();
	}

	std::future<SSessionPtr> SatoriBaseClient::authenticateRefreshAsync(
		SSessionPtr inSession
	) {
		auto promise = std::make_shared<std::promise<SSessionPtr>>();

		authenticateRefresh(inSession,
			[=](const SSessionPtr& outSession) {
				promise->set_value(outSession);
			},
			[=](const Nakama::NError& error) {
				promise->set_exception(std::make_exception_ptr<Nakama::NException>(error));
			});

		return promise->get_future();
	}

	std::future<void> SatoriBaseClient::authenticateLogoutAsync(
		SSessionPtr session
	) {
		std::shared_ptr<std::promise<void>> promise = std::make_shared<std::promise<void>>();

		authenticateLogout(session,
			[=]() {
				promise->set_value();
			},
			[=](const Nakama::NError& error) {
				promise->set_exception(std::make_exception_ptr<Nakama::NException>(error));
			});

		return promise->get_future();
	}

	std::future<void> SatoriBaseClient::deleteIdentityAsync(
		SSessionPtr session
	) {
		std::shared_ptr<std::promise<void>> promise = std::make_shared<std::promise<void>>();

		deleteIdentity(session,
			[=]() {
				promise->set_value();
			},
			[=](const Nakama::NError& error) {
				promise->set_exception(std::make_exception_ptr<Nakama::NException>(error));
			});

		return promise->get_future();
	}

	std::future<void> SatoriBaseClient::postEventAsync(
		SSessionPtr session,
		const std::vector<SEvent> &events
	) {
		std::shared_ptr<std::promise<void>> promise = std::make_shared<std::promise<void>>();

		postEvent(session, events,
			[=]() {
				promise->set_value();
			},
			[=](const Nakama::NError& error) {
				promise->set_exception(std::make_exception_ptr<Nakama::NException>(error));
			});

		return promise->get_future();
	}

	std::future<SExperimentList> SatoriBaseClient::getExperimentsAsync(
		SSessionPtr session,
		const std::vector<std::string> &names
	) {
		std::shared_ptr<std::promise<SExperimentList>> promise = std::make_shared<std::promise<SExperimentList>>();

		getExperiments(session, names,
			[=](const SExperimentList& experiments) {
				promise->set_value(experiments);
			},
			[=](const Nakama::NError& error) {
				promise->set_exception(std::make_exception_ptr<Nakama::NException>(error));
			});

		return promise->get_future();
	}

	std::future<SFlagList> SatoriBaseClient::getFlagsAsync(
		SSessionPtr session,
		const std::vector<std::string>& names
	) {
		std::shared_ptr<std::promise<SFlagList>> promise = std::make_shared<std::promise<SFlagList>>();

		getFlags(session, names,
			[=](const SFlagList& flags) {
				promise->set_value(flags);
			},
			[=](const Nakama::NError& error) {
				promise->set_exception(std::make_exception_ptr<Nakama::NException>(error));
			});

		return promise->get_future();
	}

	std::future<SLiveEventList> SatoriBaseClient::getLiveEventsAsync(
		SSessionPtr session,
		const std::vector<std::string>& liveEventNames
	) {
		std::shared_ptr<std::promise<SLiveEventList>> promise = std::make_shared<std::promise<SLiveEventList>>();

		getLiveEvents(session, liveEventNames,
			[=](const SLiveEventList& liveEvents) {
				promise->set_value(liveEvents);
			},
			[=](const Nakama::NError& error) {
				promise->set_exception(std::make_exception_ptr<Nakama::NException>(error));
			});

		return promise->get_future();
	}

	std::future<SSessionPtr> SatoriBaseClient::identifyAsync(
		SSessionPtr inSession,
		const std::string& id,
		const std::unordered_map<std::string, std::string>& defaultProperties,
		const std::unordered_map<std::string, std::string>& customProperties
	) {
		std::shared_ptr<std::promise<SSessionPtr>> promise = std::make_shared<std::promise<SSessionPtr>>();

		identify(inSession, id, defaultProperties, customProperties,
			[=](const SSessionPtr& outSession) {
				promise->set_value(outSession);
			},
			[=](const Nakama::NError& error) {
				promise->set_exception(std::make_exception_ptr<Nakama::NException>(error));
			});

		return promise->get_future();
	}

	std::future<SProperties> SatoriBaseClient::listIdentityPropertiesAsync(
		SSessionPtr session
	) {
		std::shared_ptr<std::promise<SProperties>> promise = std::make_shared<std::promise<SProperties>>();

		listIdentityProperties(session,
			[=](const SProperties& properties) {
				promise->set_value(properties);
			},
			[=](const Nakama::NError& error) {
				promise->set_exception(std::make_exception_ptr<Nakama::NException>(error));
			});

		return promise->get_future();
	}

	std::future<void> SatoriBaseClient::updatePropertiesAsync(
		SSessionPtr session,
		const std::unordered_map<std::string, std::string>& defaultProperties,
		const std::unordered_map<std::string, std::string>& customProperties,
		const bool recompute
	) {
		std::shared_ptr<std::promise<void>> promise = std::make_shared<std::promise<void>>();

		updateProperties(session, defaultProperties, customProperties, recompute,
			[=]() {
				promise->set_value();
			},
			[=](const Nakama::NError& error) {
				promise->set_exception(std::make_exception_ptr<Nakama::NException>(error));
			});

		return promise->get_future();
	}

	std::future<SGetMessageListResponse> SatoriBaseClient::getMessagesAsync(
		SSessionPtr session,
		int32_t limit,
		bool forward,
		const std::string &cursor
	) {
		std::shared_ptr<std::promise<SGetMessageListResponse>> promise = std::make_shared<std::promise<SGetMessageListResponse>>();

		getMessages(session, limit, forward, cursor,
			[=](const SGetMessageListResponse& messages) {
				promise->set_value(messages);
			},
			[=](const Nakama::NError& error) {
				promise->set_exception(std::make_exception_ptr<Nakama::NException>(error));
			});

		return promise->get_future();
	}

	std::future<void> SatoriBaseClient::updateMessageAsync(
		SSessionPtr session,
		const std::string &messageId,
		const Nakama::NTimestamp readTime,
		const Nakama::NTimestamp consumeTime
	) {
		std::shared_ptr<std::promise<void>> promise = std::make_shared<std::promise<void>>();

		updateMessage(session, messageId, readTime, consumeTime,
			[=]() {
				promise->set_value();
			},
			[=](const Nakama::NError& error) {
				promise->set_exception(std::make_exception_ptr<Nakama::NException>(error));
			});

		return promise->get_future();
	}

	std::future<void> SatoriBaseClient::deleteMessageAsync(
		SSessionPtr session,
		const std::string &messageId
	) {
		std::shared_ptr<std::promise<void>> promise = std::make_shared<std::promise<void>>();

		deleteMessage(session, messageId,
			[=]() {
				promise->set_value();
			},
			[=](const Nakama::NError& error) {
				promise->set_exception(std::make_exception_ptr<Nakama::NException>(error));
			});

		return promise->get_future();
	}
}
