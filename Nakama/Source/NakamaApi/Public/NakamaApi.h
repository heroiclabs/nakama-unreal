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
#include "Templates/SharedPointer.h"
#include "Dom/JsonObject.h"
#include "HAL/ThreadSafeBool.h"
#include "NakamaTypes.h"

#include "NakamaApi.generated.h"

NAKAMAAPI_API DECLARE_LOG_CATEGORY_EXTERN(LogNakama, Log, All);

/** The friendship status. */
UENUM(BlueprintType)
enum class ENakamaFriend_State : uint8
{
	FRIEND = 0,
	INVITE_SENT = 1,
	INVITE_RECEIVED = 2,
	BLOCKED = 3
};

/** The group role status. */
UENUM(BlueprintType)
enum class ENakamaGroupUserList_GroupUser_State : uint8
{
	SUPERADMIN = 0,
	ADMIN = 1,
	MEMBER = 2,
	JOIN_REQUEST = 3
};

/** The group role status. */
UENUM(BlueprintType)
enum class ENakamaUserGroupList_UserGroup_State : uint8
{
	SUPERADMIN = 0,
	ADMIN = 1,
	MEMBER = 2,
	JOIN_REQUEST = 3
};

/** Validation Provider, */
UENUM(BlueprintType)
enum class ENakamaStoreProvider : uint8
{
	APPLE_APP_STORE = 0,
	GOOGLE_PLAY_STORE = 1,
	HUAWEI_APP_GALLERY = 2,
	FACEBOOK_INSTANT_STORE = 3
};

/** Environment where a purchase/subscription took place, */
UENUM(BlueprintType)
enum class ENakamaStoreEnvironment : uint8
{
	UNKNOWN = 0,
	SANDBOX = 1,
	PRODUCTION = 2
};

/** Operator that can be used to override the one set in the leaderboard. */
UENUM(BlueprintType)
enum class ENakamaOperator : uint8
{
	NO_OVERRIDE = 0,
	BEST = 1,
	SET = 2,
	INCREMENT = 3,
	DECREMENT = 4
};

USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaError
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Message;

	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 Code = 0;
};
/** gRPC status codes returned by Nakama in FNakamaError::Code. */
namespace NakamaErrorCode
{
	constexpr int32 OK = 0;
	constexpr int32 Cancelled = 1;
	constexpr int32 Unknown = 2;
	constexpr int32 InvalidArgument = 3;
	constexpr int32 DeadlineExceeded = 4;
	constexpr int32 NotFound = 5;
	constexpr int32 AlreadyExists = 6;
	constexpr int32 PermissionDenied = 7;
	constexpr int32 ResourceExhausted = 8;
	constexpr int32 FailedPrecondition = 9;
	constexpr int32 Aborted = 10;
	constexpr int32 OutOfRange = 11;
	constexpr int32 Unimplemented = 12;
	constexpr int32 Internal = 13;
	constexpr int32 Unavailable = 14;
	constexpr int32 DataLoss = 15;
	constexpr int32 Unauthenticated = 16;
}

struct NAKAMAAPI_API FNakamaCancellationToken
{
	void Cancel() { bCancelled.Store(true); }
	bool IsCancelled() const { return bCancelled.Load(); }
	static TSharedPtr<FNakamaCancellationToken> Create() { return MakeShared<FNakamaCancellationToken>(); }
private:
	TAtomic<bool> bCancelled{false};
};
using FNakamaCancellationTokenPtr = TSharedPtr<FNakamaCancellationToken>;

enum class ENakamaRequestAuth : uint8
{
	None,
	Basic,
	Bearer,
	HttpKey
};

/** Low-level API client configuration. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaApiConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nakama")
	FString ServerKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nakama")
	FString Host;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nakama")
	int32 Port = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nakama")
	bool bUseSSL = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nakama")
	float Timeout = 10.0f;

	FString GetBaseUrl() const noexcept;
};

/** Low-level Nakama API: data types + free functions for HTTP RPCs (callback-based). */
namespace NakamaApi
{

	/** Add friends by ID or username to a user's account. */
	NAKAMAAPI_API void AddFriends(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		FString Metadata,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add friends by ID or username to a user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void AddFriends(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		const TArray<FString>& Ids,

		const TArray<FString>& Usernames,

		FString Metadata,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add users to a group. */
	NAKAMAAPI_API void AddGroupUsers(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString GroupId,
		const TArray<FString>& UserIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add users to a group. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void AddGroupUsers(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString GroupId,

		const TArray<FString>& UserIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Refresh a user's session using a refresh token retrieved from a previous authentication request. */
	NAKAMAAPI_API void SessionRefresh(
		const FNakamaApiConfig& Config,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void(const FNakamaSession&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Log out a session, invalidate a refresh token, or log out all sessions/refresh tokens for a user. */
	NAKAMAAPI_API void SessionLogout(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Token,
		FString RefreshToken,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Log out a session, invalidate a refresh token, or log out all sessions/refresh tokens for a user. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void SessionLogout(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString Token,

		FString RefreshToken,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Authenticate a user with an Apple ID against the server. */
	NAKAMAAPI_API void AuthenticateApple(
		const FNakamaApiConfig& Config,
		FNakamaAccountApple Account,
		bool Create,
		FString Username,
		TFunction<void(const FNakamaSession&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Authenticate a user with a custom id against the server. */
	NAKAMAAPI_API void AuthenticateCustom(
		const FNakamaApiConfig& Config,
		FNakamaAccountCustom Account,
		bool Create,
		FString Username,
		TFunction<void(const FNakamaSession&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Authenticate a user with a device id against the server. */
	NAKAMAAPI_API void AuthenticateDevice(
		const FNakamaApiConfig& Config,
		FNakamaAccountDevice Account,
		bool Create,
		FString Username,
		TFunction<void(const FNakamaSession&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Authenticate a user with an email+password against the server. */
	NAKAMAAPI_API void AuthenticateEmail(
		const FNakamaApiConfig& Config,
		FNakamaAccountEmail Account,
		bool Create,
		FString Username,
		TFunction<void(const FNakamaSession&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Authenticate a user with a Facebook OAuth token against the server. */
	NAKAMAAPI_API void AuthenticateFacebook(
		const FNakamaApiConfig& Config,
		FNakamaAccountFacebook Account,
		bool Create,
		FString Username,
		bool Sync,
		TFunction<void(const FNakamaSession&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Authenticate a user with a Facebook Instant Game token against the server. */
	NAKAMAAPI_API void AuthenticateFacebookInstantGame(
		const FNakamaApiConfig& Config,
		FNakamaAccountFacebookInstantGame Account,
		bool Create,
		FString Username,
		TFunction<void(const FNakamaSession&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Authenticate a user with Apple's GameCenter against the server. */
	NAKAMAAPI_API void AuthenticateGameCenter(
		const FNakamaApiConfig& Config,
		FNakamaAccountGameCenter Account,
		bool Create,
		FString Username,
		TFunction<void(const FNakamaSession&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Authenticate a user with Google against the server. */
	NAKAMAAPI_API void AuthenticateGoogle(
		const FNakamaApiConfig& Config,
		FNakamaAccountGoogle Account,
		bool Create,
		FString Username,
		TFunction<void(const FNakamaSession&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Authenticate a user with Steam against the server. */
	NAKAMAAPI_API void AuthenticateSteam(
		const FNakamaApiConfig& Config,
		FNakamaAccountSteam Account,
		bool Create,
		FString Username,
		bool Sync,
		TFunction<void(const FNakamaSession&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Ban a set of users from a group. */
	NAKAMAAPI_API void BanGroupUsers(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString GroupId,
		const TArray<FString>& UserIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Ban a set of users from a group. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void BanGroupUsers(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString GroupId,

		const TArray<FString>& UserIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Block one or more users by ID or username. */
	NAKAMAAPI_API void BlockFriends(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Block one or more users by ID or username. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void BlockFriends(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		const TArray<FString>& Ids,

		const TArray<FString>& Usernames,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Create a new group with the current user as the owner. */
	NAKAMAAPI_API void CreateGroup(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Name,
		FString Description,
		FString LangTag,
		FString AvatarUrl,
		bool Open,
		int32 MaxCount,
		TFunction<void(const FNakamaGroup&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Create a new group with the current user as the owner. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void CreateGroup(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString Name,

		FString Description,

		FString LangTag,

		FString AvatarUrl,

		bool Open,

		int32 MaxCount,
		TFunction<void(const FNakamaGroup&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete the current user's account. */
	NAKAMAAPI_API void DeleteAccount(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void DeleteAccount(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete one or more users by ID or username. */
	NAKAMAAPI_API void DeleteFriends(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete one or more users by ID or username. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void DeleteFriends(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		const TArray<FString>& Ids,

		const TArray<FString>& Usernames,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete a group by ID. */
	NAKAMAAPI_API void DeleteGroup(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString GroupId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete a group by ID. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void DeleteGroup(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString GroupId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete a leaderboard record. */
	NAKAMAAPI_API void DeleteLeaderboardRecord(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString LeaderboardId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete a leaderboard record. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void DeleteLeaderboardRecord(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString LeaderboardId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete one or more notifications for the current user. */
	NAKAMAAPI_API void DeleteNotifications(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		const TArray<FString>& Ids,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete one or more notifications for the current user. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void DeleteNotifications(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		const TArray<FString>& Ids,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete a tournament record. */
	NAKAMAAPI_API void DeleteTournamentRecord(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString TournamentId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete a tournament record. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void DeleteTournamentRecord(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString TournamentId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete one or more objects by ID or username. */
	NAKAMAAPI_API void DeleteStorageObjects(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		const TArray<FNakamaDeleteStorageObjectId>& ObjectIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete one or more objects by ID or username. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void DeleteStorageObjects(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		const TArray<FNakamaDeleteStorageObjectId>& ObjectIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Submit an event for processing in the server's registered runtime custom events handler. */
	NAKAMAAPI_API void Event(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Name,
		FString Timestamp,
		bool External,
		const TMap<FString, FString>& Properties,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Submit an event for processing in the server's registered runtime custom events handler. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void Event(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString Name,

		FString Timestamp,

		bool External,
		const TMap<FString, FString>& Properties,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Fetch the current user's account. */
	NAKAMAAPI_API void GetAccount(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		TFunction<void(const FNakamaAccount&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Fetch the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void GetAccount(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		TFunction<void(const FNakamaAccount&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Fetch zero or more users by ID and/or username. */
	NAKAMAAPI_API void GetUsers(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		const TArray<FString>& FacebookIds,
		TFunction<void(const FNakamaUsers&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Fetch zero or more users by ID and/or username. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void GetUsers(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		const TArray<FString>& Ids,

		const TArray<FString>& Usernames,

		const TArray<FString>& FacebookIds,
		TFunction<void(const FNakamaUsers&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Get subscription by product id. */
	NAKAMAAPI_API void GetSubscription(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString ProductId,
		TFunction<void(const FNakamaValidatedSubscription&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Get subscription by product id. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void GetSubscription(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString ProductId,
		TFunction<void(const FNakamaValidatedSubscription&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Get matchmaker stats. */
	NAKAMAAPI_API void GetMatchmakerStats(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		TFunction<void(const FNakamaMatchmakerStats&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Get matchmaker stats. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void GetMatchmakerStats(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		TFunction<void(const FNakamaMatchmakerStats&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** A healthcheck which load balancers can use to check the service. */
	NAKAMAAPI_API void Healthcheck(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** A healthcheck which load balancers can use to check the service. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void Healthcheck(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Import Facebook friends and add them to a user's account. */
	NAKAMAAPI_API void ImportFacebookFriends(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FNakamaAccountFacebook Account,
		bool Reset,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Import Facebook friends and add them to a user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ImportFacebookFriends(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FNakamaAccountFacebook Account,

		bool Reset,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Import Steam friends and add them to a user's account. */
	NAKAMAAPI_API void ImportSteamFriends(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FNakamaAccountSteam Account,
		bool Reset,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Import Steam friends and add them to a user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ImportSteamFriends(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FNakamaAccountSteam Account,

		bool Reset,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Immediately join an open group, or request to join a closed one. */
	NAKAMAAPI_API void JoinGroup(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString GroupId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Immediately join an open group, or request to join a closed one. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void JoinGroup(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString GroupId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Attempt to join an open and running tournament. */
	NAKAMAAPI_API void JoinTournament(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString TournamentId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Attempt to join an open and running tournament. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void JoinTournament(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString TournamentId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Kick a set of users from a group. */
	NAKAMAAPI_API void KickGroupUsers(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString GroupId,
		const TArray<FString>& UserIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Kick a set of users from a group. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void KickGroupUsers(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString GroupId,

		const TArray<FString>& UserIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Leave a group the user is a member of. */
	NAKAMAAPI_API void LeaveGroup(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString GroupId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Leave a group the user is a member of. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void LeaveGroup(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString GroupId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add an Apple ID to the social profiles on the current user's account. */
	NAKAMAAPI_API void LinkApple(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add an Apple ID to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void LinkApple(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add a custom ID to the social profiles on the current user's account. */
	NAKAMAAPI_API void LinkCustom(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Id,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add a custom ID to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void LinkCustom(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString Id,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add a device ID to the social profiles on the current user's account. */
	NAKAMAAPI_API void LinkDevice(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Id,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add a device ID to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void LinkDevice(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString Id,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add an email+password to the social profiles on the current user's account. */
	NAKAMAAPI_API void LinkEmail(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Email,
		FString Password,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add an email+password to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void LinkEmail(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString Email,

		FString Password,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add Facebook to the social profiles on the current user's account. */
	NAKAMAAPI_API void LinkFacebook(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FNakamaAccountFacebook Account,
		bool Sync,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add Facebook to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void LinkFacebook(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FNakamaAccountFacebook Account,

		bool Sync,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add Facebook Instant Game to the social profiles on the current user's account. */
	NAKAMAAPI_API void LinkFacebookInstantGame(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString SignedPlayerInfo,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add Facebook Instant Game to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void LinkFacebookInstantGame(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString SignedPlayerInfo,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add Apple's GameCenter to the social profiles on the current user's account. */
	NAKAMAAPI_API void LinkGameCenter(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString PlayerId,
		FString BundleId,
		int64 TimestampSeconds,
		FString Salt,
		FString Signature,
		FString PublicKeyUrl,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add Apple's GameCenter to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void LinkGameCenter(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString PlayerId,

		FString BundleId,

		int64 TimestampSeconds,

		FString Salt,

		FString Signature,

		FString PublicKeyUrl,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add Google to the social profiles on the current user's account. */
	NAKAMAAPI_API void LinkGoogle(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add Google to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void LinkGoogle(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add Steam to the social profiles on the current user's account. */
	NAKAMAAPI_API void LinkSteam(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FNakamaAccountSteam Account,
		bool Sync,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add Steam to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void LinkSteam(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FNakamaAccountSteam Account,

		bool Sync,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List a channel's message history. */
	NAKAMAAPI_API void ListChannelMessages(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString ChannelId,
		int32 Limit,
		bool Forward,
		FString Cursor,
		TFunction<void(const FNakamaChannelMessageList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List a channel's message history. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListChannelMessages(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString ChannelId,

		int32 Limit,

		bool Forward,

		FString Cursor,
		TFunction<void(const FNakamaChannelMessageList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List all friends for the current user. */
	NAKAMAAPI_API void ListFriends(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		int32 Limit,
		int32 State,
		FString Cursor,
		TFunction<void(const FNakamaFriendList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List all friends for the current user. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListFriends(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		int32 Limit,

		int32 State,

		FString Cursor,
		TFunction<void(const FNakamaFriendList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List friends of friends for the current user. */
	NAKAMAAPI_API void ListFriendsOfFriends(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		int32 Limit,
		FString Cursor,
		TFunction<void(const FNakamaFriendsOfFriendsList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List friends of friends for the current user. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListFriendsOfFriends(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		int32 Limit,

		FString Cursor,
		TFunction<void(const FNakamaFriendsOfFriendsList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List groups based on given filters. */
	NAKAMAAPI_API void ListGroups(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Name,
		FString Cursor,
		int32 Limit,
		FString LangTag,
		int32 Members,
		bool Open,
		TFunction<void(const FNakamaGroupList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List groups based on given filters. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListGroups(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString Name,

		FString Cursor,

		int32 Limit,

		FString LangTag,

		int32 Members,

		bool Open,
		TFunction<void(const FNakamaGroupList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List all users that are part of a group. */
	NAKAMAAPI_API void ListGroupUsers(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString GroupId,
		int32 Limit,
		int32 State,
		FString Cursor,
		TFunction<void(const FNakamaGroupUserList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List all users that are part of a group. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListGroupUsers(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString GroupId,

		int32 Limit,

		int32 State,

		FString Cursor,
		TFunction<void(const FNakamaGroupUserList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List leaderboard records. */
	NAKAMAAPI_API void ListLeaderboardRecords(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString LeaderboardId,
		const TArray<FString>& OwnerIds,
		int32 Limit,
		FString Cursor,
		int64 Expiry,
		TFunction<void(const FNakamaLeaderboardRecordList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List leaderboard records. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListLeaderboardRecords(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString LeaderboardId,

		const TArray<FString>& OwnerIds,

		int32 Limit,

		FString Cursor,

		int64 Expiry,
		TFunction<void(const FNakamaLeaderboardRecordList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List leaderboard records around the target ownerId. */
	NAKAMAAPI_API void ListLeaderboardRecordsAroundOwner(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString LeaderboardId,
		int32 Limit,
		FString OwnerId,
		int64 Expiry,
		FString Cursor,
		TFunction<void(const FNakamaLeaderboardRecordList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List leaderboard records around the target ownerId. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListLeaderboardRecordsAroundOwner(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString LeaderboardId,

		int32 Limit,

		FString OwnerId,

		int64 Expiry,

		FString Cursor,
		TFunction<void(const FNakamaLeaderboardRecordList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List running matches and optionally filter by matching criteria. */
	NAKAMAAPI_API void ListMatches(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		int32 Limit,
		bool Authoritative,
		FString Label,
		int32 MinSize,
		int32 MaxSize,
		FString Query,
		TFunction<void(const FNakamaMatchList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List running matches and optionally filter by matching criteria. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListMatches(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		int32 Limit,

		bool Authoritative,

		FString Label,

		int32 MinSize,

		int32 MaxSize,

		FString Query,
		TFunction<void(const FNakamaMatchList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List parties and optionally filter by matching criteria. */
	NAKAMAAPI_API void ListParties(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		int32 Limit,
		bool Open,
		FString Query,
		FString Cursor,
		TFunction<void(const FNakamaPartyList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List parties and optionally filter by matching criteria. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListParties(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		int32 Limit,

		bool Open,

		FString Query,

		FString Cursor,
		TFunction<void(const FNakamaPartyList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Fetch list of notifications. */
	NAKAMAAPI_API void ListNotifications(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		int32 Limit,
		FString CacheableCursor,
		TFunction<void(const FNakamaNotificationList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Fetch list of notifications. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListNotifications(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		int32 Limit,

		FString CacheableCursor,
		TFunction<void(const FNakamaNotificationList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List publicly readable storage objects in a given collection. */
	NAKAMAAPI_API void ListStorageObjects(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString UserId,
		FString Collection,
		int32 Limit,
		FString Cursor,
		TFunction<void(const FNakamaStorageObjectList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List publicly readable storage objects in a given collection. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListStorageObjects(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString UserId,

		FString Collection,

		int32 Limit,

		FString Cursor,
		TFunction<void(const FNakamaStorageObjectList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List user's subscriptions. */
	NAKAMAAPI_API void ListSubscriptions(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		int32 Limit,
		FString Cursor,
		TFunction<void(const FNakamaSubscriptionList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List user's subscriptions. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListSubscriptions(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		int32 Limit,

		FString Cursor,
		TFunction<void(const FNakamaSubscriptionList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List current or upcoming tournaments. */
	NAKAMAAPI_API void ListTournaments(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		int32 CategoryStart,
		int32 CategoryEnd,
		int32 StartTime,
		int32 EndTime,
		int32 Limit,
		FString Cursor,
		TFunction<void(const FNakamaTournamentList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List current or upcoming tournaments. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListTournaments(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		int32 CategoryStart,

		int32 CategoryEnd,

		int32 StartTime,

		int32 EndTime,

		int32 Limit,

		FString Cursor,
		TFunction<void(const FNakamaTournamentList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List tournament records. */
	NAKAMAAPI_API void ListTournamentRecords(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString TournamentId,
		const TArray<FString>& OwnerIds,
		int32 Limit,
		FString Cursor,
		int64 Expiry,
		TFunction<void(const FNakamaTournamentRecordList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List tournament records. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListTournamentRecords(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString TournamentId,

		const TArray<FString>& OwnerIds,

		int32 Limit,

		FString Cursor,

		int64 Expiry,
		TFunction<void(const FNakamaTournamentRecordList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List tournament records for a given owner. */
	NAKAMAAPI_API void ListTournamentRecordsAroundOwner(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString TournamentId,
		int32 Limit,
		FString OwnerId,
		int64 Expiry,
		FString Cursor,
		TFunction<void(const FNakamaTournamentRecordList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List tournament records for a given owner. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListTournamentRecordsAroundOwner(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString TournamentId,

		int32 Limit,

		FString OwnerId,

		int64 Expiry,

		FString Cursor,
		TFunction<void(const FNakamaTournamentRecordList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List groups the current user belongs to. */
	NAKAMAAPI_API void ListUserGroups(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString UserId,
		int32 Limit,
		int32 State,
		FString Cursor,
		TFunction<void(const FNakamaUserGroupList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List groups the current user belongs to. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListUserGroups(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString UserId,

		int32 Limit,

		int32 State,

		FString Cursor,
		TFunction<void(const FNakamaUserGroupList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Promote a set of users in a group to the next role up. */
	NAKAMAAPI_API void PromoteGroupUsers(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString GroupId,
		const TArray<FString>& UserIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Promote a set of users in a group to the next role up. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void PromoteGroupUsers(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString GroupId,

		const TArray<FString>& UserIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Demote a set of users in a group to the next role down. */
	NAKAMAAPI_API void DemoteGroupUsers(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString GroupId,
		const TArray<FString>& UserIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Demote a set of users in a group to the next role down. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void DemoteGroupUsers(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString GroupId,

		const TArray<FString>& UserIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Get storage objects. */
	NAKAMAAPI_API void ReadStorageObjects(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		const TArray<FNakamaReadStorageObjectId>& ObjectIds,
		TFunction<void(const FNakamaStorageObjects&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Get storage objects. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ReadStorageObjects(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		const TArray<FNakamaReadStorageObjectId>& ObjectIds,
		TFunction<void(const FNakamaStorageObjects&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Execute a Lua function on the server. */
	NAKAMAAPI_API void RpcFunc(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Id,
		TSharedPtr<FJsonObject> Payload,
		FString HttpKey,
		TFunction<void(const FNakamaRpc&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Execute a Lua function on the server. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void RpcFunc(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString Id,
		TSharedPtr<FJsonObject> Payload,
		TFunction<void(const FNakamaRpc&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove the Apple ID from the social profiles on the current user's account. */
	NAKAMAAPI_API void UnlinkApple(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove the Apple ID from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void UnlinkApple(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove the custom ID from the social profiles on the current user's account. */
	NAKAMAAPI_API void UnlinkCustom(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Id,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove the custom ID from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void UnlinkCustom(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString Id,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove the device ID from the social profiles on the current user's account. */
	NAKAMAAPI_API void UnlinkDevice(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Id,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove the device ID from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void UnlinkDevice(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString Id,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove the email+password from the social profiles on the current user's account. */
	NAKAMAAPI_API void UnlinkEmail(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Email,
		FString Password,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove the email+password from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void UnlinkEmail(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString Email,

		FString Password,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove Facebook from the social profiles on the current user's account. */
	NAKAMAAPI_API void UnlinkFacebook(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove Facebook from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void UnlinkFacebook(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove Facebook Instant Game profile from the social profiles on the current user's account. */
	NAKAMAAPI_API void UnlinkFacebookInstantGame(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString SignedPlayerInfo,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove Facebook Instant Game profile from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void UnlinkFacebookInstantGame(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString SignedPlayerInfo,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove Apple's GameCenter from the social profiles on the current user's account. */
	NAKAMAAPI_API void UnlinkGameCenter(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString PlayerId,
		FString BundleId,
		int64 TimestampSeconds,
		FString Salt,
		FString Signature,
		FString PublicKeyUrl,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove Apple's GameCenter from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void UnlinkGameCenter(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString PlayerId,

		FString BundleId,

		int64 TimestampSeconds,

		FString Salt,

		FString Signature,

		FString PublicKeyUrl,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove Google from the social profiles on the current user's account. */
	NAKAMAAPI_API void UnlinkGoogle(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove Google from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void UnlinkGoogle(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove Steam from the social profiles on the current user's account. */
	NAKAMAAPI_API void UnlinkSteam(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove Steam from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void UnlinkSteam(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Update fields in the current user's account. */
	NAKAMAAPI_API void UpdateAccount(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Username,
		FString DisplayName,
		FString AvatarUrl,
		FString LangTag,
		FString Location,
		FString Timezone,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Update fields in the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void UpdateAccount(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString Username,

		FString DisplayName,

		FString AvatarUrl,

		FString LangTag,

		FString Location,

		FString Timezone,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Update fields in a given group. */
	NAKAMAAPI_API void UpdateGroup(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString GroupId,
		FString Name,
		FString Description,
		FString LangTag,
		FString AvatarUrl,
		bool Open,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Update fields in a given group. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void UpdateGroup(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString GroupId,

		FString Name,

		FString Description,

		FString LangTag,

		FString AvatarUrl,

		bool Open,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Validate Apple IAP Receipt */
	NAKAMAAPI_API void ValidatePurchaseApple(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Receipt,
		bool Persist,
		TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Validate Apple IAP Receipt (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ValidatePurchaseApple(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString Receipt,

		bool Persist,
		TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Validate Apple Subscription Receipt */
	NAKAMAAPI_API void ValidateSubscriptionApple(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Receipt,
		bool Persist,
		TFunction<void(const FNakamaValidateSubscriptionResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Validate Apple Subscription Receipt (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ValidateSubscriptionApple(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString Receipt,

		bool Persist,
		TFunction<void(const FNakamaValidateSubscriptionResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Validate Google IAP Receipt */
	NAKAMAAPI_API void ValidatePurchaseGoogle(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Purchase,
		bool Persist,
		TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Validate Google IAP Receipt (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ValidatePurchaseGoogle(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString Purchase,

		bool Persist,
		TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Validate Google Subscription Receipt */
	NAKAMAAPI_API void ValidateSubscriptionGoogle(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Receipt,
		bool Persist,
		TFunction<void(const FNakamaValidateSubscriptionResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Validate Google Subscription Receipt (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ValidateSubscriptionGoogle(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString Receipt,

		bool Persist,
		TFunction<void(const FNakamaValidateSubscriptionResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Validate Huawei IAP Receipt */
	NAKAMAAPI_API void ValidatePurchaseHuawei(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Purchase,
		FString Signature,
		bool Persist,
		TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Validate Huawei IAP Receipt (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ValidatePurchaseHuawei(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString Purchase,

		FString Signature,

		bool Persist,
		TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Validate FB Instant IAP Receipt */
	NAKAMAAPI_API void ValidatePurchaseFacebookInstant(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString SignedRequest,
		bool Persist,
		TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Validate FB Instant IAP Receipt (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ValidatePurchaseFacebookInstant(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString SignedRequest,

		bool Persist,
		TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Write a record to a leaderboard. */
	NAKAMAAPI_API void WriteLeaderboardRecord(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString LeaderboardId,
		FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite Record,
		TFunction<void(const FNakamaLeaderboardRecord&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Write a record to a leaderboard. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void WriteLeaderboardRecord(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString LeaderboardId,

		FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite Record,
		TFunction<void(const FNakamaLeaderboardRecord&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Write objects into the storage engine. */
	NAKAMAAPI_API void WriteStorageObjects(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		const TArray<FNakamaWriteStorageObject>& Objects,
		TFunction<void(const FNakamaStorageObjectAcks&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Write objects into the storage engine. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void WriteStorageObjects(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		const TArray<FNakamaWriteStorageObject>& Objects,
		TFunction<void(const FNakamaStorageObjectAcks&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Write a record to a tournament. */
	NAKAMAAPI_API void WriteTournamentRecord(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString TournamentId,
		FNakamaWriteTournamentRecordRequest_TournamentRecordWrite Record,
		TFunction<void(const FNakamaLeaderboardRecord&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Write a record to a tournament. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void WriteTournamentRecord(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,

		FString TournamentId,

		FNakamaWriteTournamentRecordRequest_TournamentRecordWrite Record,
		TFunction<void(const FNakamaLeaderboardRecord&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;
}
