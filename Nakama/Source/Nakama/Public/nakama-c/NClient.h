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

#include "nakama-c/NSession.h"
#include "nakama-c/NError.h"
#include "nakama-c/data/NAccount.h"
#include "nakama-c/data/NGroup.h"
#include "nakama-c/data/NGroupList.h"
#include "nakama-c/data/NGroupUserList.h"
#include "nakama-c/data/NUsers.h"
#include "nakama-c/data/NUserGroupList.h"
#include "nakama-c/data/NFriendList.h"
#include "nakama-c/data/NLeaderboardRecordList.h"
#include "nakama-c/data/NMatchList.h"
#include "nakama-c/data/NNotificationList.h"
#include "nakama-c/data/NChannelMessageList.h"
#include "nakama-c/data/NTournamentList.h"
#include "nakama-c/data/NTournamentRecordList.h"
#include "nakama-c/data/NStorageObjectList.h"
#include "nakama-c/data/NStorageObjectAck.h"
#include "nakama-c/data/NStorageObjectWrite.h"
#include "nakama-c/data/NStorageObjectId.h"
#include "nakama-c/data/NRpc.h"
#include "nakama-c/NStringMap.h"
#include "nakama-c/realtime/NRtClient.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct NAKAMA_API NClient_ { char c; }* NClient;
    typedef void* NClientReqData;
    typedef void (*NClientDefaultErrorCallback)(NClient client, const sNError*);
    typedef void (*NClientErrorCallback)(NClient client, NClientReqData reqData, const sNError*);
    typedef void (*NSessionCallback)(NClient client, NClientReqData reqData, NSession);
    typedef void (*NSuccessEmptyCallback)(NClient client, NClientReqData reqData);

    /**
     * A client to interact with Nakama server.
     */

    /**
     * Set default error callback.
     *
     * Will be called if a request fails and no error callback was set for the request.
     *
     * @param errorCallback The error callback.
     */
    NAKAMA_API void NClient_setErrorCallback(NClient client, NClientDefaultErrorCallback errorCallback);

    /**
     * Set user data.
     *
     * Client just holds this data so you can receive it later when you need it.
     *
     * @param userData The user data.
     */
    NAKAMA_API void NClient_setUserData(NClient client, void* userData);

    /**
     * Get user data.
     *
     * @return The user data.
     */
    NAKAMA_API void* NClient_getUserData(NClient client);

    /**
     * Disconnects the client. This function kills all outgoing exchanges immediately without waiting.
     */
    NAKAMA_API void NClient_disconnect(NClient client);

    /**
     * Pumps requests queue in your thread.
     * Call it periodically, each 50 ms is ok.
     */
    NAKAMA_API void NClient_tick(NClient client);

    /**
     * Create a new real-time client with parameters from client.
     *
     * @param port The port number of the server.
     *        Set NDEFAULT_PORT then: 7350 for non-SSL connection, 443 for SSL.
     * @return a new NRtClient instance.
     */
    NAKAMA_API NRtClient NClient_createRtClient(NClient client, int32_t port);
    
    /**
     * Create a new real-time client with custom parameters.
     *
     * @param parameters The real-time client parameters.
     * @return a new NRtClient instance.
     */
    NAKAMA_API NRtClient NClient_createRtClientEx(NClient client, const sRtClientParameters* parameters);

    /**
     * Authenticate a user with a device id.
     *
     * @param id A device identifier usually obtained from a platform API.
     * @param username A username used to create the user. Defaults to empty string.
     * @param create True if the user should be created when authenticated. Defaults to false.
     */
    NAKAMA_API void NClient_authenticateDevice(
        NClient client,
        const char* id,
        const char* username,              // optional, pass NULL
        bool create,
        NStringMap vars,                   // optional, pass NULL
        NClientReqData reqData,            // optional, pass NULL
        NSessionCallback successCallback,  // optional, pass NULL
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * Authenticate a user with an email and password.
     *
     * @param email The email address of the user.
     * @param password The password for the user.
     * @param username A username used to create the user.
     * @param create True if the user should be created when authenticated.
     */
    NAKAMA_API void NClient_authenticateEmail(
        NClient client,
        const char* email,
        const char* password,
        const char* username,              // optional, pass NULL
        bool create,
        NStringMap vars,                   // optional, pass NULL
        NClientReqData reqData,            // optional, pass NULL
        NSessionCallback successCallback,  // optional, pass NULL
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * Authenticate a user with a Facebook auth token.
     *
     * @param accessToken An OAuth access token from the Facebook SDK.
     * @param username A username used to create the user.
     * @param create True if the user should be created when authenticated.
     * @param importFriends True if the Facebook friends should be imported.
     */
    NAKAMA_API void NClient_authenticateFacebook(
        NClient client,
        const char* accessToken,
        const char* username,              // optional, pass NULL
        bool create,
        bool importFriends,
        NStringMap vars,                   // optional, pass NULL
        NClientReqData reqData,            // optional, pass NULL
        NSessionCallback successCallback,  // optional, pass NULL
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * Authenticate a user with a Google auth token.
     *
     * @param accessToken An OAuth access token from the Google SDK.
     * @param username A username used to create the user.
     * @param create True if the user should be created when authenticated.
     */
    NAKAMA_API void NClient_authenticateGoogle(
        NClient client,
        const char* accessToken,
        const char* username,              // optional, pass NULL
        bool create,
        NStringMap vars,                   // optional, pass NULL
        NClientReqData reqData,            // optional, pass NULL
        NSessionCallback successCallback,  // optional, pass NULL
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * Authenticate a user with Apple Game Center.
     *
     * @param playerId The player id of the user in Game Center.
     * @param bundleId The bundle id of the Game Center application.
     * @param timestampSeconds The date and time that the signature was created.
     * @param salt A random <c>NSString</c> used to compute the hash and keep it randomized.
     * @param signature The verification signature data generated.
     * @param publicKeyUrl The URL for the public encryption key.
     * @param create True if the user should be created when authenticated.
     * @param username A username used to create the user.
     */
    NAKAMA_API void NClient_authenticateGameCenter(
        NClient client,
        const char* playerId,
        const char* bundleId,
        NTimestamp timestampSeconds,
        const char* salt,
        const char* signature,
        const char* publicKeyUrl,
        const char* username,              // optional, pass NULL
        bool create,
        NStringMap vars,                   // optional, pass NULL
        NClientReqData reqData,            // optional, pass NULL
        NSessionCallback successCallback,  // optional, pass NULL
        NClientErrorCallback errorCallback // optional, pass NULL
    );

	/**
     * Authenticate a user with a custom id.
     *
     * @param id A custom identifier usually obtained from an external authentication service.
     * @param username A username used to create the user.
     * @param create True if the user should be created when authenticated.
     */
    NAKAMA_API void NClient_authenticateCustom(
        NClient client,
        const char* id,
        const char* username,              // optional, pass NULL
        bool create,
        NStringMap vars,                   // optional, pass NULL
        NClientReqData reqData,            // optional, pass NULL
        NSessionCallback successCallback,  // optional, pass NULL
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * Authenticate a user with a Steam auth token.
     *
     * @param token An authentication token from the Steam network.
     * @param username A username used to create the user.
     * @param create True if the user should be created when authenticated.
     */
    NAKAMA_API void NClient_authenticateSteam(
        NClient client,
        const char* token,
        const char* username,              // optional, pass NULL
        bool create,
        NStringMap vars,                   // optional, pass NULL
        NClientReqData reqData,            // optional, pass NULL
        NSessionCallback successCallback,  // optional, pass NULL
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * Link a Facebook profile to a user account.
     *
     * @param session The session of the user.
     * @param accessToken An OAuth access token from the Facebook SDK.
     * @param importFriends True if the Facebook friends should be imported.
     */
    NAKAMA_API void NClient_linkFacebook(
        NClient client,
        NSession session,
        const char* accessToken,
        bool importFriends,
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData),     // optional, pass NULL
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * Link an email with password to the user account owned by the session.
     *
     * @param session The session of the user.
     * @param email The email address of the user.
     * @param password The password for the user.
     */
    NAKAMA_API void NClient_linkEmail(
        NClient client,
        NSession session,
        const char* email,
        const char* password,
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData), // optional, pass NULL
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * Link a device id to the user account owned by the session.
     *
     * @param session The session of the user.
     * @param id A device identifier usually obtained from a platform API.
     */
    NAKAMA_API void NClient_linkDevice(
        NClient client,
        NSession session,
        const char* id,
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData), // optional, pass NULL
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * Link a Google profile to a user account.
     *
     * @param session The session of the user.
     * @param accessToken An OAuth access token from the Google SDK.
     */
    NAKAMA_API void NClient_linkGoogle(
        NClient client,
        NSession session,
        const char* accessToken,
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData), // optional, pass NULL
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * Link a Game Center profile to a user account.
     *
     * @param session The session of the user.
     * @param playerId The player id of the user in Game Center.
     * @param bundleId The bundle id of the Game Center application.
     * @param timestampSeconds The date and time that the signature was created.
     * @param salt A random <c>NSString</c> used to compute the hash and keep it randomized.
     * @param signature The verification signature data generated.
     * @param publicKeyUrl The URL for the public encryption key.
     */
    NAKAMA_API void NClient_linkGameCenter(
        NClient client,
        NSession session,
        const char* playerId,
        const char* bundleId,
        NTimestamp timestampSeconds,
        const char* salt,
        const char* signature,
        const char* publicKeyUrl,
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData), // optional, pass NULL
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * Link a Steam profile to a user account.
     *
     * @param session The session of the user.
     * @param token An authentication token from the Steam network.
     */
    NAKAMA_API void NClient_linkSteam(
        NClient client,
        NSession session,
        const char* token,
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData), // optional, pass NULL
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * Link a custom id to the user account owned by the session.
     *
     * @param session The session of the user.
     * @param id A custom identifier usually obtained from an external authentication service.
     */
    NAKAMA_API void NClient_linkCustom(
        NClient client,
        NSession session,
        const char* id,
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData), // optional, pass NULL
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * Unlink a Facebook profile from the user account owned by the session.
     *
     * @param session The session of the user.
     * @param accessToken An OAuth access token from the Facebook SDK.
     */
    NAKAMA_API void NClient_unlinkFacebook(
        NClient client,
        NSession session,
        const char* accessToken,
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData), // optional, pass NULL
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * Unlink an email with password from the user account owned by the session.
     *
     * @param session The session of the user.
     * @param email The email address of the user.
     * @param password The password for the user.
     */
    NAKAMA_API void NClient_unlinkEmail(
        NClient client,
        NSession session,
        const char* email,
        const char* password,
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData), // optional, pass NULL
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * Unlink a Google profile from the user account owned by the session.
     *
     * @param session The session of the user.
     * @param accessToken An OAuth access token from the Google SDK.
     */
    NAKAMA_API void NClient_unlinkGoogle(
        NClient client,
        NSession session,
        const char* accessToken,
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData), // optional, pass NULL
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * Unlink a Game Center profile from the user account owned by the session.
     *
     * @param session The session of the user.
     * @param playerId The player id of the user in Game Center.
     * @param bundleId The bundle id of the Game Center application.
     * @param timestampSeconds The date and time that the signature was created.
     * @param salt A random <c>NSString</c> used to compute the hash and keep it randomized.
     * @param signature The verification signature data generated.
     * @param publicKeyUrl The URL for the public encryption key.
     */
    NAKAMA_API void NClient_unlinkGameCenter(
        NClient client,
        NSession session,
        const char* playerId,
        const char* bundleId,
        NTimestamp timestampSeconds,
        const char* salt,
        const char* signature,
        const char* publicKeyUrl,
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData), // optional, pass NULL
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * Unlink a Steam profile from the user account owned by the session.
     *
     * @param session The session of the user.
     * @param token An authentication token from the Steam network.
     */
    NAKAMA_API void NClient_unlinkSteam(
        NClient client,
        NSession session,
        const char* token,
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData), // optional, pass NULL
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * Unlink a device id from the user account owned by the session.
     *
     * @param session The session of the user.
     * @param id A device identifier usually obtained from a platform API.
     */
    NAKAMA_API void NClient_unlinkDevice(
        NClient client,
        NSession session,
        const char* id,
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData), // optional, pass NULL
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * Unlink a custom id from the user account owned by the session.
     *
     * @param session The session of the user.
     * @param id A custom identifier usually obtained from an external authentication service.
     */
    NAKAMA_API void NClient_unlinkCustom(
        NClient client,
        NSession session,
        const char* id,
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData), // optional, pass NULL
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * Import Facebook friends and add them to the user's account.
     *
     * The server will import friends when the user authenticates with Facebook. This function can be used to be
     * explicit with the import operation.
     *
     * @param session The session of the user.
     * @param token An OAuth access token from the Facebook SDK.
     * @param reset True if the Facebook friend import for the user should be reset.
     */
    NAKAMA_API void NClient_importFacebookFriends(
        NClient client,
        NSession session,
        const char* token,
        bool reset,
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData), // optional, pass NULL
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * Fetch the user account owned by the session.
     *
     * @param session The session of the user.
     */
    NAKAMA_API void NClient_getAccount(
        NClient client,
        NSession session,
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData, const sNAccount*),  // optional, pass NULL
        NClientErrorCallback errorCallback          // optional, pass NULL
    );

    /**
     * Update the current user's account on the server.
     *
     * @param session The session for the user.
     * @param username The new username for the user.
     * @param displayName A new display name for the user.
     * @param avatarUrl A new avatar url for the user.
     * @param langTag A new language tag in BCP-47 format for the user.
     * @param location A new location for the user.
     * @param timezone New timezone information for the user.
     */
    NAKAMA_API void NClient_updateAccount(
        NClient client,
        NSession session,
        const char* username,              // optional, pass NULL
        const char* displayName,           // optional, pass NULL
        const char* avatarUrl,             // optional, pass NULL
        const char* langTag,               // optional, pass NULL
        const char* location,              // optional, pass NULL
        const char* timezone,              // optional, pass NULL
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData),  // optional, pass NULL
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * Fetch one or more users by id, usernames, and Facebook ids.
     *
     * @param session The session of the user.
     * @param ids List of user IDs. This is list of strings, delimiter is \0, end of list is \0\0
     * @param usernames List of usernames. This is list of strings, delimiter is \0, end of list is \0\0
     * @param facebookIds List of Facebook IDs. This is list of strings, delimiter is \0, end of list is \0\0
     */
    NAKAMA_API void NClient_getUsers(
        NClient client,
        NSession session,
        const char** ids,                         // optional, pass NULL
        uint16_t idsCount,
        const char** usernames,                   // optional, pass NULL
        uint16_t usernamesCount,
        const char** facebookIds,                 // optional, pass NULL
        uint16_t facebookIdsCount,
        NClientReqData reqData,                   // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData, const sNUsers*),
        NClientErrorCallback errorCallback        // optional, pass NULL
    );

    /**
     * Add one or more friends by id.
     *
     * @param session The session of the user.
     * @param ids The ids of the users to add or invite as friends.
     * @param usernames The usernames of the users to add as friends.
     */
    NAKAMA_API void NClient_addFriends(
        NClient client,
        NSession session,
        const char** ids,                   // optional, pass NULL
        uint16_t idsCount,
        const char** usernames,             // optional, pass NULL
        uint16_t usernamesCount,
        NClientReqData reqData,             // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData),   // optional, pass NULL
        NClientErrorCallback errorCallback  // optional, pass NULL
    );

    /**
     * Delete one more or users by id or username from friends.
     *
     * @param session The session of the user.
     * @param ids the user ids to remove as friends.
     * @param usernames The usernames to remove as friends.
     */
    NAKAMA_API void NClient_deleteFriends(
        NClient client,
        NSession session,
        const char** ids,                   // optional, pass NULL
        uint16_t idsCount,
        const char** usernames,             // optional, pass NULL
        uint16_t usernamesCount,
        NClientReqData reqData,             // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData),   // optional, pass NULL
        NClientErrorCallback errorCallback  // optional, pass NULL
    );

    /**
     * Block one or more friends by id.
     *
     * @param session The session of the user.
     * @param ids The ids of the users to block.
     * @param usernames The usernames of the users to block.
     */
    NAKAMA_API void NClient_blockFriends(
        NClient client,
        NSession session,
        const char** ids,                   // optional, pass NULL
        uint16_t idsCount,
        const char** usernames,             // optional, pass NULL
        uint16_t usernamesCount,
        NClientReqData reqData,             // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData),   // optional, pass NULL
        NClientErrorCallback errorCallback  // optional, pass NULL
    );

    /**
     * List of friends of the current user.
     *
     * @param session The session of the user.
     */
    NAKAMA_API void NClient_listFriends(
        NClient client,
        NSession session,
        const int32_t* limit,              // optional, pass NULL
        const eFriendState* state,         // optional, pass NULL
        const char* cursor,                // optional, pass NULL
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData, const sNFriendList*),
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * Create a group.
     *
     * @param session The session of the user.
     * @param name The name for the group.
     * @param description A description for the group.
     * @param avatarUrl An avatar url for the group.
     * @param langTag A language tag in BCP-47 format for the group.
     * @param open True if the group should have open membership.
     */
    NAKAMA_API void NClient_createGroup(
        NClient client,
        NSession session,
        const char* name,
        const char* description,   // optional, pass NULL
        const char* avatarUrl,     // optional, pass NULL
        const char* langTag,       // optional, pass NULL
        bool open,
        const int32_t* maxCount,   // optional, pass NULL
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData, const sNGroup*),
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * Delete a group by id.
     *
     * @param session The session of the user.
     * @param groupId The group id to to remove.
     */
    NAKAMA_API void NClient_deleteGroup(
        NClient client,
        NSession session,
        const char* groupId,
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData), // optional, pass NULL
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * Add one or more users to the group.
     *
     * @param session The session of the user.
     * @param groupId The id of the group to add users into.
     * @param ids The ids of the users to add or invite to the group.
     */
    NAKAMA_API void NClient_addGroupUsers(
        NClient client,
        NSession session,
        const char* groupId,
        const char** ids,
        uint16_t idsCount,
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData), // optional, pass NULL
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * List all users part of the group.
     *
     * @param session The session of the user.
     * @param groupId The id of the group.
     */
    NAKAMA_API void NClient_listGroupUsers(
        NClient client,
        NSession session,
        const char* groupId,
        const int32_t* limit,              // optional, pass NULL
        const eFriendState* state,         // optional, pass NULL
        const char* cursor,                // optional, pass NULL
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData, const sNGroupUserList*),
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * Kick one or more users from the group.
     *
     * @param session The session of the user.
     * @param groupId The id of the group.
     * @param ids The ids of the users to kick.
     */
    NAKAMA_API void NClient_kickGroupUsers(
        NClient client,
        NSession session,
        const char* groupId,
        const char** ids,  // array of pointers to strings
        uint16_t idsCount,
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData), // optional, pass NULL
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * Join a group if it has open membership or request to join it.
     *
     * @param session The session of the user.
     * @param groupId The id of the group to join.
     */
    NAKAMA_API void NClient_joinGroup(
        NClient client,
        NSession session,
        const char* groupId,
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData), // optional, pass NULL
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * Leave a group by id.
     *
     * @param session The session of the user.
     * @param groupId The id of the group to leave.
     */
    NAKAMA_API void NClient_leaveGroup(
        NClient client,
        NSession session,
        const char* groupId,
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData), // optional, pass NULL
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * List groups on the server.
     *
     * @param session The session of the user.
     * @param name The name filter to apply to the group list.
     * @param limit The number of groups to list.
     * @param cursor A cursor for the current position in the groups to list.
     */
    NAKAMA_API void NClient_listGroups(
        NClient client,
        NSession session,
        const char* name,
        const int32_t* limit,              // optional, pass NULL
        const char* cursor,                // optional, pass NULL
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData, const sNGroupList*),
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * List of groups the current user is a member of.
     *
     * @param session The session of the user.
     */
    NAKAMA_API void NClient_listOwnUserGroups(
        NClient client,
        NSession session,
        const int32_t* limit,              // optional, pass NULL
        const eFriendState* state,         // optional, pass NULL
        const char* cursor,                // optional, pass NULL
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData, const sNUserGroupList*),
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * List groups a user is a member of.
     *
     * @param session The session of the user.
     * @param userId The id of the user whose groups to list.
     */
    NAKAMA_API void NClient_listUserGroups(
        NClient client,
        NSession session,
        const char* userId,                // optional, pass NULL
        const int32_t* limit,              // optional, pass NULL
        const eFriendState* state,         // optional, pass NULL
        const char* cursor,                // optional, pass NULL
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData, const sNUserGroupList*),
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * Promote one or more users in the group.
     *
     * @param session The session of the user.
     * @param groupId The id of the group to promote users into.
     * @param ids The ids of the users to promote.
     */
    NAKAMA_API void NClient_promoteGroupUsers(
        NClient client,
        NSession session,
        const char* groupId,
        const char** ids,
        uint16_t idsCount,
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData), // optional, pass NULL
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * Update a group.
     *
     * The user must have the correct access permissions for the group.
     *
     * @param session The session of the user.
     * @param groupId The id of the group to update.
     * @param name A new name for the group.
     * @param description A new description for the group.
     * @param avatarUrl A new avatar url for the group.
     * @param langTag A new language tag in BCP-47 format for the group.
     * @param open True if the group should have open membership.
     */
    NAKAMA_API void NClient_updateGroup(
        NClient client,
        NSession session,
        const char* groupId,
        const char* name, // optional, pass NULL
        const char* description, // optional, pass NULL
        const char* avatarUrl, // optional, pass NULL
        const char* langTag, // optional, pass NULL
        const bool* open, // optional, pass NULL
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData), // optional, pass NULL
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * List records from a leaderboard.
     *
     * @param session The session of the user.
     * @param leaderboardId The id of the leaderboard to list.
     * @param ownerIds Record owners to fetch with the list of records.
     * @param limit The number of records to list.
     * @param cursor A cursor for the current position in the leaderboard records to list.
     */
    NAKAMA_API void NClient_listLeaderboardRecords(
        NClient client,
        NSession session,
        const char* leaderboardId,
        const char** ownerIds,             // optional, pass NULL
        uint16_t ownerIdsCount,
        int32_t limit,                     // optional, pass 0
        const char* cursor,                // optional, pass NULL
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData, const sNLeaderboardRecordList*),
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * List leaderboard records from a given leaderboard around the owner.
     *
     * @param session The session of the user.
     * @param leaderboardId The id of the leaderboard to list.
     * @param ownerId The owner to retrieve records around.
     * @param limit Max number of records to return. Between 1 and 100.
     */
    NAKAMA_API void NClient_listLeaderboardRecordsAroundOwner(
        NClient client,
        NSession session,
        const char* leaderboardId,
        const char* ownerId,
        int32_t limit, // optional, pass 0
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData, const sNLeaderboardRecordList*),
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * Write a record to a leaderboard.
     *
     * @param session The session for the user.
     * @param leaderboardId The id of the leaderboard to write.
     * @param score The score for the leaderboard record.
     * @param subscore The subscore for the leaderboard record.
     * @param metadata The metadata for the leaderboard record.
     */
    NAKAMA_API void NClient_writeLeaderboardRecord(
        NClient client,
        NSession session,
        const char* leaderboardId,
        int64_t score,
        const int64_t* subscore,           // optional, pass NULL
        const char* metadata,              // optional, pass NULL
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData, const sNLeaderboardRecord*),
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * A request to submit a score to a tournament.
     *
     * @param session The session for the user.
     * @param tournamentId The tournament ID to write the record for.
     * @param score The score value to submit.
     * @param subscore  An optional secondary value.
     * @param metadata A JSON object of additional properties.
     */
    NAKAMA_API void NClient_writeTournamentRecord(
        NClient client,
        NSession session,
        const char* tournamentId,
        int64_t score,
        const int64_t* subscore,           // optional, pass NULL
        const char* metadata,              // optional, pass NULL
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData, const sNLeaderboardRecord*),
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * Delete a leaderboard record.
     *
     * @param session The session of the user.
     * @param leaderboardId The id of the leaderboard with the record to be deleted.
     */
    NAKAMA_API void NClient_deleteLeaderboardRecord(
        NClient client,
        NSession session,
        const char* leaderboardId,
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData), // optional, pass NULL
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * Fetch a list of matches active on the server.
     *
     * @param session The session of the user.
     * @param min_size The minimum number of match participants.
     * @param max_size The maximum number of match participants.
     * @param limit The number of matches to list.
     * @param label The label to filter the match list on.
     * @param authoritative <c>true</c> to include authoritative matches.
     */
    NAKAMA_API void NClient_listMatches(
        NClient client,
        NSession session,
        int32_t min_size,                  // optional, pass 0
        int32_t max_size,                  // optional, pass 0
        int32_t limit,                     // optional, pass 0
        const char* label,                 // optional, pass NULL
        bool authoritative,
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData, const sNMatchList*),
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * List notifications for the user with an optional cursor.
     *
     * @param session The session of the user.
     * @param limit The number of notifications to list.
     * @param cacheableCursor A cursor for the current position in notifications to list.
     */
    NAKAMA_API void NClient_listNotifications(
        NClient client,
        NSession session,
        int32_t limit,// optional, pass 0
        const char* cacheableCursor,// optional, pass NULL
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData, const sNNotificationList*),
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * Delete one or more notifications by id.
     *
     * @param session The session of the user.
     * @param notificationIds The notification ids to remove.
     */
    NAKAMA_API void NClient_deleteNotifications(
        NClient client,
        NSession session,
        const char** notificationIds,
        uint16_t notificationIdsCount,
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData), // optional, pass NULL
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * List messages from a chat channel.
     *
     * @param session The session of the user.
     * @param channelId A channel identifier.
     * @param limit The number of chat messages to list.
     * @param cursor A cursor for the current position in the messages history to list.
     * @param forward Fetch messages forward from the current cursor (or the start).
     */
    NAKAMA_API void NClient_listChannelMessages(
        NClient client,
        NSession session,
        const char* channelId,
        int32_t limit,                     // optional, pass 0
        const char* cursor,                // optional, pass NULL
        bool forward,
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData, const sNChannelMessageList*),
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * List active/upcoming tournaments based on given filters.
     *
     * @param session The session of the user.
     * @param categoryStart The start of the categories to include. Defaults to 0.
     * @param categoryEnd The end of the categories to include. Defaults to 128.
     * @param startTime The start time for tournaments. Defaults to current Unix time.
     * @param endTime The end time for tournaments. Defaults to +1 year from current Unix time.
     * @param limit Max number of records to return. Between 1 and 100.
     * @param cursor A next page cursor for listings.
     */
    NAKAMA_API void NClient_listTournaments(
        NClient client,
        NSession session,
        const uint32_t* categoryStart, // optional, pass NULL
        const uint32_t* categoryEnd, // optional, pass NULL
        const uint32_t* startTime, // optional, pass NULL
        const uint32_t* endTime, // optional, pass NULL
        int32_t limit, // optional, pass 0
        const char* cursor, // optional, pass NULL
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData, const sNTournamentList*),
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * List tournament records from a given tournament.
     *
     * @param session The session of the user.
     * @param tournamentId The ID of the tournament to list for.
     * @param limit Max number of records to return. Between 1 and 100.
     * @param cursor A next or previous page cursor.
     * @param ownerIds One or more owners to retrieve records for.
     */
    NAKAMA_API void NClient_listTournamentRecords(
        NClient client,
        NSession session,
        const char* tournamentId,
        int32_t limit,                     // optional, pass 0
        const char* cursor,                // optional, pass NULL
        const char** ownerIds,             // optional, pass NULL
        uint16_t ownerIdsCount,
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData, const sNTournamentRecordList*),
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * List tournament records from a given tournament around the owner.
     *
     * @param session The session of the user.
     * @param tournamentId The ID of the tournament to list for.
     * @param ownerId The owner to retrieve records around.
     * @param limit Max number of records to return. Between 1 and 100.
     */
    NAKAMA_API void NClient_listTournamentRecordsAroundOwner(
        NClient client,
        NSession session,
        const char* tournamentId,
        const char* ownerId,
        int32_t limit,                     // optional, pass 0
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData, const sNTournamentRecordList*),
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * Join a tournament if it has open membership or request to join it.
     *
     * @param session The session of the user.
     * @param tournamentId The id of the tournament to join.
     */
    NAKAMA_API void NClient_joinTournament(
        NClient client,
        NSession session,
        const char* tournamentId,
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData), // optional, pass NULL
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * List storage objects in a collection which have public read access.
     *
     * @param session The session of the user.
     * @param collection The collection to list over.
     * @param limit The number of objects to list.
     * @param cursor A cursor to paginate over the collection.
     */
    NAKAMA_API void NClient_listStorageObjects(
        NClient client,
        NSession session,
        const char* collection,
        int32_t limit, // optional, pass 0
        const char* cursor, // optional, pass NULL
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData, const sNStorageObjectList*),
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * List storage objects in a collection which belong to a specific user and have public read access.
     *
     * @param session The session of the user.
     * @param collection The collection to list over.
     * @param userId The user ID of the user to list objects for.
     * @param limit The number of objects to list.
     * @param cursor A cursor to paginate over the collection.
     */
    NAKAMA_API void NClient_listUsersStorageObjects(
        NClient client,
        NSession session,
        const char* collection,
        const char* userId,
        int32_t limit,                     // optional, pass 0
        const char* cursor,                // optional, pass NULL
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData, const sNStorageObjectList*),
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * Write objects to the storage engine.
     *
     * @param session The session of the user.
     * @param objects The objects to write.
     */
    NAKAMA_API void NClient_writeStorageObjects(
        NClient client,
        NSession session,
        const sNStorageObjectWrite* objects,
        uint16_t objectsCount,
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData, const sNStorageObjectAck* acks, uint16_t count),
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * Read one or more objects from the storage engine.
     *
     * @param session The session of the user.
     * @param objectIds The objects to read.
     */
    NAKAMA_API void NClient_readStorageObjects(
        NClient client,
        NSession session,
        const sNReadStorageObjectId* objectIds,
        uint16_t objectIdsCount,
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData, const sNStorageObject* objects, uint16_t count),
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * Delete one or more storage objects.
     *
     * @param session The session of the user.
     * @param objectIds The ids of the objects to delete.
     */
    NAKAMA_API void NClient_deleteStorageObjects(
        NClient client,
        NSession session,
        const sNDeleteStorageObjectId* objectIds,
        uint16_t objectIdsCount,
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData), // optional, pass NULL
        NClientErrorCallback errorCallback // optional, pass NULL
    );

    /**
     * Execute a Lua function with an input payload on the server.
     *
     * @param session The session of the user.
     * @param id The id of the function to execute on the server.
     * @param payload The payload to send with the function call.
     */
    NAKAMA_API void NClient_rpc(
        NClient client,
        NSession session,
        const char* id,
        const char* payload,               // optional, pass NULL
        NClientReqData reqData,            // optional, pass NULL
        void (*successCallback)(NClient, NClientReqData, const sNRpc*),
        NClientErrorCallback errorCallback // optional, pass NULL
    );

#ifdef __cplusplus
}
#endif
