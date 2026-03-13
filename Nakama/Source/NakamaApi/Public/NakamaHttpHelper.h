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

#include <atomic>
#include "CoreMinimal.h"
#include "Dom/JsonObject.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Misc/Base64.h"
#include "Misc/DateTime.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/MemoryWriter.h"
#include "Templates/Function.h"
#include "Templates/SharedPointer.h"
#include "NakamaTypes.h"

/**
 * Internal HTTP helpers shared between NakamaApi and SatoriApi.
 * All functions are typed against FNakamaClientConfig and ENakamaRequestAuth so
 * SatoriApi does not need to redefine equivalent types.
 *
 * Include this header in generated .cpp files only — not in public API headers.
 */
namespace NakamaHttpInternal
{

inline FString SerializeJsonToString(const TSharedPtr<FJsonObject>& Json)
{
	TArray<uint8> JsonBytes;
	JsonBytes.Reserve(1024);
	FMemoryWriter Archive(JsonBytes);
	TSharedRef<TJsonWriter<UTF8CHAR, TCondensedJsonPrintPolicy<UTF8CHAR>>> Writer =
		TJsonWriterFactory<UTF8CHAR, TCondensedJsonPrintPolicy<UTF8CHAR>>::Create(&Archive);
	FJsonSerializer::Serialize(Json.ToSharedRef(), Writer);
	Writer->Close();
	FUTF8ToTCHAR Converter(reinterpret_cast<const ANSICHAR*>(JsonBytes.GetData()), JsonBytes.Num());
	return FString(Converter.Length(), Converter.Get());
}

inline FString SerializeJsonEscaped(const TSharedPtr<FJsonObject>& Json)
{
	TArray<uint8> JsonBytes;
	JsonBytes.Reserve(2048);
	FMemoryWriter Archive(JsonBytes);
	TSharedRef<TJsonWriter<UTF8CHAR, TCondensedJsonPrintPolicy<UTF8CHAR>>> Writer =
		TJsonWriterFactory<UTF8CHAR, TCondensedJsonPrintPolicy<UTF8CHAR>>::Create(&Archive);
	FJsonSerializer::Serialize(Json.ToSharedRef(), Writer);
	Writer->Close();
	FUTF8ToTCHAR Converter(reinterpret_cast<const ANSICHAR*>(JsonBytes.GetData()), JsonBytes.Num());
	FString Condensed(Converter.Length(), Converter.Get());
	FString Escaped = Condensed.Replace(TEXT("\\"), TEXT("\\\\")).Replace(TEXT("\""), TEXT("\\\""));
	return TEXT("\"") + Escaped + TEXT("\"");
}

inline void DoHttpRequest(
	const FNakamaClientConfig& Config,
	const FString& Endpoint,
	const FString& Method,
	const FString& BodyString,
	ENakamaRequestAuth AuthType,
	const FString& TokenString,
	TFunction<void(TSharedPtr<FJsonObject>)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	const FString Url = Config.GetBaseUrl() + Endpoint;

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(Url);
	Request->SetVerb(Method);
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("Accept"), TEXT("application/json"));

	switch (AuthType)
	{
	case ENakamaRequestAuth::Basic:
		{
			const FString Auth = FString::Printf(TEXT("%s:"), *Config.ServerKey);
			Request->SetHeader(TEXT("Authorization"), FString::Printf(TEXT("Basic %s"), *FBase64::Encode(Auth)));
		}
		break;
	case ENakamaRequestAuth::Bearer:
		if (!TokenString.IsEmpty())
		{
			Request->SetHeader(TEXT("Authorization"), FString::Printf(TEXT("Bearer %s"), *TokenString));
		}
		break;
	case ENakamaRequestAuth::HttpKey:
		if (!TokenString.IsEmpty())
		{
			const FString Auth = FString::Printf(TEXT("%s:"), *TokenString);
			Request->SetHeader(TEXT("Authorization"), FString::Printf(TEXT("Basic %s"), *FBase64::Encode(Auth)));
		}
		break;
	case ENakamaRequestAuth::None:
	default:
		break;
	}

	if (!BodyString.IsEmpty() && Method != TEXT("GET"))
	{
		Request->SetContentAsString(BodyString);
	}

	Request->SetTimeout(Timeout);

	Request->OnProcessRequestComplete().BindLambda(
		[OnSuccess, OnError, CancellationToken](FHttpRequestPtr Req, FHttpResponsePtr Res, bool bSuccess)
		{
			if (CancellationToken->load())
			{
				if (OnError)
				{
					OnError(FNakamaError(TEXT("Request cancelled"), -1));
				}
				return;
			}

			if (!bSuccess || !Res.IsValid())
			{
				if (OnError)
				{
					OnError(FNakamaError(TEXT("Connection failed"), 0));
				}
				return;
			}

			const int32 Code = Res->GetResponseCode();
			const FString Content = Res->GetContentAsString();

			if (Code < 200 || Code >= 300)
			{
				FString ErrorMsg = FString::Printf(TEXT("HTTP %d"), Code);
				int32 ErrorCode = Code;
				TSharedPtr<FJsonObject> Json;
				if (FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Content), Json) && Json.IsValid())
				{
					if (Json->HasField(TEXT("message")))
					{
						ErrorMsg = Json->GetStringField(TEXT("message"));
					}
					if (Json->HasField(TEXT("code")))
					{
						ErrorCode = static_cast<int32>(Json->GetNumberField(TEXT("code")));
					}
				}
				if (OnError)
				{
					OnError(FNakamaError(ErrorMsg, ErrorCode));
				}
				return;
			}

			TSharedPtr<FJsonObject> Json;
			if (!Content.IsEmpty())
			{
				if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Content), Json) || !Json.IsValid())
				{
					if (OnError)
					{
						OnError(FNakamaError(TEXT("Invalid JSON response"), 500));
					}
					return;
				}
			}

			if (OnSuccess)
			{
				OnSuccess(Json);
			}
		});

	Request->ProcessRequest();
}

inline void SendRequest(
	const FNakamaClientConfig& Config,
	const FString& Endpoint,
	const FString& Method,
	const FString& BodyString,
	ENakamaRequestAuth AuthType,
	const FString& BearerToken,
	TFunction<void(TSharedPtr<FJsonObject>)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	if (CancellationToken->load())
	{
		if (OnError)
		{
			OnError(FNakamaError(TEXT("Request cancelled"), -1));
		}
		return;
	}

	DoHttpRequest(Config, Endpoint, Method, BodyString, AuthType, BearerToken, OnSuccess, OnError, Timeout, CancellationToken);
}

inline void MakeRequest(
	const FNakamaClientConfig& Config,
	const FString& Endpoint,
	const FString& Method,
	const TSharedPtr<FJsonObject>& Body,
	ENakamaRequestAuth AuthType,
	const FString& BearerToken,
	TFunction<void(TSharedPtr<FJsonObject>)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError,
	float Timeout,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	FString BodyString;
	if (Body.IsValid() && Method != TEXT("GET"))
	{
		BodyString = SerializeJsonToString(Body);
	}
	SendRequest(Config, Endpoint, Method, BodyString, AuthType, BearerToken, OnSuccess, OnError, Timeout, CancellationToken);
}

} // namespace NakamaHttpInternal
