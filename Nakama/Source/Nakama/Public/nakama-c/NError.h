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
 
#ifdef __cplusplus
extern "C" {
#endif

    /// Error codes
    typedef enum NAKAMA_API NErrorCode
    {
        /// Unknown error
        NErrorCode_Unknown                  = 0,

        /// Some requested entity was not found.
        NErrorCode_NotFound                 = 1,

        /// Some entity that we attempted to create already exists.
        NErrorCode_AlreadyExists            = 2,

        /// Client specified an invalid argument.
        NErrorCode_InvalidArgument          = 3,

        /// The request does not have valid authentication credentials for the operation.
        NErrorCode_Unauthenticated          = 4,

        /// The caller does not have permission to execute the specified operation.
        NErrorCode_PermissionDenied         = 5,

        /// The service is currently unavailable. This is a most likely a transient
        /// condition and may be corrected by retrying with a backoff.
        ///
        /// \warning Although data MIGHT not have been transmitted when this
        /// status occurs, there is NOT A GUARANTEE that the server has not seen
        /// anything. So in general it is unsafe to retry on this status code
        /// if the call is non-idempotent.
        NErrorCode_ConnectionError          = -1,

        /// Internal errors. Means some invariants expected by underlying System has
        /// been broken. If you see one of these errors, Something is very broken.
        NErrorCode_InternalError            = -2,

        /// The request has been cancelled by user.
        NErrorCode_CancelledByUser          = -3
    } tNErrorCode;

    typedef struct NAKAMA_API NError
    {
        const char* message;
        tNErrorCode code;
    } sNError;

    NAKAMA_API const char* NErrorCode_toString(tNErrorCode code);
    NAKAMA_API const char* NError_toString(const sNError* error);

#ifdef __cplusplus
}
#endif
