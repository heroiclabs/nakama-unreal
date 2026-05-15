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
#include "SatoriOptionals.generated.h"

USTRUCT(BlueprintType)
struct SATORIAPI_API FSatoriOptionalBool
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Satori|Optional")
	bool bIsSet = false;

	UPROPERTY(BlueprintReadWrite, Category = "Satori|Optional")
	bool Value = false;

	FSatoriOptionalBool() = default;
	FSatoriOptionalBool(bool InValue) : bIsSet(true), Value(InValue) {}

	bool IsSet() const { return bIsSet; }
	bool IsEmpty() const { return !bIsSet; }
	bool GetValue() const { return Value; }
};

USTRUCT(BlueprintType)
struct SATORIAPI_API FSatoriOptionalInt32
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Satori|Optional")
	bool bIsSet = false;

	UPROPERTY(BlueprintReadWrite, Category = "Satori|Optional")
	int32 Value = 0;

	FSatoriOptionalInt32() = default;
	FSatoriOptionalInt32(int32 InValue) : bIsSet(true), Value(InValue) {}
	FSatoriOptionalInt32(double InValue) : bIsSet(true), Value(static_cast<int32>(InValue)) {}

	bool IsSet() const { return bIsSet; }
	bool IsEmpty() const { return !bIsSet; }
	int32 GetValue() const { return Value; }
};

USTRUCT(BlueprintType)
struct SATORIAPI_API FSatoriOptionalInt64
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Satori|Optional")
	bool bIsSet = false;

	UPROPERTY(BlueprintReadWrite, Category = "Satori|Optional")
	int64 Value = 0;

	FSatoriOptionalInt64() = default;
	FSatoriOptionalInt64(int32 InValue) : bIsSet(true), Value(static_cast<int64>(InValue)) {}
	FSatoriOptionalInt64(int64 InValue) : bIsSet(true), Value(InValue) {}
	FSatoriOptionalInt64(double InValue) : bIsSet(true), Value(static_cast<int64>(InValue)) {}

	bool IsSet() const { return bIsSet; }
	bool IsEmpty() const { return !bIsSet; }
	int64 GetValue() const { return Value; }
};

USTRUCT(BlueprintType)
struct SATORIAPI_API FSatoriOptionalFloat
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Satori|Optional")
	bool bIsSet = false;

	UPROPERTY(BlueprintReadWrite, Category = "Satori|Optional")
	float Value = 0.f;

	FSatoriOptionalFloat() = default;
	FSatoriOptionalFloat(float InValue) : bIsSet(true), Value(InValue) {}
	FSatoriOptionalFloat(double InValue) : bIsSet(true), Value(static_cast<float>(InValue)) {}

	bool IsSet() const { return bIsSet; }
	bool IsEmpty() const { return !bIsSet; }
	float GetValue() const { return Value; }
};

USTRUCT(BlueprintType)
struct SATORIAPI_API FSatoriOptionalDouble
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Satori|Optional")
	bool bIsSet = false;

	UPROPERTY(BlueprintReadWrite, Category = "Satori|Optional")
	double Value = 0.0;

	FSatoriOptionalDouble() = default;
	FSatoriOptionalDouble(double InValue) : bIsSet(true), Value(InValue) {}

	bool IsSet() const { return bIsSet; }
	bool IsEmpty() const { return !bIsSet; }
	double GetValue() const { return Value; }
};
