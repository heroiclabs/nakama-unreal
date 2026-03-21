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
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	FString Metadata)
{
	UNakamaClientAddFriends* Action = NewObject<UNakamaClientAddFriends>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientAddFriends> WeakThis(this);

	NakamaApi::AddFriends(
		Client,
		Session,
		StoredIds,
		StoredUsernames,
		StoredMetadata,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// AddGroupUsers
UNakamaClientAddGroupUsers* UNakamaClientAddGroupUsers::AddGroupUsers(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString GroupId,
	const TArray<FString>& UserIds)
{
	UNakamaClientAddGroupUsers* Action = NewObject<UNakamaClientAddGroupUsers>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientAddGroupUsers> WeakThis(this);

	NakamaApi::AddGroupUsers(
		Client,
		Session,
		StoredGroupId,
		StoredUserIds,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// SessionRefresh
UNakamaClientSessionRefresh* UNakamaClientSessionRefresh::SessionRefresh(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	FString Token,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientSessionRefresh* Action = NewObject<UNakamaClientSessionRefresh>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientSessionRefresh> WeakThis(this);

	NakamaApi::SessionRefresh(
		Client,
		StoredToken,
		StoredVars,
		[WeakThis](const FNakamaSession& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// SessionLogout
UNakamaClientSessionLogout* UNakamaClientSessionLogout::SessionLogout(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString Token,
	FString RefreshToken)
{
	UNakamaClientSessionLogout* Action = NewObject<UNakamaClientSessionLogout>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientSessionLogout> WeakThis(this);

	NakamaApi::SessionLogout(
		Client,
		Session,
		StoredToken,
		StoredRefreshToken,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// AuthenticateApple
UNakamaClientAuthenticateApple* UNakamaClientAuthenticateApple::AuthenticateApple(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	FString Token,
	bool Create,
	FString Username,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientAuthenticateApple* Action = NewObject<UNakamaClientAuthenticateApple>(GetTransientPackage());
	Action->Client = Client;
	Action->StoredToken = Token;
	Action->StoredVars = Vars;
	Action->StoredCreate = Create;
	Action->StoredUsername = Username;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientAuthenticateApple::Activate()
{
	static const TCHAR* TraceScope_AuthenticateApple = TEXT("NakamaBP_AuthenticateApple");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_AuthenticateApple);

	TWeakObjectPtr<UNakamaClientAuthenticateApple> WeakThis(this);
	FNakamaAccountApple StoredAccount;
	StoredAccount.Token = StoredToken;
	StoredAccount.Vars = StoredVars;

	NakamaApi::AuthenticateApple(
		Client,
		StoredAccount,
		StoredCreate,
		StoredUsername,
		[WeakThis](const FNakamaSession& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// AuthenticateCustom
UNakamaClientAuthenticateCustom* UNakamaClientAuthenticateCustom::AuthenticateCustom(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	FString Id,
	bool Create,
	FString Username,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientAuthenticateCustom* Action = NewObject<UNakamaClientAuthenticateCustom>(GetTransientPackage());
	Action->Client = Client;
	Action->StoredId = Id;
	Action->StoredVars = Vars;
	Action->StoredCreate = Create;
	Action->StoredUsername = Username;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientAuthenticateCustom::Activate()
{
	static const TCHAR* TraceScope_AuthenticateCustom = TEXT("NakamaBP_AuthenticateCustom");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_AuthenticateCustom);

	TWeakObjectPtr<UNakamaClientAuthenticateCustom> WeakThis(this);
	FNakamaAccountCustom StoredAccount;
	StoredAccount.Id = StoredId;
	StoredAccount.Vars = StoredVars;

	NakamaApi::AuthenticateCustom(
		Client,
		StoredAccount,
		StoredCreate,
		StoredUsername,
		[WeakThis](const FNakamaSession& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// AuthenticateDevice
UNakamaClientAuthenticateDevice* UNakamaClientAuthenticateDevice::AuthenticateDevice(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	FString Id,
	bool Create,
	FString Username,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientAuthenticateDevice* Action = NewObject<UNakamaClientAuthenticateDevice>(GetTransientPackage());
	Action->Client = Client;
	Action->StoredId = Id;
	Action->StoredVars = Vars;
	Action->StoredCreate = Create;
	Action->StoredUsername = Username;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientAuthenticateDevice::Activate()
{
	static const TCHAR* TraceScope_AuthenticateDevice = TEXT("NakamaBP_AuthenticateDevice");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_AuthenticateDevice);

	TWeakObjectPtr<UNakamaClientAuthenticateDevice> WeakThis(this);
	FNakamaAccountDevice StoredAccount;
	StoredAccount.Id = StoredId;
	StoredAccount.Vars = StoredVars;

	NakamaApi::AuthenticateDevice(
		Client,
		StoredAccount,
		StoredCreate,
		StoredUsername,
		[WeakThis](const FNakamaSession& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// AuthenticateEmail
UNakamaClientAuthenticateEmail* UNakamaClientAuthenticateEmail::AuthenticateEmail(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	FString Email,
	FString Password,
	bool Create,
	FString Username,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientAuthenticateEmail* Action = NewObject<UNakamaClientAuthenticateEmail>(GetTransientPackage());
	Action->Client = Client;
	Action->StoredEmail = Email;
	Action->StoredPassword = Password;
	Action->StoredVars = Vars;
	Action->StoredCreate = Create;
	Action->StoredUsername = Username;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientAuthenticateEmail::Activate()
{
	static const TCHAR* TraceScope_AuthenticateEmail = TEXT("NakamaBP_AuthenticateEmail");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_AuthenticateEmail);

	TWeakObjectPtr<UNakamaClientAuthenticateEmail> WeakThis(this);
	FNakamaAccountEmail StoredAccount;
	StoredAccount.Email = StoredEmail;
	StoredAccount.Password = StoredPassword;
	StoredAccount.Vars = StoredVars;

	NakamaApi::AuthenticateEmail(
		Client,
		StoredAccount,
		StoredCreate,
		StoredUsername,
		[WeakThis](const FNakamaSession& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// AuthenticateFacebook
UNakamaClientAuthenticateFacebook* UNakamaClientAuthenticateFacebook::AuthenticateFacebook(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	FString Token,
	bool Create,
	FString Username,
	bool Sync,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientAuthenticateFacebook* Action = NewObject<UNakamaClientAuthenticateFacebook>(GetTransientPackage());
	Action->Client = Client;
	Action->StoredToken = Token;
	Action->StoredVars = Vars;
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

	TWeakObjectPtr<UNakamaClientAuthenticateFacebook> WeakThis(this);
	FNakamaAccountFacebook StoredAccount;
	StoredAccount.Token = StoredToken;
	StoredAccount.Vars = StoredVars;

	NakamaApi::AuthenticateFacebook(
		Client,
		StoredAccount,
		StoredCreate,
		StoredUsername,
		StoredSync,
		[WeakThis](const FNakamaSession& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// AuthenticateFacebookInstantGame
UNakamaClientAuthenticateFacebookInstantGame* UNakamaClientAuthenticateFacebookInstantGame::AuthenticateFacebookInstantGame(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	FString SignedPlayerInfo,
	bool Create,
	FString Username,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientAuthenticateFacebookInstantGame* Action = NewObject<UNakamaClientAuthenticateFacebookInstantGame>(GetTransientPackage());
	Action->Client = Client;
	Action->StoredSignedPlayerInfo = SignedPlayerInfo;
	Action->StoredVars = Vars;
	Action->StoredCreate = Create;
	Action->StoredUsername = Username;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientAuthenticateFacebookInstantGame::Activate()
{
	static const TCHAR* TraceScope_AuthenticateFacebookInstantGame = TEXT("NakamaBP_AuthenticateFacebookInstantGame");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_AuthenticateFacebookInstantGame);

	TWeakObjectPtr<UNakamaClientAuthenticateFacebookInstantGame> WeakThis(this);
	FNakamaAccountFacebookInstantGame StoredAccount;
	StoredAccount.SignedPlayerInfo = StoredSignedPlayerInfo;
	StoredAccount.Vars = StoredVars;

	NakamaApi::AuthenticateFacebookInstantGame(
		Client,
		StoredAccount,
		StoredCreate,
		StoredUsername,
		[WeakThis](const FNakamaSession& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// AuthenticateGameCenter
UNakamaClientAuthenticateGameCenter* UNakamaClientAuthenticateGameCenter::AuthenticateGameCenter(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	FString PlayerId,
	FString BundleId,
	int64 TimestampSeconds,
	FString Salt,
	FString Signature,
	FString PublicKeyUrl,
	bool Create,
	FString Username,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientAuthenticateGameCenter* Action = NewObject<UNakamaClientAuthenticateGameCenter>(GetTransientPackage());
	Action->Client = Client;
	Action->StoredPlayerId = PlayerId;
	Action->StoredBundleId = BundleId;
	Action->StoredTimestampSeconds = TimestampSeconds;
	Action->StoredSalt = Salt;
	Action->StoredSignature = Signature;
	Action->StoredPublicKeyUrl = PublicKeyUrl;
	Action->StoredVars = Vars;
	Action->StoredCreate = Create;
	Action->StoredUsername = Username;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientAuthenticateGameCenter::Activate()
{
	static const TCHAR* TraceScope_AuthenticateGameCenter = TEXT("NakamaBP_AuthenticateGameCenter");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_AuthenticateGameCenter);

	TWeakObjectPtr<UNakamaClientAuthenticateGameCenter> WeakThis(this);
	FNakamaAccountGameCenter StoredAccount;
	StoredAccount.PlayerId = StoredPlayerId;
	StoredAccount.BundleId = StoredBundleId;
	StoredAccount.TimestampSeconds = StoredTimestampSeconds;
	StoredAccount.Salt = StoredSalt;
	StoredAccount.Signature = StoredSignature;
	StoredAccount.PublicKeyUrl = StoredPublicKeyUrl;
	StoredAccount.Vars = StoredVars;

	NakamaApi::AuthenticateGameCenter(
		Client,
		StoredAccount,
		StoredCreate,
		StoredUsername,
		[WeakThis](const FNakamaSession& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// AuthenticateGoogle
UNakamaClientAuthenticateGoogle* UNakamaClientAuthenticateGoogle::AuthenticateGoogle(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	FString Token,
	bool Create,
	FString Username,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientAuthenticateGoogle* Action = NewObject<UNakamaClientAuthenticateGoogle>(GetTransientPackage());
	Action->Client = Client;
	Action->StoredToken = Token;
	Action->StoredVars = Vars;
	Action->StoredCreate = Create;
	Action->StoredUsername = Username;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientAuthenticateGoogle::Activate()
{
	static const TCHAR* TraceScope_AuthenticateGoogle = TEXT("NakamaBP_AuthenticateGoogle");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_AuthenticateGoogle);

	TWeakObjectPtr<UNakamaClientAuthenticateGoogle> WeakThis(this);
	FNakamaAccountGoogle StoredAccount;
	StoredAccount.Token = StoredToken;
	StoredAccount.Vars = StoredVars;

	NakamaApi::AuthenticateGoogle(
		Client,
		StoredAccount,
		StoredCreate,
		StoredUsername,
		[WeakThis](const FNakamaSession& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// AuthenticateSteam
UNakamaClientAuthenticateSteam* UNakamaClientAuthenticateSteam::AuthenticateSteam(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	FString Token,
	bool Create,
	FString Username,
	bool Sync,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientAuthenticateSteam* Action = NewObject<UNakamaClientAuthenticateSteam>(GetTransientPackage());
	Action->Client = Client;
	Action->StoredToken = Token;
	Action->StoredVars = Vars;
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

	TWeakObjectPtr<UNakamaClientAuthenticateSteam> WeakThis(this);
	FNakamaAccountSteam StoredAccount;
	StoredAccount.Token = StoredToken;
	StoredAccount.Vars = StoredVars;

	NakamaApi::AuthenticateSteam(
		Client,
		StoredAccount,
		StoredCreate,
		StoredUsername,
		StoredSync,
		[WeakThis](const FNakamaSession& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// BanGroupUsers
UNakamaClientBanGroupUsers* UNakamaClientBanGroupUsers::BanGroupUsers(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString GroupId,
	const TArray<FString>& UserIds)
{
	UNakamaClientBanGroupUsers* Action = NewObject<UNakamaClientBanGroupUsers>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientBanGroupUsers> WeakThis(this);

	NakamaApi::BanGroupUsers(
		Client,
		Session,
		StoredGroupId,
		StoredUserIds,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// BlockFriends
UNakamaClientBlockFriends* UNakamaClientBlockFriends::BlockFriends(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames)
{
	UNakamaClientBlockFriends* Action = NewObject<UNakamaClientBlockFriends>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientBlockFriends> WeakThis(this);

	NakamaApi::BlockFriends(
		Client,
		Session,
		StoredIds,
		StoredUsernames,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// CreateGroup
UNakamaClientCreateGroup* UNakamaClientCreateGroup::CreateGroup(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString Name,
	FString Description,
	FString LangTag,
	FString AvatarUrl,
	bool Open,
	int32 MaxCount)
{
	UNakamaClientCreateGroup* Action = NewObject<UNakamaClientCreateGroup>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientCreateGroup> WeakThis(this);

	NakamaApi::CreateGroup(
		Client,
		Session,
		StoredName,
		StoredDescription,
		StoredLangTag,
		StoredAvatarUrl,
		StoredOpen,
		StoredMaxCount,
		[WeakThis](const FNakamaGroup& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// DeleteAccount
UNakamaClientDeleteAccount* UNakamaClientDeleteAccount::DeleteAccount(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session)
{
	UNakamaClientDeleteAccount* Action = NewObject<UNakamaClientDeleteAccount>(GetTransientPackage());
	Action->Client = Client;
	Action->Session = Session;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientDeleteAccount::Activate()
{
	static const TCHAR* TraceScope_DeleteAccount = TEXT("NakamaBP_DeleteAccount");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_DeleteAccount);

	TWeakObjectPtr<UNakamaClientDeleteAccount> WeakThis(this);

	NakamaApi::DeleteAccount(
		Client,
		Session,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// DeleteFriends
UNakamaClientDeleteFriends* UNakamaClientDeleteFriends::DeleteFriends(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames)
{
	UNakamaClientDeleteFriends* Action = NewObject<UNakamaClientDeleteFriends>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientDeleteFriends> WeakThis(this);

	NakamaApi::DeleteFriends(
		Client,
		Session,
		StoredIds,
		StoredUsernames,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// DeleteGroup
UNakamaClientDeleteGroup* UNakamaClientDeleteGroup::DeleteGroup(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString GroupId)
{
	UNakamaClientDeleteGroup* Action = NewObject<UNakamaClientDeleteGroup>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientDeleteGroup> WeakThis(this);

	NakamaApi::DeleteGroup(
		Client,
		Session,
		StoredGroupId,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// DeleteLeaderboardRecord
UNakamaClientDeleteLeaderboardRecord* UNakamaClientDeleteLeaderboardRecord::DeleteLeaderboardRecord(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString LeaderboardId)
{
	UNakamaClientDeleteLeaderboardRecord* Action = NewObject<UNakamaClientDeleteLeaderboardRecord>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientDeleteLeaderboardRecord> WeakThis(this);

	NakamaApi::DeleteLeaderboardRecord(
		Client,
		Session,
		StoredLeaderboardId,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// DeleteNotifications
UNakamaClientDeleteNotifications* UNakamaClientDeleteNotifications::DeleteNotifications(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	const TArray<FString>& Ids)
{
	UNakamaClientDeleteNotifications* Action = NewObject<UNakamaClientDeleteNotifications>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientDeleteNotifications> WeakThis(this);

	NakamaApi::DeleteNotifications(
		Client,
		Session,
		StoredIds,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// DeleteTournamentRecord
UNakamaClientDeleteTournamentRecord* UNakamaClientDeleteTournamentRecord::DeleteTournamentRecord(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString TournamentId)
{
	UNakamaClientDeleteTournamentRecord* Action = NewObject<UNakamaClientDeleteTournamentRecord>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientDeleteTournamentRecord> WeakThis(this);

	NakamaApi::DeleteTournamentRecord(
		Client,
		Session,
		StoredTournamentId,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// DeleteStorageObjects
UNakamaClientDeleteStorageObjects* UNakamaClientDeleteStorageObjects::DeleteStorageObjects(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	const TArray<FNakamaDeleteStorageObjectId>& ObjectIds)
{
	UNakamaClientDeleteStorageObjects* Action = NewObject<UNakamaClientDeleteStorageObjects>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientDeleteStorageObjects> WeakThis(this);

	NakamaApi::DeleteStorageObjects(
		Client,
		Session,
		StoredObjectIds,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// Event
UNakamaClientEvent* UNakamaClientEvent::Event(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString Name,
	FString Timestamp,
	bool External,
	const TMap<FString, FString>& Properties)
{
	UNakamaClientEvent* Action = NewObject<UNakamaClientEvent>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientEvent> WeakThis(this);

	NakamaApi::Event(
		Client,
		Session,
		StoredName,
		StoredTimestamp,
		StoredExternal,
		StoredProperties,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// GetAccount
UNakamaClientGetAccount* UNakamaClientGetAccount::GetAccount(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session)
{
	UNakamaClientGetAccount* Action = NewObject<UNakamaClientGetAccount>(GetTransientPackage());
	Action->Client = Client;
	Action->Session = Session;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientGetAccount::Activate()
{
	static const TCHAR* TraceScope_GetAccount = TEXT("NakamaBP_GetAccount");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_GetAccount);

	TWeakObjectPtr<UNakamaClientGetAccount> WeakThis(this);

	NakamaApi::GetAccount(
		Client,
		Session,
		[WeakThis](const FNakamaAccount& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// GetUsers
UNakamaClientGetUsers* UNakamaClientGetUsers::GetUsers(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	const TArray<FString>& FacebookIds)
{
	UNakamaClientGetUsers* Action = NewObject<UNakamaClientGetUsers>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientGetUsers> WeakThis(this);

	NakamaApi::GetUsers(
		Client,
		Session,
		StoredIds,
		StoredUsernames,
		StoredFacebookIds,
		[WeakThis](const FNakamaUsers& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// GetSubscription
UNakamaClientGetSubscription* UNakamaClientGetSubscription::GetSubscription(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString ProductId)
{
	UNakamaClientGetSubscription* Action = NewObject<UNakamaClientGetSubscription>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientGetSubscription> WeakThis(this);

	NakamaApi::GetSubscription(
		Client,
		Session,
		StoredProductId,
		[WeakThis](const FNakamaValidatedSubscription& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// GetMatchmakerStats
UNakamaClientGetMatchmakerStats* UNakamaClientGetMatchmakerStats::GetMatchmakerStats(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session)
{
	UNakamaClientGetMatchmakerStats* Action = NewObject<UNakamaClientGetMatchmakerStats>(GetTransientPackage());
	Action->Client = Client;
	Action->Session = Session;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientGetMatchmakerStats::Activate()
{
	static const TCHAR* TraceScope_GetMatchmakerStats = TEXT("NakamaBP_GetMatchmakerStats");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_GetMatchmakerStats);

	TWeakObjectPtr<UNakamaClientGetMatchmakerStats> WeakThis(this);

	NakamaApi::GetMatchmakerStats(
		Client,
		Session,
		[WeakThis](const FNakamaMatchmakerStats& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// Healthcheck
UNakamaClientHealthcheck* UNakamaClientHealthcheck::Healthcheck(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session)
{
	UNakamaClientHealthcheck* Action = NewObject<UNakamaClientHealthcheck>(GetTransientPackage());
	Action->Client = Client;
	Action->Session = Session;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientHealthcheck::Activate()
{
	static const TCHAR* TraceScope_Healthcheck = TEXT("NakamaBP_Healthcheck");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_Healthcheck);

	TWeakObjectPtr<UNakamaClientHealthcheck> WeakThis(this);

	NakamaApi::Healthcheck(
		Client,
		Session,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// ImportFacebookFriends
UNakamaClientImportFacebookFriends* UNakamaClientImportFacebookFriends::ImportFacebookFriends(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString Token,
	bool Reset,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientImportFacebookFriends* Action = NewObject<UNakamaClientImportFacebookFriends>(GetTransientPackage());
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredToken = Token;
	Action->StoredVars = Vars;
	Action->StoredReset = Reset;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientImportFacebookFriends::Activate()
{
	static const TCHAR* TraceScope_ImportFacebookFriends = TEXT("NakamaBP_ImportFacebookFriends");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ImportFacebookFriends);

	TWeakObjectPtr<UNakamaClientImportFacebookFriends> WeakThis(this);
	FNakamaAccountFacebook StoredAccount;
	StoredAccount.Token = StoredToken;
	StoredAccount.Vars = StoredVars;

	NakamaApi::ImportFacebookFriends(
		Client,
		Session,
		StoredAccount,
		StoredReset,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// ImportSteamFriends
UNakamaClientImportSteamFriends* UNakamaClientImportSteamFriends::ImportSteamFriends(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString Token,
	bool Reset,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientImportSteamFriends* Action = NewObject<UNakamaClientImportSteamFriends>(GetTransientPackage());
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredToken = Token;
	Action->StoredVars = Vars;
	Action->StoredReset = Reset;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientImportSteamFriends::Activate()
{
	static const TCHAR* TraceScope_ImportSteamFriends = TEXT("NakamaBP_ImportSteamFriends");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ImportSteamFriends);

	TWeakObjectPtr<UNakamaClientImportSteamFriends> WeakThis(this);
	FNakamaAccountSteam StoredAccount;
	StoredAccount.Token = StoredToken;
	StoredAccount.Vars = StoredVars;

	NakamaApi::ImportSteamFriends(
		Client,
		Session,
		StoredAccount,
		StoredReset,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// JoinGroup
UNakamaClientJoinGroup* UNakamaClientJoinGroup::JoinGroup(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString GroupId)
{
	UNakamaClientJoinGroup* Action = NewObject<UNakamaClientJoinGroup>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientJoinGroup> WeakThis(this);

	NakamaApi::JoinGroup(
		Client,
		Session,
		StoredGroupId,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// JoinTournament
UNakamaClientJoinTournament* UNakamaClientJoinTournament::JoinTournament(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString TournamentId)
{
	UNakamaClientJoinTournament* Action = NewObject<UNakamaClientJoinTournament>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientJoinTournament> WeakThis(this);

	NakamaApi::JoinTournament(
		Client,
		Session,
		StoredTournamentId,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// KickGroupUsers
UNakamaClientKickGroupUsers* UNakamaClientKickGroupUsers::KickGroupUsers(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString GroupId,
	const TArray<FString>& UserIds)
{
	UNakamaClientKickGroupUsers* Action = NewObject<UNakamaClientKickGroupUsers>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientKickGroupUsers> WeakThis(this);

	NakamaApi::KickGroupUsers(
		Client,
		Session,
		StoredGroupId,
		StoredUserIds,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// LeaveGroup
UNakamaClientLeaveGroup* UNakamaClientLeaveGroup::LeaveGroup(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString GroupId)
{
	UNakamaClientLeaveGroup* Action = NewObject<UNakamaClientLeaveGroup>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientLeaveGroup> WeakThis(this);

	NakamaApi::LeaveGroup(
		Client,
		Session,
		StoredGroupId,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// LinkApple
UNakamaClientLinkApple* UNakamaClientLinkApple::LinkApple(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString Token,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientLinkApple* Action = NewObject<UNakamaClientLinkApple>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientLinkApple> WeakThis(this);

	NakamaApi::LinkApple(
		Client,
		Session,
		StoredToken,
		StoredVars,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// LinkCustom
UNakamaClientLinkCustom* UNakamaClientLinkCustom::LinkCustom(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString Id,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientLinkCustom* Action = NewObject<UNakamaClientLinkCustom>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientLinkCustom> WeakThis(this);

	NakamaApi::LinkCustom(
		Client,
		Session,
		StoredId,
		StoredVars,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// LinkDevice
UNakamaClientLinkDevice* UNakamaClientLinkDevice::LinkDevice(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString Id,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientLinkDevice* Action = NewObject<UNakamaClientLinkDevice>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientLinkDevice> WeakThis(this);

	NakamaApi::LinkDevice(
		Client,
		Session,
		StoredId,
		StoredVars,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// LinkEmail
UNakamaClientLinkEmail* UNakamaClientLinkEmail::LinkEmail(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString Email,
	FString Password,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientLinkEmail* Action = NewObject<UNakamaClientLinkEmail>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientLinkEmail> WeakThis(this);

	NakamaApi::LinkEmail(
		Client,
		Session,
		StoredEmail,
		StoredPassword,
		StoredVars,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// LinkFacebook
UNakamaClientLinkFacebook* UNakamaClientLinkFacebook::LinkFacebook(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString Token,
	bool Sync,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientLinkFacebook* Action = NewObject<UNakamaClientLinkFacebook>(GetTransientPackage());
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredToken = Token;
	Action->StoredVars = Vars;
	Action->StoredSync = Sync;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientLinkFacebook::Activate()
{
	static const TCHAR* TraceScope_LinkFacebook = TEXT("NakamaBP_LinkFacebook");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_LinkFacebook);

	TWeakObjectPtr<UNakamaClientLinkFacebook> WeakThis(this);
	FNakamaAccountFacebook StoredAccount;
	StoredAccount.Token = StoredToken;
	StoredAccount.Vars = StoredVars;

	NakamaApi::LinkFacebook(
		Client,
		Session,
		StoredAccount,
		StoredSync,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// LinkFacebookInstantGame
UNakamaClientLinkFacebookInstantGame* UNakamaClientLinkFacebookInstantGame::LinkFacebookInstantGame(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString SignedPlayerInfo,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientLinkFacebookInstantGame* Action = NewObject<UNakamaClientLinkFacebookInstantGame>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientLinkFacebookInstantGame> WeakThis(this);

	NakamaApi::LinkFacebookInstantGame(
		Client,
		Session,
		StoredSignedPlayerInfo,
		StoredVars,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// LinkGameCenter
UNakamaClientLinkGameCenter* UNakamaClientLinkGameCenter::LinkGameCenter(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString PlayerId,
	FString BundleId,
	int64 TimestampSeconds,
	FString Salt,
	FString Signature,
	FString PublicKeyUrl,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientLinkGameCenter* Action = NewObject<UNakamaClientLinkGameCenter>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientLinkGameCenter> WeakThis(this);

	NakamaApi::LinkGameCenter(
		Client,
		Session,
		StoredPlayerId,
		StoredBundleId,
		StoredTimestampSeconds,
		StoredSalt,
		StoredSignature,
		StoredPublicKeyUrl,
		StoredVars,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// LinkGoogle
UNakamaClientLinkGoogle* UNakamaClientLinkGoogle::LinkGoogle(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString Token,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientLinkGoogle* Action = NewObject<UNakamaClientLinkGoogle>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientLinkGoogle> WeakThis(this);

	NakamaApi::LinkGoogle(
		Client,
		Session,
		StoredToken,
		StoredVars,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// LinkSteam
UNakamaClientLinkSteam* UNakamaClientLinkSteam::LinkSteam(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString Token,
	bool Sync,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientLinkSteam* Action = NewObject<UNakamaClientLinkSteam>(GetTransientPackage());
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredToken = Token;
	Action->StoredVars = Vars;
	Action->StoredSync = Sync;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientLinkSteam::Activate()
{
	static const TCHAR* TraceScope_LinkSteam = TEXT("NakamaBP_LinkSteam");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_LinkSteam);

	TWeakObjectPtr<UNakamaClientLinkSteam> WeakThis(this);
	FNakamaAccountSteam StoredAccount;
	StoredAccount.Token = StoredToken;
	StoredAccount.Vars = StoredVars;

	NakamaApi::LinkSteam(
		Client,
		Session,
		StoredAccount,
		StoredSync,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// ListChannelMessages
UNakamaClientListChannelMessages* UNakamaClientListChannelMessages::ListChannelMessages(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString ChannelId,
	int32 Limit,
	bool Forward,
	FString Cursor)
{
	UNakamaClientListChannelMessages* Action = NewObject<UNakamaClientListChannelMessages>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientListChannelMessages> WeakThis(this);

	NakamaApi::ListChannelMessages(
		Client,
		Session,
		StoredChannelId,
		StoredLimit,
		StoredForward,
		StoredCursor,
		[WeakThis](const FNakamaChannelMessageList& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// ListFriends
UNakamaClientListFriends* UNakamaClientListFriends::ListFriends(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	int32 Limit,
	int32 State,
	FString Cursor)
{
	UNakamaClientListFriends* Action = NewObject<UNakamaClientListFriends>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientListFriends> WeakThis(this);

	NakamaApi::ListFriends(
		Client,
		Session,
		StoredLimit,
		StoredState,
		StoredCursor,
		[WeakThis](const FNakamaFriendList& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// ListFriendsOfFriends
UNakamaClientListFriendsOfFriends* UNakamaClientListFriendsOfFriends::ListFriendsOfFriends(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	int32 Limit,
	FString Cursor)
{
	UNakamaClientListFriendsOfFriends* Action = NewObject<UNakamaClientListFriendsOfFriends>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientListFriendsOfFriends> WeakThis(this);

	NakamaApi::ListFriendsOfFriends(
		Client,
		Session,
		StoredLimit,
		StoredCursor,
		[WeakThis](const FNakamaFriendsOfFriendsList& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// ListGroups
UNakamaClientListGroups* UNakamaClientListGroups::ListGroups(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString Name,
	FString Cursor,
	int32 Limit,
	FString LangTag,
	int32 Members,
	bool Open)
{
	UNakamaClientListGroups* Action = NewObject<UNakamaClientListGroups>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientListGroups> WeakThis(this);

	NakamaApi::ListGroups(
		Client,
		Session,
		StoredName,
		StoredCursor,
		StoredLimit,
		StoredLangTag,
		StoredMembers,
		StoredOpen,
		[WeakThis](const FNakamaGroupList& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// ListGroupUsers
UNakamaClientListGroupUsers* UNakamaClientListGroupUsers::ListGroupUsers(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString GroupId,
	int32 Limit,
	int32 State,
	FString Cursor)
{
	UNakamaClientListGroupUsers* Action = NewObject<UNakamaClientListGroupUsers>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientListGroupUsers> WeakThis(this);

	NakamaApi::ListGroupUsers(
		Client,
		Session,
		StoredGroupId,
		StoredLimit,
		StoredState,
		StoredCursor,
		[WeakThis](const FNakamaGroupUserList& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// ListLeaderboardRecords
UNakamaClientListLeaderboardRecords* UNakamaClientListLeaderboardRecords::ListLeaderboardRecords(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString LeaderboardId,
	const TArray<FString>& OwnerIds,
	int32 Limit,
	FString Cursor,
	int64 Expiry)
{
	UNakamaClientListLeaderboardRecords* Action = NewObject<UNakamaClientListLeaderboardRecords>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientListLeaderboardRecords> WeakThis(this);

	NakamaApi::ListLeaderboardRecords(
		Client,
		Session,
		StoredLeaderboardId,
		StoredOwnerIds,
		StoredLimit,
		StoredCursor,
		StoredExpiry,
		[WeakThis](const FNakamaLeaderboardRecordList& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// ListLeaderboardRecordsAroundOwner
UNakamaClientListLeaderboardRecordsAroundOwner* UNakamaClientListLeaderboardRecordsAroundOwner::ListLeaderboardRecordsAroundOwner(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString LeaderboardId,
	int32 Limit,
	FString OwnerId,
	int64 Expiry,
	FString Cursor)
{
	UNakamaClientListLeaderboardRecordsAroundOwner* Action = NewObject<UNakamaClientListLeaderboardRecordsAroundOwner>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientListLeaderboardRecordsAroundOwner> WeakThis(this);

	NakamaApi::ListLeaderboardRecordsAroundOwner(
		Client,
		Session,
		StoredLeaderboardId,
		StoredLimit,
		StoredOwnerId,
		StoredExpiry,
		StoredCursor,
		[WeakThis](const FNakamaLeaderboardRecordList& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// ListMatches
UNakamaClientListMatches* UNakamaClientListMatches::ListMatches(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	int32 Limit,
	bool Authoritative,
	FString Label,
	int32 MinSize,
	int32 MaxSize,
	FString Query)
{
	UNakamaClientListMatches* Action = NewObject<UNakamaClientListMatches>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientListMatches> WeakThis(this);

	NakamaApi::ListMatches(
		Client,
		Session,
		StoredLimit,
		StoredAuthoritative,
		StoredLabel,
		StoredMinSize,
		StoredMaxSize,
		StoredQuery,
		[WeakThis](const FNakamaMatchList& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// ListParties
UNakamaClientListParties* UNakamaClientListParties::ListParties(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	int32 Limit,
	bool Open,
	FString Query,
	FString Cursor)
{
	UNakamaClientListParties* Action = NewObject<UNakamaClientListParties>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientListParties> WeakThis(this);

	NakamaApi::ListParties(
		Client,
		Session,
		StoredLimit,
		StoredOpen,
		StoredQuery,
		StoredCursor,
		[WeakThis](const FNakamaPartyList& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// ListNotifications
UNakamaClientListNotifications* UNakamaClientListNotifications::ListNotifications(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	int32 Limit,
	FString CacheableCursor)
{
	UNakamaClientListNotifications* Action = NewObject<UNakamaClientListNotifications>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientListNotifications> WeakThis(this);

	NakamaApi::ListNotifications(
		Client,
		Session,
		StoredLimit,
		StoredCacheableCursor,
		[WeakThis](const FNakamaNotificationList& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// ListStorageObjects
UNakamaClientListStorageObjects* UNakamaClientListStorageObjects::ListStorageObjects(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString UserId,
	FString Collection,
	int32 Limit,
	FString Cursor)
{
	UNakamaClientListStorageObjects* Action = NewObject<UNakamaClientListStorageObjects>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientListStorageObjects> WeakThis(this);

	NakamaApi::ListStorageObjects(
		Client,
		Session,
		StoredUserId,
		StoredCollection,
		StoredLimit,
		StoredCursor,
		[WeakThis](const FNakamaStorageObjectList& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// ListSubscriptions
UNakamaClientListSubscriptions* UNakamaClientListSubscriptions::ListSubscriptions(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	int32 Limit,
	FString Cursor)
{
	UNakamaClientListSubscriptions* Action = NewObject<UNakamaClientListSubscriptions>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientListSubscriptions> WeakThis(this);

	NakamaApi::ListSubscriptions(
		Client,
		Session,
		StoredLimit,
		StoredCursor,
		[WeakThis](const FNakamaSubscriptionList& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// ListTournaments
UNakamaClientListTournaments* UNakamaClientListTournaments::ListTournaments(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	int32 CategoryStart,
	int32 CategoryEnd,
	int32 StartTime,
	int32 EndTime,
	int32 Limit,
	FString Cursor)
{
	UNakamaClientListTournaments* Action = NewObject<UNakamaClientListTournaments>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientListTournaments> WeakThis(this);

	NakamaApi::ListTournaments(
		Client,
		Session,
		StoredCategoryStart,
		StoredCategoryEnd,
		StoredStartTime,
		StoredEndTime,
		StoredLimit,
		StoredCursor,
		[WeakThis](const FNakamaTournamentList& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// ListTournamentRecords
UNakamaClientListTournamentRecords* UNakamaClientListTournamentRecords::ListTournamentRecords(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString TournamentId,
	const TArray<FString>& OwnerIds,
	int32 Limit,
	FString Cursor,
	int64 Expiry)
{
	UNakamaClientListTournamentRecords* Action = NewObject<UNakamaClientListTournamentRecords>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientListTournamentRecords> WeakThis(this);

	NakamaApi::ListTournamentRecords(
		Client,
		Session,
		StoredTournamentId,
		StoredOwnerIds,
		StoredLimit,
		StoredCursor,
		StoredExpiry,
		[WeakThis](const FNakamaTournamentRecordList& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// ListTournamentRecordsAroundOwner
UNakamaClientListTournamentRecordsAroundOwner* UNakamaClientListTournamentRecordsAroundOwner::ListTournamentRecordsAroundOwner(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString TournamentId,
	int32 Limit,
	FString OwnerId,
	int64 Expiry,
	FString Cursor)
{
	UNakamaClientListTournamentRecordsAroundOwner* Action = NewObject<UNakamaClientListTournamentRecordsAroundOwner>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientListTournamentRecordsAroundOwner> WeakThis(this);

	NakamaApi::ListTournamentRecordsAroundOwner(
		Client,
		Session,
		StoredTournamentId,
		StoredLimit,
		StoredOwnerId,
		StoredExpiry,
		StoredCursor,
		[WeakThis](const FNakamaTournamentRecordList& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// ListUserGroups
UNakamaClientListUserGroups* UNakamaClientListUserGroups::ListUserGroups(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString UserId,
	int32 Limit,
	int32 State,
	FString Cursor)
{
	UNakamaClientListUserGroups* Action = NewObject<UNakamaClientListUserGroups>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientListUserGroups> WeakThis(this);

	NakamaApi::ListUserGroups(
		Client,
		Session,
		StoredUserId,
		StoredLimit,
		StoredState,
		StoredCursor,
		[WeakThis](const FNakamaUserGroupList& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// PromoteGroupUsers
UNakamaClientPromoteGroupUsers* UNakamaClientPromoteGroupUsers::PromoteGroupUsers(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString GroupId,
	const TArray<FString>& UserIds)
{
	UNakamaClientPromoteGroupUsers* Action = NewObject<UNakamaClientPromoteGroupUsers>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientPromoteGroupUsers> WeakThis(this);

	NakamaApi::PromoteGroupUsers(
		Client,
		Session,
		StoredGroupId,
		StoredUserIds,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// DemoteGroupUsers
UNakamaClientDemoteGroupUsers* UNakamaClientDemoteGroupUsers::DemoteGroupUsers(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString GroupId,
	const TArray<FString>& UserIds)
{
	UNakamaClientDemoteGroupUsers* Action = NewObject<UNakamaClientDemoteGroupUsers>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientDemoteGroupUsers> WeakThis(this);

	NakamaApi::DemoteGroupUsers(
		Client,
		Session,
		StoredGroupId,
		StoredUserIds,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// ReadStorageObjects
UNakamaClientReadStorageObjects* UNakamaClientReadStorageObjects::ReadStorageObjects(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	const TArray<FNakamaReadStorageObjectId>& ObjectIds)
{
	UNakamaClientReadStorageObjects* Action = NewObject<UNakamaClientReadStorageObjects>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientReadStorageObjects> WeakThis(this);

	NakamaApi::ReadStorageObjects(
		Client,
		Session,
		StoredObjectIds,
		[WeakThis](const FNakamaStorageObjects& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// RpcFunc
UNakamaClientRpcFunc* UNakamaClientRpcFunc::RpcFunc(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString Id,
	const TMap<FString, FString>& Payload,
	FString HttpKey)
{
	UNakamaClientRpcFunc* Action = NewObject<UNakamaClientRpcFunc>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientRpcFunc> WeakThis(this);

	NakamaApi::RpcFunc(
		Client,
		Session,
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
		[WeakThis](const FNakamaRpc& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// UnlinkApple
UNakamaClientUnlinkApple* UNakamaClientUnlinkApple::UnlinkApple(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString Token,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientUnlinkApple* Action = NewObject<UNakamaClientUnlinkApple>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientUnlinkApple> WeakThis(this);

	NakamaApi::UnlinkApple(
		Client,
		Session,
		StoredToken,
		StoredVars,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// UnlinkCustom
UNakamaClientUnlinkCustom* UNakamaClientUnlinkCustom::UnlinkCustom(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString Id,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientUnlinkCustom* Action = NewObject<UNakamaClientUnlinkCustom>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientUnlinkCustom> WeakThis(this);

	NakamaApi::UnlinkCustom(
		Client,
		Session,
		StoredId,
		StoredVars,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// UnlinkDevice
UNakamaClientUnlinkDevice* UNakamaClientUnlinkDevice::UnlinkDevice(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString Id,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientUnlinkDevice* Action = NewObject<UNakamaClientUnlinkDevice>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientUnlinkDevice> WeakThis(this);

	NakamaApi::UnlinkDevice(
		Client,
		Session,
		StoredId,
		StoredVars,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// UnlinkEmail
UNakamaClientUnlinkEmail* UNakamaClientUnlinkEmail::UnlinkEmail(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString Email,
	FString Password,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientUnlinkEmail* Action = NewObject<UNakamaClientUnlinkEmail>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientUnlinkEmail> WeakThis(this);

	NakamaApi::UnlinkEmail(
		Client,
		Session,
		StoredEmail,
		StoredPassword,
		StoredVars,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// UnlinkFacebook
UNakamaClientUnlinkFacebook* UNakamaClientUnlinkFacebook::UnlinkFacebook(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString Token,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientUnlinkFacebook* Action = NewObject<UNakamaClientUnlinkFacebook>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientUnlinkFacebook> WeakThis(this);

	NakamaApi::UnlinkFacebook(
		Client,
		Session,
		StoredToken,
		StoredVars,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// UnlinkFacebookInstantGame
UNakamaClientUnlinkFacebookInstantGame* UNakamaClientUnlinkFacebookInstantGame::UnlinkFacebookInstantGame(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString SignedPlayerInfo,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientUnlinkFacebookInstantGame* Action = NewObject<UNakamaClientUnlinkFacebookInstantGame>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientUnlinkFacebookInstantGame> WeakThis(this);

	NakamaApi::UnlinkFacebookInstantGame(
		Client,
		Session,
		StoredSignedPlayerInfo,
		StoredVars,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// UnlinkGameCenter
UNakamaClientUnlinkGameCenter* UNakamaClientUnlinkGameCenter::UnlinkGameCenter(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString PlayerId,
	FString BundleId,
	int64 TimestampSeconds,
	FString Salt,
	FString Signature,
	FString PublicKeyUrl,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientUnlinkGameCenter* Action = NewObject<UNakamaClientUnlinkGameCenter>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientUnlinkGameCenter> WeakThis(this);

	NakamaApi::UnlinkGameCenter(
		Client,
		Session,
		StoredPlayerId,
		StoredBundleId,
		StoredTimestampSeconds,
		StoredSalt,
		StoredSignature,
		StoredPublicKeyUrl,
		StoredVars,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// UnlinkGoogle
UNakamaClientUnlinkGoogle* UNakamaClientUnlinkGoogle::UnlinkGoogle(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString Token,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientUnlinkGoogle* Action = NewObject<UNakamaClientUnlinkGoogle>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientUnlinkGoogle> WeakThis(this);

	NakamaApi::UnlinkGoogle(
		Client,
		Session,
		StoredToken,
		StoredVars,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// UnlinkSteam
UNakamaClientUnlinkSteam* UNakamaClientUnlinkSteam::UnlinkSteam(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString Token,
	const TMap<FString, FString>& Vars)
{
	UNakamaClientUnlinkSteam* Action = NewObject<UNakamaClientUnlinkSteam>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientUnlinkSteam> WeakThis(this);

	NakamaApi::UnlinkSteam(
		Client,
		Session,
		StoredToken,
		StoredVars,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// UpdateAccount
UNakamaClientUpdateAccount* UNakamaClientUpdateAccount::UpdateAccount(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString Username,
	FString DisplayName,
	FString AvatarUrl,
	FString LangTag,
	FString Location,
	FString Timezone)
{
	UNakamaClientUpdateAccount* Action = NewObject<UNakamaClientUpdateAccount>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientUpdateAccount> WeakThis(this);

	NakamaApi::UpdateAccount(
		Client,
		Session,
		StoredUsername,
		StoredDisplayName,
		StoredAvatarUrl,
		StoredLangTag,
		StoredLocation,
		StoredTimezone,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// UpdateGroup
UNakamaClientUpdateGroup* UNakamaClientUpdateGroup::UpdateGroup(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString GroupId,
	FString Name,
	FString Description,
	FString LangTag,
	FString AvatarUrl,
	bool Open)
{
	UNakamaClientUpdateGroup* Action = NewObject<UNakamaClientUpdateGroup>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientUpdateGroup> WeakThis(this);

	NakamaApi::UpdateGroup(
		Client,
		Session,
		StoredGroupId,
		StoredName,
		StoredDescription,
		StoredLangTag,
		StoredAvatarUrl,
		StoredOpen,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// ValidatePurchaseApple
UNakamaClientValidatePurchaseApple* UNakamaClientValidatePurchaseApple::ValidatePurchaseApple(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString Receipt,
	bool Persist)
{
	UNakamaClientValidatePurchaseApple* Action = NewObject<UNakamaClientValidatePurchaseApple>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientValidatePurchaseApple> WeakThis(this);

	NakamaApi::ValidatePurchaseApple(
		Client,
		Session,
		StoredReceipt,
		StoredPersist,
		[WeakThis](const FNakamaValidatePurchaseResponse& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// ValidateSubscriptionApple
UNakamaClientValidateSubscriptionApple* UNakamaClientValidateSubscriptionApple::ValidateSubscriptionApple(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString Receipt,
	bool Persist)
{
	UNakamaClientValidateSubscriptionApple* Action = NewObject<UNakamaClientValidateSubscriptionApple>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientValidateSubscriptionApple> WeakThis(this);

	NakamaApi::ValidateSubscriptionApple(
		Client,
		Session,
		StoredReceipt,
		StoredPersist,
		[WeakThis](const FNakamaValidateSubscriptionResponse& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// ValidatePurchaseGoogle
UNakamaClientValidatePurchaseGoogle* UNakamaClientValidatePurchaseGoogle::ValidatePurchaseGoogle(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString Purchase,
	bool Persist)
{
	UNakamaClientValidatePurchaseGoogle* Action = NewObject<UNakamaClientValidatePurchaseGoogle>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientValidatePurchaseGoogle> WeakThis(this);

	NakamaApi::ValidatePurchaseGoogle(
		Client,
		Session,
		StoredPurchase,
		StoredPersist,
		[WeakThis](const FNakamaValidatePurchaseResponse& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// ValidateSubscriptionGoogle
UNakamaClientValidateSubscriptionGoogle* UNakamaClientValidateSubscriptionGoogle::ValidateSubscriptionGoogle(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString Receipt,
	bool Persist)
{
	UNakamaClientValidateSubscriptionGoogle* Action = NewObject<UNakamaClientValidateSubscriptionGoogle>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientValidateSubscriptionGoogle> WeakThis(this);

	NakamaApi::ValidateSubscriptionGoogle(
		Client,
		Session,
		StoredReceipt,
		StoredPersist,
		[WeakThis](const FNakamaValidateSubscriptionResponse& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// ValidatePurchaseHuawei
UNakamaClientValidatePurchaseHuawei* UNakamaClientValidatePurchaseHuawei::ValidatePurchaseHuawei(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString Purchase,
	FString Signature,
	bool Persist)
{
	UNakamaClientValidatePurchaseHuawei* Action = NewObject<UNakamaClientValidatePurchaseHuawei>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientValidatePurchaseHuawei> WeakThis(this);

	NakamaApi::ValidatePurchaseHuawei(
		Client,
		Session,
		StoredPurchase,
		StoredSignature,
		StoredPersist,
		[WeakThis](const FNakamaValidatePurchaseResponse& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// ValidatePurchaseFacebookInstant
UNakamaClientValidatePurchaseFacebookInstant* UNakamaClientValidatePurchaseFacebookInstant::ValidatePurchaseFacebookInstant(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString SignedRequest,
	bool Persist)
{
	UNakamaClientValidatePurchaseFacebookInstant* Action = NewObject<UNakamaClientValidatePurchaseFacebookInstant>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientValidatePurchaseFacebookInstant> WeakThis(this);

	NakamaApi::ValidatePurchaseFacebookInstant(
		Client,
		Session,
		StoredSignedRequest,
		StoredPersist,
		[WeakThis](const FNakamaValidatePurchaseResponse& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// WriteLeaderboardRecord
UNakamaClientWriteLeaderboardRecord* UNakamaClientWriteLeaderboardRecord::WriteLeaderboardRecord(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString LeaderboardId,
	int64 Score,
	int64 Subscore,
	FString Metadata,
	ENakamaOperator Operator)
{
	UNakamaClientWriteLeaderboardRecord* Action = NewObject<UNakamaClientWriteLeaderboardRecord>(GetTransientPackage());
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredLeaderboardId = LeaderboardId;
	Action->StoredScore = Score;
	Action->StoredSubscore = Subscore;
	Action->StoredMetadata = Metadata;
	Action->StoredOperator = Operator;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientWriteLeaderboardRecord::Activate()
{
	static const TCHAR* TraceScope_WriteLeaderboardRecord = TEXT("NakamaBP_WriteLeaderboardRecord");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_WriteLeaderboardRecord);

	TWeakObjectPtr<UNakamaClientWriteLeaderboardRecord> WeakThis(this);
	FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite StoredRecord;
	StoredRecord.Score = StoredScore;
	StoredRecord.Subscore = StoredSubscore;
	StoredRecord.Metadata = StoredMetadata;
	StoredRecord.Operator = StoredOperator;

	NakamaApi::WriteLeaderboardRecord(
		Client,
		Session,
		StoredLeaderboardId,
		StoredRecord,
		[WeakThis](const FNakamaLeaderboardRecord& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// WriteStorageObjects
UNakamaClientWriteStorageObjects* UNakamaClientWriteStorageObjects::WriteStorageObjects(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	const TArray<FNakamaWriteStorageObject>& Objects)
{
	UNakamaClientWriteStorageObjects* Action = NewObject<UNakamaClientWriteStorageObjects>(GetTransientPackage());
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

	TWeakObjectPtr<UNakamaClientWriteStorageObjects> WeakThis(this);

	NakamaApi::WriteStorageObjects(
		Client,
		Session,
		StoredObjects,
		[WeakThis](const FNakamaStorageObjectAcks& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// WriteTournamentRecord
UNakamaClientWriteTournamentRecord* UNakamaClientWriteTournamentRecord::WriteTournamentRecord(
	UObject* WorldContextObject,
	FNakamaClientConfig Client,
	const FNakamaSession& Session,
	FString TournamentId,
	int64 Score,
	int64 Subscore,
	FString Metadata,
	ENakamaOperator Operator)
{
	UNakamaClientWriteTournamentRecord* Action = NewObject<UNakamaClientWriteTournamentRecord>(GetTransientPackage());
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredTournamentId = TournamentId;
	Action->StoredScore = Score;
	Action->StoredSubscore = Subscore;
	Action->StoredMetadata = Metadata;
	Action->StoredOperator = Operator;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaClientWriteTournamentRecord::Activate()
{
	static const TCHAR* TraceScope_WriteTournamentRecord = TEXT("NakamaBP_WriteTournamentRecord");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_WriteTournamentRecord);

	TWeakObjectPtr<UNakamaClientWriteTournamentRecord> WeakThis(this);
	FNakamaWriteTournamentRecordRequest_TournamentRecordWrite StoredRecord;
	StoredRecord.Score = StoredScore;
	StoredRecord.Subscore = StoredSubscore;
	StoredRecord.Metadata = StoredMetadata;
	StoredRecord.Operator = StoredOperator;

	NakamaApi::WriteTournamentRecord(
		Client,
		Session,
		StoredTournamentId,
		StoredRecord,
		[WeakThis](const FNakamaLeaderboardRecord& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FNakamaError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}
