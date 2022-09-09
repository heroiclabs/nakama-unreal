// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NakamaClient.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NakamaLibrary.generated.h"


/**
 *
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	
	UFUNCTION(BlueprintCallable, Category = "Nakama|Utilities")
	static FNakamaChatMessage ChatMessageJsonToStruct(FString JsonMessage);

	UFUNCTION(BlueprintCallable, Category = "Nakama|Utilities")
	static FString ChatMessageStructToJson(FNakamaChatMessage MessageStruct);


};
