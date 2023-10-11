// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "NakamaClient.h"
#include "Templates/SharedPointer.h"
#include "NakamaLogger.h"
#include "NakamaLoggingMacros.h"

class FNakamaUtils
{
	
public:
	
	// Handle Request Methods for REST API
	static FString ENakamaRequesMethodToFString(ENakamaRequestMethod Verb)
	{
		switch (Verb)
		{
		case ENakamaRequestMethod::GET:
			return TEXT("GET");
		case ENakamaRequestMethod::POST:
			return TEXT("POST");
		case ENakamaRequestMethod::PUT:
			return TEXT("PUT");
		case ENakamaRequestMethod::DEL:
			return TEXT("DELETE");
		default:
			// Handle unrecognized verb if needed
			break;
		}

		// Return an empty string for unrecognized verbs
		return FString();
	}

	// Bool to String Helper
	static FString BoolToString(bool Value)
	{
		return Value ? TEXT("true") : TEXT("false");
	}

	// Build Query String
	static FString BuildQueryString(const TMultiMap<FString, FString>& QueryParams)
	{
		FString QueryString;

		for (const auto& Param : QueryParams)
		{
			if (!QueryString.IsEmpty())
			{
				QueryString += "&";
			}

			// Only specific inputs needs to be encoded
			//FString EncodedKey = FGenericPlatformHttp::UrlEncode(Param.Key);
			//FString EncodedValue = FGenericPlatformHttp::UrlEncode(Param.Value);

			QueryString += Param.Key + "=" + Param.Value;
		}

		return QueryString;
	}

	// Extra client checks for lambdas in requests
	static bool IsClientActive(const UNakamaClient *Client)
	{
		return IsValid(Client) && Client->bIsActive == true;
	}

	// Extra client checks for lambdas in requests
	static bool IsRealtimeClientActive(const UNakamaRealtimeClient *RealtimeClient)
	{
		return IsValid(RealtimeClient) && RealtimeClient->bIsActive == true;
	}

	// Json helpers
	static FString EncodeJson(TSharedPtr<FJsonObject> JsonObject)
	{
		FString OutputString;
		const TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
		FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
		return OutputString;
	}

	// Enum as integer string
	template<typename TEnum>
	static FString GetEnumValueAsIntString(TEnum EnumValue)
	{
		const int32 IntValue = static_cast<int32>(EnumValue);
		return FString::FromInt(IntValue);
	}

	// Error handling
	static FNakamaError HandleInvalidClient()
	{
		FNakamaError Error;
		Error.Message = FString(TEXT("Client Missing"));
		Error.Code = ENakamaErrorCode::InvalidArgument;
		
		NAKAMA_LOG_ERROR(Error.Message);
		
		return Error;
	}

	static FNakamaError HandleInvalidSession()
	{
		FNakamaError Error;
		Error.Message = FString(TEXT("Session Missing"));
		Error.Code = ENakamaErrorCode::InvalidArgument;
		
		NAKAMA_LOG_ERROR(Error.Message);
		
		return Error;
	}

	static FNakamaError HandleInvalidClientAndSession()
	{
		FNakamaError Error;
		Error.Message = FString(TEXT("Client and Session Missing"));
		Error.Code = ENakamaErrorCode::InvalidArgument;
		
		NAKAMA_LOG_ERROR(Error.Message);
		
		return Error;
	}

	static FNakamaRtError HandleInvalidRealtimeClient()
	{
		FNakamaRtError Error;
		Error.Message = FString(TEXT("Realtime Client Missing"));
		Error.Code = ENakamaRtErrorCode::UNKNOWN; // Do bad input?

		NAKAMA_LOG_ERROR(Error.Message);

		return Error;
	}

	// Base64 Encode/Decode
	static FString Base64Encode(const FString& Source)
	{
		TArray<uint8> ByteArray;
		FTCHARToUTF8 StringSrc = FTCHARToUTF8(Source.GetCharArray().GetData());
		ByteArray.Append((uint8*)StringSrc.Get(), StringSrc.Length());

		return FBase64::Encode(ByteArray);
	}
	
	static bool Base64Decode(const FString& Source, FString& Dest)
	{
		TArray<uint8> ByteArray;
		bool Success = FBase64::Decode(Source, ByteArray);

		FUTF8ToTCHAR StringSrc = FUTF8ToTCHAR((const ANSICHAR*)ByteArray.GetData(), ByteArray.Num());
		Dest.AppendChars(StringSrc.Get(), StringSrc.Length());

		return Success;
	}

	// Working with Optionals (mainly from Blueprints)

	template <typename T>
	static TOptional<T> CreateOptional(const T& value, const T& defaultValue)
	{
		return value != defaultValue ? TOptional<T>(value) : TOptional<T>();
	}

	// Conversion

	static TMap<FString, double> ConvertFloatMapToDouble(const TMap<FString, float>& FloatMap)
	{
		TMap<FString, double> DoubleMap;
		for (const auto& Pair : FloatMap)
		{
			DoubleMap.Add(Pair.Key, static_cast<double>(Pair.Value));
		}
		return DoubleMap;
	}
	
};
