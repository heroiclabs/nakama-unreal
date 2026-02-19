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
#include "Async/Future.h"
#include "NakamaApi.h"
#include <type_traits>

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
	FNakamaSession Value{};
	FNakamaError Error;
	bool bIsError = true;
};

struct NAKAMA_API FNakamaGroupResult
{
	using ValueType = FNakamaGroup;
	FNakamaGroup Value{};
	FNakamaError Error;
	bool bIsError = true;
};

struct NAKAMA_API FNakamaAccountResult
{
	using ValueType = FNakamaAccount;
	FNakamaAccount Value{};
	FNakamaError Error;
	bool bIsError = true;
};

struct NAKAMA_API FNakamaUsersResult
{
	using ValueType = FNakamaUsers;
	FNakamaUsers Value{};
	FNakamaError Error;
	bool bIsError = true;
};

struct NAKAMA_API FNakamaValidatedSubscriptionResult
{
	using ValueType = FNakamaValidatedSubscription;
	FNakamaValidatedSubscription Value{};
	FNakamaError Error;
	bool bIsError = true;
};

struct NAKAMA_API FNakamaMatchmakerStatsResult
{
	using ValueType = FNakamaMatchmakerStats;
	FNakamaMatchmakerStats Value{};
	FNakamaError Error;
	bool bIsError = true;
};

struct NAKAMA_API FNakamaChannelMessageListResult
{
	using ValueType = FNakamaChannelMessageList;
	FNakamaChannelMessageList Value{};
	FNakamaError Error;
	bool bIsError = true;
};

struct NAKAMA_API FNakamaFriendListResult
{
	using ValueType = FNakamaFriendList;
	FNakamaFriendList Value{};
	FNakamaError Error;
	bool bIsError = true;
};

struct NAKAMA_API FNakamaFriendsOfFriendsListResult
{
	using ValueType = FNakamaFriendsOfFriendsList;
	FNakamaFriendsOfFriendsList Value{};
	FNakamaError Error;
	bool bIsError = true;
};

struct NAKAMA_API FNakamaGroupListResult
{
	using ValueType = FNakamaGroupList;
	FNakamaGroupList Value{};
	FNakamaError Error;
	bool bIsError = true;
};

struct NAKAMA_API FNakamaGroupUserListResult
{
	using ValueType = FNakamaGroupUserList;
	FNakamaGroupUserList Value{};
	FNakamaError Error;
	bool bIsError = true;
};

struct NAKAMA_API FNakamaLeaderboardRecordListResult
{
	using ValueType = FNakamaLeaderboardRecordList;
	FNakamaLeaderboardRecordList Value{};
	FNakamaError Error;
	bool bIsError = true;
};

struct NAKAMA_API FNakamaMatchListResult
{
	using ValueType = FNakamaMatchList;
	FNakamaMatchList Value{};
	FNakamaError Error;
	bool bIsError = true;
};

struct NAKAMA_API FNakamaPartyListResult
{
	using ValueType = FNakamaPartyList;
	FNakamaPartyList Value{};
	FNakamaError Error;
	bool bIsError = true;
};

struct NAKAMA_API FNakamaNotificationListResult
{
	using ValueType = FNakamaNotificationList;
	FNakamaNotificationList Value{};
	FNakamaError Error;
	bool bIsError = true;
};

struct NAKAMA_API FNakamaStorageObjectListResult
{
	using ValueType = FNakamaStorageObjectList;
	FNakamaStorageObjectList Value{};
	FNakamaError Error;
	bool bIsError = true;
};

struct NAKAMA_API FNakamaSubscriptionListResult
{
	using ValueType = FNakamaSubscriptionList;
	FNakamaSubscriptionList Value{};
	FNakamaError Error;
	bool bIsError = true;
};

struct NAKAMA_API FNakamaTournamentListResult
{
	using ValueType = FNakamaTournamentList;
	FNakamaTournamentList Value{};
	FNakamaError Error;
	bool bIsError = true;
};

struct NAKAMA_API FNakamaTournamentRecordListResult
{
	using ValueType = FNakamaTournamentRecordList;
	FNakamaTournamentRecordList Value{};
	FNakamaError Error;
	bool bIsError = true;
};

struct NAKAMA_API FNakamaUserGroupListResult
{
	using ValueType = FNakamaUserGroupList;
	FNakamaUserGroupList Value{};
	FNakamaError Error;
	bool bIsError = true;
};

struct NAKAMA_API FNakamaStorageObjectsResult
{
	using ValueType = FNakamaStorageObjects;
	FNakamaStorageObjects Value{};
	FNakamaError Error;
	bool bIsError = true;
};

struct NAKAMA_API FNakamaRpcResult
{
	using ValueType = FNakamaRpc;
	FNakamaRpc Value{};
	FNakamaError Error;
	bool bIsError = true;
};

struct NAKAMA_API FNakamaValidatePurchaseResponseResult
{
	using ValueType = FNakamaValidatePurchaseResponse;
	FNakamaValidatePurchaseResponse Value{};
	FNakamaError Error;
	bool bIsError = true;
};

struct NAKAMA_API FNakamaValidateSubscriptionResponseResult
{
	using ValueType = FNakamaValidateSubscriptionResponse;
	FNakamaValidateSubscriptionResponse Value{};
	FNakamaError Error;
	bool bIsError = true;
};

struct NAKAMA_API FNakamaLeaderboardRecordResult
{
	using ValueType = FNakamaLeaderboardRecord;
	FNakamaLeaderboardRecord Value{};
	FNakamaError Error;
	bool bIsError = true;
};

struct NAKAMA_API FNakamaStorageObjectAcksResult
{
	using ValueType = FNakamaStorageObjectAcks;
	FNakamaStorageObjectAcks Value{};
	FNakamaError Error;
	bool bIsError = true;
};

// Forward declaration
template<typename T> struct TNakamaFuture;

/** Type trait: is T a TNakamaFuture<U>? */
template<typename T> struct TIsTNakamaFuture : std::false_type {};
template<typename T> struct TIsTNakamaFuture<TNakamaFuture<T>> : std::true_type {};

/**
 * Chainable future wrapper for async Nakama operations.
 * Parameterized by concrete result type (e.g. FNakamaSessionResult).
 *
 * Chaining: Next(callback(const ValueType&) -> TNakamaFuture<OtherResult>) — flattens and propagates errors
 * Terminal: Next(callback(ResultT) -> void) — receives the full result
 */
template<typename ResultT>
struct TNakamaFuture
{
	using ValueType = typename ResultT::ValueType;
	using WrappedResultType = ResultT;

	TFuture<ResultT> Future;

	TNakamaFuture() = default;

	explicit TNakamaFuture(TFuture<ResultT>&& InFuture) noexcept
		: Future(MoveTemp(InFuture)) {}

	TNakamaFuture(TNakamaFuture&& Other) noexcept = default;
	TNakamaFuture& operator=(TNakamaFuture&& Other) noexcept = default;
	TNakamaFuture(const TNakamaFuture&) = delete;
	TNakamaFuture& operator=(const TNakamaFuture&) = delete;

	/** Chaining Next: callback(const ValueType&) -> TNakamaFuture<OtherResult> */
	template<typename Func,
		typename Ret = std::invoke_result_t<std::decay_t<Func>, const ValueType&>,
		std::enable_if_t<TIsTNakamaFuture<Ret>::value, int> = 0>
	Ret Next(Func&& Callback) && noexcept
	{
		using InnerResultT = typename Ret::WrappedResultType;
		auto OuterPromise = MakeShared<TPromise<InnerResultT>>();
		Ret ResultFuture(OuterPromise->GetFuture());

		MoveTemp(Future).Next([Cb = Forward<Func>(Callback), OuterPromise](ResultT Result) mutable
		{
			if (Result.bIsError)
			{
				OuterPromise->SetValue(InnerResultT{{}, Result.Error, true});
				return;
			}
			Ret Inner = Cb(Result.Value);
			MoveTemp(Inner.Future).Next([OuterPromise](InnerResultT InnerResult) mutable
			{
				OuterPromise->SetValue(MoveTemp(InnerResult));
			});
		});

		return ResultFuture;
	}

	/** Terminal Next: callback(ResultT) -> void */
	template<typename Func,
		typename Ret = std::invoke_result_t<std::decay_t<Func>, ResultT>,
		std::enable_if_t<!TIsTNakamaFuture<Ret>::value, int> = 0>
	void Next(Func&& Callback) && noexcept
	{
		MoveTemp(Future).Next([Cb = Forward<Func>(Callback)](ResultT Result) mutable
		{
			Cb(MoveTemp(Result));
		});
	}
};

/** Retry configuration for transient error handling. */
struct NAKAMA_API FNakamaRetryConfiguration
{
	/** Maximum number of retry attempts (0 = no retries). */
	int32 MaxRetries = 4;

	/** Base delay in milliseconds before first retry. Actual delay uses exponential backoff with full jitter. */
	int32 BaseDelayMs = 500;

	FNakamaRetryConfiguration() = default;
	FNakamaRetryConfiguration(int32 InMaxRetries, int32 InBaseDelayMs)
		: MaxRetries(InMaxRetries), BaseDelayMs(InBaseDelayMs) {}
};

/**
 * High-level Nakama client configuration.
 * Holds an API config plus retry and session auto-refresh settings.
 */
struct NAKAMA_API FNakamaClient
{
	FNakamaApiConfig ApiConfig;
	FNakamaRetryConfiguration RetryConfiguration;
	bool bAutoRefreshSession = true;
	int64 AutoRefreshBufferSeconds = 300;

	/** Called after a session is automatically refreshed, so callers can persist the updated session. */
	TFunction<void(const FNakamaSession&)> OnSessionRefreshed;

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
	NAKAMA_API float CalculateBackoff(int32 Attempt, const FNakamaRetryConfiguration& Config) noexcept;

	/** Add friends by ID or username to a user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> AddFriends(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		FString Metadata,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add friends by ID or username to a user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> AddFriends(
		FNakamaClient Client,
		const FString& HttpKey,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		FString Metadata,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add users to a group. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> AddGroupUsers(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString GroupId,
		const TArray<FString>& UserIds,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add users to a group. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> AddGroupUsers(
		FNakamaClient Client,
		const FString& HttpKey,
		FString GroupId,
		const TArray<FString>& UserIds,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Refresh a user's session using a refresh token retrieved from a previous authentication request. */
	NAKAMA_API TNakamaFuture<FNakamaSessionResult> SessionRefresh(
		FNakamaClient Client,
		FString Token,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Log out a session, invalidate a refresh token, or log out all sessions/refresh tokens for a user. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> SessionLogout(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString Token,
		FString RefreshToken,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Log out a session, invalidate a refresh token, or log out all sessions/refresh tokens for a user. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> SessionLogout(
		FNakamaClient Client,
		const FString& HttpKey,
		FString Token,
		FString RefreshToken,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Authenticate a user with an Apple ID against the server. */
	NAKAMA_API TNakamaFuture<FNakamaSessionResult> AuthenticateApple(
		FNakamaClient Client,
		FNakamaAccountApple Account,
		bool Create,
		FString Username,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Authenticate a user with a custom id against the server. */
	NAKAMA_API TNakamaFuture<FNakamaSessionResult> AuthenticateCustom(
		FNakamaClient Client,
		FNakamaAccountCustom Account,
		bool Create,
		FString Username,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Authenticate a user with a device id against the server. */
	NAKAMA_API TNakamaFuture<FNakamaSessionResult> AuthenticateDevice(
		FNakamaClient Client,
		FNakamaAccountDevice Account,
		bool Create,
		FString Username,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Authenticate a user with an email+password against the server. */
	NAKAMA_API TNakamaFuture<FNakamaSessionResult> AuthenticateEmail(
		FNakamaClient Client,
		FNakamaAccountEmail Account,
		bool Create,
		FString Username,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Authenticate a user with a Facebook OAuth token against the server. */
	NAKAMA_API TNakamaFuture<FNakamaSessionResult> AuthenticateFacebook(
		FNakamaClient Client,
		FNakamaAccountFacebook Account,
		bool Create,
		FString Username,
		bool Sync,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Authenticate a user with a Facebook Instant Game token against the server. */
	NAKAMA_API TNakamaFuture<FNakamaSessionResult> AuthenticateFacebookInstantGame(
		FNakamaClient Client,
		FNakamaAccountFacebookInstantGame Account,
		bool Create,
		FString Username,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Authenticate a user with Apple's GameCenter against the server. */
	NAKAMA_API TNakamaFuture<FNakamaSessionResult> AuthenticateGameCenter(
		FNakamaClient Client,
		FNakamaAccountGameCenter Account,
		bool Create,
		FString Username,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Authenticate a user with Google against the server. */
	NAKAMA_API TNakamaFuture<FNakamaSessionResult> AuthenticateGoogle(
		FNakamaClient Client,
		FNakamaAccountGoogle Account,
		bool Create,
		FString Username,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Authenticate a user with Steam against the server. */
	NAKAMA_API TNakamaFuture<FNakamaSessionResult> AuthenticateSteam(
		FNakamaClient Client,
		FNakamaAccountSteam Account,
		bool Create,
		FString Username,
		bool Sync,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Ban a set of users from a group. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> BanGroupUsers(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString GroupId,
		const TArray<FString>& UserIds,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Ban a set of users from a group. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> BanGroupUsers(
		FNakamaClient Client,
		const FString& HttpKey,
		FString GroupId,
		const TArray<FString>& UserIds,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Block one or more users by ID or username. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> BlockFriends(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Block one or more users by ID or username. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> BlockFriends(
		FNakamaClient Client,
		const FString& HttpKey,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Create a new group with the current user as the owner. */
	NAKAMA_API TNakamaFuture<FNakamaGroupResult> CreateGroup(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString Name,
		FString Description,
		FString LangTag,
		FString AvatarUrl,
		bool Open,
		int32 MaxCount,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Create a new group with the current user as the owner. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaGroupResult> CreateGroup(
		FNakamaClient Client,
		const FString& HttpKey,
		FString Name,
		FString Description,
		FString LangTag,
		FString AvatarUrl,
		bool Open,
		int32 MaxCount,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete the current user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> DeleteAccount(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete the current user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> DeleteAccount(
		FNakamaClient Client,
		const FString& HttpKey,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete one or more users by ID or username. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> DeleteFriends(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete one or more users by ID or username. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> DeleteFriends(
		FNakamaClient Client,
		const FString& HttpKey,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete a group by ID. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> DeleteGroup(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString GroupId,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete a group by ID. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> DeleteGroup(
		FNakamaClient Client,
		const FString& HttpKey,
		FString GroupId,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete a leaderboard record. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> DeleteLeaderboardRecord(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString LeaderboardId,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete a leaderboard record. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> DeleteLeaderboardRecord(
		FNakamaClient Client,
		const FString& HttpKey,
		FString LeaderboardId,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete one or more notifications for the current user. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> DeleteNotifications(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		const TArray<FString>& Ids,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete one or more notifications for the current user. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> DeleteNotifications(
		FNakamaClient Client,
		const FString& HttpKey,
		const TArray<FString>& Ids,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete a tournament record. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> DeleteTournamentRecord(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString TournamentId,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete a tournament record. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> DeleteTournamentRecord(
		FNakamaClient Client,
		const FString& HttpKey,
		FString TournamentId,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete one or more objects by ID or username. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> DeleteStorageObjects(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		const TArray<FNakamaDeleteStorageObjectId>& ObjectIds,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete one or more objects by ID or username. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> DeleteStorageObjects(
		FNakamaClient Client,
		const FString& HttpKey,
		const TArray<FNakamaDeleteStorageObjectId>& ObjectIds,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Submit an event for processing in the server's registered runtime custom events handler. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> Event(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString Name,
		FString Timestamp,
		bool External,
		const TMap<FString, FString>& Properties,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Submit an event for processing in the server's registered runtime custom events handler. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> Event(
		FNakamaClient Client,
		const FString& HttpKey,
		FString Name,
		FString Timestamp,
		bool External,
		const TMap<FString, FString>& Properties,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Fetch the current user's account. */
	NAKAMA_API TNakamaFuture<FNakamaAccountResult> GetAccount(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Fetch the current user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaAccountResult> GetAccount(
		FNakamaClient Client,
		const FString& HttpKey,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Fetch zero or more users by ID and/or username. */
	NAKAMA_API TNakamaFuture<FNakamaUsersResult> GetUsers(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		const TArray<FString>& FacebookIds,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Fetch zero or more users by ID and/or username. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaUsersResult> GetUsers(
		FNakamaClient Client,
		const FString& HttpKey,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		const TArray<FString>& FacebookIds,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Get subscription by product id. */
	NAKAMA_API TNakamaFuture<FNakamaValidatedSubscriptionResult> GetSubscription(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString ProductId,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Get subscription by product id. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaValidatedSubscriptionResult> GetSubscription(
		FNakamaClient Client,
		const FString& HttpKey,
		FString ProductId,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Get matchmaker stats. */
	NAKAMA_API TNakamaFuture<FNakamaMatchmakerStatsResult> GetMatchmakerStats(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Get matchmaker stats. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaMatchmakerStatsResult> GetMatchmakerStats(
		FNakamaClient Client,
		const FString& HttpKey,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** A healthcheck which load balancers can use to check the service. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> Healthcheck(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** A healthcheck which load balancers can use to check the service. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> Healthcheck(
		FNakamaClient Client,
		const FString& HttpKey,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Import Facebook friends and add them to a user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> ImportFacebookFriends(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FNakamaAccountFacebook Account,
		bool Reset,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Import Facebook friends and add them to a user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> ImportFacebookFriends(
		FNakamaClient Client,
		const FString& HttpKey,
		FNakamaAccountFacebook Account,
		bool Reset,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Import Steam friends and add them to a user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> ImportSteamFriends(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FNakamaAccountSteam Account,
		bool Reset,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Import Steam friends and add them to a user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> ImportSteamFriends(
		FNakamaClient Client,
		const FString& HttpKey,
		FNakamaAccountSteam Account,
		bool Reset,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Immediately join an open group, or request to join a closed one. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> JoinGroup(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString GroupId,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Immediately join an open group, or request to join a closed one. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> JoinGroup(
		FNakamaClient Client,
		const FString& HttpKey,
		FString GroupId,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Attempt to join an open and running tournament. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> JoinTournament(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString TournamentId,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Attempt to join an open and running tournament. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> JoinTournament(
		FNakamaClient Client,
		const FString& HttpKey,
		FString TournamentId,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Kick a set of users from a group. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> KickGroupUsers(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString GroupId,
		const TArray<FString>& UserIds,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Kick a set of users from a group. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> KickGroupUsers(
		FNakamaClient Client,
		const FString& HttpKey,
		FString GroupId,
		const TArray<FString>& UserIds,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Leave a group the user is a member of. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> LeaveGroup(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString GroupId,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Leave a group the user is a member of. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> LeaveGroup(
		FNakamaClient Client,
		const FString& HttpKey,
		FString GroupId,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add an Apple ID to the social profiles on the current user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkApple(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString Token,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add an Apple ID to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkApple(
		FNakamaClient Client,
		const FString& HttpKey,
		FString Token,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add a custom ID to the social profiles on the current user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkCustom(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString Id,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add a custom ID to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkCustom(
		FNakamaClient Client,
		const FString& HttpKey,
		FString Id,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add a device ID to the social profiles on the current user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkDevice(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString Id,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add a device ID to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkDevice(
		FNakamaClient Client,
		const FString& HttpKey,
		FString Id,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add an email+password to the social profiles on the current user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkEmail(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString Email,
		FString Password,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add an email+password to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkEmail(
		FNakamaClient Client,
		const FString& HttpKey,
		FString Email,
		FString Password,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add Facebook to the social profiles on the current user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkFacebook(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FNakamaAccountFacebook Account,
		bool Sync,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add Facebook to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkFacebook(
		FNakamaClient Client,
		const FString& HttpKey,
		FNakamaAccountFacebook Account,
		bool Sync,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add Facebook Instant Game to the social profiles on the current user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkFacebookInstantGame(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString SignedPlayerInfo,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add Facebook Instant Game to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkFacebookInstantGame(
		FNakamaClient Client,
		const FString& HttpKey,
		FString SignedPlayerInfo,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add Apple's GameCenter to the social profiles on the current user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkGameCenter(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString PlayerId,
		FString BundleId,
		int64 TimestampSeconds,
		FString Salt,
		FString Signature,
		FString PublicKeyUrl,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add Apple's GameCenter to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkGameCenter(
		FNakamaClient Client,
		const FString& HttpKey,
		FString PlayerId,
		FString BundleId,
		int64 TimestampSeconds,
		FString Salt,
		FString Signature,
		FString PublicKeyUrl,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add Google to the social profiles on the current user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkGoogle(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString Token,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add Google to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkGoogle(
		FNakamaClient Client,
		const FString& HttpKey,
		FString Token,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add Steam to the social profiles on the current user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkSteam(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FNakamaAccountSteam Account,
		bool Sync,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add Steam to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkSteam(
		FNakamaClient Client,
		const FString& HttpKey,
		FNakamaAccountSteam Account,
		bool Sync,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List a channel's message history. */
	NAKAMA_API TNakamaFuture<FNakamaChannelMessageListResult> ListChannelMessages(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString ChannelId,
		int32 Limit,
		bool Forward,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List a channel's message history. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaChannelMessageListResult> ListChannelMessages(
		FNakamaClient Client,
		const FString& HttpKey,
		FString ChannelId,
		int32 Limit,
		bool Forward,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List all friends for the current user. */
	NAKAMA_API TNakamaFuture<FNakamaFriendListResult> ListFriends(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		int32 Limit,
		int32 State,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List all friends for the current user. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaFriendListResult> ListFriends(
		FNakamaClient Client,
		const FString& HttpKey,
		int32 Limit,
		int32 State,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List friends of friends for the current user. */
	NAKAMA_API TNakamaFuture<FNakamaFriendsOfFriendsListResult> ListFriendsOfFriends(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		int32 Limit,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List friends of friends for the current user. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaFriendsOfFriendsListResult> ListFriendsOfFriends(
		FNakamaClient Client,
		const FString& HttpKey,
		int32 Limit,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List groups based on given filters. */
	NAKAMA_API TNakamaFuture<FNakamaGroupListResult> ListGroups(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString Name,
		FString Cursor,
		int32 Limit,
		FString LangTag,
		int32 Members,
		bool Open,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List groups based on given filters. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaGroupListResult> ListGroups(
		FNakamaClient Client,
		const FString& HttpKey,
		FString Name,
		FString Cursor,
		int32 Limit,
		FString LangTag,
		int32 Members,
		bool Open,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List all users that are part of a group. */
	NAKAMA_API TNakamaFuture<FNakamaGroupUserListResult> ListGroupUsers(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString GroupId,
		int32 Limit,
		int32 State,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List all users that are part of a group. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaGroupUserListResult> ListGroupUsers(
		FNakamaClient Client,
		const FString& HttpKey,
		FString GroupId,
		int32 Limit,
		int32 State,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List leaderboard records. */
	NAKAMA_API TNakamaFuture<FNakamaLeaderboardRecordListResult> ListLeaderboardRecords(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString LeaderboardId,
		const TArray<FString>& OwnerIds,
		int32 Limit,
		FString Cursor,
		int64 Expiry,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List leaderboard records. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaLeaderboardRecordListResult> ListLeaderboardRecords(
		FNakamaClient Client,
		const FString& HttpKey,
		FString LeaderboardId,
		const TArray<FString>& OwnerIds,
		int32 Limit,
		FString Cursor,
		int64 Expiry,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List leaderboard records around the target ownerId. */
	NAKAMA_API TNakamaFuture<FNakamaLeaderboardRecordListResult> ListLeaderboardRecordsAroundOwner(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString LeaderboardId,
		int32 Limit,
		FString OwnerId,
		int64 Expiry,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List leaderboard records around the target ownerId. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaLeaderboardRecordListResult> ListLeaderboardRecordsAroundOwner(
		FNakamaClient Client,
		const FString& HttpKey,
		FString LeaderboardId,
		int32 Limit,
		FString OwnerId,
		int64 Expiry,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List running matches and optionally filter by matching criteria. */
	NAKAMA_API TNakamaFuture<FNakamaMatchListResult> ListMatches(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		int32 Limit,
		bool Authoritative,
		FString Label,
		int32 MinSize,
		int32 MaxSize,
		FString Query,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List running matches and optionally filter by matching criteria. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaMatchListResult> ListMatches(
		FNakamaClient Client,
		const FString& HttpKey,
		int32 Limit,
		bool Authoritative,
		FString Label,
		int32 MinSize,
		int32 MaxSize,
		FString Query,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List parties and optionally filter by matching criteria. */
	NAKAMA_API TNakamaFuture<FNakamaPartyListResult> ListParties(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		int32 Limit,
		bool Open,
		FString Query,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List parties and optionally filter by matching criteria. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaPartyListResult> ListParties(
		FNakamaClient Client,
		const FString& HttpKey,
		int32 Limit,
		bool Open,
		FString Query,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Fetch list of notifications. */
	NAKAMA_API TNakamaFuture<FNakamaNotificationListResult> ListNotifications(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		int32 Limit,
		FString CacheableCursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Fetch list of notifications. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaNotificationListResult> ListNotifications(
		FNakamaClient Client,
		const FString& HttpKey,
		int32 Limit,
		FString CacheableCursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List publicly readable storage objects in a given collection. */
	NAKAMA_API TNakamaFuture<FNakamaStorageObjectListResult> ListStorageObjects(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString UserId,
		FString Collection,
		int32 Limit,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List publicly readable storage objects in a given collection. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaStorageObjectListResult> ListStorageObjects(
		FNakamaClient Client,
		const FString& HttpKey,
		FString UserId,
		FString Collection,
		int32 Limit,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List user's subscriptions. */
	NAKAMA_API TNakamaFuture<FNakamaSubscriptionListResult> ListSubscriptions(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		int32 Limit,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List user's subscriptions. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaSubscriptionListResult> ListSubscriptions(
		FNakamaClient Client,
		const FString& HttpKey,
		int32 Limit,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List current or upcoming tournaments. */
	NAKAMA_API TNakamaFuture<FNakamaTournamentListResult> ListTournaments(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		int32 CategoryStart,
		int32 CategoryEnd,
		int32 StartTime,
		int32 EndTime,
		int32 Limit,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List current or upcoming tournaments. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaTournamentListResult> ListTournaments(
		FNakamaClient Client,
		const FString& HttpKey,
		int32 CategoryStart,
		int32 CategoryEnd,
		int32 StartTime,
		int32 EndTime,
		int32 Limit,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List tournament records. */
	NAKAMA_API TNakamaFuture<FNakamaTournamentRecordListResult> ListTournamentRecords(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString TournamentId,
		const TArray<FString>& OwnerIds,
		int32 Limit,
		FString Cursor,
		int64 Expiry,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List tournament records. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaTournamentRecordListResult> ListTournamentRecords(
		FNakamaClient Client,
		const FString& HttpKey,
		FString TournamentId,
		const TArray<FString>& OwnerIds,
		int32 Limit,
		FString Cursor,
		int64 Expiry,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List tournament records for a given owner. */
	NAKAMA_API TNakamaFuture<FNakamaTournamentRecordListResult> ListTournamentRecordsAroundOwner(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString TournamentId,
		int32 Limit,
		FString OwnerId,
		int64 Expiry,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List tournament records for a given owner. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaTournamentRecordListResult> ListTournamentRecordsAroundOwner(
		FNakamaClient Client,
		const FString& HttpKey,
		FString TournamentId,
		int32 Limit,
		FString OwnerId,
		int64 Expiry,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List groups the current user belongs to. */
	NAKAMA_API TNakamaFuture<FNakamaUserGroupListResult> ListUserGroups(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString UserId,
		int32 Limit,
		int32 State,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List groups the current user belongs to. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaUserGroupListResult> ListUserGroups(
		FNakamaClient Client,
		const FString& HttpKey,
		FString UserId,
		int32 Limit,
		int32 State,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Promote a set of users in a group to the next role up. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> PromoteGroupUsers(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString GroupId,
		const TArray<FString>& UserIds,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Promote a set of users in a group to the next role up. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> PromoteGroupUsers(
		FNakamaClient Client,
		const FString& HttpKey,
		FString GroupId,
		const TArray<FString>& UserIds,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Demote a set of users in a group to the next role down. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> DemoteGroupUsers(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString GroupId,
		const TArray<FString>& UserIds,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Demote a set of users in a group to the next role down. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> DemoteGroupUsers(
		FNakamaClient Client,
		const FString& HttpKey,
		FString GroupId,
		const TArray<FString>& UserIds,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Get storage objects. */
	NAKAMA_API TNakamaFuture<FNakamaStorageObjectsResult> ReadStorageObjects(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		const TArray<FNakamaReadStorageObjectId>& ObjectIds,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Get storage objects. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaStorageObjectsResult> ReadStorageObjects(
		FNakamaClient Client,
		const FString& HttpKey,
		const TArray<FNakamaReadStorageObjectId>& ObjectIds,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Execute a Lua function on the server. */
	NAKAMA_API TNakamaFuture<FNakamaRpcResult> RpcFunc(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString Id,
		TSharedPtr<FJsonObject> Payload,
		FString HttpKey,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Execute a Lua function on the server. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaRpcResult> RpcFunc(
		FNakamaClient Client,
		const FString& HttpKey,
		FString Id,
		TSharedPtr<FJsonObject> Payload,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove the Apple ID from the social profiles on the current user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkApple(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString Token,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove the Apple ID from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkApple(
		FNakamaClient Client,
		const FString& HttpKey,
		FString Token,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove the custom ID from the social profiles on the current user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkCustom(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString Id,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove the custom ID from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkCustom(
		FNakamaClient Client,
		const FString& HttpKey,
		FString Id,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove the device ID from the social profiles on the current user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkDevice(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString Id,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove the device ID from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkDevice(
		FNakamaClient Client,
		const FString& HttpKey,
		FString Id,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove the email+password from the social profiles on the current user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkEmail(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString Email,
		FString Password,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove the email+password from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkEmail(
		FNakamaClient Client,
		const FString& HttpKey,
		FString Email,
		FString Password,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove Facebook from the social profiles on the current user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkFacebook(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString Token,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove Facebook from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkFacebook(
		FNakamaClient Client,
		const FString& HttpKey,
		FString Token,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove Facebook Instant Game profile from the social profiles on the current user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkFacebookInstantGame(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString SignedPlayerInfo,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove Facebook Instant Game profile from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkFacebookInstantGame(
		FNakamaClient Client,
		const FString& HttpKey,
		FString SignedPlayerInfo,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove Apple's GameCenter from the social profiles on the current user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkGameCenter(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString PlayerId,
		FString BundleId,
		int64 TimestampSeconds,
		FString Salt,
		FString Signature,
		FString PublicKeyUrl,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove Apple's GameCenter from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkGameCenter(
		FNakamaClient Client,
		const FString& HttpKey,
		FString PlayerId,
		FString BundleId,
		int64 TimestampSeconds,
		FString Salt,
		FString Signature,
		FString PublicKeyUrl,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove Google from the social profiles on the current user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkGoogle(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString Token,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove Google from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkGoogle(
		FNakamaClient Client,
		const FString& HttpKey,
		FString Token,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove Steam from the social profiles on the current user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkSteam(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString Token,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove Steam from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkSteam(
		FNakamaClient Client,
		const FString& HttpKey,
		FString Token,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Update fields in the current user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UpdateAccount(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString Username,
		FString DisplayName,
		FString AvatarUrl,
		FString LangTag,
		FString Location,
		FString Timezone,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Update fields in the current user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UpdateAccount(
		FNakamaClient Client,
		const FString& HttpKey,
		FString Username,
		FString DisplayName,
		FString AvatarUrl,
		FString LangTag,
		FString Location,
		FString Timezone,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Update fields in a given group. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UpdateGroup(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString GroupId,
		FString Name,
		FString Description,
		FString LangTag,
		FString AvatarUrl,
		bool Open,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Update fields in a given group. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UpdateGroup(
		FNakamaClient Client,
		const FString& HttpKey,
		FString GroupId,
		FString Name,
		FString Description,
		FString LangTag,
		FString AvatarUrl,
		bool Open,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Validate Apple IAP Receipt */
	NAKAMA_API TNakamaFuture<FNakamaValidatePurchaseResponseResult> ValidatePurchaseApple(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString Receipt,
		bool Persist,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Validate Apple IAP Receipt (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaValidatePurchaseResponseResult> ValidatePurchaseApple(
		FNakamaClient Client,
		const FString& HttpKey,
		FString Receipt,
		bool Persist,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Validate Apple Subscription Receipt */
	NAKAMA_API TNakamaFuture<FNakamaValidateSubscriptionResponseResult> ValidateSubscriptionApple(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString Receipt,
		bool Persist,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Validate Apple Subscription Receipt (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaValidateSubscriptionResponseResult> ValidateSubscriptionApple(
		FNakamaClient Client,
		const FString& HttpKey,
		FString Receipt,
		bool Persist,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Validate Google IAP Receipt */
	NAKAMA_API TNakamaFuture<FNakamaValidatePurchaseResponseResult> ValidatePurchaseGoogle(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString Purchase,
		bool Persist,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Validate Google IAP Receipt (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaValidatePurchaseResponseResult> ValidatePurchaseGoogle(
		FNakamaClient Client,
		const FString& HttpKey,
		FString Purchase,
		bool Persist,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Validate Google Subscription Receipt */
	NAKAMA_API TNakamaFuture<FNakamaValidateSubscriptionResponseResult> ValidateSubscriptionGoogle(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString Receipt,
		bool Persist,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Validate Google Subscription Receipt (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaValidateSubscriptionResponseResult> ValidateSubscriptionGoogle(
		FNakamaClient Client,
		const FString& HttpKey,
		FString Receipt,
		bool Persist,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Validate Huawei IAP Receipt */
	NAKAMA_API TNakamaFuture<FNakamaValidatePurchaseResponseResult> ValidatePurchaseHuawei(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString Purchase,
		FString Signature,
		bool Persist,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Validate Huawei IAP Receipt (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaValidatePurchaseResponseResult> ValidatePurchaseHuawei(
		FNakamaClient Client,
		const FString& HttpKey,
		FString Purchase,
		FString Signature,
		bool Persist,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Validate FB Instant IAP Receipt */
	NAKAMA_API TNakamaFuture<FNakamaValidatePurchaseResponseResult> ValidatePurchaseFacebookInstant(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString SignedRequest,
		bool Persist,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Validate FB Instant IAP Receipt (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaValidatePurchaseResponseResult> ValidatePurchaseFacebookInstant(
		FNakamaClient Client,
		const FString& HttpKey,
		FString SignedRequest,
		bool Persist,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Write a record to a leaderboard. */
	NAKAMA_API TNakamaFuture<FNakamaLeaderboardRecordResult> WriteLeaderboardRecord(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString LeaderboardId,
		FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite Record,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Write a record to a leaderboard. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaLeaderboardRecordResult> WriteLeaderboardRecord(
		FNakamaClient Client,
		const FString& HttpKey,
		FString LeaderboardId,
		FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite Record,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Write objects into the storage engine. */
	NAKAMA_API TNakamaFuture<FNakamaStorageObjectAcksResult> WriteStorageObjects(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		const TArray<FNakamaWriteStorageObject>& Objects,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Write objects into the storage engine. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaStorageObjectAcksResult> WriteStorageObjects(
		FNakamaClient Client,
		const FString& HttpKey,
		const TArray<FNakamaWriteStorageObject>& Objects,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Write a record to a tournament. */
	NAKAMA_API TNakamaFuture<FNakamaLeaderboardRecordResult> WriteTournamentRecord(
		FNakamaClient Client,
		FNakamaSessionPtr Session,
		FString TournamentId,
		FNakamaWriteTournamentRecordRequest_TournamentRecordWrite Record,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Write a record to a tournament. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaLeaderboardRecordResult> WriteTournamentRecord(
		FNakamaClient Client,
		const FString& HttpKey,
		FString TournamentId,
		FNakamaWriteTournamentRecordRequest_TournamentRecordWrite Record,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;
}
