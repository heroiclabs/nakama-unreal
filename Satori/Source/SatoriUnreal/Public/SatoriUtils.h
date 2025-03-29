// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "SatoriClient.h"
#include "Templates/SharedPointer.h"
#include "SatoriLogger.h"
#include "SatoriLoggingMacros.h"

class SATORIUNREAL_API FSatoriUtils
{
public:
	// Handle Request Methods for REST API
	static FString ESatoriRequesMethodToFString(ESatoriRequestMethod Verb)
	{
		switch (Verb)
		{
		case ESatoriRequestMethod::GET:
			return TEXT("GET");
		case ESatoriRequestMethod::POST:
			return TEXT("POST");
		case ESatoriRequestMethod::PUT:
			return TEXT("PUT");
		case ESatoriRequestMethod::DEL:
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
	static bool IsClientActive(const USatoriClient *Client)
	{
		return IsValid(Client) && Client->bIsActive == true;
	}

	// Json helpers
	static FString EncodeJson(TSharedPtr<FJsonObject> JsonObject)
	{
		FString OutputString;
		const TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
		FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
		return OutputString;
	}

	static bool SerializeJsonObject(const TSharedPtr<FJsonObject>& JsonObject, FString& OutSerializedJson)
	{
		if (!JsonObject.IsValid())
		{
			return false;
		}

		const TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&OutSerializedJson);
		if (!FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter))
		{
			JsonWriter->Close();
			return false;
		}

		JsonWriter->Close();

		return true;
	}

	static TSharedPtr<FJsonObject> DeserializeJsonObject(const FString& JsonString) {
		TSharedPtr<FJsonObject> JsonObject;
		const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);
		if (!FJsonSerializer::Deserialize(JsonReader, JsonObject))
		{
			JsonObject = nullptr;
		}
		return JsonObject;
	}

	static void AddVarsToJson(const TSharedPtr<FJsonObject>& JsonObject, const TMap<FString, FString>& Vars, const FString varsFieldName = TEXT("vars"), const bool addAlways = false) {

		if (addAlways || Vars.Num() > 0)
		{
			const TSharedPtr<FJsonObject> VarsJson = MakeShared<FJsonObject>();
			for (const auto& Var : Vars)
			{
				if (!Var.Key.IsEmpty() && !Var.Value.IsEmpty())
				{
					VarsJson->SetStringField(Var.Key, Var.Value);
				}
				else
				{
					SATORI_LOG_WARN(TEXT("AddVarsToJson: Empty key or value detected."));
				}
			}
			JsonObject->SetObjectField(varsFieldName, VarsJson);
		}
	}

	// Enum as integer string
	template<typename TEnum>
	static FString GetEnumValueAsIntString(TEnum EnumValue)
	{
		const int32 IntValue = static_cast<int32>(EnumValue);
		return FString::FromInt(IntValue);
	}

	// Error handling
	static FSatoriError HandleInvalidClient()
	{
		FSatoriError Error;
		Error.Message = FString(TEXT("Client Missing"));
		Error.Code = ESatoriErrorCode::InvalidArgument;
		
		SATORI_LOG_ERROR(Error.Message);
		
		return Error;
	}

	static FSatoriError HandleInvalidSession()
	{
		FSatoriError Error;
		Error.Message = FString(TEXT("Session Missing"));
		Error.Code = ESatoriErrorCode::InvalidArgument;
		
		SATORI_LOG_ERROR(Error.Message);
		
		return Error;
	}

	static FSatoriError HandleInvalidClientAndSession()
	{
		FSatoriError Error;
		Error.Message = FString(TEXT("Client and Session Missing"));
		Error.Code = ESatoriErrorCode::InvalidArgument;
		
		SATORI_LOG_ERROR(Error.Message);
		
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

	// Common functions used by multiple clients
	static void ProcessRequestComplete(FHttpRequestPtr Request, const FHttpResponsePtr& Response, bool bSuccess, const TFunction<void(const FString&)>& SuccessCallback, const TFunction<void(const FSatoriError& Error)>& ErrorCallback);
	
	static void HandleJsonSerializationFailure(TFunction<void(const FSatoriError& Error)> ErrorCallback);
	static bool IsSessionValid(const USatoriSession* Session, TFunction<void(const FSatoriError& Error)> ErrorCallback);
	static bool IsResponseSuccessful(int32 ResponseCode);
	static FSatoriError CreateRequestFailureError();

	// Make HTTP request
	static TSharedRef<IHttpRequest, ESPMode::ThreadSafe> MakeRequest(
		const FString& URL,
		const FString& Content,
		ESatoriRequestMethod RequestMethod,
		const FString& SessionToken,
		float Timeout
	);

	static void SetBasicAuthorizationHeader(TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest, const FString& ServerKey)
	{
		FString AuthToken = FString::Printf(TEXT("%s:"), *ServerKey);
		FTCHARToUTF8 Utf8Token = FTCHARToUTF8(*AuthToken);
		FString EncodedAuthToken = FBase64::Encode((const uint8*)Utf8Token.Get(), Utf8Token.Length());
		FString AuthorizationHeader = FString::Printf(TEXT("Basic %s"), *EncodedAuthToken);

		//SATORI_LOG_DEBUG(FString::Printf( TEXT("Authorization Header: %s"), *AuthorizationHeader ));

		HttpRequest->SetHeader(TEXT("Authorization"), AuthorizationHeader);
	}
};
