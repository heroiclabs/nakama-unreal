/*
 * Copyright 2019 The Nakama Authors
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

#include "nakama-cpp/NTypes.h"
#include <functional>
#include <string>
#include <map>
#include <memory>

NAKAMA_NAMESPACE_BEGIN

    using NHttpHeaders = std::map<std::string, std::string>;
    using NHttpQueryArgs = std::multimap<std::string, std::string>;

    enum class NAKAMA_API NHttpReqMethod
    {
        GET,
        POST,
        PUT,
        DEL,
    };

    struct NAKAMA_API NHttpRequest
    {
        NHttpReqMethod method = NHttpReqMethod::POST;
        NHttpHeaders headers;
        NHttpQueryArgs queryArgs;
        std::string path;
        std::string body;
    };

    struct NAKAMA_API NHttpResponse
    {
        int statusCode = 0;            /// HTTP status code, 200 - OK
        std::string body;              /// response body
        std::string errorMessage;      /// error message string
    };

    using NHttpResponsePtr = std::shared_ptr<NHttpResponse>;
    using NHttpResponseCallback = std::function<void (NHttpResponsePtr)>;

    namespace InternalStatusCodes
    {
        static const int CONNECTION_ERROR = 600;            /// This indicates a general connection error
        static const int NOT_INITIALIZED_ERROR = 601;       /// HTTP client is not initialized properly
    }

    /**
     * HTTP transport interface
     */
    class NAKAMA_API NHttpTransportInterface
    {
    public:
        virtual ~NHttpTransportInterface() {}

        virtual void setBaseUri(const std::string& uri) = 0;

        virtual void tick() = 0;

        /**
         * Invoke HTTP request
         */
        virtual void request(const NHttpRequest& req, const NHttpResponseCallback& callback = nullptr) = 0;
    };

    using NHttpTransportPtr = std::shared_ptr<NHttpTransportInterface>;

NAKAMA_NAMESPACE_END
