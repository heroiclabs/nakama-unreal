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
#include "Tasks/Task.h"
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

	struct FState
	{
		ResultT Result{};
		UE::Tasks::FTaskEvent Event{ UE_SOURCE_LOCATION };
		void Resolve(ResultT&& InResult)
		{
			Result = MoveTemp(InResult);
			Event.Trigger();
		}
	};

	TSharedPtr<FState> State;

	TNakamaFuture() = default;
	explicit TNakamaFuture(TSharedPtr<FState> InState) noexcept
		: State(MoveTemp(InState)) {}
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
		auto OuterState = MakeShared<typename TNakamaFuture<InnerResultT>::FState>();
		auto CapturedState = State;
		UE::Tasks::Launch(UE_SOURCE_LOCATION,
			[Cb = Forward<Func>(Callback), CapturedState, OuterState]() mutable
			{
				if (CapturedState->Result.bIsError)
				{
					OuterState->Resolve(InnerResultT{{}, CapturedState->Result.Error, true});
					return;
				}
				Ret Inner = Cb(CapturedState->Result.Value);
				auto InnerState = Inner.State;
				UE::Tasks::Launch(UE_SOURCE_LOCATION,
					[InnerState, OuterState]()
					{
						OuterState->Resolve(MoveTemp(InnerState->Result));
					},
					InnerState->Event);
			},
			CapturedState->Event);
		State.Reset();
		return TNakamaFuture<InnerResultT>(OuterState);
	}

	/** Terminal Next: callback(ResultT) -> void */
	template<typename Func,
		typename Ret = std::invoke_result_t<std::decay_t<Func>, ResultT>,
		std::enable_if_t<!TIsTNakamaFuture<Ret>::value, int> = 0>
	void Next(Func&& Callback) && noexcept
	{
		auto CapturedState = State;
		UE::Tasks::Launch(UE_SOURCE_LOCATION,
			[Cb = Forward<Func>(Callback), CapturedState]() mutable
			{
				Cb(MoveTemp(CapturedState->Result));
			},
			CapturedState->Event);
		State.Reset();
	}
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
	NAKAMA_API float CalculateBackoff(int32 Attempt, const FNakamaRetryConfig& Config) noexcept;

	/** Add friends by ID or username to a user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> AddFriends(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		FString Metadata,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Add friends by ID or username to a user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> AddFriends(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		FString Metadata,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Add users to a group. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> AddGroupUsers(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString GroupId,
		const TArray<FString>& UserIds,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Add users to a group. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> AddGroupUsers(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString GroupId,
		const TArray<FString>& UserIds,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Refresh a user's session using a refresh token retrieved from a previous authentication request. */
	NAKAMA_API TNakamaFuture<FNakamaSessionResult> SessionRefresh(
		const FNakamaClientConfig& ClientConfig,
		FString Token,
		const TMap<FString, FString>& Vars,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Log out a session, invalidate a refresh token, or log out all sessions/refresh tokens for a user. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> SessionLogout(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString Token,
		FString RefreshToken,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Log out a session, invalidate a refresh token, or log out all sessions/refresh tokens for a user. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> SessionLogout(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString Token,
		FString RefreshToken,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Authenticate a user with an Apple ID against the server. */
	NAKAMA_API TNakamaFuture<FNakamaSessionResult> AuthenticateApple(
		const FNakamaClientConfig& ClientConfig,
		FNakamaAccountApple Account,
		bool Create,
		FString Username,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Authenticate a user with a custom id against the server. */
	NAKAMA_API TNakamaFuture<FNakamaSessionResult> AuthenticateCustom(
		const FNakamaClientConfig& ClientConfig,
		FNakamaAccountCustom Account,
		bool Create,
		FString Username,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Authenticate a user with a device id against the server. */
	NAKAMA_API TNakamaFuture<FNakamaSessionResult> AuthenticateDevice(
		const FNakamaClientConfig& ClientConfig,
		FNakamaAccountDevice Account,
		bool Create,
		FString Username,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Authenticate a user with an email+password against the server. */
	NAKAMA_API TNakamaFuture<FNakamaSessionResult> AuthenticateEmail(
		const FNakamaClientConfig& ClientConfig,
		FNakamaAccountEmail Account,
		bool Create,
		FString Username,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Authenticate a user with a Facebook OAuth token against the server. */
	NAKAMA_API TNakamaFuture<FNakamaSessionResult> AuthenticateFacebook(
		const FNakamaClientConfig& ClientConfig,
		FNakamaAccountFacebook Account,
		bool Create,
		FString Username,
		bool Sync,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Authenticate a user with a Facebook Instant Game token against the server. */
	NAKAMA_API TNakamaFuture<FNakamaSessionResult> AuthenticateFacebookInstantGame(
		const FNakamaClientConfig& ClientConfig,
		FNakamaAccountFacebookInstantGame Account,
		bool Create,
		FString Username,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Authenticate a user with Apple's GameCenter against the server. */
	NAKAMA_API TNakamaFuture<FNakamaSessionResult> AuthenticateGameCenter(
		const FNakamaClientConfig& ClientConfig,
		FNakamaAccountGameCenter Account,
		bool Create,
		FString Username,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Authenticate a user with Google against the server. */
	NAKAMA_API TNakamaFuture<FNakamaSessionResult> AuthenticateGoogle(
		const FNakamaClientConfig& ClientConfig,
		FNakamaAccountGoogle Account,
		bool Create,
		FString Username,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Authenticate a user with Steam against the server. */
	NAKAMA_API TNakamaFuture<FNakamaSessionResult> AuthenticateSteam(
		const FNakamaClientConfig& ClientConfig,
		FNakamaAccountSteam Account,
		bool Create,
		FString Username,
		bool Sync,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Ban a set of users from a group. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> BanGroupUsers(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString GroupId,
		const TArray<FString>& UserIds,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Ban a set of users from a group. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> BanGroupUsers(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString GroupId,
		const TArray<FString>& UserIds,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Block one or more users by ID or username. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> BlockFriends(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Block one or more users by ID or username. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> BlockFriends(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Create a new group with the current user as the owner. */
	NAKAMA_API TNakamaFuture<FNakamaGroupResult> CreateGroup(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString Name,
		FString Description,
		FString LangTag,
		FString AvatarUrl,
		bool Open,
		int32 MaxCount,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Create a new group with the current user as the owner. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaGroupResult> CreateGroup(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString Name,
		FString Description,
		FString LangTag,
		FString AvatarUrl,
		bool Open,
		int32 MaxCount,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Delete the current user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> DeleteAccount(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Delete the current user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> DeleteAccount(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Delete one or more users by ID or username. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> DeleteFriends(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Delete one or more users by ID or username. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> DeleteFriends(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Delete a group by ID. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> DeleteGroup(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString GroupId,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Delete a group by ID. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> DeleteGroup(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString GroupId,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Delete a leaderboard record. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> DeleteLeaderboardRecord(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString LeaderboardId,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Delete a leaderboard record. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> DeleteLeaderboardRecord(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString LeaderboardId,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Delete one or more notifications for the current user. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> DeleteNotifications(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		const TArray<FString>& Ids,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Delete one or more notifications for the current user. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> DeleteNotifications(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		const TArray<FString>& Ids,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Delete a tournament record. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> DeleteTournamentRecord(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString TournamentId,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Delete a tournament record. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> DeleteTournamentRecord(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString TournamentId,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Delete one or more objects by ID or username. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> DeleteStorageObjects(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		const TArray<FNakamaDeleteStorageObjectId>& ObjectIds,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Delete one or more objects by ID or username. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> DeleteStorageObjects(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		const TArray<FNakamaDeleteStorageObjectId>& ObjectIds,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Submit an event for processing in the server's registered runtime custom events handler. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> Event(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString Name,
		FString Timestamp,
		bool External,
		const TMap<FString, FString>& Properties,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Submit an event for processing in the server's registered runtime custom events handler. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> Event(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString Name,
		FString Timestamp,
		bool External,
		const TMap<FString, FString>& Properties,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Fetch the current user's account. */
	NAKAMA_API TNakamaFuture<FNakamaAccountResult> GetAccount(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Fetch the current user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaAccountResult> GetAccount(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Fetch zero or more users by ID and/or username. */
	NAKAMA_API TNakamaFuture<FNakamaUsersResult> GetUsers(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		const TArray<FString>& FacebookIds,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Fetch zero or more users by ID and/or username. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaUsersResult> GetUsers(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		const TArray<FString>& FacebookIds,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Get subscription by product id. */
	NAKAMA_API TNakamaFuture<FNakamaValidatedSubscriptionResult> GetSubscription(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString ProductId,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Get subscription by product id. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaValidatedSubscriptionResult> GetSubscription(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString ProductId,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Get matchmaker stats. */
	NAKAMA_API TNakamaFuture<FNakamaMatchmakerStatsResult> GetMatchmakerStats(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Get matchmaker stats. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaMatchmakerStatsResult> GetMatchmakerStats(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** A healthcheck which load balancers can use to check the service. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> Healthcheck(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** A healthcheck which load balancers can use to check the service. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> Healthcheck(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Import Facebook friends and add them to a user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> ImportFacebookFriends(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FNakamaAccountFacebook Account,
		bool Reset,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Import Facebook friends and add them to a user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> ImportFacebookFriends(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FNakamaAccountFacebook Account,
		bool Reset,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Import Steam friends and add them to a user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> ImportSteamFriends(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FNakamaAccountSteam Account,
		bool Reset,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Import Steam friends and add them to a user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> ImportSteamFriends(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FNakamaAccountSteam Account,
		bool Reset,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Immediately join an open group, or request to join a closed one. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> JoinGroup(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString GroupId,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Immediately join an open group, or request to join a closed one. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> JoinGroup(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString GroupId,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Attempt to join an open and running tournament. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> JoinTournament(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString TournamentId,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Attempt to join an open and running tournament. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> JoinTournament(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString TournamentId,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Kick a set of users from a group. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> KickGroupUsers(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString GroupId,
		const TArray<FString>& UserIds,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Kick a set of users from a group. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> KickGroupUsers(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString GroupId,
		const TArray<FString>& UserIds,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Leave a group the user is a member of. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> LeaveGroup(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString GroupId,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Leave a group the user is a member of. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> LeaveGroup(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString GroupId,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Add an Apple ID to the social profiles on the current user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkApple(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString Token,
		const TMap<FString, FString>& Vars,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Add an Apple ID to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkApple(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString Token,
		const TMap<FString, FString>& Vars,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Add a custom ID to the social profiles on the current user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkCustom(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString Id,
		const TMap<FString, FString>& Vars,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Add a custom ID to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkCustom(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString Id,
		const TMap<FString, FString>& Vars,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Add a device ID to the social profiles on the current user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkDevice(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString Id,
		const TMap<FString, FString>& Vars,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Add a device ID to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkDevice(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString Id,
		const TMap<FString, FString>& Vars,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Add an email+password to the social profiles on the current user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkEmail(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString Email,
		FString Password,
		const TMap<FString, FString>& Vars,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Add an email+password to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkEmail(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString Email,
		FString Password,
		const TMap<FString, FString>& Vars,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Add Facebook to the social profiles on the current user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkFacebook(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FNakamaAccountFacebook Account,
		bool Sync,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Add Facebook to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkFacebook(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FNakamaAccountFacebook Account,
		bool Sync,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Add Facebook Instant Game to the social profiles on the current user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkFacebookInstantGame(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString SignedPlayerInfo,
		const TMap<FString, FString>& Vars,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Add Facebook Instant Game to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkFacebookInstantGame(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString SignedPlayerInfo,
		const TMap<FString, FString>& Vars,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Add Apple's GameCenter to the social profiles on the current user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkGameCenter(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString PlayerId,
		FString BundleId,
		int64 TimestampSeconds,
		FString Salt,
		FString Signature,
		FString PublicKeyUrl,
		const TMap<FString, FString>& Vars,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Add Apple's GameCenter to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkGameCenter(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString PlayerId,
		FString BundleId,
		int64 TimestampSeconds,
		FString Salt,
		FString Signature,
		FString PublicKeyUrl,
		const TMap<FString, FString>& Vars,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Add Google to the social profiles on the current user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkGoogle(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString Token,
		const TMap<FString, FString>& Vars,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Add Google to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkGoogle(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString Token,
		const TMap<FString, FString>& Vars,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Add Steam to the social profiles on the current user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkSteam(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FNakamaAccountSteam Account,
		bool Sync,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Add Steam to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> LinkSteam(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FNakamaAccountSteam Account,
		bool Sync,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** List a channel's message history. */
	NAKAMA_API TNakamaFuture<FNakamaChannelMessageListResult> ListChannelMessages(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString ChannelId,
		int32 Limit,
		bool Forward,
		FString Cursor,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** List a channel's message history. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaChannelMessageListResult> ListChannelMessages(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString ChannelId,
		int32 Limit,
		bool Forward,
		FString Cursor,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** List all friends for the current user. */
	NAKAMA_API TNakamaFuture<FNakamaFriendListResult> ListFriends(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		int32 Limit,
		int32 State,
		FString Cursor,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** List all friends for the current user. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaFriendListResult> ListFriends(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		int32 Limit,
		int32 State,
		FString Cursor,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** List friends of friends for the current user. */
	NAKAMA_API TNakamaFuture<FNakamaFriendsOfFriendsListResult> ListFriendsOfFriends(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		int32 Limit,
		FString Cursor,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** List friends of friends for the current user. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaFriendsOfFriendsListResult> ListFriendsOfFriends(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		int32 Limit,
		FString Cursor,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** List groups based on given filters. */
	NAKAMA_API TNakamaFuture<FNakamaGroupListResult> ListGroups(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString Name,
		FString Cursor,
		int32 Limit,
		FString LangTag,
		int32 Members,
		bool Open,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** List groups based on given filters. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaGroupListResult> ListGroups(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString Name,
		FString Cursor,
		int32 Limit,
		FString LangTag,
		int32 Members,
		bool Open,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** List all users that are part of a group. */
	NAKAMA_API TNakamaFuture<FNakamaGroupUserListResult> ListGroupUsers(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString GroupId,
		int32 Limit,
		int32 State,
		FString Cursor,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** List all users that are part of a group. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaGroupUserListResult> ListGroupUsers(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString GroupId,
		int32 Limit,
		int32 State,
		FString Cursor,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** List leaderboard records. */
	NAKAMA_API TNakamaFuture<FNakamaLeaderboardRecordListResult> ListLeaderboardRecords(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString LeaderboardId,
		const TArray<FString>& OwnerIds,
		int32 Limit,
		FString Cursor,
		int64 Expiry,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** List leaderboard records. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaLeaderboardRecordListResult> ListLeaderboardRecords(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString LeaderboardId,
		const TArray<FString>& OwnerIds,
		int32 Limit,
		FString Cursor,
		int64 Expiry,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** List leaderboard records around the target ownerId. */
	NAKAMA_API TNakamaFuture<FNakamaLeaderboardRecordListResult> ListLeaderboardRecordsAroundOwner(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString LeaderboardId,
		int32 Limit,
		FString OwnerId,
		int64 Expiry,
		FString Cursor,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** List leaderboard records around the target ownerId. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaLeaderboardRecordListResult> ListLeaderboardRecordsAroundOwner(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString LeaderboardId,
		int32 Limit,
		FString OwnerId,
		int64 Expiry,
		FString Cursor,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** List running matches and optionally filter by matching criteria. */
	NAKAMA_API TNakamaFuture<FNakamaMatchListResult> ListMatches(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		int32 Limit,
		bool Authoritative,
		FString Label,
		int32 MinSize,
		int32 MaxSize,
		FString Query,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** List running matches and optionally filter by matching criteria. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaMatchListResult> ListMatches(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		int32 Limit,
		bool Authoritative,
		FString Label,
		int32 MinSize,
		int32 MaxSize,
		FString Query,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** List parties and optionally filter by matching criteria. */
	NAKAMA_API TNakamaFuture<FNakamaPartyListResult> ListParties(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		int32 Limit,
		bool Open,
		FString Query,
		FString Cursor,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** List parties and optionally filter by matching criteria. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaPartyListResult> ListParties(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		int32 Limit,
		bool Open,
		FString Query,
		FString Cursor,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Fetch list of notifications. */
	NAKAMA_API TNakamaFuture<FNakamaNotificationListResult> ListNotifications(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		int32 Limit,
		FString CacheableCursor,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Fetch list of notifications. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaNotificationListResult> ListNotifications(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		int32 Limit,
		FString CacheableCursor,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** List publicly readable storage objects in a given collection. */
	NAKAMA_API TNakamaFuture<FNakamaStorageObjectListResult> ListStorageObjects(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString UserId,
		FString Collection,
		int32 Limit,
		FString Cursor,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** List publicly readable storage objects in a given collection. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaStorageObjectListResult> ListStorageObjects(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString UserId,
		FString Collection,
		int32 Limit,
		FString Cursor,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** List user's subscriptions. */
	NAKAMA_API TNakamaFuture<FNakamaSubscriptionListResult> ListSubscriptions(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		int32 Limit,
		FString Cursor,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** List user's subscriptions. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaSubscriptionListResult> ListSubscriptions(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		int32 Limit,
		FString Cursor,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** List current or upcoming tournaments. */
	NAKAMA_API TNakamaFuture<FNakamaTournamentListResult> ListTournaments(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		int32 CategoryStart,
		int32 CategoryEnd,
		int32 StartTime,
		int32 EndTime,
		int32 Limit,
		FString Cursor,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** List current or upcoming tournaments. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaTournamentListResult> ListTournaments(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		int32 CategoryStart,
		int32 CategoryEnd,
		int32 StartTime,
		int32 EndTime,
		int32 Limit,
		FString Cursor,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** List tournament records. */
	NAKAMA_API TNakamaFuture<FNakamaTournamentRecordListResult> ListTournamentRecords(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString TournamentId,
		const TArray<FString>& OwnerIds,
		int32 Limit,
		FString Cursor,
		int64 Expiry,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** List tournament records. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaTournamentRecordListResult> ListTournamentRecords(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString TournamentId,
		const TArray<FString>& OwnerIds,
		int32 Limit,
		FString Cursor,
		int64 Expiry,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** List tournament records for a given owner. */
	NAKAMA_API TNakamaFuture<FNakamaTournamentRecordListResult> ListTournamentRecordsAroundOwner(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString TournamentId,
		int32 Limit,
		FString OwnerId,
		int64 Expiry,
		FString Cursor,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** List tournament records for a given owner. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaTournamentRecordListResult> ListTournamentRecordsAroundOwner(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString TournamentId,
		int32 Limit,
		FString OwnerId,
		int64 Expiry,
		FString Cursor,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** List groups the current user belongs to. */
	NAKAMA_API TNakamaFuture<FNakamaUserGroupListResult> ListUserGroups(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString UserId,
		int32 Limit,
		int32 State,
		FString Cursor,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** List groups the current user belongs to. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaUserGroupListResult> ListUserGroups(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString UserId,
		int32 Limit,
		int32 State,
		FString Cursor,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Promote a set of users in a group to the next role up. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> PromoteGroupUsers(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString GroupId,
		const TArray<FString>& UserIds,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Promote a set of users in a group to the next role up. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> PromoteGroupUsers(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString GroupId,
		const TArray<FString>& UserIds,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Demote a set of users in a group to the next role down. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> DemoteGroupUsers(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString GroupId,
		const TArray<FString>& UserIds,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Demote a set of users in a group to the next role down. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> DemoteGroupUsers(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString GroupId,
		const TArray<FString>& UserIds,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Get storage objects. */
	NAKAMA_API TNakamaFuture<FNakamaStorageObjectsResult> ReadStorageObjects(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		const TArray<FNakamaReadStorageObjectId>& ObjectIds,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Get storage objects. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaStorageObjectsResult> ReadStorageObjects(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		const TArray<FNakamaReadStorageObjectId>& ObjectIds,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Execute a Lua function on the server. */
	NAKAMA_API TNakamaFuture<FNakamaRpcResult> RpcFunc(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString Id,
		TSharedPtr<FJsonObject> Payload,
		FString HttpKey,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Execute a Lua function on the server. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaRpcResult> RpcFunc(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString Id,
		TSharedPtr<FJsonObject> Payload,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Remove the Apple ID from the social profiles on the current user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkApple(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString Token,
		const TMap<FString, FString>& Vars,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Remove the Apple ID from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkApple(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString Token,
		const TMap<FString, FString>& Vars,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Remove the custom ID from the social profiles on the current user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkCustom(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString Id,
		const TMap<FString, FString>& Vars,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Remove the custom ID from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkCustom(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString Id,
		const TMap<FString, FString>& Vars,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Remove the device ID from the social profiles on the current user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkDevice(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString Id,
		const TMap<FString, FString>& Vars,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Remove the device ID from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkDevice(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString Id,
		const TMap<FString, FString>& Vars,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Remove the email+password from the social profiles on the current user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkEmail(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString Email,
		FString Password,
		const TMap<FString, FString>& Vars,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Remove the email+password from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkEmail(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString Email,
		FString Password,
		const TMap<FString, FString>& Vars,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Remove Facebook from the social profiles on the current user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkFacebook(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString Token,
		const TMap<FString, FString>& Vars,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Remove Facebook from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkFacebook(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString Token,
		const TMap<FString, FString>& Vars,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Remove Facebook Instant Game profile from the social profiles on the current user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkFacebookInstantGame(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString SignedPlayerInfo,
		const TMap<FString, FString>& Vars,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Remove Facebook Instant Game profile from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkFacebookInstantGame(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString SignedPlayerInfo,
		const TMap<FString, FString>& Vars,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Remove Apple's GameCenter from the social profiles on the current user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkGameCenter(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString PlayerId,
		FString BundleId,
		int64 TimestampSeconds,
		FString Salt,
		FString Signature,
		FString PublicKeyUrl,
		const TMap<FString, FString>& Vars,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Remove Apple's GameCenter from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkGameCenter(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString PlayerId,
		FString BundleId,
		int64 TimestampSeconds,
		FString Salt,
		FString Signature,
		FString PublicKeyUrl,
		const TMap<FString, FString>& Vars,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Remove Google from the social profiles on the current user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkGoogle(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString Token,
		const TMap<FString, FString>& Vars,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Remove Google from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkGoogle(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString Token,
		const TMap<FString, FString>& Vars,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Remove Steam from the social profiles on the current user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkSteam(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString Token,
		const TMap<FString, FString>& Vars,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Remove Steam from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UnlinkSteam(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString Token,
		const TMap<FString, FString>& Vars,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Update fields in the current user's account. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UpdateAccount(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString Username,
		FString DisplayName,
		FString AvatarUrl,
		FString LangTag,
		FString Location,
		FString Timezone,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Update fields in the current user's account. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UpdateAccount(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString Username,
		FString DisplayName,
		FString AvatarUrl,
		FString LangTag,
		FString Location,
		FString Timezone,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Update fields in a given group. */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UpdateGroup(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString GroupId,
		FString Name,
		FString Description,
		FString LangTag,
		FString AvatarUrl,
		bool Open,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Update fields in a given group. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaVoidResult> UpdateGroup(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString GroupId,
		FString Name,
		FString Description,
		FString LangTag,
		FString AvatarUrl,
		bool Open,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Validate Apple IAP Receipt */
	NAKAMA_API TNakamaFuture<FNakamaValidatePurchaseResponseResult> ValidatePurchaseApple(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString Receipt,
		bool Persist,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Validate Apple IAP Receipt (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaValidatePurchaseResponseResult> ValidatePurchaseApple(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString Receipt,
		bool Persist,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Validate Apple Subscription Receipt */
	NAKAMA_API TNakamaFuture<FNakamaValidateSubscriptionResponseResult> ValidateSubscriptionApple(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString Receipt,
		bool Persist,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Validate Apple Subscription Receipt (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaValidateSubscriptionResponseResult> ValidateSubscriptionApple(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString Receipt,
		bool Persist,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Validate Google IAP Receipt */
	NAKAMA_API TNakamaFuture<FNakamaValidatePurchaseResponseResult> ValidatePurchaseGoogle(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString Purchase,
		bool Persist,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Validate Google IAP Receipt (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaValidatePurchaseResponseResult> ValidatePurchaseGoogle(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString Purchase,
		bool Persist,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Validate Google Subscription Receipt */
	NAKAMA_API TNakamaFuture<FNakamaValidateSubscriptionResponseResult> ValidateSubscriptionGoogle(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString Receipt,
		bool Persist,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Validate Google Subscription Receipt (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaValidateSubscriptionResponseResult> ValidateSubscriptionGoogle(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString Receipt,
		bool Persist,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Validate Huawei IAP Receipt */
	NAKAMA_API TNakamaFuture<FNakamaValidatePurchaseResponseResult> ValidatePurchaseHuawei(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString Purchase,
		FString Signature,
		bool Persist,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Validate Huawei IAP Receipt (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaValidatePurchaseResponseResult> ValidatePurchaseHuawei(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString Purchase,
		FString Signature,
		bool Persist,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Validate FB Instant IAP Receipt */
	NAKAMA_API TNakamaFuture<FNakamaValidatePurchaseResponseResult> ValidatePurchaseFacebookInstant(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString SignedRequest,
		bool Persist,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Validate FB Instant IAP Receipt (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaValidatePurchaseResponseResult> ValidatePurchaseFacebookInstant(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString SignedRequest,
		bool Persist,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Write a record to a leaderboard. */
	NAKAMA_API TNakamaFuture<FNakamaLeaderboardRecordResult> WriteLeaderboardRecord(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString LeaderboardId,
		FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite Record,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Write a record to a leaderboard. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaLeaderboardRecordResult> WriteLeaderboardRecord(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString LeaderboardId,
		FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite Record,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Write objects into the storage engine. */
	NAKAMA_API TNakamaFuture<FNakamaStorageObjectAcksResult> WriteStorageObjects(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		const TArray<FNakamaWriteStorageObject>& Objects,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Write objects into the storage engine. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaStorageObjectAcksResult> WriteStorageObjects(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		const TArray<FNakamaWriteStorageObject>& Objects,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Write a record to a tournament. */
	NAKAMA_API TNakamaFuture<FNakamaLeaderboardRecordResult> WriteTournamentRecord(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaSession& Session,
		FString TournamentId,
		FNakamaWriteTournamentRecordRequest_TournamentRecordWrite Record,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Write a record to a tournament. (Server-to-server with HTTP key) */
	NAKAMA_API TNakamaFuture<FNakamaLeaderboardRecordResult> WriteTournamentRecord(
		const FNakamaClientConfig& ClientConfig,
		const FString& HttpKey,
		FString TournamentId,
		FNakamaWriteTournamentRecordRequest_TournamentRecordWrite Record,
		const FNakamaRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;
}
