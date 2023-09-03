// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NakamaLogger.generated.h"

//DECLARE_LOG_CATEGORY_EXTERN(LogNakama, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogNakamaUnreal, Log, All);

UENUM(BlueprintType, Category = "Nakama")
enum class ENakamaLogLevel : uint8
{
	Debug,
	Info,
	Warn,
	Error,
	Fatal
};

/**
 * 
 */
UCLASS()
class NAKAMAUNREAL_API UNakamaLogger : public UObject
{
	GENERATED_BODY()

public:
	UNakamaLogger();

	UFUNCTION(BlueprintCallable, Category = "Nakama")
	static void SetLogLevel(ENakamaLogLevel InLogLevel);

	UFUNCTION(BlueprintCallable, Category = "Nakama")
	static void Log(ENakamaLogLevel InLogLevel, const FString& Message);

	UFUNCTION(BlueprintCallable, Category = "Nakama")
	static void EnableLogging(bool bEnable);

private:
	static ENakamaLogLevel CurrentLogLevel;
	static bool bLoggingEnabled;
	static bool IsLoggable(ENakamaLogLevel InLogLevel);
};
