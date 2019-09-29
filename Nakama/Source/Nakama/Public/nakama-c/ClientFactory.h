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

#include "nakama-c/NClient.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct NAKAMA_API NClientParameters
    {
        /// The key used to authenticate with the server without a session. Defaults to "defaultkey".
        const char* serverKey;

        /// The host address of the server. Defaults to "127.0.0.1".
        const char* host;

        /// The port number of the server.
        /// set NDEFAULT_PORT to use default server ports (can be changed in the server config):
        /// 7349 - gRPC API
        /// 7350 - HTTP API
        /// 443  - gRPC & HTTP API if SSL is enabled
        int32_t port;

        /// Set connection strings to use the secure mode with the server. Defaults to false.
        /// The server must be configured to make use of this option. With HTTP, GRPC, and WebSockets the server must
        /// be configured with an SSL certificate or use a load balancer which performs SSL termination.
        /// For rUDP you must configure the server to expose it's IP address so it can be bundled within session tokens.
        /// See the server documentation for more information.
        bool ssl;
    } tNClientParameters;

    /**
     * Creates a default client to interact with Nakama server.
     * 
     * @param parameters the client parameters
     */
    NAKAMA_API NClient createDefaultNakamaClient(const tNClientParameters* parameters);

    /**
     * Creates the gRPC client to interact with Nakama server.
     *
     * @param parameters the client parameters
     */
    NAKAMA_API NClient createGrpcNakamaClient(const tNClientParameters* parameters);

    /**
     * Creates the REST client (HTTP/1.1) to interact with Nakama server.
     *
     * @param parameters the client parameters
     */
    NAKAMA_API NClient createRestNakamaClient(const tNClientParameters* parameters);

    /**
     * Destroys a client.
     *
     * @param client the client
     */
    NAKAMA_API void destroyNakamaClient(NClient client);

#ifdef __cplusplus
}
#endif
