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

#include "NakamaApi.h"
#include "NakamaHttpHelper.h"

#include "Modules/ModuleManager.h"

DEFINE_LOG_CATEGORY(LogNakama);

using namespace NakamaHttpInternal;

void NakamaApi::AddFriends(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	FString Metadata,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/friend");
	TArray<FString> QueryParams;
	for (const FString& Item : Ids)
	{
		QueryParams.Add(FString::Printf(TEXT("ids=%s"), *Item));
	}
	for (const FString& Item : Usernames)
	{
		QueryParams.Add(FString::Printf(TEXT("usernames=%s"), *Item));
	}
	if (!Metadata.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("metadata=%s"), *Metadata));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::AddFriends(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	FString Metadata,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/friend");
	TArray<FString> QueryParams;
	for (const FString& Item : Ids)
	{
		QueryParams.Add(FString::Printf(TEXT("ids=%s"), *Item));
	}
	for (const FString& Item : Usernames)
	{
		QueryParams.Add(FString::Printf(TEXT("usernames=%s"), *Item));
	}
	if (!Metadata.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("metadata=%s"), *Metadata));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::AddGroupUsers(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString GroupId,
	const TArray<FString>& UserIds,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/group/{group_id}/add");
	Endpoint = Endpoint.Replace(TEXT("{group_id}"), *GroupId);
	TArray<FString> QueryParams;
	for (const FString& Item : UserIds)
	{
		QueryParams.Add(FString::Printf(TEXT("user_ids=%s"), *Item));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::AddGroupUsers(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString GroupId,
	const TArray<FString>& UserIds,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/group/{group_id}/add");
	Endpoint = Endpoint.Replace(TEXT("{group_id}"), *GroupId);
	TArray<FString> QueryParams;
	for (const FString& Item : UserIds)
	{
		QueryParams.Add(FString::Printf(TEXT("user_ids=%s"), *Item));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::SessionRefresh(
	const FNakamaClientConfig& Config,
	FString Token,
	const TMap<FString, FString>& Vars,
	TFunction<void(const FNakamaSession&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/session/refresh");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Basic;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Token.IsEmpty())
	{
		Body->SetStringField(TEXT("token"), Token);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, TEXT(""),
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaSession Result = FNakamaSession::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::SessionLogout(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString Token,
	FString RefreshToken,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/session/logout");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Token.IsEmpty())
	{
		Body->SetStringField(TEXT("token"), Token);
	}
	if (!RefreshToken.IsEmpty())
	{
		Body->SetStringField(TEXT("refresh_token"), RefreshToken);
	}

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::SessionLogout(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString Token,
	FString RefreshToken,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/session/logout");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Token.IsEmpty())
	{
		Body->SetStringField(TEXT("token"), Token);
	}
	if (!RefreshToken.IsEmpty())
	{
		Body->SetStringField(TEXT("refresh_token"), RefreshToken);
	}

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::AuthenticateApple(
	const FNakamaClientConfig& Config,
	FNakamaAccountApple Account,
	bool Create,
	FString Username,
	TFunction<void(const FNakamaSession&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/authenticate/apple");
	TArray<FString> QueryParams;
	QueryParams.Add(FString::Printf(TEXT("create=%s"), Create ? TEXT("true") : TEXT("false")));
	if (!Username.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("username=%s"), *Username));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Basic;TSharedPtr<FJsonObject> Body;
	Body = Account.ToJson();

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, TEXT(""),
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaSession Result = FNakamaSession::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::AuthenticateCustom(
	const FNakamaClientConfig& Config,
	FNakamaAccountCustom Account,
	bool Create,
	FString Username,
	TFunction<void(const FNakamaSession&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/authenticate/custom");
	TArray<FString> QueryParams;
	QueryParams.Add(FString::Printf(TEXT("create=%s"), Create ? TEXT("true") : TEXT("false")));
	if (!Username.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("username=%s"), *Username));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Basic;TSharedPtr<FJsonObject> Body;
	Body = Account.ToJson();

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, TEXT(""),
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaSession Result = FNakamaSession::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::AuthenticateDevice(
	const FNakamaClientConfig& Config,
	FNakamaAccountDevice Account,
	bool Create,
	FString Username,
	TFunction<void(const FNakamaSession&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/authenticate/device");
	TArray<FString> QueryParams;
	QueryParams.Add(FString::Printf(TEXT("create=%s"), Create ? TEXT("true") : TEXT("false")));
	if (!Username.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("username=%s"), *Username));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Basic;TSharedPtr<FJsonObject> Body;
	Body = Account.ToJson();

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, TEXT(""),
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaSession Result = FNakamaSession::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::AuthenticateEmail(
	const FNakamaClientConfig& Config,
	FNakamaAccountEmail Account,
	bool Create,
	FString Username,
	TFunction<void(const FNakamaSession&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/authenticate/email");
	TArray<FString> QueryParams;
	QueryParams.Add(FString::Printf(TEXT("create=%s"), Create ? TEXT("true") : TEXT("false")));
	if (!Username.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("username=%s"), *Username));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Basic;TSharedPtr<FJsonObject> Body;
	Body = Account.ToJson();

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, TEXT(""),
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaSession Result = FNakamaSession::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::AuthenticateFacebook(
	const FNakamaClientConfig& Config,
	FNakamaAccountFacebook Account,
	bool Create,
	FString Username,
	bool Sync,
	TFunction<void(const FNakamaSession&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/authenticate/facebook");
	TArray<FString> QueryParams;
	QueryParams.Add(FString::Printf(TEXT("create=%s"), Create ? TEXT("true") : TEXT("false")));
	if (!Username.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("username=%s"), *Username));
	}
	QueryParams.Add(FString::Printf(TEXT("sync=%s"), Sync ? TEXT("true") : TEXT("false")));
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Basic;TSharedPtr<FJsonObject> Body;
	Body = Account.ToJson();

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, TEXT(""),
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaSession Result = FNakamaSession::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::AuthenticateFacebookInstantGame(
	const FNakamaClientConfig& Config,
	FNakamaAccountFacebookInstantGame Account,
	bool Create,
	FString Username,
	TFunction<void(const FNakamaSession&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/authenticate/facebookinstantgame");
	TArray<FString> QueryParams;
	QueryParams.Add(FString::Printf(TEXT("create=%s"), Create ? TEXT("true") : TEXT("false")));
	if (!Username.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("username=%s"), *Username));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Basic;TSharedPtr<FJsonObject> Body;
	Body = Account.ToJson();

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, TEXT(""),
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaSession Result = FNakamaSession::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::AuthenticateGameCenter(
	const FNakamaClientConfig& Config,
	FNakamaAccountGameCenter Account,
	bool Create,
	FString Username,
	TFunction<void(const FNakamaSession&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/authenticate/gamecenter");
	TArray<FString> QueryParams;
	QueryParams.Add(FString::Printf(TEXT("create=%s"), Create ? TEXT("true") : TEXT("false")));
	if (!Username.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("username=%s"), *Username));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Basic;TSharedPtr<FJsonObject> Body;
	Body = Account.ToJson();

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, TEXT(""),
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaSession Result = FNakamaSession::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::AuthenticateGoogle(
	const FNakamaClientConfig& Config,
	FNakamaAccountGoogle Account,
	bool Create,
	FString Username,
	TFunction<void(const FNakamaSession&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/authenticate/google");
	TArray<FString> QueryParams;
	QueryParams.Add(FString::Printf(TEXT("create=%s"), Create ? TEXT("true") : TEXT("false")));
	if (!Username.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("username=%s"), *Username));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Basic;TSharedPtr<FJsonObject> Body;
	Body = Account.ToJson();

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, TEXT(""),
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaSession Result = FNakamaSession::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::AuthenticateSteam(
	const FNakamaClientConfig& Config,
	FNakamaAccountSteam Account,
	bool Create,
	FString Username,
	bool Sync,
	TFunction<void(const FNakamaSession&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/authenticate/steam");
	TArray<FString> QueryParams;
	QueryParams.Add(FString::Printf(TEXT("create=%s"), Create ? TEXT("true") : TEXT("false")));
	if (!Username.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("username=%s"), *Username));
	}
	QueryParams.Add(FString::Printf(TEXT("sync=%s"), Sync ? TEXT("true") : TEXT("false")));
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Basic;TSharedPtr<FJsonObject> Body;
	Body = Account.ToJson();

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, TEXT(""),
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaSession Result = FNakamaSession::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::BanGroupUsers(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString GroupId,
	const TArray<FString>& UserIds,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/group/{group_id}/ban");
	Endpoint = Endpoint.Replace(TEXT("{group_id}"), *GroupId);
	TArray<FString> QueryParams;
	for (const FString& Item : UserIds)
	{
		QueryParams.Add(FString::Printf(TEXT("user_ids=%s"), *Item));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::BanGroupUsers(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString GroupId,
	const TArray<FString>& UserIds,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/group/{group_id}/ban");
	Endpoint = Endpoint.Replace(TEXT("{group_id}"), *GroupId);
	TArray<FString> QueryParams;
	for (const FString& Item : UserIds)
	{
		QueryParams.Add(FString::Printf(TEXT("user_ids=%s"), *Item));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::BlockFriends(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/friend/block");
	TArray<FString> QueryParams;
	for (const FString& Item : Ids)
	{
		QueryParams.Add(FString::Printf(TEXT("ids=%s"), *Item));
	}
	for (const FString& Item : Usernames)
	{
		QueryParams.Add(FString::Printf(TEXT("usernames=%s"), *Item));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::BlockFriends(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/friend/block");
	TArray<FString> QueryParams;
	for (const FString& Item : Ids)
	{
		QueryParams.Add(FString::Printf(TEXT("ids=%s"), *Item));
	}
	for (const FString& Item : Usernames)
	{
		QueryParams.Add(FString::Printf(TEXT("usernames=%s"), *Item));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::CreateGroup(
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
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/group");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Name.IsEmpty())
	{
		Body->SetStringField(TEXT("name"), Name);
	}
	if (!Description.IsEmpty())
	{
		Body->SetStringField(TEXT("description"), Description);
	}
	if (!LangTag.IsEmpty())
	{
		Body->SetStringField(TEXT("lang_tag"), LangTag);
	}
	if (!AvatarUrl.IsEmpty())
	{
		Body->SetStringField(TEXT("avatar_url"), AvatarUrl);
	}
	Body->SetBoolField(TEXT("open"), Open);
	Body->SetNumberField(TEXT("max_count"), MaxCount);

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaGroup Result = FNakamaGroup::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::CreateGroup(
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
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/group");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Name.IsEmpty())
	{
		Body->SetStringField(TEXT("name"), Name);
	}
	if (!Description.IsEmpty())
	{
		Body->SetStringField(TEXT("description"), Description);
	}
	if (!LangTag.IsEmpty())
	{
		Body->SetStringField(TEXT("lang_tag"), LangTag);
	}
	if (!AvatarUrl.IsEmpty())
	{
		Body->SetStringField(TEXT("avatar_url"), AvatarUrl);
	}
	Body->SetBoolField(TEXT("open"), Open);
	Body->SetNumberField(TEXT("max_count"), MaxCount);

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaGroup Result = FNakamaGroup::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::DeleteAccount(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account");

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("DELETE"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::DeleteAccount(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account");TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("DELETE"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::DeleteFriends(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/friend");
	TArray<FString> QueryParams;
	for (const FString& Item : Ids)
	{
		QueryParams.Add(FString::Printf(TEXT("ids=%s"), *Item));
	}
	for (const FString& Item : Usernames)
	{
		QueryParams.Add(FString::Printf(TEXT("usernames=%s"), *Item));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("DELETE"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::DeleteFriends(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/friend");
	TArray<FString> QueryParams;
	for (const FString& Item : Ids)
	{
		QueryParams.Add(FString::Printf(TEXT("ids=%s"), *Item));
	}
	for (const FString& Item : Usernames)
	{
		QueryParams.Add(FString::Printf(TEXT("usernames=%s"), *Item));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("DELETE"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::DeleteGroup(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString GroupId,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/group/{group_id}");
	Endpoint = Endpoint.Replace(TEXT("{group_id}"), *GroupId);
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("DELETE"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::DeleteGroup(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString GroupId,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/group/{group_id}");
	Endpoint = Endpoint.Replace(TEXT("{group_id}"), *GroupId);
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("DELETE"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::DeleteLeaderboardRecord(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString LeaderboardId,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/leaderboard/{leaderboard_id}");
	Endpoint = Endpoint.Replace(TEXT("{leaderboard_id}"), *LeaderboardId);
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("DELETE"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::DeleteLeaderboardRecord(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString LeaderboardId,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/leaderboard/{leaderboard_id}");
	Endpoint = Endpoint.Replace(TEXT("{leaderboard_id}"), *LeaderboardId);
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("DELETE"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::DeleteNotifications(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	const TArray<FString>& Ids,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/notification");
	TArray<FString> QueryParams;
	for (const FString& Item : Ids)
	{
		QueryParams.Add(FString::Printf(TEXT("ids=%s"), *Item));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("DELETE"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::DeleteNotifications(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	const TArray<FString>& Ids,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/notification");
	TArray<FString> QueryParams;
	for (const FString& Item : Ids)
	{
		QueryParams.Add(FString::Printf(TEXT("ids=%s"), *Item));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("DELETE"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::DeleteTournamentRecord(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString TournamentId,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/tournament/{tournament_id}");
	Endpoint = Endpoint.Replace(TEXT("{tournament_id}"), *TournamentId);
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("DELETE"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::DeleteTournamentRecord(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString TournamentId,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/tournament/{tournament_id}");
	Endpoint = Endpoint.Replace(TEXT("{tournament_id}"), *TournamentId);
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("DELETE"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::DeleteStorageObjects(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	const TArray<FNakamaDeleteStorageObjectId>& ObjectIds,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/storage/delete");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (ObjectIds.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : ObjectIds)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Body->SetArrayField(TEXT("object_ids"), Array);
	}

	MakeRequest(Config, Endpoint, TEXT("PUT"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::DeleteStorageObjects(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	const TArray<FNakamaDeleteStorageObjectId>& ObjectIds,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/storage/delete");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (ObjectIds.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : ObjectIds)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Body->SetArrayField(TEXT("object_ids"), Array);
	}

	MakeRequest(Config, Endpoint, TEXT("PUT"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::Event(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString Name,
	FString Timestamp,
	bool External,
	const TMap<FString, FString>& Properties,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/event");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Name.IsEmpty())
	{
		Body->SetStringField(TEXT("name"), Name);
	}
	Body->SetStringField(TEXT("timestamp"), Timestamp);
	Body->SetBoolField(TEXT("external"), External);
	if (Properties.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Properties)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("properties"), MapObj);
	}

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::Event(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString Name,
	FString Timestamp,
	bool External,
	const TMap<FString, FString>& Properties,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/event");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Name.IsEmpty())
	{
		Body->SetStringField(TEXT("name"), Name);
	}
	Body->SetStringField(TEXT("timestamp"), Timestamp);
	Body->SetBoolField(TEXT("external"), External);
	if (Properties.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Properties)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("properties"), MapObj);
	}

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::GetAccount(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	TFunction<void(const FNakamaAccount&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account");

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaAccount Result = FNakamaAccount::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::GetAccount(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	TFunction<void(const FNakamaAccount&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account");TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaAccount Result = FNakamaAccount::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::GetUsers(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	const TArray<FString>& FacebookIds,
	TFunction<void(const FNakamaUsers&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/user");
	TArray<FString> QueryParams;
	for (const FString& Item : Ids)
	{
		QueryParams.Add(FString::Printf(TEXT("ids=%s"), *Item));
	}
	for (const FString& Item : Usernames)
	{
		QueryParams.Add(FString::Printf(TEXT("usernames=%s"), *Item));
	}
	for (const FString& Item : FacebookIds)
	{
		QueryParams.Add(FString::Printf(TEXT("facebook_ids=%s"), *Item));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaUsers Result = FNakamaUsers::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::GetUsers(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	const TArray<FString>& FacebookIds,
	TFunction<void(const FNakamaUsers&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/user");
	TArray<FString> QueryParams;
	for (const FString& Item : Ids)
	{
		QueryParams.Add(FString::Printf(TEXT("ids=%s"), *Item));
	}
	for (const FString& Item : Usernames)
	{
		QueryParams.Add(FString::Printf(TEXT("usernames=%s"), *Item));
	}
	for (const FString& Item : FacebookIds)
	{
		QueryParams.Add(FString::Printf(TEXT("facebook_ids=%s"), *Item));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaUsers Result = FNakamaUsers::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::GetSubscription(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString ProductId,
	TFunction<void(const FNakamaValidatedSubscription&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/iap/subscription/{product_id}");
	Endpoint = Endpoint.Replace(TEXT("{product_id}"), *ProductId);
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaValidatedSubscription Result = FNakamaValidatedSubscription::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::GetSubscription(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString ProductId,
	TFunction<void(const FNakamaValidatedSubscription&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/iap/subscription/{product_id}");
	Endpoint = Endpoint.Replace(TEXT("{product_id}"), *ProductId);
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaValidatedSubscription Result = FNakamaValidatedSubscription::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::GetMatchmakerStats(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	TFunction<void(const FNakamaMatchmakerStats&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/matchmaker/stats");

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaMatchmakerStats Result = FNakamaMatchmakerStats::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::GetMatchmakerStats(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	TFunction<void(const FNakamaMatchmakerStats&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/matchmaker/stats");TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaMatchmakerStats Result = FNakamaMatchmakerStats::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::Healthcheck(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/healthcheck");

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::Healthcheck(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/healthcheck");TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ImportFacebookFriends(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FNakamaAccountFacebook Account,
	bool Reset,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/friend/facebook");
	TArray<FString> QueryParams;
	QueryParams.Add(FString::Printf(TEXT("reset=%s"), Reset ? TEXT("true") : TEXT("false")));
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = Account.ToJson();

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ImportFacebookFriends(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FNakamaAccountFacebook Account,
	bool Reset,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/friend/facebook");
	TArray<FString> QueryParams;
	QueryParams.Add(FString::Printf(TEXT("reset=%s"), Reset ? TEXT("true") : TEXT("false")));
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = Account.ToJson();

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ImportSteamFriends(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FNakamaAccountSteam Account,
	bool Reset,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/friend/steam");
	TArray<FString> QueryParams;
	QueryParams.Add(FString::Printf(TEXT("reset=%s"), Reset ? TEXT("true") : TEXT("false")));
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = Account.ToJson();

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ImportSteamFriends(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FNakamaAccountSteam Account,
	bool Reset,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/friend/steam");
	TArray<FString> QueryParams;
	QueryParams.Add(FString::Printf(TEXT("reset=%s"), Reset ? TEXT("true") : TEXT("false")));
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = Account.ToJson();

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::JoinGroup(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString GroupId,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/group/{group_id}/join");
	Endpoint = Endpoint.Replace(TEXT("{group_id}"), *GroupId);
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::JoinGroup(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString GroupId,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/group/{group_id}/join");
	Endpoint = Endpoint.Replace(TEXT("{group_id}"), *GroupId);
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::JoinTournament(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString TournamentId,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/tournament/{tournament_id}/join");
	Endpoint = Endpoint.Replace(TEXT("{tournament_id}"), *TournamentId);
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::JoinTournament(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString TournamentId,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/tournament/{tournament_id}/join");
	Endpoint = Endpoint.Replace(TEXT("{tournament_id}"), *TournamentId);
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::KickGroupUsers(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString GroupId,
	const TArray<FString>& UserIds,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/group/{group_id}/kick");
	Endpoint = Endpoint.Replace(TEXT("{group_id}"), *GroupId);
	TArray<FString> QueryParams;
	for (const FString& Item : UserIds)
	{
		QueryParams.Add(FString::Printf(TEXT("user_ids=%s"), *Item));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::KickGroupUsers(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString GroupId,
	const TArray<FString>& UserIds,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/group/{group_id}/kick");
	Endpoint = Endpoint.Replace(TEXT("{group_id}"), *GroupId);
	TArray<FString> QueryParams;
	for (const FString& Item : UserIds)
	{
		QueryParams.Add(FString::Printf(TEXT("user_ids=%s"), *Item));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::LeaveGroup(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString GroupId,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/group/{group_id}/leave");
	Endpoint = Endpoint.Replace(TEXT("{group_id}"), *GroupId);
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::LeaveGroup(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString GroupId,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/group/{group_id}/leave");
	Endpoint = Endpoint.Replace(TEXT("{group_id}"), *GroupId);
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::LinkApple(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString Token,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/link/apple");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Token.IsEmpty())
	{
		Body->SetStringField(TEXT("token"), Token);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::LinkApple(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString Token,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/link/apple");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Token.IsEmpty())
	{
		Body->SetStringField(TEXT("token"), Token);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::LinkCustom(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString Id,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/link/custom");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Id.IsEmpty())
	{
		Body->SetStringField(TEXT("id"), Id);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::LinkCustom(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString Id,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/link/custom");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Id.IsEmpty())
	{
		Body->SetStringField(TEXT("id"), Id);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::LinkDevice(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString Id,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/link/device");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Id.IsEmpty())
	{
		Body->SetStringField(TEXT("id"), Id);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::LinkDevice(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString Id,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/link/device");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Id.IsEmpty())
	{
		Body->SetStringField(TEXT("id"), Id);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::LinkEmail(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString Email,
	FString Password,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/link/email");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Email.IsEmpty())
	{
		Body->SetStringField(TEXT("email"), Email);
	}
	if (!Password.IsEmpty())
	{
		Body->SetStringField(TEXT("password"), Password);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::LinkEmail(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString Email,
	FString Password,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/link/email");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Email.IsEmpty())
	{
		Body->SetStringField(TEXT("email"), Email);
	}
	if (!Password.IsEmpty())
	{
		Body->SetStringField(TEXT("password"), Password);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::LinkFacebook(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FNakamaAccountFacebook Account,
	bool Sync,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/link/facebook");
	TArray<FString> QueryParams;
	QueryParams.Add(FString::Printf(TEXT("sync=%s"), Sync ? TEXT("true") : TEXT("false")));
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = Account.ToJson();

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::LinkFacebook(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FNakamaAccountFacebook Account,
	bool Sync,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/link/facebook");
	TArray<FString> QueryParams;
	QueryParams.Add(FString::Printf(TEXT("sync=%s"), Sync ? TEXT("true") : TEXT("false")));
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = Account.ToJson();

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::LinkFacebookInstantGame(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString SignedPlayerInfo,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/link/facebookinstantgame");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!SignedPlayerInfo.IsEmpty())
	{
		Body->SetStringField(TEXT("signed_player_info"), SignedPlayerInfo);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::LinkFacebookInstantGame(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString SignedPlayerInfo,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/link/facebookinstantgame");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!SignedPlayerInfo.IsEmpty())
	{
		Body->SetStringField(TEXT("signed_player_info"), SignedPlayerInfo);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::LinkGameCenter(
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
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/link/gamecenter");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!PlayerId.IsEmpty())
	{
		Body->SetStringField(TEXT("player_id"), PlayerId);
	}
	if (!BundleId.IsEmpty())
	{
		Body->SetStringField(TEXT("bundle_id"), BundleId);
	}
	Body->SetNumberField(TEXT("timestamp_seconds"), TimestampSeconds);
	if (!Salt.IsEmpty())
	{
		Body->SetStringField(TEXT("salt"), Salt);
	}
	if (!Signature.IsEmpty())
	{
		Body->SetStringField(TEXT("signature"), Signature);
	}
	if (!PublicKeyUrl.IsEmpty())
	{
		Body->SetStringField(TEXT("public_key_url"), PublicKeyUrl);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::LinkGameCenter(
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
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/link/gamecenter");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!PlayerId.IsEmpty())
	{
		Body->SetStringField(TEXT("player_id"), PlayerId);
	}
	if (!BundleId.IsEmpty())
	{
		Body->SetStringField(TEXT("bundle_id"), BundleId);
	}
	Body->SetNumberField(TEXT("timestamp_seconds"), TimestampSeconds);
	if (!Salt.IsEmpty())
	{
		Body->SetStringField(TEXT("salt"), Salt);
	}
	if (!Signature.IsEmpty())
	{
		Body->SetStringField(TEXT("signature"), Signature);
	}
	if (!PublicKeyUrl.IsEmpty())
	{
		Body->SetStringField(TEXT("public_key_url"), PublicKeyUrl);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::LinkGoogle(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString Token,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/link/google");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Token.IsEmpty())
	{
		Body->SetStringField(TEXT("token"), Token);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::LinkGoogle(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString Token,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/link/google");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Token.IsEmpty())
	{
		Body->SetStringField(TEXT("token"), Token);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::LinkSteam(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FNakamaAccountSteam Account,
	bool Sync,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/link/steam");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	Body->SetObjectField(TEXT("account"), Account.ToJson());
	Body->SetBoolField(TEXT("sync"), Sync);

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::LinkSteam(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FNakamaAccountSteam Account,
	bool Sync,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/link/steam");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	Body->SetObjectField(TEXT("account"), Account.ToJson());
	Body->SetBoolField(TEXT("sync"), Sync);

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ListChannelMessages(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString ChannelId,
	int32 Limit,
	bool Forward,
	FString Cursor,
	TFunction<void(const FNakamaChannelMessageList&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/channel/{channel_id}");
	Endpoint = Endpoint.Replace(TEXT("{channel_id}"), *ChannelId);
	TArray<FString> QueryParams;
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	QueryParams.Add(FString::Printf(TEXT("forward=%s"), Forward ? TEXT("true") : TEXT("false")));
	if (!Cursor.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("cursor=%s"), *Cursor));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaChannelMessageList Result = FNakamaChannelMessageList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ListChannelMessages(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString ChannelId,
	int32 Limit,
	bool Forward,
	FString Cursor,
	TFunction<void(const FNakamaChannelMessageList&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/channel/{channel_id}");
	Endpoint = Endpoint.Replace(TEXT("{channel_id}"), *ChannelId);
	TArray<FString> QueryParams;
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	QueryParams.Add(FString::Printf(TEXT("forward=%s"), Forward ? TEXT("true") : TEXT("false")));
	if (!Cursor.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("cursor=%s"), *Cursor));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaChannelMessageList Result = FNakamaChannelMessageList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ListFriends(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	int32 Limit,
	int32 State,
	FString Cursor,
	TFunction<void(const FNakamaFriendList&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/friend");
	TArray<FString> QueryParams;
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	if (State != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("state=%d"), State));
	}
	if (!Cursor.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("cursor=%s"), *Cursor));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaFriendList Result = FNakamaFriendList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ListFriends(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	int32 Limit,
	int32 State,
	FString Cursor,
	TFunction<void(const FNakamaFriendList&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/friend");
	TArray<FString> QueryParams;
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	if (State != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("state=%d"), State));
	}
	if (!Cursor.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("cursor=%s"), *Cursor));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaFriendList Result = FNakamaFriendList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ListFriendsOfFriends(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	int32 Limit,
	FString Cursor,
	TFunction<void(const FNakamaFriendsOfFriendsList&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/friend/friends");
	TArray<FString> QueryParams;
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	if (!Cursor.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("cursor=%s"), *Cursor));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaFriendsOfFriendsList Result = FNakamaFriendsOfFriendsList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ListFriendsOfFriends(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	int32 Limit,
	FString Cursor,
	TFunction<void(const FNakamaFriendsOfFriendsList&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/friend/friends");
	TArray<FString> QueryParams;
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	if (!Cursor.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("cursor=%s"), *Cursor));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaFriendsOfFriendsList Result = FNakamaFriendsOfFriendsList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ListGroups(
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
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/group");
	TArray<FString> QueryParams;
	if (!Name.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("name=%s"), *Name));
	}
	if (!Cursor.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("cursor=%s"), *Cursor));
	}
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	if (!LangTag.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("lang_tag=%s"), *LangTag));
	}
	if (Members != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("members=%d"), Members));
	}
	QueryParams.Add(FString::Printf(TEXT("open=%s"), Open ? TEXT("true") : TEXT("false")));
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaGroupList Result = FNakamaGroupList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ListGroups(
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
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/group");
	TArray<FString> QueryParams;
	if (!Name.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("name=%s"), *Name));
	}
	if (!Cursor.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("cursor=%s"), *Cursor));
	}
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	if (!LangTag.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("lang_tag=%s"), *LangTag));
	}
	if (Members != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("members=%d"), Members));
	}
	QueryParams.Add(FString::Printf(TEXT("open=%s"), Open ? TEXT("true") : TEXT("false")));
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaGroupList Result = FNakamaGroupList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ListGroupUsers(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString GroupId,
	int32 Limit,
	int32 State,
	FString Cursor,
	TFunction<void(const FNakamaGroupUserList&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/group/{group_id}/user");
	Endpoint = Endpoint.Replace(TEXT("{group_id}"), *GroupId);
	TArray<FString> QueryParams;
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	if (State != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("state=%d"), State));
	}
	if (!Cursor.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("cursor=%s"), *Cursor));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaGroupUserList Result = FNakamaGroupUserList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ListGroupUsers(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString GroupId,
	int32 Limit,
	int32 State,
	FString Cursor,
	TFunction<void(const FNakamaGroupUserList&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/group/{group_id}/user");
	Endpoint = Endpoint.Replace(TEXT("{group_id}"), *GroupId);
	TArray<FString> QueryParams;
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	if (State != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("state=%d"), State));
	}
	if (!Cursor.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("cursor=%s"), *Cursor));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaGroupUserList Result = FNakamaGroupUserList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ListLeaderboardRecords(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString LeaderboardId,
	const TArray<FString>& OwnerIds,
	int32 Limit,
	FString Cursor,
	int64 Expiry,
	TFunction<void(const FNakamaLeaderboardRecordList&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/leaderboard/{leaderboard_id}");
	Endpoint = Endpoint.Replace(TEXT("{leaderboard_id}"), *LeaderboardId);
	TArray<FString> QueryParams;
	for (const FString& Item : OwnerIds)
	{
		QueryParams.Add(FString::Printf(TEXT("owner_ids=%s"), *Item));
	}
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	if (!Cursor.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("cursor=%s"), *Cursor));
	}
	if (Expiry != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("expiry=%lld"), Expiry));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaLeaderboardRecordList Result = FNakamaLeaderboardRecordList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ListLeaderboardRecords(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString LeaderboardId,
	const TArray<FString>& OwnerIds,
	int32 Limit,
	FString Cursor,
	int64 Expiry,
	TFunction<void(const FNakamaLeaderboardRecordList&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/leaderboard/{leaderboard_id}");
	Endpoint = Endpoint.Replace(TEXT("{leaderboard_id}"), *LeaderboardId);
	TArray<FString> QueryParams;
	for (const FString& Item : OwnerIds)
	{
		QueryParams.Add(FString::Printf(TEXT("owner_ids=%s"), *Item));
	}
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	if (!Cursor.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("cursor=%s"), *Cursor));
	}
	if (Expiry != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("expiry=%lld"), Expiry));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaLeaderboardRecordList Result = FNakamaLeaderboardRecordList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ListLeaderboardRecordsAroundOwner(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString LeaderboardId,
	int32 Limit,
	FString OwnerId,
	int64 Expiry,
	FString Cursor,
	TFunction<void(const FNakamaLeaderboardRecordList&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/leaderboard/{leaderboard_id}/owner/{owner_id}");
	Endpoint = Endpoint.Replace(TEXT("{leaderboard_id}"), *LeaderboardId);
	Endpoint = Endpoint.Replace(TEXT("{owner_id}"), *OwnerId);
	TArray<FString> QueryParams;
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	if (Expiry != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("expiry=%lld"), Expiry));
	}
	if (!Cursor.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("cursor=%s"), *Cursor));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaLeaderboardRecordList Result = FNakamaLeaderboardRecordList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ListLeaderboardRecordsAroundOwner(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString LeaderboardId,
	int32 Limit,
	FString OwnerId,
	int64 Expiry,
	FString Cursor,
	TFunction<void(const FNakamaLeaderboardRecordList&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/leaderboard/{leaderboard_id}/owner/{owner_id}");
	Endpoint = Endpoint.Replace(TEXT("{leaderboard_id}"), *LeaderboardId);
	Endpoint = Endpoint.Replace(TEXT("{owner_id}"), *OwnerId);
	TArray<FString> QueryParams;
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	if (Expiry != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("expiry=%lld"), Expiry));
	}
	if (!Cursor.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("cursor=%s"), *Cursor));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaLeaderboardRecordList Result = FNakamaLeaderboardRecordList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ListMatches(
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
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/match");
	TArray<FString> QueryParams;
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	QueryParams.Add(FString::Printf(TEXT("authoritative=%s"), Authoritative ? TEXT("true") : TEXT("false")));
	if (!Label.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("label=%s"), *Label));
	}
	if (MinSize != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("min_size=%d"), MinSize));
	}
	if (MaxSize != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("max_size=%d"), MaxSize));
	}
	if (!Query.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("query=%s"), *Query));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaMatchList Result = FNakamaMatchList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ListMatches(
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
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/match");
	TArray<FString> QueryParams;
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	QueryParams.Add(FString::Printf(TEXT("authoritative=%s"), Authoritative ? TEXT("true") : TEXT("false")));
	if (!Label.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("label=%s"), *Label));
	}
	if (MinSize != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("min_size=%d"), MinSize));
	}
	if (MaxSize != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("max_size=%d"), MaxSize));
	}
	if (!Query.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("query=%s"), *Query));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaMatchList Result = FNakamaMatchList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ListParties(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	int32 Limit,
	bool Open,
	FString Query,
	FString Cursor,
	TFunction<void(const FNakamaPartyList&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/party");
	TArray<FString> QueryParams;
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	QueryParams.Add(FString::Printf(TEXT("open=%s"), Open ? TEXT("true") : TEXT("false")));
	if (!Query.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("query=%s"), *Query));
	}
	if (!Cursor.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("cursor=%s"), *Cursor));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaPartyList Result = FNakamaPartyList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ListParties(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	int32 Limit,
	bool Open,
	FString Query,
	FString Cursor,
	TFunction<void(const FNakamaPartyList&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/party");
	TArray<FString> QueryParams;
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	QueryParams.Add(FString::Printf(TEXT("open=%s"), Open ? TEXT("true") : TEXT("false")));
	if (!Query.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("query=%s"), *Query));
	}
	if (!Cursor.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("cursor=%s"), *Cursor));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaPartyList Result = FNakamaPartyList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ListNotifications(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	int32 Limit,
	FString CacheableCursor,
	TFunction<void(const FNakamaNotificationList&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/notification");
	TArray<FString> QueryParams;
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	if (!CacheableCursor.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("cacheable_cursor=%s"), *CacheableCursor));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaNotificationList Result = FNakamaNotificationList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ListNotifications(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	int32 Limit,
	FString CacheableCursor,
	TFunction<void(const FNakamaNotificationList&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/notification");
	TArray<FString> QueryParams;
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	if (!CacheableCursor.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("cacheable_cursor=%s"), *CacheableCursor));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaNotificationList Result = FNakamaNotificationList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ListStorageObjects(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString UserId,
	FString Collection,
	int32 Limit,
	FString Cursor,
	TFunction<void(const FNakamaStorageObjectList&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/storage/{collection}");
	Endpoint = Endpoint.Replace(TEXT("{collection}"), *Collection);
	TArray<FString> QueryParams;
	if (!UserId.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("user_id=%s"), *UserId));
	}
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	if (!Cursor.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("cursor=%s"), *Cursor));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaStorageObjectList Result = FNakamaStorageObjectList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ListStorageObjects(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString UserId,
	FString Collection,
	int32 Limit,
	FString Cursor,
	TFunction<void(const FNakamaStorageObjectList&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/storage/{collection}");
	Endpoint = Endpoint.Replace(TEXT("{collection}"), *Collection);
	TArray<FString> QueryParams;
	if (!UserId.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("user_id=%s"), *UserId));
	}
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	if (!Cursor.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("cursor=%s"), *Cursor));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaStorageObjectList Result = FNakamaStorageObjectList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ListSubscriptions(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	int32 Limit,
	FString Cursor,
	TFunction<void(const FNakamaSubscriptionList&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/iap/subscription");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	Body->SetNumberField(TEXT("limit"), Limit);
	if (!Cursor.IsEmpty())
	{
		Body->SetStringField(TEXT("cursor"), Cursor);
	}

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaSubscriptionList Result = FNakamaSubscriptionList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ListSubscriptions(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	int32 Limit,
	FString Cursor,
	TFunction<void(const FNakamaSubscriptionList&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/iap/subscription");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	Body->SetNumberField(TEXT("limit"), Limit);
	if (!Cursor.IsEmpty())
	{
		Body->SetStringField(TEXT("cursor"), Cursor);
	}

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaSubscriptionList Result = FNakamaSubscriptionList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ListTournaments(
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
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/tournament");
	TArray<FString> QueryParams;
	if (CategoryStart != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("category_start=%d"), CategoryStart));
	}
	if (CategoryEnd != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("category_end=%d"), CategoryEnd));
	}
	if (StartTime != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("start_time=%d"), StartTime));
	}
	if (EndTime != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("end_time=%d"), EndTime));
	}
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	if (!Cursor.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("cursor=%s"), *Cursor));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaTournamentList Result = FNakamaTournamentList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ListTournaments(
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
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/tournament");
	TArray<FString> QueryParams;
	if (CategoryStart != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("category_start=%d"), CategoryStart));
	}
	if (CategoryEnd != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("category_end=%d"), CategoryEnd));
	}
	if (StartTime != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("start_time=%d"), StartTime));
	}
	if (EndTime != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("end_time=%d"), EndTime));
	}
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	if (!Cursor.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("cursor=%s"), *Cursor));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaTournamentList Result = FNakamaTournamentList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ListTournamentRecords(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString TournamentId,
	const TArray<FString>& OwnerIds,
	int32 Limit,
	FString Cursor,
	int64 Expiry,
	TFunction<void(const FNakamaTournamentRecordList&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/tournament/{tournament_id}");
	Endpoint = Endpoint.Replace(TEXT("{tournament_id}"), *TournamentId);
	TArray<FString> QueryParams;
	for (const FString& Item : OwnerIds)
	{
		QueryParams.Add(FString::Printf(TEXT("owner_ids=%s"), *Item));
	}
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	if (!Cursor.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("cursor=%s"), *Cursor));
	}
	if (Expiry != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("expiry=%lld"), Expiry));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaTournamentRecordList Result = FNakamaTournamentRecordList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ListTournamentRecords(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString TournamentId,
	const TArray<FString>& OwnerIds,
	int32 Limit,
	FString Cursor,
	int64 Expiry,
	TFunction<void(const FNakamaTournamentRecordList&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/tournament/{tournament_id}");
	Endpoint = Endpoint.Replace(TEXT("{tournament_id}"), *TournamentId);
	TArray<FString> QueryParams;
	for (const FString& Item : OwnerIds)
	{
		QueryParams.Add(FString::Printf(TEXT("owner_ids=%s"), *Item));
	}
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	if (!Cursor.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("cursor=%s"), *Cursor));
	}
	if (Expiry != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("expiry=%lld"), Expiry));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaTournamentRecordList Result = FNakamaTournamentRecordList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ListTournamentRecordsAroundOwner(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString TournamentId,
	int32 Limit,
	FString OwnerId,
	int64 Expiry,
	FString Cursor,
	TFunction<void(const FNakamaTournamentRecordList&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/tournament/{tournament_id}/owner/{owner_id}");
	Endpoint = Endpoint.Replace(TEXT("{tournament_id}"), *TournamentId);
	Endpoint = Endpoint.Replace(TEXT("{owner_id}"), *OwnerId);
	TArray<FString> QueryParams;
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	if (Expiry != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("expiry=%lld"), Expiry));
	}
	if (!Cursor.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("cursor=%s"), *Cursor));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaTournamentRecordList Result = FNakamaTournamentRecordList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ListTournamentRecordsAroundOwner(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString TournamentId,
	int32 Limit,
	FString OwnerId,
	int64 Expiry,
	FString Cursor,
	TFunction<void(const FNakamaTournamentRecordList&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/tournament/{tournament_id}/owner/{owner_id}");
	Endpoint = Endpoint.Replace(TEXT("{tournament_id}"), *TournamentId);
	Endpoint = Endpoint.Replace(TEXT("{owner_id}"), *OwnerId);
	TArray<FString> QueryParams;
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	if (Expiry != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("expiry=%lld"), Expiry));
	}
	if (!Cursor.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("cursor=%s"), *Cursor));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaTournamentRecordList Result = FNakamaTournamentRecordList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ListUserGroups(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString UserId,
	int32 Limit,
	int32 State,
	FString Cursor,
	TFunction<void(const FNakamaUserGroupList&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/user/{user_id}/group");
	Endpoint = Endpoint.Replace(TEXT("{user_id}"), *UserId);
	TArray<FString> QueryParams;
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	if (State != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("state=%d"), State));
	}
	if (!Cursor.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("cursor=%s"), *Cursor));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaUserGroupList Result = FNakamaUserGroupList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ListUserGroups(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString UserId,
	int32 Limit,
	int32 State,
	FString Cursor,
	TFunction<void(const FNakamaUserGroupList&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/user/{user_id}/group");
	Endpoint = Endpoint.Replace(TEXT("{user_id}"), *UserId);
	TArray<FString> QueryParams;
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	if (State != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("state=%d"), State));
	}
	if (!Cursor.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("cursor=%s"), *Cursor));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaUserGroupList Result = FNakamaUserGroupList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::PromoteGroupUsers(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString GroupId,
	const TArray<FString>& UserIds,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/group/{group_id}/promote");
	Endpoint = Endpoint.Replace(TEXT("{group_id}"), *GroupId);
	TArray<FString> QueryParams;
	for (const FString& Item : UserIds)
	{
		QueryParams.Add(FString::Printf(TEXT("user_ids=%s"), *Item));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::PromoteGroupUsers(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString GroupId,
	const TArray<FString>& UserIds,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/group/{group_id}/promote");
	Endpoint = Endpoint.Replace(TEXT("{group_id}"), *GroupId);
	TArray<FString> QueryParams;
	for (const FString& Item : UserIds)
	{
		QueryParams.Add(FString::Printf(TEXT("user_ids=%s"), *Item));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::DemoteGroupUsers(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString GroupId,
	const TArray<FString>& UserIds,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/group/{group_id}/demote");
	Endpoint = Endpoint.Replace(TEXT("{group_id}"), *GroupId);
	TArray<FString> QueryParams;
	for (const FString& Item : UserIds)
	{
		QueryParams.Add(FString::Printf(TEXT("user_ids=%s"), *Item));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::DemoteGroupUsers(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString GroupId,
	const TArray<FString>& UserIds,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/group/{group_id}/demote");
	Endpoint = Endpoint.Replace(TEXT("{group_id}"), *GroupId);
	TArray<FString> QueryParams;
	for (const FString& Item : UserIds)
	{
		QueryParams.Add(FString::Printf(TEXT("user_ids=%s"), *Item));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ReadStorageObjects(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	const TArray<FNakamaReadStorageObjectId>& ObjectIds,
	TFunction<void(const FNakamaStorageObjects&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/storage");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (ObjectIds.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : ObjectIds)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Body->SetArrayField(TEXT("object_ids"), Array);
	}

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaStorageObjects Result = FNakamaStorageObjects::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ReadStorageObjects(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	const TArray<FNakamaReadStorageObjectId>& ObjectIds,
	TFunction<void(const FNakamaStorageObjects&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/storage");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (ObjectIds.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : ObjectIds)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Body->SetArrayField(TEXT("object_ids"), Array);
	}

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaStorageObjects Result = FNakamaStorageObjects::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::RpcFunc(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString Id,
	TSharedPtr<FJsonObject> Payload,
	FString HttpKey,
	TFunction<void(const FNakamaRpc&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/rpc/{id}");
	Endpoint = Endpoint.Replace(TEXT("{id}"), *Id);
	TArray<FString> QueryParams;
	if (!HttpKey.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("http_key=%s"), *HttpKey));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	FString BodyString;
	if (Payload.IsValid())
	{
		BodyString = SerializeJsonEscaped(Payload);
	}

	SendRequest(Config, Endpoint, TEXT("POST"), BodyString, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaRpc Result = FNakamaRpc::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::RpcFunc(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString Id,
	TSharedPtr<FJsonObject> Payload,
	TFunction<void(const FNakamaRpc&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/rpc/{id}");
	Endpoint = Endpoint.Replace(TEXT("{id}"), *Id);
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	FString BodyString;
	if (Payload.IsValid())
	{
		BodyString = SerializeJsonEscaped(Payload);
	}

	SendRequest(Config, Endpoint, TEXT("POST"), BodyString, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaRpc Result = FNakamaRpc::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::UnlinkApple(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString Token,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/unlink/apple");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Token.IsEmpty())
	{
		Body->SetStringField(TEXT("token"), Token);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::UnlinkApple(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString Token,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/unlink/apple");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Token.IsEmpty())
	{
		Body->SetStringField(TEXT("token"), Token);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::UnlinkCustom(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString Id,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/unlink/custom");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Id.IsEmpty())
	{
		Body->SetStringField(TEXT("id"), Id);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::UnlinkCustom(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString Id,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/unlink/custom");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Id.IsEmpty())
	{
		Body->SetStringField(TEXT("id"), Id);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::UnlinkDevice(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString Id,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/unlink/device");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Id.IsEmpty())
	{
		Body->SetStringField(TEXT("id"), Id);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::UnlinkDevice(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString Id,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/unlink/device");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Id.IsEmpty())
	{
		Body->SetStringField(TEXT("id"), Id);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::UnlinkEmail(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString Email,
	FString Password,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/unlink/email");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Email.IsEmpty())
	{
		Body->SetStringField(TEXT("email"), Email);
	}
	if (!Password.IsEmpty())
	{
		Body->SetStringField(TEXT("password"), Password);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::UnlinkEmail(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString Email,
	FString Password,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/unlink/email");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Email.IsEmpty())
	{
		Body->SetStringField(TEXT("email"), Email);
	}
	if (!Password.IsEmpty())
	{
		Body->SetStringField(TEXT("password"), Password);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::UnlinkFacebook(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString Token,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/unlink/facebook");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Token.IsEmpty())
	{
		Body->SetStringField(TEXT("token"), Token);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::UnlinkFacebook(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString Token,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/unlink/facebook");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Token.IsEmpty())
	{
		Body->SetStringField(TEXT("token"), Token);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::UnlinkFacebookInstantGame(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString SignedPlayerInfo,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/unlink/facebookinstantgame");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!SignedPlayerInfo.IsEmpty())
	{
		Body->SetStringField(TEXT("signed_player_info"), SignedPlayerInfo);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::UnlinkFacebookInstantGame(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString SignedPlayerInfo,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/unlink/facebookinstantgame");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!SignedPlayerInfo.IsEmpty())
	{
		Body->SetStringField(TEXT("signed_player_info"), SignedPlayerInfo);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::UnlinkGameCenter(
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
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/unlink/gamecenter");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!PlayerId.IsEmpty())
	{
		Body->SetStringField(TEXT("player_id"), PlayerId);
	}
	if (!BundleId.IsEmpty())
	{
		Body->SetStringField(TEXT("bundle_id"), BundleId);
	}
	Body->SetNumberField(TEXT("timestamp_seconds"), TimestampSeconds);
	if (!Salt.IsEmpty())
	{
		Body->SetStringField(TEXT("salt"), Salt);
	}
	if (!Signature.IsEmpty())
	{
		Body->SetStringField(TEXT("signature"), Signature);
	}
	if (!PublicKeyUrl.IsEmpty())
	{
		Body->SetStringField(TEXT("public_key_url"), PublicKeyUrl);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::UnlinkGameCenter(
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
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/unlink/gamecenter");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!PlayerId.IsEmpty())
	{
		Body->SetStringField(TEXT("player_id"), PlayerId);
	}
	if (!BundleId.IsEmpty())
	{
		Body->SetStringField(TEXT("bundle_id"), BundleId);
	}
	Body->SetNumberField(TEXT("timestamp_seconds"), TimestampSeconds);
	if (!Salt.IsEmpty())
	{
		Body->SetStringField(TEXT("salt"), Salt);
	}
	if (!Signature.IsEmpty())
	{
		Body->SetStringField(TEXT("signature"), Signature);
	}
	if (!PublicKeyUrl.IsEmpty())
	{
		Body->SetStringField(TEXT("public_key_url"), PublicKeyUrl);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::UnlinkGoogle(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString Token,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/unlink/google");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Token.IsEmpty())
	{
		Body->SetStringField(TEXT("token"), Token);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::UnlinkGoogle(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString Token,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/unlink/google");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Token.IsEmpty())
	{
		Body->SetStringField(TEXT("token"), Token);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::UnlinkSteam(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString Token,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/unlink/steam");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Token.IsEmpty())
	{
		Body->SetStringField(TEXT("token"), Token);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::UnlinkSteam(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString Token,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account/unlink/steam");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Token.IsEmpty())
	{
		Body->SetStringField(TEXT("token"), Token);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::UpdateAccount(
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
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Username.IsEmpty())
	{
		Body->SetStringField(TEXT("username"), Username);
	}
	if (!DisplayName.IsEmpty())
	{
		Body->SetStringField(TEXT("display_name"), DisplayName);
	}
	if (!AvatarUrl.IsEmpty())
	{
		Body->SetStringField(TEXT("avatar_url"), AvatarUrl);
	}
	if (!LangTag.IsEmpty())
	{
		Body->SetStringField(TEXT("lang_tag"), LangTag);
	}
	if (!Location.IsEmpty())
	{
		Body->SetStringField(TEXT("location"), Location);
	}
	if (!Timezone.IsEmpty())
	{
		Body->SetStringField(TEXT("timezone"), Timezone);
	}

	MakeRequest(Config, Endpoint, TEXT("PUT"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::UpdateAccount(
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
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/account");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Username.IsEmpty())
	{
		Body->SetStringField(TEXT("username"), Username);
	}
	if (!DisplayName.IsEmpty())
	{
		Body->SetStringField(TEXT("display_name"), DisplayName);
	}
	if (!AvatarUrl.IsEmpty())
	{
		Body->SetStringField(TEXT("avatar_url"), AvatarUrl);
	}
	if (!LangTag.IsEmpty())
	{
		Body->SetStringField(TEXT("lang_tag"), LangTag);
	}
	if (!Location.IsEmpty())
	{
		Body->SetStringField(TEXT("location"), Location);
	}
	if (!Timezone.IsEmpty())
	{
		Body->SetStringField(TEXT("timezone"), Timezone);
	}

	MakeRequest(Config, Endpoint, TEXT("PUT"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::UpdateGroup(
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
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/group/{group_id}");
	Endpoint = Endpoint.Replace(TEXT("{group_id}"), *GroupId);
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!GroupId.IsEmpty())
	{
		Body->SetStringField(TEXT("group_id"), GroupId);
	}
	if (!Name.IsEmpty())
	{
		Body->SetStringField(TEXT("name"), Name);
	}
	if (!Description.IsEmpty())
	{
		Body->SetStringField(TEXT("description"), Description);
	}
	if (!LangTag.IsEmpty())
	{
		Body->SetStringField(TEXT("lang_tag"), LangTag);
	}
	if (!AvatarUrl.IsEmpty())
	{
		Body->SetStringField(TEXT("avatar_url"), AvatarUrl);
	}
	Body->SetBoolField(TEXT("open"), Open);

	MakeRequest(Config, Endpoint, TEXT("PUT"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::UpdateGroup(
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
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/group/{group_id}");
	Endpoint = Endpoint.Replace(TEXT("{group_id}"), *GroupId);
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!GroupId.IsEmpty())
	{
		Body->SetStringField(TEXT("group_id"), GroupId);
	}
	if (!Name.IsEmpty())
	{
		Body->SetStringField(TEXT("name"), Name);
	}
	if (!Description.IsEmpty())
	{
		Body->SetStringField(TEXT("description"), Description);
	}
	if (!LangTag.IsEmpty())
	{
		Body->SetStringField(TEXT("lang_tag"), LangTag);
	}
	if (!AvatarUrl.IsEmpty())
	{
		Body->SetStringField(TEXT("avatar_url"), AvatarUrl);
	}
	Body->SetBoolField(TEXT("open"), Open);

	MakeRequest(Config, Endpoint, TEXT("PUT"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ValidatePurchaseApple(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString Receipt,
	bool Persist,
	TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/iap/purchase/apple");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Receipt.IsEmpty())
	{
		Body->SetStringField(TEXT("receipt"), Receipt);
	}
	Body->SetBoolField(TEXT("persist"), Persist);

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaValidatePurchaseResponse Result = FNakamaValidatePurchaseResponse::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ValidatePurchaseApple(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString Receipt,
	bool Persist,
	TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/iap/purchase/apple");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Receipt.IsEmpty())
	{
		Body->SetStringField(TEXT("receipt"), Receipt);
	}
	Body->SetBoolField(TEXT("persist"), Persist);

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaValidatePurchaseResponse Result = FNakamaValidatePurchaseResponse::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ValidateSubscriptionApple(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString Receipt,
	bool Persist,
	TFunction<void(const FNakamaValidateSubscriptionResponse&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/iap/subscription/apple");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Receipt.IsEmpty())
	{
		Body->SetStringField(TEXT("receipt"), Receipt);
	}
	Body->SetBoolField(TEXT("persist"), Persist);

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaValidateSubscriptionResponse Result = FNakamaValidateSubscriptionResponse::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ValidateSubscriptionApple(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString Receipt,
	bool Persist,
	TFunction<void(const FNakamaValidateSubscriptionResponse&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/iap/subscription/apple");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Receipt.IsEmpty())
	{
		Body->SetStringField(TEXT("receipt"), Receipt);
	}
	Body->SetBoolField(TEXT("persist"), Persist);

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaValidateSubscriptionResponse Result = FNakamaValidateSubscriptionResponse::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ValidatePurchaseGoogle(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString Purchase,
	bool Persist,
	TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/iap/purchase/google");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Purchase.IsEmpty())
	{
		Body->SetStringField(TEXT("purchase"), Purchase);
	}
	Body->SetBoolField(TEXT("persist"), Persist);

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaValidatePurchaseResponse Result = FNakamaValidatePurchaseResponse::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ValidatePurchaseGoogle(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString Purchase,
	bool Persist,
	TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/iap/purchase/google");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Purchase.IsEmpty())
	{
		Body->SetStringField(TEXT("purchase"), Purchase);
	}
	Body->SetBoolField(TEXT("persist"), Persist);

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaValidatePurchaseResponse Result = FNakamaValidatePurchaseResponse::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ValidateSubscriptionGoogle(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString Receipt,
	bool Persist,
	TFunction<void(const FNakamaValidateSubscriptionResponse&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/iap/subscription/google");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Receipt.IsEmpty())
	{
		Body->SetStringField(TEXT("receipt"), Receipt);
	}
	Body->SetBoolField(TEXT("persist"), Persist);

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaValidateSubscriptionResponse Result = FNakamaValidateSubscriptionResponse::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ValidateSubscriptionGoogle(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString Receipt,
	bool Persist,
	TFunction<void(const FNakamaValidateSubscriptionResponse&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/iap/subscription/google");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Receipt.IsEmpty())
	{
		Body->SetStringField(TEXT("receipt"), Receipt);
	}
	Body->SetBoolField(TEXT("persist"), Persist);

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaValidateSubscriptionResponse Result = FNakamaValidateSubscriptionResponse::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ValidatePurchaseHuawei(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString Purchase,
	FString Signature,
	bool Persist,
	TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/iap/purchase/huawei");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Purchase.IsEmpty())
	{
		Body->SetStringField(TEXT("purchase"), Purchase);
	}
	if (!Signature.IsEmpty())
	{
		Body->SetStringField(TEXT("signature"), Signature);
	}
	Body->SetBoolField(TEXT("persist"), Persist);

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaValidatePurchaseResponse Result = FNakamaValidatePurchaseResponse::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ValidatePurchaseHuawei(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString Purchase,
	FString Signature,
	bool Persist,
	TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/iap/purchase/huawei");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Purchase.IsEmpty())
	{
		Body->SetStringField(TEXT("purchase"), Purchase);
	}
	if (!Signature.IsEmpty())
	{
		Body->SetStringField(TEXT("signature"), Signature);
	}
	Body->SetBoolField(TEXT("persist"), Persist);

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaValidatePurchaseResponse Result = FNakamaValidatePurchaseResponse::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ValidatePurchaseFacebookInstant(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString SignedRequest,
	bool Persist,
	TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/iap/purchase/facebookinstant");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!SignedRequest.IsEmpty())
	{
		Body->SetStringField(TEXT("signed_request"), SignedRequest);
	}
	Body->SetBoolField(TEXT("persist"), Persist);

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaValidatePurchaseResponse Result = FNakamaValidatePurchaseResponse::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::ValidatePurchaseFacebookInstant(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString SignedRequest,
	bool Persist,
	TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/iap/purchase/facebookinstant");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!SignedRequest.IsEmpty())
	{
		Body->SetStringField(TEXT("signed_request"), SignedRequest);
	}
	Body->SetBoolField(TEXT("persist"), Persist);

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaValidatePurchaseResponse Result = FNakamaValidatePurchaseResponse::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::WriteLeaderboardRecord(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString LeaderboardId,
	FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite Record,
	TFunction<void(const FNakamaLeaderboardRecord&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/leaderboard/{leaderboard_id}");
	Endpoint = Endpoint.Replace(TEXT("{leaderboard_id}"), *LeaderboardId);
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = Record.ToJson();

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaLeaderboardRecord Result = FNakamaLeaderboardRecord::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::WriteLeaderboardRecord(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString LeaderboardId,
	FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite Record,
	TFunction<void(const FNakamaLeaderboardRecord&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/leaderboard/{leaderboard_id}");
	Endpoint = Endpoint.Replace(TEXT("{leaderboard_id}"), *LeaderboardId);
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = Record.ToJson();

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaLeaderboardRecord Result = FNakamaLeaderboardRecord::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::WriteStorageObjects(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	const TArray<FNakamaWriteStorageObject>& Objects,
	TFunction<void(const FNakamaStorageObjectAcks&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/storage");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (Objects.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Objects)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Body->SetArrayField(TEXT("objects"), Array);
	}

	MakeRequest(Config, Endpoint, TEXT("PUT"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaStorageObjectAcks Result = FNakamaStorageObjectAcks::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::WriteStorageObjects(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	const TArray<FNakamaWriteStorageObject>& Objects,
	TFunction<void(const FNakamaStorageObjectAcks&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/storage");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (Objects.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Objects)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Body->SetArrayField(TEXT("objects"), Array);
	}

	MakeRequest(Config, Endpoint, TEXT("PUT"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaStorageObjectAcks Result = FNakamaStorageObjectAcks::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::WriteTournamentRecord(
	const FNakamaClientConfig& Config,
	const FNakamaSession& Session,
	FString TournamentId,
	FNakamaWriteTournamentRecordRequest_TournamentRecordWrite Record,
	TFunction<void(const FNakamaLeaderboardRecord&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/tournament/{tournament_id}");
	Endpoint = Endpoint.Replace(TEXT("{tournament_id}"), *TournamentId);
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = Record.ToJson();

	MakeRequest(Config, Endpoint, TEXT("PUT"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaLeaderboardRecord Result = FNakamaLeaderboardRecord::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

void NakamaApi::WriteTournamentRecord(
	const FNakamaClientConfig& Config,
	const FString& HttpKey,
	FString TournamentId,
	FNakamaWriteTournamentRecordRequest_TournamentRecordWrite Record,
	TFunction<void(const FNakamaLeaderboardRecord&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v2/tournament/{tournament_id}");
	Endpoint = Endpoint.Replace(TEXT("{tournament_id}"), *TournamentId);
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = Record.ToJson();

	MakeRequest(Config, Endpoint, TEXT("PUT"), Body, ENakamaRequestAuth::HttpKey, HttpKey,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FNakamaLeaderboardRecord Result = FNakamaLeaderboardRecord::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, Timeout, CancellationToken);
}

// Module implementation
class FNakamaApiModule : public IModuleInterface
{
public:
	virtual void StartupModule() override
	{
		UE_LOG(LogNakama, Log, TEXT("NakamaApi module starting"));
	}

	virtual void ShutdownModule() override
	{
		UE_LOG(LogNakama, Log, TEXT("NakamaApi module shutting down"));
	}
};

IMPLEMENT_MODULE(FNakamaApiModule, NakamaApi)
