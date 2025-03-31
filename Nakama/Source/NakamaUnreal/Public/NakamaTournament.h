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
#include "NakamaLeaderboard.h"
#include "NakamaTournament.generated.h"


USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaTournament
{
	GENERATED_BODY()

	// The ID of the tournament.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Tournaments")
	FString Id;

	// The title for the tournament.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Tournaments")
	FString Title;

	// The description of the tournament. May be blank.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Tournaments")
	FString Description;

	// The category of the tournament. e.g. "vip" could be category 1.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Tournaments")
	int32 Category = 0;

	// ASC or DESC sort mode of scores in the tournament.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Tournaments")
	int32 SortOrder = 0;

	// The current number of players in the tournament.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Tournaments")
	int32 Size = 0;

	// The maximum number of players for the tournament.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Tournaments")
	int32 MaxSize = 0;

	// The maximum score updates allowed per player for the current tournament.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Tournaments")
	int32 MaxNumScore = 0;

	// True if the tournament is active and can enter. A computed value.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Tournaments")
	bool CanEnter = false;

	// The UNIX time when the tournament was created.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Tournaments")
	FDateTime CreateTime = 0;

	// The UNIX time when the tournament will start.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Tournaments")
	FDateTime StartTime = 0;

	// The UNIX time when the tournament will be stopped.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Tournaments")
	FDateTime EndTime = 0;

	// The UNIX time when the tournament stops being active until next reset. A computed value.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Tournaments")
	int32 EndActive = 0;

	// The UNIX time when the tournament is next playable. A computed value.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Tournaments")
	int32 NextReset = 0;

	// Duration of the tournament in seconds.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Tournaments")
	int32 Duration = 0;

	// The UNIX time when the tournament start being active. A computed value.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Tournaments")
	int32 StartActive = 0;

	// Additional information stored as a JSON object.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Tournaments")
	FString Metadata;

	FNakamaTournament(const FString& JsonString);
	FNakamaTournament(const TSharedPtr<FJsonObject> JsonObject);
	FNakamaTournament();
	
};

// A set of tournament records which may be part of a tournament records page or a batch of individual records.
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaTournamentRecordList
{
	GENERATED_BODY()

	// A list of tournament records.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Tournaments")
	TArray<FNakamaLeaderboardRecord> Records;

	// A batched set of tournament records belonging to specified owners.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Tournaments")
	TArray<FNakamaLeaderboardRecord> OwnerRecords;

	// The cursor to send when retrieving the next page, if any.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Tournaments")
	FString NextCursor;

	// The cursor to send when retrieving the previous page, if any.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Tournaments")
	FString PrevCursor;

	FNakamaTournamentRecordList(const FString& JsonString);
	FNakamaTournamentRecordList();

};

// A list of tournaments.
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaTournamentList
{
	GENERATED_BODY()

	// A list of tournament records.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Tournaments")
	TArray<FNakamaTournament> Tournaments;

	// The cursor to send when retrieving the next page, if any.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Tournaments")
	FString Cursor;

	FNakamaTournamentList(const FString& JsonString);
	FNakamaTournamentList();

};