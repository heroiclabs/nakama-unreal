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

#include <string>
#include <functional>
#include <memory>
#include <vector>
#include "nakama-cpp/NSessionInterface.h"
#include "nakama-cpp/realtime/NRtClientInterface.h"
#include "nakama-cpp/NError.h"
#include "nakama-cpp/data/NAccount.h"
#include "nakama-cpp/data/NGroup.h"
#include "nakama-cpp/data/NGroupList.h"
#include "nakama-cpp/data/NGroupUserList.h"
#include "nakama-cpp/data/NUsers.h"
#include "nakama-cpp/data/NUserGroupList.h"
#include "nakama-cpp/data/NFriends.h"
#include "nakama-cpp/data/NLeaderboardRecordList.h"
#include "nakama-cpp/data/NMatchList.h"
#include "nakama-cpp/data/NNotificationList.h"
#include "nakama-cpp/data/NChannelMessageList.h"
#include "nakama-cpp/data/NTournamentList.h"
#include "nakama-cpp/data/NTournamentRecordList.h"
#include "nakama-cpp/data/NStorageObjectList.h"
#include "nakama-cpp/data/NStorageObjectAck.h"
#include "nakama-cpp/data/NStorageObjectWrite.h"
#include "nakama-cpp/data/NStorageObjectId.h"
#include "nakama-cpp/data/NRpc.h"

namespace Nakama {

    using ErrorCallback = std::function<void(const NError&)>;

    /**
     * A client interface to interact with Nakama server.
     */
    class NClientInterface
    {
    public:
        virtual ~NClientInterface() {}

        /**
         * Disconnects the client. This function kills all outgoing exchanges immediately without waiting.
         */
        virtual void disconnect() = 0;

        /**
         * Pumps requests queue in your thread.
         * Call it periodically, each 50 ms is ok.
         */
        virtual void tick() = 0;

        /**
         * Create a new real-time client.
         * @param port The port number of the server. Default is 7350.
         * @param transport The websocket transport. If not set then default websocket transport will be used.
         * @return a new NRtClient instance.
         */
        virtual NRtClientPtr createRtClient(int32_t port = 7350, NRtTransportPtr transport = nullptr) = 0;

        /**
         * Authenticate a user with a device id.
         *
         * @param id A device identifier usually obtained from a platform API.
         * @param username A username used to create the user. Defaults to empty string.
         * @param create True if the user should be created when authenticated. Defaults to false.
         */
        virtual void authenticateDevice(
            const std::string& id,
            const opt::optional<std::string>& username = opt::nullopt,
            const opt::optional<bool>& create = opt::nullopt,
            std::function<void (NSessionPtr)> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
        * Authenticate a user with an email and password.
        *
        * @param email The email address of the user.
        * @param password The password for the user.
        * @param username A username used to create the user.
        * @param create True if the user should be created when authenticated.
        */
        virtual void authenticateEmail(
            const std::string& email,
            const std::string& password,
            const std::string& username = std::string(),
            bool create = false,
            std::function<void(NSessionPtr)> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
        * Authenticate a user with a Facebook auth token.
        *
        * @param accessToken An OAuth access token from the Facebook SDK.
        * @param username A username used to create the user.
        * @param create True if the user should be created when authenticated.
        * @param importFriends True if the Facebook friends should be imported.
        */
        virtual void authenticateFacebook(
            const std::string& accessToken,
            const std::string& username = std::string(),
            bool create = false,
            bool importFriends = false,
            std::function<void(NSessionPtr)> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
        * Authenticate a user with a Google auth token.
        *
        * @param accessToken An OAuth access token from the Google SDK.
        * @param username A username used to create the user.
        * @param create True if the user should be created when authenticated.
        */
        virtual void authenticateGoogle(
            const std::string& accessToken,
            const std::string& username = std::string(),
            bool create = false,
            std::function<void(NSessionPtr)> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

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
        virtual void authenticateGameCenter(
            const std::string& playerId,
            const std::string& bundleId,
            NTimestamp timestampSeconds,
            const std::string& salt,
            const std::string& signature,
            const std::string& publicKeyUrl,
            const std::string& username = std::string(),
            bool create = false,
            std::function<void(NSessionPtr)> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
         * Authenticate a user with a custom id.
         *
         * @param id A custom identifier usually obtained from an external authentication service.
         * @param username A username used to create the user.
         * @param create True if the user should be created when authenticated.
         */
        virtual void authenticateCustom(
            const std::string& id,
            const std::string& username = std::string(),
            bool create = false,
            std::function<void(NSessionPtr)> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
         * Authenticate a user with a Steam auth token.
         *
         * @param token An authentication token from the Steam network.
         * @param username A username used to create the user.
         * @param create True if the user should be created when authenticated.
         */
        virtual void authenticateSteam(
            const std::string& token,
            const std::string& username = std::string(),
            bool create = false,
            std::function<void(NSessionPtr)> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
         * Link a Facebook profile to a user account.
         *
         * @param session The session of the user.
         * @param accessToken An OAuth access token from the Facebook SDK.
         * @param importFriends True if the Facebook friends should be imported.
         */
        virtual void linkFacebook(
            NSessionPtr session,
            const std::string& accessToken,
            const opt::optional<bool>& importFriends = opt::nullopt,
            std::function<void()> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
         * Link an email with password to the user account owned by the session.
         *
         * @param session The session of the user.
         * @param email The email address of the user.
         * @param password The password for the user.
         */
        virtual void linkEmail(
            NSessionPtr session,
            const std::string& email,
            const std::string& password,
            std::function<void()> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
         * Link a device id to the user account owned by the session.
         *
         * @param session The session of the user.
         * @param id A device identifier usually obtained from a platform API.
         */
        virtual void linkDevice(
            NSessionPtr session,
            const std::string& id,
            std::function<void()> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
         * Link a Google profile to a user account.
         *
         * @param session The session of the user.
         * @param accessToken An OAuth access token from the Google SDK.
         */
        virtual void linkGoogle(
            NSessionPtr session,
            const std::string& accessToken,
            std::function<void()> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

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
        virtual void linkGameCenter(
            NSessionPtr session,
            const std::string& playerId,
            const std::string& bundleId,
            NTimestamp timestampSeconds,
            const std::string& salt,
            const std::string& signature,
            const std::string& publicKeyUrl,
            std::function<void()> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
         * Link a Steam profile to a user account.
         *
         * @param session The session of the user.
         * @param token An authentication token from the Steam network.
         */
        virtual void linkSteam(
            NSessionPtr session,
            const std::string& token,
            std::function<void()> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
         * Link a custom id to the user account owned by the session.
         *
         * @param session The session of the user.
         * @param id A custom identifier usually obtained from an external authentication service.
         */
        virtual void linkCustom(
            NSessionPtr session,
            const std::string& id,
            std::function<void()> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
         * Unlink a Facebook profile from the user account owned by the session.
         *
         * @param session The session of the user.
         * @param accessToken An OAuth access token from the Facebook SDK.
         */
        virtual void unlinkFacebook(
            NSessionPtr session,
            const std::string& accessToken,
            std::function<void()> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
         * Unlink an email with password from the user account owned by the session.
         *
         * @param session The session of the user.
         * @param email The email address of the user.
         * @param password The password for the user.
         */
        virtual void unlinkEmail(
            NSessionPtr session,
            const std::string& email,
            const std::string& password,
            std::function<void()> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
         * Unlink a Google profile from the user account owned by the session.
         *
         * @param session The session of the user.
         * @param accessToken An OAuth access token from the Google SDK.
         */
        virtual void unlinkGoogle(
            NSessionPtr session,
            const std::string& accessToken,
            std::function<void()> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

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
        virtual void unlinkGameCenter(
            NSessionPtr session,
            const std::string& playerId,
            const std::string& bundleId,
            NTimestamp timestampSeconds,
            const std::string& salt,
            const std::string& signature,
            const std::string& publicKeyUrl,
            std::function<void()> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
         * Unlink a Steam profile from the user account owned by the session.
         *
         * @param session The session of the user.
         * @param token An authentication token from the Steam network.
         */
        virtual void unlinkSteam(
            NSessionPtr session,
            const std::string& token,
            std::function<void()> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
         * Unlink a device id from the user account owned by the session.
         *
         * @param session The session of the user.
         * @param id A device identifier usually obtained from a platform API.
         */
        virtual void unlinkDevice(
            NSessionPtr session,
            const std::string& id,
            std::function<void()> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
         * Unlink a custom id from the user account owned by the session.
         *
         * @param session The session of the user.
         * @param id A custom identifier usually obtained from an external authentication service.
         */
        virtual void unlinkCustom(
            NSessionPtr session,
            const std::string& id,
            std::function<void()> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

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
        virtual void importFacebookFriends(
            NSessionPtr session,
            const std::string& token,
            const opt::optional<bool>& reset = opt::nullopt,
            std::function<void()> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
         * Fetch the user account owned by the session.
         *
         * @param session The session of the user.
         */
        virtual void getAccount(
            NSessionPtr session,
            std::function<void(const NAccount&)> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

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
        virtual void updateAccount(
            NSessionPtr session,
            const opt::optional<std::string>& username    = opt::nullopt,
            const opt::optional<std::string>& displayName = opt::nullopt,
            const opt::optional<std::string>& avatarUrl   = opt::nullopt,
            const opt::optional<std::string>& langTag     = opt::nullopt,
            const opt::optional<std::string>& location    = opt::nullopt,
            const opt::optional<std::string>& timezone    = opt::nullopt,
            std::function<void()> successCallback         = nullptr,
            ErrorCallback errorCallback                   = nullptr
        ) = 0;

        /**
        * Fetch one or more users by id, usernames, and Facebook ids.
        *
        * @param session The session of the user.
        * @param ids List of user IDs.
        * @param usernames List of usernames.
        * @param facebookIds List of Facebook IDs.
        */
        virtual void getUsers(
            NSessionPtr session,
            const std::vector<std::string>& ids,
            const std::vector<std::string>& usernames = {},
            const std::vector<std::string>& facebookIds = {},
            std::function<void(const NUsers&)> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
         * Add one or more friends by id.
         *
         * @param session The session of the user.
         * @param ids The ids of the users to add or invite as friends.
         * @param usernames The usernames of the users to add as friends.
         */
        virtual void addFriends(
            NSessionPtr session,
            const std::vector<std::string>& ids,
            const std::vector<std::string>& usernames = {},
            std::function<void()> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
         * Delete one more or users by id or username from friends.
         *
         * @param session The session of the user.
         * @param ids the user ids to remove as friends.
         * @param usernames The usernames to remove as friends.
         */
        virtual void deleteFriends(
            NSessionPtr session,
            const std::vector<std::string>& ids,
            const std::vector<std::string>& usernames = {},
            std::function<void()> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
         * Block one or more friends by id.
         *
         * @param session The session of the user.
         * @param ids The ids of the users to block.
         * @param usernames The usernames of the users to block.
         */
        virtual void blockFriends(
            NSessionPtr session,
            const std::vector<std::string>& ids,
            const std::vector<std::string>& usernames = {},
            std::function<void()> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
        * List of friends of the current user.
        *
        * @param session The session of the user.
        */
        virtual void listFriends(
            NSessionPtr session,
            std::function<void(NFriendsPtr)> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

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
        virtual void createGroup(
            NSessionPtr session,
            const std::string& name,
            const std::string& description = "",
            const std::string& avatarUrl = "",
            const std::string& langTag = "",
            bool open = false,
            std::function<void(const NGroup&)> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
         * Delete a group by id.
         *
         * @param session The session of the user.
         * @param groupId The group id to to remove.
         */
        virtual void deleteGroup(
            NSessionPtr session,
            const std::string& groupId,
            std::function<void()> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
         * Add one or more users to the group.
         *
         * @param session The session of the user.
         * @param groupId The id of the group to add users into.
         * @param ids The ids of the users to add or invite to the group.
         */
        virtual void addGroupUsers(
            NSessionPtr session,
            const std::string& groupId,
            const std::vector<std::string>& ids,
            std::function<void()> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
        * List all users part of the group.
        *
        * @param session The session of the user.
        * @param groupId The id of the group.
        */
        virtual void listGroupUsers(
            NSessionPtr session,
            const std::string& groupId,
            std::function<void(NGroupUserListPtr)> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
        * Kick one or more users from the group.
        *
        * @param session The session of the user.
        * @param groupId The id of the group.
        * @param ids The ids of the users to kick.
        */
        virtual void kickGroupUsers(
            NSessionPtr session,
            const std::string& groupId,
            const std::vector<std::string>& ids,
            std::function<void()> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
        * Join a group if it has open membership or request to join it.
        *
        * @param session The session of the user.
        * @param groupId The id of the group to join.
        */
        virtual void joinGroup(
            NSessionPtr session,
            const std::string& groupId,
            std::function<void()> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
        * Leave a group by id.
        *
        * @param session The session of the user.
        * @param groupId The id of the group to leave.
        */
        virtual void leaveGroup(
            NSessionPtr session,
            const std::string& groupId,
            std::function<void()> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
        * List groups on the server.
        *
        * @param session The session of the user.
        * @param name The name filter to apply to the group list.
        * @param limit The number of groups to list.
        * @param cursor A cursor for the current position in the groups to list.
        */
        virtual void listGroups(
            NSessionPtr session,
            const std::string& name,
            int32_t limit = 0,
            const std::string& cursor = "",
            std::function<void(NGroupListPtr)> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
         * List of groups the current user is a member of.
         *
         * @param session The session of the user.
         */
        virtual void listUserGroups(
            NSessionPtr session,
            std::function<void(NUserGroupListPtr)> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
         * List groups a user is a member of.
         *
         * @param session The session of the user.
         * @param userId The id of the user whose groups to list.
         */
        virtual void listUserGroups(
            NSessionPtr session,
            const std::string& userId,
            std::function<void(NUserGroupListPtr)> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
         * Promote one or more users in the group.
         *
         * @param session The session of the user.
         * @param groupId The id of the group to promote users into.
         * @param ids The ids of the users to promote.
         */
        virtual void promoteGroupUsers(
            NSessionPtr session,
            const std::string& groupId,
            const std::vector<std::string>& ids,
            std::function<void()> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

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
        virtual void updateGroup(
            NSessionPtr session,
            const std::string& groupId,
            const opt::optional<std::string>& name = opt::nullopt,
            const opt::optional<std::string>& description = opt::nullopt,
            const opt::optional<std::string>& avatarUrl = opt::nullopt,
            const opt::optional<std::string>& langTag = opt::nullopt,
            const opt::optional<bool>& open = opt::nullopt,
            std::function<void()> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
         * List records from a leaderboard.
         *
         * @param session The session of the user.
         * @param leaderboardId The id of the leaderboard to list.
         * @param ownerIds Record owners to fetch with the list of records.
         * @param limit The number of records to list.
         * @param cursor A cursor for the current position in the leaderboard records to list.
         */
        virtual void listLeaderboardRecords(
            NSessionPtr session,
            const std::string& leaderboardId,
            const std::vector<std::string>& ownerIds = {},
            const opt::optional<int32_t>& limit = opt::nullopt,
            const opt::optional<std::string>& cursor = opt::nullopt,
            std::function<void(NLeaderboardRecordListPtr)> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
        * List leaderboard records from a given leaderboard around the owner.
        *
        * @param session The session of the user.
        * @param leaderboardId The id of the leaderboard to list.
        * @param ownerId The owner to retrieve records around.
        * @param limit Max number of records to return. Between 1 and 100.
        */
        virtual void listLeaderboardRecordsAroundOwner(
            NSessionPtr session,
            const std::string& leaderboardId,
            const std::string& ownerId,
            const opt::optional<int32_t>& limit = opt::nullopt,
            std::function<void(NLeaderboardRecordListPtr)> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
        * Write a record to a leaderboard.
        *
        * @param session The session for the user.
        * @param leaderboardId The id of the leaderboard to write.
        * @param score The score for the leaderboard record.
        * @param subscore The subscore for the leaderboard record.
        * @param metadata The metadata for the leaderboard record.
        */
        virtual void writeLeaderboardRecord(
            NSessionPtr session,
            const std::string& leaderboardId,
            int64_t score,
            const opt::optional<int64_t>& subscore = opt::nullopt,
            const opt::optional<std::string>& metadata = opt::nullopt,
            std::function<void(NLeaderboardRecord)> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
        * A request to submit a score to a tournament.
        *
        * @param session The session for the user.
        * @param tournamentId The tournament ID to write the record for.
        * @param score The score value to submit.
        * @param subscore  An optional secondary value.
        * @param metadata A JSON object of additional properties.
        */
        virtual void writeTournamentRecord(
            NSessionPtr session,
            const std::string& tournamentId,
            int64_t score,
            const opt::optional<int64_t>& subscore = opt::nullopt,
            const opt::optional<std::string>& metadata = opt::nullopt,
            std::function<void(NLeaderboardRecord)> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
        * Delete a leaderboard record.
        *
        * @param session The session of the user.
        * @param leaderboardId The id of the leaderboard with the record to be deleted.
        */
        virtual void deleteLeaderboardRecord(
            NSessionPtr session,
            const std::string& leaderboardId,
            std::function<void()> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

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
        virtual void listMatches(
            NSessionPtr session,
            const opt::optional<int32_t>& min_size = opt::nullopt,
            const opt::optional<int32_t>& max_size = opt::nullopt,
            const opt::optional<int32_t>& limit = opt::nullopt,
            const opt::optional<std::string>& label = opt::nullopt,
            const opt::optional<bool>& authoritative = opt::nullopt,
            std::function<void(NMatchListPtr)> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
        * List notifications for the user with an optional cursor.
        *
        * @param session The session of the user.
        * @param limit The number of notifications to list.
        * @param cacheableCursor A cursor for the current position in notifications to list.
        */
        virtual void listNotifications(
            NSessionPtr session,
            const opt::optional<int32_t>& limit = opt::nullopt,
            const opt::optional<std::string>& cacheableCursor = opt::nullopt,
            std::function<void(NNotificationListPtr)> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
        * Delete one or more notifications by id.
        *
        * @param session The session of the user.
        * @param notificationIds The notification ids to remove.
        */
        virtual void deleteNotifications(
            NSessionPtr session,
            const std::vector<std::string>& notificationIds,
            std::function<void()> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
        * List messages from a chat channel.
        *
        * @param session The session of the user.
        * @param channelId A channel identifier.
        * @param limit The number of chat messages to list.
        * @param cursor A cursor for the current position in the messages history to list.
        * @param forward Fetch messages forward from the current cursor (or the start).
        */
        virtual void listChannelMessages(
            NSessionPtr session,
            const std::string& channelId,
            const opt::optional<int32_t>& limit = opt::nullopt,
            const opt::optional<std::string>& cursor = opt::nullopt,
            const opt::optional<bool>& forward = opt::nullopt,
            std::function<void(NChannelMessageListPtr)> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

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
        virtual void listTournaments(
            NSessionPtr session,
            const opt::optional<uint32_t>& categoryStart = opt::nullopt,
            const opt::optional<uint32_t>& categoryEnd = opt::nullopt,
            const opt::optional<uint32_t>& startTime = opt::nullopt,
            const opt::optional<uint32_t>& endTime = opt::nullopt,
            const opt::optional<int32_t>& limit = opt::nullopt,
            const opt::optional<std::string>& cursor = opt::nullopt,
            std::function<void(NTournamentListPtr)> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
         * List tournament records from a given tournament.
         *
         * @param session The session of the user.
         * @param tournamentId The ID of the tournament to list for.
         * @param limit Max number of records to return. Between 1 and 100.
         * @param cursor A next or previous page cursor.
         * @param ownerIds One or more owners to retrieve records for.
         */
        virtual void listTournamentRecords(
            NSessionPtr session,
            const std::string& tournamentId,
            const opt::optional<int32_t>& limit = opt::nullopt,
            const opt::optional<std::string>& cursor = opt::nullopt,
            const std::vector<std::string>& ownerIds = {},
            std::function<void(NTournamentRecordListPtr)> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
         * List tournament records from a given tournament around the owner.
         *
         * @param session The session of the user.
         * @param tournamentId The ID of the tournament to list for.
         * @param ownerId The owner to retrieve records around.
         * @param limit Max number of records to return. Between 1 and 100.
         */
        virtual void listTournamentRecordsAroundOwner(
            NSessionPtr session,
            const std::string& tournamentId,
            const std::string& ownerId,
            const opt::optional<int32_t>& limit = opt::nullopt,
            std::function<void(NTournamentRecordListPtr)> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
         * Join a tournament if it has open membership or request to join it.
         *
         * @param session The session of the user.
         * @param tournamentId The id of the tournament to join.
         */
        virtual void joinTournament(
            NSessionPtr session,
            const std::string& tournamentId,
            std::function<void()> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
         * List storage objects in a collection which have public read access.
         *
         * @param session The session of the user.
         * @param collection The collection to list over.
         * @param limit The number of objects to list.
         * @param cursor A cursor to paginate over the collection.
         */
        virtual void listStorageObjects(
            NSessionPtr session,
            const std::string& collection,
            const opt::optional<int32_t>& limit = opt::nullopt,
            const opt::optional<std::string>& cursor = opt::nullopt,
            std::function<void(NStorageObjectListPtr)> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
         * List storage objects in a collection which belong to a specific user and have public read access.
         *
         * @param session The session of the user.
         * @param collection The collection to list over.
         * @param userId The user ID of the user to list objects for.
         * @param limit The number of objects to list.
         * @param cursor A cursor to paginate over the collection.
         */
        virtual void listUsersStorageObjects(
            NSessionPtr session,
            const std::string& collection,
            const std::string& userId,
            const opt::optional<int32_t>& limit = opt::nullopt,
            const opt::optional<std::string>& cursor = opt::nullopt,
            std::function<void(NStorageObjectListPtr)> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
         * Write objects to the storage engine.
         *
         * @param session The session of the user.
         * @param objects The objects to write.
         */
        virtual void writeStorageObjects(
            NSessionPtr session,
            const std::vector<NStorageObjectWrite>& objects,
            std::function<void(const NStorageObjectAcks&)> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
         * Read one or more objects from the storage engine.
         *
         * @param session The session of the user.
         * @param objectIds The objects to read.
         */
        virtual void readStorageObjects(
            NSessionPtr session,
            const std::vector<NReadStorageObjectId>& objectIds,
            std::function<void(const NStorageObjects&)> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
         * Delete one or more storage objects.
         *
         * @param session The session of the user.
         * @param objectIds The ids of the objects to delete.
         */
        virtual void deleteStorageObjects(
            NSessionPtr session,
            const std::vector<NDeleteStorageObjectId>& objectIds,
            std::function<void()> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;

        /**
         * Execute a Lua function with an input payload on the server.
         *
         * @param session The session of the user.
         * @param id The id of the function to execute on the server.
         * @param payload The payload to send with the function call.
         */
        virtual void rpc(
            NSessionPtr session,
            const std::string& id,
            const opt::optional<std::string>& payload = opt::nullopt,
            std::function<void(const NRpc&)> successCallback = nullptr,
            ErrorCallback errorCallback = nullptr
        ) = 0;
    };

    using NClientPtr = std::shared_ptr<NClientInterface>;
}
