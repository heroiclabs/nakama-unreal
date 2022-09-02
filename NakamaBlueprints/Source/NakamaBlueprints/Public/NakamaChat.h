#pragma once

#include "CoreMinimal.h"
#include "NakamaChannelTypes.h"
#include "nakama-cpp/realtime/rtdata/NChannel.h"
#include "NakamaPresence.h"
#include "NakamaChat.generated.h"

//struct FNakamaUserPresence; // Forward Declare

namespace Nakama
{
	struct NChannel;
}

// For sending messages (Internal to plugin, no need to convert)
USTRUCT(BlueprintType) 
struct NAKAMABLUEPRINTS_API FNakamaChatMessage
{
	GENERATED_BODY()

	// The Chat Message.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nakama Chat")
	FString ChatMessage;

	// The Message Type.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nakama Chat")
	ENakamaChannelType MessageType;

	// Group Name to Send To.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nakama Chat")
	FString GroupName;

};


// Channels
USTRUCT(BlueprintType)
struct NAKAMABLUEPRINTS_API FNakamaChannel
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama Chat")
	FString RoomName;

	// The ID of the group, or an empty string if this message was not sent through a group channel.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama Chat")
	FString GroupId;

	// The ID of the first DM user, or an empty string if this message was not sent through a DM chat.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama Chat")
	FString UserIdOne;

	// The ID of the second DM user, or an empty string if this message was not sent through a DM chat.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama Chat")
	FString UserIdTwo;

	FNakamaChannel(const NChannel& NakamaNativeChannel);
	FNakamaChannel();
	
};

// For sending messages (Internal to plugin, no need to convert)
USTRUCT(BlueprintType)
struct NAKAMABLUEPRINTS_API FNakamaPrivateChat
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