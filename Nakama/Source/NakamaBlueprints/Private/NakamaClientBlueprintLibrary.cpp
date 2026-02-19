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
// Async Action Classes Implementation
// ============================================================================

// AddFriends
UNakamaClientAddFriends* UNakamaClientAddFriends::AddFriends(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::AddFriends(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredIds,
		StoredUsernames,
		StoredMetadata,
		[this]()
		{
			OnSuccess.Broadcast();
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// AddGroupUsers
UNakamaClientAddGroupUsers* UNakamaClientAddGroupUsers::AddGroupUsers(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::AddGroupUsers(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredGroupId,
		StoredUserIds,
		[this]()
		{
			OnSuccess.Broadcast();
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// SessionRefresh
UNakamaClientSessionRefresh* UNakamaClientSessionRefresh::SessionRefresh(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::SessionRefresh(
		Client,
		StoredToken,
		StoredVars,
		[this](const FNakamaSession& Result)
		{
			OnSuccess.Broadcast(Result);
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// SessionLogout
UNakamaClientSessionLogout* UNakamaClientSessionLogout::SessionLogout(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::SessionLogout(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredToken,
		StoredRefreshToken,
		[this]()
		{
			OnSuccess.Broadcast();
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// AuthenticateApple
UNakamaClientAuthenticateApple* UNakamaClientAuthenticateApple::AuthenticateApple(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::AuthenticateApple(
		Client,
		StoredAccount,
		StoredCreate,
		StoredUsername,
		[this](const FNakamaSession& Result)
		{
			OnSuccess.Broadcast(Result);
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// AuthenticateCustom
UNakamaClientAuthenticateCustom* UNakamaClientAuthenticateCustom::AuthenticateCustom(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::AuthenticateCustom(
		Client,
		StoredAccount,
		StoredCreate,
		StoredUsername,
		[this](const FNakamaSession& Result)
		{
			OnSuccess.Broadcast(Result);
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// AuthenticateDevice
UNakamaClientAuthenticateDevice* UNakamaClientAuthenticateDevice::AuthenticateDevice(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::AuthenticateDevice(
		Client,
		StoredAccount,
		StoredCreate,
		StoredUsername,
		[this](const FNakamaSession& Result)
		{
			OnSuccess.Broadcast(Result);
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// AuthenticateEmail
UNakamaClientAuthenticateEmail* UNakamaClientAuthenticateEmail::AuthenticateEmail(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::AuthenticateEmail(
		Client,
		StoredAccount,
		StoredCreate,
		StoredUsername,
		[this](const FNakamaSession& Result)
		{
			OnSuccess.Broadcast(Result);
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// AuthenticateFacebook
UNakamaClientAuthenticateFacebook* UNakamaClientAuthenticateFacebook::AuthenticateFacebook(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::AuthenticateFacebook(
		Client,
		StoredAccount,
		StoredCreate,
		StoredUsername,
		StoredSync,
		[this](const FNakamaSession& Result)
		{
			OnSuccess.Broadcast(Result);
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// AuthenticateFacebookInstantGame
UNakamaClientAuthenticateFacebookInstantGame* UNakamaClientAuthenticateFacebookInstantGame::AuthenticateFacebookInstantGame(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::AuthenticateFacebookInstantGame(
		Client,
		StoredAccount,
		StoredCreate,
		StoredUsername,
		[this](const FNakamaSession& Result)
		{
			OnSuccess.Broadcast(Result);
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// AuthenticateGameCenter
UNakamaClientAuthenticateGameCenter* UNakamaClientAuthenticateGameCenter::AuthenticateGameCenter(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::AuthenticateGameCenter(
		Client,
		StoredAccount,
		StoredCreate,
		StoredUsername,
		[this](const FNakamaSession& Result)
		{
			OnSuccess.Broadcast(Result);
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// AuthenticateGoogle
UNakamaClientAuthenticateGoogle* UNakamaClientAuthenticateGoogle::AuthenticateGoogle(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::AuthenticateGoogle(
		Client,
		StoredAccount,
		StoredCreate,
		StoredUsername,
		[this](const FNakamaSession& Result)
		{
			OnSuccess.Broadcast(Result);
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// AuthenticateSteam
UNakamaClientAuthenticateSteam* UNakamaClientAuthenticateSteam::AuthenticateSteam(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::AuthenticateSteam(
		Client,
		StoredAccount,
		StoredCreate,
		StoredUsername,
		StoredSync,
		[this](const FNakamaSession& Result)
		{
			OnSuccess.Broadcast(Result);
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// BanGroupUsers
UNakamaClientBanGroupUsers* UNakamaClientBanGroupUsers::BanGroupUsers(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::BanGroupUsers(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredGroupId,
		StoredUserIds,
		[this]()
		{
			OnSuccess.Broadcast();
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// BlockFriends
UNakamaClientBlockFriends* UNakamaClientBlockFriends::BlockFriends(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::BlockFriends(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredIds,
		StoredUsernames,
		[this]()
		{
			OnSuccess.Broadcast();
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// CreateGroup
UNakamaClientCreateGroup* UNakamaClientCreateGroup::CreateGroup(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::CreateGroup(
		Client,
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
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// DeleteAccount
UNakamaClientDeleteAccount* UNakamaClientDeleteAccount::DeleteAccount(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::DeleteAccount(
		Client,
		MakeShared<FNakamaSession>(Session),
		[this]()
		{
			OnSuccess.Broadcast();
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// DeleteFriends
UNakamaClientDeleteFriends* UNakamaClientDeleteFriends::DeleteFriends(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::DeleteFriends(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredIds,
		StoredUsernames,
		[this]()
		{
			OnSuccess.Broadcast();
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// DeleteGroup
UNakamaClientDeleteGroup* UNakamaClientDeleteGroup::DeleteGroup(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::DeleteGroup(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredGroupId,
		[this]()
		{
			OnSuccess.Broadcast();
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// DeleteLeaderboardRecord
UNakamaClientDeleteLeaderboardRecord* UNakamaClientDeleteLeaderboardRecord::DeleteLeaderboardRecord(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::DeleteLeaderboardRecord(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredLeaderboardId,
		[this]()
		{
			OnSuccess.Broadcast();
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// DeleteNotifications
UNakamaClientDeleteNotifications* UNakamaClientDeleteNotifications::DeleteNotifications(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::DeleteNotifications(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredIds,
		[this]()
		{
			OnSuccess.Broadcast();
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// DeleteTournamentRecord
UNakamaClientDeleteTournamentRecord* UNakamaClientDeleteTournamentRecord::DeleteTournamentRecord(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::DeleteTournamentRecord(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredTournamentId,
		[this]()
		{
			OnSuccess.Broadcast();
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// DeleteStorageObjects
UNakamaClientDeleteStorageObjects* UNakamaClientDeleteStorageObjects::DeleteStorageObjects(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::DeleteStorageObjects(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredObjectIds,
		[this]()
		{
			OnSuccess.Broadcast();
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// Event
UNakamaClientEvent* UNakamaClientEvent::Event(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::Event(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredName,
		StoredTimestamp,
		StoredExternal,
		StoredProperties,
		[this]()
		{
			OnSuccess.Broadcast();
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// GetAccount
UNakamaClientGetAccount* UNakamaClientGetAccount::GetAccount(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::GetAccount(
		Client,
		MakeShared<FNakamaSession>(Session),
		[this](const FNakamaAccount& Result)
		{
			OnSuccess.Broadcast(Result);
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// GetUsers
UNakamaClientGetUsers* UNakamaClientGetUsers::GetUsers(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::GetUsers(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredIds,
		StoredUsernames,
		StoredFacebookIds,
		[this](const FNakamaUsers& Result)
		{
			OnSuccess.Broadcast(Result);
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// GetSubscription
UNakamaClientGetSubscription* UNakamaClientGetSubscription::GetSubscription(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::GetSubscription(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredProductId,
		[this](const FNakamaValidatedSubscription& Result)
		{
			OnSuccess.Broadcast(Result);
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// GetMatchmakerStats
UNakamaClientGetMatchmakerStats* UNakamaClientGetMatchmakerStats::GetMatchmakerStats(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::GetMatchmakerStats(
		Client,
		MakeShared<FNakamaSession>(Session),
		[this](const FNakamaMatchmakerStats& Result)
		{
			OnSuccess.Broadcast(Result);
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// Healthcheck
UNakamaClientHealthcheck* UNakamaClientHealthcheck::Healthcheck(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::Healthcheck(
		Client,
		MakeShared<FNakamaSession>(Session),
		[this]()
		{
			OnSuccess.Broadcast();
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// ImportFacebookFriends
UNakamaClientImportFacebookFriends* UNakamaClientImportFacebookFriends::ImportFacebookFriends(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::ImportFacebookFriends(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredAccount,
		StoredReset,
		[this]()
		{
			OnSuccess.Broadcast();
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// ImportSteamFriends
UNakamaClientImportSteamFriends* UNakamaClientImportSteamFriends::ImportSteamFriends(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::ImportSteamFriends(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredAccount,
		StoredReset,
		[this]()
		{
			OnSuccess.Broadcast();
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// JoinGroup
UNakamaClientJoinGroup* UNakamaClientJoinGroup::JoinGroup(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::JoinGroup(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredGroupId,
		[this]()
		{
			OnSuccess.Broadcast();
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// JoinTournament
UNakamaClientJoinTournament* UNakamaClientJoinTournament::JoinTournament(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::JoinTournament(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredTournamentId,
		[this]()
		{
			OnSuccess.Broadcast();
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// KickGroupUsers
UNakamaClientKickGroupUsers* UNakamaClientKickGroupUsers::KickGroupUsers(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::KickGroupUsers(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredGroupId,
		StoredUserIds,
		[this]()
		{
			OnSuccess.Broadcast();
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// LeaveGroup
UNakamaClientLeaveGroup* UNakamaClientLeaveGroup::LeaveGroup(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::LeaveGroup(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredGroupId,
		[this]()
		{
			OnSuccess.Broadcast();
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// LinkApple
UNakamaClientLinkApple* UNakamaClientLinkApple::LinkApple(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::LinkApple(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredToken,
		StoredVars,
		[this]()
		{
			OnSuccess.Broadcast();
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// LinkCustom
UNakamaClientLinkCustom* UNakamaClientLinkCustom::LinkCustom(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::LinkCustom(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredId,
		StoredVars,
		[this]()
		{
			OnSuccess.Broadcast();
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// LinkDevice
UNakamaClientLinkDevice* UNakamaClientLinkDevice::LinkDevice(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::LinkDevice(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredId,
		StoredVars,
		[this]()
		{
			OnSuccess.Broadcast();
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// LinkEmail
UNakamaClientLinkEmail* UNakamaClientLinkEmail::LinkEmail(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::LinkEmail(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredEmail,
		StoredPassword,
		StoredVars,
		[this]()
		{
			OnSuccess.Broadcast();
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// LinkFacebook
UNakamaClientLinkFacebook* UNakamaClientLinkFacebook::LinkFacebook(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::LinkFacebook(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredAccount,
		StoredSync,
		[this]()
		{
			OnSuccess.Broadcast();
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// LinkFacebookInstantGame
UNakamaClientLinkFacebookInstantGame* UNakamaClientLinkFacebookInstantGame::LinkFacebookInstantGame(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::LinkFacebookInstantGame(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredSignedPlayerInfo,
		StoredVars,
		[this]()
		{
			OnSuccess.Broadcast();
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// LinkGameCenter
UNakamaClientLinkGameCenter* UNakamaClientLinkGameCenter::LinkGameCenter(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::LinkGameCenter(
		Client,
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
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// LinkGoogle
UNakamaClientLinkGoogle* UNakamaClientLinkGoogle::LinkGoogle(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::LinkGoogle(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredToken,
		StoredVars,
		[this]()
		{
			OnSuccess.Broadcast();
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// LinkSteam
UNakamaClientLinkSteam* UNakamaClientLinkSteam::LinkSteam(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::LinkSteam(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredAccount,
		StoredSync,
		[this]()
		{
			OnSuccess.Broadcast();
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// ListChannelMessages
UNakamaClientListChannelMessages* UNakamaClientListChannelMessages::ListChannelMessages(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::ListChannelMessages(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredChannelId,
		StoredLimit,
		StoredForward,
		StoredCursor,
		[this](const FNakamaChannelMessageList& Result)
		{
			OnSuccess.Broadcast(Result);
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// ListFriends
UNakamaClientListFriends* UNakamaClientListFriends::ListFriends(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::ListFriends(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredLimit,
		StoredState,
		StoredCursor,
		[this](const FNakamaFriendList& Result)
		{
			OnSuccess.Broadcast(Result);
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// ListFriendsOfFriends
UNakamaClientListFriendsOfFriends* UNakamaClientListFriendsOfFriends::ListFriendsOfFriends(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::ListFriendsOfFriends(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredLimit,
		StoredCursor,
		[this](const FNakamaFriendsOfFriendsList& Result)
		{
			OnSuccess.Broadcast(Result);
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// ListGroups
UNakamaClientListGroups* UNakamaClientListGroups::ListGroups(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::ListGroups(
		Client,
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
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// ListGroupUsers
UNakamaClientListGroupUsers* UNakamaClientListGroupUsers::ListGroupUsers(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::ListGroupUsers(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredGroupId,
		StoredLimit,
		StoredState,
		StoredCursor,
		[this](const FNakamaGroupUserList& Result)
		{
			OnSuccess.Broadcast(Result);
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// ListLeaderboardRecords
UNakamaClientListLeaderboardRecords* UNakamaClientListLeaderboardRecords::ListLeaderboardRecords(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::ListLeaderboardRecords(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredLeaderboardId,
		StoredOwnerIds,
		StoredLimit,
		StoredCursor,
		StoredExpiry,
		[this](const FNakamaLeaderboardRecordList& Result)
		{
			OnSuccess.Broadcast(Result);
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// ListLeaderboardRecordsAroundOwner
UNakamaClientListLeaderboardRecordsAroundOwner* UNakamaClientListLeaderboardRecordsAroundOwner::ListLeaderboardRecordsAroundOwner(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::ListLeaderboardRecordsAroundOwner(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredLeaderboardId,
		StoredLimit,
		StoredOwnerId,
		StoredExpiry,
		StoredCursor,
		[this](const FNakamaLeaderboardRecordList& Result)
		{
			OnSuccess.Broadcast(Result);
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// ListMatches
UNakamaClientListMatches* UNakamaClientListMatches::ListMatches(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::ListMatches(
		Client,
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
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// ListParties
UNakamaClientListParties* UNakamaClientListParties::ListParties(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::ListParties(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredLimit,
		StoredOpen,
		StoredQuery,
		StoredCursor,
		[this](const FNakamaPartyList& Result)
		{
			OnSuccess.Broadcast(Result);
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// ListNotifications
UNakamaClientListNotifications* UNakamaClientListNotifications::ListNotifications(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::ListNotifications(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredLimit,
		StoredCacheableCursor,
		[this](const FNakamaNotificationList& Result)
		{
			OnSuccess.Broadcast(Result);
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// ListStorageObjects
UNakamaClientListStorageObjects* UNakamaClientListStorageObjects::ListStorageObjects(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::ListStorageObjects(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredUserId,
		StoredCollection,
		StoredLimit,
		StoredCursor,
		[this](const FNakamaStorageObjectList& Result)
		{
			OnSuccess.Broadcast(Result);
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// ListSubscriptions
UNakamaClientListSubscriptions* UNakamaClientListSubscriptions::ListSubscriptions(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::ListSubscriptions(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredLimit,
		StoredCursor,
		[this](const FNakamaSubscriptionList& Result)
		{
			OnSuccess.Broadcast(Result);
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// ListTournaments
UNakamaClientListTournaments* UNakamaClientListTournaments::ListTournaments(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::ListTournaments(
		Client,
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
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// ListTournamentRecords
UNakamaClientListTournamentRecords* UNakamaClientListTournamentRecords::ListTournamentRecords(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::ListTournamentRecords(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredTournamentId,
		StoredOwnerIds,
		StoredLimit,
		StoredCursor,
		StoredExpiry,
		[this](const FNakamaTournamentRecordList& Result)
		{
			OnSuccess.Broadcast(Result);
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// ListTournamentRecordsAroundOwner
UNakamaClientListTournamentRecordsAroundOwner* UNakamaClientListTournamentRecordsAroundOwner::ListTournamentRecordsAroundOwner(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::ListTournamentRecordsAroundOwner(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredTournamentId,
		StoredLimit,
		StoredOwnerId,
		StoredExpiry,
		StoredCursor,
		[this](const FNakamaTournamentRecordList& Result)
		{
			OnSuccess.Broadcast(Result);
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// ListUserGroups
UNakamaClientListUserGroups* UNakamaClientListUserGroups::ListUserGroups(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::ListUserGroups(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredUserId,
		StoredLimit,
		StoredState,
		StoredCursor,
		[this](const FNakamaUserGroupList& Result)
		{
			OnSuccess.Broadcast(Result);
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// PromoteGroupUsers
UNakamaClientPromoteGroupUsers* UNakamaClientPromoteGroupUsers::PromoteGroupUsers(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::PromoteGroupUsers(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredGroupId,
		StoredUserIds,
		[this]()
		{
			OnSuccess.Broadcast();
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// DemoteGroupUsers
UNakamaClientDemoteGroupUsers* UNakamaClientDemoteGroupUsers::DemoteGroupUsers(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::DemoteGroupUsers(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredGroupId,
		StoredUserIds,
		[this]()
		{
			OnSuccess.Broadcast();
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// ReadStorageObjects
UNakamaClientReadStorageObjects* UNakamaClientReadStorageObjects::ReadStorageObjects(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::ReadStorageObjects(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredObjectIds,
		[this](const FNakamaStorageObjects& Result)
		{
			OnSuccess.Broadcast(Result);
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// RpcFunc
UNakamaClientRpcFunc* UNakamaClientRpcFunc::RpcFunc(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::RpcFunc(
		Client,
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
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// UnlinkApple
UNakamaClientUnlinkApple* UNakamaClientUnlinkApple::UnlinkApple(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::UnlinkApple(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredToken,
		StoredVars,
		[this]()
		{
			OnSuccess.Broadcast();
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// UnlinkCustom
UNakamaClientUnlinkCustom* UNakamaClientUnlinkCustom::UnlinkCustom(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::UnlinkCustom(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredId,
		StoredVars,
		[this]()
		{
			OnSuccess.Broadcast();
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// UnlinkDevice
UNakamaClientUnlinkDevice* UNakamaClientUnlinkDevice::UnlinkDevice(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::UnlinkDevice(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredId,
		StoredVars,
		[this]()
		{
			OnSuccess.Broadcast();
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// UnlinkEmail
UNakamaClientUnlinkEmail* UNakamaClientUnlinkEmail::UnlinkEmail(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::UnlinkEmail(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredEmail,
		StoredPassword,
		StoredVars,
		[this]()
		{
			OnSuccess.Broadcast();
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// UnlinkFacebook
UNakamaClientUnlinkFacebook* UNakamaClientUnlinkFacebook::UnlinkFacebook(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::UnlinkFacebook(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredToken,
		StoredVars,
		[this]()
		{
			OnSuccess.Broadcast();
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// UnlinkFacebookInstantGame
UNakamaClientUnlinkFacebookInstantGame* UNakamaClientUnlinkFacebookInstantGame::UnlinkFacebookInstantGame(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::UnlinkFacebookInstantGame(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredSignedPlayerInfo,
		StoredVars,
		[this]()
		{
			OnSuccess.Broadcast();
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// UnlinkGameCenter
UNakamaClientUnlinkGameCenter* UNakamaClientUnlinkGameCenter::UnlinkGameCenter(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::UnlinkGameCenter(
		Client,
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
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// UnlinkGoogle
UNakamaClientUnlinkGoogle* UNakamaClientUnlinkGoogle::UnlinkGoogle(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::UnlinkGoogle(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredToken,
		StoredVars,
		[this]()
		{
			OnSuccess.Broadcast();
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// UnlinkSteam
UNakamaClientUnlinkSteam* UNakamaClientUnlinkSteam::UnlinkSteam(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::UnlinkSteam(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredToken,
		StoredVars,
		[this]()
		{
			OnSuccess.Broadcast();
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// UpdateAccount
UNakamaClientUpdateAccount* UNakamaClientUpdateAccount::UpdateAccount(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::UpdateAccount(
		Client,
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
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// UpdateGroup
UNakamaClientUpdateGroup* UNakamaClientUpdateGroup::UpdateGroup(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::UpdateGroup(
		Client,
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
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// ValidatePurchaseApple
UNakamaClientValidatePurchaseApple* UNakamaClientValidatePurchaseApple::ValidatePurchaseApple(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::ValidatePurchaseApple(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredReceipt,
		StoredPersist,
		[this](const FNakamaValidatePurchaseResponse& Result)
		{
			OnSuccess.Broadcast(Result);
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// ValidateSubscriptionApple
UNakamaClientValidateSubscriptionApple* UNakamaClientValidateSubscriptionApple::ValidateSubscriptionApple(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::ValidateSubscriptionApple(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredReceipt,
		StoredPersist,
		[this](const FNakamaValidateSubscriptionResponse& Result)
		{
			OnSuccess.Broadcast(Result);
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// ValidatePurchaseGoogle
UNakamaClientValidatePurchaseGoogle* UNakamaClientValidatePurchaseGoogle::ValidatePurchaseGoogle(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::ValidatePurchaseGoogle(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredPurchase,
		StoredPersist,
		[this](const FNakamaValidatePurchaseResponse& Result)
		{
			OnSuccess.Broadcast(Result);
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// ValidateSubscriptionGoogle
UNakamaClientValidateSubscriptionGoogle* UNakamaClientValidateSubscriptionGoogle::ValidateSubscriptionGoogle(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::ValidateSubscriptionGoogle(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredReceipt,
		StoredPersist,
		[this](const FNakamaValidateSubscriptionResponse& Result)
		{
			OnSuccess.Broadcast(Result);
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// ValidatePurchaseHuawei
UNakamaClientValidatePurchaseHuawei* UNakamaClientValidatePurchaseHuawei::ValidatePurchaseHuawei(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::ValidatePurchaseHuawei(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredPurchase,
		StoredSignature,
		StoredPersist,
		[this](const FNakamaValidatePurchaseResponse& Result)
		{
			OnSuccess.Broadcast(Result);
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// ValidatePurchaseFacebookInstant
UNakamaClientValidatePurchaseFacebookInstant* UNakamaClientValidatePurchaseFacebookInstant::ValidatePurchaseFacebookInstant(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::ValidatePurchaseFacebookInstant(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredSignedRequest,
		StoredPersist,
		[this](const FNakamaValidatePurchaseResponse& Result)
		{
			OnSuccess.Broadcast(Result);
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// WriteLeaderboardRecord
UNakamaClientWriteLeaderboardRecord* UNakamaClientWriteLeaderboardRecord::WriteLeaderboardRecord(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::WriteLeaderboardRecord(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredLeaderboardId,
		StoredRecord,
		[this](const FNakamaLeaderboardRecord& Result)
		{
			OnSuccess.Broadcast(Result);
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// WriteStorageObjects
UNakamaClientWriteStorageObjects* UNakamaClientWriteStorageObjects::WriteStorageObjects(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::WriteStorageObjects(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredObjects,
		[this](const FNakamaStorageObjectAcks& Result)
		{
			OnSuccess.Broadcast(Result);
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
			SetReadyToDestroy();
		}
	);
}

// WriteTournamentRecord
UNakamaClientWriteTournamentRecord* UNakamaClientWriteTournamentRecord::WriteTournamentRecord(
	UObject* WorldContextObject,
	FNakamaApiConfig Client,
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

	AddToRoot();

	NakamaApi::WriteTournamentRecord(
		Client,
		MakeShared<FNakamaSession>(Session),
		StoredTournamentId,
		StoredRecord,
		[this](const FNakamaLeaderboardRecord& Result)
		{
			OnSuccess.Broadcast(Result);
			RemoveFromRoot();
			SetReadyToDestroy();
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(Error);
			RemoveFromRoot();
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
