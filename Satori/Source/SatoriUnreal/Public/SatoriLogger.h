// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SatoriLogger.generated.h"

//DECLARE_LOG_CATEGORY_EXTERN(LogSatori, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogSatoriUnreal, Log, All);

UENUM(BlueprintType, Category = "Satori")
enum class ESatoriLogLevel : uint8
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
class SATORIUNREAL_API USatoriLogger : public UObject
{
	GENERATED_BODY()

public:
	USatoriLogger();

	UFUNCTION(BlueprintCallable, Category = "Satori")
	static void SetLogLevel(ESatoriLogLevel InLogLevel);

	UFUNCTION(BlueprintCallable, Category = "Satori")
	static void Log(ESatoriLogLevel InLogLevel, const FString& Message);

	UFUNCTION(BlueprintCallable, Category = "Satori")
	static void EnableLogging(bool bEnable);

private:
	static ESatoriLogLevel CurrentLogLevel;
	static bool bLoggingEnabled;
	static bool IsLoggable(ESatoriLogLevel InLogLevel);
};
