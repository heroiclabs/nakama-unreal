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

#pragma once

#include "CoreMinimal.h"
#include "Nakama.gen.h"
#include "NakamaClientConfig.h"
#include "NakamaSession.h"
#include "NakamaFuture.h"

/** Retry configuration for transient error handling + session auto-refresh. */
struct NAKAMA_API FNakamaRetryConfig
{
	/** Maximum number of retry attempts (0 = no retries). */
	int32 MaxRetries = 4;

	/** Base delay in milliseconds before first retry. Actual delay uses exponential backoff with full jitter. */
	int32 BaseDelayMs = 500;

	/** Whether to automatically refresh expired sessions before making API calls. */
	bool bAutoRefreshSession = true;

	/** How many seconds before expiry a session is considered "about to expire" and gets refreshed. */
	int64 AutoRefreshBufferSeconds = 300;

	/** HTTP request timeout in seconds. */
	float Timeout = 10.0f;

	/**
	 * Called after a session is automatically refreshed, so callers can persist the updated session.
	 *
	 * If the callback captures a UObject pointer, set OnSessionRefreshedOwner to that object.
	 * The callback will be skipped if the owner has been garbage-collected, preventing
	 * dangling-pointer crashes during in-flight retries.
	 */
	TFunction<void(const FNakamaSession&)> OnSessionRefreshed;

	/** Optional weak owner for OnSessionRefreshed. When set, the callback is skipped if the owner is stale. */
	TWeakObjectPtr<UObject> OnSessionRefreshedOwner;
};

/**
 * High-level Nakama API: free functions with retry logic + session auto-refresh.
 *
 * Transient errors (UNAVAILABLE, INTERNAL, DEADLINE_EXCEEDED) are
 * automatically retried with exponential backoff and full jitter.
 */
namespace Nakama
{
	/** Returns true if the error code is considered transient (eligible for retry). */
	NAKAMA_API bool IsTransientError(const FNakamaError& Error);

	/** Compute backoff delay in seconds for a given attempt using exponential backoff with full jitter. */
	NAKAMA_API float CalculateBackoff(int32 Attempt, const FNakamaRetryConfig& Config);

  /**
  * Add friends by ID or username to a user's account.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param Ids	 The account id of a user.
  * @param Usernames	 The account username of a user.
  * @param Metadata	 Optional metadata to add to friends.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> AddFriends(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const TArray<FString>& Ids,
    const TArray<FString>& Usernames,
    const FString& Metadata,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Add users to a group.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param GroupId	 The group to add users to.
  * @param UserIds	 The users to add.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> AddGroupUsers(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& GroupId,
    const TArray<FString>& UserIds,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Refresh a user's session using a refresh token retrieved from a previous authentication request.
  *
  * @param ClientConfig	The client configuration.
  * @param Token	 Refresh token.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaSessionResult> SessionRefresh(
    const FNakamaClientConfig& ClientConfig,
    const FString& Token,
    const TMap<FString, FString>& Vars,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Log out a session, invalidate a refresh token, or log out all sessions/refresh tokens for a user.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param Token	 Session token to log out.
  * @param RefreshToken	 Refresh token to invalidate.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> SessionLogout(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& Token,
    const FString& RefreshToken,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Authenticate a user with an Apple ID against the server.
  *
  * @param ClientConfig	The client configuration.
  * @param Create	 Register the account if the user does not already exist.
  * @param Username	 Set the username on the account at register. Must be unique.
  * @param AccountToken	 The ID token received from Apple to validate.
  * @param AccountVars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaSessionResult> AuthenticateApple(
    const FNakamaClientConfig& ClientConfig,
    FNakamaOptionalBool Create,
    const FString& Username,
    const FString& AccountToken,
    const TMap<FString, FString>& AccountVars = {},
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Authenticate a user with a custom id against the server.
  *
  * @param ClientConfig	The client configuration.
  * @param Create	 Register the account if the user does not already exist.
  * @param Username	 Set the username on the account at register. Must be unique.
  * @param AccountId	 A custom identifier.
  * @param AccountVars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaSessionResult> AuthenticateCustom(
    const FNakamaClientConfig& ClientConfig,
    FNakamaOptionalBool Create,
    const FString& Username,
    const FString& AccountId,
    const TMap<FString, FString>& AccountVars = {},
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Authenticate a user with a device id against the server.
  *
  * @param ClientConfig	The client configuration.
  * @param Create	 Register the account if the user does not already exist.
  * @param Username	 Set the username on the account at register. Must be unique.
  * @param AccountId	 A device identifier. Should be obtained by a platform-specific device API.
  * @param AccountVars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaSessionResult> AuthenticateDevice(
    const FNakamaClientConfig& ClientConfig,
    FNakamaOptionalBool Create,
    const FString& Username,
    const FString& AccountId,
    const TMap<FString, FString>& AccountVars = {},
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Authenticate a user with an email+password against the server.
  *
  * @param ClientConfig	The client configuration.
  * @param Create	 Register the account if the user does not already exist.
  * @param Username	 Set the username on the account at register. Must be unique.
  * @param AccountEmail	 A valid RFC-5322 email address.
  * @param AccountPassword	 A password for the user account.
  * @param AccountVars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaSessionResult> AuthenticateEmail(
    const FNakamaClientConfig& ClientConfig,
    FNakamaOptionalBool Create,
    const FString& Username,
    const FString& AccountEmail,
    const FString& AccountPassword,
    const TMap<FString, FString>& AccountVars = {},
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Authenticate a user with a Facebook OAuth token against the server.
  *
  * @param ClientConfig	The client configuration.
  * @param Create	 Register the account if the user does not already exist.
  * @param Username	 Set the username on the account at register. Must be unique.
  * @param Sync	 Import Facebook friends for the user.
  * @param AccountToken	 The OAuth token received from Facebook to access their profile API.
  * @param AccountVars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaSessionResult> AuthenticateFacebook(
    const FNakamaClientConfig& ClientConfig,
    FNakamaOptionalBool Create,
    const FString& Username,
    FNakamaOptionalBool Sync,
    const FString& AccountToken,
    const TMap<FString, FString>& AccountVars = {},
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Authenticate a user with a Facebook Instant Game token against the server.
  *
  * @param ClientConfig	The client configuration.
  * @param Create	 Register the account if the user does not already exist.
  * @param Username	 Set the username on the account at register. Must be unique.
  * @param AccountSignedPlayerInfo	 The OAuth token received from a Facebook Instant Game that may be decoded with the Application Secret (must be available with the nakama configuration)
  * @param AccountVars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaSessionResult> AuthenticateFacebookInstantGame(
    const FNakamaClientConfig& ClientConfig,
    FNakamaOptionalBool Create,
    const FString& Username,
    const FString& AccountSignedPlayerInfo,
    const TMap<FString, FString>& AccountVars = {},
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Authenticate a user with Apple's GameCenter against the server.
  *
  * @param ClientConfig	The client configuration.
  * @param Create	 Register the account if the user does not already exist.
  * @param Username	 Set the username on the account at register. Must be unique.
  * @param AccountPlayerId	 Player ID (generated by GameCenter).
  * @param AccountBundleId	 Bundle ID (generated by GameCenter).
  * @param AccountTimestampSeconds	 Time since UNIX epoch when the signature was created.
  * @param AccountSalt	 A random "NSString" used to compute the hash and keep it randomized.
  * @param AccountSignature	 The verification signature data generated.
  * @param AccountPublicKeyUrl	 The URL for the public encryption key.
  * @param AccountVars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaSessionResult> AuthenticateGameCenter(
    const FNakamaClientConfig& ClientConfig,
    FNakamaOptionalBool Create,
    const FString& Username,
    const FString& AccountPlayerId,
    const FString& AccountBundleId,
    int64 AccountTimestampSeconds,
    const FString& AccountSalt,
    const FString& AccountSignature,
    const FString& AccountPublicKeyUrl,
    const TMap<FString, FString>& AccountVars = {},
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Authenticate a user with Google against the server.
  *
  * @param ClientConfig	The client configuration.
  * @param Create	 Register the account if the user does not already exist.
  * @param Username	 Set the username on the account at register. Must be unique.
  * @param AccountToken	 The OAuth token received from Google to access their profile API.
  * @param AccountVars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaSessionResult> AuthenticateGoogle(
    const FNakamaClientConfig& ClientConfig,
    FNakamaOptionalBool Create,
    const FString& Username,
    const FString& AccountToken,
    const TMap<FString, FString>& AccountVars = {},
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Authenticate a user with Steam against the server.
  *
  * @param ClientConfig	The client configuration.
  * @param Create	 Register the account if the user does not already exist.
  * @param Username	 Set the username on the account at register. Must be unique.
  * @param Sync	 Import Steam friends for the user.
  * @param AccountToken	 The account token received from Steam to access their profile API.
  * @param AccountVars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaSessionResult> AuthenticateSteam(
    const FNakamaClientConfig& ClientConfig,
    FNakamaOptionalBool Create,
    const FString& Username,
    FNakamaOptionalBool Sync,
    const FString& AccountToken,
    const TMap<FString, FString>& AccountVars = {},
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Ban a set of users from a group.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param GroupId	 The group to ban users from.
  * @param UserIds	 The users to ban.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> BanGroupUsers(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& GroupId,
    const TArray<FString>& UserIds,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Block one or more users by ID or username.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param Ids	 The account id of a user.
  * @param Usernames	 The account username of a user.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> BlockFriends(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const TArray<FString>& Ids,
    const TArray<FString>& Usernames,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Create a new group with the current user as the owner.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param Name	 A unique name for the group.
  * @param Description	 A description for the group.
  * @param LangTag	 The language expected to be a tag which follows the BCP-47 spec.
  * @param AvatarUrl	 A URL for an avatar image.
  * @param Open	 Mark a group as open or not where only admins can accept members.
  * @param MaxCount	 Maximum number of group members.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaGroupResult> CreateGroup(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& Name,
    const FString& Description,
    const FString& LangTag,
    const FString& AvatarUrl,
    bool Open,
    int32 MaxCount,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Delete the current user's account.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> DeleteAccount(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Delete one or more users by ID or username.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param Ids	 The account id of a user.
  * @param Usernames	 The account username of a user.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> DeleteFriends(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const TArray<FString>& Ids,
    const TArray<FString>& Usernames,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Delete a group by ID.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param GroupId	 The id of a group.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> DeleteGroup(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& GroupId,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Delete a leaderboard record.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param LeaderboardId	 The leaderboard ID to delete from.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> DeleteLeaderboardRecord(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& LeaderboardId,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Delete one or more notifications for the current user.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param Ids	 The id of notifications.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> DeleteNotifications(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const TArray<FString>& Ids,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Delete a tournament record.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param TournamentId	 The tournament ID to delete from.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> DeleteTournamentRecord(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& TournamentId,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Delete one or more objects by ID or username.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param ObjectIds	 Batch of storage objects.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> DeleteStorageObjects(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const TArray<FNakamaDeleteStorageObjectId>& ObjectIds,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Submit an event for processing in the server's registered runtime custom events handler.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param Name	 An event name, type, category, or identifier.
  * @param Timestamp	 The time when the event was triggered.
  * @param External	 True if the event came directly from a client call, false otherwise.
  * @param Properties	 Arbitrary event property values.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> Event(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& Name,
    const FDateTime& Timestamp,
    bool External,
    const TMap<FString, FString>& Properties,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Fetch the current user's account.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaAccountResult> GetAccount(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Fetch zero or more users by ID and/or username.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param Ids	 The account id of a user.
  * @param Usernames	 The account username of a user.
  * @param FacebookIds	 The Facebook ID of a user.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaUsersResult> GetUsers(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const TArray<FString>& Ids,
    const TArray<FString>& Usernames,
    const TArray<FString>& FacebookIds,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Get subscription by product id.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param ProductId	 Product id of the subscription
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaValidatedSubscriptionResult> GetSubscription(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& ProductId,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Get matchmaker stats.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaMatchmakerStatsResult> GetMatchmakerStats(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * A healthcheck which load balancers can use to check the service.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> Healthcheck(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Import Facebook friends and add them to a user's account.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param Reset	 Reset the current user's friends list.
  * @param AccountToken	 The OAuth token received from Facebook to access their profile API.
  * @param AccountVars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> ImportFacebookFriends(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    FNakamaOptionalBool Reset,
    const FString& AccountToken,
    const TMap<FString, FString>& AccountVars = {},
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Import Steam friends and add them to a user's account.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param Reset	 Reset the current user's friends list.
  * @param AccountToken	 The account token received from Steam to access their profile API.
  * @param AccountVars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> ImportSteamFriends(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    FNakamaOptionalBool Reset,
    const FString& AccountToken,
    const TMap<FString, FString>& AccountVars = {},
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Immediately join an open group, or request to join a closed one.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param GroupId	 The group ID to join. The group must already exist.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> JoinGroup(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& GroupId,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Attempt to join an open and running tournament.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param TournamentId	 The ID of the tournament to join. The tournament must already exist.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> JoinTournament(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& TournamentId,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Kick a set of users from a group.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param GroupId	 The group ID to kick from.
  * @param UserIds	 The users to kick.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> KickGroupUsers(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& GroupId,
    const TArray<FString>& UserIds,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Leave a group the user is a member of.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param GroupId	 The group ID to leave.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> LeaveGroup(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& GroupId,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Add an Apple ID to the social profiles on the current user's account.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param Token	 The ID token received from Apple to validate.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkApple(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& Token,
    const TMap<FString, FString>& Vars,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Add a custom ID to the social profiles on the current user's account.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param Id	 A custom identifier.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkCustom(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& Id,
    const TMap<FString, FString>& Vars,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Add a device ID to the social profiles on the current user's account.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param Id	 A device identifier. Should be obtained by a platform-specific device API.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkDevice(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& Id,
    const TMap<FString, FString>& Vars,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Add an email+password to the social profiles on the current user's account.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param Email	 A valid RFC-5322 email address.
  * @param Password	 A password for the user account.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkEmail(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& Email,
    const FString& Password,
    const TMap<FString, FString>& Vars,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Add Facebook to the social profiles on the current user's account.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param Sync	 Import Facebook friends for the user.
  * @param AccountToken	 The OAuth token received from Facebook to access their profile API.
  * @param AccountVars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkFacebook(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    FNakamaOptionalBool Sync,
    const FString& AccountToken,
    const TMap<FString, FString>& AccountVars = {},
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Add Facebook Instant Game to the social profiles on the current user's account.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param SignedPlayerInfo	 The OAuth token received from a Facebook Instant Game that may be decoded with the Application Secret (must be available with the nakama configuration)
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkFacebookInstantGame(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& SignedPlayerInfo,
    const TMap<FString, FString>& Vars,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Add Apple's GameCenter to the social profiles on the current user's account.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param PlayerId	 Player ID (generated by GameCenter).
  * @param BundleId	 Bundle ID (generated by GameCenter).
  * @param TimestampSeconds	 Time since UNIX epoch when the signature was created.
  * @param Salt	 A random "NSString" used to compute the hash and keep it randomized.
  * @param Signature	 The verification signature data generated.
  * @param PublicKeyUrl	 The URL for the public encryption key.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkGameCenter(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& PlayerId,
    const FString& BundleId,
    int64 TimestampSeconds,
    const FString& Salt,
    const FString& Signature,
    const FString& PublicKeyUrl,
    const TMap<FString, FString>& Vars,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Add Google to the social profiles on the current user's account.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param Token	 The OAuth token received from Google to access their profile API.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkGoogle(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& Token,
    const TMap<FString, FString>& Vars,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Add Steam to the social profiles on the current user's account.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param Sync	 Import Steam friends for the user.
  * @param AccountToken	 The account token received from Steam to access their profile API.
  * @param AccountVars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkSteam(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    FNakamaOptionalBool Sync,
    const FString& AccountToken,
    const TMap<FString, FString>& AccountVars = {},
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * List a channel's message history.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param ChannelId	 The channel ID to list from.
  * @param Limit	 Max number of records to return. Between 1 and 100.
  * @param Forward	 True if listing should be older messages to newer, false if reverse.
  * @param Cursor	 A pagination cursor, if any.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaChannelMessageListResult> ListChannelMessages(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& ChannelId,
    FNakamaOptionalInt32 Limit,
    FNakamaOptionalBool Forward,
    const FString& Cursor,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * List all friends for the current user.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param Limit	 Max number of records to return. Between 1 and 1000.
  * @param State	 The friend state to list.
  * @param Cursor	 An optional next page cursor.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaFriendListResult> ListFriends(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    FNakamaOptionalInt32 Limit,
    FNakamaOptionalInt32 State,
    const FString& Cursor,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * List friends of friends for the current user.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param Limit	 Max number of records to return. Between 1 and 100.
  * @param Cursor	 An optional next page cursor.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaFriendsOfFriendsListResult> ListFriendsOfFriends(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    FNakamaOptionalInt32 Limit,
    const FString& Cursor,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * List groups based on given filters.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param Name	 List groups that contain this value in their names.
  * @param Cursor	 Optional pagination cursor.
  * @param Limit	 Max number of groups to return. Between 1 and 100.
  * @param LangTag	 Language tag filter
  * @param Members	 Number of group members
  * @param Open	 Optional Open/Closed filter.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaGroupListResult> ListGroups(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& Name,
    const FString& Cursor,
    FNakamaOptionalInt32 Limit,
    const FString& LangTag,
    FNakamaOptionalInt32 Members,
    FNakamaOptionalBool Open,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * List all users that are part of a group.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param GroupId	 The group ID to list from.
  * @param Limit	 Max number of records to return. Between 1 and 100.
  * @param State	 The group user state to list.
  * @param Cursor	 An optional next page cursor.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaGroupUserListResult> ListGroupUsers(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& GroupId,
    FNakamaOptionalInt32 Limit,
    FNakamaOptionalInt32 State,
    const FString& Cursor,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * List leaderboard records.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param LeaderboardId	 The ID of the leaderboard to list for.
  * @param OwnerIds	 One or more owners to retrieve records for.
  * @param Limit	 Max number of records to return. Between 1 and 100.
  * @param Cursor	 A next or previous page cursor.
  * @param Expiry	 Expiry in seconds (since epoch) to begin fetching records from. Optional. 0 means from current time.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaLeaderboardRecordListResult> ListLeaderboardRecords(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& LeaderboardId,
    const TArray<FString>& OwnerIds,
    FNakamaOptionalInt32 Limit,
    const FString& Cursor,
    FNakamaOptionalInt64 Expiry,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * List leaderboard records around the target ownerId.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param LeaderboardId	 The ID of the tournament to list for.
  * @param Limit	 Max number of records to return. Between 1 and 100.
  * @param OwnerId	 The owner to retrieve records around.
  * @param Expiry	 Expiry in seconds (since epoch) to begin fetching records from.
  * @param Cursor	 A next or previous page cursor.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaLeaderboardRecordListResult> ListLeaderboardRecordsAroundOwner(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& LeaderboardId,
    FNakamaOptionalInt32 Limit,
    const FString& OwnerId,
    FNakamaOptionalInt64 Expiry,
    const FString& Cursor,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * List running matches and optionally filter by matching criteria.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param Limit	 Limit the number of returned matches.
  * @param Authoritative	 Authoritative or relayed matches.
  * @param Label	 Label filter.
  * @param MinSize	 Minimum user count.
  * @param MaxSize	 Maximum user count.
  * @param Query	 Arbitrary label query.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaMatchListResult> ListMatches(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    FNakamaOptionalInt32 Limit,
    FNakamaOptionalBool Authoritative,
    const FString& Label,
    FNakamaOptionalInt32 MinSize,
    FNakamaOptionalInt32 MaxSize,
    const FString& Query,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * List parties and optionally filter by matching criteria.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param Limit	 Limit the number of returned parties.
  * @param Open	 Optionally filter by open/closed parties.
  * @param Query	 Arbitrary label query.
  * @param Cursor	 Cursor for the next page of results, if any.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaPartyListResult> ListParties(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    FNakamaOptionalInt32 Limit,
    FNakamaOptionalBool Open,
    const FString& Query,
    const FString& Cursor,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Fetch list of notifications.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param Limit	 The number of notifications to get. Between 1 and 100.
  * @param CacheableCursor	 A cursor to page through notifications. May be cached by clients to get from point in time forwards.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaNotificationListResult> ListNotifications(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    FNakamaOptionalInt32 Limit,
    const FString& CacheableCursor,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * List publicly readable storage objects in a given collection.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param UserId	 ID of the user.
  * @param Collection	 The collection which stores the object.
  * @param Limit	 The number of storage objects to list. Between 1 and 100.
  * @param Cursor	 The cursor to page through results from.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaStorageObjectListResult> ListStorageObjects(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& UserId,
    const FString& Collection,
    FNakamaOptionalInt32 Limit,
    const FString& Cursor,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * List user's subscriptions.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param Limit	 Max number of results per page
  * @param Cursor	 Cursor to retrieve a page of records from
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaSubscriptionListResult> ListSubscriptions(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    FNakamaOptionalInt32 Limit,
    const FString& Cursor,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * List current or upcoming tournaments.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param CategoryStart	 The start of the categories to include. Defaults to 0.
  * @param CategoryEnd	 The end of the categories to include. Defaults to 128.
  * @param StartTime	 The start time for tournaments. Defaults to epoch.
  * @param EndTime	 The end time for tournaments. Defaults to +1 year from current Unix time.
  * @param Limit	 Max number of records to return. Between 1 and 100.
  * @param Cursor	 A next page cursor for listings (optional).
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaTournamentListResult> ListTournaments(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    FNakamaOptionalInt32 CategoryStart,
    FNakamaOptionalInt32 CategoryEnd,
    FNakamaOptionalInt32 StartTime,
    FNakamaOptionalInt32 EndTime,
    FNakamaOptionalInt32 Limit,
    const FString& Cursor,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * List tournament records.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param TournamentId	 The ID of the tournament to list for.
  * @param OwnerIds	 One or more owners to retrieve records for.
  * @param Limit	 Max number of records to return. Between 1 and 100.
  * @param Cursor	 A next or previous page cursor.
  * @param Expiry	 Expiry in seconds (since epoch) to begin fetching records from.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaTournamentRecordListResult> ListTournamentRecords(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& TournamentId,
    const TArray<FString>& OwnerIds,
    FNakamaOptionalInt32 Limit,
    const FString& Cursor,
    FNakamaOptionalInt64 Expiry,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * List tournament records for a given owner.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param TournamentId	 The ID of the tournament to list for.
  * @param Limit	 Max number of records to return. Between 1 and 100.
  * @param OwnerId	 The owner to retrieve records around.
  * @param Expiry	 Expiry in seconds (since epoch) to begin fetching records from.
  * @param Cursor	 A next or previous page cursor.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaTournamentRecordListResult> ListTournamentRecordsAroundOwner(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& TournamentId,
    FNakamaOptionalInt32 Limit,
    const FString& OwnerId,
    FNakamaOptionalInt64 Expiry,
    const FString& Cursor,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * List groups the current user belongs to.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param UserId	 ID of the user.
  * @param Limit	 Max number of records to return. Between 1 and 100.
  * @param State	 The user group state to list.
  * @param Cursor	 An optional next page cursor.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaUserGroupListResult> ListUserGroups(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& UserId,
    FNakamaOptionalInt32 Limit,
    FNakamaOptionalInt32 State,
    const FString& Cursor,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Promote a set of users in a group to the next role up.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param GroupId	 The group ID to promote in.
  * @param UserIds	 The users to promote.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> PromoteGroupUsers(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& GroupId,
    const TArray<FString>& UserIds,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Demote a set of users in a group to the next role down.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param GroupId	 The group ID to demote in.
  * @param UserIds	 The users to demote.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> DemoteGroupUsers(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& GroupId,
    const TArray<FString>& UserIds,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Get storage objects.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param ObjectIds	 Batch of storage objects.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaStorageObjectsResult> ReadStorageObjects(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const TArray<FNakamaReadStorageObjectId>& ObjectIds,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Execute a Lua function on the server.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param Id	 The identifier of the function.
  * @param Payload	 The payload of the function which must be a JSON object.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaRpcResult> RpcFunc(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& Id,
    const FString& Payload,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );
  
  /**
  * Execute a Lua function on the server. (S2S Variant)
  *
  * @param ClientConfig	The client configuration.
  * @param HttpKey	 The authentication key used when executed as a non-client HTTP request.
  * @param Id	 The identifier of the function.
  * @param Payload	 The payload of the function which must be a JSON object.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaRpcResult> RpcFunc(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const FString& Id,
    const FString& Payload,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Remove the Apple ID from the social profiles on the current user's account.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param Token	 The ID token received from Apple to validate.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkApple(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& Token,
    const TMap<FString, FString>& Vars,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Remove the custom ID from the social profiles on the current user's account.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param Id	 A custom identifier.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkCustom(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& Id,
    const TMap<FString, FString>& Vars,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Remove the device ID from the social profiles on the current user's account.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param Id	 A device identifier. Should be obtained by a platform-specific device API.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkDevice(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& Id,
    const TMap<FString, FString>& Vars,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Remove the email+password from the social profiles on the current user's account.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param Email	 A valid RFC-5322 email address.
  * @param Password	 A password for the user account.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkEmail(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& Email,
    const FString& Password,
    const TMap<FString, FString>& Vars,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Remove Facebook from the social profiles on the current user's account.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param Token	 The OAuth token received from Facebook to access their profile API.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkFacebook(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& Token,
    const TMap<FString, FString>& Vars,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Remove Facebook Instant Game profile from the social profiles on the current user's account.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param SignedPlayerInfo	 The OAuth token received from a Facebook Instant Game that may be decoded with the Application Secret (must be available with the nakama configuration)
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkFacebookInstantGame(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& SignedPlayerInfo,
    const TMap<FString, FString>& Vars,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Remove Apple's GameCenter from the social profiles on the current user's account.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param PlayerId	 Player ID (generated by GameCenter).
  * @param BundleId	 Bundle ID (generated by GameCenter).
  * @param TimestampSeconds	 Time since UNIX epoch when the signature was created.
  * @param Salt	 A random "NSString" used to compute the hash and keep it randomized.
  * @param Signature	 The verification signature data generated.
  * @param PublicKeyUrl	 The URL for the public encryption key.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkGameCenter(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& PlayerId,
    const FString& BundleId,
    int64 TimestampSeconds,
    const FString& Salt,
    const FString& Signature,
    const FString& PublicKeyUrl,
    const TMap<FString, FString>& Vars,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Remove Google from the social profiles on the current user's account.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param Token	 The OAuth token received from Google to access their profile API.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkGoogle(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& Token,
    const TMap<FString, FString>& Vars,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Remove Steam from the social profiles on the current user's account.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param Token	 The account token received from Steam to access their profile API.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkSteam(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& Token,
    const TMap<FString, FString>& Vars,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Update fields in the current user's account.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param Username	 The username of the user's account.
  * @param DisplayName	 The display name of the user.
  * @param AvatarUrl	 A URL for an avatar image.
  * @param LangTag	 The language expected to be a tag which follows the BCP-47 spec.
  * @param Location	 The location set by the user.
  * @param Timezone	 The timezone set by the user.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> UpdateAccount(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& Username,
    const FString& DisplayName,
    const FString& AvatarUrl,
    const FString& LangTag,
    const FString& Location,
    const FString& Timezone,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Update fields in a given group.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param GroupId	 The ID of the group to update.
  * @param Name	 Name.
  * @param Description	 Description string.
  * @param LangTag	 Lang tag.
  * @param AvatarUrl	 Avatar URL.
  * @param Open	 Open is true if anyone should be allowed to join, or false if joins must be approved by a group admin.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> UpdateGroup(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& GroupId,
    const FString& Name,
    const FString& Description,
    const FString& LangTag,
    const FString& AvatarUrl,
    FNakamaOptionalBool Open,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Validate Apple IAP Receipt
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param Receipt	 Base64 encoded Apple receipt data payload.
  * @param Persist	 Persist the purchase
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaValidatePurchaseResponseResult> ValidatePurchaseApple(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& Receipt,
    FNakamaOptionalBool Persist,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Validate Apple Subscription Receipt
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param Receipt	 Base64 encoded Apple receipt data payload.
  * @param Persist	 Persist the subscription.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaValidateSubscriptionResponseResult> ValidateSubscriptionApple(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& Receipt,
    FNakamaOptionalBool Persist,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Validate Google IAP Receipt
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param Purchase	 JSON encoded Google purchase payload.
  * @param Persist	 Persist the purchase
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaValidatePurchaseResponseResult> ValidatePurchaseGoogle(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& Purchase,
    FNakamaOptionalBool Persist,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Validate Google Subscription Receipt
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param Receipt	 JSON encoded Google purchase payload.
  * @param Persist	 Persist the subscription.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaValidateSubscriptionResponseResult> ValidateSubscriptionGoogle(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& Receipt,
    FNakamaOptionalBool Persist,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Validate Huawei IAP Receipt
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param Purchase	 JSON encoded Huawei InAppPurchaseData.
  * @param Signature	 InAppPurchaseData signature.
  * @param Persist	 Persist the purchase
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaValidatePurchaseResponseResult> ValidatePurchaseHuawei(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& Purchase,
    const FString& Signature,
    FNakamaOptionalBool Persist,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Validate FB Instant IAP Receipt
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param SignedRequest	 Base64 encoded Facebook Instant signedRequest receipt data payload.
  * @param Persist	 Persist the purchase
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaValidatePurchaseResponseResult> ValidatePurchaseFacebookInstant(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& SignedRequest,
    FNakamaOptionalBool Persist,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Write a record to a leaderboard.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param LeaderboardId	 The ID of the leaderboard to write to.
  * @param RecordScore	 The score value to submit.
  * @param RecordSubscore	 An optional secondary value.
  * @param RecordMetadata	 Optional record metadata.
  * @param RecordOperator	 Operator override.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaLeaderboardRecordResult> WriteLeaderboardRecord(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& LeaderboardId,
    int64 RecordScore,
    int64 RecordSubscore,
    const FString& RecordMetadata,
    ENakamaOperator RecordOperator,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Write objects into the storage engine.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param Objects	 The objects to store on the server.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaStorageObjectAcksResult> WriteStorageObjects(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const TArray<FNakamaWriteStorageObject>& Objects,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );

  /**
  * Write a record to a tournament.
  *
  * @param ClientConfig	The client configuration.
  * @param Session	The session of the user.
  * @param TournamentId	 The tournament ID to write the record for.
  * @param RecordScore	 The score value to submit.
  * @param RecordSubscore	 An optional secondary value.
  * @param RecordMetadata	 A JSON object of additional properties (optional).
  * @param RecordOperator	 Operator override.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaLeaderboardRecordResult> WriteTournamentRecord(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FString& TournamentId,
    int64 RecordScore,
    int64 RecordSubscore,
    const FString& RecordMetadata,
    ENakamaOperator RecordOperator,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  );
}
