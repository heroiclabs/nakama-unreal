/**
* Copyright 2017 The Nakama Authors
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "NakamaSDK/NError.h"
#include "NakamaSDK/NFriend.h"
#include "NakamaSDK/NSelf.h"
#include "NakamaSDK/NUser.h"
#include "NakamaSDK/NUserPresence.h"
#include "NakamaSDK/NGroup.h"
#include "NakamaSDK/NCursor.h"
#include "NakamaSDK/NGroupUser.h"
#include "NakamaSDK/NResultSet.h"
#include "NakamaSDK/NStorageKey.h"
#include "NakamaSDK/NStorageData.h"
#include "NakamaSDK/NMatch.h"
#include "NakamaSDK/NMatchData.h"
#include "NakamaSDK/NMatchPresence.h"
#include "NakamaSDK/NTopicId.h"
#include "NakamaSDK/NTopic.h"
#include "NakamaSDK/NTopicMessage.h"
#include "NakamaSDK/NTopicMessageAck.h"
#include "NakamaSDK/NTopicPresence.h"
#include "NBPDataClasses.generated.h"

#define FROM_NAKAMA_DATE(date) FDateTime::FromUnixTimestamp(date/1000)

class UPlayFabJsonObject;

using namespace Nakama;

// ------------------------- NError -------------------------

UCLASS(BlueprintType)
class UNBPError : public UObject
{
	GENERATED_BODY()

public:
	static UNBPError* From(NError data);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Error")
		FString GetErrorMessage();

private:
	NError Wrapped;
};

// ------------------------- NCursor -------------------------

UCLASS(BlueprintType)
class UNBPCursor : public UObject
{
	GENERATED_BODY()

public:
	static UNBPCursor* From(NCursor data);
	NCursor GetNCursor() { return Wrapped; }

private:
	NCursor Wrapped;
};

// ------------------------- NFriend -------------------------

UENUM(BlueprintType)
enum class EFriendType : uint8
{
	Friend = 0, Invite, Invited, Blocked
};

UCLASS(BlueprintType)
class UNBPFriend : public UObject
{
	GENERATED_BODY()

public:
	static UNBPFriend* From(NFriend data);

	static TArray<UNBPFriend*> FromResultSet(NResultSet<NFriend>* resultSet);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Friend")
		FString GetAvatarUrl() { return UTF8_TO_TCHAR(Wrapped.GetAvatarUrl().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Friend")
		FDateTime GetCreatedAt() { return FROM_NAKAMA_DATE(Wrapped.GetCreatedAt()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Friend")
		FString GetFullname() { return UTF8_TO_TCHAR(Wrapped.GetFullname().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Friend")
		FString GetHandle() { return UTF8_TO_TCHAR(Wrapped.GetHandle().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Friend")
		FString GetId() { return UTF8_TO_TCHAR(Wrapped.GetId().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Friend")
		FString GetLang() { return UTF8_TO_TCHAR(Wrapped.GetLang().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Friend")
		FDateTime GetLastOnlineAt() { return FROM_NAKAMA_DATE(Wrapped.GetLastOnlineAt()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Friend")
		FString GetLocation() { return UTF8_TO_TCHAR(Wrapped.GetLocation().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Friend")
		FString GetMetadata() { return UTF8_TO_TCHAR(Wrapped.GetMetadata().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Friend")
		FString GetTimezone() { return UTF8_TO_TCHAR(Wrapped.GetTimezone().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Friend")
		FDateTime GetUpdatedAt() { return FROM_NAKAMA_DATE(Wrapped.GetUpdatedAt()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Friend")
		EFriendType GetState() { return (EFriendType)Wrapped.GetState(); }

private:
	NFriend Wrapped;
};

// ------------------------- NSelf -------------------------

UCLASS(BlueprintType)
class UNBPSelf : public UObject
{
	GENERATED_BODY()

public:
	static UNBPSelf* From(NSelf data);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Self")
		FString GetAvatarUrl() { return UTF8_TO_TCHAR(Wrapped.GetAvatarUrl().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Self")
		FDateTime GetCreatedAt() { return FROM_NAKAMA_DATE(Wrapped.GetCreatedAt()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Self")
		FString GetFullname() { return UTF8_TO_TCHAR(Wrapped.GetAvatarUrl().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Self")
		FString GetHandle() { return UTF8_TO_TCHAR(Wrapped.GetAvatarUrl().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Self")
		FString GetId() { return UTF8_TO_TCHAR(Wrapped.GetAvatarUrl().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Self")
		FString GetLang() { return UTF8_TO_TCHAR(Wrapped.GetAvatarUrl().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Self")
		FDateTime GetLastOnlineAt() { return FROM_NAKAMA_DATE(Wrapped.GetLastOnlineAt()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Self")
		FString GetLocation() { return UTF8_TO_TCHAR(Wrapped.GetAvatarUrl().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Self")
		FString GetMetadata() { return UTF8_TO_TCHAR(Wrapped.GetAvatarUrl().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Self")
		FString GetTimezone() { return UTF8_TO_TCHAR(Wrapped.GetAvatarUrl().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Self")
		FDateTime GetUpdatedAt() { return FROM_NAKAMA_DATE(Wrapped.GetUpdatedAt()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Self")
		FString GetCustomId() { return UTF8_TO_TCHAR(Wrapped.GetAvatarUrl().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Self")
		TArray<FString> GetDeviceIds();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Self")
		FString GetEmail() { return UTF8_TO_TCHAR(Wrapped.GetAvatarUrl().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Self")
		FString GetFacebookId() { return UTF8_TO_TCHAR(Wrapped.GetAvatarUrl().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Self")
		FString GetGameCenterId() { return UTF8_TO_TCHAR(Wrapped.GetAvatarUrl().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Self")
		FString GetSteamId() { return UTF8_TO_TCHAR(Wrapped.GetAvatarUrl().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Self")
		bool IsVerified() { return Wrapped.IsVerified(); }

private:
	NSelf Wrapped;
};

// ------------------------- NGroup -------------------------

UCLASS(BlueprintType)
class UNBPGroup : public UObject
{
	GENERATED_BODY()

public:
	static TArray<UNBPGroup*> FromResultSet(NResultSet<NGroup>* resultSet);

	static UNBPGroup* From(NGroup data);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group")
		FString GetId() { return UTF8_TO_TCHAR(Wrapped.GetId().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group")
		bool IsPrivate() { return Wrapped.IsPrivate(); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group")
		FString GetCreatorId() { return UTF8_TO_TCHAR(Wrapped.GetCreatorId().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group")
		FString GetName() { return UTF8_TO_TCHAR(Wrapped.GetName().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group")
		FString GetDescription() { return UTF8_TO_TCHAR(Wrapped.GetDescription().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group")
		FString GetAvatarUrl() { return UTF8_TO_TCHAR(Wrapped.GetAvatarUrl().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group")
		FString GetLang() { return UTF8_TO_TCHAR(Wrapped.GetLang().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group")
		FString GetMetadata() { return UTF8_TO_TCHAR(Wrapped.GetMetadata().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group")
		FDateTime GetCount() { return FROM_NAKAMA_DATE(Wrapped.GetCount()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group")
		FDateTime GetCreatedAt() { return FROM_NAKAMA_DATE(Wrapped.GetCreatedAt()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group")
		FDateTime GetUpdatedAt() { return FROM_NAKAMA_DATE(Wrapped.GetUpdatedAt()); }

private:
	NGroup Wrapped;
};

// ------------------------- NGroupUser -------------------------

UENUM(BlueprintType)
enum class EGroupUserType : uint8
{
	Admin = 0, Member, Join
};

UCLASS(BlueprintType)
class UNBPGroupUser : public UObject
{
	GENERATED_BODY()

public:
	static TArray<UNBPGroupUser*> FromResultSet(NResultSet<NGroupUser>* resultSet);

	static UNBPGroupUser* From(NGroupUser data);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group Users")
		FString GetAvatarUrl() { return UTF8_TO_TCHAR(Wrapped.GetAvatarUrl().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group Users")
		FDateTime GetCreatedAt() { return FROM_NAKAMA_DATE(Wrapped.GetCreatedAt()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group Users")
		FString GetFullname() { return UTF8_TO_TCHAR(Wrapped.GetFullname().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group Users")
		FString GetHandle() { return UTF8_TO_TCHAR(Wrapped.GetHandle().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group Users")
		FString GetId() { return UTF8_TO_TCHAR(Wrapped.GetId().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group Users")
		FString GetLang() { return UTF8_TO_TCHAR(Wrapped.GetLang().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group Users")
		FDateTime GetLastOnlineAt() { return FROM_NAKAMA_DATE(Wrapped.GetLastOnlineAt()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group Users")
		FString GetLocation() { return UTF8_TO_TCHAR(Wrapped.GetLocation().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group Users")
		FString GetMetadata() { return UTF8_TO_TCHAR(Wrapped.GetMetadata().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group Users")
		FString GetTimezone() { return UTF8_TO_TCHAR(Wrapped.GetTimezone().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group Users")
		FDateTime GetUpdatedAt() { return FROM_NAKAMA_DATE(Wrapped.GetUpdatedAt()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Group Users")
		EGroupUserType GetState() { return (EGroupUserType)Wrapped.GetState(); }

private:
	NGroupUser Wrapped;
};


// ------------------------- NUser -------------------------

UCLASS(BlueprintType)
class UNBPUser : public UObject
{
	GENERATED_BODY()

public:
	static TArray<UNBPUser*> FromResultSet(NResultSet<NUser>* resultSet);

	static UNBPUser* From(NUser data);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Users")
		FString GetAvatarUrl() { return UTF8_TO_TCHAR(Wrapped.GetAvatarUrl().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Users")
		FDateTime GetCreatedAt() { return FROM_NAKAMA_DATE(Wrapped.GetCreatedAt()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Users")
		FString GetFullname() { return UTF8_TO_TCHAR(Wrapped.GetFullname().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Users")
		FString GetHandle() { return UTF8_TO_TCHAR(Wrapped.GetHandle().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Users")
		FString GetId() { return UTF8_TO_TCHAR(Wrapped.GetId().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Users")
		FString GetLang() { return UTF8_TO_TCHAR(Wrapped.GetLang().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Users")
		FDateTime GetLastOnlineAt() { return FROM_NAKAMA_DATE(Wrapped.GetLastOnlineAt()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Users")
		FString GetLocation() { return UTF8_TO_TCHAR(Wrapped.GetLocation().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Users")
		FString GetMetadata() { return UTF8_TO_TCHAR(Wrapped.GetMetadata().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Users")
		FString GetTimezone() { return UTF8_TO_TCHAR(Wrapped.GetTimezone().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Users")
		FDateTime GetUpdatedAt() { return FROM_NAKAMA_DATE(Wrapped.GetUpdatedAt()); }

private:
	NUser Wrapped;
};


// ------------------------- NStorageKey -------------------------

UCLASS(BlueprintType)
class UNBPStorageKey : public UObject
{
	GENERATED_BODY()

public:
	static TArray<UNBPStorageKey*> FromResultSet(NResultSet<NStorageKey>* resultSet);

	static UNBPStorageKey* From(NStorageKey data);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Storage Key")
		FString GetBucket() { return UTF8_TO_TCHAR(Wrapped.GetBucket().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Storage Key")
		FString GetCollection() { return UTF8_TO_TCHAR(Wrapped.GetCollection().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Storage Key")
		FString GetRecord() { return UTF8_TO_TCHAR(Wrapped.GetRecord().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Storage Key")
		FString GetVersion() { return UTF8_TO_TCHAR(Wrapped.GetVersion().c_str()); }

private:
	NStorageKey Wrapped;
};


// ------------------------- NStorageData -------------------------

UCLASS(BlueprintType)
class UNBPStorageData : public UObject
{
	GENERATED_BODY()

public:
	static TArray<UNBPStorageData*> FromResultSet(NResultSet<NStorageData>* resultSet);

	static UNBPStorageData* From(NStorageData data);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Storage Data")
		FString GetBucket() { return UTF8_TO_TCHAR(Wrapped.GetBucket().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Storage Data")
		FString GetCollection() { return UTF8_TO_TCHAR(Wrapped.GetCollection().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Storage Data")
		FString GetRecord() { return UTF8_TO_TCHAR(Wrapped.GetRecord().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Storage Data")
		FString GetUserId() { return UTF8_TO_TCHAR(Wrapped.GetUserId().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Storage Data")
		FString GetValue() { return UTF8_TO_TCHAR(Wrapped.GetValue().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Storage Data")
		FString GetVersion() { return UTF8_TO_TCHAR(Wrapped.GetVersion().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Storage Data")
		int32 GetPermissionRead() { return Wrapped.GetPermissionRead(); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Storage Data")
		int32 GetPermissionWrite() { return Wrapped.GetPermissionWrite(); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Storage Data")
		FDateTime GetCreatedAt() { return FROM_NAKAMA_DATE(Wrapped.GetCreatedAt()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Storage Data")
		FDateTime GetUpdatedAt() { return FROM_NAKAMA_DATE(Wrapped.GetUpdatedAt()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Storage Data")
		FDateTime GetExpiresAt() { return FROM_NAKAMA_DATE(Wrapped.GetExpiresAt()); }

private:
	NStorageData Wrapped;
};


// ------------------------- NUserPresence -------------------------

UCLASS(BlueprintType)
class UNBPUserPresence : public UObject
{
	GENERATED_BODY()

public:
	static TArray<UNBPUserPresence*> FromArray(std::vector<NUserPresence> pArray);

	static UNBPUserPresence* From(NUserPresence data);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|User Presence")
		FString GetUserId() { return UTF8_TO_TCHAR(Wrapped.GetUserId().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|User Presence")
		FString GetSessionId() { return UTF8_TO_TCHAR(Wrapped.GetSessionId().c_str()); }

private:
	NUserPresence Wrapped;
};


// ------------------------- NMatch -------------------------

UCLASS(BlueprintType)
class UNBPMatch : public UObject
{
	GENERATED_BODY()

public:
	static UNBPMatch* From(NMatch data);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Match")
		FString GetId() { return UTF8_TO_TCHAR(Wrapped.GetId().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Match")
		TArray<UNBPUserPresence*> GetPresence() { return UNBPUserPresence::FromArray(Wrapped.GetPresence()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Match")
		UNBPUserPresence* GetSelf() { return UNBPUserPresence::From(Wrapped.GetSelf()); }

private:
	NMatch Wrapped;
};


// ------------------------- NMatchData -------------------------

UCLASS(BlueprintType)
class UNBPMatchData : public UObject
{
	GENERATED_BODY()

public:
	static UNBPMatchData* From(NMatchData data);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Match Data")
		FString GetData() { return UTF8_TO_TCHAR(Wrapped.GetData().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Match Data")
		FString GetId() { return UTF8_TO_TCHAR(Wrapped.GetId().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Match Data")
		int32 GeOpCode() { return Wrapped.GeOpCode(); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Match Data")
		UNBPUserPresence* GetPresence() { return UNBPUserPresence::From(Wrapped.GetPresence()); }

private:
	NMatchData Wrapped;
};

// ------------------------- NMatchPresence -------------------------

UCLASS(BlueprintType)
class UNBPMatchPresence : public UObject
{
	GENERATED_BODY()

public:
	static UNBPMatchPresence* From(NMatchPresence data);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Match Presence")
		FString GetId() { return UTF8_TO_TCHAR(Wrapped.GetId().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Match Presence")
		TArray<UNBPUserPresence*> GetJoin() { return  UNBPUserPresence::FromArray(Wrapped.GetJoin()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Match Presence")
		TArray<UNBPUserPresence*> GetLeave() { return  UNBPUserPresence::FromArray(Wrapped.GetLeave()); }

private:
	NMatchPresence Wrapped;
};

// ------------------------- NTopicId -------------------------

UENUM(BlueprintType)
enum class ETopicType : uint8
{
	DirectMessage = 0, Room, Group
};

UCLASS(BlueprintType)
class UNBPTopicId : public UObject
{
	GENERATED_BODY()

public:
	static UNBPTopicId* From(NTopicId data);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Topic Id")
		FString GetId() { return UTF8_TO_TCHAR(Wrapped.GetId().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Topic Id")
		ETopicType GetType() { return (ETopicType)Wrapped.GetType(); }

	NTopicId GetNTopicId() { return Wrapped; }

private:
	NTopicId Wrapped;
};

// ------------------------- NTopic -------------------------

UCLASS(BlueprintType)
class UNBPTopic : public UObject
{
	GENERATED_BODY()

public:
	static UNBPTopic* From(NTopic data);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Topic")
		UNBPTopicId* GetTopic() { return UNBPTopicId::From(Wrapped.GetTopic()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Topic")
		TArray<UNBPUserPresence*> GetPresence() { return  UNBPUserPresence::FromArray(Wrapped.GetPresence()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Topic")
		UNBPUserPresence* GetSelf() { return  UNBPUserPresence::From(Wrapped.GetSelf()); }

private:
	NTopic Wrapped;
};

// ------------------------- NTopicMessage -------------------------

UENUM(BlueprintType)
enum class ETopicMessageType : uint8
{
	Chat = 0, GroupJoin, GroupAdd, GroupLeave, GroupKick, GroupPromoted
};

UCLASS(BlueprintType)
class UNBPTopicMessage : public UObject
{
	GENERATED_BODY()

public:
	static TArray<UNBPTopicMessage*> FromResultSet(NResultSet<NTopicMessage>* resultSet);

	static UNBPTopicMessage* From(NTopicMessage data);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Topic Message")
		UNBPTopicId* GetTopic() { return UNBPTopicId::From(Wrapped.GetTopic()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Topic Message")
		FString GetUserId() { return UTF8_TO_TCHAR(Wrapped.GetUserId().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Topic Message")
		FString GetMessageId() { return UTF8_TO_TCHAR(Wrapped.GetMessageId().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Topic Message")
		int32 GetCreatedAt() { return Wrapped.GetCreatedAt(); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Topic Message")
		int32 GetExpiresAt() { return Wrapped.GetExpiresAt(); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Topic Message")
		FString GetHandle() { return UTF8_TO_TCHAR(Wrapped.GetHandle().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Topic Message")
		ETopicMessageType GetType() { return (ETopicMessageType)Wrapped.GetType(); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Topic Message")
		FString GetData() { return UTF8_TO_TCHAR(Wrapped.GetData().c_str()); }

private:
	NTopicMessage Wrapped;
};

// ------------------------- NTopicMessageAck -------------------------

UCLASS(BlueprintType)
class UNBPTopicMessageAck : public UObject
{
	GENERATED_BODY()

public:
	static UNBPTopicMessageAck* From(NTopicMessageAck data);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Topic Message Ack")
		FString GetMessageId() { return UTF8_TO_TCHAR(Wrapped.GetMessageId().c_str()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Topic Message Ack")
		int32 GetCreatedAt() { return Wrapped.GetCreatedAt(); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Topic Message Ack")
		int32 GetExpiresAt() { return Wrapped.GetExpiresAt(); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Topic Message Ack")
		FString GetHandle() { return UTF8_TO_TCHAR(Wrapped.GetHandle().c_str()); }

private:
	NTopicMessageAck Wrapped;
};

// ------------------------- NTopicPresence -------------------------

UCLASS(BlueprintType)
class UNBPTopicPresence : public UObject
{
	GENERATED_BODY()

public:
	static UNBPTopicPresence* From(NTopicPresence data);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Topic Presence")
		UNBPTopicId* GetTopic() { return UNBPTopicId::From(Wrapped.GetTopic()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Topic Presence")
		TArray<UNBPUserPresence*> GetJoin() { return  UNBPUserPresence::FromArray(Wrapped.GetJoin()); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Topic Presence")
		TArray<UNBPUserPresence*> GetLeave() { return  UNBPUserPresence::FromArray(Wrapped.GetLeave()); }

private:
	NTopicPresence Wrapped;
};
