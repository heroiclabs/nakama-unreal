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
