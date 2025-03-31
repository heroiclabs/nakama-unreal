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