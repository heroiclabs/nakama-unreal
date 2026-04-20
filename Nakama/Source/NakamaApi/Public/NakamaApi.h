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
#include "HAL/ThreadSafeBool.h"
#include "NakamaError.h"
#include "NakamaTypes.h"

NAKAMAAPI_API DECLARE_LOG_CATEGORY_EXTERN(LogNakama, Log, All);

enum class ENakamaRequestAuth : uint8
{
  None,
  Basic,
  Bearer,
  HttpKey
};

namespace NakamaApi
{
  
  /*
  * Add friends by ID or username to a user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Ids	 The account id of a user.
  * @param Usernames	 The account username of a user.
  * @param Metadata	 Optional metadata to add to friends.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void AddFriends(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const TArray<FString>& Ids,
    const TArray<FString>& Usernames,
    const FString& Metadata,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Add friends by ID or username to a user's account.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Ids	 The account id of a user.
  * @param Usernames	 The account username of a user.
  * @param Metadata	 Optional metadata to add to friends.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void AddFriends(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const TArray<FString>& Ids,
    const TArray<FString>& Usernames,
    const FString& Metadata,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Add users to a group.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param GroupId	 The group to add users to.
  * @param UserIds	 The users to add.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void AddGroupUsers(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& GroupId,
    const TArray<FString>& UserIds,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Add users to a group.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param GroupId	 The group to add users to.
  * @param UserIds	 The users to add.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void AddGroupUsers(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& GroupId,
    const TArray<FString>& UserIds,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Refresh a user's session using a refresh token retrieved from a previous authentication request.
  *
  * @param Config	The client configuration.
  * @param Token	 Refresh token.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void SessionRefresh(
    const FNakamaClientConfig& Config,
    const FString& Token,
    const TMap<FString, FString>& Vars,
    TFunction<void(const FNakamaSession&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Log out a session, invalidate a refresh token, or log out all sessions/refresh tokens for a user.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Token	 Session token to log out.
  * @param RefreshToken	 Refresh token to invalidate.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void SessionLogout(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& Token,
    const FString& RefreshToken,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Log out a session, invalidate a refresh token, or log out all sessions/refresh tokens for a user.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Token	 Session token to log out.
  * @param RefreshToken	 Refresh token to invalidate.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void SessionLogout(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& Token,
    const FString& RefreshToken,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Authenticate a user with an Apple ID against the server.
  *
  * @param Config	The client configuration.
  * @param Account	 The Apple account details.
  * @param Create	 Register the account if the user does not already exist.
  * @param Username	 Set the username on the account at register. Must be unique.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void AuthenticateApple(
    const FNakamaClientConfig& Config,
    const FNakamaAccountApple& Account,
    bool Create,
    const FString& Username,
    TFunction<void(const FNakamaSession&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Authenticate a user with a custom id against the server.
  *
  * @param Config	The client configuration.
  * @param Account	 The custom account details.
  * @param Create	 Register the account if the user does not already exist.
  * @param Username	 Set the username on the account at register. Must be unique.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void AuthenticateCustom(
    const FNakamaClientConfig& Config,
    const FNakamaAccountCustom& Account,
    bool Create,
    const FString& Username,
    TFunction<void(const FNakamaSession&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Authenticate a user with a device id against the server.
  *
  * @param Config	The client configuration.
  * @param Account	 The device account details.
  * @param Create	 Register the account if the user does not already exist.
  * @param Username	 Set the username on the account at register. Must be unique.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void AuthenticateDevice(
    const FNakamaClientConfig& Config,
    const FNakamaAccountDevice& Account,
    bool Create,
    const FString& Username,
    TFunction<void(const FNakamaSession&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Authenticate a user with an email+password against the server.
  *
  * @param Config	The client configuration.
  * @param Account	 The email account details.
  * @param Create	 Register the account if the user does not already exist.
  * @param Username	 Set the username on the account at register. Must be unique.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void AuthenticateEmail(
    const FNakamaClientConfig& Config,
    const FNakamaAccountEmail& Account,
    bool Create,
    const FString& Username,
    TFunction<void(const FNakamaSession&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Authenticate a user with a Facebook OAuth token against the server.
  *
  * @param Config	The client configuration.
  * @param Account	 The Facebook account details.
  * @param Create	 Register the account if the user does not already exist.
  * @param Username	 Set the username on the account at register. Must be unique.
  * @param Sync	 Import Facebook friends for the user.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void AuthenticateFacebook(
    const FNakamaClientConfig& Config,
    const FNakamaAccountFacebook& Account,
    bool Create,
    const FString& Username,
    bool Sync,
    TFunction<void(const FNakamaSession&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Authenticate a user with a Facebook Instant Game token against the server.
  *
  * @param Config	The client configuration.
  * @param Account	 The Facebook Instant Game account details.
  * @param Create	 Register the account if the user does not already exist.
  * @param Username	 Set the username on the account at register. Must be unique.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void AuthenticateFacebookInstantGame(
    const FNakamaClientConfig& Config,
    const FNakamaAccountFacebookInstantGame& Account,
    bool Create,
    const FString& Username,
    TFunction<void(const FNakamaSession&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Authenticate a user with Apple's GameCenter against the server.
  *
  * @param Config	The client configuration.
  * @param Account	 The Game Center account details.
  * @param Create	 Register the account if the user does not already exist.
  * @param Username	 Set the username on the account at register. Must be unique.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void AuthenticateGameCenter(
    const FNakamaClientConfig& Config,
    const FNakamaAccountGameCenter& Account,
    bool Create,
    const FString& Username,
    TFunction<void(const FNakamaSession&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Authenticate a user with Google against the server.
  *
  * @param Config	The client configuration.
  * @param Account	 The Google account details.
  * @param Create	 Register the account if the user does not already exist.
  * @param Username	 Set the username on the account at register. Must be unique.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void AuthenticateGoogle(
    const FNakamaClientConfig& Config,
    const FNakamaAccountGoogle& Account,
    bool Create,
    const FString& Username,
    TFunction<void(const FNakamaSession&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Authenticate a user with Steam against the server.
  *
  * @param Config	The client configuration.
  * @param Account	 The Steam account details.
  * @param Create	 Register the account if the user does not already exist.
  * @param Username	 Set the username on the account at register. Must be unique.
  * @param Sync	 Import Steam friends for the user.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void AuthenticateSteam(
    const FNakamaClientConfig& Config,
    const FNakamaAccountSteam& Account,
    bool Create,
    const FString& Username,
    bool Sync,
    TFunction<void(const FNakamaSession&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Ban a set of users from a group.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param GroupId	 The group to ban users from.
  * @param UserIds	 The users to ban.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void BanGroupUsers(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& GroupId,
    const TArray<FString>& UserIds,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Ban a set of users from a group.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param GroupId	 The group to ban users from.
  * @param UserIds	 The users to ban.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void BanGroupUsers(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& GroupId,
    const TArray<FString>& UserIds,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Block one or more users by ID or username.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Ids	 The account id of a user.
  * @param Usernames	 The account username of a user.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void BlockFriends(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const TArray<FString>& Ids,
    const TArray<FString>& Usernames,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Block one or more users by ID or username.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Ids	 The account id of a user.
  * @param Usernames	 The account username of a user.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void BlockFriends(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const TArray<FString>& Ids,
    const TArray<FString>& Usernames,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
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
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void CreateGroup(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& Name,
    const FString& Description,
    const FString& LangTag,
    const FString& AvatarUrl,
    bool Open,
    int32 MaxCount,
    TFunction<void(const FNakamaGroup&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
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
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void CreateGroup(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& Name,
    const FString& Description,
    const FString& LangTag,
    const FString& AvatarUrl,
    bool Open,
    int32 MaxCount,
    TFunction<void(const FNakamaGroup&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Delete the current user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void DeleteAccount(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Delete the current user's account.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void DeleteAccount(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Delete one or more users by ID or username.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Ids	 The account id of a user.
  * @param Usernames	 The account username of a user.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void DeleteFriends(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const TArray<FString>& Ids,
    const TArray<FString>& Usernames,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Delete one or more users by ID or username.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Ids	 The account id of a user.
  * @param Usernames	 The account username of a user.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void DeleteFriends(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const TArray<FString>& Ids,
    const TArray<FString>& Usernames,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Delete a group by ID.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param GroupId	 The id of a group.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void DeleteGroup(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& GroupId,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Delete a group by ID.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param GroupId	 The id of a group.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void DeleteGroup(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& GroupId,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Delete a leaderboard record.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param LeaderboardId	 The leaderboard ID to delete from.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void DeleteLeaderboardRecord(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& LeaderboardId,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Delete a leaderboard record.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param LeaderboardId	 The leaderboard ID to delete from.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void DeleteLeaderboardRecord(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& LeaderboardId,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Delete one or more notifications for the current user.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Ids	 The id of notifications.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void DeleteNotifications(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const TArray<FString>& Ids,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Delete one or more notifications for the current user.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Ids	 The id of notifications.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void DeleteNotifications(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const TArray<FString>& Ids,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Delete a tournament record.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param TournamentId	 The tournament ID to delete from.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void DeleteTournamentRecord(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& TournamentId,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Delete a tournament record.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param TournamentId	 The tournament ID to delete from.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void DeleteTournamentRecord(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& TournamentId,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Delete one or more objects by ID or username.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param ObjectIds	 Batch of storage objects.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void DeleteStorageObjects(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const TArray<FNakamaDeleteStorageObjectId>& ObjectIds,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Delete one or more objects by ID or username.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param ObjectIds	 Batch of storage objects.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void DeleteStorageObjects(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const TArray<FNakamaDeleteStorageObjectId>& ObjectIds,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Submit an event for processing in the server's registered runtime custom events handler.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Name	 An event name, type, category, or identifier.
  * @param Timestamp	 The time when the event was triggered.
  * @param External	 True if the event came directly from a client call, false otherwise.
  * @param Properties	 Arbitrary event property values.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void Event(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& Name,
    const FString& Timestamp,
    bool External,
    const TMap<FString, FString>& Properties,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Submit an event for processing in the server's registered runtime custom events handler.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Name	 An event name, type, category, or identifier.
  * @param Timestamp	 The time when the event was triggered.
  * @param External	 True if the event came directly from a client call, false otherwise.
  * @param Properties	 Arbitrary event property values.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void Event(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& Name,
    const FString& Timestamp,
    bool External,
    const TMap<FString, FString>& Properties,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Fetch the current user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void GetAccount(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    TFunction<void(const FNakamaAccount&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Fetch the current user's account.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void GetAccount(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    TFunction<void(const FNakamaAccount&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Fetch zero or more users by ID and/or username.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Ids	 The account id of a user.
  * @param Usernames	 The account username of a user.
  * @param FacebookIds	 The Facebook ID of a user.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void GetUsers(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const TArray<FString>& Ids,
    const TArray<FString>& Usernames,
    const TArray<FString>& FacebookIds,
    TFunction<void(const FNakamaUsers&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Fetch zero or more users by ID and/or username.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Ids	 The account id of a user.
  * @param Usernames	 The account username of a user.
  * @param FacebookIds	 The Facebook ID of a user.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void GetUsers(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const TArray<FString>& Ids,
    const TArray<FString>& Usernames,
    const TArray<FString>& FacebookIds,
    TFunction<void(const FNakamaUsers&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Get subscription by product id.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param ProductId	 Product id of the subscription
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void GetSubscription(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& ProductId,
    TFunction<void(const FNakamaValidatedSubscription&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Get subscription by product id.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param ProductId	 Product id of the subscription
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void GetSubscription(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& ProductId,
    TFunction<void(const FNakamaValidatedSubscription&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Get matchmaker stats.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void GetMatchmakerStats(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    TFunction<void(const FNakamaMatchmakerStats&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Get matchmaker stats.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void GetMatchmakerStats(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    TFunction<void(const FNakamaMatchmakerStats&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * A healthcheck which load balancers can use to check the service.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void Healthcheck(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * A healthcheck which load balancers can use to check the service.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void Healthcheck(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Import Facebook friends and add them to a user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Account	 The Facebook account details.
  * @param Reset	 Reset the current user's friends list.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ImportFacebookFriends(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FNakamaAccountFacebook& Account,
    bool Reset,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Import Facebook friends and add them to a user's account.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Account	 The Facebook account details.
  * @param Reset	 Reset the current user's friends list.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ImportFacebookFriends(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FNakamaAccountFacebook& Account,
    bool Reset,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Import Steam friends and add them to a user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Account	 The Facebook account details.
  * @param Reset	 Reset the current user's friends list.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ImportSteamFriends(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FNakamaAccountSteam& Account,
    bool Reset,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Import Steam friends and add them to a user's account.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Account	 The Facebook account details.
  * @param Reset	 Reset the current user's friends list.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ImportSteamFriends(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FNakamaAccountSteam& Account,
    bool Reset,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Immediately join an open group, or request to join a closed one.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param GroupId	 The group ID to join. The group must already exist.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void JoinGroup(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& GroupId,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Immediately join an open group, or request to join a closed one.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param GroupId	 The group ID to join. The group must already exist.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void JoinGroup(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& GroupId,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Attempt to join an open and running tournament.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param TournamentId	 The ID of the tournament to join. The tournament must already exist.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void JoinTournament(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& TournamentId,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Attempt to join an open and running tournament.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param TournamentId	 The ID of the tournament to join. The tournament must already exist.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void JoinTournament(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& TournamentId,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Kick a set of users from a group.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param GroupId	 The group ID to kick from.
  * @param UserIds	 The users to kick.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void KickGroupUsers(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& GroupId,
    const TArray<FString>& UserIds,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Kick a set of users from a group.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param GroupId	 The group ID to kick from.
  * @param UserIds	 The users to kick.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void KickGroupUsers(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& GroupId,
    const TArray<FString>& UserIds,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Leave a group the user is a member of.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param GroupId	 The group ID to leave.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void LeaveGroup(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& GroupId,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Leave a group the user is a member of.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param GroupId	 The group ID to leave.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void LeaveGroup(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& GroupId,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Add an Apple ID to the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Token	 The ID token received from Apple to validate.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void LinkApple(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& Token,
    const TMap<FString, FString>& Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Add an Apple ID to the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Token	 The ID token received from Apple to validate.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void LinkApple(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& Token,
    const TMap<FString, FString>& Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Add a custom ID to the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Id	 A custom identifier.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void LinkCustom(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& Id,
    const TMap<FString, FString>& Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Add a custom ID to the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Id	 A custom identifier.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void LinkCustom(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& Id,
    const TMap<FString, FString>& Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Add a device ID to the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Id	 A device identifier. Should be obtained by a platform-specific device API.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void LinkDevice(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& Id,
    const TMap<FString, FString>& Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Add a device ID to the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Id	 A device identifier. Should be obtained by a platform-specific device API.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void LinkDevice(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& Id,
    const TMap<FString, FString>& Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Add an email+password to the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Email	 A valid RFC-5322 email address.
  * @param Password	 A password for the user account.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void LinkEmail(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& Email,
    const FString& Password,
    const TMap<FString, FString>& Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Add an email+password to the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Email	 A valid RFC-5322 email address.
  * @param Password	 A password for the user account.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void LinkEmail(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& Email,
    const FString& Password,
    const TMap<FString, FString>& Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Add Facebook to the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Account	 The Facebook account details.
  * @param Sync	 Import Facebook friends for the user.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void LinkFacebook(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FNakamaAccountFacebook& Account,
    bool Sync,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Add Facebook to the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Account	 The Facebook account details.
  * @param Sync	 Import Facebook friends for the user.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void LinkFacebook(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FNakamaAccountFacebook& Account,
    bool Sync,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Add Facebook Instant Game to the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param SignedPlayerInfo	 The OAuth token received from a Facebook Instant Game that may be decoded with the Application Secret (must be available with the nakama configuration)
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void LinkFacebookInstantGame(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& SignedPlayerInfo,
    const TMap<FString, FString>& Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Add Facebook Instant Game to the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param SignedPlayerInfo	 The OAuth token received from a Facebook Instant Game that may be decoded with the Application Secret (must be available with the nakama configuration)
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void LinkFacebookInstantGame(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& SignedPlayerInfo,
    const TMap<FString, FString>& Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
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
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void LinkGameCenter(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& PlayerId,
    const FString& BundleId,
    int64 TimestampSeconds,
    const FString& Salt,
    const FString& Signature,
    const FString& PublicKeyUrl,
    const TMap<FString, FString>& Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
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
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void LinkGameCenter(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& PlayerId,
    const FString& BundleId,
    int64 TimestampSeconds,
    const FString& Salt,
    const FString& Signature,
    const FString& PublicKeyUrl,
    const TMap<FString, FString>& Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Add Google to the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Token	 The OAuth token received from Google to access their profile API.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void LinkGoogle(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& Token,
    const TMap<FString, FString>& Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Add Google to the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Token	 The OAuth token received from Google to access their profile API.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void LinkGoogle(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& Token,
    const TMap<FString, FString>& Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Add Steam to the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Account	 The Facebook account details.
  * @param Sync	 Import Steam friends for the user.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void LinkSteam(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FNakamaAccountSteam& Account,
    bool Sync,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Add Steam to the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Account	 The Facebook account details.
  * @param Sync	 Import Steam friends for the user.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void LinkSteam(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FNakamaAccountSteam& Account,
    bool Sync,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * List a channel's message history.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param ChannelId	 The channel ID to list from.
  * @param Limit	 Max number of records to return. Between 1 and 100.
  * @param Forward	 True if listing should be older messages to newer, false if reverse.
  * @param Cursor	 A pagination cursor, if any.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ListChannelMessages(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& ChannelId,
    int32 Limit,
    bool Forward,
    const FString& Cursor,
    TFunction<void(const FNakamaChannelMessageList&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * List a channel's message history.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param ChannelId	 The channel ID to list from.
  * @param Limit	 Max number of records to return. Between 1 and 100.
  * @param Forward	 True if listing should be older messages to newer, false if reverse.
  * @param Cursor	 A pagination cursor, if any.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ListChannelMessages(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& ChannelId,
    int32 Limit,
    bool Forward,
    const FString& Cursor,
    TFunction<void(const FNakamaChannelMessageList&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * List all friends for the current user.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Limit	 Max number of records to return. Between 1 and 1000.
  * @param State	 The friend state to list.
  * @param Cursor	 An optional next page cursor.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ListFriends(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    int32 Limit,
    int32 State,
    const FString& Cursor,
    TFunction<void(const FNakamaFriendList&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * List all friends for the current user.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Limit	 Max number of records to return. Between 1 and 1000.
  * @param State	 The friend state to list.
  * @param Cursor	 An optional next page cursor.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ListFriends(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    int32 Limit,
    int32 State,
    const FString& Cursor,
    TFunction<void(const FNakamaFriendList&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * List friends of friends for the current user.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Limit	 Max number of records to return. Between 1 and 100.
  * @param Cursor	 An optional next page cursor.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ListFriendsOfFriends(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    int32 Limit,
    const FString& Cursor,
    TFunction<void(const FNakamaFriendsOfFriendsList&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * List friends of friends for the current user.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Limit	 Max number of records to return. Between 1 and 100.
  * @param Cursor	 An optional next page cursor.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ListFriendsOfFriends(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    int32 Limit,
    const FString& Cursor,
    TFunction<void(const FNakamaFriendsOfFriendsList&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
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
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ListGroups(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& Name,
    const FString& Cursor,
    int32 Limit,
    const FString& LangTag,
    int32 Members,
    bool Open,
    TFunction<void(const FNakamaGroupList&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
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
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ListGroups(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& Name,
    const FString& Cursor,
    int32 Limit,
    const FString& LangTag,
    int32 Members,
    bool Open,
    TFunction<void(const FNakamaGroupList&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * List all users that are part of a group.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param GroupId	 The group ID to list from.
  * @param Limit	 Max number of records to return. Between 1 and 100.
  * @param State	 The group user state to list.
  * @param Cursor	 An optional next page cursor.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ListGroupUsers(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& GroupId,
    int32 Limit,
    int32 State,
    const FString& Cursor,
    TFunction<void(const FNakamaGroupUserList&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * List all users that are part of a group.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param GroupId	 The group ID to list from.
  * @param Limit	 Max number of records to return. Between 1 and 100.
  * @param State	 The group user state to list.
  * @param Cursor	 An optional next page cursor.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ListGroupUsers(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& GroupId,
    int32 Limit,
    int32 State,
    const FString& Cursor,
    TFunction<void(const FNakamaGroupUserList&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * List leaderboard records.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param LeaderboardId	 The ID of the leaderboard to list for.
  * @param OwnerIds	 One or more owners to retrieve records for.
  * @param Limit	 Max number of records to return. Between 1 and 100.
  * @param Cursor	 A next or previous page cursor.
  * @param Expiry	 Expiry in seconds (since epoch) to begin fetching records from. Optional. 0 means from current time.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ListLeaderboardRecords(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& LeaderboardId,
    const TArray<FString>& OwnerIds,
    int32 Limit,
    const FString& Cursor,
    int64 Expiry,
    TFunction<void(const FNakamaLeaderboardRecordList&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * List leaderboard records.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param LeaderboardId	 The ID of the leaderboard to list for.
  * @param OwnerIds	 One or more owners to retrieve records for.
  * @param Limit	 Max number of records to return. Between 1 and 100.
  * @param Cursor	 A next or previous page cursor.
  * @param Expiry	 Expiry in seconds (since epoch) to begin fetching records from. Optional. 0 means from current time.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ListLeaderboardRecords(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& LeaderboardId,
    const TArray<FString>& OwnerIds,
    int32 Limit,
    const FString& Cursor,
    int64 Expiry,
    TFunction<void(const FNakamaLeaderboardRecordList&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * List leaderboard records around the target ownerId.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param LeaderboardId	 The ID of the tournament to list for.
  * @param Limit	 Max number of records to return. Between 1 and 100.
  * @param OwnerId	 The owner to retrieve records around.
  * @param Expiry	 Expiry in seconds (since epoch) to begin fetching records from.
  * @param Cursor	 A next or previous page cursor.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ListLeaderboardRecordsAroundOwner(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& LeaderboardId,
    int32 Limit,
    const FString& OwnerId,
    int64 Expiry,
    const FString& Cursor,
    TFunction<void(const FNakamaLeaderboardRecordList&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * List leaderboard records around the target ownerId.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param LeaderboardId	 The ID of the tournament to list for.
  * @param Limit	 Max number of records to return. Between 1 and 100.
  * @param OwnerId	 The owner to retrieve records around.
  * @param Expiry	 Expiry in seconds (since epoch) to begin fetching records from.
  * @param Cursor	 A next or previous page cursor.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ListLeaderboardRecordsAroundOwner(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& LeaderboardId,
    int32 Limit,
    const FString& OwnerId,
    int64 Expiry,
    const FString& Cursor,
    TFunction<void(const FNakamaLeaderboardRecordList&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
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
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ListMatches(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    int32 Limit,
    bool Authoritative,
    const FString& Label,
    int32 MinSize,
    int32 MaxSize,
    const FString& Query,
    TFunction<void(const FNakamaMatchList&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
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
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ListMatches(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    int32 Limit,
    bool Authoritative,
    const FString& Label,
    int32 MinSize,
    int32 MaxSize,
    const FString& Query,
    TFunction<void(const FNakamaMatchList&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * List parties and optionally filter by matching criteria.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Limit	 Limit the number of returned parties.
  * @param Open	 Optionally filter by open/closed parties.
  * @param Query	 Arbitrary label query.
  * @param Cursor	 Cursor for the next page of results, if any.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ListParties(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    int32 Limit,
    bool Open,
    const FString& Query,
    const FString& Cursor,
    TFunction<void(const FNakamaPartyList&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * List parties and optionally filter by matching criteria.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Limit	 Limit the number of returned parties.
  * @param Open	 Optionally filter by open/closed parties.
  * @param Query	 Arbitrary label query.
  * @param Cursor	 Cursor for the next page of results, if any.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ListParties(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    int32 Limit,
    bool Open,
    const FString& Query,
    const FString& Cursor,
    TFunction<void(const FNakamaPartyList&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Fetch list of notifications.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Limit	 The number of notifications to get. Between 1 and 100.
  * @param CacheableCursor	 A cursor to page through notifications. May be cached by clients to get from point in time forwards.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ListNotifications(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    int32 Limit,
    const FString& CacheableCursor,
    TFunction<void(const FNakamaNotificationList&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Fetch list of notifications.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Limit	 The number of notifications to get. Between 1 and 100.
  * @param CacheableCursor	 A cursor to page through notifications. May be cached by clients to get from point in time forwards.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ListNotifications(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    int32 Limit,
    const FString& CacheableCursor,
    TFunction<void(const FNakamaNotificationList&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * List publicly readable storage objects in a given collection.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param UserId	 ID of the user.
  * @param Collection	 The collection which stores the object.
  * @param Limit	 The number of storage objects to list. Between 1 and 100.
  * @param Cursor	 The cursor to page through results from.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ListStorageObjects(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& UserId,
    const FString& Collection,
    int32 Limit,
    const FString& Cursor,
    TFunction<void(const FNakamaStorageObjectList&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * List publicly readable storage objects in a given collection.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param UserId	 ID of the user.
  * @param Collection	 The collection which stores the object.
  * @param Limit	 The number of storage objects to list. Between 1 and 100.
  * @param Cursor	 The cursor to page through results from.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ListStorageObjects(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& UserId,
    const FString& Collection,
    int32 Limit,
    const FString& Cursor,
    TFunction<void(const FNakamaStorageObjectList&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * List user's subscriptions.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Limit	 Max number of results per page
  * @param Cursor	 Cursor to retrieve a page of records from
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ListSubscriptions(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    int32 Limit,
    const FString& Cursor,
    TFunction<void(const FNakamaSubscriptionList&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * List user's subscriptions.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Limit	 Max number of results per page
  * @param Cursor	 Cursor to retrieve a page of records from
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ListSubscriptions(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    int32 Limit,
    const FString& Cursor,
    TFunction<void(const FNakamaSubscriptionList&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
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
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ListTournaments(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    int32 CategoryStart,
    int32 CategoryEnd,
    int32 StartTime,
    int32 EndTime,
    int32 Limit,
    const FString& Cursor,
    TFunction<void(const FNakamaTournamentList&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
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
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ListTournaments(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    int32 CategoryStart,
    int32 CategoryEnd,
    int32 StartTime,
    int32 EndTime,
    int32 Limit,
    const FString& Cursor,
    TFunction<void(const FNakamaTournamentList&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * List tournament records.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param TournamentId	 The ID of the tournament to list for.
  * @param OwnerIds	 One or more owners to retrieve records for.
  * @param Limit	 Max number of records to return. Between 1 and 100.
  * @param Cursor	 A next or previous page cursor.
  * @param Expiry	 Expiry in seconds (since epoch) to begin fetching records from.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ListTournamentRecords(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& TournamentId,
    const TArray<FString>& OwnerIds,
    int32 Limit,
    const FString& Cursor,
    int64 Expiry,
    TFunction<void(const FNakamaTournamentRecordList&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * List tournament records.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param TournamentId	 The ID of the tournament to list for.
  * @param OwnerIds	 One or more owners to retrieve records for.
  * @param Limit	 Max number of records to return. Between 1 and 100.
  * @param Cursor	 A next or previous page cursor.
  * @param Expiry	 Expiry in seconds (since epoch) to begin fetching records from.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ListTournamentRecords(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& TournamentId,
    const TArray<FString>& OwnerIds,
    int32 Limit,
    const FString& Cursor,
    int64 Expiry,
    TFunction<void(const FNakamaTournamentRecordList&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * List tournament records for a given owner.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param TournamentId	 The ID of the tournament to list for.
  * @param Limit	 Max number of records to return. Between 1 and 100.
  * @param OwnerId	 The owner to retrieve records around.
  * @param Expiry	 Expiry in seconds (since epoch) to begin fetching records from.
  * @param Cursor	 A next or previous page cursor.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ListTournamentRecordsAroundOwner(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& TournamentId,
    int32 Limit,
    const FString& OwnerId,
    int64 Expiry,
    const FString& Cursor,
    TFunction<void(const FNakamaTournamentRecordList&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * List tournament records for a given owner.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param TournamentId	 The ID of the tournament to list for.
  * @param Limit	 Max number of records to return. Between 1 and 100.
  * @param OwnerId	 The owner to retrieve records around.
  * @param Expiry	 Expiry in seconds (since epoch) to begin fetching records from.
  * @param Cursor	 A next or previous page cursor.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ListTournamentRecordsAroundOwner(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& TournamentId,
    int32 Limit,
    const FString& OwnerId,
    int64 Expiry,
    const FString& Cursor,
    TFunction<void(const FNakamaTournamentRecordList&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * List groups the current user belongs to.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param UserId	 ID of the user.
  * @param Limit	 Max number of records to return. Between 1 and 100.
  * @param State	 The user group state to list.
  * @param Cursor	 An optional next page cursor.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ListUserGroups(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& UserId,
    int32 Limit,
    int32 State,
    const FString& Cursor,
    TFunction<void(const FNakamaUserGroupList&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * List groups the current user belongs to.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param UserId	 ID of the user.
  * @param Limit	 Max number of records to return. Between 1 and 100.
  * @param State	 The user group state to list.
  * @param Cursor	 An optional next page cursor.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ListUserGroups(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& UserId,
    int32 Limit,
    int32 State,
    const FString& Cursor,
    TFunction<void(const FNakamaUserGroupList&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Promote a set of users in a group to the next role up.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param GroupId	 The group ID to promote in.
  * @param UserIds	 The users to promote.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void PromoteGroupUsers(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& GroupId,
    const TArray<FString>& UserIds,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Promote a set of users in a group to the next role up.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param GroupId	 The group ID to promote in.
  * @param UserIds	 The users to promote.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void PromoteGroupUsers(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& GroupId,
    const TArray<FString>& UserIds,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Demote a set of users in a group to the next role down.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param GroupId	 The group ID to demote in.
  * @param UserIds	 The users to demote.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void DemoteGroupUsers(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& GroupId,
    const TArray<FString>& UserIds,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Demote a set of users in a group to the next role down.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param GroupId	 The group ID to demote in.
  * @param UserIds	 The users to demote.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void DemoteGroupUsers(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& GroupId,
    const TArray<FString>& UserIds,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Get storage objects.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param ObjectIds	 Batch of storage objects.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ReadStorageObjects(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const TArray<FNakamaReadStorageObjectId>& ObjectIds,
    TFunction<void(const FNakamaStorageObjects&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Get storage objects.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param ObjectIds	 Batch of storage objects.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ReadStorageObjects(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const TArray<FNakamaReadStorageObjectId>& ObjectIds,
    TFunction<void(const FNakamaStorageObjects&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Execute a Lua function on the server.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Id	 The identifier of the function.
  * @param Payload	 The payload of the function which must be a JSON object.
  * @param HttpKey	 The authentication key used when executed as a non-client HTTP request.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void RpcFunc(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& Id,
    const FString& Payload,
    const FString& HttpKey,
    TFunction<void(const FNakamaRpc&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Execute a Lua function on the server.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Id	 The identifier of the function.
  * @param Payload	 The payload of the function which must be a JSON object.
  * @param HttpKey	 The authentication key used when executed as a non-client HTTP request.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void RpcFunc(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& Id,
    const FString& Payload,
    const FString& HttpKey,
    TFunction<void(const FNakamaRpc&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Remove the Apple ID from the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Token	 The ID token received from Apple to validate.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void UnlinkApple(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& Token,
    const TMap<FString, FString>& Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Remove the Apple ID from the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Token	 The ID token received from Apple to validate.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void UnlinkApple(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& Token,
    const TMap<FString, FString>& Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Remove the custom ID from the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Id	 A custom identifier.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void UnlinkCustom(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& Id,
    const TMap<FString, FString>& Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Remove the custom ID from the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Id	 A custom identifier.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void UnlinkCustom(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& Id,
    const TMap<FString, FString>& Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Remove the device ID from the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Id	 A device identifier. Should be obtained by a platform-specific device API.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void UnlinkDevice(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& Id,
    const TMap<FString, FString>& Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Remove the device ID from the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Id	 A device identifier. Should be obtained by a platform-specific device API.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void UnlinkDevice(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& Id,
    const TMap<FString, FString>& Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Remove the email+password from the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Email	 A valid RFC-5322 email address.
  * @param Password	 A password for the user account.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void UnlinkEmail(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& Email,
    const FString& Password,
    const TMap<FString, FString>& Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Remove the email+password from the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Email	 A valid RFC-5322 email address.
  * @param Password	 A password for the user account.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void UnlinkEmail(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& Email,
    const FString& Password,
    const TMap<FString, FString>& Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Remove Facebook from the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Token	 The OAuth token received from Facebook to access their profile API.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void UnlinkFacebook(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& Token,
    const TMap<FString, FString>& Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Remove Facebook from the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Token	 The OAuth token received from Facebook to access their profile API.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void UnlinkFacebook(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& Token,
    const TMap<FString, FString>& Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Remove Facebook Instant Game profile from the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param SignedPlayerInfo	 The OAuth token received from a Facebook Instant Game that may be decoded with the Application Secret (must be available with the nakama configuration)
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void UnlinkFacebookInstantGame(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& SignedPlayerInfo,
    const TMap<FString, FString>& Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Remove Facebook Instant Game profile from the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param SignedPlayerInfo	 The OAuth token received from a Facebook Instant Game that may be decoded with the Application Secret (must be available with the nakama configuration)
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void UnlinkFacebookInstantGame(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& SignedPlayerInfo,
    const TMap<FString, FString>& Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
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
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void UnlinkGameCenter(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& PlayerId,
    const FString& BundleId,
    int64 TimestampSeconds,
    const FString& Salt,
    const FString& Signature,
    const FString& PublicKeyUrl,
    const TMap<FString, FString>& Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
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
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void UnlinkGameCenter(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& PlayerId,
    const FString& BundleId,
    int64 TimestampSeconds,
    const FString& Salt,
    const FString& Signature,
    const FString& PublicKeyUrl,
    const TMap<FString, FString>& Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Remove Google from the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Token	 The OAuth token received from Google to access their profile API.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void UnlinkGoogle(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& Token,
    const TMap<FString, FString>& Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Remove Google from the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Token	 The OAuth token received from Google to access their profile API.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void UnlinkGoogle(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& Token,
    const TMap<FString, FString>& Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Remove Steam from the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Token	 The account token received from Steam to access their profile API.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void UnlinkSteam(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& Token,
    const TMap<FString, FString>& Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Remove Steam from the social profiles on the current user's account.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Token	 The account token received from Steam to access their profile API.
  * @param Vars	 Extra information that will be bundled in the session token.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void UnlinkSteam(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& Token,
    const TMap<FString, FString>& Vars,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
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
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void UpdateAccount(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& Username,
    const FString& DisplayName,
    const FString& AvatarUrl,
    const FString& LangTag,
    const FString& Location,
    const FString& Timezone,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
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
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void UpdateAccount(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& Username,
    const FString& DisplayName,
    const FString& AvatarUrl,
    const FString& LangTag,
    const FString& Location,
    const FString& Timezone,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
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
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void UpdateGroup(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& GroupId,
    const FString& Name,
    const FString& Description,
    const FString& LangTag,
    const FString& AvatarUrl,
    bool Open,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
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
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void UpdateGroup(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& GroupId,
    const FString& Name,
    const FString& Description,
    const FString& LangTag,
    const FString& AvatarUrl,
    bool Open,
    TFunction<void()> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Validate Apple IAP Receipt
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Receipt	 Base64 encoded Apple receipt data payload.
  * @param Persist	 Persist the purchase
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ValidatePurchaseApple(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& Receipt,
    bool Persist,
    TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Validate Apple IAP Receipt
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Receipt	 Base64 encoded Apple receipt data payload.
  * @param Persist	 Persist the purchase
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ValidatePurchaseApple(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& Receipt,
    bool Persist,
    TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Validate Apple Subscription Receipt
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Receipt	 Base64 encoded Apple receipt data payload.
  * @param Persist	 Persist the subscription.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ValidateSubscriptionApple(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& Receipt,
    bool Persist,
    TFunction<void(const FNakamaValidateSubscriptionResponse&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Validate Apple Subscription Receipt
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Receipt	 Base64 encoded Apple receipt data payload.
  * @param Persist	 Persist the subscription.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ValidateSubscriptionApple(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& Receipt,
    bool Persist,
    TFunction<void(const FNakamaValidateSubscriptionResponse&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Validate Google IAP Receipt
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Purchase	 JSON encoded Google purchase payload.
  * @param Persist	 Persist the purchase
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ValidatePurchaseGoogle(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& Purchase,
    bool Persist,
    TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Validate Google IAP Receipt
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Purchase	 JSON encoded Google purchase payload.
  * @param Persist	 Persist the purchase
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ValidatePurchaseGoogle(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& Purchase,
    bool Persist,
    TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Validate Google Subscription Receipt
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Receipt	 JSON encoded Google purchase payload.
  * @param Persist	 Persist the subscription.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ValidateSubscriptionGoogle(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& Receipt,
    bool Persist,
    TFunction<void(const FNakamaValidateSubscriptionResponse&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Validate Google Subscription Receipt
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Receipt	 JSON encoded Google purchase payload.
  * @param Persist	 Persist the subscription.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ValidateSubscriptionGoogle(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& Receipt,
    bool Persist,
    TFunction<void(const FNakamaValidateSubscriptionResponse&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Validate Huawei IAP Receipt
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Purchase	 JSON encoded Huawei InAppPurchaseData.
  * @param Signature	 InAppPurchaseData signature.
  * @param Persist	 Persist the purchase
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ValidatePurchaseHuawei(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& Purchase,
    const FString& Signature,
    bool Persist,
    TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Validate Huawei IAP Receipt
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Purchase	 JSON encoded Huawei InAppPurchaseData.
  * @param Signature	 InAppPurchaseData signature.
  * @param Persist	 Persist the purchase
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ValidatePurchaseHuawei(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& Purchase,
    const FString& Signature,
    bool Persist,
    TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Validate FB Instant IAP Receipt
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param SignedRequest	 Base64 encoded Facebook Instant signedRequest receipt data payload.
  * @param Persist	 Persist the purchase
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ValidatePurchaseFacebookInstant(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& SignedRequest,
    bool Persist,
    TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Validate FB Instant IAP Receipt
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param SignedRequest	 Base64 encoded Facebook Instant signedRequest receipt data payload.
  * @param Persist	 Persist the purchase
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void ValidatePurchaseFacebookInstant(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& SignedRequest,
    bool Persist,
    TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Write a record to a leaderboard.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param LeaderboardId	 The ID of the leaderboard to write to.
  * @param Record	 Record input.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void WriteLeaderboardRecord(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& LeaderboardId,
    const FNakamaWriteLeaderboardRecordRequestLeaderboardRecordWrite& Record,
    TFunction<void(const FNakamaLeaderboardRecord&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Write a record to a leaderboard.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param LeaderboardId	 The ID of the leaderboard to write to.
  * @param Record	 Record input.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void WriteLeaderboardRecord(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& LeaderboardId,
    const FNakamaWriteLeaderboardRecordRequestLeaderboardRecordWrite& Record,
    TFunction<void(const FNakamaLeaderboardRecord&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Write objects into the storage engine.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Objects	 The objects to store on the server.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void WriteStorageObjects(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const TArray<FNakamaWriteStorageObject>& Objects,
    TFunction<void(const FNakamaStorageObjectAcks&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Write objects into the storage engine.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Objects	 The objects to store on the server.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void WriteStorageObjects(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const TArray<FNakamaWriteStorageObject>& Objects,
    TFunction<void(const FNakamaStorageObjectAcks&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Write a record to a tournament.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param TournamentId	 The tournament ID to write the record for.
  * @param Record	 Record input.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void WriteTournamentRecord(
    const FNakamaClientConfig& Config,
    const FString& HttpKey,
    const FString& TournamentId,
    const FNakamaWriteTournamentRecordRequestTournamentRecordWrite& Record,
    TFunction<void(const FNakamaLeaderboardRecord&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Write a record to a tournament.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param TournamentId	 The tournament ID to write the record for.
  * @param Record	 Record input.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  NAKAMAAPI_API void WriteTournamentRecord(
    const FNakamaClientConfig& Config,
    const FNakamaSession& Session,
    const FString& TournamentId,
    const FNakamaWriteTournamentRecordRequestTournamentRecordWrite& Record,
    TFunction<void(const FNakamaLeaderboardRecord&)> OnSuccess,
    TFunction<void(const FNakamaError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
}
