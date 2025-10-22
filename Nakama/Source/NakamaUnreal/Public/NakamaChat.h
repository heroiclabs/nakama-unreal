/*
* Copyright 2025 The Nakama Authors
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
#include "NakamaChannelTypes.h"
#include "NakamaPresence.h"
#include "NakamaChat.generated.h"

namespace Nakama
{
	struct NChannel;
}

// For sending messages (Internal to plugin, no need to convert)
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaChatMessage
{
	GENERATED_BODY()

	// The Chat Message.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nakama Chat")
	FString ChatMessage;

	// The Message Type.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nakama Chat")
	ENakamaChannelType MessageType = ENakamaChannelType::TYPE_UNSPECIFIED;

	// Group Name to Send To.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nakama Chat")
	FString GroupName;

	FNakamaChatMessage() : ChatMessage(TEXT("")), MessageType(ENakamaChannelType::DIRECT_MESSAGE), GroupName(TEXT(""))
	{ }
};


// Channels
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaChannel
{
	GENERATED_BODY()

	// The ID of the channel.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama Chat")
	FString Id;

	// The users currently in the channel.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama Chat")
	TArray<FNakamaUserPresence> Presences;

	// A reference to the current user's presence in the channel.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, DisplayName = "Self", Category = "Nakama Chat")
	FNakamaUserPresence Me;

	// The name of the chat room, or an empty string if this message was not sent through a chat room.
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama Chat")
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama Chat", meta = (JsonProperty = "room_name"))
	FString RoomName;

	// The ID of the group, or an empty string if this message was not sent through a group channel.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama Chat", meta = (JsonProperty = "group_id"))
	FString GroupId;

	// The ID of the first DM user, or an empty string if this message was not sent through a DM chat.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama Chat", meta = (JsonProperty = "user_id_one"))
	FString UserIdOne;

	// The ID of the second DM user, or an empty string if this message was not sent through a DM chat.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama Chat", meta = (JsonProperty = "user_id_two"))
	FString UserIdTwo;

	FNakamaChannel(const FString& JsonString);
	FNakamaChannel();
};

// For sending messages (Internal to plugin, no need to convert)
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaPrivateChat
{
	GENERATED_BODY()

	// User Id One
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama Chat")
	FString UserIdOne;

	// User Id Two
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama Chat")
	FString UserIdTwo;

	// Channel Id.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama Chat")
	FString ChannelId;

};