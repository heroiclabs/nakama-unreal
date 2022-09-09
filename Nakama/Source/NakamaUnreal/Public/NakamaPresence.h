// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "nakama-cpp/Nakama.h"
#include "NakamaPresence.generated.h"

using namespace Nakama;


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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|User|Presence")
	FString UserID;

	// A unique session ID identifying the particular connection, because the user may have many.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|User|Presence")
	FString SessionID;

	// The username for display purposes.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|User|Presence")
	FString Username;

	// Whether this presence generates persistent data/messages, if applicable for the stream type.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|User|Presence")
	bool Persistence = false;

	// A user-set status message for this stream, if applicable.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|User|Presence")
	FString Status;

	FNakamaUserPresence(const NUserPresence& NativeUserPresence);
	FNakamaUserPresence();

};