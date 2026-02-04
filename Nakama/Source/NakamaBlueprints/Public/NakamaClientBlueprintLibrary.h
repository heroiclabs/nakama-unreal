/*
 * Copyright 2026 The Nakama Authors
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

/* This code is auto-generated. DO NOT EDIT. */

#pragma once

#include "CoreMinimal.h"
#include "Templates/Function.h"
#include "NakamaClient.h"
#include "NakamaError.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "NakamaClientBlueprintLibrary.generated.h"

using namespace Nakama;

/**
 * Blueprint Library to expose NakamaClient functions.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientBlueprintLibrary : public UBlueprintFunctionLibrary
{
  GENERATED_BODY()

public:

  /**
  * Creates a default client to interact with Nakama server.
  *
  * @param ServerKey Server key should match the one on the Nakama Server.
  * @param Host The endpoint host name.
  * @param Port The port to use, default is 7350.
  * @param UseSSL Use "https" scheme if you've setup SSL.
  * @param EnableDebug To enable logs output to console with debug logging level.
  */
  UFUNCTION(BlueprintCallable, Category = "Nakama|Client")
  static UNakamaClient* CreateDefaultClient(
    const FString& ServerKey = "defaultkey",
    const FString& Host = "localhost",
    int32 Port = 7350,
    bool UseSSL = false,
    bool EnableDebug = true
  );


  

  
  
  /**
  *
  * Add friends by ID or username to a user's account.
  *
  * @param Ids  The account id of a user.
  * @param Usernames  The account username of a user.
  * @param Metadata  Optional metadata to add to friends.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void AddFriends(
    UNakamaClient* Client,
    const TArray<FString>& Ids,
    const TArray<FString>& Usernames,
    FString Metadata,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Add users to a group.
  *
  * @param GroupId  The group to add users to.
  * @param UserIds  The users to add.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void AddGroupUsers(
    UNakamaClient* Client,
    FString GroupId,
    const TArray<FString>& UserIds,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Refresh a user's session using a refresh token retrieved from a previous authentication request.
  *
  * @param Token  Refresh token.
  * @param Vars  Extra information that will be bundled in the session token.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void SessionRefresh(
    UNakamaClient* Client,
    FString Token,
    TMap<FString, FString> Vars,
    TFunction<void(FNakamaSession)> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Log out a session, invalidate a refresh token, or log out all sessions/refresh tokens for a user.
  *
  * @param Token  Session token to log out.
  * @param RefreshToken  Refresh token to invalidate.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void SessionLogout(
    UNakamaClient* Client,
    FString Token,
    FString RefreshToken,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Authenticate a user with an Apple ID against the server.
  *
  * @param Account  The Apple account details.
  * @param Create  Register the account if the user does not already exist.
  * @param Username  Set the username on the account at register. Must be unique.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void AuthenticateApple(
    UNakamaClient* Client,
    FNakamaAccountApple Account,
    bool Create,
    FString Username,
    TFunction<void(FNakamaSession)> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Authenticate a user with a custom id against the server.
  *
  * @param Account  The custom account details.
  * @param Create  Register the account if the user does not already exist.
  * @param Username  Set the username on the account at register. Must be unique.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void AuthenticateCustom(
    UNakamaClient* Client,
    FNakamaAccountCustom Account,
    bool Create,
    FString Username,
    TFunction<void(FNakamaSession)> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Authenticate a user with a device id against the server.
  *
  * @param Account  The device account details.
  * @param Create  Register the account if the user does not already exist.
  * @param Username  Set the username on the account at register. Must be unique.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void AuthenticateDevice(
    UNakamaClient* Client,
    FNakamaAccountDevice Account,
    bool Create,
    FString Username,
    TFunction<void(FNakamaSession)> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Authenticate a user with an email+password against the server.
  *
  * @param Account  The email account details.
  * @param Create  Register the account if the user does not already exist.
  * @param Username  Set the username on the account at register. Must be unique.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void AuthenticateEmail(
    UNakamaClient* Client,
    FNakamaAccountEmail Account,
    bool Create,
    FString Username,
    TFunction<void(FNakamaSession)> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Authenticate a user with a Facebook OAuth token against the server.
  *
  * @param Account  The Facebook account details.
  * @param Create  Register the account if the user does not already exist.
  * @param Username  Set the username on the account at register. Must be unique.
  * @param Sync  Import Facebook friends for the user.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void AuthenticateFacebook(
    UNakamaClient* Client,
    FNakamaAccountFacebook Account,
    bool Create,
    FString Username,
    bool Sync,
    TFunction<void(FNakamaSession)> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Authenticate a user with a Facebook Instant Game token against the server.
  *
  * @param Account  The Facebook Instant Game account details.
  * @param Create  Register the account if the user does not already exist.
  * @param Username  Set the username on the account at register. Must be unique.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void AuthenticateFacebookInstantGame(
    UNakamaClient* Client,
    FNakamaAccountFacebookInstantGame Account,
    bool Create,
    FString Username,
    TFunction<void(FNakamaSession)> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Authenticate a user with Apple's GameCenter against the server.
  *
  * @param Account  The Game Center account details.
  * @param Create  Register the account if the user does not already exist.
  * @param Username  Set the username on the account at register. Must be unique.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void AuthenticateGameCenter(
    UNakamaClient* Client,
    FNakamaAccountGameCenter Account,
    bool Create,
    FString Username,
    TFunction<void(FNakamaSession)> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Authenticate a user with Google against the server.
  *
  * @param Account  The Google account details.
  * @param Create  Register the account if the user does not already exist.
  * @param Username  Set the username on the account at register. Must be unique.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void AuthenticateGoogle(
    UNakamaClient* Client,
    FNakamaAccountGoogle Account,
    bool Create,
    FString Username,
    TFunction<void(FNakamaSession)> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Authenticate a user with Steam against the server.
  *
  * @param Account  The Steam account details.
  * @param Create  Register the account if the user does not already exist.
  * @param Username  Set the username on the account at register. Must be unique.
  * @param Sync  Import Steam friends for the user.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void AuthenticateSteam(
    UNakamaClient* Client,
    FNakamaAccountSteam Account,
    bool Create,
    FString Username,
    bool Sync,
    TFunction<void(FNakamaSession)> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Ban a set of users from a group.
  *
  * @param GroupId  The group to ban users from.
  * @param UserIds  The users to ban.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void BanGroupUsers(
    UNakamaClient* Client,
    FString GroupId,
    const TArray<FString>& UserIds,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Block one or more users by ID or username.
  *
  * @param Ids  The account id of a user.
  * @param Usernames  The account username of a user.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void BlockFriends(
    UNakamaClient* Client,
    const TArray<FString>& Ids,
    const TArray<FString>& Usernames,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Create a new group with the current user as the owner.
  *
  * @param Name  A unique name for the group.
  * @param Description  A description for the group.
  * @param LangTag  The language expected to be a tag which follows the BCP-47 spec.
  * @param AvatarUrl  A URL for an avatar image.
  * @param Open  Mark a group as open or not where only admins can accept members.
  * @param MaxCount  Maximum number of group members.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void CreateGroup(
    UNakamaClient* Client,
    FString Name,
    FString Description,
    FString LangTag,
    FString AvatarUrl,
    bool Open,
    int32 MaxCount,
    TFunction<void(FNakamaGroup)> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Delete the current user's account.
  *
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void DeleteAccount(
    UNakamaClient* Client,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Delete one or more users by ID or username.
  *
  * @param Ids  The account id of a user.
  * @param Usernames  The account username of a user.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void DeleteFriends(
    UNakamaClient* Client,
    const TArray<FString>& Ids,
    const TArray<FString>& Usernames,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Delete a group by ID.
  *
  * @param GroupId  The id of a group.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void DeleteGroup(
    UNakamaClient* Client,
    FString GroupId,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Delete a leaderboard record.
  *
  * @param LeaderboardId  The leaderboard ID to delete from.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void DeleteLeaderboardRecord(
    UNakamaClient* Client,
    FString LeaderboardId,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Delete one or more notifications for the current user.
  *
  * @param Ids  The id of notifications.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void DeleteNotifications(
    UNakamaClient* Client,
    const TArray<FString>& Ids,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Delete a tournament record.
  *
  * @param TournamentId  The tournament ID to delete from.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void DeleteTournamentRecord(
    UNakamaClient* Client,
    FString TournamentId,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Delete one or more objects by ID or username.
  *
  * @param ObjectIds  Batch of storage objects.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void DeleteStorageObjects(
    UNakamaClient* Client,
    const TArray<FNakamaDeleteStorageObjectId>& ObjectIds,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Submit an event for processing in the server's registered runtime custom events handler.
  *
  * @param Name  An event name, type, category, or identifier.
  * @param Timestamp  The time when the event was triggered.
  * @param External  True if the event came directly from a client call, false otherwise.
  * @param Properties  Arbitrary event property values.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void Event(
    UNakamaClient* Client,
    FString Name,
    FString Timestamp,
    bool External,
    TMap<FString, FString> Properties,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Fetch the current user's account.
  *
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void GetAccount(
    UNakamaClient* Client,
    TFunction<void(FNakamaAccount)> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Fetch zero or more users by ID and/or username.
  *
  * @param Ids  The account id of a user.
  * @param Usernames  The account username of a user.
  * @param FacebookIds  The Facebook ID of a user.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void GetUsers(
    UNakamaClient* Client,
    const TArray<FString>& Ids,
    const TArray<FString>& Usernames,
    const TArray<FString>& FacebookIds,
    TFunction<void(FNakamaUsers)> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Get subscription by product id.
  *
  * @param ProductId  Product id of the subscription
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void GetSubscription(
    UNakamaClient* Client,
    FString ProductId,
    TFunction<void(FNakamaValidatedSubscription)> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Get matchmaker stats.
  *
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void GetMatchmakerStats(
    UNakamaClient* Client,
    TFunction<void(FNakamaMatchmakerStats)> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * A healthcheck which load balancers can use to check the service.
  *
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void Healthcheck(
    UNakamaClient* Client,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Import Facebook friends and add them to a user's account.
  *
  * @param Account  The Facebook account details.
  * @param Reset  Reset the current user's friends list.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void ImportFacebookFriends(
    UNakamaClient* Client,
    FNakamaAccountFacebook Account,
    bool Reset,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Import Steam friends and add them to a user's account.
  *
  * @param Account  The Facebook account details.
  * @param Reset  Reset the current user's friends list.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void ImportSteamFriends(
    UNakamaClient* Client,
    FNakamaAccountSteam Account,
    bool Reset,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Immediately join an open group, or request to join a closed one.
  *
  * @param GroupId  The group ID to join. The group must already exist.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void JoinGroup(
    UNakamaClient* Client,
    FString GroupId,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Attempt to join an open and running tournament.
  *
  * @param TournamentId  The ID of the tournament to join. The tournament must already exist.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void JoinTournament(
    UNakamaClient* Client,
    FString TournamentId,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Kick a set of users from a group.
  *
  * @param GroupId  The group ID to kick from.
  * @param UserIds  The users to kick.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void KickGroupUsers(
    UNakamaClient* Client,
    FString GroupId,
    const TArray<FString>& UserIds,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Leave a group the user is a member of.
  *
  * @param GroupId  The group ID to leave.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void LeaveGroup(
    UNakamaClient* Client,
    FString GroupId,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Add an Apple ID to the social profiles on the current user's account.
  *
  * @param Token  The ID token received from Apple to validate.
  * @param Vars  Extra information that will be bundled in the session token.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void LinkApple(
    UNakamaClient* Client,
    FString Token,
    TMap<FString, FString> Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Add a custom ID to the social profiles on the current user's account.
  *
  * @param Id  A custom identifier.
  * @param Vars  Extra information that will be bundled in the session token.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void LinkCustom(
    UNakamaClient* Client,
    FString Id,
    TMap<FString, FString> Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Add a device ID to the social profiles on the current user's account.
  *
  * @param Id  A device identifier. Should be obtained by a platform-specific device API.
  * @param Vars  Extra information that will be bundled in the session token.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void LinkDevice(
    UNakamaClient* Client,
    FString Id,
    TMap<FString, FString> Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Add an email+password to the social profiles on the current user's account.
  *
  * @param Email  A valid RFC-5322 email address.
  * @param Password  A password for the user account.
  * @param Vars  Extra information that will be bundled in the session token.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void LinkEmail(
    UNakamaClient* Client,
    FString Email,
    FString Password,
    TMap<FString, FString> Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Add Facebook to the social profiles on the current user's account.
  *
  * @param Account  The Facebook account details.
  * @param Sync  Import Facebook friends for the user.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void LinkFacebook(
    UNakamaClient* Client,
    FNakamaAccountFacebook Account,
    bool Sync,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Add Facebook Instant Game to the social profiles on the current user's account.
  *
  * @param SignedPlayerInfo  The OAuth token received from a Facebook Instant Game that may be decoded with the Application Secret (must be available with the nakama configuration)
  * @param Vars  Extra information that will be bundled in the session token.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void LinkFacebookInstantGame(
    UNakamaClient* Client,
    FString SignedPlayerInfo,
    TMap<FString, FString> Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Add Apple's GameCenter to the social profiles on the current user's account.
  *
  * @param PlayerId  Player ID (generated by GameCenter).
  * @param BundleId  Bundle ID (generated by GameCenter).
  * @param TimestampSeconds  Time since UNIX epoch when the signature was created.
  * @param Salt  A random "NSString" used to compute the hash and keep it randomized.
  * @param Signature  The verification signature data generated.
  * @param PublicKeyUrl  The URL for the public encryption key.
  * @param Vars  Extra information that will be bundled in the session token.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void LinkGameCenter(
    UNakamaClient* Client,
    FString PlayerId,
    FString BundleId,
    int64 TimestampSeconds,
    FString Salt,
    FString Signature,
    FString PublicKeyUrl,
    TMap<FString, FString> Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Add Google to the social profiles on the current user's account.
  *
  * @param Token  The OAuth token received from Google to access their profile API.
  * @param Vars  Extra information that will be bundled in the session token.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void LinkGoogle(
    UNakamaClient* Client,
    FString Token,
    TMap<FString, FString> Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Add Steam to the social profiles on the current user's account.
  *
  * @param Account  The Facebook account details.
  * @param Sync  Import Steam friends for the user.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void LinkSteam(
    UNakamaClient* Client,
    FNakamaAccountSteam Account,
    bool Sync,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * List a channel's message history.
  *
  * @param ChannelId  The channel ID to list from.
  * @param Limit  Max number of records to return. Between 1 and 100.
  * @param Forward  True if listing should be older messages to newer, false if reverse.
  * @param Cursor  A pagination cursor, if any.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void ListChannelMessages(
    UNakamaClient* Client,
    FString ChannelId,
    int32 Limit,
    bool Forward,
    FString Cursor,
    TFunction<void(FNakamaChannelMessageList)> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * List all friends for the current user.
  *
  * @param Limit  Max number of records to return. Between 1 and 100.
  * @param State  The friend state to list.
  * @param Cursor  An optional next page cursor.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void ListFriends(
    UNakamaClient* Client,
    int32 Limit,
    int32 State,
    FString Cursor,
    TFunction<void(FNakamaFriendList)> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * List friends of friends for the current user.
  *
  * @param Limit  Max number of records to return. Between 1 and 100.
  * @param Cursor  An optional next page cursor.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void ListFriendsOfFriends(
    UNakamaClient* Client,
    int32 Limit,
    FString Cursor,
    TFunction<void(FNakamaFriendsOfFriendsList)> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * List groups based on given filters.
  *
  * @param Name  List groups that contain this value in their names.
  * @param Cursor  Optional pagination cursor.
  * @param Limit  Max number of groups to return. Between 1 and 100.
  * @param LangTag  Language tag filter
  * @param Members  Number of group members
  * @param Open  Optional Open/Closed filter.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void ListGroups(
    UNakamaClient* Client,
    FString Name,
    FString Cursor,
    int32 Limit,
    FString LangTag,
    int32 Members,
    bool Open,
    TFunction<void(FNakamaGroupList)> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * List all users that are part of a group.
  *
  * @param GroupId  The group ID to list from.
  * @param Limit  Max number of records to return. Between 1 and 100.
  * @param State  The group user state to list.
  * @param Cursor  An optional next page cursor.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void ListGroupUsers(
    UNakamaClient* Client,
    FString GroupId,
    int32 Limit,
    int32 State,
    FString Cursor,
    TFunction<void(FNakamaGroupUserList)> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * List leaderboard records.
  *
  * @param LeaderboardId  The ID of the leaderboard to list for.
  * @param OwnerIds  One or more owners to retrieve records for.
  * @param Limit  Max number of records to return. Between 1 and 100.
  * @param Cursor  A next or previous page cursor.
  * @param Expiry  Expiry in seconds (since epoch) to begin fetching records from. Optional. 0 means from current time.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void ListLeaderboardRecords(
    UNakamaClient* Client,
    FString LeaderboardId,
    const TArray<FString>& OwnerIds,
    int32 Limit,
    FString Cursor,
    int64 Expiry,
    TFunction<void(FNakamaLeaderboardRecordList)> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * List leaderboard records around the target ownerId.
  *
  * @param LeaderboardId  The ID of the tournament to list for.
  * @param Limit  Max number of records to return. Between 1 and 100.
  * @param OwnerId  The owner to retrieve records around.
  * @param Expiry  Expiry in seconds (since epoch) to begin fetching records from.
  * @param Cursor  A next or previous page cursor.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void ListLeaderboardRecordsAroundOwner(
    UNakamaClient* Client,
    FString LeaderboardId,
    uint32 Limit,
    FString OwnerId,
    int64 Expiry,
    FString Cursor,
    TFunction<void(FNakamaLeaderboardRecordList)> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * List running matches and optionally filter by matching criteria.
  *
  * @param Limit  Limit the number of returned matches.
  * @param Authoritative  Authoritative or relayed matches.
  * @param Label  Label filter.
  * @param MinSize  Minimum user count.
  * @param MaxSize  Maximum user count.
  * @param Query  Arbitrary label query.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void ListMatches(
    UNakamaClient* Client,
    int32 Limit,
    bool Authoritative,
    FString Label,
    int32 MinSize,
    int32 MaxSize,
    FString Query,
    TFunction<void(FNakamaMatchList)> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * List parties and optionally filter by matching criteria.
  *
  * @param Limit  Limit the number of returned parties.
  * @param Open  Optionally filter by open/closed parties.
  * @param Query  Arbitrary label query.
  * @param Cursor  Cursor for the next page of results, if any.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void ListParties(
    UNakamaClient* Client,
    int32 Limit,
    bool Open,
    FString Query,
    FString Cursor,
    TFunction<void(FNakamaPartyList)> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Fetch list of notifications.
  *
  * @param Limit  The number of notifications to get. Between 1 and 100.
  * @param CacheableCursor  A cursor to page through notifications. May be cached by clients to get from point in time forwards.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void ListNotifications(
    UNakamaClient* Client,
    int32 Limit,
    FString CacheableCursor,
    TFunction<void(FNakamaNotificationList)> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * List publicly readable storage objects in a given collection.
  *
  * @param UserId  ID of the user.
  * @param Collection  The collection which stores the object.
  * @param Limit  The number of storage objects to list. Between 1 and 100.
  * @param Cursor  The cursor to page through results from.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void ListStorageObjects(
    UNakamaClient* Client,
    FString UserId,
    FString Collection,
    int32 Limit,
    FString Cursor,
    TFunction<void(FNakamaStorageObjectList)> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * List user's subscriptions.
  *
  * @param Limit  Max number of results per page
  * @param Cursor  Cursor to retrieve a page of records from
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void ListSubscriptions(
    UNakamaClient* Client,
    int32 Limit,
    FString Cursor,
    TFunction<void(FNakamaSubscriptionList)> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * List current or upcoming tournaments.
  *
  * @param CategoryStart  The start of the categories to include. Defaults to 0.
  * @param CategoryEnd  The end of the categories to include. Defaults to 128.
  * @param StartTime  The start time for tournaments. Defaults to epoch.
  * @param EndTime  The end time for tournaments. Defaults to +1 year from current Unix time.
  * @param Limit  Max number of records to return. Between 1 and 100.
  * @param Cursor  A next page cursor for listings (optional).
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void ListTournaments(
    UNakamaClient* Client,
    uint32 CategoryStart,
    uint32 CategoryEnd,
    uint32 StartTime,
    uint32 EndTime,
    int32 Limit,
    FString Cursor,
    TFunction<void(FNakamaTournamentList)> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * List tournament records.
  *
  * @param TournamentId  The ID of the tournament to list for.
  * @param OwnerIds  One or more owners to retrieve records for.
  * @param Limit  Max number of records to return. Between 1 and 100.
  * @param Cursor  A next or previous page cursor.
  * @param Expiry  Expiry in seconds (since epoch) to begin fetching records from.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void ListTournamentRecords(
    UNakamaClient* Client,
    FString TournamentId,
    const TArray<FString>& OwnerIds,
    int32 Limit,
    FString Cursor,
    int64 Expiry,
    TFunction<void(FNakamaTournamentRecordList)> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * List tournament records for a given owner.
  *
  * @param TournamentId  The ID of the tournament to list for.
  * @param Limit  Max number of records to return. Between 1 and 100.
  * @param OwnerId  The owner to retrieve records around.
  * @param Expiry  Expiry in seconds (since epoch) to begin fetching records from.
  * @param Cursor  A next or previous page cursor.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void ListTournamentRecordsAroundOwner(
    UNakamaClient* Client,
    FString TournamentId,
    uint32 Limit,
    FString OwnerId,
    int64 Expiry,
    FString Cursor,
    TFunction<void(FNakamaTournamentRecordList)> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * List groups the current user belongs to.
  *
  * @param UserId  ID of the user.
  * @param Limit  Max number of records to return. Between 1 and 100.
  * @param State  The user group state to list.
  * @param Cursor  An optional next page cursor.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void ListUserGroups(
    UNakamaClient* Client,
    FString UserId,
    int32 Limit,
    int32 State,
    FString Cursor,
    TFunction<void(FNakamaUserGroupList)> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Promote a set of users in a group to the next role up.
  *
  * @param GroupId  The group ID to promote in.
  * @param UserIds  The users to promote.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void PromoteGroupUsers(
    UNakamaClient* Client,
    FString GroupId,
    const TArray<FString>& UserIds,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Demote a set of users in a group to the next role down.
  *
  * @param GroupId  The group ID to demote in.
  * @param UserIds  The users to demote.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void DemoteGroupUsers(
    UNakamaClient* Client,
    FString GroupId,
    const TArray<FString>& UserIds,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Get storage objects.
  *
  * @param ObjectIds  Batch of storage objects.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void ReadStorageObjects(
    UNakamaClient* Client,
    const TArray<FNakamaReadStorageObjectId>& ObjectIds,
    TFunction<void(FNakamaStorageObjects)> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Execute a Lua function on the server.
  *
  * @param Id  The identifier of the function.
  * @param Payload  The payload of the function which must be a JSON object.
  * @param HttpKey  The authentication key used when executed as a non-client HTTP request.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void RpcFunc(
    UNakamaClient* Client,
    FString Id,
    FString Payload,
    FString HttpKey,
    TFunction<void(FNakamaRpc)> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Remove the Apple ID from the social profiles on the current user's account.
  *
  * @param Token  The ID token received from Apple to validate.
  * @param Vars  Extra information that will be bundled in the session token.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void UnlinkApple(
    UNakamaClient* Client,
    FString Token,
    TMap<FString, FString> Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Remove the custom ID from the social profiles on the current user's account.
  *
  * @param Id  A custom identifier.
  * @param Vars  Extra information that will be bundled in the session token.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void UnlinkCustom(
    UNakamaClient* Client,
    FString Id,
    TMap<FString, FString> Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Remove the device ID from the social profiles on the current user's account.
  *
  * @param Id  A device identifier. Should be obtained by a platform-specific device API.
  * @param Vars  Extra information that will be bundled in the session token.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void UnlinkDevice(
    UNakamaClient* Client,
    FString Id,
    TMap<FString, FString> Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Remove the email+password from the social profiles on the current user's account.
  *
  * @param Email  A valid RFC-5322 email address.
  * @param Password  A password for the user account.
  * @param Vars  Extra information that will be bundled in the session token.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void UnlinkEmail(
    UNakamaClient* Client,
    FString Email,
    FString Password,
    TMap<FString, FString> Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Remove Facebook from the social profiles on the current user's account.
  *
  * @param Token  The OAuth token received from Facebook to access their profile API.
  * @param Vars  Extra information that will be bundled in the session token.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void UnlinkFacebook(
    UNakamaClient* Client,
    FString Token,
    TMap<FString, FString> Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Remove Facebook Instant Game profile from the social profiles on the current user's account.
  *
  * @param SignedPlayerInfo  The OAuth token received from a Facebook Instant Game that may be decoded with the Application Secret (must be available with the nakama configuration)
  * @param Vars  Extra information that will be bundled in the session token.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void UnlinkFacebookInstantGame(
    UNakamaClient* Client,
    FString SignedPlayerInfo,
    TMap<FString, FString> Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Remove Apple's GameCenter from the social profiles on the current user's account.
  *
  * @param PlayerId  Player ID (generated by GameCenter).
  * @param BundleId  Bundle ID (generated by GameCenter).
  * @param TimestampSeconds  Time since UNIX epoch when the signature was created.
  * @param Salt  A random "NSString" used to compute the hash and keep it randomized.
  * @param Signature  The verification signature data generated.
  * @param PublicKeyUrl  The URL for the public encryption key.
  * @param Vars  Extra information that will be bundled in the session token.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void UnlinkGameCenter(
    UNakamaClient* Client,
    FString PlayerId,
    FString BundleId,
    int64 TimestampSeconds,
    FString Salt,
    FString Signature,
    FString PublicKeyUrl,
    TMap<FString, FString> Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Remove Google from the social profiles on the current user's account.
  *
  * @param Token  The OAuth token received from Google to access their profile API.
  * @param Vars  Extra information that will be bundled in the session token.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void UnlinkGoogle(
    UNakamaClient* Client,
    FString Token,
    TMap<FString, FString> Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Remove Steam from the social profiles on the current user's account.
  *
  * @param Token  The account token received from Steam to access their profile API.
  * @param Vars  Extra information that will be bundled in the session token.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void UnlinkSteam(
    UNakamaClient* Client,
    FString Token,
    TMap<FString, FString> Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Update fields in the current user's account.
  *
  * @param Username  The username of the user's account.
  * @param DisplayName  The display name of the user.
  * @param AvatarUrl  A URL for an avatar image.
  * @param LangTag  The language expected to be a tag which follows the BCP-47 spec.
  * @param Location  The location set by the user.
  * @param Timezone  The timezone set by the user.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void UpdateAccount(
    UNakamaClient* Client,
    FString Username,
    FString DisplayName,
    FString AvatarUrl,
    FString LangTag,
    FString Location,
    FString Timezone,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Update fields in a given group.
  *
  * @param GroupId  The ID of the group to update.
  * @param Name  Name.
  * @param Description  Description string.
  * @param LangTag  Lang tag.
  * @param AvatarUrl  Avatar URL.
  * @param Open  Open is true if anyone should be allowed to join, or false if joins must be approved by a group admin.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void UpdateGroup(
    UNakamaClient* Client,
    FString GroupId,
    FString Name,
    FString Description,
    FString LangTag,
    FString AvatarUrl,
    bool Open,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Validate Apple IAP Receipt
  *
  * @param Receipt  Base64 encoded Apple receipt data payload.
  * @param Persist  Persist the purchase
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void ValidatePurchaseApple(
    UNakamaClient* Client,
    FString Receipt,
    bool Persist,
    TFunction<void(FNakamaValidatePurchaseResponse)> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Validate Apple Subscription Receipt
  *
  * @param Receipt  Base64 encoded Apple receipt data payload.
  * @param Persist  Persist the subscription.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void ValidateSubscriptionApple(
    UNakamaClient* Client,
    FString Receipt,
    bool Persist,
    TFunction<void(FNakamaValidateSubscriptionResponse)> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Validate Google IAP Receipt
  *
  * @param Purchase  JSON encoded Google purchase payload.
  * @param Persist  Persist the purchase
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void ValidatePurchaseGoogle(
    UNakamaClient* Client,
    FString Purchase,
    bool Persist,
    TFunction<void(FNakamaValidatePurchaseResponse)> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Validate Google Subscription Receipt
  *
  * @param Receipt  JSON encoded Google purchase payload.
  * @param Persist  Persist the subscription.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void ValidateSubscriptionGoogle(
    UNakamaClient* Client,
    FString Receipt,
    bool Persist,
    TFunction<void(FNakamaValidateSubscriptionResponse)> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Validate Huawei IAP Receipt
  *
  * @param Purchase  JSON encoded Huawei InAppPurchaseData.
  * @param Signature  InAppPurchaseData signature.
  * @param Persist  Persist the purchase
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void ValidatePurchaseHuawei(
    UNakamaClient* Client,
    FString Purchase,
    FString Signature,
    bool Persist,
    TFunction<void(FNakamaValidatePurchaseResponse)> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Validate FB Instant IAP Receipt
  *
  * @param SignedRequest  Base64 encoded Facebook Instant signedRequest receipt data payload.
  * @param Persist  Persist the purchase
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void ValidatePurchaseFacebookInstant(
    UNakamaClient* Client,
    FString SignedRequest,
    bool Persist,
    TFunction<void(FNakamaValidatePurchaseResponse)> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Write a record to a leaderboard.
  *
  * @param LeaderboardId  The ID of the leaderboard to write to.
  * @param Record  Record input.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void WriteLeaderboardRecord(
    UNakamaClient* Client,
    FString LeaderboardId,
    FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite Record,
    TFunction<void(FNakamaLeaderboardRecord)> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Write objects into the storage engine.
  *
  * @param Objects  The objects to store on the server.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void WriteStorageObjects(
    UNakamaClient* Client,
    const TArray<FNakamaWriteStorageObject>& Objects,
    TFunction<void(FNakamaStorageObjectAcks)> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );

  
  
  /**
  *
  * Write a record to a tournament.
  *
  * @param TournamentId  The tournament ID to write the record for.
  * @param Record  Record input.
  * @param OnSuccess Callback to invoke on success
  * @param OnError Callback to invoke on error
  */
  static void WriteTournamentRecord(
    UNakamaClient* Client,
    FString TournamentId,
    FNakamaWriteTournamentRecordRequest_TournamentRecordWrite Record,
    TFunction<void(FNakamaLeaderboardRecord)> OnSuccess,
    TFunction<void(const FNakamaError& Error)> OnError
  );
};
