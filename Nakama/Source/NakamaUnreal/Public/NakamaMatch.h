// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "nakama-cpp/data/NMatchList.h"
#include "nakama-cpp/realtime/rtdata/NMatchData.h"

#include "NakamaPresence.h"

#include "NakamaMatch.generated.h"

using namespace Nakama;

USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaMatch
{
	GENERATED_BODY() // NMatchmakerMatched

	FNakamaMatch()
		: Authoritative(false), Size(0)
	{
	}

	FNakamaMatch(const NMatch& NativeMatch);

	// The ID of the match, can be used to join.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Realtime")
	FString MatchId;

	// True if it's an server-managed authoritative match, false otherwise.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Realtime")
	bool Authoritative;

	// Match label, if any.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Realtime")
	FString Label;

	// Current number of users in the match.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Realtime")
	int32 Size = 0;

	// The users currently in the match.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Realtime")
	TArray<FNakamaUserPresence> Pressences;

	// A reference to the current user's presence in the match.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, DisplayName = "Self", Category = "Nakama|Realtime")
	FNakamaUserPresence Me;

};

USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaMatchData
{
	GENERATED_BODY()

	// The match unique ID.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Realtime")
	FString MatchId;

	// A reference to the user presence that sent this data, if any.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Realtime")
	FNakamaUserPresence Presence;

	// User presences that have just left the match.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Realtime")
	int64 OpCode;

	// Data payload, if any.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Realtime")
	FString Data;

	FNakamaMatchData(const NMatchData& NativeMatchData);
	FNakamaMatchData();
};

// A list of realtime matches.
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaMatchList
{
	GENERATED_BODY()

	// A number of matches corresponding to a list operation.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Realtime")
	TArray<FNakamaMatch> Matches;

	FNakamaMatchList(const NMatchList& NakamaNativeMatchList);
	FNakamaMatchList();
};
