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
#include "NakamaApi.h"
#include "NakamaFuture.h"

/** Tag type used as the value type for RPCs that return no data. */
struct NAKAMA_API FNakamaVoid {};
struct NAKAMA_API FNakamaVoidResult
{
	using ValueType = FNakamaVoid;
	FNakamaVoid Value{};
	FNakamaError Error;
	bool bIsError = true;
};
struct NAKAMA_API FNakamaSessionResult
{
  using ValueType = FNakamaSession;
  FNakamaSession Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaGroupResult
{
  using ValueType = FNakamaGroup;
  FNakamaGroup Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaAccountResult
{
  using ValueType = FNakamaAccount;
  FNakamaAccount Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaUsersResult
{
  using ValueType = FNakamaUsers;
  FNakamaUsers Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaValidatedSubscriptionResult
{
  using ValueType = FNakamaValidatedSubscription;
  FNakamaValidatedSubscription Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaMatchmakerStatsResult
{
  using ValueType = FNakamaMatchmakerStats;
  FNakamaMatchmakerStats Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaChannelMessageListResult
{
  using ValueType = FNakamaChannelMessageList;
  FNakamaChannelMessageList Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaFriendListResult
{
  using ValueType = FNakamaFriendList;
  FNakamaFriendList Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaFriendsOfFriendsListResult
{
  using ValueType = FNakamaFriendsOfFriendsList;
  FNakamaFriendsOfFriendsList Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaGroupListResult
{
  using ValueType = FNakamaGroupList;
  FNakamaGroupList Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaGroupUserListResult
{
  using ValueType = FNakamaGroupUserList;
  FNakamaGroupUserList Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaLeaderboardRecordListResult
{
  using ValueType = FNakamaLeaderboardRecordList;
  FNakamaLeaderboardRecordList Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaMatchListResult
{
  using ValueType = FNakamaMatchList;
  FNakamaMatchList Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaPartyListResult
{
  using ValueType = FNakamaPartyList;
  FNakamaPartyList Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaNotificationListResult
{
  using ValueType = FNakamaNotificationList;
  FNakamaNotificationList Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaStorageObjectListResult
{
  using ValueType = FNakamaStorageObjectList;
  FNakamaStorageObjectList Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaSubscriptionListResult
{
  using ValueType = FNakamaSubscriptionList;
  FNakamaSubscriptionList Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaTournamentListResult
{
  using ValueType = FNakamaTournamentList;
  FNakamaTournamentList Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaTournamentRecordListResult
{
  using ValueType = FNakamaTournamentRecordList;
  FNakamaTournamentRecordList Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaUserGroupListResult
{
  using ValueType = FNakamaUserGroupList;
  FNakamaUserGroupList Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaStorageObjectsResult
{
  using ValueType = FNakamaStorageObjects;
  FNakamaStorageObjects Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaRpcResult
{
  using ValueType = FNakamaRpc;
  FNakamaRpc Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaValidatePurchaseResponseResult
{
  using ValueType = FNakamaValidatePurchaseResponse;
  FNakamaValidatePurchaseResponse Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaValidateSubscriptionResponseResult
{
  using ValueType = FNakamaValidateSubscriptionResponse;
  FNakamaValidateSubscriptionResponse Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaLeaderboardRecordResult
{
  using ValueType = FNakamaLeaderboardRecord;
  FNakamaLeaderboardRecord Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaStorageObjectAcksResult
{
  using ValueType = FNakamaStorageObjectAcks;
  FNakamaStorageObjectAcks Value {};
  FNakamaError Error;
  bool bIsError = true;
};

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
	NAKAMA_API bool IsTransientError(const FNakamaError& Error) noexcept;

	/** Compute backoff delay in seconds for a given attempt using exponential backoff with full jitter. */
	NAKAMA_API float CalculateBackoff(int32 Attempt, const FNakamaRetryConfig& Config) noexcept;

  /**
  * Add friends by ID or username to a user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Ids	 The account id of a user.
  * @param Usernames	 The account username of a user.
  * @param Metadata	 Optional metadata to add to friends.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> AddFriends(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const TArray<FString>& Ids,
    const TArray<FString>& Usernames,
    const FString& Metadata,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Add friends by ID or username to a user's account.
  *
  * @param Config	The client configuration.
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
  ) noexcept;

  /**
  * Add users to a group.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param GroupId	 The group to add users to.
  * @param UserIds	 The users to add.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> AddGroupUsers(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const FString& GroupId,
    const TArray<FString>& UserIds,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Add users to a group.
  *
  * @param Config	The client configuration.
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
  ) noexcept;

  /**
  * Refresh a user's session using a refresh token retrieved from a previous authentication request.
  *
  * @param Config	The client configuration.
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
  ) noexcept;

  /**
  * Log out a session, invalidate a refresh token, or log out all sessions/refresh tokens for a user.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Token	 Session token to log out.
  * @param RefreshToken	 Refresh token to invalidate.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> SessionLogout(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const FString& Token,
    const FString& RefreshToken,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Log out a session, invalidate a refresh token, or log out all sessions/refresh tokens for a user.
  *
  * @param Config	The client configuration.
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
  ) noexcept;

  /**
  * Authenticate a user with an Apple ID against the server.
  *
  * @param Config	The client configuration.
  * @param Create	 Register the account if the user does not already exist.
  * @param Username	 Set the username on the account at register. Must be unique.
  * @param AccountToken	 The ID token received from Apple to validate.
  * @param AccountVars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaSessionResult> AuthenticateApple(
    const FNakamaClientConfig& ClientConfig,
    bool Create,
    const FString& Username,
    const FString& AccountToken,
    const TMap<FString, FString>& AccountVars = {},
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Authenticate a user with a custom id against the server.
  *
  * @param Config	The client configuration.
  * @param Create	 Register the account if the user does not already exist.
  * @param Username	 Set the username on the account at register. Must be unique.
  * @param AccountId	 A custom identifier.
  * @param AccountVars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaSessionResult> AuthenticateCustom(
    const FNakamaClientConfig& ClientConfig,
    bool Create,
    const FString& Username,
    const FString& AccountId,
    const TMap<FString, FString>& AccountVars = {},
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Authenticate a user with a device id against the server.
  *
  * @param Config	The client configuration.
  * @param Create	 Register the account if the user does not already exist.
  * @param Username	 Set the username on the account at register. Must be unique.
  * @param AccountId	 A device identifier. Should be obtained by a platform-specific device API.
  * @param AccountVars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaSessionResult> AuthenticateDevice(
    const FNakamaClientConfig& ClientConfig,
    bool Create,
    const FString& Username,
    const FString& AccountId,
    const TMap<FString, FString>& AccountVars = {},
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Authenticate a user with an email+password against the server.
  *
  * @param Config	The client configuration.
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
    bool Create,
    const FString& Username,
    const FString& AccountEmail,
    const FString& AccountPassword,
    const TMap<FString, FString>& AccountVars = {},
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Authenticate a user with a Facebook OAuth token against the server.
  *
  * @param Config	The client configuration.
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
    bool Create,
    const FString& Username,
    bool Sync,
    const FString& AccountToken,
    const TMap<FString, FString>& AccountVars = {},
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Authenticate a user with a Facebook Instant Game token against the server.
  *
  * @param Config	The client configuration.
  * @param Create	 Register the account if the user does not already exist.
  * @param Username	 Set the username on the account at register. Must be unique.
  * @param AccountSignedPlayerInfo	 The OAuth token received from a Facebook Instant Game that may be decoded with the Application Secret (must be available with the nakama configuration)
  * @param AccountVars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaSessionResult> AuthenticateFacebookInstantGame(
    const FNakamaClientConfig& ClientConfig,
    bool Create,
    const FString& Username,
    const FString& AccountSignedPlayerInfo,
    const TMap<FString, FString>& AccountVars = {},
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Authenticate a user with Apple's GameCenter against the server.
  *
  * @param Config	The client configuration.
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
    bool Create,
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
  ) noexcept;

  /**
  * Authenticate a user with Google against the server.
  *
  * @param Config	The client configuration.
  * @param Create	 Register the account if the user does not already exist.
  * @param Username	 Set the username on the account at register. Must be unique.
  * @param AccountToken	 The OAuth token received from Google to access their profile API.
  * @param AccountVars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaSessionResult> AuthenticateGoogle(
    const FNakamaClientConfig& ClientConfig,
    bool Create,
    const FString& Username,
    const FString& AccountToken,
    const TMap<FString, FString>& AccountVars = {},
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Authenticate a user with Steam against the server.
  *
  * @param Config	The client configuration.
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
    bool Create,
    const FString& Username,
    bool Sync,
    const FString& AccountToken,
    const TMap<FString, FString>& AccountVars = {},
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Ban a set of users from a group.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param GroupId	 The group to ban users from.
  * @param UserIds	 The users to ban.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> BanGroupUsers(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const FString& GroupId,
    const TArray<FString>& UserIds,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Ban a set of users from a group.
  *
  * @param Config	The client configuration.
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
  ) noexcept;

  /**
  * Block one or more users by ID or username.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Ids	 The account id of a user.
  * @param Usernames	 The account username of a user.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> BlockFriends(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const TArray<FString>& Ids,
    const TArray<FString>& Usernames,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Block one or more users by ID or username.
  *
  * @param Config	The client configuration.
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
  ) noexcept;

  /**
  * Create a new group with the current user as the owner.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
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
    const FString& HttpKey,
    const FString& Name,
    const FString& Description,
    const FString& LangTag,
    const FString& AvatarUrl,
    bool Open,
    int32 MaxCount,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Create a new group with the current user as the owner.
  *
  * @param Config	The client configuration.
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
  ) noexcept;

  /**
  * Delete the current user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> DeleteAccount(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Delete the current user's account.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> DeleteAccount(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Delete one or more users by ID or username.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Ids	 The account id of a user.
  * @param Usernames	 The account username of a user.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> DeleteFriends(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const TArray<FString>& Ids,
    const TArray<FString>& Usernames,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Delete one or more users by ID or username.
  *
  * @param Config	The client configuration.
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
  ) noexcept;

  /**
  * Delete a group by ID.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param GroupId	 The id of a group.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> DeleteGroup(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const FString& GroupId,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Delete a group by ID.
  *
  * @param Config	The client configuration.
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
  ) noexcept;

  /**
  * Delete a leaderboard record.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param LeaderboardId	 The leaderboard ID to delete from.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> DeleteLeaderboardRecord(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const FString& LeaderboardId,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Delete a leaderboard record.
  *
  * @param Config	The client configuration.
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
  ) noexcept;

  /**
  * Delete one or more notifications for the current user.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Ids	 The id of notifications.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> DeleteNotifications(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const TArray<FString>& Ids,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Delete one or more notifications for the current user.
  *
  * @param Config	The client configuration.
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
  ) noexcept;

  /**
  * Delete a tournament record.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param TournamentId	 The tournament ID to delete from.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> DeleteTournamentRecord(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const FString& TournamentId,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Delete a tournament record.
  *
  * @param Config	The client configuration.
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
  ) noexcept;

  /**
  * Delete one or more objects by ID or username.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param ObjectIds	 Batch of storage objects.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> DeleteStorageObjects(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const TArray<FNakamaDeleteStorageObjectId>& ObjectIds,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Delete one or more objects by ID or username.
  *
  * @param Config	The client configuration.
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
  ) noexcept;

  /**
  * Submit an event for processing in the server's registered runtime custom events handler.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Name	 An event name, type, category, or identifier.
  * @param Timestamp	 The time when the event was triggered.
  * @param External	 True if the event came directly from a client call, false otherwise.
  * @param Properties	 Arbitrary event property values.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> Event(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const FString& Name,
    const FString& Timestamp,
    bool External,
    const TMap<FString, FString>& Properties,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Submit an event for processing in the server's registered runtime custom events handler.
  *
  * @param Config	The client configuration.
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
    const FString& Timestamp,
    bool External,
    const TMap<FString, FString>& Properties,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Fetch the current user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaAccountResult> GetAccount(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Fetch the current user's account.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaAccountResult> GetAccount(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Fetch zero or more users by ID and/or username.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Ids	 The account id of a user.
  * @param Usernames	 The account username of a user.
  * @param FacebookIds	 The Facebook ID of a user.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaUsersResult> GetUsers(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const TArray<FString>& Ids,
    const TArray<FString>& Usernames,
    const TArray<FString>& FacebookIds,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Fetch zero or more users by ID and/or username.
  *
  * @param Config	The client configuration.
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
  ) noexcept;

  /**
  * Get subscription by product id.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param ProductId	 Product id of the subscription
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaValidatedSubscriptionResult> GetSubscription(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const FString& ProductId,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Get subscription by product id.
  *
  * @param Config	The client configuration.
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
  ) noexcept;

  /**
  * Get matchmaker stats.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaMatchmakerStatsResult> GetMatchmakerStats(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Get matchmaker stats.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaMatchmakerStatsResult> GetMatchmakerStats(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * A healthcheck which load balancers can use to check the service.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> Healthcheck(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * A healthcheck which load balancers can use to check the service.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> Healthcheck(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Import Facebook friends and add them to a user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Reset	 Reset the current user's friends list.
  * @param AccountToken	 The OAuth token received from Facebook to access their profile API.
  * @param AccountVars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> ImportFacebookFriends(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    bool Reset,
    const FString& AccountToken,
    const TMap<FString, FString>& AccountVars = {},
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Import Facebook friends and add them to a user's account.
  *
  * @param Config	The client configuration.
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
    bool Reset,
    const FString& AccountToken,
    const TMap<FString, FString>& AccountVars = {},
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Import Steam friends and add them to a user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Reset	 Reset the current user's friends list.
  * @param AccountToken	 The account token received from Steam to access their profile API.
  * @param AccountVars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> ImportSteamFriends(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    bool Reset,
    const FString& AccountToken,
    const TMap<FString, FString>& AccountVars = {},
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Import Steam friends and add them to a user's account.
  *
  * @param Config	The client configuration.
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
    bool Reset,
    const FString& AccountToken,
    const TMap<FString, FString>& AccountVars = {},
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Immediately join an open group, or request to join a closed one.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param GroupId	 The group ID to join. The group must already exist.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> JoinGroup(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const FString& GroupId,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Immediately join an open group, or request to join a closed one.
  *
  * @param Config	The client configuration.
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
  ) noexcept;

  /**
  * Attempt to join an open and running tournament.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param TournamentId	 The ID of the tournament to join. The tournament must already exist.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> JoinTournament(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const FString& TournamentId,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Attempt to join an open and running tournament.
  *
  * @param Config	The client configuration.
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
  ) noexcept;

  /**
  * Kick a set of users from a group.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param GroupId	 The group ID to kick from.
  * @param UserIds	 The users to kick.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> KickGroupUsers(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const FString& GroupId,
    const TArray<FString>& UserIds,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Kick a set of users from a group.
  *
  * @param Config	The client configuration.
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
  ) noexcept;

  /**
  * Leave a group the user is a member of.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param GroupId	 The group ID to leave.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> LeaveGroup(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const FString& GroupId,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Leave a group the user is a member of.
  *
  * @param Config	The client configuration.
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
  ) noexcept;

  /**
  * Add an Apple ID to the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Token	 The ID token received from Apple to validate.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkApple(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const FString& Token,
    const TMap<FString, FString>& Vars,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Add an Apple ID to the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
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
  ) noexcept;

  /**
  * Add a custom ID to the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Id	 A custom identifier.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkCustom(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const FString& Id,
    const TMap<FString, FString>& Vars,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Add a custom ID to the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
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
  ) noexcept;

  /**
  * Add a device ID to the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Id	 A device identifier. Should be obtained by a platform-specific device API.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkDevice(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const FString& Id,
    const TMap<FString, FString>& Vars,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Add a device ID to the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
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
  ) noexcept;

  /**
  * Add an email+password to the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Email	 A valid RFC-5322 email address.
  * @param Password	 A password for the user account.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkEmail(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const FString& Email,
    const FString& Password,
    const TMap<FString, FString>& Vars,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Add an email+password to the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
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
  ) noexcept;

  /**
  * Add Facebook to the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Sync	 Import Facebook friends for the user.
  * @param AccountToken	 The OAuth token received from Facebook to access their profile API.
  * @param AccountVars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkFacebook(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    bool Sync,
    const FString& AccountToken,
    const TMap<FString, FString>& AccountVars = {},
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Add Facebook to the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
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
    bool Sync,
    const FString& AccountToken,
    const TMap<FString, FString>& AccountVars = {},
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Add Facebook Instant Game to the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param SignedPlayerInfo	 The OAuth token received from a Facebook Instant Game that may be decoded with the Application Secret (must be available with the nakama configuration)
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkFacebookInstantGame(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const FString& SignedPlayerInfo,
    const TMap<FString, FString>& Vars,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Add Facebook Instant Game to the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
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
  ) noexcept;

  /**
  * Add Apple's GameCenter to the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
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
    const FString& HttpKey,
    const FString& PlayerId,
    const FString& BundleId,
    int64 TimestampSeconds,
    const FString& Salt,
    const FString& Signature,
    const FString& PublicKeyUrl,
    const TMap<FString, FString>& Vars,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Add Apple's GameCenter to the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
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
  ) noexcept;

  /**
  * Add Google to the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Token	 The OAuth token received from Google to access their profile API.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkGoogle(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const FString& Token,
    const TMap<FString, FString>& Vars,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Add Google to the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
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
  ) noexcept;

  /**
  * Add Steam to the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Sync	 Import Steam friends for the user.
  * @param AccountToken	 The account token received from Steam to access their profile API.
  * @param AccountVars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkSteam(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    bool Sync,
    const FString& AccountToken,
    const TMap<FString, FString>& AccountVars = {},
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Add Steam to the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
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
    bool Sync,
    const FString& AccountToken,
    const TMap<FString, FString>& AccountVars = {},
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * List a channel's message history.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param ChannelId	 The channel ID to list from.
  * @param Limit	 Max number of records to return. Between 1 and 100.
  * @param Forward	 True if listing should be older messages to newer, false if reverse.
  * @param Cursor	 A pagination cursor, if any.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaChannelMessageListResult> ListChannelMessages(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const FString& ChannelId,
    int32 Limit,
    bool Forward,
    const FString& Cursor,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * List a channel's message history.
  *
  * @param Config	The client configuration.
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
    int32 Limit,
    bool Forward,
    const FString& Cursor,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * List all friends for the current user.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Limit	 Max number of records to return. Between 1 and 1000.
  * @param State	 The friend state to list.
  * @param Cursor	 An optional next page cursor.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaFriendListResult> ListFriends(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    int32 Limit,
    int32 State,
    const FString& Cursor,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * List all friends for the current user.
  *
  * @param Config	The client configuration.
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
    int32 Limit,
    int32 State,
    const FString& Cursor,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * List friends of friends for the current user.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Limit	 Max number of records to return. Between 1 and 100.
  * @param Cursor	 An optional next page cursor.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaFriendsOfFriendsListResult> ListFriendsOfFriends(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    int32 Limit,
    const FString& Cursor,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * List friends of friends for the current user.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Limit	 Max number of records to return. Between 1 and 100.
  * @param Cursor	 An optional next page cursor.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaFriendsOfFriendsListResult> ListFriendsOfFriends(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    int32 Limit,
    const FString& Cursor,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * List groups based on given filters.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
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
    const FString& HttpKey,
    const FString& Name,
    const FString& Cursor,
    int32 Limit,
    const FString& LangTag,
    int32 Members,
    bool Open,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * List groups based on given filters.
  *
  * @param Config	The client configuration.
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
    int32 Limit,
    const FString& LangTag,
    int32 Members,
    bool Open,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * List all users that are part of a group.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param GroupId	 The group ID to list from.
  * @param Limit	 Max number of records to return. Between 1 and 100.
  * @param State	 The group user state to list.
  * @param Cursor	 An optional next page cursor.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaGroupUserListResult> ListGroupUsers(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const FString& GroupId,
    int32 Limit,
    int32 State,
    const FString& Cursor,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * List all users that are part of a group.
  *
  * @param Config	The client configuration.
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
    int32 Limit,
    int32 State,
    const FString& Cursor,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * List leaderboard records.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
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
    const FString& HttpKey,
    const FString& LeaderboardId,
    const TArray<FString>& OwnerIds,
    int32 Limit,
    const FString& Cursor,
    int64 Expiry,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * List leaderboard records.
  *
  * @param Config	The client configuration.
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
    int32 Limit,
    const FString& Cursor,
    int64 Expiry,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * List leaderboard records around the target ownerId.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
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
    const FString& HttpKey,
    const FString& LeaderboardId,
    int32 Limit,
    const FString& OwnerId,
    int64 Expiry,
    const FString& Cursor,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * List leaderboard records around the target ownerId.
  *
  * @param Config	The client configuration.
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
    int32 Limit,
    const FString& OwnerId,
    int64 Expiry,
    const FString& Cursor,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * List running matches and optionally filter by matching criteria.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
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
    const FString& HttpKey,
    int32 Limit,
    bool Authoritative,
    const FString& Label,
    int32 MinSize,
    int32 MaxSize,
    const FString& Query,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * List running matches and optionally filter by matching criteria.
  *
  * @param Config	The client configuration.
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
    int32 Limit,
    bool Authoritative,
    const FString& Label,
    int32 MinSize,
    int32 MaxSize,
    const FString& Query,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * List parties and optionally filter by matching criteria.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Limit	 Limit the number of returned parties.
  * @param Open	 Optionally filter by open/closed parties.
  * @param Query	 Arbitrary label query.
  * @param Cursor	 Cursor for the next page of results, if any.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaPartyListResult> ListParties(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    int32 Limit,
    bool Open,
    const FString& Query,
    const FString& Cursor,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * List parties and optionally filter by matching criteria.
  *
  * @param Config	The client configuration.
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
    int32 Limit,
    bool Open,
    const FString& Query,
    const FString& Cursor,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Fetch list of notifications.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Limit	 The number of notifications to get. Between 1 and 100.
  * @param CacheableCursor	 A cursor to page through notifications. May be cached by clients to get from point in time forwards.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaNotificationListResult> ListNotifications(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    int32 Limit,
    const FString& CacheableCursor,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Fetch list of notifications.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Limit	 The number of notifications to get. Between 1 and 100.
  * @param CacheableCursor	 A cursor to page through notifications. May be cached by clients to get from point in time forwards.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaNotificationListResult> ListNotifications(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    int32 Limit,
    const FString& CacheableCursor,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * List publicly readable storage objects in a given collection.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param UserId	 ID of the user.
  * @param Collection	 The collection which stores the object.
  * @param Limit	 The number of storage objects to list. Between 1 and 100.
  * @param Cursor	 The cursor to page through results from.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaStorageObjectListResult> ListStorageObjects(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const FString& UserId,
    const FString& Collection,
    int32 Limit,
    const FString& Cursor,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * List publicly readable storage objects in a given collection.
  *
  * @param Config	The client configuration.
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
    int32 Limit,
    const FString& Cursor,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * List user's subscriptions.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Limit	 Max number of results per page
  * @param Cursor	 Cursor to retrieve a page of records from
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaSubscriptionListResult> ListSubscriptions(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    int32 Limit,
    const FString& Cursor,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * List user's subscriptions.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Limit	 Max number of results per page
  * @param Cursor	 Cursor to retrieve a page of records from
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaSubscriptionListResult> ListSubscriptions(
    const FNakamaClientConfig& ClientConfig,
    const FNakamaSession& Session,
    int32 Limit,
    const FString& Cursor,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * List current or upcoming tournaments.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
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
    const FString& HttpKey,
    int32 CategoryStart,
    int32 CategoryEnd,
    int32 StartTime,
    int32 EndTime,
    int32 Limit,
    const FString& Cursor,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * List current or upcoming tournaments.
  *
  * @param Config	The client configuration.
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
    int32 CategoryStart,
    int32 CategoryEnd,
    int32 StartTime,
    int32 EndTime,
    int32 Limit,
    const FString& Cursor,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * List tournament records.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
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
    const FString& HttpKey,
    const FString& TournamentId,
    const TArray<FString>& OwnerIds,
    int32 Limit,
    const FString& Cursor,
    int64 Expiry,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * List tournament records.
  *
  * @param Config	The client configuration.
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
    int32 Limit,
    const FString& Cursor,
    int64 Expiry,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * List tournament records for a given owner.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
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
    const FString& HttpKey,
    const FString& TournamentId,
    int32 Limit,
    const FString& OwnerId,
    int64 Expiry,
    const FString& Cursor,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * List tournament records for a given owner.
  *
  * @param Config	The client configuration.
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
    int32 Limit,
    const FString& OwnerId,
    int64 Expiry,
    const FString& Cursor,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * List groups the current user belongs to.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param UserId	 ID of the user.
  * @param Limit	 Max number of records to return. Between 1 and 100.
  * @param State	 The user group state to list.
  * @param Cursor	 An optional next page cursor.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaUserGroupListResult> ListUserGroups(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const FString& UserId,
    int32 Limit,
    int32 State,
    const FString& Cursor,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * List groups the current user belongs to.
  *
  * @param Config	The client configuration.
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
    int32 Limit,
    int32 State,
    const FString& Cursor,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Promote a set of users in a group to the next role up.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param GroupId	 The group ID to promote in.
  * @param UserIds	 The users to promote.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> PromoteGroupUsers(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const FString& GroupId,
    const TArray<FString>& UserIds,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Promote a set of users in a group to the next role up.
  *
  * @param Config	The client configuration.
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
  ) noexcept;

  /**
  * Demote a set of users in a group to the next role down.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param GroupId	 The group ID to demote in.
  * @param UserIds	 The users to demote.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> DemoteGroupUsers(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const FString& GroupId,
    const TArray<FString>& UserIds,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Demote a set of users in a group to the next role down.
  *
  * @param Config	The client configuration.
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
  ) noexcept;

  /**
  * Get storage objects.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param ObjectIds	 Batch of storage objects.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaStorageObjectsResult> ReadStorageObjects(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const TArray<FNakamaReadStorageObjectId>& ObjectIds,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Get storage objects.
  *
  * @param Config	The client configuration.
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
  ) noexcept;

  /**
  * Execute a Lua function on the server.
  *
  * @param Config	The client configuration.
  * @param Id	 The identifier of the function.
  * @param Payload	 The payload of the function which must be a JSON object.
  * @param HttpKey	 The authentication key used when executed as a non-client HTTP request.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaRpcResult> RpcFunc(
    const FNakamaClientConfig& ClientConfig,
    const FString& Id,
    const FString& Payload,
    const FString& HttpKey,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Remove the Apple ID from the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Token	 The ID token received from Apple to validate.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkApple(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const FString& Token,
    const TMap<FString, FString>& Vars,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Remove the Apple ID from the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
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
  ) noexcept;

  /**
  * Remove the custom ID from the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Id	 A custom identifier.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkCustom(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const FString& Id,
    const TMap<FString, FString>& Vars,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Remove the custom ID from the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
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
  ) noexcept;

  /**
  * Remove the device ID from the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Id	 A device identifier. Should be obtained by a platform-specific device API.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkDevice(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const FString& Id,
    const TMap<FString, FString>& Vars,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Remove the device ID from the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
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
  ) noexcept;

  /**
  * Remove the email+password from the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Email	 A valid RFC-5322 email address.
  * @param Password	 A password for the user account.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkEmail(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const FString& Email,
    const FString& Password,
    const TMap<FString, FString>& Vars,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Remove the email+password from the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
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
  ) noexcept;

  /**
  * Remove Facebook from the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Token	 The OAuth token received from Facebook to access their profile API.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkFacebook(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const FString& Token,
    const TMap<FString, FString>& Vars,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Remove Facebook from the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
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
  ) noexcept;

  /**
  * Remove Facebook Instant Game profile from the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param SignedPlayerInfo	 The OAuth token received from a Facebook Instant Game that may be decoded with the Application Secret (must be available with the nakama configuration)
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkFacebookInstantGame(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const FString& SignedPlayerInfo,
    const TMap<FString, FString>& Vars,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Remove Facebook Instant Game profile from the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
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
  ) noexcept;

  /**
  * Remove Apple's GameCenter from the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
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
    const FString& HttpKey,
    const FString& PlayerId,
    const FString& BundleId,
    int64 TimestampSeconds,
    const FString& Salt,
    const FString& Signature,
    const FString& PublicKeyUrl,
    const TMap<FString, FString>& Vars,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Remove Apple's GameCenter from the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
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
  ) noexcept;

  /**
  * Remove Google from the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Token	 The OAuth token received from Google to access their profile API.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkGoogle(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const FString& Token,
    const TMap<FString, FString>& Vars,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Remove Google from the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
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
  ) noexcept;

  /**
  * Remove Steam from the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Token	 The account token received from Steam to access their profile API.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkSteam(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const FString& Token,
    const TMap<FString, FString>& Vars,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Remove Steam from the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
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
  ) noexcept;

  /**
  * Update fields in the current user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
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
    const FString& HttpKey,
    const FString& Username,
    const FString& DisplayName,
    const FString& AvatarUrl,
    const FString& LangTag,
    const FString& Location,
    const FString& Timezone,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Update fields in the current user's account.
  *
  * @param Config	The client configuration.
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
  ) noexcept;

  /**
  * Update fields in a given group.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
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
    const FString& HttpKey,
    const FString& GroupId,
    const FString& Name,
    const FString& Description,
    const FString& LangTag,
    const FString& AvatarUrl,
    bool Open,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Update fields in a given group.
  *
  * @param Config	The client configuration.
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
    bool Open,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Validate Apple IAP Receipt
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Receipt	 Base64 encoded Apple receipt data payload.
  * @param Persist	 Persist the purchase
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaValidatePurchaseResponseResult> ValidatePurchaseApple(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const FString& Receipt,
    bool Persist,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Validate Apple IAP Receipt
  *
  * @param Config	The client configuration.
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
    bool Persist,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Validate Apple Subscription Receipt
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Receipt	 Base64 encoded Apple receipt data payload.
  * @param Persist	 Persist the subscription.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaValidateSubscriptionResponseResult> ValidateSubscriptionApple(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const FString& Receipt,
    bool Persist,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Validate Apple Subscription Receipt
  *
  * @param Config	The client configuration.
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
    bool Persist,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Validate Google IAP Receipt
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Purchase	 JSON encoded Google purchase payload.
  * @param Persist	 Persist the purchase
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaValidatePurchaseResponseResult> ValidatePurchaseGoogle(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const FString& Purchase,
    bool Persist,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Validate Google IAP Receipt
  *
  * @param Config	The client configuration.
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
    bool Persist,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Validate Google Subscription Receipt
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Receipt	 JSON encoded Google purchase payload.
  * @param Persist	 Persist the subscription.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaValidateSubscriptionResponseResult> ValidateSubscriptionGoogle(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const FString& Receipt,
    bool Persist,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Validate Google Subscription Receipt
  *
  * @param Config	The client configuration.
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
    bool Persist,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Validate Huawei IAP Receipt
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Purchase	 JSON encoded Huawei InAppPurchaseData.
  * @param Signature	 InAppPurchaseData signature.
  * @param Persist	 Persist the purchase
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaValidatePurchaseResponseResult> ValidatePurchaseHuawei(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const FString& Purchase,
    const FString& Signature,
    bool Persist,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Validate Huawei IAP Receipt
  *
  * @param Config	The client configuration.
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
    bool Persist,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Validate FB Instant IAP Receipt
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param SignedRequest	 Base64 encoded Facebook Instant signedRequest receipt data payload.
  * @param Persist	 Persist the purchase
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaValidatePurchaseResponseResult> ValidatePurchaseFacebookInstant(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const FString& SignedRequest,
    bool Persist,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Validate FB Instant IAP Receipt
  *
  * @param Config	The client configuration.
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
    bool Persist,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Write a record to a leaderboard.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
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
    const FString& HttpKey,
    const FString& LeaderboardId,
    int64 RecordScore,
    int64 RecordSubscore,
    const FString& RecordMetadata,
    ENakamaOperator RecordOperator,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Write a record to a leaderboard.
  *
  * @param Config	The client configuration.
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
  ) noexcept;

  /**
  * Write objects into the storage engine.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Objects	 The objects to store on the server.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  NAKAMA_API TNakamaFuture<FNakamaStorageObjectAcksResult> WriteStorageObjects(
    const FNakamaClientConfig& ClientConfig,
    const FString& HttpKey,
    const TArray<FNakamaWriteStorageObject>& Objects,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Write objects into the storage engine.
  *
  * @param Config	The client configuration.
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
  ) noexcept;

  /**
  * Write a record to a tournament.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
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
    const FString& HttpKey,
    const FString& TournamentId,
    int64 RecordScore,
    int64 RecordSubscore,
    const FString& RecordMetadata,
    ENakamaOperator RecordOperator,
    const FNakamaRetryConfig& RetryConfig = {},
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;

  /**
  * Write a record to a tournament.
  *
  * @param Config	The client configuration.
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
  ) noexcept;
}
