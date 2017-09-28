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
#include "OnlineBlueprintCallProxyBase.h"
#include "NBPDataClasses.h"
#include "NakamaClientAPI.generated.h"

DECLARE_DYNAMIC_DELEGATE(FDelegateOnSuccess);
DECLARE_DYNAMIC_DELEGATE_OneParam(FDelegateOnFail, UNBPError*, error);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FDelegateOnSuccess_FriendList, TArray<UNBPFriend*>, friends, UNBPCursor*, cursor);
DECLARE_DYNAMIC_DELEGATE_OneParam(FDelegateOnSuccess_Self, UNBPSelf*, playerSelf);
DECLARE_DYNAMIC_DELEGATE_OneParam(FDelegateOnSuccess_Group, UNBPGroup*, group);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FDelegateOnSuccess_GroupList, TArray<UNBPGroup*>, groups, UNBPCursor*, cursor);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FDelegateOnSuccess_GroupSelfList, TArray<UNBPGroupSelf*>, groups, UNBPCursor*, cursor);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FDelegateOnSuccess_GroupUserList, TArray<UNBPGroupUser*>, users, UNBPCursor*, cursor);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FDelegateOnSuccess_UsersList, TArray<UNBPUser*>, users, UNBPCursor*, cursor);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FDelegateOnSuccess_StorageKeyList, TArray<UNBPStorageKey*>, keys, UNBPCursor*, cursor);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FDelegateOnSuccess_StorageDataList, TArray<UNBPStorageData*>, data, UNBPCursor*, cursor);
DECLARE_DYNAMIC_DELEGATE_OneParam(FDelegateOnSuccess_Match, UNBPMatch*, match);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FDelegateOnSuccess_MatchList, TArray<UNBPMatch*>, matches, UNBPCursor*, cursor);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FDelegateOnSuccess_TopicList, TArray<UNBPTopic*>, topics, UNBPCursor*, cursor);
DECLARE_DYNAMIC_DELEGATE_OneParam(FDelegateOnSuccess_TopicMessageAck, UNBPTopicMessageAck*, ack);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FDelegateOnSuccess_TopicMessageList, TArray<UNBPTopicMessage*>, messages, UNBPCursor*, cursor);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FDelegateOnSuccess_LeaderboardList, TArray<UNBPLeaderboard*>, leaderboards, UNBPCursor*, cursor);
DECLARE_DYNAMIC_DELEGATE_OneParam(FDelegateOnSuccess_LeaderboardRecord, UNBPLeaderboardRecord*, leaderboardRecord);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FDelegateOnSuccess_LeaderboardRecordList, TArray<UNBPLeaderboardRecord*>, leaderboardRecords, UNBPCursor*, cursor);
DECLARE_DYNAMIC_DELEGATE_OneParam(FDelegateOnSuccess_MatchmakeTicket, UNBPMatchmakeTicket*, ticket);
DECLARE_DYNAMIC_DELEGATE_OneParam(FDelegateOnSuccess_RuntimeRpc, UNBPRuntimeRpc*, rpc);
DECLARE_DYNAMIC_DELEGATE_OneParam(FDelegateOnSuccess_PurchaseRecord, UNBPPurchaseRecord*, record);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FDelegateOnSuccess_NotificationList, TArray<UNBPNotification*>, notifications, UNBPCursor*, cursor);

/**
 * Handling for Authentication
 */

UCLASS()
class UNBPAuthenticateRequest : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()
	
public:
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Client|Register")
		static UNBPAuthenticateRequest* RegisterWithCustomId(UNakamaComponent* nakama, FString id, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Client|Login")
		static UNBPAuthenticateRequest* LoginWithCustomId(UNakamaComponent* nakama, FString id, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Client|Register")
		static UNBPAuthenticateRequest* RegisterWithDeviceId(UNakamaComponent* nakama, FString deviceId, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Client|Login")
		static UNBPAuthenticateRequest* LoginWithDeviceId(UNakamaComponent* nakama, FString deviceId, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Client|Register")
		static UNBPAuthenticateRequest* RegisterWithEmail(UNakamaComponent* nakama, FString email, FString password, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Client|Login")
		static UNBPAuthenticateRequest* LoginWithEmail(UNakamaComponent* nakama, FString email, FString password, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Client|Register")
		static UNBPAuthenticateRequest* RegisterWithFacebook(UNakamaComponent* nakama, FString oauthToken, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Client|Login")
		static UNBPAuthenticateRequest* LoginWithFacebook(UNakamaComponent* nakama, FString oauthToken, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Client|Register")
		static UNBPAuthenticateRequest* RegisterWithGameCenter(UNakamaComponent* nakama, FString playerId, FString bundleId, FDateTime timestamp, FString salt, FString signature, FString publicKeyUrl, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Client|Login")
		static UNBPAuthenticateRequest* LoginWithGameCenter(UNakamaComponent* nakama, FString playerId, FString bundleId, FDateTime timestamp, FString salt, FString signature, FString publicKeyUrl, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Client|Register")
		static UNBPAuthenticateRequest* RegisterWithGoogle(UNakamaComponent* nakama, FString oauthToken, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Client|Login")
		static UNBPAuthenticateRequest* LoginWithGoogle(UNakamaComponent* nakama, FString oauthToken, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Client|Register")
		static UNBPAuthenticateRequest* RegisterWithSteam(UNakamaComponent* nakama, FString sessionToken, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Client|Login")
		static UNBPAuthenticateRequest* LoginWithSteam(UNakamaComponent* nakama, FString sessionToken, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

private:
	enum AuthType { Custom, Device, Email, Facebook, GameCenter, Google, Steam };
	AuthType type;
	bool Register;
	UPROPERTY() FString PrimaryId;
	UPROPERTY() FString Password;
	UPROPERTY() FString BundleId;
	UPROPERTY() FDateTime Timestamp;
	UPROPERTY() FString Salt;
	UPROPERTY() FString Signature;
	UPROPERTY() FString PublicKeyUrl;
	UPROPERTY() UNakamaComponent* NakamaRef;
	UPROPERTY() FDelegateOnSuccess OnSuccess;
	UPROPERTY() FDelegateOnFail OnFail;
};


/**
* Handling for Friends
*/

UCLASS()
class UNBPManageFriendRequest : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Friends")
		static UNBPManageFriendRequest* AddFriendByUserId(UNakamaComponent* nakama, FString userId, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Friends")
		static UNBPManageFriendRequest* AddFriendByHandle(UNakamaComponent* nakama, FString handle, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Friends")
		static UNBPManageFriendRequest* BlockFriendByUserId(UNakamaComponent* nakama, FString userId, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Friends")
		static UNBPManageFriendRequest* RemoveFriendByUserId(UNakamaComponent* nakama, FString userId, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Friends")
		static UNBPManageFriendRequest* ListFriends(UNakamaComponent* nakama, FDelegateOnSuccess_FriendList onSuccess, FDelegateOnFail onFail);

private:
	enum Mode { Add, AddHandle, Block, Remove, List };

	Mode mode;
	UPROPERTY() FString Id;
	UPROPERTY() UNakamaComponent* NakamaRef;
	UPROPERTY() FDelegateOnSuccess OnManageSuccess;
	UPROPERTY() FDelegateOnSuccess_FriendList OnListSuccess;
	UPROPERTY() FDelegateOnFail OnFail;
};


/**
* Handling for Self
*/

UCLASS()
class UNBPSelfFetchRequest : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Self")
		static UNBPSelfFetchRequest* FetchSelf(UNakamaComponent* nakama, FDelegateOnSuccess_Self onSuccess, FDelegateOnFail onFail);

private:
	UPROPERTY() UNakamaComponent* NakamaRef;
	UPROPERTY() FDelegateOnSuccess_Self OnSuccess;
	UPROPERTY() FDelegateOnFail OnFail;
};

UCLASS()
class UNBPSelfUpdateRequest : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Self")
		static UNBPSelfUpdateRequest* UpdateSelf(UNakamaComponent* nakama, FString handle, FString fullname, FString avatarUrl, FString lang, FString location, FString metadata, FString timezone, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

private:
	UPROPERTY() FString Handle;
	UPROPERTY() FString Fullname;
	UPROPERTY() FString AvatarUrl;
	UPROPERTY() FString Lang;
	UPROPERTY() FString Location;
	UPROPERTY() FString Metadata;
	UPROPERTY() FString Timezone;
	UPROPERTY() UNakamaComponent* NakamaRef;
	UPROPERTY() FDelegateOnSuccess OnSuccess;
	UPROPERTY() FDelegateOnFail OnFail;
};

UCLASS()
class UNBPSelfLinkRequest : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Client|Register")
		static UNBPSelfLinkRequest* LinkCustomId(UNakamaComponent* nakama, FString id, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Client|Login")
		static UNBPSelfLinkRequest* UnlinkCustomId(UNakamaComponent* nakama, FString id, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Client|Register")
		static UNBPSelfLinkRequest* LinkDeviceId(UNakamaComponent* nakama, FString deviceId, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Client|Login")
		static UNBPSelfLinkRequest* UnlinkDeviceId(UNakamaComponent* nakama, FString deviceId, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Client|Register")
		static UNBPSelfLinkRequest* LinkEmail(UNakamaComponent* nakama, FString email, FString password, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Client|Login")
		static UNBPSelfLinkRequest* UnlinkEmail(UNakamaComponent* nakama, FString email, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Client|Register")
		static UNBPSelfLinkRequest* LinkFacebook(UNakamaComponent* nakama, FString oauthToken, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Client|Login")
		static UNBPSelfLinkRequest* UnlinkFacebook(UNakamaComponent* nakama, FString oauthToken, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Client|Register")
		static UNBPSelfLinkRequest* LinkGameCenter(UNakamaComponent* nakama, FString playerId, FString bundleId, FDateTime timestamp, FString salt, FString signature, FString publicKeyUrl, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Client|Login")
		static UNBPSelfLinkRequest* UnlinkGameCenter(UNakamaComponent* nakama, FString playerId, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Client|Register")
		static UNBPSelfLinkRequest* LinkGoogle(UNakamaComponent* nakama, FString oauthToken, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Client|Login")
		static UNBPSelfLinkRequest* UnlinkGoogle(UNakamaComponent* nakama, FString oauthToken, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Client|Register")
		static UNBPSelfLinkRequest* LinkSteam(UNakamaComponent* nakama, FString sessionToken, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Client|Login")
		static UNBPSelfLinkRequest* UnlinkSteam(UNakamaComponent* nakama, FString sessionToken, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

private:
	enum AuthType { Custom, Device, Email, Facebook, GameCenter, Google, Steam };
	AuthType type;
	bool Link;
	UPROPERTY() FString PrimaryId;
	UPROPERTY() FString Password;
	UPROPERTY() FString BundleId;
	UPROPERTY() FDateTime Timestamp;
	UPROPERTY() FString Salt;
	UPROPERTY() FString Signature;
	UPROPERTY() FString PublicKeyUrl;
	UPROPERTY() UNakamaComponent* NakamaRef;
	UPROPERTY() FDelegateOnSuccess OnSuccess;
	UPROPERTY() FDelegateOnFail OnFail;
};


/**
* Handling for Groups
*/

UCLASS()
class UNBPManageGroupsRequest : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Group")
		static UNBPManageGroupsRequest* CreateGroup(UNakamaComponent* nakama, FString name, FString description, FString avatarUrl, FString lang, FString metadata, bool privateGroup, FDelegateOnSuccess_GroupList onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Group")
		static UNBPManageGroupsRequest* RemoveGroup(UNakamaComponent* nakama, FString groupId, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Group")
		static UNBPManageGroupsRequest* UpdateGroup(UNakamaComponent* nakama, FString groupId, FString name, FString description, FString avatarUrl, FString lang, FString metadata, bool privateGroup, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

private:
	enum Mode { Create, Remove, Update };

	Mode mode;
	UPROPERTY() FString GroupId;
	UPROPERTY() FString Name;
	UPROPERTY() FString Description;
	UPROPERTY() FString AvatarUrl;
	UPROPERTY() FString Lang;
	UPROPERTY() FString Metadata;
	UPROPERTY() bool PrivateGroup;
	UPROPERTY() UNakamaComponent* NakamaRef;
	UPROPERTY() FDelegateOnSuccess OnManageSuccess;
	UPROPERTY() FDelegateOnSuccess_GroupList OnGroupSuccess;
	UPROPERTY() FDelegateOnFail OnFail;
};


UCLASS()
class UNBPListGroupsRequest : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Group")
		static UNBPListGroupsRequest* FetchGroups(UNakamaComponent* nakama, TArray<FString> groupIds, TArray<FString> names, FDelegateOnSuccess_GroupList onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Group")
		static UNBPListGroupsRequest* ListGroups(UNakamaComponent* nakama, int32 pageLimit, bool ascending, UNBPCursor* cursor, FString filterByLang, FDateTime filterByCreatedAt, int32 filterByCount, FDelegateOnSuccess_GroupList onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Group")
		static UNBPListGroupsRequest* ListSelfGroups(UNakamaComponent* nakama, FDelegateOnSuccess_GroupSelfList onSuccess, FDelegateOnFail onFail);

private:
	enum Mode { Fetch, List, SelfList };

	Mode mode;
	UPROPERTY() TArray<FString> GroupIds;
	UPROPERTY() TArray<FString> Names;
	UPROPERTY() int32 PageLimit;
	UPROPERTY() bool Ascending;
	UPROPERTY() UNBPCursor* Cursor = nullptr;
	UPROPERTY() FString FilterByLang;
	UPROPERTY() FDateTime FilterByCreatedAt;
	UPROPERTY() int32 FilterByCount;
	UPROPERTY() UNakamaComponent* NakamaRef;
	UPROPERTY() FDelegateOnSuccess_GroupList OnSuccess;
	UPROPERTY() FDelegateOnSuccess_GroupSelfList OnSelfSuccess;
	UPROPERTY() FDelegateOnFail OnFail;
};


UCLASS()
class UNBPJoinLeaveGroupRequest : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Group")
		static UNBPJoinLeaveGroupRequest* JoinGroup(UNakamaComponent* nakama, FString groupId, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Group")
		static UNBPJoinLeaveGroupRequest* LeaveGroup(UNakamaComponent* nakama, FString groupId, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

private:
	enum Mode { Join, Leave };

	Mode mode;
	UPROPERTY() FString GroupId;
	UPROPERTY() UNakamaComponent* NakamaRef;
	UPROPERTY() FDelegateOnSuccess OnSuccess;
	UPROPERTY() FDelegateOnFail OnFail;
};


/**
* Handling for GroupUsers
*/

UCLASS()
class UNBPManageGroupUsersRequest : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Group Users")
		static UNBPManageGroupUsersRequest* AddUserToGroup(UNakamaComponent* nakama, FString groupId, FString userId, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Group Users")
		static UNBPManageGroupUsersRequest* KickUserFromGroup(UNakamaComponent* nakama, FString groupId, FString userId, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Group Users")
		static UNBPManageGroupUsersRequest* PromoteGroupUser(UNakamaComponent* nakama, FString groupId, FString userId, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Group Users")
		static UNBPManageGroupUsersRequest* ListGroupUsers(UNakamaComponent* nakama, FString groupId, FDelegateOnSuccess_GroupUserList onSuccess, FDelegateOnFail onFail);

private:
	enum Mode { Add, Kick, Promote, List };

	Mode mode;
	UPROPERTY() FString GroupId;
	UPROPERTY() FString UserId;
	UPROPERTY() UNakamaComponent* NakamaRef;
	UPROPERTY() FDelegateOnSuccess OnManageSuccess;
	UPROPERTY() FDelegateOnSuccess_GroupUserList OnListSuccess;
	UPROPERTY() FDelegateOnFail OnFail;
};


/**
* Handling for Users
*/

UCLASS()
class UNBPListUsersRequest : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Users")
		static UNBPListUsersRequest* FetchUsersById(UNakamaComponent* nakama, TArray<FString> userIds, FDelegateOnSuccess_UsersList onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Users")
		static UNBPListUsersRequest* FetchUsersByHandle(UNakamaComponent* nakama, TArray<FString> handles, FDelegateOnSuccess_UsersList onSuccess, FDelegateOnFail onFail);

private:
	UPROPERTY() TArray<FString> UserIds;
	UPROPERTY() TArray<FString> Handles;
	UPROPERTY() UNakamaComponent* NakamaRef;
	UPROPERTY() FDelegateOnSuccess_UsersList OnSuccess;
	UPROPERTY() FDelegateOnFail OnFail;
};


/**
* Handling for Storage
*/

UCLASS()
class UNBPStorageRequest : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Storage")
		static UNBPStorageRequest* Write(UNakamaComponent* nakama, FString bucket, FString collection, FString record, FString value, FString version, FDelegateOnSuccess_StorageKeyList onSuccess, FDelegateOnFail onFail, EStoragePermissionRead readPermission = EStoragePermissionRead::OwnerRead, EStoragePermissionWrite writePermission = EStoragePermissionWrite::OwnerWrite);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Storage")
		static UNBPStorageRequest* WriteMany(UNakamaComponent* nakama, TArray<FString> buckets, TArray<FString> collections, TArray<FString> records, TArray<FString> values, TArray<FString> versions, FDelegateOnSuccess_StorageKeyList onSuccess, FDelegateOnFail onFail, TArray<EStoragePermissionRead> readPermission, TArray<EStoragePermissionWrite> writePermission);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Storage")
		static UNBPStorageRequest* Update(UNakamaComponent* nakama, FString bucket, FString collection, FString record, UNBPStorateUpdateOps* operations, FDelegateOnSuccess_StorageKeyList onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Storage")
		static UNBPStorageRequest* UpdateFull(UNakamaComponent* nakama, FString bucket, FString collection, FString record, FString version, UNBPStorateUpdateOps* operations, FDelegateOnSuccess_StorageKeyList onSuccess, FDelegateOnFail onFail, EStoragePermissionRead readPermission = EStoragePermissionRead::OwnerRead, EStoragePermissionWrite writePermission = EStoragePermissionWrite::OwnerWrite);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Storage")
		static UNBPStorageRequest* Fetch(UNakamaComponent* nakama, FString bucket, FString collection, FString record, FString userId, FDelegateOnSuccess_StorageDataList onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Storage")
		static UNBPStorageRequest* FetchMany(UNakamaComponent* nakama, TArray<FString> buckets, TArray<FString> collections, TArray<FString> records, TArray<FString> userIds, FDelegateOnSuccess_StorageDataList onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Storage")
		static UNBPStorageRequest* List(UNakamaComponent* nakama, FString bucket, FString collection, FString userId, UNBPCursor* cursor, int32 limit, FDelegateOnSuccess_StorageDataList onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Storage")
		static UNBPStorageRequest* Remove(UNakamaComponent* nakama, FString bucket, FString collection, FString record, FString version, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Storage")
		static UNBPStorageRequest* RemoveMany(UNakamaComponent* nakama, TArray<FString> buckets, TArray<FString> collections, TArray<FString> records, TArray<FString> versions, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

private:
	enum Mode { WriteData, FetchData, ListData, RemoveData, UpdateData };

	Mode mode;

	UPROPERTY() TArray<FString> Buckets;
	UPROPERTY() TArray<FString> Collections;
	UPROPERTY() TArray<FString> Records;
	UPROPERTY() TArray<FString> Values;
	UPROPERTY() TArray<FString> UserIds;
	UPROPERTY() TArray<FString> Versions;
	UPROPERTY() UNBPStorateUpdateOps* Operations;
	UPROPERTY() TArray<EStoragePermissionRead> ReadPermissions;
	UPROPERTY() TArray<EStoragePermissionWrite> WritePermissions;
	UPROPERTY() UNBPCursor* Cursor = nullptr;
	UPROPERTY() int32 Limit;
	UPROPERTY() UNakamaComponent* NakamaRef;
	UPROPERTY() FDelegateOnSuccess OnVoidSuccess;
	UPROPERTY() FDelegateOnSuccess_StorageKeyList OnKeySuccess;
	UPROPERTY() FDelegateOnSuccess_StorageDataList OnDataSuccess;
	UPROPERTY() FDelegateOnFail OnFail;
};


/**
* Handling for Matches
*/

UCLASS()
class UNBPMatchRequest : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Match")
		static UNBPMatchRequest* CreateMatch(UNakamaComponent* nakama, FDelegateOnSuccess_Match onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Match")
		static UNBPMatchRequest* JoinMatch(UNakamaComponent* nakama, FString matchId, FDelegateOnSuccess_MatchList onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Match")
		static UNBPMatchRequest* LeaveMatch(UNakamaComponent* nakama, FString matchId, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Match")
		static UNBPMatchRequest* SendData(UNakamaComponent* nakama, FString matchId, int32 opCode, FString data, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

private:
	enum Mode { Create, Join, Leave, Post };

	Mode mode;

	UPROPERTY() FString MatchId;
	UPROPERTY() int32 OpCode;
	UPROPERTY() FString Data;
	UPROPERTY() UNakamaComponent* NakamaRef;
	UPROPERTY() FDelegateOnSuccess_Match OnCreateSuccess;
	UPROPERTY() FDelegateOnSuccess_MatchList OnJoinSuccess;
	UPROPERTY() FDelegateOnSuccess OnLeaveSendSuccess;
	UPROPERTY() FDelegateOnFail OnFail;
};


/**
* Handling for Topics
*/

UCLASS()
class UNBPTopicRequest : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Topic")
		static UNBPTopicRequest* JoinDirectMessageTopic(UNakamaComponent* nakama, FString userId, FDelegateOnSuccess_TopicList onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Topic")
		static UNBPTopicRequest* JoinRoomTopic(UNakamaComponent* nakama, FString room, FDelegateOnSuccess_TopicList onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Topic")
		static UNBPTopicRequest* JoinGroupTopic(UNakamaComponent* nakama, FString groupId, FDelegateOnSuccess_TopicList onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Topic")
		static UNBPTopicRequest* LeaveTopic(UNakamaComponent* nakama, UNBPTopicId* topicId, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Topic")
		static UNBPTopicRequest* SendTopicMessage(UNakamaComponent* nakama, UNBPTopicId* topicId, FString data, FDelegateOnSuccess_TopicMessageAck onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Topic")
		static UNBPTopicRequest* ListDirectMessageTopicMessages(UNakamaComponent* nakama, FString userId, UNBPCursor* cursor, bool forward, int32 limit, FDelegateOnSuccess_TopicMessageList onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Topic")
		static UNBPTopicRequest* ListRoomTopicMessages(UNakamaComponent* nakama, FString room, UNBPCursor* cursor, bool forward, int32 limit, FDelegateOnSuccess_TopicMessageList onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Topic")
		static UNBPTopicRequest* ListGroupTopicMessages(UNakamaComponent* nakama, FString groupId, UNBPCursor* cursor, bool forward, int32 limit, FDelegateOnSuccess_TopicMessageList onSuccess, FDelegateOnFail onFail);

private:
	enum Mode { Join, Leave, Send, List };

	Mode mode;
	TopicType TType;

	UPROPERTY() FString Id;
	UPROPERTY() UNBPTopicId* TopicId;
	UPROPERTY() FString Data;
	UPROPERTY() bool Forward;
	UPROPERTY() UNBPCursor* Cursor = nullptr;
	UPROPERTY() int32 Limit;
	UPROPERTY() UNakamaComponent* NakamaRef;
	UPROPERTY() FDelegateOnSuccess_TopicList OnJoinSuccess;
	UPROPERTY() FDelegateOnSuccess OnLeaveSuccess;
	UPROPERTY() FDelegateOnSuccess_TopicMessageAck OnSendSuccess;
	UPROPERTY() FDelegateOnSuccess_TopicMessageList OnListSuccess;
	UPROPERTY() FDelegateOnFail OnFail;
};


/**
* Handling for Leaderboards
*/

UCLASS()
class UNBPListLeaderboardsRequest : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Leaderboard")
		static UNBPListLeaderboardsRequest* ListLeaderboards(UNakamaComponent* nakama, UNBPCursor* cursor, int32 limit, FDelegateOnSuccess_LeaderboardList onSuccess, FDelegateOnFail onFail);

private:
	UPROPERTY() UNBPCursor* Cursor = nullptr;
	UPROPERTY() int32 Limit;
	UPROPERTY() UNakamaComponent* NakamaRef;
	UPROPERTY() FDelegateOnSuccess_LeaderboardList OnSuccess;
	UPROPERTY() FDelegateOnFail OnFail;
};


/**
* Handling for LeaderboardRecords
*/

UCLASS()
class UNBPLeaderboardRecordsRequest : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Leaderboard Record")
		static UNBPLeaderboardRecordsRequest* FetchRecords(UNakamaComponent* nakama, FString leaderboardId, UNBPCursor* cursor, int32 limit, FDelegateOnSuccess_LeaderboardRecordList onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Leaderboard Record")
		static UNBPLeaderboardRecordsRequest* ListRecords(UNakamaComponent* nakama, FString leaderboardId, TArray<FString> ownerIdsFilter, FString langFilter, FString locationFilter, FString timezoneFilter, UNBPCursor* cursor, int32 limit, FDelegateOnSuccess_LeaderboardRecordList onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Leaderboard Record")
		static UNBPLeaderboardRecordsRequest* WriteRecord(UNakamaComponent* nakama, FString leaderboardId, FString location, FString timezone, FString metadata, int32 setValue, int32 bestValue, int32 incr, int32 decr, FDelegateOnSuccess_LeaderboardRecordList onSuccess, FDelegateOnFail onFail);

private:
	enum Mode { Fetch, List, Write };

	Mode mode;

	UPROPERTY() FString LeaderboardId;
	UPROPERTY() TArray<FString> OwnerIds;
	UPROPERTY() FString Location;
	UPROPERTY() FString Timezone;
	UPROPERTY() FString Metadata;
	UPROPERTY() FString Lang;
	UPROPERTY() int32 Set;
	UPROPERTY() int32 Best;
	UPROPERTY() int32 Incr;
	UPROPERTY() int32 Decr;
	UPROPERTY() UNBPCursor* Cursor = nullptr;
	UPROPERTY() int32 Limit;
	UPROPERTY() UNakamaComponent* NakamaRef;
	UPROPERTY() FDelegateOnSuccess_LeaderboardRecordList OnSuccess;
	UPROPERTY() FDelegateOnFail OnFail;
};


/**
* Handling for Matchmaking
*/

UCLASS()
class UNBPMatchmakeRequest : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Matchmake")
		static UNBPMatchmakeRequest* AddRequest(UNakamaComponent* nakama, int32 requiredCount, FDelegateOnSuccess_MatchmakeTicket onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Matchmake")
		static UNBPMatchmakeRequest* RemoveRequest(UNakamaComponent* nakama, UNBPMatchmakeTicket* ticket, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

private:
	enum Mode { Add, Remove };

	Mode mode;

	UPROPERTY() UNBPMatchmakeTicket* Ticket = nullptr;
	UPROPERTY() int32 RequiredCount;
	UPROPERTY() UNakamaComponent* NakamaRef;
	UPROPERTY() FDelegateOnSuccess_MatchmakeTicket OnAddSuccess;
	UPROPERTY() FDelegateOnSuccess OnRemoveSuccess;
	UPROPERTY() FDelegateOnFail OnFail;
};


/**
* Handling for Notifications
*/

UCLASS()
class UNBPNotificationRequest : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Notification")
		static UNBPNotificationRequest* ListMessages(UNakamaComponent* nakama, UNBPCursor* cursor, int32 limit, FDelegateOnSuccess_NotificationList onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Notification")
		static UNBPNotificationRequest* RemoveMessage(UNakamaComponent* nakama, FString notificationId, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Notification")
		static UNBPNotificationRequest* RemoveMessages(UNakamaComponent* nakama, TArray<FString> notificationIds, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail);

private:
	enum Mode { List, Remove };

	Mode mode;

	UPROPERTY() TArray<FString> NotificationIds;
	UPROPERTY() UNBPCursor* Cursor = nullptr;
	UPROPERTY() int32 Limit;
	UPROPERTY() UNakamaComponent* NakamaRef;
	UPROPERTY() FDelegateOnSuccess_NotificationList OnListSuccess;
	UPROPERTY() FDelegateOnSuccess OnRemoveSuccess;
	UPROPERTY() FDelegateOnFail OnFail;
};


/**
* Handling for PurchaseValidations
*/

UCLASS()
class UNBPPurchaseValidationRequest : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Purchase Validation")
		static UNBPPurchaseValidationRequest* ValidateApplePurchase(UNakamaComponent* nakama, FString productId, FString receiptData, FDelegateOnSuccess_PurchaseRecord onSuccess, FDelegateOnFail onFail);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Purchase Validation")
		static UNBPPurchaseValidationRequest* ValidateGooglePurchase(UNakamaComponent* nakama, FString productId, FString productType, FString purchaseToken, FDelegateOnSuccess_PurchaseRecord onSuccess, FDelegateOnFail onFail);

private:
	enum Mode { Apple, Google };

	Mode mode;

	UPROPERTY() FString ProductId;
	UPROPERTY() FString ReceiptData;
	UPROPERTY() FString ProductType;
	UPROPERTY() FString PurchaseToken;
	UPROPERTY() UNakamaComponent* NakamaRef;
	UPROPERTY() FDelegateOnSuccess_PurchaseRecord OnSuccess;
	UPROPERTY() FDelegateOnFail OnFail;
};


/**
* Handling for RPC
*/

UCLASS()
class UNBPRpcRequest : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Nakama|Matchmake")
		static UNBPRpcRequest* RunRpc(UNakamaComponent* nakama, FString id, FString payload, FDelegateOnSuccess_RuntimeRpc onSuccess, FDelegateOnFail onFail);

private:
	UPROPERTY() FString Id;
	UPROPERTY() FString Payload;
	UPROPERTY() UNakamaComponent* NakamaRef;
	UPROPERTY() FDelegateOnSuccess_RuntimeRpc OnSuccess;
	UPROPERTY() FDelegateOnFail OnFail;
};
