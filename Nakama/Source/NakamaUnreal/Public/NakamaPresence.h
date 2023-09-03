// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NakamaPresence.generated.h"


UENUM(BlueprintType)
enum class ENakamaPresenceEvent : uint8
{
	None,
	LEAVES UMETA(DisplayName = "Leaves"),
	JOINS UMETA(DisplayName = "Joins"),
};


USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaUserPresence
{
	GENERATED_BODY()

	// The user this presence belongs to.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|User|Presence", meta = (JsonProperty = "user_id"))
	FString UserID;

	// A unique session ID identifying the particular connection, because the user may have many.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|User|Presence", meta = (JsonProperty = "session_id"))
	FString SessionID;

	// The username for display purposes.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|User|Presence", meta = (JsonProperty = "username"))
	FString Username;

	// Whether this presence generates persistent data/messages, if applicable for the stream type.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|User|Presence", meta = (JsonProperty = "persistence"))
	bool Persistence = false;

	// A user-set status message for this stream, if applicable.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|User|Presence")
	FString Status;

	FNakamaUserPresence(const FString& JsonString);
	FNakamaUserPresence();

};