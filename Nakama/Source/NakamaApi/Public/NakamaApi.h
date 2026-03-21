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

#include <atomic>
#include "CoreMinimal.h"
#include "Templates/Function.h"
#include "Templates/SharedPointer.h"
#include "Dom/JsonObject.h"
#include "NakamaTypes.h"

NAKAMAAPI_API DECLARE_LOG_CATEGORY_EXTERN(LogNakama, Log, All);

/** Low-level Nakama API: data types + free functions for HTTP RPCs (callback-based). */
namespace NakamaApi
{

	/** Add friends by ID or username to a user's account. */
	NAKAMAAPI_API void AddFriends(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		FString Metadata,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Add friends by ID or username to a user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void AddFriends(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		FString Metadata,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Add users to a group. */
	NAKAMAAPI_API void AddGroupUsers(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString GroupId,
		const TArray<FString>& UserIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Add users to a group. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void AddGroupUsers(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString GroupId,
		const TArray<FString>& UserIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Refresh a user's session using a refresh token retrieved from a previous authentication request. */
	NAKAMAAPI_API void SessionRefresh(
		const FNakamaClientConfig& Config,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void(const FNakamaSession&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Log out a session, invalidate a refresh token, or log out all sessions/refresh tokens for a user. */
	NAKAMAAPI_API void SessionLogout(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString Token,
		FString RefreshToken,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Log out a session, invalidate a refresh token, or log out all sessions/refresh tokens for a user. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void SessionLogout(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString Token,
		FString RefreshToken,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Authenticate a user with an Apple ID against the server. */
	NAKAMAAPI_API void AuthenticateApple(
		const FNakamaClientConfig& Config,
		FNakamaAccountApple Account,
		bool Create,
		FString Username,
		TFunction<void(const FNakamaSession&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Authenticate a user with a custom id against the server. */
	NAKAMAAPI_API void AuthenticateCustom(
		const FNakamaClientConfig& Config,
		FNakamaAccountCustom Account,
		bool Create,
		FString Username,
		TFunction<void(const FNakamaSession&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Authenticate a user with a device id against the server. */
	NAKAMAAPI_API void AuthenticateDevice(
		const FNakamaClientConfig& Config,
		FNakamaAccountDevice Account,
		bool Create,
		FString Username,
		TFunction<void(const FNakamaSession&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Authenticate a user with an email+password against the server. */
	NAKAMAAPI_API void AuthenticateEmail(
		const FNakamaClientConfig& Config,
		FNakamaAccountEmail Account,
		bool Create,
		FString Username,
		TFunction<void(const FNakamaSession&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Authenticate a user with a Facebook OAuth token against the server. */
	NAKAMAAPI_API void AuthenticateFacebook(
		const FNakamaClientConfig& Config,
		FNakamaAccountFacebook Account,
		bool Create,
		FString Username,
		bool Sync,
		TFunction<void(const FNakamaSession&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Authenticate a user with a Facebook Instant Game token against the server. */
	NAKAMAAPI_API void AuthenticateFacebookInstantGame(
		const FNakamaClientConfig& Config,
		FNakamaAccountFacebookInstantGame Account,
		bool Create,
		FString Username,
		TFunction<void(const FNakamaSession&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Authenticate a user with Apple's GameCenter against the server. */
	NAKAMAAPI_API void AuthenticateGameCenter(
		const FNakamaClientConfig& Config,
		FNakamaAccountGameCenter Account,
		bool Create,
		FString Username,
		TFunction<void(const FNakamaSession&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Authenticate a user with Google against the server. */
	NAKAMAAPI_API void AuthenticateGoogle(
		const FNakamaClientConfig& Config,
		FNakamaAccountGoogle Account,
		bool Create,
		FString Username,
		TFunction<void(const FNakamaSession&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Authenticate a user with Steam against the server. */
	NAKAMAAPI_API void AuthenticateSteam(
		const FNakamaClientConfig& Config,
		FNakamaAccountSteam Account,
		bool Create,
		FString Username,
		bool Sync,
		TFunction<void(const FNakamaSession&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Ban a set of users from a group. */
	NAKAMAAPI_API void BanGroupUsers(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString GroupId,
		const TArray<FString>& UserIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Ban a set of users from a group. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void BanGroupUsers(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString GroupId,
		const TArray<FString>& UserIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Block one or more users by ID or username. */
	NAKAMAAPI_API void BlockFriends(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Block one or more users by ID or username. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void BlockFriends(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Create a new group with the current user as the owner. */
	NAKAMAAPI_API void CreateGroup(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString Name,
		FString Description,
		FString LangTag,
		FString AvatarUrl,
		bool Open,
		int32 MaxCount,
		TFunction<void(const FNakamaGroup&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Create a new group with the current user as the owner. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void CreateGroup(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString Name,
		FString Description,
		FString LangTag,
		FString AvatarUrl,
		bool Open,
		int32 MaxCount,
		TFunction<void(const FNakamaGroup&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Delete the current user's account. */
	NAKAMAAPI_API void DeleteAccount(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Delete the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void DeleteAccount(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Delete one or more users by ID or username. */
	NAKAMAAPI_API void DeleteFriends(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Delete one or more users by ID or username. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void DeleteFriends(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Delete a group by ID. */
	NAKAMAAPI_API void DeleteGroup(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString GroupId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Delete a group by ID. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void DeleteGroup(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString GroupId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Delete a leaderboard record. */
	NAKAMAAPI_API void DeleteLeaderboardRecord(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString LeaderboardId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Delete a leaderboard record. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void DeleteLeaderboardRecord(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString LeaderboardId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Delete one or more notifications for the current user. */
	NAKAMAAPI_API void DeleteNotifications(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		const TArray<FString>& Ids,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Delete one or more notifications for the current user. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void DeleteNotifications(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		const TArray<FString>& Ids,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Delete a tournament record. */
	NAKAMAAPI_API void DeleteTournamentRecord(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString TournamentId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Delete a tournament record. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void DeleteTournamentRecord(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString TournamentId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Delete one or more objects by ID or username. */
	NAKAMAAPI_API void DeleteStorageObjects(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		const TArray<FNakamaDeleteStorageObjectId>& ObjectIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Delete one or more objects by ID or username. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void DeleteStorageObjects(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		const TArray<FNakamaDeleteStorageObjectId>& ObjectIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Submit an event for processing in the server's registered runtime custom events handler. */
	NAKAMAAPI_API void Event(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString Name,
		FString Timestamp,
		bool External,
		const TMap<FString, FString>& Properties,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Submit an event for processing in the server's registered runtime custom events handler. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void Event(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString Name,
		FString Timestamp,
		bool External,
		const TMap<FString, FString>& Properties,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Fetch the current user's account. */
	NAKAMAAPI_API void GetAccount(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		TFunction<void(const FNakamaAccount&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Fetch the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void GetAccount(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		TFunction<void(const FNakamaAccount&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Fetch zero or more users by ID and/or username. */
	NAKAMAAPI_API void GetUsers(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		const TArray<FString>& FacebookIds,
		TFunction<void(const FNakamaUsers&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Fetch zero or more users by ID and/or username. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void GetUsers(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		const TArray<FString>& FacebookIds,
		TFunction<void(const FNakamaUsers&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Get subscription by product id. */
	NAKAMAAPI_API void GetSubscription(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString ProductId,
		TFunction<void(const FNakamaValidatedSubscription&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Get subscription by product id. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void GetSubscription(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString ProductId,
		TFunction<void(const FNakamaValidatedSubscription&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Get matchmaker stats. */
	NAKAMAAPI_API void GetMatchmakerStats(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		TFunction<void(const FNakamaMatchmakerStats&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Get matchmaker stats. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void GetMatchmakerStats(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		TFunction<void(const FNakamaMatchmakerStats&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** A healthcheck which load balancers can use to check the service. */
	NAKAMAAPI_API void Healthcheck(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** A healthcheck which load balancers can use to check the service. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void Healthcheck(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Import Facebook friends and add them to a user's account. */
	NAKAMAAPI_API void ImportFacebookFriends(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FNakamaAccountFacebook Account,
		bool Reset,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Import Facebook friends and add them to a user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ImportFacebookFriends(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FNakamaAccountFacebook Account,
		bool Reset,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Import Steam friends and add them to a user's account. */
	NAKAMAAPI_API void ImportSteamFriends(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FNakamaAccountSteam Account,
		bool Reset,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Import Steam friends and add them to a user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ImportSteamFriends(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FNakamaAccountSteam Account,
		bool Reset,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Immediately join an open group, or request to join a closed one. */
	NAKAMAAPI_API void JoinGroup(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString GroupId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Immediately join an open group, or request to join a closed one. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void JoinGroup(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString GroupId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Attempt to join an open and running tournament. */
	NAKAMAAPI_API void JoinTournament(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString TournamentId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Attempt to join an open and running tournament. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void JoinTournament(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString TournamentId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Kick a set of users from a group. */
	NAKAMAAPI_API void KickGroupUsers(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString GroupId,
		const TArray<FString>& UserIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Kick a set of users from a group. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void KickGroupUsers(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString GroupId,
		const TArray<FString>& UserIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Leave a group the user is a member of. */
	NAKAMAAPI_API void LeaveGroup(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString GroupId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Leave a group the user is a member of. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void LeaveGroup(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString GroupId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Add an Apple ID to the social profiles on the current user's account. */
	NAKAMAAPI_API void LinkApple(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Add an Apple ID to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void LinkApple(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Add a custom ID to the social profiles on the current user's account. */
	NAKAMAAPI_API void LinkCustom(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString Id,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Add a custom ID to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void LinkCustom(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString Id,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Add a device ID to the social profiles on the current user's account. */
	NAKAMAAPI_API void LinkDevice(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString Id,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Add a device ID to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void LinkDevice(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString Id,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Add an email+password to the social profiles on the current user's account. */
	NAKAMAAPI_API void LinkEmail(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString Email,
		FString Password,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Add an email+password to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void LinkEmail(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString Email,
		FString Password,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Add Facebook to the social profiles on the current user's account. */
	NAKAMAAPI_API void LinkFacebook(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FNakamaAccountFacebook Account,
		bool Sync,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Add Facebook to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void LinkFacebook(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FNakamaAccountFacebook Account,
		bool Sync,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Add Facebook Instant Game to the social profiles on the current user's account. */
	NAKAMAAPI_API void LinkFacebookInstantGame(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString SignedPlayerInfo,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Add Facebook Instant Game to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void LinkFacebookInstantGame(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString SignedPlayerInfo,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Add Apple's GameCenter to the social profiles on the current user's account. */
	NAKAMAAPI_API void LinkGameCenter(
		const FNakamaClientConfig& Config,
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
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Add Apple's GameCenter to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void LinkGameCenter(
		const FNakamaClientConfig& Config,
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
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Add Google to the social profiles on the current user's account. */
	NAKAMAAPI_API void LinkGoogle(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Add Google to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void LinkGoogle(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Add Steam to the social profiles on the current user's account. */
	NAKAMAAPI_API void LinkSteam(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FNakamaAccountSteam Account,
		bool Sync,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Add Steam to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void LinkSteam(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FNakamaAccountSteam Account,
		bool Sync,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** List a channel's message history. */
	NAKAMAAPI_API void ListChannelMessages(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString ChannelId,
		int32 Limit,
		bool Forward,
		FString Cursor,
		TFunction<void(const FNakamaChannelMessageList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** List a channel's message history. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListChannelMessages(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString ChannelId,
		int32 Limit,
		bool Forward,
		FString Cursor,
		TFunction<void(const FNakamaChannelMessageList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** List all friends for the current user. */
	NAKAMAAPI_API void ListFriends(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		int32 Limit,
		int32 State,
		FString Cursor,
		TFunction<void(const FNakamaFriendList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** List all friends for the current user. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListFriends(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		int32 Limit,
		int32 State,
		FString Cursor,
		TFunction<void(const FNakamaFriendList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** List friends of friends for the current user. */
	NAKAMAAPI_API void ListFriendsOfFriends(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		int32 Limit,
		FString Cursor,
		TFunction<void(const FNakamaFriendsOfFriendsList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** List friends of friends for the current user. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListFriendsOfFriends(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		int32 Limit,
		FString Cursor,
		TFunction<void(const FNakamaFriendsOfFriendsList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** List groups based on given filters. */
	NAKAMAAPI_API void ListGroups(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString Name,
		FString Cursor,
		int32 Limit,
		FString LangTag,
		int32 Members,
		bool Open,
		TFunction<void(const FNakamaGroupList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** List groups based on given filters. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListGroups(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString Name,
		FString Cursor,
		int32 Limit,
		FString LangTag,
		int32 Members,
		bool Open,
		TFunction<void(const FNakamaGroupList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** List all users that are part of a group. */
	NAKAMAAPI_API void ListGroupUsers(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString GroupId,
		int32 Limit,
		int32 State,
		FString Cursor,
		TFunction<void(const FNakamaGroupUserList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** List all users that are part of a group. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListGroupUsers(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString GroupId,
		int32 Limit,
		int32 State,
		FString Cursor,
		TFunction<void(const FNakamaGroupUserList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** List leaderboard records. */
	NAKAMAAPI_API void ListLeaderboardRecords(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString LeaderboardId,
		const TArray<FString>& OwnerIds,
		int32 Limit,
		FString Cursor,
		int64 Expiry,
		TFunction<void(const FNakamaLeaderboardRecordList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** List leaderboard records. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListLeaderboardRecords(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString LeaderboardId,
		const TArray<FString>& OwnerIds,
		int32 Limit,
		FString Cursor,
		int64 Expiry,
		TFunction<void(const FNakamaLeaderboardRecordList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** List leaderboard records around the target ownerId. */
	NAKAMAAPI_API void ListLeaderboardRecordsAroundOwner(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString LeaderboardId,
		int32 Limit,
		FString OwnerId,
		int64 Expiry,
		FString Cursor,
		TFunction<void(const FNakamaLeaderboardRecordList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** List leaderboard records around the target ownerId. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListLeaderboardRecordsAroundOwner(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString LeaderboardId,
		int32 Limit,
		FString OwnerId,
		int64 Expiry,
		FString Cursor,
		TFunction<void(const FNakamaLeaderboardRecordList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** List running matches and optionally filter by matching criteria. */
	NAKAMAAPI_API void ListMatches(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		int32 Limit,
		bool Authoritative,
		FString Label,
		int32 MinSize,
		int32 MaxSize,
		FString Query,
		TFunction<void(const FNakamaMatchList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** List running matches and optionally filter by matching criteria. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListMatches(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		int32 Limit,
		bool Authoritative,
		FString Label,
		int32 MinSize,
		int32 MaxSize,
		FString Query,
		TFunction<void(const FNakamaMatchList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** List parties and optionally filter by matching criteria. */
	NAKAMAAPI_API void ListParties(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		int32 Limit,
		bool Open,
		FString Query,
		FString Cursor,
		TFunction<void(const FNakamaPartyList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** List parties and optionally filter by matching criteria. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListParties(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		int32 Limit,
		bool Open,
		FString Query,
		FString Cursor,
		TFunction<void(const FNakamaPartyList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Fetch list of notifications. */
	NAKAMAAPI_API void ListNotifications(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		int32 Limit,
		FString CacheableCursor,
		TFunction<void(const FNakamaNotificationList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Fetch list of notifications. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListNotifications(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		int32 Limit,
		FString CacheableCursor,
		TFunction<void(const FNakamaNotificationList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** List publicly readable storage objects in a given collection. */
	NAKAMAAPI_API void ListStorageObjects(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString UserId,
		FString Collection,
		int32 Limit,
		FString Cursor,
		TFunction<void(const FNakamaStorageObjectList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** List publicly readable storage objects in a given collection. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListStorageObjects(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString UserId,
		FString Collection,
		int32 Limit,
		FString Cursor,
		TFunction<void(const FNakamaStorageObjectList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** List user's subscriptions. */
	NAKAMAAPI_API void ListSubscriptions(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		int32 Limit,
		FString Cursor,
		TFunction<void(const FNakamaSubscriptionList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** List user's subscriptions. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListSubscriptions(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		int32 Limit,
		FString Cursor,
		TFunction<void(const FNakamaSubscriptionList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** List current or upcoming tournaments. */
	NAKAMAAPI_API void ListTournaments(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		int32 CategoryStart,
		int32 CategoryEnd,
		int32 StartTime,
		int32 EndTime,
		int32 Limit,
		FString Cursor,
		TFunction<void(const FNakamaTournamentList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** List current or upcoming tournaments. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListTournaments(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		int32 CategoryStart,
		int32 CategoryEnd,
		int32 StartTime,
		int32 EndTime,
		int32 Limit,
		FString Cursor,
		TFunction<void(const FNakamaTournamentList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** List tournament records. */
	NAKAMAAPI_API void ListTournamentRecords(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString TournamentId,
		const TArray<FString>& OwnerIds,
		int32 Limit,
		FString Cursor,
		int64 Expiry,
		TFunction<void(const FNakamaTournamentRecordList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** List tournament records. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListTournamentRecords(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString TournamentId,
		const TArray<FString>& OwnerIds,
		int32 Limit,
		FString Cursor,
		int64 Expiry,
		TFunction<void(const FNakamaTournamentRecordList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** List tournament records for a given owner. */
	NAKAMAAPI_API void ListTournamentRecordsAroundOwner(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString TournamentId,
		int32 Limit,
		FString OwnerId,
		int64 Expiry,
		FString Cursor,
		TFunction<void(const FNakamaTournamentRecordList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** List tournament records for a given owner. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListTournamentRecordsAroundOwner(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString TournamentId,
		int32 Limit,
		FString OwnerId,
		int64 Expiry,
		FString Cursor,
		TFunction<void(const FNakamaTournamentRecordList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** List groups the current user belongs to. */
	NAKAMAAPI_API void ListUserGroups(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString UserId,
		int32 Limit,
		int32 State,
		FString Cursor,
		TFunction<void(const FNakamaUserGroupList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** List groups the current user belongs to. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListUserGroups(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString UserId,
		int32 Limit,
		int32 State,
		FString Cursor,
		TFunction<void(const FNakamaUserGroupList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Promote a set of users in a group to the next role up. */
	NAKAMAAPI_API void PromoteGroupUsers(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString GroupId,
		const TArray<FString>& UserIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Promote a set of users in a group to the next role up. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void PromoteGroupUsers(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString GroupId,
		const TArray<FString>& UserIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Demote a set of users in a group to the next role down. */
	NAKAMAAPI_API void DemoteGroupUsers(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString GroupId,
		const TArray<FString>& UserIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Demote a set of users in a group to the next role down. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void DemoteGroupUsers(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString GroupId,
		const TArray<FString>& UserIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Get storage objects. */
	NAKAMAAPI_API void ReadStorageObjects(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		const TArray<FNakamaReadStorageObjectId>& ObjectIds,
		TFunction<void(const FNakamaStorageObjects&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Get storage objects. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ReadStorageObjects(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		const TArray<FNakamaReadStorageObjectId>& ObjectIds,
		TFunction<void(const FNakamaStorageObjects&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Execute a Lua function on the server. */
	NAKAMAAPI_API void RpcFunc(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString Id,
		TSharedPtr<FJsonObject> Payload,
		FString HttpKey,
		TFunction<void(const FNakamaRpc&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Execute a Lua function on the server. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void RpcFunc(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString Id,
		TSharedPtr<FJsonObject> Payload,
		TFunction<void(const FNakamaRpc&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Remove the Apple ID from the social profiles on the current user's account. */
	NAKAMAAPI_API void UnlinkApple(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Remove the Apple ID from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void UnlinkApple(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Remove the custom ID from the social profiles on the current user's account. */
	NAKAMAAPI_API void UnlinkCustom(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString Id,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Remove the custom ID from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void UnlinkCustom(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString Id,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Remove the device ID from the social profiles on the current user's account. */
	NAKAMAAPI_API void UnlinkDevice(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString Id,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Remove the device ID from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void UnlinkDevice(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString Id,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Remove the email+password from the social profiles on the current user's account. */
	NAKAMAAPI_API void UnlinkEmail(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString Email,
		FString Password,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Remove the email+password from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void UnlinkEmail(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString Email,
		FString Password,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Remove Facebook from the social profiles on the current user's account. */
	NAKAMAAPI_API void UnlinkFacebook(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Remove Facebook from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void UnlinkFacebook(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Remove Facebook Instant Game profile from the social profiles on the current user's account. */
	NAKAMAAPI_API void UnlinkFacebookInstantGame(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString SignedPlayerInfo,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Remove Facebook Instant Game profile from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void UnlinkFacebookInstantGame(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString SignedPlayerInfo,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Remove Apple's GameCenter from the social profiles on the current user's account. */
	NAKAMAAPI_API void UnlinkGameCenter(
		const FNakamaClientConfig& Config,
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
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Remove Apple's GameCenter from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void UnlinkGameCenter(
		const FNakamaClientConfig& Config,
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
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Remove Google from the social profiles on the current user's account. */
	NAKAMAAPI_API void UnlinkGoogle(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Remove Google from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void UnlinkGoogle(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Remove Steam from the social profiles on the current user's account. */
	NAKAMAAPI_API void UnlinkSteam(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Remove Steam from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void UnlinkSteam(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Update fields in the current user's account. */
	NAKAMAAPI_API void UpdateAccount(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString Username,
		FString DisplayName,
		FString AvatarUrl,
		FString LangTag,
		FString Location,
		FString Timezone,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Update fields in the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void UpdateAccount(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString Username,
		FString DisplayName,
		FString AvatarUrl,
		FString LangTag,
		FString Location,
		FString Timezone,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Update fields in a given group. */
	NAKAMAAPI_API void UpdateGroup(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString GroupId,
		FString Name,
		FString Description,
		FString LangTag,
		FString AvatarUrl,
		bool Open,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Update fields in a given group. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void UpdateGroup(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString GroupId,
		FString Name,
		FString Description,
		FString LangTag,
		FString AvatarUrl,
		bool Open,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Validate Apple IAP Receipt */
	NAKAMAAPI_API void ValidatePurchaseApple(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString Receipt,
		bool Persist,
		TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Validate Apple IAP Receipt (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ValidatePurchaseApple(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString Receipt,
		bool Persist,
		TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Validate Apple Subscription Receipt */
	NAKAMAAPI_API void ValidateSubscriptionApple(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString Receipt,
		bool Persist,
		TFunction<void(const FNakamaValidateSubscriptionResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Validate Apple Subscription Receipt (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ValidateSubscriptionApple(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString Receipt,
		bool Persist,
		TFunction<void(const FNakamaValidateSubscriptionResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Validate Google IAP Receipt */
	NAKAMAAPI_API void ValidatePurchaseGoogle(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString Purchase,
		bool Persist,
		TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Validate Google IAP Receipt (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ValidatePurchaseGoogle(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString Purchase,
		bool Persist,
		TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Validate Google Subscription Receipt */
	NAKAMAAPI_API void ValidateSubscriptionGoogle(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString Receipt,
		bool Persist,
		TFunction<void(const FNakamaValidateSubscriptionResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Validate Google Subscription Receipt (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ValidateSubscriptionGoogle(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString Receipt,
		bool Persist,
		TFunction<void(const FNakamaValidateSubscriptionResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Validate Huawei IAP Receipt */
	NAKAMAAPI_API void ValidatePurchaseHuawei(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString Purchase,
		FString Signature,
		bool Persist,
		TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Validate Huawei IAP Receipt (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ValidatePurchaseHuawei(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString Purchase,
		FString Signature,
		bool Persist,
		TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Validate FB Instant IAP Receipt */
	NAKAMAAPI_API void ValidatePurchaseFacebookInstant(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString SignedRequest,
		bool Persist,
		TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Validate FB Instant IAP Receipt (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ValidatePurchaseFacebookInstant(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString SignedRequest,
		bool Persist,
		TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Write a record to a leaderboard. */
	NAKAMAAPI_API void WriteLeaderboardRecord(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString LeaderboardId,
		FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite Record,
		TFunction<void(const FNakamaLeaderboardRecord&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Write a record to a leaderboard. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void WriteLeaderboardRecord(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString LeaderboardId,
		FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite Record,
		TFunction<void(const FNakamaLeaderboardRecord&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Write objects into the storage engine. */
	NAKAMAAPI_API void WriteStorageObjects(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		const TArray<FNakamaWriteStorageObject>& Objects,
		TFunction<void(const FNakamaStorageObjectAcks&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Write objects into the storage engine. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void WriteStorageObjects(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		const TArray<FNakamaWriteStorageObject>& Objects,
		TFunction<void(const FNakamaStorageObjectAcks&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Write a record to a tournament. */
	NAKAMAAPI_API void WriteTournamentRecord(
		const FNakamaClientConfig& Config,
		const FNakamaSession& Session,
		FString TournamentId,
		FNakamaWriteTournamentRecordRequest_TournamentRecordWrite Record,
		TFunction<void(const FNakamaLeaderboardRecord&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;

	/** Write a record to a tournament. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void WriteTournamentRecord(
		const FNakamaClientConfig& Config,
		const FString& HttpKey,
		FString TournamentId,
		FNakamaWriteTournamentRecordRequest_TournamentRecordWrite Record,
		TFunction<void(const FNakamaLeaderboardRecord&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		float Timeout = 10.0f,
		TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)) noexcept;
}
