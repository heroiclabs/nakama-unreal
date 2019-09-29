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

    typedef struct NAKAMA_API NSession_ { char c; }* NSession;

    /**
     * @param session The session.
     * @return The authentication token used to construct this session.
     */
    NAKAMA_API const char* NSession_getAuthToken(NSession session);

    /**
     * @param session The session.
     * @return <c>True</c> if the user account for this session was just created.
     */
    NAKAMA_API bool NSession_isCreated(NSession session);

    /**
     * @param session The session.
     * @return The username of the user who owns this session.
     */
    NAKAMA_API const char* NSession_getUsername(NSession session);

    /**
     * @param session The session.
     * @return The ID of the user who owns this session.
     */
    NAKAMA_API const char* NSession_getUserId(NSession session);

    /**
     * @param session The session.
     * @return The timestamp in milliseconds when this session object was created.
     */
    NAKAMA_API NTimestamp NSession_getCreateTime(NSession session);

    /**
     * @param session The session.
     * @return The timestamp in milliseconds when this session will expire.
     */
    NAKAMA_API NTimestamp NSession_getExpireTime(NSession session);

    /**
     * @param session The session.
     * @return <c>True</c> if the session has expired against the current time.
     */
    NAKAMA_API bool NSession_isExpired(NSession session);

    /**
     * Check if the session has expired against the input time.
     *
     * @param session The session.
     * @param now The time to compare against the session.
     *        Use getUnixTimestampMs() to get current time.
     * @return <c>true</c> if the session has expired.
     */
    NAKAMA_API bool NSession_isExpiredByTime(NSession session, NTimestamp now);

    /**
     * Get session variables.
     *
     * @param session The session.
     * @return NStringMap. Delete it after usage with NStringMap_destroy()
     */
    NAKAMA_API NStringMap NSession_getVariables(NSession session);

    /**
     * Get session variable value by name.
     *
     * @param session The session.
     * @return variable value or NULL if not found.
     */
    NAKAMA_API const char* NSession_getVariable(NSession session, const char* name);

    /**
     * Restore a session from an authentication token.
     *
     * @param token The authentication token from a <c>NSession</c>.
     * @return A session restored from the authentication token.
     */
    NAKAMA_API NSession restoreNakamaSession(const char* token);

    /**
     * Destroy a session.
     *
     * @param session The session.
     */
    NAKAMA_API void NSession_destroy(NSession session);

#ifdef __cplusplus
}
#endif
