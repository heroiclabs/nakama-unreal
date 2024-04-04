// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NakamaError.generated.h"

// Error Data
UENUM(BlueprintType)
enum class ENakamaErrorCode : uint8
{
	Ok = 0 UMETA(DisplayName = "Ok"),
	Cancelled = 1 UMETA(DisplayName = "Cancelled"),
	Unknown = 2 UMETA(DisplayName = "Unknown"),
	InvalidArgument = 3 UMETA(DisplayName = "Invalid Argument"),
	DeadlineExceeded = 4 UMETA(DisplayName = "Deadline Exceeded"),
	NotFound = 5 UMETA(DisplayName = "Not Found"),
	AlreadyExists = 6 UMETA(DisplayName = "Already Exists"),
	PermissionDenied = 7 UMETA(DisplayName = "Permission Denied"),
	ResourceExhausted = 8 UMETA(DisplayName = "Resource Exhausted"),
	FailedPrecondition = 9 UMETA(DisplayName = "Failed Precondition"),
	Aborted = 10 UMETA(DisplayName = "Aborted"),
	OutOfRange = 11 UMETA(DisplayName = "Out Of Range"),
	Unimplemented = 12 UMETA(DisplayName = "Unimplemented"),
	Internal = 13 UMETA(DisplayName = "Internal"),
	Unavailable = 14 UMETA(DisplayName = "Unavailable"),
	DataLoss = 15 UMETA(DisplayName = "Data Loss"),
	Unauthenticated = 16 UMETA(DisplayName = "Unauthenticated")
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