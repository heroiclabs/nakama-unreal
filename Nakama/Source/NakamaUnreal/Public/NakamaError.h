// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NakamaError.generated.h"

// Error Data
UENUM(BlueprintType)
enum class ENakamaErrorCode : uint8
{
	Unknown = 0 UMETA(DisplayName = "Unknown"),
	NotFound = 1 UMETA(DisplayName = "Not Found"),
	AlreadyExists = 2 UMETA(DisplayName = "Already Exists"),
	InvalidArgument = 3 UMETA(DisplayName = "Invalid Argument"),
	Unauthenticated = 4 UMETA(DisplayName = "Unauthenticated"),
	PermissionDenied = 5 UMETA(DisplayName = "Permission Denied"),
	ConnectionError = 6  UMETA(DisplayName = "Connection Error"), // -1
	InternalError = 7 UMETA(DisplayName = "Internal Error"), // -2
	CancelledByUser = 8 UMETA(DisplayName = "Cancelled By User"), //-3
};

USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaError
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama Error")
	FString Message;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama Error")
	ENakamaErrorCode Code;

	FNakamaError(const FString& JsonString);
	FNakamaError(): Code(ENakamaErrorCode::Unknown) { }

	ENakamaErrorCode ConvertNakamaErrorCode(int32 CodeValue);


};