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

#include "nakama-cpp/satori/HardcodedLowLevelSatoriAPI.h"

namespace Satori {
	struct SFromJsonInterface {
		virtual ~SFromJsonInterface() {}
		virtual bool fromJson(std::string jsonString) = 0;
	};

    struct SInternalAuthenticateLogoutRequest : public SAuthenticateLogoutRequest, public SFromJsonInterface {
        bool fromJson(std::string jsonString) override;
    };

    struct SInternalAuthenticateRefreshRequest : public SAuthenticateRefreshRequest, public SFromJsonInterface {
        bool fromJson(std::string jsonString) override;
    };

    struct SInternalAuthenticateRequest : public SAuthenticateRequest, public SFromJsonInterface {
        bool fromJson(std::string jsonString) override;
    };

    struct SInternalEvent : public SEvent, public SFromJsonInterface {
        bool fromJson(std::string jsonString) override;
    };

    struct SInternalEventRequest : public SEventRequest, public SFromJsonInterface {
        bool fromJson(std::string jsonString) override;
    };

    struct SInternalExperiment : public SExperiment, public SFromJsonInterface {
        bool fromJson(std::string jsonString) override;
    };

    struct SInternalExperimentList : public SExperimentList, public SFromJsonInterface {
        bool fromJson(std::string jsonString) override;
    };

    struct SInternalFlag : public SFlag, public SFromJsonInterface {
        bool fromJson(std::string jsonString) override;
    };

    struct SInternalFlagList : public SFlagList, public SFromJsonInterface {
        bool fromJson(std::string jsonString) override;
    };

    struct SInternalGetExperimentsRequest : public SGetExperimentsRequest, public SFromJsonInterface {
        bool fromJson(std::string jsonString) override;
    };

    struct SInternalGetFlagsRequest : public SGetFlagsRequest, public SFromJsonInterface {
        bool fromJson(std::string jsonString) override;
    };

    struct SInternalGetLiveEventsRequest : public SGetLiveEventsRequest, public SFromJsonInterface {
        bool fromJson(std::string jsonString) override;
    };

    struct SInternalIdentifyRequest : public SIdentifyRequest, public SFromJsonInterface {
        bool fromJson(std::string jsonString) override;
    };

    struct SInternalLiveEvent : public SLiveEvent, public SFromJsonInterface {
        bool fromJson(std::string jsonString) override;
    };

    struct SInternalLiveEventList : public SLiveEventList, public SFromJsonInterface {
        bool fromJson(std::string jsonString) override;
    };

    struct SInternalProperties : public SProperties, public SFromJsonInterface {
        bool fromJson(std::string jsonString) override;
    };

    struct SInternalSession : public SSession, public SFromJsonInterface {
        bool fromJson(std::string jsonString) override;
    };

    struct SInternalUpdatePropertiesRequest : public SUpdatePropertiesRequest, public SFromJsonInterface {
        bool fromJson(std::string jsonString) override;
    };

    struct SInternalGetMessageListRequest : public SGetMessageListRequest, public SFromJsonInterface {
        bool fromJson(std::string jsonString) override;
    };

    struct SInternalMessage : public SMessage, public SFromJsonInterface {
        bool fromJson(std::string jsonString) override;
    };

    struct SInternalGetMessageListResponse : public SGetMessageListResponse, public SFromJsonInterface {
        bool fromJson(std::string jsonString) override;
    };

    struct SInternalUpdateMessageRequest : public SUpdateMessageRequest, public SFromJsonInterface {
        bool fromJson(std::string jsonString) override;
    };

    struct SInternalDeleteMessageRequest : public SDeleteMessageRequest, public SFromJsonInterface {
        bool fromJson(std::string jsonString) override;
    };
}