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
#include "NakamaRtError.h"
//#include "NakamaUtils.h"
#include "Serialization/JsonSerializer.h"
#include "UObject/NoExportTypes.h"
#include "NakamaRealtimeRequestContext.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FNakamaRealtimeEnvelope
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
	int32 CID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nakama")
	FString Payload;

	FNakamaRealtimeEnvelope()
		: CID(-1)
		, Payload("")
	{
	}

	FString EncodeJson(TSharedPtr<FJsonObject> JsonObject)
	{
		FString OutputString;
		TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
		FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
		return OutputString;
	}
	
};

// Change delegate types
DECLARE_DELEGATE_OneParam(FNakamaRealtimeSuccessCallback, const FNakamaRealtimeEnvelope&); // This basically holds the payload
DECLARE_DELEGATE_OneParam(FNakamaRealtimeErrorCallback, const FNakamaRtError&);

UCLASS()
class NAKAMAUNREAL_API UNakamaRealtimeRequestContext : public UObject
{
	GENERATED_BODY()


public:
	UNakamaRealtimeRequestContext() {}

	// Note: In Nakama:
	// Errors = RtErrorCallback (always)
	// Success = std::function<void(::nakama::realtime::Envelope&)>
	
	// The callback to invoke on success
	FNakamaRealtimeSuccessCallback SuccessCallback;

	// The callback to invoke on error
	FNakamaRealtimeErrorCallback ErrorCallback;

	// The CID for the request
	int32 CID;
};
