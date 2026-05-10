/*
 * Copyright 2026 The Nakama Authors
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
#include "NakamaOptionals.generated.h"

USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaOptionalBool
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Nakama|Optional")
	bool bIsSet = false;

	UPROPERTY(BlueprintReadWrite, Category = "Nakama|Optional")
	bool Value = false;

	FNakamaOptionalBool() = default;
	FNakamaOptionalBool(bool InValue) : bIsSet(true), Value(InValue) {}

	bool IsSet() const { return bIsSet; }
	bool IsEmpty() const { return !bIsSet; }
	bool GetValue() const { return Value; }
};

USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaOptionalInt32
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Nakama|Optional")
	bool bIsSet = false;

	UPROPERTY(BlueprintReadWrite, Category = "Nakama|Optional")
	int32 Value = 0;

	FNakamaOptionalInt32() = default;
	FNakamaOptionalInt32(int32 InValue) : bIsSet(true), Value(InValue) {}
	FNakamaOptionalInt32(double InValue) : bIsSet(true), Value(static_cast<int32>(InValue)) {}

	bool IsSet() const { return bIsSet; }
	bool IsEmpty() const { return !bIsSet; }
	int32 GetValue() const { return Value; }
};

USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaOptionalInt64
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Nakama|Optional")
	bool bIsSet = false;

	UPROPERTY(BlueprintReadWrite, Category = "Nakama|Optional")
	int64 Value = 0;

	FNakamaOptionalInt64() = default;
	FNakamaOptionalInt64(int64 InValue) : bIsSet(true), Value(InValue) {}
	FNakamaOptionalInt64(double InValue) : bIsSet(true), Value(static_cast<int64>(InValue)) {}

	bool IsSet() const { return bIsSet; }
	bool IsEmpty() const { return !bIsSet; }
	int64 GetValue() const { return Value; }
};

USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaOptionalFloat
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Nakama|Optional")
	bool bIsSet = false;

	UPROPERTY(BlueprintReadWrite, Category = "Nakama|Optional")
	float Value = 0.f;

	FNakamaOptionalFloat() = default;
	FNakamaOptionalFloat(float InValue) : bIsSet(true), Value(InValue) {}
	FNakamaOptionalFloat(double InValue) : bIsSet(true), Value(static_cast<float>(InValue)) {}

	bool IsSet() const { return bIsSet; }
	bool IsEmpty() const { return !bIsSet; }
	float GetValue() const { return Value; }
};

USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaOptionalDouble
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Nakama|Optional")
	bool bIsSet = false;

	UPROPERTY(BlueprintReadWrite, Category = "Nakama|Optional")
	double Value = 0.0;

	FNakamaOptionalDouble() = default;
	FNakamaOptionalDouble(double InValue) : bIsSet(true), Value(InValue) {}

	bool IsSet() const { return bIsSet; }
	bool IsEmpty() const { return !bIsSet; }
	double GetValue() const { return Value; }
};

using FNakamaRtOptionalBool   = FNakamaOptionalBool;
using FNakamaRtOptionalInt32  = FNakamaOptionalInt32;
using FNakamaRtOptionalInt64  = FNakamaOptionalInt64;
using FNakamaRtOptionalFloat  = FNakamaOptionalFloat;
using FNakamaRtOptionalDouble = FNakamaOptionalDouble;

