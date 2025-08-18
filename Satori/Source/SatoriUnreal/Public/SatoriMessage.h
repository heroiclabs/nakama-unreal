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
#include "SatoriMessage.generated.h"


// Messages
USTRUCT(BlueprintType)
struct SATORIUNREAL_API FSatoriMessage
{
	GENERATED_BODY()

	// The identifier of the schedule.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|Messages")
	FString ScheduleID;

	// The send time for the message.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|Messages")
	int64 SendTime;

	// A key-value pairs of metadata.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|Messages")
	TMap<FString, FString> Metadata;

	// The time the message was created.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|Messages")
	int64 CreateTime;

	// The time the message was updated.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|Messages")
	int64 UpdateTime;

	// The time the message was read by the client.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|Messages")
	int64 ReadTime;

	// The time the message was consumed by the identity.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|Messages")
	int64 ConsumeTime;

	// The message's text.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|Messages")
	FString Text;

	// The message's unique identifier.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|Messages")
	FString ID;

	// The message's title.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|Messages")
	FString Title;

	// The message's image url.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|Messages")
	FString ImageURL;

	FSatoriMessage(const FString& JsonString);
	FSatoriMessage(const TSharedPtr<class FJsonObject> JsonObject);
	FSatoriMessage(); // Default Constructor
};

USTRUCT(BlueprintType)
struct SATORIUNREAL_API FSatoriMessageList
{
	GENERATED_BODY()

	// Flags.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|Messages")
	TArray<FSatoriMessage> Messages;

	FSatoriMessageList(const FString& JsonString);
	FSatoriMessageList(); // Default Constructor
};
