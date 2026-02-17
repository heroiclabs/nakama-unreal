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

#include "NakamaClientBlueprintLibrary.h"

// ============================================================================
// Blueprint Function Library Implementation
// ============================================================================

FNakamaClientRef UNakamaBlueprintLibrary::CreateDefaultClient(
	const FString& ServerKey,
	const FString& Host,
	int32 Port,
	bool UseSSL,
	bool EnableDebug)
{
	return FNakamaClientRef(MakeShared<FNakamaApiConfig>(FNakamaApiConfig{ServerKey, Host, Port, UseSSL, EnableDebug}));
}

bool UNakamaBlueprintLibrary::IsValidClient(const FNakamaClientRef& Client)
{
	return Client.IsValid();
}

// ============================================================================
// Async Action Classes Implementation
// ============================================================================

// AddFriends
UNakamaClientAddFriends* UNakamaClientAddFriends::AddFriends(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	FString Metadata)
{
	UNakamaClientAddFriends* Action = NewObject<UNakamaClientAddFriends>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredIds = Ids;
	Action->StoredUsernames = Usernames;
	Action->StoredMetadata = Metadata;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientAddFriends::Activate()
{
	static const TCHAR* TraceScope_AddFriends = TEXT("NakamaBP_AddFriends");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_AddFriends);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::AddFriends(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredIds,
		StoredUsernames,
		StoredMetadata,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// AddGroupUsers
UNakamaClientAddGroupUsers* UNakamaClientAddGroupUsers::AddGroupUsers(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString GroupId,
	const TArray<FString>& UserIds)
{
	UNakamaClientAddGroupUsers* Action = NewObject<UNakamaClientAddGroupUsers>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredGroupId = GroupId;
	Action->StoredUserIds = UserIds;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientAddGroupUsers::Activate()
{
	static const TCHAR* TraceScope_AddGroupUsers = TEXT("NakamaBP_AddGroupUsers");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_AddGroupUsers);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::AddGroupUsers(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredGroupId,
		StoredUserIds,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// SessionRefresh
UNakamaClientSessionRefresh* UNakamaClientSessionRefresh::SessionRefresh(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	FString Token,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientSessionRefresh* Action = NewObject<UNakamaClientSessionRefresh>();
	Action->Client = Client;
	Action->StoredToken = Token;
	Action->StoredVars = Vars;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientSessionRefresh::Activate()
{
	static const TCHAR* TraceScope_SessionRefresh = TEXT("NakamaBP_SessionRefresh");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_SessionRefresh);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::SessionRefresh(
		Config,
		StoredToken,
		StoredVars,
		[this](const FNakamaSession& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// SessionLogout
UNakamaClientSessionLogout* UNakamaClientSessionLogout::SessionLogout(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString Token,
	FString RefreshToken)
{
	UNakamaClientSessionLogout* Action = NewObject<UNakamaClientSessionLogout>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredToken = Token;
	Action->StoredRefreshToken = RefreshToken;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientSessionLogout::Activate()
{
	static const TCHAR* TraceScope_SessionLogout = TEXT("NakamaBP_SessionLogout");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_SessionLogout);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::SessionLogout(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredToken,
		StoredRefreshToken,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// AuthenticateApple
UNakamaClientAuthenticateApple* UNakamaClientAuthenticateApple::AuthenticateApple(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	FNakamaAccountApple Account,
	bool Create,
	FString Username)
{
	UNakamaClientAuthenticateApple* Action = NewObject<UNakamaClientAuthenticateApple>();
	Action->Client = Client;
	Action->StoredAccount = Account;
	Action->StoredCreate = Create;
	Action->StoredUsername = Username;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientAuthenticateApple::Activate()
{
	static const TCHAR* TraceScope_AuthenticateApple = TEXT("NakamaBP_AuthenticateApple");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_AuthenticateApple);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::AuthenticateApple(
		Config,
		StoredAccount,
		StoredCreate,
		StoredUsername,
		[this](const FNakamaSession& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// AuthenticateCustom
UNakamaClientAuthenticateCustom* UNakamaClientAuthenticateCustom::AuthenticateCustom(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	FNakamaAccountCustom Account,
	bool Create,
	FString Username)
{
	UNakamaClientAuthenticateCustom* Action = NewObject<UNakamaClientAuthenticateCustom>();
	Action->Client = Client;
	Action->StoredAccount = Account;
	Action->StoredCreate = Create;
	Action->StoredUsername = Username;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientAuthenticateCustom::Activate()
{
	static const TCHAR* TraceScope_AuthenticateCustom = TEXT("NakamaBP_AuthenticateCustom");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_AuthenticateCustom);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::AuthenticateCustom(
		Config,
		StoredAccount,
		StoredCreate,
		StoredUsername,
		[this](const FNakamaSession& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// AuthenticateDevice
UNakamaClientAuthenticateDevice* UNakamaClientAuthenticateDevice::AuthenticateDevice(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	FNakamaAccountDevice Account,
	bool Create,
	FString Username)
{
	UNakamaClientAuthenticateDevice* Action = NewObject<UNakamaClientAuthenticateDevice>();
	Action->Client = Client;
	Action->StoredAccount = Account;
	Action->StoredCreate = Create;
	Action->StoredUsername = Username;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientAuthenticateDevice::Activate()
{
	static const TCHAR* TraceScope_AuthenticateDevice = TEXT("NakamaBP_AuthenticateDevice");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_AuthenticateDevice);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::AuthenticateDevice(
		Config,
		StoredAccount,
		StoredCreate,
		StoredUsername,
		[this](const FNakamaSession& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// AuthenticateEmail
UNakamaClientAuthenticateEmail* UNakamaClientAuthenticateEmail::AuthenticateEmail(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	FNakamaAccountEmail Account,
	bool Create,
	FString Username)
{
	UNakamaClientAuthenticateEmail* Action = NewObject<UNakamaClientAuthenticateEmail>();
	Action->Client = Client;
	Action->StoredAccount = Account;
	Action->StoredCreate = Create;
	Action->StoredUsername = Username;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientAuthenticateEmail::Activate()
{
	static const TCHAR* TraceScope_AuthenticateEmail = TEXT("NakamaBP_AuthenticateEmail");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_AuthenticateEmail);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::AuthenticateEmail(
		Config,
		StoredAccount,
		StoredCreate,
		StoredUsername,
		[this](const FNakamaSession& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// AuthenticateFacebook
UNakamaClientAuthenticateFacebook* UNakamaClientAuthenticateFacebook::AuthenticateFacebook(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	FNakamaAccountFacebook Account,
	bool Create,
	FString Username,
	bool Sync)
{
	UNakamaClientAuthenticateFacebook* Action = NewObject<UNakamaClientAuthenticateFacebook>();
	Action->Client = Client;
	Action->StoredAccount = Account;
	Action->StoredCreate = Create;
	Action->StoredUsername = Username;
	Action->StoredSync = Sync;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientAuthenticateFacebook::Activate()
{
	static const TCHAR* TraceScope_AuthenticateFacebook = TEXT("NakamaBP_AuthenticateFacebook");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_AuthenticateFacebook);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::AuthenticateFacebook(
		Config,
		StoredAccount,
		StoredCreate,
		StoredUsername,
		StoredSync,
		[this](const FNakamaSession& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// AuthenticateFacebookInstantGame
UNakamaClientAuthenticateFacebookInstantGame* UNakamaClientAuthenticateFacebookInstantGame::AuthenticateFacebookInstantGame(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	FNakamaAccountFacebookInstantGame Account,
	bool Create,
	FString Username)
{
	UNakamaClientAuthenticateFacebookInstantGame* Action = NewObject<UNakamaClientAuthenticateFacebookInstantGame>();
	Action->Client = Client;
	Action->StoredAccount = Account;
	Action->StoredCreate = Create;
	Action->StoredUsername = Username;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientAuthenticateFacebookInstantGame::Activate()
{
	static const TCHAR* TraceScope_AuthenticateFacebookInstantGame = TEXT("NakamaBP_AuthenticateFacebookInstantGame");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_AuthenticateFacebookInstantGame);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::AuthenticateFacebookInstantGame(
		Config,
		StoredAccount,
		StoredCreate,
		StoredUsername,
		[this](const FNakamaSession& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// AuthenticateGameCenter
UNakamaClientAuthenticateGameCenter* UNakamaClientAuthenticateGameCenter::AuthenticateGameCenter(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	FNakamaAccountGameCenter Account,
	bool Create,
	FString Username)
{
	UNakamaClientAuthenticateGameCenter* Action = NewObject<UNakamaClientAuthenticateGameCenter>();
	Action->Client = Client;
	Action->StoredAccount = Account;
	Action->StoredCreate = Create;
	Action->StoredUsername = Username;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientAuthenticateGameCenter::Activate()
{
	static const TCHAR* TraceScope_AuthenticateGameCenter = TEXT("NakamaBP_AuthenticateGameCenter");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_AuthenticateGameCenter);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::AuthenticateGameCenter(
		Config,
		StoredAccount,
		StoredCreate,
		StoredUsername,
		[this](const FNakamaSession& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// AuthenticateGoogle
UNakamaClientAuthenticateGoogle* UNakamaClientAuthenticateGoogle::AuthenticateGoogle(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	FNakamaAccountGoogle Account,
	bool Create,
	FString Username)
{
	UNakamaClientAuthenticateGoogle* Action = NewObject<UNakamaClientAuthenticateGoogle>();
	Action->Client = Client;
	Action->StoredAccount = Account;
	Action->StoredCreate = Create;
	Action->StoredUsername = Username;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientAuthenticateGoogle::Activate()
{
	static const TCHAR* TraceScope_AuthenticateGoogle = TEXT("NakamaBP_AuthenticateGoogle");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_AuthenticateGoogle);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::AuthenticateGoogle(
		Config,
		StoredAccount,
		StoredCreate,
		StoredUsername,
		[this](const FNakamaSession& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// AuthenticateSteam
UNakamaClientAuthenticateSteam* UNakamaClientAuthenticateSteam::AuthenticateSteam(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	FNakamaAccountSteam Account,
	bool Create,
	FString Username,
	bool Sync)
{
	UNakamaClientAuthenticateSteam* Action = NewObject<UNakamaClientAuthenticateSteam>();
	Action->Client = Client;
	Action->StoredAccount = Account;
	Action->StoredCreate = Create;
	Action->StoredUsername = Username;
	Action->StoredSync = Sync;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientAuthenticateSteam::Activate()
{
	static const TCHAR* TraceScope_AuthenticateSteam = TEXT("NakamaBP_AuthenticateSteam");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_AuthenticateSteam);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::AuthenticateSteam(
		Config,
		StoredAccount,
		StoredCreate,
		StoredUsername,
		StoredSync,
		[this](const FNakamaSession& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// BanGroupUsers
UNakamaClientBanGroupUsers* UNakamaClientBanGroupUsers::BanGroupUsers(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString GroupId,
	const TArray<FString>& UserIds)
{
	UNakamaClientBanGroupUsers* Action = NewObject<UNakamaClientBanGroupUsers>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredGroupId = GroupId;
	Action->StoredUserIds = UserIds;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientBanGroupUsers::Activate()
{
	static const TCHAR* TraceScope_BanGroupUsers = TEXT("NakamaBP_BanGroupUsers");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_BanGroupUsers);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::BanGroupUsers(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredGroupId,
		StoredUserIds,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// BlockFriends
UNakamaClientBlockFriends* UNakamaClientBlockFriends::BlockFriends(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames)
{
	UNakamaClientBlockFriends* Action = NewObject<UNakamaClientBlockFriends>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredIds = Ids;
	Action->StoredUsernames = Usernames;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientBlockFriends::Activate()
{
	static const TCHAR* TraceScope_BlockFriends = TEXT("NakamaBP_BlockFriends");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_BlockFriends);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::BlockFriends(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredIds,
		StoredUsernames,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// CreateGroup
UNakamaClientCreateGroup* UNakamaClientCreateGroup::CreateGroup(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString Name,
	FString Description,
	FString LangTag,
	FString AvatarUrl,
	bool Open,
	int32 MaxCount)
{
	UNakamaClientCreateGroup* Action = NewObject<UNakamaClientCreateGroup>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredName = Name;
	Action->StoredDescription = Description;
	Action->StoredLangTag = LangTag;
	Action->StoredAvatarUrl = AvatarUrl;
	Action->StoredOpen = Open;
	Action->StoredMaxCount = MaxCount;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientCreateGroup::Activate()
{
	static const TCHAR* TraceScope_CreateGroup = TEXT("NakamaBP_CreateGroup");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_CreateGroup);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::CreateGroup(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredName,
		StoredDescription,
		StoredLangTag,
		StoredAvatarUrl,
		StoredOpen,
		StoredMaxCount,
		[this](const FNakamaGroup& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// DeleteAccount
UNakamaClientDeleteAccount* UNakamaClientDeleteAccount::DeleteAccount(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session)
{
	UNakamaClientDeleteAccount* Action = NewObject<UNakamaClientDeleteAccount>();
	Action->Client = Client;
	Action->Session = Session;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientDeleteAccount::Activate()
{
	static const TCHAR* TraceScope_DeleteAccount = TEXT("NakamaBP_DeleteAccount");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_DeleteAccount);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::DeleteAccount(
		Config,
		MakeShared<FNakamaSession>(Session),
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// DeleteFriends
UNakamaClientDeleteFriends* UNakamaClientDeleteFriends::DeleteFriends(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames)
{
	UNakamaClientDeleteFriends* Action = NewObject<UNakamaClientDeleteFriends>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredIds = Ids;
	Action->StoredUsernames = Usernames;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientDeleteFriends::Activate()
{
	static const TCHAR* TraceScope_DeleteFriends = TEXT("NakamaBP_DeleteFriends");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_DeleteFriends);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::DeleteFriends(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredIds,
		StoredUsernames,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// DeleteGroup
UNakamaClientDeleteGroup* UNakamaClientDeleteGroup::DeleteGroup(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString GroupId)
{
	UNakamaClientDeleteGroup* Action = NewObject<UNakamaClientDeleteGroup>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredGroupId = GroupId;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientDeleteGroup::Activate()
{
	static const TCHAR* TraceScope_DeleteGroup = TEXT("NakamaBP_DeleteGroup");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_DeleteGroup);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::DeleteGroup(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredGroupId,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// DeleteLeaderboardRecord
UNakamaClientDeleteLeaderboardRecord* UNakamaClientDeleteLeaderboardRecord::DeleteLeaderboardRecord(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString LeaderboardId)
{
	UNakamaClientDeleteLeaderboardRecord* Action = NewObject<UNakamaClientDeleteLeaderboardRecord>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredLeaderboardId = LeaderboardId;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientDeleteLeaderboardRecord::Activate()
{
	static const TCHAR* TraceScope_DeleteLeaderboardRecord = TEXT("NakamaBP_DeleteLeaderboardRecord");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_DeleteLeaderboardRecord);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::DeleteLeaderboardRecord(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredLeaderboardId,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// DeleteNotifications
UNakamaClientDeleteNotifications* UNakamaClientDeleteNotifications::DeleteNotifications(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	const TArray<FString>& Ids)
{
	UNakamaClientDeleteNotifications* Action = NewObject<UNakamaClientDeleteNotifications>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredIds = Ids;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientDeleteNotifications::Activate()
{
	static const TCHAR* TraceScope_DeleteNotifications = TEXT("NakamaBP_DeleteNotifications");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_DeleteNotifications);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::DeleteNotifications(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredIds,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// DeleteTournamentRecord
UNakamaClientDeleteTournamentRecord* UNakamaClientDeleteTournamentRecord::DeleteTournamentRecord(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString TournamentId)
{
	UNakamaClientDeleteTournamentRecord* Action = NewObject<UNakamaClientDeleteTournamentRecord>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredTournamentId = TournamentId;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientDeleteTournamentRecord::Activate()
{
	static const TCHAR* TraceScope_DeleteTournamentRecord = TEXT("NakamaBP_DeleteTournamentRecord");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_DeleteTournamentRecord);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::DeleteTournamentRecord(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredTournamentId,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// DeleteStorageObjects
UNakamaClientDeleteStorageObjects* UNakamaClientDeleteStorageObjects::DeleteStorageObjects(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	const TArray<FNakamaDeleteStorageObjectId>& ObjectIds)
{
	UNakamaClientDeleteStorageObjects* Action = NewObject<UNakamaClientDeleteStorageObjects>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredObjectIds = ObjectIds;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientDeleteStorageObjects::Activate()
{
	static const TCHAR* TraceScope_DeleteStorageObjects = TEXT("NakamaBP_DeleteStorageObjects");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_DeleteStorageObjects);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::DeleteStorageObjects(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredObjectIds,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// Event
UNakamaClientEvent* UNakamaClientEvent::Event(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString Name,
	FString Timestamp,
	bool External,
	const TMap<FString, FString>& Properties)
{
	UNakamaClientEvent* Action = NewObject<UNakamaClientEvent>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredName = Name;
	Action->StoredTimestamp = Timestamp;
	Action->StoredExternal = External;
	Action->StoredProperties = Properties;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientEvent::Activate()
{
	static const TCHAR* TraceScope_Event = TEXT("NakamaBP_Event");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_Event);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::Event(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredName,
		StoredTimestamp,
		StoredExternal,
		StoredProperties,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// GetAccount
UNakamaClientGetAccount* UNakamaClientGetAccount::GetAccount(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session)
{
	UNakamaClientGetAccount* Action = NewObject<UNakamaClientGetAccount>();
	Action->Client = Client;
	Action->Session = Session;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientGetAccount::Activate()
{
	static const TCHAR* TraceScope_GetAccount = TEXT("NakamaBP_GetAccount");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_GetAccount);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::GetAccount(
		Config,
		MakeShared<FNakamaSession>(Session),
		[this](const FNakamaAccount& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// GetUsers
UNakamaClientGetUsers* UNakamaClientGetUsers::GetUsers(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	const TArray<FString>& FacebookIds)
{
	UNakamaClientGetUsers* Action = NewObject<UNakamaClientGetUsers>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredIds = Ids;
	Action->StoredUsernames = Usernames;
	Action->StoredFacebookIds = FacebookIds;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientGetUsers::Activate()
{
	static const TCHAR* TraceScope_GetUsers = TEXT("NakamaBP_GetUsers");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_GetUsers);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::GetUsers(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredIds,
		StoredUsernames,
		StoredFacebookIds,
		[this](const FNakamaUsers& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// GetSubscription
UNakamaClientGetSubscription* UNakamaClientGetSubscription::GetSubscription(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString ProductId)
{
	UNakamaClientGetSubscription* Action = NewObject<UNakamaClientGetSubscription>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredProductId = ProductId;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientGetSubscription::Activate()
{
	static const TCHAR* TraceScope_GetSubscription = TEXT("NakamaBP_GetSubscription");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_GetSubscription);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::GetSubscription(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredProductId,
		[this](const FNakamaValidatedSubscription& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// GetMatchmakerStats
UNakamaClientGetMatchmakerStats* UNakamaClientGetMatchmakerStats::GetMatchmakerStats(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session)
{
	UNakamaClientGetMatchmakerStats* Action = NewObject<UNakamaClientGetMatchmakerStats>();
	Action->Client = Client;
	Action->Session = Session;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientGetMatchmakerStats::Activate()
{
	static const TCHAR* TraceScope_GetMatchmakerStats = TEXT("NakamaBP_GetMatchmakerStats");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_GetMatchmakerStats);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::GetMatchmakerStats(
		Config,
		MakeShared<FNakamaSession>(Session),
		[this](const FNakamaMatchmakerStats& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// Healthcheck
UNakamaClientHealthcheck* UNakamaClientHealthcheck::Healthcheck(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session)
{
	UNakamaClientHealthcheck* Action = NewObject<UNakamaClientHealthcheck>();
	Action->Client = Client;
	Action->Session = Session;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientHealthcheck::Activate()
{
	static const TCHAR* TraceScope_Healthcheck = TEXT("NakamaBP_Healthcheck");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_Healthcheck);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::Healthcheck(
		Config,
		MakeShared<FNakamaSession>(Session),
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// ImportFacebookFriends
UNakamaClientImportFacebookFriends* UNakamaClientImportFacebookFriends::ImportFacebookFriends(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FNakamaAccountFacebook Account,
	bool Reset)
{
	UNakamaClientImportFacebookFriends* Action = NewObject<UNakamaClientImportFacebookFriends>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredAccount = Account;
	Action->StoredReset = Reset;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientImportFacebookFriends::Activate()
{
	static const TCHAR* TraceScope_ImportFacebookFriends = TEXT("NakamaBP_ImportFacebookFriends");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ImportFacebookFriends);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::ImportFacebookFriends(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredAccount,
		StoredReset,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// ImportSteamFriends
UNakamaClientImportSteamFriends* UNakamaClientImportSteamFriends::ImportSteamFriends(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FNakamaAccountSteam Account,
	bool Reset)
{
	UNakamaClientImportSteamFriends* Action = NewObject<UNakamaClientImportSteamFriends>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredAccount = Account;
	Action->StoredReset = Reset;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientImportSteamFriends::Activate()
{
	static const TCHAR* TraceScope_ImportSteamFriends = TEXT("NakamaBP_ImportSteamFriends");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ImportSteamFriends);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::ImportSteamFriends(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredAccount,
		StoredReset,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// JoinGroup
UNakamaClientJoinGroup* UNakamaClientJoinGroup::JoinGroup(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString GroupId)
{
	UNakamaClientJoinGroup* Action = NewObject<UNakamaClientJoinGroup>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredGroupId = GroupId;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientJoinGroup::Activate()
{
	static const TCHAR* TraceScope_JoinGroup = TEXT("NakamaBP_JoinGroup");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_JoinGroup);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::JoinGroup(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredGroupId,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// JoinTournament
UNakamaClientJoinTournament* UNakamaClientJoinTournament::JoinTournament(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString TournamentId)
{
	UNakamaClientJoinTournament* Action = NewObject<UNakamaClientJoinTournament>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredTournamentId = TournamentId;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientJoinTournament::Activate()
{
	static const TCHAR* TraceScope_JoinTournament = TEXT("NakamaBP_JoinTournament");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_JoinTournament);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::JoinTournament(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredTournamentId,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// KickGroupUsers
UNakamaClientKickGroupUsers* UNakamaClientKickGroupUsers::KickGroupUsers(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString GroupId,
	const TArray<FString>& UserIds)
{
	UNakamaClientKickGroupUsers* Action = NewObject<UNakamaClientKickGroupUsers>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredGroupId = GroupId;
	Action->StoredUserIds = UserIds;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientKickGroupUsers::Activate()
{
	static const TCHAR* TraceScope_KickGroupUsers = TEXT("NakamaBP_KickGroupUsers");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_KickGroupUsers);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::KickGroupUsers(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredGroupId,
		StoredUserIds,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// LeaveGroup
UNakamaClientLeaveGroup* UNakamaClientLeaveGroup::LeaveGroup(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString GroupId)
{
	UNakamaClientLeaveGroup* Action = NewObject<UNakamaClientLeaveGroup>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredGroupId = GroupId;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientLeaveGroup::Activate()
{
	static const TCHAR* TraceScope_LeaveGroup = TEXT("NakamaBP_LeaveGroup");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_LeaveGroup);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::LeaveGroup(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredGroupId,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// LinkApple
UNakamaClientLinkApple* UNakamaClientLinkApple::LinkApple(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString Token,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientLinkApple* Action = NewObject<UNakamaClientLinkApple>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredToken = Token;
	Action->StoredVars = Vars;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientLinkApple::Activate()
{
	static const TCHAR* TraceScope_LinkApple = TEXT("NakamaBP_LinkApple");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_LinkApple);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::LinkApple(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredToken,
		StoredVars,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// LinkCustom
UNakamaClientLinkCustom* UNakamaClientLinkCustom::LinkCustom(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString Id,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientLinkCustom* Action = NewObject<UNakamaClientLinkCustom>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredId = Id;
	Action->StoredVars = Vars;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientLinkCustom::Activate()
{
	static const TCHAR* TraceScope_LinkCustom = TEXT("NakamaBP_LinkCustom");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_LinkCustom);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::LinkCustom(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredId,
		StoredVars,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// LinkDevice
UNakamaClientLinkDevice* UNakamaClientLinkDevice::LinkDevice(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString Id,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientLinkDevice* Action = NewObject<UNakamaClientLinkDevice>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredId = Id;
	Action->StoredVars = Vars;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientLinkDevice::Activate()
{
	static const TCHAR* TraceScope_LinkDevice = TEXT("NakamaBP_LinkDevice");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_LinkDevice);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::LinkDevice(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredId,
		StoredVars,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// LinkEmail
UNakamaClientLinkEmail* UNakamaClientLinkEmail::LinkEmail(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString Email,
	FString Password,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientLinkEmail* Action = NewObject<UNakamaClientLinkEmail>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredEmail = Email;
	Action->StoredPassword = Password;
	Action->StoredVars = Vars;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientLinkEmail::Activate()
{
	static const TCHAR* TraceScope_LinkEmail = TEXT("NakamaBP_LinkEmail");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_LinkEmail);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::LinkEmail(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredEmail,
		StoredPassword,
		StoredVars,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// LinkFacebook
UNakamaClientLinkFacebook* UNakamaClientLinkFacebook::LinkFacebook(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FNakamaAccountFacebook Account,
	bool Sync)
{
	UNakamaClientLinkFacebook* Action = NewObject<UNakamaClientLinkFacebook>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredAccount = Account;
	Action->StoredSync = Sync;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientLinkFacebook::Activate()
{
	static const TCHAR* TraceScope_LinkFacebook = TEXT("NakamaBP_LinkFacebook");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_LinkFacebook);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::LinkFacebook(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredAccount,
		StoredSync,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// LinkFacebookInstantGame
UNakamaClientLinkFacebookInstantGame* UNakamaClientLinkFacebookInstantGame::LinkFacebookInstantGame(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString SignedPlayerInfo,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientLinkFacebookInstantGame* Action = NewObject<UNakamaClientLinkFacebookInstantGame>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredSignedPlayerInfo = SignedPlayerInfo;
	Action->StoredVars = Vars;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientLinkFacebookInstantGame::Activate()
{
	static const TCHAR* TraceScope_LinkFacebookInstantGame = TEXT("NakamaBP_LinkFacebookInstantGame");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_LinkFacebookInstantGame);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::LinkFacebookInstantGame(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredSignedPlayerInfo,
		StoredVars,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// LinkGameCenter
UNakamaClientLinkGameCenter* UNakamaClientLinkGameCenter::LinkGameCenter(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString PlayerId,
	FString BundleId,
	int64 TimestampSeconds,
	FString Salt,
	FString Signature,
	FString PublicKeyUrl,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientLinkGameCenter* Action = NewObject<UNakamaClientLinkGameCenter>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredPlayerId = PlayerId;
	Action->StoredBundleId = BundleId;
	Action->StoredTimestampSeconds = TimestampSeconds;
	Action->StoredSalt = Salt;
	Action->StoredSignature = Signature;
	Action->StoredPublicKeyUrl = PublicKeyUrl;
	Action->StoredVars = Vars;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientLinkGameCenter::Activate()
{
	static const TCHAR* TraceScope_LinkGameCenter = TEXT("NakamaBP_LinkGameCenter");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_LinkGameCenter);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::LinkGameCenter(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredPlayerId,
		StoredBundleId,
		StoredTimestampSeconds,
		StoredSalt,
		StoredSignature,
		StoredPublicKeyUrl,
		StoredVars,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// LinkGoogle
UNakamaClientLinkGoogle* UNakamaClientLinkGoogle::LinkGoogle(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString Token,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientLinkGoogle* Action = NewObject<UNakamaClientLinkGoogle>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredToken = Token;
	Action->StoredVars = Vars;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientLinkGoogle::Activate()
{
	static const TCHAR* TraceScope_LinkGoogle = TEXT("NakamaBP_LinkGoogle");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_LinkGoogle);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::LinkGoogle(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredToken,
		StoredVars,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// LinkSteam
UNakamaClientLinkSteam* UNakamaClientLinkSteam::LinkSteam(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FNakamaAccountSteam Account,
	bool Sync)
{
	UNakamaClientLinkSteam* Action = NewObject<UNakamaClientLinkSteam>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredAccount = Account;
	Action->StoredSync = Sync;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientLinkSteam::Activate()
{
	static const TCHAR* TraceScope_LinkSteam = TEXT("NakamaBP_LinkSteam");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_LinkSteam);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::LinkSteam(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredAccount,
		StoredSync,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// ListChannelMessages
UNakamaClientListChannelMessages* UNakamaClientListChannelMessages::ListChannelMessages(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString ChannelId,
	int32 Limit,
	bool Forward,
	FString Cursor)
{
	UNakamaClientListChannelMessages* Action = NewObject<UNakamaClientListChannelMessages>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredChannelId = ChannelId;
	Action->StoredLimit = Limit;
	Action->StoredForward = Forward;
	Action->StoredCursor = Cursor;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientListChannelMessages::Activate()
{
	static const TCHAR* TraceScope_ListChannelMessages = TEXT("NakamaBP_ListChannelMessages");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ListChannelMessages);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::ListChannelMessages(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredChannelId,
		StoredLimit,
		StoredForward,
		StoredCursor,
		[this](const FNakamaChannelMessageList& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// ListFriends
UNakamaClientListFriends* UNakamaClientListFriends::ListFriends(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	int32 Limit,
	int32 State,
	FString Cursor)
{
	UNakamaClientListFriends* Action = NewObject<UNakamaClientListFriends>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredLimit = Limit;
	Action->StoredState = State;
	Action->StoredCursor = Cursor;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientListFriends::Activate()
{
	static const TCHAR* TraceScope_ListFriends = TEXT("NakamaBP_ListFriends");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ListFriends);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::ListFriends(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredLimit,
		StoredState,
		StoredCursor,
		[this](const FNakamaFriendList& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// ListFriendsOfFriends
UNakamaClientListFriendsOfFriends* UNakamaClientListFriendsOfFriends::ListFriendsOfFriends(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	int32 Limit,
	FString Cursor)
{
	UNakamaClientListFriendsOfFriends* Action = NewObject<UNakamaClientListFriendsOfFriends>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredLimit = Limit;
	Action->StoredCursor = Cursor;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientListFriendsOfFriends::Activate()
{
	static const TCHAR* TraceScope_ListFriendsOfFriends = TEXT("NakamaBP_ListFriendsOfFriends");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ListFriendsOfFriends);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::ListFriendsOfFriends(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredLimit,
		StoredCursor,
		[this](const FNakamaFriendsOfFriendsList& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// ListGroups
UNakamaClientListGroups* UNakamaClientListGroups::ListGroups(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString Name,
	FString Cursor,
	int32 Limit,
	FString LangTag,
	int32 Members,
	bool Open)
{
	UNakamaClientListGroups* Action = NewObject<UNakamaClientListGroups>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredName = Name;
	Action->StoredCursor = Cursor;
	Action->StoredLimit = Limit;
	Action->StoredLangTag = LangTag;
	Action->StoredMembers = Members;
	Action->StoredOpen = Open;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientListGroups::Activate()
{
	static const TCHAR* TraceScope_ListGroups = TEXT("NakamaBP_ListGroups");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ListGroups);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::ListGroups(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredName,
		StoredCursor,
		StoredLimit,
		StoredLangTag,
		StoredMembers,
		StoredOpen,
		[this](const FNakamaGroupList& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// ListGroupUsers
UNakamaClientListGroupUsers* UNakamaClientListGroupUsers::ListGroupUsers(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString GroupId,
	int32 Limit,
	int32 State,
	FString Cursor)
{
	UNakamaClientListGroupUsers* Action = NewObject<UNakamaClientListGroupUsers>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredGroupId = GroupId;
	Action->StoredLimit = Limit;
	Action->StoredState = State;
	Action->StoredCursor = Cursor;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientListGroupUsers::Activate()
{
	static const TCHAR* TraceScope_ListGroupUsers = TEXT("NakamaBP_ListGroupUsers");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ListGroupUsers);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::ListGroupUsers(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredGroupId,
		StoredLimit,
		StoredState,
		StoredCursor,
		[this](const FNakamaGroupUserList& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// ListLeaderboardRecords
UNakamaClientListLeaderboardRecords* UNakamaClientListLeaderboardRecords::ListLeaderboardRecords(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString LeaderboardId,
	const TArray<FString>& OwnerIds,
	int32 Limit,
	FString Cursor,
	int64 Expiry)
{
	UNakamaClientListLeaderboardRecords* Action = NewObject<UNakamaClientListLeaderboardRecords>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredLeaderboardId = LeaderboardId;
	Action->StoredOwnerIds = OwnerIds;
	Action->StoredLimit = Limit;
	Action->StoredCursor = Cursor;
	Action->StoredExpiry = Expiry;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientListLeaderboardRecords::Activate()
{
	static const TCHAR* TraceScope_ListLeaderboardRecords = TEXT("NakamaBP_ListLeaderboardRecords");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ListLeaderboardRecords);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::ListLeaderboardRecords(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredLeaderboardId,
		StoredOwnerIds,
		StoredLimit,
		StoredCursor,
		StoredExpiry,
		[this](const FNakamaLeaderboardRecordList& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// ListLeaderboardRecordsAroundOwner
UNakamaClientListLeaderboardRecordsAroundOwner* UNakamaClientListLeaderboardRecordsAroundOwner::ListLeaderboardRecordsAroundOwner(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString LeaderboardId,
	int32 Limit,
	FString OwnerId,
	int64 Expiry,
	FString Cursor)
{
	UNakamaClientListLeaderboardRecordsAroundOwner* Action = NewObject<UNakamaClientListLeaderboardRecordsAroundOwner>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredLeaderboardId = LeaderboardId;
	Action->StoredLimit = Limit;
	Action->StoredOwnerId = OwnerId;
	Action->StoredExpiry = Expiry;
	Action->StoredCursor = Cursor;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientListLeaderboardRecordsAroundOwner::Activate()
{
	static const TCHAR* TraceScope_ListLeaderboardRecordsAroundOwner = TEXT("NakamaBP_ListLeaderboardRecordsAroundOwner");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ListLeaderboardRecordsAroundOwner);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::ListLeaderboardRecordsAroundOwner(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredLeaderboardId,
		StoredLimit,
		StoredOwnerId,
		StoredExpiry,
		StoredCursor,
		[this](const FNakamaLeaderboardRecordList& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// ListMatches
UNakamaClientListMatches* UNakamaClientListMatches::ListMatches(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	int32 Limit,
	bool Authoritative,
	FString Label,
	int32 MinSize,
	int32 MaxSize,
	FString Query)
{
	UNakamaClientListMatches* Action = NewObject<UNakamaClientListMatches>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredLimit = Limit;
	Action->StoredAuthoritative = Authoritative;
	Action->StoredLabel = Label;
	Action->StoredMinSize = MinSize;
	Action->StoredMaxSize = MaxSize;
	Action->StoredQuery = Query;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientListMatches::Activate()
{
	static const TCHAR* TraceScope_ListMatches = TEXT("NakamaBP_ListMatches");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ListMatches);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::ListMatches(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredLimit,
		StoredAuthoritative,
		StoredLabel,
		StoredMinSize,
		StoredMaxSize,
		StoredQuery,
		[this](const FNakamaMatchList& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// ListParties
UNakamaClientListParties* UNakamaClientListParties::ListParties(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	int32 Limit,
	bool Open,
	FString Query,
	FString Cursor)
{
	UNakamaClientListParties* Action = NewObject<UNakamaClientListParties>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredLimit = Limit;
	Action->StoredOpen = Open;
	Action->StoredQuery = Query;
	Action->StoredCursor = Cursor;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientListParties::Activate()
{
	static const TCHAR* TraceScope_ListParties = TEXT("NakamaBP_ListParties");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ListParties);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::ListParties(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredLimit,
		StoredOpen,
		StoredQuery,
		StoredCursor,
		[this](const FNakamaPartyList& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// ListNotifications
UNakamaClientListNotifications* UNakamaClientListNotifications::ListNotifications(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	int32 Limit,
	FString CacheableCursor)
{
	UNakamaClientListNotifications* Action = NewObject<UNakamaClientListNotifications>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredLimit = Limit;
	Action->StoredCacheableCursor = CacheableCursor;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientListNotifications::Activate()
{
	static const TCHAR* TraceScope_ListNotifications = TEXT("NakamaBP_ListNotifications");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ListNotifications);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::ListNotifications(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredLimit,
		StoredCacheableCursor,
		[this](const FNakamaNotificationList& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// ListStorageObjects
UNakamaClientListStorageObjects* UNakamaClientListStorageObjects::ListStorageObjects(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString UserId,
	FString Collection,
	int32 Limit,
	FString Cursor)
{
	UNakamaClientListStorageObjects* Action = NewObject<UNakamaClientListStorageObjects>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredUserId = UserId;
	Action->StoredCollection = Collection;
	Action->StoredLimit = Limit;
	Action->StoredCursor = Cursor;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientListStorageObjects::Activate()
{
	static const TCHAR* TraceScope_ListStorageObjects = TEXT("NakamaBP_ListStorageObjects");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ListStorageObjects);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::ListStorageObjects(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredUserId,
		StoredCollection,
		StoredLimit,
		StoredCursor,
		[this](const FNakamaStorageObjectList& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// ListSubscriptions
UNakamaClientListSubscriptions* UNakamaClientListSubscriptions::ListSubscriptions(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	int32 Limit,
	FString Cursor)
{
	UNakamaClientListSubscriptions* Action = NewObject<UNakamaClientListSubscriptions>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredLimit = Limit;
	Action->StoredCursor = Cursor;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientListSubscriptions::Activate()
{
	static const TCHAR* TraceScope_ListSubscriptions = TEXT("NakamaBP_ListSubscriptions");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ListSubscriptions);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::ListSubscriptions(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredLimit,
		StoredCursor,
		[this](const FNakamaSubscriptionList& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// ListTournaments
UNakamaClientListTournaments* UNakamaClientListTournaments::ListTournaments(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	int32 CategoryStart,
	int32 CategoryEnd,
	int32 StartTime,
	int32 EndTime,
	int32 Limit,
	FString Cursor)
{
	UNakamaClientListTournaments* Action = NewObject<UNakamaClientListTournaments>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredCategoryStart = CategoryStart;
	Action->StoredCategoryEnd = CategoryEnd;
	Action->StoredStartTime = StartTime;
	Action->StoredEndTime = EndTime;
	Action->StoredLimit = Limit;
	Action->StoredCursor = Cursor;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientListTournaments::Activate()
{
	static const TCHAR* TraceScope_ListTournaments = TEXT("NakamaBP_ListTournaments");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ListTournaments);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::ListTournaments(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredCategoryStart,
		StoredCategoryEnd,
		StoredStartTime,
		StoredEndTime,
		StoredLimit,
		StoredCursor,
		[this](const FNakamaTournamentList& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// ListTournamentRecords
UNakamaClientListTournamentRecords* UNakamaClientListTournamentRecords::ListTournamentRecords(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString TournamentId,
	const TArray<FString>& OwnerIds,
	int32 Limit,
	FString Cursor,
	int64 Expiry)
{
	UNakamaClientListTournamentRecords* Action = NewObject<UNakamaClientListTournamentRecords>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredTournamentId = TournamentId;
	Action->StoredOwnerIds = OwnerIds;
	Action->StoredLimit = Limit;
	Action->StoredCursor = Cursor;
	Action->StoredExpiry = Expiry;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientListTournamentRecords::Activate()
{
	static const TCHAR* TraceScope_ListTournamentRecords = TEXT("NakamaBP_ListTournamentRecords");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ListTournamentRecords);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::ListTournamentRecords(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredTournamentId,
		StoredOwnerIds,
		StoredLimit,
		StoredCursor,
		StoredExpiry,
		[this](const FNakamaTournamentRecordList& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// ListTournamentRecordsAroundOwner
UNakamaClientListTournamentRecordsAroundOwner* UNakamaClientListTournamentRecordsAroundOwner::ListTournamentRecordsAroundOwner(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString TournamentId,
	int32 Limit,
	FString OwnerId,
	int64 Expiry,
	FString Cursor)
{
	UNakamaClientListTournamentRecordsAroundOwner* Action = NewObject<UNakamaClientListTournamentRecordsAroundOwner>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredTournamentId = TournamentId;
	Action->StoredLimit = Limit;
	Action->StoredOwnerId = OwnerId;
	Action->StoredExpiry = Expiry;
	Action->StoredCursor = Cursor;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientListTournamentRecordsAroundOwner::Activate()
{
	static const TCHAR* TraceScope_ListTournamentRecordsAroundOwner = TEXT("NakamaBP_ListTournamentRecordsAroundOwner");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ListTournamentRecordsAroundOwner);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::ListTournamentRecordsAroundOwner(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredTournamentId,
		StoredLimit,
		StoredOwnerId,
		StoredExpiry,
		StoredCursor,
		[this](const FNakamaTournamentRecordList& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// ListUserGroups
UNakamaClientListUserGroups* UNakamaClientListUserGroups::ListUserGroups(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString UserId,
	int32 Limit,
	int32 State,
	FString Cursor)
{
	UNakamaClientListUserGroups* Action = NewObject<UNakamaClientListUserGroups>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredUserId = UserId;
	Action->StoredLimit = Limit;
	Action->StoredState = State;
	Action->StoredCursor = Cursor;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientListUserGroups::Activate()
{
	static const TCHAR* TraceScope_ListUserGroups = TEXT("NakamaBP_ListUserGroups");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ListUserGroups);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::ListUserGroups(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredUserId,
		StoredLimit,
		StoredState,
		StoredCursor,
		[this](const FNakamaUserGroupList& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// PromoteGroupUsers
UNakamaClientPromoteGroupUsers* UNakamaClientPromoteGroupUsers::PromoteGroupUsers(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString GroupId,
	const TArray<FString>& UserIds)
{
	UNakamaClientPromoteGroupUsers* Action = NewObject<UNakamaClientPromoteGroupUsers>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredGroupId = GroupId;
	Action->StoredUserIds = UserIds;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientPromoteGroupUsers::Activate()
{
	static const TCHAR* TraceScope_PromoteGroupUsers = TEXT("NakamaBP_PromoteGroupUsers");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_PromoteGroupUsers);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::PromoteGroupUsers(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredGroupId,
		StoredUserIds,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// DemoteGroupUsers
UNakamaClientDemoteGroupUsers* UNakamaClientDemoteGroupUsers::DemoteGroupUsers(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString GroupId,
	const TArray<FString>& UserIds)
{
	UNakamaClientDemoteGroupUsers* Action = NewObject<UNakamaClientDemoteGroupUsers>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredGroupId = GroupId;
	Action->StoredUserIds = UserIds;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientDemoteGroupUsers::Activate()
{
	static const TCHAR* TraceScope_DemoteGroupUsers = TEXT("NakamaBP_DemoteGroupUsers");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_DemoteGroupUsers);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::DemoteGroupUsers(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredGroupId,
		StoredUserIds,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// ReadStorageObjects
UNakamaClientReadStorageObjects* UNakamaClientReadStorageObjects::ReadStorageObjects(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	const TArray<FNakamaReadStorageObjectId>& ObjectIds)
{
	UNakamaClientReadStorageObjects* Action = NewObject<UNakamaClientReadStorageObjects>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredObjectIds = ObjectIds;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientReadStorageObjects::Activate()
{
	static const TCHAR* TraceScope_ReadStorageObjects = TEXT("NakamaBP_ReadStorageObjects");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ReadStorageObjects);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::ReadStorageObjects(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredObjectIds,
		[this](const FNakamaStorageObjects& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// RpcFunc
UNakamaClientRpcFunc* UNakamaClientRpcFunc::RpcFunc(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString Id,
	const TMap<FString, FString>& Payload,
	FString HttpKey)
{
	UNakamaClientRpcFunc* Action = NewObject<UNakamaClientRpcFunc>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredId = Id;
	Action->StoredPayload = Payload;
	Action->StoredHttpKey = HttpKey;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientRpcFunc::Activate()
{
	static const TCHAR* TraceScope_RpcFunc = TEXT("NakamaBP_RpcFunc");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_RpcFunc);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::RpcFunc(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredId,
		[&]() -> TSharedPtr<FJsonObject> {
			if (StoredPayload.Num() == 0) { return nullptr; }
			TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
			for (const auto& Pair : StoredPayload)
			{
				Json->SetStringField(Pair.Key, Pair.Value);
			}
			return Json;
		}(),
		StoredHttpKey,
		[this](const FNakamaRpc& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// UnlinkApple
UNakamaClientUnlinkApple* UNakamaClientUnlinkApple::UnlinkApple(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString Token,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientUnlinkApple* Action = NewObject<UNakamaClientUnlinkApple>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredToken = Token;
	Action->StoredVars = Vars;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientUnlinkApple::Activate()
{
	static const TCHAR* TraceScope_UnlinkApple = TEXT("NakamaBP_UnlinkApple");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_UnlinkApple);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::UnlinkApple(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredToken,
		StoredVars,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// UnlinkCustom
UNakamaClientUnlinkCustom* UNakamaClientUnlinkCustom::UnlinkCustom(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString Id,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientUnlinkCustom* Action = NewObject<UNakamaClientUnlinkCustom>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredId = Id;
	Action->StoredVars = Vars;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientUnlinkCustom::Activate()
{
	static const TCHAR* TraceScope_UnlinkCustom = TEXT("NakamaBP_UnlinkCustom");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_UnlinkCustom);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::UnlinkCustom(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredId,
		StoredVars,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// UnlinkDevice
UNakamaClientUnlinkDevice* UNakamaClientUnlinkDevice::UnlinkDevice(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString Id,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientUnlinkDevice* Action = NewObject<UNakamaClientUnlinkDevice>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredId = Id;
	Action->StoredVars = Vars;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientUnlinkDevice::Activate()
{
	static const TCHAR* TraceScope_UnlinkDevice = TEXT("NakamaBP_UnlinkDevice");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_UnlinkDevice);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::UnlinkDevice(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredId,
		StoredVars,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// UnlinkEmail
UNakamaClientUnlinkEmail* UNakamaClientUnlinkEmail::UnlinkEmail(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString Email,
	FString Password,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientUnlinkEmail* Action = NewObject<UNakamaClientUnlinkEmail>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredEmail = Email;
	Action->StoredPassword = Password;
	Action->StoredVars = Vars;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientUnlinkEmail::Activate()
{
	static const TCHAR* TraceScope_UnlinkEmail = TEXT("NakamaBP_UnlinkEmail");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_UnlinkEmail);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::UnlinkEmail(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredEmail,
		StoredPassword,
		StoredVars,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// UnlinkFacebook
UNakamaClientUnlinkFacebook* UNakamaClientUnlinkFacebook::UnlinkFacebook(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString Token,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientUnlinkFacebook* Action = NewObject<UNakamaClientUnlinkFacebook>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredToken = Token;
	Action->StoredVars = Vars;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientUnlinkFacebook::Activate()
{
	static const TCHAR* TraceScope_UnlinkFacebook = TEXT("NakamaBP_UnlinkFacebook");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_UnlinkFacebook);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::UnlinkFacebook(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredToken,
		StoredVars,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// UnlinkFacebookInstantGame
UNakamaClientUnlinkFacebookInstantGame* UNakamaClientUnlinkFacebookInstantGame::UnlinkFacebookInstantGame(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString SignedPlayerInfo,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientUnlinkFacebookInstantGame* Action = NewObject<UNakamaClientUnlinkFacebookInstantGame>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredSignedPlayerInfo = SignedPlayerInfo;
	Action->StoredVars = Vars;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientUnlinkFacebookInstantGame::Activate()
{
	static const TCHAR* TraceScope_UnlinkFacebookInstantGame = TEXT("NakamaBP_UnlinkFacebookInstantGame");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_UnlinkFacebookInstantGame);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::UnlinkFacebookInstantGame(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredSignedPlayerInfo,
		StoredVars,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// UnlinkGameCenter
UNakamaClientUnlinkGameCenter* UNakamaClientUnlinkGameCenter::UnlinkGameCenter(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString PlayerId,
	FString BundleId,
	int64 TimestampSeconds,
	FString Salt,
	FString Signature,
	FString PublicKeyUrl,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientUnlinkGameCenter* Action = NewObject<UNakamaClientUnlinkGameCenter>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredPlayerId = PlayerId;
	Action->StoredBundleId = BundleId;
	Action->StoredTimestampSeconds = TimestampSeconds;
	Action->StoredSalt = Salt;
	Action->StoredSignature = Signature;
	Action->StoredPublicKeyUrl = PublicKeyUrl;
	Action->StoredVars = Vars;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientUnlinkGameCenter::Activate()
{
	static const TCHAR* TraceScope_UnlinkGameCenter = TEXT("NakamaBP_UnlinkGameCenter");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_UnlinkGameCenter);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::UnlinkGameCenter(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredPlayerId,
		StoredBundleId,
		StoredTimestampSeconds,
		StoredSalt,
		StoredSignature,
		StoredPublicKeyUrl,
		StoredVars,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// UnlinkGoogle
UNakamaClientUnlinkGoogle* UNakamaClientUnlinkGoogle::UnlinkGoogle(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString Token,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientUnlinkGoogle* Action = NewObject<UNakamaClientUnlinkGoogle>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredToken = Token;
	Action->StoredVars = Vars;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientUnlinkGoogle::Activate()
{
	static const TCHAR* TraceScope_UnlinkGoogle = TEXT("NakamaBP_UnlinkGoogle");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_UnlinkGoogle);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::UnlinkGoogle(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredToken,
		StoredVars,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// UnlinkSteam
UNakamaClientUnlinkSteam* UNakamaClientUnlinkSteam::UnlinkSteam(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString Token,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientUnlinkSteam* Action = NewObject<UNakamaClientUnlinkSteam>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredToken = Token;
	Action->StoredVars = Vars;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientUnlinkSteam::Activate()
{
	static const TCHAR* TraceScope_UnlinkSteam = TEXT("NakamaBP_UnlinkSteam");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_UnlinkSteam);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::UnlinkSteam(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredToken,
		StoredVars,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// UpdateAccount
UNakamaClientUpdateAccount* UNakamaClientUpdateAccount::UpdateAccount(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString Username,
	FString DisplayName,
	FString AvatarUrl,
	FString LangTag,
	FString Location,
	FString Timezone)
{
	UNakamaClientUpdateAccount* Action = NewObject<UNakamaClientUpdateAccount>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredUsername = Username;
	Action->StoredDisplayName = DisplayName;
	Action->StoredAvatarUrl = AvatarUrl;
	Action->StoredLangTag = LangTag;
	Action->StoredLocation = Location;
	Action->StoredTimezone = Timezone;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientUpdateAccount::Activate()
{
	static const TCHAR* TraceScope_UpdateAccount = TEXT("NakamaBP_UpdateAccount");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_UpdateAccount);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::UpdateAccount(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredUsername,
		StoredDisplayName,
		StoredAvatarUrl,
		StoredLangTag,
		StoredLocation,
		StoredTimezone,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// UpdateGroup
UNakamaClientUpdateGroup* UNakamaClientUpdateGroup::UpdateGroup(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString GroupId,
	FString Name,
	FString Description,
	FString LangTag,
	FString AvatarUrl,
	bool Open)
{
	UNakamaClientUpdateGroup* Action = NewObject<UNakamaClientUpdateGroup>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredGroupId = GroupId;
	Action->StoredName = Name;
	Action->StoredDescription = Description;
	Action->StoredLangTag = LangTag;
	Action->StoredAvatarUrl = AvatarUrl;
	Action->StoredOpen = Open;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientUpdateGroup::Activate()
{
	static const TCHAR* TraceScope_UpdateGroup = TEXT("NakamaBP_UpdateGroup");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_UpdateGroup);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::UpdateGroup(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredGroupId,
		StoredName,
		StoredDescription,
		StoredLangTag,
		StoredAvatarUrl,
		StoredOpen,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// ValidatePurchaseApple
UNakamaClientValidatePurchaseApple* UNakamaClientValidatePurchaseApple::ValidatePurchaseApple(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString Receipt,
	bool Persist)
{
	UNakamaClientValidatePurchaseApple* Action = NewObject<UNakamaClientValidatePurchaseApple>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredReceipt = Receipt;
	Action->StoredPersist = Persist;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientValidatePurchaseApple::Activate()
{
	static const TCHAR* TraceScope_ValidatePurchaseApple = TEXT("NakamaBP_ValidatePurchaseApple");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ValidatePurchaseApple);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::ValidatePurchaseApple(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredReceipt,
		StoredPersist,
		[this](const FNakamaValidatePurchaseResponse& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// ValidateSubscriptionApple
UNakamaClientValidateSubscriptionApple* UNakamaClientValidateSubscriptionApple::ValidateSubscriptionApple(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString Receipt,
	bool Persist)
{
	UNakamaClientValidateSubscriptionApple* Action = NewObject<UNakamaClientValidateSubscriptionApple>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredReceipt = Receipt;
	Action->StoredPersist = Persist;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientValidateSubscriptionApple::Activate()
{
	static const TCHAR* TraceScope_ValidateSubscriptionApple = TEXT("NakamaBP_ValidateSubscriptionApple");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ValidateSubscriptionApple);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::ValidateSubscriptionApple(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredReceipt,
		StoredPersist,
		[this](const FNakamaValidateSubscriptionResponse& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// ValidatePurchaseGoogle
UNakamaClientValidatePurchaseGoogle* UNakamaClientValidatePurchaseGoogle::ValidatePurchaseGoogle(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString Purchase,
	bool Persist)
{
	UNakamaClientValidatePurchaseGoogle* Action = NewObject<UNakamaClientValidatePurchaseGoogle>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredPurchase = Purchase;
	Action->StoredPersist = Persist;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientValidatePurchaseGoogle::Activate()
{
	static const TCHAR* TraceScope_ValidatePurchaseGoogle = TEXT("NakamaBP_ValidatePurchaseGoogle");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ValidatePurchaseGoogle);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::ValidatePurchaseGoogle(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredPurchase,
		StoredPersist,
		[this](const FNakamaValidatePurchaseResponse& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// ValidateSubscriptionGoogle
UNakamaClientValidateSubscriptionGoogle* UNakamaClientValidateSubscriptionGoogle::ValidateSubscriptionGoogle(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString Receipt,
	bool Persist)
{
	UNakamaClientValidateSubscriptionGoogle* Action = NewObject<UNakamaClientValidateSubscriptionGoogle>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredReceipt = Receipt;
	Action->StoredPersist = Persist;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientValidateSubscriptionGoogle::Activate()
{
	static const TCHAR* TraceScope_ValidateSubscriptionGoogle = TEXT("NakamaBP_ValidateSubscriptionGoogle");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ValidateSubscriptionGoogle);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::ValidateSubscriptionGoogle(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredReceipt,
		StoredPersist,
		[this](const FNakamaValidateSubscriptionResponse& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// ValidatePurchaseHuawei
UNakamaClientValidatePurchaseHuawei* UNakamaClientValidatePurchaseHuawei::ValidatePurchaseHuawei(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString Purchase,
	FString Signature,
	bool Persist)
{
	UNakamaClientValidatePurchaseHuawei* Action = NewObject<UNakamaClientValidatePurchaseHuawei>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredPurchase = Purchase;
	Action->StoredSignature = Signature;
	Action->StoredPersist = Persist;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientValidatePurchaseHuawei::Activate()
{
	static const TCHAR* TraceScope_ValidatePurchaseHuawei = TEXT("NakamaBP_ValidatePurchaseHuawei");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ValidatePurchaseHuawei);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::ValidatePurchaseHuawei(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredPurchase,
		StoredSignature,
		StoredPersist,
		[this](const FNakamaValidatePurchaseResponse& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// ValidatePurchaseFacebookInstant
UNakamaClientValidatePurchaseFacebookInstant* UNakamaClientValidatePurchaseFacebookInstant::ValidatePurchaseFacebookInstant(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString SignedRequest,
	bool Persist)
{
	UNakamaClientValidatePurchaseFacebookInstant* Action = NewObject<UNakamaClientValidatePurchaseFacebookInstant>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredSignedRequest = SignedRequest;
	Action->StoredPersist = Persist;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientValidatePurchaseFacebookInstant::Activate()
{
	static const TCHAR* TraceScope_ValidatePurchaseFacebookInstant = TEXT("NakamaBP_ValidatePurchaseFacebookInstant");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ValidatePurchaseFacebookInstant);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::ValidatePurchaseFacebookInstant(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredSignedRequest,
		StoredPersist,
		[this](const FNakamaValidatePurchaseResponse& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// WriteLeaderboardRecord
UNakamaClientWriteLeaderboardRecord* UNakamaClientWriteLeaderboardRecord::WriteLeaderboardRecord(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString LeaderboardId,
	FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite Record)
{
	UNakamaClientWriteLeaderboardRecord* Action = NewObject<UNakamaClientWriteLeaderboardRecord>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredLeaderboardId = LeaderboardId;
	Action->StoredRecord = Record;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientWriteLeaderboardRecord::Activate()
{
	static const TCHAR* TraceScope_WriteLeaderboardRecord = TEXT("NakamaBP_WriteLeaderboardRecord");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_WriteLeaderboardRecord);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::WriteLeaderboardRecord(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredLeaderboardId,
		StoredRecord,
		[this](const FNakamaLeaderboardRecord& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// WriteStorageObjects
UNakamaClientWriteStorageObjects* UNakamaClientWriteStorageObjects::WriteStorageObjects(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	const TArray<FNakamaWriteStorageObject>& Objects)
{
	UNakamaClientWriteStorageObjects* Action = NewObject<UNakamaClientWriteStorageObjects>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredObjects = Objects;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientWriteStorageObjects::Activate()
{
	static const TCHAR* TraceScope_WriteStorageObjects = TEXT("NakamaBP_WriteStorageObjects");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_WriteStorageObjects);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::WriteStorageObjects(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredObjects,
		[this](const FNakamaStorageObjectAcks& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// WriteTournamentRecord
UNakamaClientWriteTournamentRecord* UNakamaClientWriteTournamentRecord::WriteTournamentRecord(
	UObject* WorldContextObject,
	const FNakamaClientRef& Client,
	const FNakamaSession& Session,
	FString TournamentId,
	FNakamaWriteTournamentRecordRequest_TournamentRecordWrite Record)
{
	UNakamaClientWriteTournamentRecord* Action = NewObject<UNakamaClientWriteTournamentRecord>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredTournamentId = TournamentId;
	Action->StoredRecord = Record;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientWriteTournamentRecord::Activate()
{
	static const TCHAR* TraceScope_WriteTournamentRecord = TEXT("NakamaBP_WriteTournamentRecord");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_WriteTournamentRecord);
	FNakamaApiConfigPtr Config = Client.GetConfig();
	if (!Config)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	NakamaApi::WriteTournamentRecord(
		Config,
		MakeShared<FNakamaSession>(Session),
		StoredTournamentId,
		StoredRecord,
		[this](const FNakamaLeaderboardRecord& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// ============================================================================
// Module Implementation
// ============================================================================

#include "Modules/ModuleManager.h"

class FNakamaBlueprintsModule : public IModuleInterface
{
};

IMPLEMENT_MODULE(FNakamaBlueprintsModule, NakamaBlueprints)
