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
#include "SatoriLiveEvent.generated.h"

UENUM(BlueprintType)
enum class ESatoriLiveEventStatus : uint8
{
	UNKNOWN = 0,
	ACTIVE = 1,
	UPCOMING = 2,
	TERMINATED = 3
};

// LiveEvents
USTRUCT(BlueprintType)
struct SATORIUNREAL_API FSatoriLiveEvent
{
	GENERATED_BODY()

	// The labels associated with this experiment.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|LiveEvents")
	TArray<FString> Labels;
	
	// The names of the feature flags this experiment overrides.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|LiveEvents")
	TArray<FString> FlagNames;
	
	// The live event identifier.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|LiveEvents")
	FString ID;

	// Name.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|LiveEvents")
	FString Name;

	// Description.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|LiveEvents")
	FString Description;

	// Event value.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|LiveEvents")
	FString Value;

	// Reset CRON schedule, if configured.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|LiveEvents")
	FString ResetCron;

	// Start time of current event run.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|LiveEvents")
	int64 ActiveStartTimeSec = 0;

	// End time of current event run.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|LiveEvents")
	int64 ActiveEndTimeSec = 0;
	
	// End time of the caller's participation, if participation_duration_sec is set on the event. 0 means no limit.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|LiveEvents")
	int64 ActiveParticipationEndTimeSec = 0;

	// Start time.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|LiveEvents")
	int64 StartTimeSec = 0;

	// End time, 0 if it repeats forever.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|LiveEvents")
	int64 EndTimeSec = 0;

	// Duration in seconds.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|LiveEvents")
	int64 DurationSec = 0;
	
	// The status of this live event run.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|LiveEvents")
	ESatoriLiveEventStatus Status = ESatoriLiveEventStatus::UNKNOWN;

	FSatoriLiveEvent(const FString& JsonString);
	FSatoriLiveEvent(const TSharedPtr<class FJsonObject> JsonObject);
	FSatoriLiveEvent(); // Default Constructor
};

USTRUCT(BlueprintType)
struct SATORIUNREAL_API FSatoriLiveEventList
{
	GENERATED_BODY()

	// Live events.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|LiveEvents")
	TArray<FSatoriLiveEvent> LiveEvents;
	
	// Live events that require explicit joins.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|LiveEvents")
	TArray<FSatoriLiveEvent> ExplicitJoinLiveEvents;

	FSatoriLiveEventList(const FString& JsonString);
	FSatoriLiveEventList(); // Default Constructor
};
