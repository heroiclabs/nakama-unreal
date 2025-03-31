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


// LiveEvents
USTRUCT(BlueprintType)
struct SATORIUNREAL_API FSatoriLiveEvent
{
	GENERATED_BODY()

	// Name.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|LiveEvents")
	FString Name;

	// Description.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|LiveEvents")
	FString Description;

	// Event value.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|LiveEvents")
	FString Value;

	// Start time of current event run.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|LiveEvents")
	int64 ActiveStartTimeSec = -1;

	// End time of current event run.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|LiveEvents")
	int64 ActiveEndTimeSec = -1;

	// The live event identifier.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|LiveEvents")
	FString ID;

	// Start time.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|LiveEvents")
	int64 StartTimeSec = -1;

	// End time, 0 if it repeats forever.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|LiveEvents")
	int64 EndTimeSec = -1;

	// Duration in seconds.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|LiveEvents")
	int64 DurationSec = -1;

	// Reset CRON schedule, if configured.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|LiveEvents")
	FString ResetCron;

	FSatoriLiveEvent(const FString& JsonString);
	FSatoriLiveEvent(const TSharedPtr<FJsonObject> JsonObject);
	FSatoriLiveEvent(); // Default Constructor
};

USTRUCT(BlueprintType)
struct SATORIUNREAL_API FSatoriLiveEventList
{
	GENERATED_BODY()

	// Flags.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|LiveEvents")
	TArray<FSatoriLiveEvent> LiveEvents;

	FSatoriLiveEventList(const FString& JsonString);
	FSatoriLiveEventList(); // Default Constructor
};
