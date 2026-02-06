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
	return FNakamaClientRef(FNakamaClient::CreateDefaultClient(ServerKey, Host, Port, UseSSL, EnableDebug));
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->AddFriends(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->AddGroupUsers(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->SessionRefresh(
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->SessionLogout(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->AuthenticateApple(
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->AuthenticateCustom(
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->AuthenticateDevice(
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->AuthenticateEmail(
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->AuthenticateFacebook(
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->AuthenticateFacebookInstantGame(
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->AuthenticateGameCenter(
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->AuthenticateGoogle(
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->AuthenticateSteam(
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->BanGroupUsers(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->BlockFriends(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->CreateGroup(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->DeleteAccount(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->DeleteFriends(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->DeleteGroup(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->DeleteLeaderboardRecord(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->DeleteNotifications(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->DeleteTournamentRecord(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->DeleteStorageObjects(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->Event(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->GetAccount(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->GetUsers(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->GetSubscription(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->GetMatchmakerStats(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->Healthcheck(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->ImportFacebookFriends(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->ImportSteamFriends(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->JoinGroup(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->JoinTournament(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->KickGroupUsers(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->LeaveGroup(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->LinkApple(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->LinkCustom(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->LinkDevice(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->LinkEmail(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->LinkFacebook(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->LinkFacebookInstantGame(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->LinkGameCenter(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->LinkGoogle(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->LinkSteam(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->ListChannelMessages(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->ListFriends(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->ListFriendsOfFriends(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->ListGroups(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->ListGroupUsers(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->ListLeaderboardRecords(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->ListLeaderboardRecordsAroundOwner(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->ListMatches(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->ListParties(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->ListNotifications(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->ListStorageObjects(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->ListSubscriptions(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->ListTournaments(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->ListTournamentRecords(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->ListTournamentRecordsAroundOwner(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->ListUserGroups(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->PromoteGroupUsers(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->DemoteGroupUsers(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->ReadStorageObjects(
		Session,
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
	FString Payload,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->RpcFunc(
		Session,
		StoredId,
		StoredPayload,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->UnlinkApple(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->UnlinkCustom(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->UnlinkDevice(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->UnlinkEmail(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->UnlinkFacebook(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->UnlinkFacebookInstantGame(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->UnlinkGameCenter(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->UnlinkGoogle(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->UnlinkSteam(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->UpdateAccount(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->UpdateGroup(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->ValidatePurchaseApple(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->ValidateSubscriptionApple(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->ValidatePurchaseGoogle(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->ValidateSubscriptionGoogle(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->ValidatePurchaseHuawei(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->ValidatePurchaseFacebookInstant(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->WriteLeaderboardRecord(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->WriteStorageObjects(
		Session,
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
	TSharedPtr<FNakamaClient> ClientPtr = Client.GetClient();
	if (!ClientPtr)
	{
		FNakamaError Error;
		Error.Message = TEXT("Invalid Nakama client");
		Error.Code = -1;
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	ClientPtr->WriteTournamentRecord(
		Session,
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
