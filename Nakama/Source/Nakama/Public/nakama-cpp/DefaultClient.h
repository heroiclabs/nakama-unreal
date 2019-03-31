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

#include "nakama-cpp/NClientInterface.h"

namespace Nakama {

    struct DefaultClientParameters
    {
        /// The key used to authenticate with the server without a session. Defaults to "defaultkey".
        std::string serverKey = "defaultkey";

        /// The host address of the server. Defaults to "127.0.0.1".
        std::string host = "127.0.0.1";

        /// The port number of the server. Defaults to 7349.
        int port = 7349;

        /// Set connection strings to use the secure mode with the server. Defaults to false.
        /// The server must be configured to make use of this option. With HTTP, GRPC, and WebSockets the server must
        /// be configured with an SSL certificate or use a load balancer which performs SSL termination.
        /// For rUDP you must configure the server to expose it's IP address so it can be bundled within session tokens.
        /// See the server documentation for more information.
        bool ssl = false;
    };

    /**
     * Creates a default client to interact with Nakama server.
     * 
     * @param parameters the client parameters
     */
    NClientPtr createDefaultClient(const DefaultClientParameters& parameters);

}
