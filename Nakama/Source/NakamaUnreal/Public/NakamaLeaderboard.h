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
#include "NakamaLeaderboard.generated.h"

// Leaderboardss
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaLeaderboardRecord
{
	GENERATED_BODY()

	// The ID of the leaderboard this score belongs to.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Leaderboards")
	FString LeaderboardId;

	// The ID of the score owner, usually a user or group.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Leaderboards")
	FString OwnerId;

	// The username of the score owner, if the owner is a user.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Leaderboards")
	FString Username;

	// The score value.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Leaderboards")
	int64 Score = 0;

	// An optional subscore value.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Leaderboards")
	int64 SubScore = 0;

	// The number of submissions to this score record.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Leaderboards")
	int64 NumScore = 0;

	// The maximum number of score updates allowed by the owner.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Leaderboards")
	int32 MaxNumScore = 0;

	// Metadata.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Leaderboards")
	FString Metadata;

	// The UNIX time when the leaderboard record was created.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Leaderboards")
	FDateTime CreateTime = 0;

	//The UNIX time when the leaderboard record was updated.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Leaderboards")
	FDateTime UpdateTime = 0;

	//The UNIX time when the leaderboard record expires.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Leaderboards")
	FDateTime ExpiryTime = 0;

	//The rank of this record.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Leaderboards")
	int64 Rank = 0;

	FNakamaLeaderboardRecord(const FString& JsonString);
    FNakamaLeaderboardRecord(const TSharedPtr<class FJsonObject> JsonObject);
    FNakamaLeaderboardRecord();

};


UENUM(BlueprintType)
enum class ENakamaLeaderboardListBy : uint8
{
	//The object is only writable by server runtime
	BY_SCORE UMETA(DisplayName = "By Score"),
	//Only the user who owns it may write
	BY_FRIENDS UMETA(DisplayName = "By Friends"),
};


USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaLeaderboardRecordList
{
	GENERATED_BODY()

	//A list of leaderboard records.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Leaderboards")
	TArray<FNakamaLeaderboardRecord> Records;

	//A batched set of leaderboard records belonging to specified owners.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Leaderboards")
	TArray<FNakamaLeaderboardRecord> OwnerRecords;

	//The cursor to send when retrieving the next page, if any.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Leaderboards")
	FString NextCursor;

	//The cursor to send when retrieving the previous page, if any.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Leaderboards")
	FString PrevCursor;

	FNakamaLeaderboardRecordList(const FString& JsonString);
	FNakamaLeaderboardRecordList();

};