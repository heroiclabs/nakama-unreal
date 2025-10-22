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
#include "NakamaPresence.h"
#include "NakamaMatch.generated.h"

USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaMatch
{
	GENERATED_BODY() // NMatchmakerMatched

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
	TArray<FNakamaUserPresence> Pressences; // Typo

	// A reference to the current user's presence in the match.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, DisplayName = "Self", Category = "Nakama|Realtime")
	FNakamaUserPresence Me;

	FNakamaMatch(const FString& JsonString);
    FNakamaMatch(const TSharedPtr<class FJsonObject> JsonObject);
	FNakamaMatch() : Authoritative(false), Size(0) { }

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

	FNakamaMatchData(const FString& JsonString);
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

	FNakamaMatchList(const FString& JsonString);
	FNakamaMatchList();
};
