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
#include "SatoriFlag.generated.h"


// Flags
UENUM(BlueprintType)
enum class FSatoriFlagValueChangeReasonType : uint8
{
	UNKNOWN = 0,
	FLAG_VARIANT = 1,
	LIVE_EVENT = 2,
	EXPERIMENT = 3
};

USTRUCT(BlueprintType)
struct SATORIUNREAL_API FSatoriFlagValueChangeReason
{
	GENERATED_BODY()

	// The type of the configuration that declared the override.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|Flags")
	FSatoriFlagValueChangeReasonType Type = FSatoriFlagValueChangeReasonType::UNKNOWN;

	// The name of the configuration that overrides the flag value.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|Flags")
	FString Name;

	// The variant name of the configuration that overrides the flag value.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|Flags")
	FString VariantName;

	FSatoriFlagValueChangeReason(const FString& JsonString);
	FSatoriFlagValueChangeReason(const TSharedPtr<class FJsonObject> JsonObject);
	FSatoriFlagValueChangeReason(); // Default Constructor
};

USTRUCT(BlueprintType)
struct SATORIUNREAL_API FSatoriFlag
{
	GENERATED_BODY()

	// Flag name.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|Flags")
	FString Name;

	// Value associated with this flag.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|Flags")
	FString Value;

	// Whether the value for this flag has conditionally changed from the default state.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|Flags")
	bool bConditionChanged = false;

	// The origin of change on the flag value returned.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|Flags")
	FSatoriFlagValueChangeReason ChangeReason;

	FSatoriFlag(const FString& JsonString);
	FSatoriFlag(const TSharedPtr<class FJsonObject> JsonObject);
	FSatoriFlag(); // Default Constructor
};

USTRUCT(BlueprintType)
struct SATORIUNREAL_API FSatoriFlagList
{
	GENERATED_BODY()

	// Flags.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|Flags")
	TArray<FSatoriFlag> Flags;

	FSatoriFlagList(const FString& JsonString);
	FSatoriFlagList(); // Default Constructor
};


// Flag Overrides

UENUM(BlueprintType)
enum class FSatoriFlagOverrideType : uint8
{
	FLAG = 0,
	FLAG_VARIANT = 1,
	LIVE_EVENT_FLAG = 2,
	LIVE_EVENT_FLAG_VARIANT = 3,
	EXPERIMENT_PHASE_VARIANT_FLAG = 4
};

USTRUCT(BlueprintType)
struct SATORIUNREAL_API FSatoriFlagOverrideValue
{
	GENERATED_BODY()

	// The type of the configuration that declared the override.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|Flags")
	FSatoriFlagOverrideType Type = FSatoriFlagOverrideType::FLAG;

	// The name of the configuration that overrides the flag value.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|Flags")
	FString Name;

	// The variant name of the configuration that overrides the flag value.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|Flags")
	FString VariantName;

	// The value of the configuration that overrides the flag.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|Flags")
	FString Value;

	// The create time of the configuration that overrides the flag.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|Flags")
	int64 CreateTimeSec;

	FSatoriFlagOverrideValue(const FString& JsonString);
	FSatoriFlagOverrideValue(const TSharedPtr<class FJsonObject> JsonObject);
	FSatoriFlagOverrideValue(); // Default Constructor
};

USTRUCT(BlueprintType)
struct SATORIUNREAL_API FSatoriFlagOverride
{
	GENERATED_BODY()

	// Flag name
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|Flags")
	FString FlagName;

	// The list of configuration that affect the value of the flag.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|Flags")
	TArray<FSatoriFlagOverrideValue> Overrides;

	FSatoriFlagOverride(const FString& JsonString);
	FSatoriFlagOverride(const TSharedPtr<class FJsonObject> JsonObject);
	FSatoriFlagOverride(); // Default Constructor
};

USTRUCT(BlueprintType)
struct SATORIUNREAL_API FSatoriFlagOverrideList
{
	GENERATED_BODY()

	// Flags.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|Flags")
	TArray<FSatoriFlagOverride> Flags;

	FSatoriFlagOverrideList(const FString& JsonString);
	FSatoriFlagOverrideList(); // Default Constructor
};
