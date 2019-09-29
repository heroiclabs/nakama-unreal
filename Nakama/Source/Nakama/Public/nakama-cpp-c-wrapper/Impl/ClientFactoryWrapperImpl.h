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

#include "nakama-cpp-c-wrapper/NakamaWrapper.h"
#include "nakama-cpp-c-wrapper/Impl/NClientWrapperImpl.h"
#include "nakama-c/Nakama.h"

NAKAMA_NAMESPACE_BEGIN

static NClientPtr createClient(const NClientParameters& parameters, std::function<::NClient (const tNClientParameters*)> creator)
{
    tNClientParameters cParams;

    cParams.host = parameters.host.c_str();
    cParams.port = parameters.port;
    cParams.serverKey = parameters.serverKey.c_str();
    cParams.ssl = parameters.ssl;

    ::NClient cptr = creator(&cParams);

    if (!cptr)
        return nullptr;

    return NClientPtr(new NClientWrapper(cptr, parameters));
}

NClientPtr createDefaultClient(const NClientParameters& parameters)
{
    return createClient(parameters, [](const tNClientParameters* cParams) { return ::createDefaultNakamaClient(cParams); });
}

NClientPtr createGrpcClient(const NClientParameters& parameters)
{
    return createClient(parameters, [](const tNClientParameters* cParams) { return ::createGrpcNakamaClient(cParams); });
}

NClientPtr createRestClient(const NClientParameters& parameters, NHttpTransportPtr httpTransport)
{
    return createClient(parameters, [](const tNClientParameters* cParams) { return ::createRestNakamaClient(cParams); });
}

NHttpTransportPtr createDefaultHttpTransport()
{
    return nullptr;
}

NAKAMA_NAMESPACE_END
