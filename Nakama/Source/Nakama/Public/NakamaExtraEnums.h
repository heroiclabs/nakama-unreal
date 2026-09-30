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

#pragma once

#include "CoreMinimal.h"
#include "NakamaExtraEnums.generated.h"

UENUM(BlueprintType)
enum class ENakamaChannelMessageCode : uint8
{
	CHANNEL_MESSAGE_TYPE_CHAT          = 0 UMETA(DisplayName = "Chat"),
	CHANNEL_MESSAGE_TYPE_CHAT_UPDATE   = 1 UMETA(DisplayName = "Chat Update"),
	CHANNEL_MESSAGE_TYPE_CHAT_REMOVE   = 2 UMETA(DisplayName = "Chat Remove"),
	CHANNEL_MESSAGE_TYPE_GROUP_JOIN    = 3 UMETA(DisplayName = "Group Join"),
	CHANNEL_MESSAGE_TYPE_GROUP_ADD     = 4 UMETA(DisplayName = "Group Add"),
	CHANNEL_MESSAGE_TYPE_GROUP_LEAVE   = 5 UMETA(DisplayName = "Group Leave"),
	CHANNEL_MESSAGE_TYPE_GROUP_KICK    = 6 UMETA(DisplayName = "Group Kick"),
	CHANNEL_MESSAGE_TYPE_GROUP_PROMOTE = 7 UMETA(DisplayName = "Group Promote"),
	CHANNEL_MESSAGE_TYPE_GROUP_BAN     = 8 UMETA(DisplayName = "Group Ban"),
	CHANNEL_MESSAGE_TYPE_GROUP_DEMOTE  = 9 UMETA(DisplayName = "Group Demote"),
};

enum class ENakamaNotificationCode : int32
{
	NOTIFICATION_CODE_UNKNOWN            =  0,
	NOTIFICATION_CODE_DM_REQUEST         = -1,
	NOTIFICATION_CODE_FRIEND_REQUEST     = -2,
	NOTIFICATION_CODE_FRIEND_ACCEPT      = -3,
	NOTIFICATION_CODE_GROUP_ADD          = -4,
	NOTIFICATION_CODE_GROUP_JOIN_REQUEST = -5,
	NOTIFICATION_CODE_FRIEND_JOIN_GAME   = -6,
	NOTIFICATION_CODE_SINGLE_SOCKET      = -7,
	NOTIFICATION_CODE_USER_BANNED        = -8,
	NOTIFICATION_CODE_FRIEND_REMOVE      = -9,
};

UENUM(BlueprintType)
enum class ENakamaStoragePermissionRead : uint8
{
	STORAGE_PERMISSION_READ_NO_READ     = 0 UMETA(DisplayName = "No Read"),
	STORAGE_PERMISSION_READ_OWNER_READ  = 1 UMETA(DisplayName = "Owner Read"),
	STORAGE_PERMISSION_READ_PUBLIC_READ = 2 UMETA(DisplayName = "Public Read"),
};

UENUM(BlueprintType)
enum class ENakamaStoragePermissionWrite : uint8
{
	STORAGE_PERMISSION_WRITE_NO_WRITE    = 0 UMETA(DisplayName = "No Write"),
	STORAGE_PERMISSION_WRITE_OWNER_WRITE = 1 UMETA(DisplayName = "Owner Write"),
};

UENUM(BlueprintType)
enum class ENakamaStreamMode : uint8
{
	STREAM_MODE_NOTIFICATIONS       = 0 UMETA(DisplayName = "Notifications"),
	STREAM_MODE_STATUS              = 1 UMETA(DisplayName = "Status"),
	STREAM_MODE_CHANNEL             = 2 UMETA(DisplayName = "Channel"),
	STREAM_MODE_GROUP               = 3 UMETA(DisplayName = "Group"),
	STREAM_MODE_DM                  = 4 UMETA(DisplayName = "DM"),
	STREAM_MODE_MATCH_RELAYED       = 5 UMETA(DisplayName = "Match Relayed"),
	STREAM_MODE_MATCH_AUTHORITATIVE = 6 UMETA(DisplayName = "Match Authoritative"),
	STREAM_MODE_PARTY               = 7 UMETA(DisplayName = "Party"),
};
