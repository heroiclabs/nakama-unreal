// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NakamaPresence.h"
#include "NakamaMatchTypes.generated.h"

USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaMatchmakerUser
{
	GENERATED_BODY()

	// User info.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Matchmaker")
	FNakamaUserPresence Presence;

	// String properties.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Matchmaker")
	TMap<FString, FString> StringProperties;

	// Numeric Properties.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Matchmaker")
	TMap<FString, int32> NumericProperties;

	FNakamaMatchmakerUser(const FString& JsonString);
	FNakamaMatchmakerUser();
};

USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaMatchmakerMatched
{
	GENERATED_BODY()

	// The matchmaking ticket that has completed.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Matchmaker")
	FString Ticket;

	// The match token or match ID to join.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Matchmaker")
	FString MatchId;

	// Match join token.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Matchmaker")
	FString Token;

	// The users that have been matched together, and information about their matchmaking data.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Matchmaker")
	TArray<FNakamaMatchmakerUser> Users;

	// A reference to the current user and their properties.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Matchmaker")
	FNakamaMatchmakerUser Me;

	FNakamaMatchmakerMatched(const FString& JsonString);
	FNakamaMatchmakerMatched();

};

USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaMatchPresenceEvent
{
	GENERATED_BODY() //NMatchmakerMatched

	//The match unique ID.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Realtime")
	FString MatchId;

	//User presences that have just joined the match.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Realtime")
	TArray<FNakamaUserPresence> Joins;

	//User presences that have just left the match.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Realtime")
	TArray<FNakamaUserPresence> Leaves;

	FNakamaMatchPresenceEvent(const FString& JsonString);
	FNakamaMatchPresenceEvent();
};

USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaMatchmakerTicket
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nakama|Matchmaker")
	FString TicketId;

	// Might want more properties here later.

	FNakamaMatchmakerTicket(const FString& JsonString);
	FNakamaMatchmakerTicket();

};
