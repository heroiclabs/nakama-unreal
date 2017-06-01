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

#include "NakamaClientAPI.h"
#include "NakamaSDK/NAuthenticateMessage.h"
#include "NakamaSDK/NFriendAddMessage.h"
#include "NakamaSDK/NFriendBlockMessage.h"
#include "NakamaSDK/NFriendRemoveMessage.h"
#include "NakamaSDK/NFriendsListMessage.h"
#include "NakamaSDK/NSelfFetchMessage.h"
#include "NakamaSDK/NSelfLinkMessage.h"
#include "NakamaSDK/NSelfUnlinkMessage.h"
#include "NakamaSDK/NSelfUpdateMessage.h"
#include "NakamaSDK/NGroupAddUserMessage.h"
#include "NakamaSDK/NGroupKickUserMessage.h"
#include "NakamaSDK/NGroupPromoteUserMessage.h"
#include "NakamaSDK/NGroupUsersListMessage.h"
#include "NakamaSDK/NGroupCreateMessage.h"
#include "NakamaSDK/NGroupRemoveMessage.h"
#include "NakamaSDK/NGroupUpdateMessage.h"
#include "NakamaSDK/NGroupsListMessage.h"
#include "NakamaSDK/NGroupsFetchMessage.h"
#include "NakamaSDK/NGroupsSelfListMessage.h"
#include "NakamaSDK/NGroupJoinMessage.h"
#include "NakamaSDK/NGroupLeaveMessage.h"
#include "NakamaSDK/NUsersFetchMessage.h"
#include "NakamaSDK/NStorageFetchMessage.h"
#include "NakamaSDK/NStorageRemoveMessage.h"
#include "NakamaSDK/NStorageWriteMessage.h"
#include "NakamaSDK/NMatchCreateMessage.h"
#include "NakamaSDK/NMatchJoinMessage.h"
#include "NakamaSDK/NMatchLeaveMessage.h"
#include "NakamaSDK/NMatchDataSendMessage.h"
#include "NakamaSDK/NTopicJoinMessage.h"
#include "NakamaSDK/NTopicLeaveMessage.h"
#include "NakamaSDK/NTopicMessageSendMessage.h"
#include "NakamaSDK/NTopicMessagesListMessage.h"
#include "NakamaSDK/NLeaderboardRecordsFetchMessage.h"
#include "NakamaSDK/NLeaderboardRecordsListMessage.h"
#include "NakamaSDK/NLeaderboardRecordWriteMessage.h"
#include "NakamaSDK/NLeaderboardsListMessage.h"
#include "NakamaComponent.h"

using namespace Nakama;

/**
 * Handling for Authentication
 */

// ------------------------- Custom -------------------------

UNBPAuthenticateRequest* UNBPAuthenticateRequest::RegisterWithCustomId(UNakamaComponent* nakama,
	FString id,
	FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPAuthenticateRequest>();
	proxy->PrimaryId = id;
	proxy->NakamaRef = nakama;
	proxy->OnSuccess = onSuccess;
	proxy->OnFail = onFail;
	proxy->Register = true;
	proxy->type = AuthType::Custom;
	return proxy;
}

UNBPAuthenticateRequest* UNBPAuthenticateRequest::LoginWithCustomId(UNakamaComponent* nakama,
	FString id,
	FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPAuthenticateRequest>();
	proxy->PrimaryId = id;
	proxy->NakamaRef = nakama;
	proxy->OnSuccess = onSuccess;
	proxy->OnFail = onFail;
	proxy->Register = false;
	proxy->type = AuthType::Custom;
	return proxy;
}

// ------------------------- Device -------------------------

UNBPAuthenticateRequest* UNBPAuthenticateRequest::RegisterWithDeviceId(UNakamaComponent* nakama,
	FString deviceId,
	FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPAuthenticateRequest>();
	proxy->PrimaryId = deviceId;
	proxy->NakamaRef = nakama;
	proxy->OnSuccess = onSuccess;
	proxy->OnFail = onFail;
	proxy->Register = true;
	proxy->type = AuthType::Device;
	return proxy;
}

UNBPAuthenticateRequest* UNBPAuthenticateRequest::LoginWithDeviceId(UNakamaComponent* nakama,
	FString deviceId,
	FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPAuthenticateRequest>();
	proxy->PrimaryId = deviceId;
	proxy->NakamaRef = nakama;
	proxy->OnSuccess = onSuccess;
	proxy->OnFail = onFail;
	proxy->Register = false;
	proxy->type = AuthType::Device;
	return proxy;
}

// ------------------------- Email -------------------------

UNBPAuthenticateRequest* UNBPAuthenticateRequest::RegisterWithEmail(UNakamaComponent* nakama,
	FString email, FString password,
	FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPAuthenticateRequest>();
	proxy->PrimaryId = email;
	proxy->Password = password;
	proxy->NakamaRef = nakama;
	proxy->OnSuccess = onSuccess;
	proxy->OnFail = onFail;
	proxy->Register = true;
	proxy->type = AuthType::Email;
	return proxy;
}

UNBPAuthenticateRequest* UNBPAuthenticateRequest::LoginWithEmail(UNakamaComponent* nakama,
	FString email, FString password,
	FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPAuthenticateRequest>();
	proxy->PrimaryId = email;
	proxy->Password = password;
	proxy->NakamaRef = nakama;
	proxy->OnSuccess = onSuccess;
	proxy->OnFail = onFail;
	proxy->Register = false;
	proxy->type = AuthType::Email;
	return proxy;
}

// ------------------------- Facebook -------------------------

UNBPAuthenticateRequest* UNBPAuthenticateRequest::RegisterWithFacebook(UNakamaComponent* nakama,
	FString oauthToken,
	FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPAuthenticateRequest>();
	proxy->PrimaryId = oauthToken;
	proxy->NakamaRef = nakama;
	proxy->OnSuccess = onSuccess;
	proxy->OnFail = onFail;
	proxy->Register = true;
	proxy->type = AuthType::Facebook;
	return proxy;
}

UNBPAuthenticateRequest* UNBPAuthenticateRequest::LoginWithFacebook(UNakamaComponent* nakama,
	FString oauthToken,
	FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPAuthenticateRequest>();
	proxy->PrimaryId = oauthToken;
	proxy->NakamaRef = nakama;
	proxy->OnSuccess = onSuccess;
	proxy->OnFail = onFail;
	proxy->Register = false;
	proxy->type = AuthType::Facebook;
	return proxy;
}

// ------------------------- GameCenter -------------------------

UNBPAuthenticateRequest* UNBPAuthenticateRequest::RegisterWithGameCenter(UNakamaComponent* nakama,
	FString playerId, FString bundleId, FDateTime timestamp, FString salt, FString signature, FString publicKeyUrl,
	FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPAuthenticateRequest>();
	proxy->PrimaryId = playerId;
	proxy->BundleId = bundleId;
	proxy->Timestamp = timestamp;
	proxy->Salt = salt;
	proxy->Signature = signature;
	proxy->PublicKeyUrl = publicKeyUrl;
	proxy->NakamaRef = nakama;
	proxy->OnSuccess = onSuccess;
	proxy->OnFail = onFail;
	proxy->Register = true;
	proxy->type = AuthType::GameCenter;
	return proxy;
}

UNBPAuthenticateRequest* UNBPAuthenticateRequest::LoginWithGameCenter(UNakamaComponent* nakama,
	FString playerId, FString bundleId, FDateTime timestamp, FString salt, FString signature, FString publicKeyUrl,
	FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPAuthenticateRequest>();
	proxy->PrimaryId = playerId;
	proxy->BundleId = bundleId;
	proxy->Timestamp = timestamp;
	proxy->Salt = salt;
	proxy->Signature = signature;
	proxy->PublicKeyUrl = publicKeyUrl;
	proxy->NakamaRef = nakama;
	proxy->OnSuccess = onSuccess;
	proxy->OnFail = onFail;
	proxy->Register = false;
	proxy->type = AuthType::GameCenter;
	return proxy;
}

// ------------------------- Google -------------------------

UNBPAuthenticateRequest* UNBPAuthenticateRequest::RegisterWithGoogle(UNakamaComponent* nakama,
	FString oauthToken,
	FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPAuthenticateRequest>();
	proxy->PrimaryId = oauthToken;
	proxy->NakamaRef = nakama;
	proxy->OnSuccess = onSuccess;
	proxy->OnFail = onFail;
	proxy->Register = true;
	proxy->type = AuthType::Google;
	return proxy;
}

UNBPAuthenticateRequest* UNBPAuthenticateRequest::LoginWithGoogle(UNakamaComponent* nakama,
	FString oauthToken,
	FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPAuthenticateRequest>();
	proxy->PrimaryId = oauthToken;
	proxy->NakamaRef = nakama;
	proxy->OnSuccess = onSuccess;
	proxy->OnFail = onFail;
	proxy->Register = false;
	proxy->type = AuthType::Google;
	return proxy;
}

// ------------------------- Steam -------------------------

UNBPAuthenticateRequest* UNBPAuthenticateRequest::RegisterWithSteam(UNakamaComponent* nakama,
	FString sessionToken,
	FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPAuthenticateRequest>();
	proxy->PrimaryId = sessionToken;
	proxy->NakamaRef = nakama;
	proxy->OnSuccess = onSuccess;
	proxy->OnFail = onFail;
	proxy->Register = true;
	proxy->type = AuthType::Steam;
	return proxy;
}

UNBPAuthenticateRequest* UNBPAuthenticateRequest::LoginWithSteam(UNakamaComponent* nakama,
	FString sessionToken,
	FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPAuthenticateRequest>();
	proxy->PrimaryId = sessionToken;
	proxy->NakamaRef = nakama;
	proxy->OnSuccess = onSuccess;
	proxy->OnFail = onFail;
	proxy->Register = false;
	proxy->type = AuthType::Steam;
	return proxy;
}

void UNBPAuthenticateRequest::Activate()
{
	auto req = this;
	auto client = NakamaRef != nullptr ? NakamaRef->GetClient() : nullptr;
	if (client == nullptr) return;

	auto success = [req, client](NSession* session) mutable {
		client->Connect(session,
			[req](bool s) { if (s && req->OnSuccess.IsBound()) req->OnSuccess.Execute(); }
		);
	};

	auto fail = [req](NError error) {
		if (req->OnFail.IsBound()) 
			req->OnFail.Execute(UNBPError::From(error));
	};

	switch (type) {
	case AuthType::Custom:
		if (req->Register)	client->Register(NAuthenticateMessage::Custom(TCHAR_TO_UTF8(*PrimaryId)), success, fail);
		else				client->Login(NAuthenticateMessage::Custom(TCHAR_TO_UTF8(*PrimaryId)), success, fail);
		break;

	case AuthType::Device:
		if (req->Register)	client->Register(NAuthenticateMessage::Device(TCHAR_TO_UTF8(*PrimaryId)), success, fail);
		else				client->Login(NAuthenticateMessage::Device(TCHAR_TO_UTF8(*PrimaryId)), success, fail);
		break;

	case AuthType::Email:
		if (req->Register)	client->Register(NAuthenticateMessage::Email(TCHAR_TO_UTF8(*PrimaryId), TCHAR_TO_UTF8(*Password)), success, fail);
		else				client->Login(NAuthenticateMessage::Email(TCHAR_TO_UTF8(*PrimaryId), TCHAR_TO_UTF8(*Password)), success, fail);
		break;

	case AuthType::Facebook:
		if (req->Register)	client->Register(NAuthenticateMessage::Facebook(TCHAR_TO_UTF8(*PrimaryId)), success, fail);
		else				client->Login(NAuthenticateMessage::Facebook(TCHAR_TO_UTF8(*PrimaryId)), success, fail);
		break;

	case AuthType::GameCenter:
		if (req->Register)	client->Register(NAuthenticateMessage::GameCenter(TCHAR_TO_UTF8(*PrimaryId), TCHAR_TO_UTF8(*BundleId), Timestamp.ToUnixTimestamp(), TCHAR_TO_UTF8(*Salt), TCHAR_TO_UTF8(*Signature), TCHAR_TO_UTF8(*PublicKeyUrl)), success, fail);
		else				client->Login(NAuthenticateMessage::GameCenter(TCHAR_TO_UTF8(*PrimaryId), TCHAR_TO_UTF8(*BundleId), Timestamp.ToUnixTimestamp(), TCHAR_TO_UTF8(*Salt), TCHAR_TO_UTF8(*Signature), TCHAR_TO_UTF8(*PublicKeyUrl)), success, fail);
		break;

	case AuthType::Google:
		if (req->Register)	client->Register(NAuthenticateMessage::Google(TCHAR_TO_UTF8(*PrimaryId)), success, fail);
		else				client->Login(NAuthenticateMessage::Google(TCHAR_TO_UTF8(*PrimaryId)), success, fail);
		break;

	case AuthType::Steam:
		if (req->Register)	client->Register(NAuthenticateMessage::Steam(TCHAR_TO_UTF8(*PrimaryId)), success, fail);
		else				client->Login(NAuthenticateMessage::Steam(TCHAR_TO_UTF8(*PrimaryId)), success, fail);
		break;

	}
}


/**
 * Handling for Friends
 */

// ------------------------- UNBPManageFriendRequest -------------------------

UNBPManageFriendRequest* UNBPManageFriendRequest::AddFriendByUserId(UNakamaComponent* nakama, FString userId, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPManageFriendRequest>();
	proxy->mode = Mode::Add;
	proxy->Id = userId;
	proxy->NakamaRef = nakama;
	proxy->OnManageSuccess = onSuccess;
	proxy->OnFail = onFail;
	return proxy;
}

UNBPManageFriendRequest* UNBPManageFriendRequest::BlockFriendByUserId(UNakamaComponent* nakama, FString userId, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPManageFriendRequest>();
	proxy->mode = Mode::Block;
	proxy->Id = userId;
	proxy->NakamaRef = nakama;
	proxy->OnManageSuccess = onSuccess;
	proxy->OnFail = onFail;
	return proxy;
}

UNBPManageFriendRequest* UNBPManageFriendRequest::RemoveFriendByUserId(UNakamaComponent* nakama, FString userId, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPManageFriendRequest>();
	proxy->mode = Mode::Remove;
	proxy->Id = userId;
	proxy->NakamaRef = nakama;
	proxy->OnManageSuccess = onSuccess;
	proxy->OnFail = onFail;
	return proxy;
}

UNBPManageFriendRequest* UNBPManageFriendRequest::ListFriends(UNakamaComponent* nakama, FDelegateOnSuccess_FriendList onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPManageFriendRequest>();
	proxy->mode = Mode::List;
	proxy->NakamaRef = nakama;
	proxy->OnListSuccess = onSuccess;
	proxy->OnFail = onFail;
	return proxy;
}

void UNBPManageFriendRequest::Activate()
{
	auto req = this;
	auto client = NakamaRef != nullptr ? NakamaRef->GetClient() : nullptr;
	if (client == nullptr) return;

	auto fail = [req](NError error) {
		if (req->OnFail.IsBound())
			req->OnFail.Execute(UNBPError::From(error));
	};

	if (mode != Mode::List) {
		auto success = [req](void* obj) {
			if (req->OnManageSuccess.IsBound()) req->OnManageSuccess.Execute();
		};

		switch (mode) {
			case Mode::Add: {
				auto message = NFriendAddMessage::Default(TCHAR_TO_UTF8(*Id));
				client->Send(message, success, fail);
				break;
			}
			case Mode::Block: {
				auto message = NFriendBlockMessage::Default(TCHAR_TO_UTF8(*Id));
				client->Send(message, success, fail);
				break;
			}
			case Mode::Remove: {
				auto message = NFriendRemoveMessage::Default(TCHAR_TO_UTF8(*Id));
				client->Send(message, success, fail);
				break;
			}
		}
	}
	else {
		auto success = [req](void* obj) {
			if (req->OnListSuccess.IsBound()) {
				auto rs = (NResultSet<NFriend>*)obj;
				req->OnListSuccess.Execute(UNBPFriend::FromResultSet(rs), UNBPCursor::From(rs->GetCursor()));
			}
		};

		auto message = NFriendsListMessage::Default();
		client->Send(message, success, fail);
	}
}

/**
* Handling for Self
*/

// ------------------------- UNBPSelfFetchRequest -------------------------

UNBPSelfFetchRequest* UNBPSelfFetchRequest::FetchSelf(UNakamaComponent* nakama, FDelegateOnSuccess_Self onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPSelfFetchRequest>();
	proxy->NakamaRef = nakama;
	proxy->OnSuccess = onSuccess;
	proxy->OnFail = onFail;
	return proxy;
}

void UNBPSelfFetchRequest::Activate()
{
	auto req = this;
	auto client = NakamaRef != nullptr ? NakamaRef->GetClient() : nullptr;
	if (client == nullptr) return;

	auto success = [req](void* obj) {
		if (req->OnSuccess.IsBound()) {
			auto data = (NSelf*)obj;
			req->OnSuccess.Execute(UNBPSelf::From(*data));
		}
	};

	auto fail = [req](NError error) {
		if (req->OnFail.IsBound())
			req->OnFail.Execute(UNBPError::From(error));
	};

	auto message = NSelfFetchMessage::Default();
	client->Send(message, success, fail);
}

// ------------------------- UNBPSelfUpdateRequest -------------------------

UNBPSelfUpdateRequest* UNBPSelfUpdateRequest::UpdateSelf(UNakamaComponent* nakama, FString handle, FString fullname, FString avatarUrl, FString lang, FString location, FString metadata, FString timezone, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPSelfUpdateRequest>();
	proxy->Handle = handle;
	proxy->Fullname = fullname;
	proxy->AvatarUrl = avatarUrl;
	proxy->Lang = lang;
	proxy->Location = location;
	proxy->Metadata = metadata;
	proxy->Timezone = timezone;
	proxy->NakamaRef = nakama;
	proxy->OnSuccess = onSuccess;
	proxy->OnFail = onFail;
	return proxy;
}

void UNBPSelfUpdateRequest::Activate()
{
	auto req = this;
	auto client = NakamaRef != nullptr ? NakamaRef->GetClient() : nullptr;
	if (client == nullptr) return;

	auto success = [req](void* obj) {
		if (req->OnSuccess.IsBound()) req->OnSuccess.Execute();
	};

	auto fail = [req](NError error) {
		if (req->OnFail.IsBound())
			req->OnFail.Execute(UNBPError::From(error));
	};

	auto builder = NSelfUpdateMessage::Builder();
	if (!Handle.IsEmpty()) builder.Handle(TCHAR_TO_UTF8(*Handle));
	if (!Fullname.IsEmpty()) builder.Fullname(TCHAR_TO_UTF8(*Fullname));
	if (!AvatarUrl.IsEmpty()) builder.AvatarUrl(TCHAR_TO_UTF8(*AvatarUrl));
	if (!Lang.IsEmpty()) builder.Lang(TCHAR_TO_UTF8(*Lang));
	if (!Location.IsEmpty()) builder.Location(TCHAR_TO_UTF8(*Location));
	if (!Metadata.IsEmpty()) builder.Metadata(TCHAR_TO_UTF8(*Metadata));
	if (!Timezone.IsEmpty()) builder.Timezone(TCHAR_TO_UTF8(*Timezone));

	auto message = builder.Build();
	client->Send(message, success, fail);
}


// ------------------------- UNBPSelfFetchRequest -------------------------

// ------------------------- Custom -------------------------

UNBPSelfLinkRequest* UNBPSelfLinkRequest::LinkCustomId(UNakamaComponent* nakama,
	FString id,
	FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPSelfLinkRequest>();
	proxy->PrimaryId = id;
	proxy->NakamaRef = nakama;
	proxy->OnSuccess = onSuccess;
	proxy->OnFail = onFail;
	proxy->Link = true;
	proxy->type = AuthType::Custom;
	return proxy;
}

UNBPSelfLinkRequest* UNBPSelfLinkRequest::UnlinkCustomId(UNakamaComponent* nakama,
	FString id,
	FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPSelfLinkRequest>();
	proxy->PrimaryId = id;
	proxy->NakamaRef = nakama;
	proxy->OnSuccess = onSuccess;
	proxy->OnFail = onFail;
	proxy->Link = false;
	proxy->type = AuthType::Custom;
	return proxy;
}

// ------------------------- Device -------------------------

UNBPSelfLinkRequest* UNBPSelfLinkRequest::LinkDeviceId(UNakamaComponent* nakama,
	FString deviceId,
	FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPSelfLinkRequest>();
	proxy->PrimaryId = deviceId;
	proxy->NakamaRef = nakama;
	proxy->OnSuccess = onSuccess;
	proxy->OnFail = onFail;
	proxy->Link = true;
	proxy->type = AuthType::Device;
	return proxy;
}

UNBPSelfLinkRequest* UNBPSelfLinkRequest::UnlinkDeviceId(UNakamaComponent* nakama,
	FString deviceId,
	FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPSelfLinkRequest>();
	proxy->PrimaryId = deviceId;
	proxy->NakamaRef = nakama;
	proxy->OnSuccess = onSuccess;
	proxy->OnFail = onFail;
	proxy->Link = false;
	proxy->type = AuthType::Device;
	return proxy;
}

// ------------------------- Email -------------------------

UNBPSelfLinkRequest* UNBPSelfLinkRequest::LinkEmail(UNakamaComponent* nakama,
	FString email, FString password,
	FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPSelfLinkRequest>();
	proxy->PrimaryId = email;
	proxy->Password = password;
	proxy->NakamaRef = nakama;
	proxy->OnSuccess = onSuccess;
	proxy->OnFail = onFail;
	proxy->Link = true;
	proxy->type = AuthType::Email;
	return proxy;
}

UNBPSelfLinkRequest* UNBPSelfLinkRequest::UnlinkEmail(UNakamaComponent* nakama,
	FString email,
	FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPSelfLinkRequest>();
	proxy->PrimaryId = email;
	proxy->NakamaRef = nakama;
	proxy->OnSuccess = onSuccess;
	proxy->OnFail = onFail;
	proxy->Link = false;
	proxy->type = AuthType::Email;
	return proxy;
}

// ------------------------- Facebook -------------------------

UNBPSelfLinkRequest* UNBPSelfLinkRequest::LinkFacebook(UNakamaComponent* nakama,
	FString oauthToken,
	FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPSelfLinkRequest>();
	proxy->PrimaryId = oauthToken;
	proxy->NakamaRef = nakama;
	proxy->OnSuccess = onSuccess;
	proxy->OnFail = onFail;
	proxy->Link = true;
	proxy->type = AuthType::Facebook;
	return proxy;
}

UNBPSelfLinkRequest* UNBPSelfLinkRequest::UnlinkFacebook(UNakamaComponent* nakama,
	FString oauthToken,
	FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPSelfLinkRequest>();
	proxy->PrimaryId = oauthToken;
	proxy->NakamaRef = nakama;
	proxy->OnSuccess = onSuccess;
	proxy->OnFail = onFail;
	proxy->Link = false;
	proxy->type = AuthType::Facebook;
	return proxy;
}

// ------------------------- GameCenter -------------------------

UNBPSelfLinkRequest* UNBPSelfLinkRequest::LinkGameCenter(UNakamaComponent* nakama,
	FString playerId, FString bundleId, FDateTime timestamp, FString salt, FString signature, FString publicKeyUrl,
	FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPSelfLinkRequest>();
	proxy->PrimaryId = playerId;
	proxy->BundleId = bundleId;
	proxy->Timestamp = timestamp;
	proxy->Salt = salt;
	proxy->Signature = signature;
	proxy->PublicKeyUrl = publicKeyUrl;
	proxy->NakamaRef = nakama;
	proxy->OnSuccess = onSuccess;
	proxy->OnFail = onFail;
	proxy->Link = true;
	proxy->type = AuthType::GameCenter;
	return proxy;
}

UNBPSelfLinkRequest* UNBPSelfLinkRequest::UnlinkGameCenter(UNakamaComponent* nakama,
	FString playerId,
	FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPSelfLinkRequest>();
	proxy->PrimaryId = playerId;
	proxy->NakamaRef = nakama;
	proxy->OnSuccess = onSuccess;
	proxy->OnFail = onFail;
	proxy->Link = false;
	proxy->type = AuthType::GameCenter;
	return proxy;
}

// ------------------------- Google -------------------------

UNBPSelfLinkRequest* UNBPSelfLinkRequest::LinkGoogle(UNakamaComponent* nakama,
	FString oauthToken,
	FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPSelfLinkRequest>();
	proxy->PrimaryId = oauthToken;
	proxy->NakamaRef = nakama;
	proxy->OnSuccess = onSuccess;
	proxy->OnFail = onFail;
	proxy->Link = true;
	proxy->type = AuthType::Google;
	return proxy;
}

UNBPSelfLinkRequest* UNBPSelfLinkRequest::UnlinkGoogle(UNakamaComponent* nakama,
	FString oauthToken,
	FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPSelfLinkRequest>();
	proxy->PrimaryId = oauthToken;
	proxy->NakamaRef = nakama;
	proxy->OnSuccess = onSuccess;
	proxy->OnFail = onFail;
	proxy->Link = false;
	proxy->type = AuthType::Google;
	return proxy;
}

// ------------------------- Steam -------------------------

UNBPSelfLinkRequest* UNBPSelfLinkRequest::LinkSteam(UNakamaComponent* nakama,
	FString sessionToken,
	FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPSelfLinkRequest>();
	proxy->PrimaryId = sessionToken;
	proxy->NakamaRef = nakama;
	proxy->OnSuccess = onSuccess;
	proxy->OnFail = onFail;
	proxy->Link = true;
	proxy->type = AuthType::Steam;
	return proxy;
}

UNBPSelfLinkRequest* UNBPSelfLinkRequest::UnlinkSteam(UNakamaComponent* nakama,
	FString sessionToken,
	FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPSelfLinkRequest>();
	proxy->PrimaryId = sessionToken;
	proxy->NakamaRef = nakama;
	proxy->OnSuccess = onSuccess;
	proxy->OnFail = onFail;
	proxy->Link = false;
	proxy->type = AuthType::Steam;
	return proxy;
}

void UNBPSelfLinkRequest::Activate()
{
	auto req = this;
	auto client = NakamaRef != nullptr ? NakamaRef->GetClient() : nullptr;
	if (client == nullptr) return;

	auto success = [req](void* obj) {
		if (req->OnSuccess.IsBound()) req->OnSuccess.Execute();
	};

	auto fail = [req](NError error) {
		if (req->OnFail.IsBound())
			req->OnFail.Execute(UNBPError::From(error));
	};

	switch (type) {
	case AuthType::Custom: {
		if (req->Link) {
			auto message = NSelfLinkMessage::Custom(TCHAR_TO_UTF8(*PrimaryId));
			client->Send(message, success, fail);
		}
		else {
			auto message = NSelfUnlinkMessage::Custom(TCHAR_TO_UTF8(*PrimaryId));
			client->Send(message, success, fail);
		}
		break;
	}

	case AuthType::Device: {
		if (req->Link) {
			auto message = NSelfLinkMessage::Device(TCHAR_TO_UTF8(*PrimaryId));
			client->Send(message, success, fail);
		}
		else {
			auto message = NSelfUnlinkMessage::Device(TCHAR_TO_UTF8(*PrimaryId));
			client->Send(message, success, fail);
		}
		break;
	}

	case AuthType::Email: {
		if (req->Link) {
			auto message = NSelfLinkMessage::Email(TCHAR_TO_UTF8(*PrimaryId), TCHAR_TO_UTF8(*Password));
			client->Send(message, success, fail);
		}
		else {
			auto message = NSelfUnlinkMessage::Email(TCHAR_TO_UTF8(*PrimaryId));
			client->Send(message, success, fail);
		}
		break;
	}

	case AuthType::Facebook: {
		if (req->Link) {
			auto message = NSelfLinkMessage::Facebook(TCHAR_TO_UTF8(*PrimaryId));
			client->Send(message, success, fail);
		}
		else {
			auto message = NSelfUnlinkMessage::Facebook(TCHAR_TO_UTF8(*PrimaryId));
			client->Send(message, success, fail);
		}
		break;
	}

	case AuthType::GameCenter: {
		if (req->Link) {
			auto message = NSelfLinkMessage::GameCenter(TCHAR_TO_UTF8(*PrimaryId), TCHAR_TO_UTF8(*BundleId), Timestamp.ToUnixTimestamp(), TCHAR_TO_UTF8(*Salt), TCHAR_TO_UTF8(*Signature), TCHAR_TO_UTF8(*PublicKeyUrl));
			client->Send(message, success, fail);
		}
		else {
			auto message = NSelfUnlinkMessage::GameCenter(TCHAR_TO_UTF8(*PrimaryId));
			client->Send(message, success, fail);
		}
		break;
	}

	case AuthType::Google: {
		if (req->Link) {
			auto message = NSelfLinkMessage::Google(TCHAR_TO_UTF8(*PrimaryId));
			client->Send(message, success, fail);
		}
		else {
			auto message = NSelfUnlinkMessage::Google(TCHAR_TO_UTF8(*PrimaryId));
			client->Send(message, success, fail);
		}
		break;
	}

	case AuthType::Steam: {
		if (req->Link) {
			auto message = NSelfLinkMessage::Steam(TCHAR_TO_UTF8(*PrimaryId));
			client->Send(message, success, fail);
		}
		else {
			auto message = NSelfUnlinkMessage::Steam(TCHAR_TO_UTF8(*PrimaryId));
			client->Send(message, success, fail);
		}
		break;
	}
	}
}


/**
* Handling for Groups
*/

// ------------------------- UNBPManageGroupsRequest -------------------------

UNBPManageGroupsRequest* UNBPManageGroupsRequest::CreateGroup(UNakamaComponent* nakama, FString name, FString description, FString avatarUrl, FString lang, FString metadata, bool privateGroup, FDelegateOnSuccess_Group onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPManageGroupsRequest>();
	proxy->mode = Mode::Create;
	proxy->Name = name;
	proxy->Description = description;
	proxy->AvatarUrl = avatarUrl;
	proxy->Lang = lang;
	proxy->Metadata = metadata;
	proxy->PrivateGroup = privateGroup;
	proxy->NakamaRef = nakama;
	proxy->OnGroupSuccess = onSuccess;
	proxy->OnFail = onFail;
	return proxy;
}

UNBPManageGroupsRequest* UNBPManageGroupsRequest::RemoveGroup(UNakamaComponent* nakama, FString groupId, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPManageGroupsRequest>();
	proxy->mode = Mode::Remove;
	proxy->GroupId = groupId;
	proxy->NakamaRef = nakama;
	proxy->OnManageSuccess = onSuccess;
	proxy->OnFail = onFail;
	return proxy;
}

UNBPManageGroupsRequest* UNBPManageGroupsRequest::UpdateGroup(UNakamaComponent* nakama, FString groupId, FString name, FString description, FString avatarUrl, FString lang, FString metadata, bool privateGroup, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPManageGroupsRequest>();
	proxy->mode = Mode::Update;
	proxy->GroupId = groupId;
	proxy->Name = name;
	proxy->Description = description;
	proxy->AvatarUrl = avatarUrl;
	proxy->Lang = lang;
	proxy->Metadata = metadata;
	proxy->PrivateGroup = privateGroup;
	proxy->NakamaRef = nakama;
	proxy->OnManageSuccess = onSuccess;
	proxy->OnFail = onFail;
	return proxy;
}

void UNBPManageGroupsRequest::Activate()
{
	auto req = this;
	auto client = NakamaRef != nullptr ? NakamaRef->GetClient() : nullptr;
	if (client == nullptr) return;

	auto fail = [req](NError error) {
		if (req->OnFail.IsBound())
			req->OnFail.Execute(UNBPError::From(error));
	};

	if (mode != Mode::Create) {
		auto success = [req](void* obj) {
			if (req->OnManageSuccess.IsBound()) req->OnManageSuccess.Execute();
		};

		switch (mode) {
		case Mode::Remove: {
			auto message = NGroupRemoveMessage::Default(TCHAR_TO_UTF8(*GroupId));
			client->Send(message, success, fail);
			break;
		}
		case Mode::Update: {
			auto builder = NGroupUpdateMessage::Builder(TCHAR_TO_UTF8(*GroupId)).Private(PrivateGroup);
			if (!Name.IsEmpty()) builder.Name(TCHAR_TO_UTF8(*Name));
			if (!Description.IsEmpty()) builder.Description(TCHAR_TO_UTF8(*Description));
			if (!AvatarUrl.IsEmpty()) builder.AvatarUrl(TCHAR_TO_UTF8(*AvatarUrl));
			if (!Lang.IsEmpty()) builder.Lang(TCHAR_TO_UTF8(*Lang));
			if (!Metadata.IsEmpty()) builder.Metadata(TCHAR_TO_UTF8(*Metadata));

			auto message = builder.Build();
			client->Send(message, success, fail);
			break;
		}
		}
	}
	else {
		auto success = [req](void* obj) {
			if (req->OnGroupSuccess.IsBound()) {
				auto data = (NGroup*)obj;
				req->OnGroupSuccess.Execute(UNBPGroup::From(*data));
			}
		};

		auto builder = NGroupCreateMessage::Builder(TCHAR_TO_UTF8(*Name)).Private(PrivateGroup);
		if (!Description.IsEmpty()) builder.Description(TCHAR_TO_UTF8(*Description));
		if (!AvatarUrl.IsEmpty()) builder.AvatarUrl(TCHAR_TO_UTF8(*AvatarUrl));
		if (!Lang.IsEmpty()) builder.Lang(TCHAR_TO_UTF8(*Lang));
		if (!Metadata.IsEmpty()) builder.Metadata(TCHAR_TO_UTF8(*Metadata));

		auto message = builder.Build();
		client->Send(message, success, fail);
	}
}


// ------------------------- UNBPListGroupsRequest -------------------------

UNBPListGroupsRequest* UNBPListGroupsRequest::FetchGroups(UNakamaComponent* nakama, TArray<FString> groupIds, FDelegateOnSuccess_GroupList onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPListGroupsRequest>();
	proxy->mode = Mode::Fetch;
	proxy->GroupIds = groupIds;
	proxy->NakamaRef = nakama;
	proxy->OnSuccess = onSuccess;
	proxy->OnFail = onFail;
	return proxy;
}

UNBPListGroupsRequest* UNBPListGroupsRequest::ListGroups(UNakamaComponent* nakama, int32 pageLimit, bool ascending, UNBPCursor* cursor, FString filterByLang, FDateTime filterByCreatedAt, int32 filterByCount, FDelegateOnSuccess_GroupList onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPListGroupsRequest>();
	proxy->mode = Mode::List;
	proxy->PageLimit = pageLimit;
	proxy->Ascending = ascending;
	proxy->Cursor = cursor;
	proxy->FilterByLang = filterByLang;
	proxy->FilterByCreatedAt = filterByCreatedAt;
	proxy->FilterByCount = filterByCount;
	proxy->NakamaRef = nakama;
	proxy->OnSuccess = onSuccess;
	proxy->OnFail = onFail;
	return proxy;
}

UNBPListGroupsRequest* UNBPListGroupsRequest::ListSelfGroups(UNakamaComponent* nakama, FDelegateOnSuccess_GroupList onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPListGroupsRequest>();
	proxy->mode = Mode::SelfList;
	proxy->NakamaRef = nakama;
	proxy->OnSuccess = onSuccess;
	proxy->OnFail = onFail;
	return proxy;
}

void UNBPListGroupsRequest::Activate()
{
	auto req = this;
	auto client = NakamaRef != nullptr ? NakamaRef->GetClient() : nullptr;
	if (client == nullptr) return;

	auto fail = [req](NError error) {
		if (req->OnFail.IsBound())
			req->OnFail.Execute(UNBPError::From(error));
	};

	auto success = [req](void* obj) {
		if (req->OnSuccess.IsBound()) {
			auto rs = (NResultSet<NGroup>*)obj;
			req->OnSuccess.Execute(UNBPGroup::FromResultSet(rs), UNBPCursor::From(rs->GetCursor()));
		}
	};

	switch (mode) {
	case Mode::Fetch: {
		if (GroupIds.Num() == 0) {
			if (OnFail.IsBound()) OnFail.Execute(UNBPError::From(NError("GroupIds was empty.")));
			return;
		}

		auto builder = NGroupsFetchMessage::Builder(TCHAR_TO_UTF8(*GroupIds[0]));
		for (int i = 1; i < GroupIds.Num(); i++) {
			builder.Add(TCHAR_TO_UTF8(*GroupIds[i]));
		}

		auto message = builder.Build();
		client->Send(message, success, fail);
		break;
	}
	case Mode::List: {
		auto builder = NGroupsListMessage::Builder().OrderByAsc(Ascending);

		if (PageLimit != 0) builder.PageLimit(PageLimit);
		if (Cursor != nullptr) builder.Cursor(Cursor->GetNCursor());
		if (!FilterByLang.IsEmpty()) builder.FilterByLang(TCHAR_TO_UTF8(*FilterByLang));
		if (FilterByCreatedAt.GetTicks() != 0) builder.FilterByCreatedAt(FilterByCreatedAt.ToUnixTimestamp());
		if (FilterByCount != 0) builder.FilterByCount(FilterByCount);

		auto message = builder.Build();
		client->Send(message, success, fail);
		break;
	}
	case Mode::SelfList: {
		auto message = NGroupsSelfListMessage::Default();
		client->Send(message, success, fail);
		break;
	}
	}
}

// ------------------------- UNBPJoinLeaveGroupRequest -------------------------

UNBPJoinLeaveGroupRequest* UNBPJoinLeaveGroupRequest::JoinGroup(UNakamaComponent* nakama, FString groupId, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPJoinLeaveGroupRequest>();
	proxy->mode = Mode::Join;
	proxy->GroupId = groupId;
	proxy->NakamaRef = nakama;
	proxy->OnSuccess = onSuccess;
	proxy->OnFail = onFail;
	return proxy;
}

UNBPJoinLeaveGroupRequest* UNBPJoinLeaveGroupRequest::LeaveGroup(UNakamaComponent* nakama, FString groupId, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPJoinLeaveGroupRequest>();
	proxy->mode = Mode::Leave;
	proxy->GroupId = groupId;
	proxy->NakamaRef = nakama;
	proxy->OnSuccess = onSuccess;
	proxy->OnFail = onFail;
	return proxy;
}

void UNBPJoinLeaveGroupRequest::Activate()
{
	auto req = this;
	auto client = NakamaRef != nullptr ? NakamaRef->GetClient() : nullptr;
	if (client == nullptr) return;

	auto fail = [req](NError error) {
		if (req->OnFail.IsBound())
			req->OnFail.Execute(UNBPError::From(error));
	};

	auto success = [req](void* obj) {
		if (req->OnSuccess.IsBound()) req->OnSuccess.Execute();
	};

	switch (mode) {
	case Mode::Join: {
		auto message = NGroupJoinMessage::Default(TCHAR_TO_UTF8(*GroupId));
		client->Send(message, success, fail);
		break;
	}
	case Mode::Leave: {
		auto message = NGroupLeaveMessage::Default(TCHAR_TO_UTF8(*GroupId));
		client->Send(message, success, fail);
		break;
	}
	}
}


/**
* Handling for GroupUsers
*/

// ------------------------- UNBPManageGroupUsersRequest -------------------------

UNBPManageGroupUsersRequest* UNBPManageGroupUsersRequest::AddUserToGroup(UNakamaComponent* nakama, FString groupId, FString userId, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPManageGroupUsersRequest>();
	proxy->mode = Mode::Add;
	proxy->GroupId = groupId;
	proxy->UserId = userId;
	proxy->NakamaRef = nakama;
	proxy->OnManageSuccess = onSuccess;
	proxy->OnFail = onFail;
	return proxy;
}

UNBPManageGroupUsersRequest* UNBPManageGroupUsersRequest::KickUserFromGroup(UNakamaComponent* nakama, FString groupId, FString userId, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPManageGroupUsersRequest>();
	proxy->mode = Mode::Kick;
	proxy->GroupId = groupId;
	proxy->UserId = userId;
	proxy->NakamaRef = nakama;
	proxy->OnManageSuccess = onSuccess;
	proxy->OnFail = onFail;
	return proxy;
}

UNBPManageGroupUsersRequest* UNBPManageGroupUsersRequest::PromoteGroupUser(UNakamaComponent* nakama, FString groupId, FString userId, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPManageGroupUsersRequest>();
	proxy->mode = Mode::Promote;
	proxy->GroupId = groupId;
	proxy->UserId = userId;
	proxy->NakamaRef = nakama;
	proxy->OnManageSuccess = onSuccess;
	proxy->OnFail = onFail;
	return proxy;
}

UNBPManageGroupUsersRequest* UNBPManageGroupUsersRequest::ListGroupUsers(UNakamaComponent* nakama, FString groupId, FDelegateOnSuccess_GroupUserList onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPManageGroupUsersRequest>();
	proxy->mode = Mode::List;
	proxy->GroupId = groupId;
	proxy->NakamaRef = nakama;
	proxy->OnListSuccess = onSuccess;
	proxy->OnFail = onFail;
	return proxy;
}

void UNBPManageGroupUsersRequest::Activate()
{
	auto req = this;
	auto client = NakamaRef != nullptr ? NakamaRef->GetClient() : nullptr;
	if (client == nullptr) return;

	auto fail = [req](NError error) {
		if (req->OnFail.IsBound())
			req->OnFail.Execute(UNBPError::From(error));
	};

	if (mode != Mode::List) {
		auto success = [req](void* obj) {
			if (req->OnManageSuccess.IsBound()) req->OnManageSuccess.Execute();
		};

		switch (mode) {
		case Mode::Add: {
			auto message = NGroupAddUserMessage::Default(TCHAR_TO_UTF8(*GroupId), TCHAR_TO_UTF8(*UserId));
			client->Send(message, success, fail);
			break;
		}
		case Mode::Kick: {
			auto message = NGroupKickUserMessage::Default(TCHAR_TO_UTF8(*GroupId), TCHAR_TO_UTF8(*UserId));
			client->Send(message, success, fail);
			break;
		}
		case Mode::Promote: {
			auto message = NGroupPromoteUserMessage::Default(TCHAR_TO_UTF8(*GroupId), TCHAR_TO_UTF8(*UserId));
			client->Send(message, success, fail);
			break;
		}
		}
	}
	else {
		auto success = [req](void* obj) {
			if (req->OnListSuccess.IsBound()) {
				auto rs = (NResultSet<NGroupUser>*)obj;
				req->OnListSuccess.Execute(UNBPGroupUser::FromResultSet(rs), UNBPCursor::From(rs->GetCursor()));
			}
		};

		auto message = NGroupUsersListMessage::Default(TCHAR_TO_UTF8(*GroupId));
		client->Send(message, success, fail);
	}
}


/**
* Handling for Users
*/

// ------------------------- UNBPListUsersRequest -------------------------

UNBPListUsersRequest* UNBPListUsersRequest::FetchUsers(UNakamaComponent* nakama, TArray<FString> userIds, FDelegateOnSuccess_UsersList onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPListUsersRequest>();
	proxy->UserIds = userIds;
	proxy->NakamaRef = nakama;
	proxy->OnSuccess = onSuccess;
	proxy->OnFail = onFail;
	return proxy;
}

void UNBPListUsersRequest::Activate()
{
	auto req = this;
	auto client = NakamaRef != nullptr ? NakamaRef->GetClient() : nullptr;
	if (client == nullptr) return;

	auto fail = [req](NError error) {
		if (req->OnFail.IsBound())
			req->OnFail.Execute(UNBPError::From(error));
	};

	auto success = [req](void* obj) {
		if (req->OnSuccess.IsBound()) {
			auto rs = (NResultSet<NUser>*)obj;
			req->OnSuccess.Execute(UNBPUser::FromResultSet(rs), UNBPCursor::From(rs->GetCursor()));
		}
	};

	if (UserIds.Num() == 0) {
		if (OnFail.IsBound()) OnFail.Execute(UNBPError::From(NError("UserIds was empty.")));
		return;
	}

	auto builder = NUsersFetchMessage::Builder(TCHAR_TO_UTF8(*UserIds[0]));
	for (int i = 1; i < UserIds.Num(); i++) {
		builder.Add(TCHAR_TO_UTF8(*UserIds[i]));
	}

	auto message = builder.Build();
	client->Send(message, success, fail);
}


/**
* Handling for Storage
*/

// ------------------------- UNBPListUsersRequest -------------------------

UNBPStorageRequest* UNBPStorageRequest::Write(UNakamaComponent* nakama, FString bucket, FString collection, FString record, FString value, FString version, FDelegateOnSuccess_StorageKeyList onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPStorageRequest>();
	proxy->mode = Mode::WriteData;
	proxy->Buckets.Add(bucket);
	proxy->Collections.Add(collection);
	proxy->Records.Add(record);
	proxy->Values.Add(value);
	if (!version.IsEmpty()) proxy->Versions.Add(version);
	proxy->NakamaRef = nakama;
	proxy->OnWriteSuccess = onSuccess;
	proxy->OnFail = onFail;
	return proxy;
}

UNBPStorageRequest* UNBPStorageRequest::WriteMany(UNakamaComponent* nakama, TArray<FString> buckets, TArray<FString> collections, TArray<FString> records, TArray<FString> values, TArray<FString> versions, FDelegateOnSuccess_StorageKeyList onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPStorageRequest>();
	proxy->mode = Mode::WriteData;
	proxy->Buckets = buckets;
	proxy->Collections = collections;
	proxy->Records = records;
	proxy->Values = values;
	proxy->Versions = versions;
	proxy->NakamaRef = nakama;
	proxy->OnWriteSuccess = onSuccess;
	proxy->OnFail = onFail;
	return proxy;
}

UNBPStorageRequest* UNBPStorageRequest::Fetch(UNakamaComponent* nakama, FString bucket, FString collection, FString record, FString userId, FDelegateOnSuccess_StorageDataList onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPStorageRequest>();
	proxy->mode = Mode::FetchData;
	proxy->Buckets.Add(bucket);
	proxy->Collections.Add(collection);
	proxy->Records.Add(record);
	proxy->UserIds.Add(userId);
	proxy->NakamaRef = nakama;
	proxy->OnFetchSuccess = onSuccess;
	proxy->OnFail = onFail;
	return proxy;
}

UNBPStorageRequest* UNBPStorageRequest::FetchMany(UNakamaComponent* nakama, TArray<FString> buckets, TArray<FString> collections, TArray<FString> records, TArray<FString> userIds, FDelegateOnSuccess_StorageDataList onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPStorageRequest>();
	proxy->mode = Mode::FetchData;
	proxy->Buckets = buckets;
	proxy->Collections = collections;
	proxy->Records = records;
	proxy->UserIds = userIds;
	proxy->NakamaRef = nakama;
	proxy->OnFetchSuccess = onSuccess;
	proxy->OnFail = onFail;
	return proxy;
}

UNBPStorageRequest* UNBPStorageRequest::Remove(UNakamaComponent* nakama, FString bucket, FString collection, FString record, FString version, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPStorageRequest>();
	proxy->mode = Mode::RemoveData;
	proxy->Buckets.Add(bucket);
	proxy->Collections.Add(collection);
	proxy->Records.Add(record);
	if (!version.IsEmpty()) proxy->Versions.Add(version);
	proxy->NakamaRef = nakama;
	proxy->OnRemoveSuccess = onSuccess;
	proxy->OnFail = onFail;
	return proxy;
}

UNBPStorageRequest* UNBPStorageRequest::RemoveMany(UNakamaComponent* nakama, TArray<FString> buckets, TArray<FString> collections, TArray<FString> records, TArray<FString> versions, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPStorageRequest>();
	proxy->mode = Mode::RemoveData;
	proxy->Buckets = buckets;
	proxy->Collections = collections;
	proxy->Records = records;
	proxy->Versions = versions;
	proxy->NakamaRef = nakama;
	proxy->OnRemoveSuccess = onSuccess;
	proxy->OnFail = onFail;
	return proxy;
}

void UNBPStorageRequest::Activate()
{
	auto req = this;
	auto client = NakamaRef != nullptr ? NakamaRef->GetClient() : nullptr;
	if (client == nullptr) return;

	auto fail = [req](NError error) {
		if (req->OnFail.IsBound())
			req->OnFail.Execute(UNBPError::From(error));
	};

	switch (mode) {
	case Mode::WriteData: {
		auto success = [req](void* obj) {
			if (req->OnWriteSuccess.IsBound()) {
				auto rs = (NResultSet<NStorageKey>*)obj;
				req->OnWriteSuccess.Execute(UNBPStorageKey::FromResultSet(rs), UNBPCursor::From(rs->GetCursor()));
			}
		};

		auto builder = NStorageWriteMessage::Builder();
		for (int i = 0; i < Buckets.Num(); i++) {
			if (Versions.Num() == 0) builder.Write(TCHAR_TO_UTF8(*Buckets[i]), TCHAR_TO_UTF8(*Collections[i]), TCHAR_TO_UTF8(*Records[i]), TCHAR_TO_UTF8(*Values[i]));
			else builder.Write(TCHAR_TO_UTF8(*Buckets[i]), TCHAR_TO_UTF8(*Collections[i]), TCHAR_TO_UTF8(*Records[i]), TCHAR_TO_UTF8(*Values[i]), TCHAR_TO_UTF8(*Versions[i]));
		}

		auto message = builder.Build();
		client->Send(message, success, fail);
		break;
	}
	case Mode::FetchData: {
		auto success = [req](void* obj) {
			if (req->OnFetchSuccess.IsBound()) {
				auto rs = (NResultSet<NStorageData>*)obj;
				req->OnFetchSuccess.Execute(UNBPStorageData::FromResultSet(rs), UNBPCursor::From(rs->GetCursor()));
			}
		};

		auto builder = NStorageFetchMessage::Builder();
		for (int i = 0; i < Buckets.Num(); i++) {
			builder.Fetch(TCHAR_TO_UTF8(*Buckets[i]), TCHAR_TO_UTF8(*Collections[i]), TCHAR_TO_UTF8(*Records[i]), TCHAR_TO_UTF8(*UserIds[i]));
		}

		auto message = builder.Build();
		client->Send(message, success, fail);
		break;
	}
	case Mode::RemoveData: {
		auto success = [req](void* obj) {
			if (req->OnRemoveSuccess.IsBound()) req->OnRemoveSuccess.Execute();
		};

		auto builder = NStorageRemoveMessage::Builder();
		for (int i = 0; i < Buckets.Num(); i++) {
			if (Versions.Num() == 0) builder.Remove(TCHAR_TO_UTF8(*Buckets[i]), TCHAR_TO_UTF8(*Collections[i]), TCHAR_TO_UTF8(*Records[i]));
			else builder.Remove(TCHAR_TO_UTF8(*Buckets[i]), TCHAR_TO_UTF8(*Collections[i]), TCHAR_TO_UTF8(*Records[i]), TCHAR_TO_UTF8(*Versions[i]));
		}

		auto message = builder.Build();
		client->Send(message, success, fail);
		break;
	}
	}
}

UNBPMatchRequest* UNBPMatchRequest::CreateMatch(UNakamaComponent* nakama, FDelegateOnSuccess_Match onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPMatchRequest>();
	proxy->mode = Mode::Create;
	proxy->NakamaRef = nakama;
	proxy->OnCreateJoinSuccess = onSuccess;
	proxy->OnFail = onFail;
	return proxy;
}

UNBPMatchRequest* UNBPMatchRequest::JoinMatch(UNakamaComponent* nakama, FString matchId, FDelegateOnSuccess_Match onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPMatchRequest>();
	proxy->mode = Mode::Join;
	proxy->MatchId = matchId;
	proxy->NakamaRef = nakama;
	proxy->OnCreateJoinSuccess = onSuccess;
	proxy->OnFail = onFail;
	return proxy;
}

UNBPMatchRequest* UNBPMatchRequest::LeaveMatch(UNakamaComponent* nakama, FString matchId, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPMatchRequest>();
	proxy->mode = Mode::Leave;
	proxy->MatchId = matchId;
	proxy->NakamaRef = nakama;
	proxy->OnLeaveSendSuccess = onSuccess;
	proxy->OnFail = onFail;
	return proxy;
}

UNBPMatchRequest* UNBPMatchRequest::SendData(UNakamaComponent* nakama, FString matchId, int32 opCode, FString data, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPMatchRequest>();
	proxy->mode = Mode::Post;
	proxy->MatchId = matchId;
	proxy->OpCode = opCode;
	proxy->Data = data;
	proxy->NakamaRef = nakama;
	proxy->OnLeaveSendSuccess = onSuccess;
	proxy->OnFail = onFail;
	return proxy;
}

void UNBPMatchRequest::Activate()
{
	auto req = this;
	auto client = NakamaRef != nullptr ? NakamaRef->GetClient() : nullptr;
	if (client == nullptr) return;

	auto fail = [req](NError error) {
		if (req->OnFail.IsBound())
			req->OnFail.Execute(UNBPError::From(error));
	};

	switch (mode) {
	case Mode::Create: {
		auto success = [req](void* obj) {
			if (req->OnCreateJoinSuccess.IsBound()) {
				auto data = (NMatch*)obj;
				req->OnCreateJoinSuccess.Execute(UNBPMatch::From(*data));
			}
		};

		auto message = NMatchCreateMessage::Default();
		client->Send(message, success, fail);
		break;
	}
	case Mode::Join: {
		auto success = [req](void* obj) {
			if (req->OnCreateJoinSuccess.IsBound()) {
				auto data = (NMatch*)obj;
				req->OnCreateJoinSuccess.Execute(UNBPMatch::From(*data));
			}
		};

		auto message = NMatchJoinMessage::Default(TCHAR_TO_UTF8(*MatchId));
		client->Send(message, success, fail);
		break;
	}
	case Mode::Leave: {
		auto success = [req](void* obj) {
			if (req->OnLeaveSendSuccess.IsBound()) {
				req->OnLeaveSendSuccess.Execute();
			}
		};

		auto message = NMatchLeaveMessage::Default(TCHAR_TO_UTF8(*MatchId));
		client->Send(message, success, fail);
		break;
	}
	case Mode::Post: {
		auto success = [req](void* obj) {
			if (req->OnLeaveSendSuccess.IsBound()) {
				req->OnLeaveSendSuccess.Execute();
			}
		};

		auto message = NMatchDataSendMessage::Default(TCHAR_TO_UTF8(*MatchId), OpCode, TCHAR_TO_UTF8(*Data));
		client->Send(message, success, fail);
		break;
	}
	}
}

UNBPTopicRequest* UNBPTopicRequest::JoinDirectMessageTopic(UNakamaComponent* nakama, FString userId, FDelegateOnSuccess_Topic onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPTopicRequest>();
	proxy->mode = Mode::Join;
	proxy->TType = TopicType::DirectMessage;
	proxy->Id = userId;
	proxy->NakamaRef = nakama;
	proxy->OnJoinSuccess = onSuccess;
	proxy->OnFail = onFail;
	return proxy;
}

UNBPTopicRequest* UNBPTopicRequest::JoinRoomTopic(UNakamaComponent* nakama, FString room, FDelegateOnSuccess_Topic onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPTopicRequest>();
	proxy->mode = Mode::Join;
	proxy->TType = TopicType::Room;
	proxy->Id = room;
	proxy->NakamaRef = nakama;
	proxy->OnJoinSuccess = onSuccess;
	proxy->OnFail = onFail;
	return proxy;
}

UNBPTopicRequest* UNBPTopicRequest::JoinGroupTopic(UNakamaComponent* nakama, FString groupId, FDelegateOnSuccess_Topic onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPTopicRequest>();
	proxy->mode = Mode::Join;
	proxy->TType = TopicType::Group;
	proxy->Id = groupId;
	proxy->NakamaRef = nakama;
	proxy->OnJoinSuccess = onSuccess;
	proxy->OnFail = onFail;
	return proxy;
}

UNBPTopicRequest* UNBPTopicRequest::LeaveTopic(UNakamaComponent* nakama, UNBPTopicId* topicId, FDelegateOnSuccess onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPTopicRequest>();
	proxy->mode = Mode::Leave;
	proxy->TopicId = topicId;
	proxy->NakamaRef = nakama;
	proxy->OnLeaveSuccess = onSuccess;
	proxy->OnFail = onFail;
	return proxy;
}

UNBPTopicRequest* UNBPTopicRequest::SendTopicMessage(UNakamaComponent* nakama, UNBPTopicId* topicId, FString data, FDelegateOnSuccess_TopicMessageAck onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPTopicRequest>();
	proxy->mode = Mode::Send;
	proxy->TopicId = topicId;
	proxy->Data = data;
	proxy->NakamaRef = nakama;
	proxy->OnSendSuccess = onSuccess;
	proxy->OnFail = onFail;
	return proxy;
}

UNBPTopicRequest* UNBPTopicRequest::ListDirectMessageTopicMessages(UNakamaComponent* nakama, FString userId, UNBPCursor* cursor, bool forward, int32 limit, FDelegateOnSuccess_TopicMessageList onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPTopicRequest>();
	proxy->mode = Mode::List;
	proxy->TType = TopicType::DirectMessage;
	proxy->Id = userId;
	proxy->Cursor = cursor;
	proxy->Forward = forward;
	proxy->Limit = limit;
	proxy->NakamaRef = nakama;
	proxy->OnListSuccess = onSuccess;
	proxy->OnFail = onFail;
	return proxy;
}

UNBPTopicRequest* UNBPTopicRequest::ListRoomTopicMessages(UNakamaComponent* nakama, FString room, UNBPCursor* cursor, bool forward, int32 limit, FDelegateOnSuccess_TopicMessageList onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPTopicRequest>();
	proxy->mode = Mode::List;
	proxy->TType = TopicType::Room;
	proxy->Id = room;
	proxy->Cursor = cursor;
	proxy->Forward = forward;
	proxy->Limit = limit;
	proxy->NakamaRef = nakama;
	proxy->OnListSuccess = onSuccess;
	proxy->OnFail = onFail;
	return proxy;
}

UNBPTopicRequest* UNBPTopicRequest::ListGroupTopicMessages(UNakamaComponent* nakama, FString groupId, UNBPCursor* cursor, bool forward, int32 limit, FDelegateOnSuccess_TopicMessageList onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPTopicRequest>();
	proxy->mode = Mode::List;
	proxy->TType = TopicType::Group;
	proxy->Id = groupId;
	proxy->Cursor = cursor;
	proxy->Forward = forward;
	proxy->Limit = limit;
	proxy->NakamaRef = nakama;
	proxy->OnListSuccess = onSuccess;
	proxy->OnFail = onFail;
	return proxy;
}

void UNBPTopicRequest::Activate()
{
	auto req = this;
	auto client = NakamaRef != nullptr ? NakamaRef->GetClient() : nullptr;
	if (client == nullptr) return;

	auto fail = [req](NError error) {
		if (req->OnFail.IsBound())
			req->OnFail.Execute(UNBPError::From(error));
	};

	switch (mode) {
	case Mode::Join: {
		auto success = [req](void* obj) {
			if (req->OnJoinSuccess.IsBound()) {
				auto data = (NTopic*)obj;
				req->OnJoinSuccess.Execute(UNBPTopic::From(*data));
			}
		};

		auto builder = NTopicJoinMessage::Builder();
		switch (TType) {
		case TopicType::DirectMessage:
			builder.TopicDirectMessage(TCHAR_TO_UTF8(*Id));
			break;
		case TopicType::Room:
			builder.TopicRoom(TCHAR_TO_UTF8(*Id));
			break;
		case TopicType::Group:
			builder.TopicGroup(TCHAR_TO_UTF8(*Id));
			break;
		}

		auto message = builder.Build();
		client->Send(message, success, fail);
		break;
	}
	case Mode::Leave: {
		auto success = [req](void* obj) {
			if (req->OnLeaveSuccess.IsBound()) {
				req->OnLeaveSuccess.Execute();
			}
		};

		auto message = NTopicLeaveMessage::Default(TopicId->GetNTopicId());
		client->Send(message, success, fail);
		break;
	}
	case Mode::Send: {
		auto success = [req](void* obj) {
			if (req->OnSendSuccess.IsBound()) {
				auto data = (NTopicMessageAck*)obj;
				req->OnSendSuccess.Execute(UNBPTopicMessageAck::From(*data));
			}
		};

		auto message = NTopicMessageSendMessage::Default(TopicId->GetNTopicId(), TCHAR_TO_UTF8(*Data));
		client->Send(message, success, fail);
		break;
	}
	case Mode::List: {
		auto success = [req](void* obj) {
			if (req->OnListSuccess.IsBound()) {
				auto rs = (NResultSet<NTopicMessage>*)obj;
				req->OnListSuccess.Execute(UNBPTopicMessage::FromResultSet(rs), UNBPCursor::From(rs->GetCursor()));
			}
		};

		auto builder = NTopicMessagesListMessage::Builder();
		if (Cursor != nullptr) builder.Cursor(Cursor->GetNCursor());
		if (Limit != 0) builder.Limit(Limit);
		builder.Forward(Forward);
		switch (TType) {
		case TopicType::DirectMessage:
			builder.TopicDirectMessage(TCHAR_TO_UTF8(*Id));
			break;
		case TopicType::Room:
			builder.TopicRoom(TCHAR_TO_UTF8(*Id));
			break;
		case TopicType::Group:
			builder.TopicGroup(TCHAR_TO_UTF8(*Id));
			break;
		}

		auto message = builder.Build();
		client->Send(message, success, fail);
		break;
	}
	}
}


/**
* Handling for Leaderboards
*/

// ------------------------- UNBPListLeaderboardsRequest -------------------------

UNBPListLeaderboardsRequest* UNBPListLeaderboardsRequest::ListLeaderboards(UNakamaComponent* nakama, UNBPCursor* cursor, int32 limit, FDelegateOnSuccess_LeaderboardList onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPListLeaderboardsRequest>();
	proxy->Cursor = cursor;
	proxy->Limit = limit;
	proxy->NakamaRef = nakama;
	proxy->OnSuccess = onSuccess;
	proxy->OnFail = onFail;
	return proxy;
}

void UNBPListLeaderboardsRequest::Activate()
{
	auto req = this;
	auto client = NakamaRef != nullptr ? NakamaRef->GetClient() : nullptr;
	if (client == nullptr) return;

	auto fail = [req](NError error) {
		if (req->OnFail.IsBound())
			req->OnFail.Execute(UNBPError::From(error));
	};

	auto success = [req](void* obj) {
		if (req->OnSuccess.IsBound()) {
			auto rs = (NResultSet<NLeaderboard>*)obj;
			req->OnSuccess.Execute(UNBPLeaderboard::FromResultSet(rs), UNBPCursor::From(rs->GetCursor()));
		}
	};

	auto builder = NLeaderboardsListMessage::Builder();
	if (Cursor != nullptr) builder.Cursor(Cursor->GetNCursor());
	if (Limit != 0) builder.Limit(Limit);

	auto message = builder.Build();
	client->Send(message, success, fail);
}


/**
* Handling for LeaderboardRecords
*/

// ------------------------- UNBPLeaderboardRecordsRequest -------------------------

UNBPLeaderboardRecordsRequest* UNBPLeaderboardRecordsRequest::FetchRecords(UNakamaComponent* nakama, FString leaderboardId, UNBPCursor* cursor, int32 limit, FDelegateOnSuccess_LeaderboardRecordList onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPLeaderboardRecordsRequest>();
	proxy->mode = Mode::Fetch;
	proxy->LeaderboardId = leaderboardId;
	proxy->Cursor = cursor;
	proxy->Limit = limit;
	proxy->NakamaRef = nakama;
	proxy->OnListFetchSuccess = onSuccess;
	proxy->OnFail = onFail;
	return proxy;
}

UNBPLeaderboardRecordsRequest* UNBPLeaderboardRecordsRequest::ListRecords(UNakamaComponent* nakama, FString leaderboardId, TArray<FString> ownerIdsFilter, FString langFilter, FString locationFilter, FString timezoneFilter, UNBPCursor* cursor, int32 limit, FDelegateOnSuccess_LeaderboardRecordList onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPLeaderboardRecordsRequest>();
	proxy->mode = Mode::List;
	proxy->LeaderboardId = leaderboardId;
	proxy->OwnerIds = ownerIdsFilter;
	proxy->Lang = langFilter;
	proxy->Location = locationFilter;
	proxy->Timezone = timezoneFilter;
	proxy->Cursor = cursor;
	proxy->Limit = limit;
	proxy->NakamaRef = nakama;
	proxy->OnListFetchSuccess = onSuccess;
	proxy->OnFail = onFail;
	return proxy;
}

UNBPLeaderboardRecordsRequest* UNBPLeaderboardRecordsRequest::WriteRecord(UNakamaComponent* nakama, FString leaderboardId, FString location, FString timezone, FString metadata, int32 setValue, int32 bestValue, int32 incr, int32 decr, FDelegateOnSuccess_LeaderboardRecord onSuccess, FDelegateOnFail onFail)
{
	auto proxy = NewObject<UNBPLeaderboardRecordsRequest>();
	proxy->mode = Mode::Write;
	proxy->LeaderboardId = leaderboardId;
	proxy->Location = location;
	proxy->Timezone = timezone;
	proxy->Metadata = metadata;
	proxy->Set = setValue;
	proxy->Best = bestValue;
	proxy->Incr = incr;
	proxy->Decr = decr;
	proxy->NakamaRef = nakama;
	proxy->OnWriteSuccess = onSuccess;
	proxy->OnFail = onFail;
	return proxy;
}

void UNBPLeaderboardRecordsRequest::Activate()
{
	auto req = this;
	auto client = NakamaRef != nullptr ? NakamaRef->GetClient() : nullptr;
	if (client == nullptr) return;

	auto fail = [req](NError error) {
		if (req->OnFail.IsBound())
			req->OnFail.Execute(UNBPError::From(error));
	};

	switch (mode) {
	case Mode::Fetch: {
		auto success = [req](void* obj) {
			if (req->OnListFetchSuccess.IsBound()) {
				auto rs = (NResultSet<NLeaderboardRecord>*)obj;
				req->OnListFetchSuccess.Execute(UNBPLeaderboardRecord::FromResultSet(rs), UNBPCursor::From(rs->GetCursor()));
			}
		};

		auto builder = NLeaderboardRecordsFetchMessage::Builder(TCHAR_TO_UTF8(*LeaderboardId));
		if (Cursor != nullptr) builder.Cursor(Cursor->GetNCursor());
		if (Limit != 0) builder.Limit(Limit);

		auto message = builder.Build();
		client->Send(message, success, fail);
		break;
	}
	case Mode::List: {
		auto success = [req](void* obj) {
			if (req->OnListFetchSuccess.IsBound()) {
				auto rs = (NResultSet<NLeaderboardRecord>*)obj;
				req->OnListFetchSuccess.Execute(UNBPLeaderboardRecord::FromResultSet(rs), UNBPCursor::From(rs->GetCursor()));
			}
		};

		auto builder = NLeaderboardRecordsListMessage::Builder(TCHAR_TO_UTF8(*LeaderboardId));
		if (OwnerIds.Num() > 0) {
			std::vector<std::string> ids;
			for (int i = 0; i < OwnerIds.Num(); i++) {
				ids.push_back(TCHAR_TO_UTF8(*OwnerIds[i]));
			}
			builder.FilterByOwnerIds(ids);
		}
		if (!Lang.IsEmpty()) builder.FilterByLang(TCHAR_TO_UTF8(*Lang));
		if (!Location.IsEmpty()) builder.FilterByLocation(TCHAR_TO_UTF8(*Location));
		if (!Timezone.IsEmpty()) builder.FilterByTimezone(TCHAR_TO_UTF8(*Timezone));
		if (Cursor != nullptr) builder.Cursor(Cursor->GetNCursor());
		if (Limit != 0) builder.Limit(Limit);

		auto message = builder.Build();
		client->Send(message, success, fail);
		break;
	}
	case Mode::Write: {
		auto success = [req](void* obj) {
			if (req->OnWriteSuccess.IsBound()) {
				auto data = (NLeaderboardRecord*)obj;
				req->OnWriteSuccess.Execute(UNBPLeaderboardRecord::From(*data));
			}
		};

		auto builder = NLeaderboardRecordWriteMessage::Builder(TCHAR_TO_UTF8(*LeaderboardId));
		if (!Location.IsEmpty()) builder.Location(TCHAR_TO_UTF8(*Location));
		if (!Timezone.IsEmpty()) builder.Timezone(TCHAR_TO_UTF8(*Timezone));
		if (!Metadata.IsEmpty()) builder.Metadata(TCHAR_TO_UTF8(*Metadata));

		// XXX: We may need to switch these to some nullable type since 0 is likely valid here.  For now, supply all values.
		builder.Set(Set);
		builder.Best(Best);
		builder.Increment(Incr);
		builder.Decrement(Decr);

		auto message = builder.Build();
		client->Send(message, success, fail);
		break;
	}
	}
}
