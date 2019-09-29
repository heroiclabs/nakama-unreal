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

#include "nakama-c/NTypes.h"
#include "nakama-c/NStringMap.h"

#ifdef __cplusplus
extern "C" {
#endif

/// The selection of possible error codes.
typedef enum NAKAMA_API RtErrorCode
{
    // client side errors
    RtErrorCode_CONNECT_ERROR                 = -1,           ///< Connect has failed.
    RtErrorCode_TRANSPORT_ERROR               = -2,           ///< Transport error.
    
    // server side errors
    RtErrorCode_RUNTIME_EXCEPTION             = 0,            ///< An unexpected result from the server.
    RtErrorCode_UNRECOGNIZED_PAYLOAD          = 1,            ///< The server received a message which is not recognised.
    RtErrorCode_MISSING_PAYLOAD               = 2,            ///< A message was expected but contains no content.
    RtErrorCode_BAD_INPUT                     = 3,            ///< Fields in the message have an invalid format.
    RtErrorCode_MATCH_NOT_FOUND               = 4,            ///< The match id was not found.
    RtErrorCode_MATCH_JOIN_REJECTED           = 5,            ///< The match join was rejected.
    RtErrorCode_RUNTIME_FUNCTION_NOT_FOUND    = 6,            ///< The runtime function does not exist on the server.
    RtErrorCode_RUNTIME_FUNCTION_EXCEPTION    = 7             ///< The runtime function executed with an error.
} eRtErrorCode;

/// A logical error which may occur on the server.
typedef struct NAKAMA_API NRtError
{
    eRtErrorCode code;                            ///< The error code
    const char* message;                          ///< A message in English to help developers debug the response.
    NStringMap context;                           ///< Additional error details which may be different for each response.
} sNRtError;

NAKAMA_API const char* RtErrorCode_toString(eRtErrorCode code);

#ifdef __cplusplus
}
#endif
