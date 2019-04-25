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
 
namespace Nakama {

    /// Error codes
    enum class NAKAMA_API ErrorCode
    {
        /// Unknown error
        Unknown                  = 0,

        /// Some requested entity was not found.
        NotFound                 = 1,

        /// Some entity that we attempted to create already exists.
        AlreadyExists            = 2,

        /// Client specified an invalid argument.
        InvalidArgument          = 3,

        /// The request does not have valid authentication credentials for the operation.
        Unauthenticated          = 4,

        /// The caller does not have permission to execute the specified operation.
        PermissionDenied         = 5,

        /// The service is currently unavailable. This is a most likely a transient
        /// condition and may be corrected by retrying with a backoff.
        ///
        /// \warning Although data MIGHT not have been transmitted when this
        /// status occurs, there is NOT A GUARANTEE that the server has not seen
        /// anything. So in general it is unsafe to retry on this status code
        /// if the call is non-idempotent.
        ConnectionError          = -1,

        /// Internal errors. Means some invariants expected by underlying System has
        /// been broken. If you see one of these errors, Something is very broken.
        InternalError            = -2
    };

    struct NAKAMA_API NError
    {
        NError() {}
        explicit NError(const std::string& message, ErrorCode code = ErrorCode::Unknown) :
            message(message), code(code) {}

        std::string message;
        ErrorCode code = ErrorCode::Unknown;
    };

    NAKAMA_API const char* toString(ErrorCode code);
    NAKAMA_API std::string toString(const NError& error);

}
