// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NakamaPresence.h"

#include "NakamaChannelTypes.generated.h"

//Chat Category//
UENUM(BlueprintType)
enum class ENakamaChannelType : uint8
{
	// Default case. Assumed as ROOM type.
	TYPE_UNSPECIFIED UMETA(DisplayName = "Unspecified"),
	// A chat room which can be created dynamically with a name.
	ROOM UMETA(DisplayName = "Room"),
	// A private chat between two users.
	DIRECT_MESSAGE UMETA(DisplayName = "Direct Message"),
	// A chat within a group on the server.
	GROUP UMETA(DisplayName = "Group"),
};

// A message sent on a channel.
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaChannelMessage
{
	GENERATED_BODY()

	// The channel this message belongs to.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Chat|Channel")
	FString ChannelId;

	// The unique ID of this message.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Chat|Channel")
	FString MessageId;

	// The code representing a message type or category.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Chat|Channel")
	int32 code = 0;

	// Message sender, usually a user ID.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Chat|Channel")
	FString SenderId;

	// The username of the message sender, if any.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Chat|Channel")
	FString Username;

	// The content payload.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Chat|Channel")
	FString Content;

	// The UNIX time when the message was created.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Chat|Channel")
	FDateTime CreateTime = 0;

	// The UNIX time when the message was last updated.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Chat|Channel")
	FDateTime UpdateTime = 0;

	// True if the message was persisted to the channel's history, false otherwise.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Chat|Channel")
	bool Persistent = false;

	// The name of the chat room, or an empty string if this message was not sent through a chat room.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Chat|Channel")
	FString RoomName;

	// The ID of the group, or an empty string if this message was not sent through a group channel.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Chat|Channel")
	FString GroupId;

	// The ID of the first DM user, or an empty string if this message was not sent through a DM chat.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Chat|Channel")
	FString UserIdOne;

	// The ID of the second DM user, or an empty string if this message was not sent through a DM chat.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Chat|Channel")
	FString UserIdTwo;

	FNakamaChannelMessage(const FString& JsonString);
	FNakamaChannelMessage(); // Default Constructor
};

// A receipt reply from a channel message send operation.
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaChannelMessageAck
{
	GENERATED_BODY()

	// The channel the message was sent to.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Chat|Channel")
	FString ChannelId;

	// The unique ID assigned to the message.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Chat|Channel")
	FString MessageId;

	// Username of the message sender.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Chat|Channel")
	FString Username;

	// The code representing a message type or category.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Chat|Channel")
	int32 code = 0;

	// The UNIX time when the message was created.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Chat|Channel")
	FDateTime CreateTime = 0;

	// The UNIX time when the message was last updated.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Chat|Channel")
	FDateTime UpdateTime = 0;

	// True if the message was persisted to the channel's history, false otherwise.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Chat|Channel")
	bool Persistent = false;

	// The name of the chat room, or an empty string if this message was not sent through a chat room.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Chat|Channel")
	FString RoomName;

	// The ID of the group, or an empty string if this message was not sent through a group channel.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Chat|Channel")
	FString GroupId;

	// The ID of the first DM user, or an empty string if this message was not sent through a DM chat.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Chat|Channel")
	FString UserIdOne;

	//
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Chat|Channel")
	FString UserIdTwo;

	FNakamaChannelMessageAck(const FString& JsonString);
	FNakamaChannelMessageAck(); // Default Constructor
};

// A list of channel messages, usually a result of a list operation.
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaChannelMessageList
{
	GENERATED_BODY()

	// A list of messages.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Chat|Channel")
	TArray<FNakamaChannelMessage> Messages;

	// The cursor to send when retireving the next page, if any.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Chat|Channel")
	FString NextCursor;

	// The cursor to send when retrieving the previous page, if any.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Chat|Channel")
	FString PrevCursor;

	FNakamaChannelMessageList(const FString& JsonString);
	FNakamaChannelMessageList();

};

USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaChannelPresenceEvent
{
	GENERATED_BODY()

	// The channel identifier this event is for.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Chat|Channel")
	FString ChannelId;

	// Presences joining the channel as part of this event, if any.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Chat|Channel")
	TArray<FNakamaUserPresence> Joins;

	// Presences leaving the channel as part of this event, if any.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Chat|Channel")
	TArray<FNakamaUserPresence> Leaves;

	// The name of the chat room, or an empty string if this message was not sent through a chat room.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Chat|Channel")
	FString RoomName;

	// The ID of the group, or an empty string if this message was not sent through a group channel.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Chat|Channel")
	FString GroupId;

	// The ID of the first DM user, or an empty string if this message was not sent through a DM chat.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Chat|Channel")
	FString UserIdOne;

	// The ID of the second DM user, or an empty string if this message was not sent through a DM chat.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Chat|Channel")
	FString UserIdTwo;

	FNakamaChannelPresenceEvent(const FString& JsonString);
	FNakamaChannelPresenceEvent(); // Default Constructor
};