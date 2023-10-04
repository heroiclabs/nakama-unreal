// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NakamaTestFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class NAKAMABLUEPRINTSTEST_API UNakamaTestFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Test")
	static FString GetMatchIdFromJsonString(const FString& JsonString);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "JSON Generation", meta = (DisplayName = "Generate Tournament JSON String"))
	static FString GenerateTournamentJSONString(
		bool bAuthoritative,
		const FString& SortOrder,
		const FString& Operator,
		int32 Duration,
		const FString& ResetSchedule,
		const FString& Title,
		const FString& Description,
		int32 Category,
		int64 StartTime,
		int64 EndTime,
		int32 MaxSize,
		int32 MaxNumScore,
		bool bJoinRequired
	);

	UFUNCTION(BlueprintPure, Category = "Nakama|Test|Utilities", meta = (DisplayName = "Get Current Unix Timestamp In Seconds"))
	static int64 GetCurrentUnixTimestampInSeconds();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Nakama|Test")
	static FString GetTournamentIdFromJsonString(const FString& JsonString);
	
};
