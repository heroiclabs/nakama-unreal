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

#include "NakamaClientConfig.generated.h"

/** Low-level API client configuration. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaClientConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nakama")
	FString ServerKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nakama")
	FString Host;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nakama")
	int32 Port = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nakama")
	bool bUseSSL = false;

	FString GetBaseUrl() const noexcept;
};
