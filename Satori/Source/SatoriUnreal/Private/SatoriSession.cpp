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

#include "SatoriSession.h"

#include "SatoriUtils.h"
#include "Misc/Base64.h"


USatoriSession* USatoriSession::SetupSession(const FString& AuthResponse)
{
	USatoriSession* ResultSession = NewObject<USatoriSession>();
    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
    const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(AuthResponse);

    if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
    {
        FString Token = JsonObject->GetStringField(TEXT("token"));
        FString RefreshToken = JsonObject->GetStringField(TEXT("refresh_token"));

		ResultSession->SessionData.AuthToken = Token;
		ResultSession->_AuthToken = Token;
		ResultSession->SessionData.RefreshToken = RefreshToken;
		ResultSession->_RefreshToken = RefreshToken;

		const TSharedPtr<FJsonObject>* PropertiesJson = nullptr;
    	if (JsonObject->TryGetObjectField(TEXT("properties"), PropertiesJson))
    	{
			FSatoriProperties Properties = FSatoriProperties(*PropertiesJson);
			ResultSession->SessionData.Properties = Properties;
			ResultSession->_Properties = Properties;
    	}

		// Parse the expiration time from the auth token JWT payload.
		TSharedPtr<FJsonObject> PayloadJson;
		if (ParseJwtPayload(Token, PayloadJson))
		{
			int64 Expires;
			if (PayloadJson->TryGetNumberField(TEXT("exp"), Expires))
			{
				ResultSession->_ExpireTime = FDateTime::FromUnixTimestamp(Expires);
			}
		}

		// Parse the expiration time from the refresh token JWT payload.
		TSharedPtr<FJsonObject> RefreshPayloadJson;
		if (ParseJwtPayload(RefreshToken, RefreshPayloadJson))
		{
			int64 RefreshExpires;
			if (RefreshPayloadJson->TryGetNumberField(TEXT("exp"), RefreshExpires))
			{
				ResultSession->_RefreshExpireTime = FDateTime::FromUnixTimestamp(RefreshExpires);
			}
		}

		return ResultSession;
    }
    else
    {
    	SATORI_LOG_ERROR(TEXT("Failed to deserialize Satori Session JSON object"));
    }
	return nullptr;
}

const FString USatoriSession::GetAuthToken()  const
{
	return _AuthToken;
}

const FString USatoriSession::GetRefreshToken() const
{
	return _RefreshToken;
}

const FSatoriProperties USatoriSession::GetProperties() const
{
	return _Properties;
}

const FDateTime USatoriSession::GetExpireTime() const
{
	return _ExpireTime;
}

const FDateTime USatoriSession::GetRefreshExpireTime() const
{
	return _RefreshExpireTime;
}

bool USatoriSession::IsExpired() const
{
	return FDateTime::UtcNow() >= _ExpireTime;
}

bool USatoriSession::IsExpiredTime(FDateTime Time) const
{
	return Time >= _ExpireTime;
}

bool USatoriSession::IsRefreshExpired() const
{
	return FDateTime::UtcNow() >= _RefreshExpireTime;
}

bool USatoriSession::IsRefreshExpiredTime(FDateTime Time) const
{
	return Time >= _RefreshExpireTime;
}

void USatoriSession::Update(const USatoriSession* Other)
{
	if (!Other)
	{
		return;
	}

	SessionData = Other->SessionData;

	_AuthToken         = Other->_AuthToken;
	_RefreshToken      = Other->_RefreshToken;
	_Properties        = Other->_Properties;
	_ExpireTime        = Other->_ExpireTime;
	_RefreshExpireTime = Other->_RefreshExpireTime;
}

USatoriSession* USatoriSession::RestoreSession(FString Token, FString RefreshToken)
{
	USatoriSession* ResultSession = NewObject<USatoriSession>();
	ResultSession->SessionData.AuthToken = Token;
	ResultSession->_AuthToken = Token;
	ResultSession->SessionData.RefreshToken = RefreshToken;
	ResultSession->_RefreshToken = RefreshToken;

	// Parse expiration times from the token JWT payloads.
	TSharedPtr<FJsonObject> PayloadJson;
	if (ParseJwtPayload(Token, PayloadJson))
	{
		int64 Expires;
		if (PayloadJson->TryGetNumberField(TEXT("exp"), Expires))
		{
			ResultSession->_ExpireTime = FDateTime::FromUnixTimestamp(Expires);
		}
	}

	TSharedPtr<FJsonObject> RefreshPayloadJson;
	if (ParseJwtPayload(RefreshToken, RefreshPayloadJson))
	{
		int64 RefreshExpires;
		if (RefreshPayloadJson->TryGetNumberField(TEXT("exp"), RefreshExpires))
		{
			ResultSession->_RefreshExpireTime = FDateTime::FromUnixTimestamp(RefreshExpires);
		}
	}

	return ResultSession;
}

bool USatoriSession::ParseJwtPayload(const FString& jwt, TSharedPtr<FJsonObject>& payloadJson)
{
	// Split the JWT into its three parts
	TArray<FString> jwtParts;
	jwt.ParseIntoArray(jwtParts, TEXT("."));

	if (jwtParts.Num() != 3)
	{
		// Invalid JWT format
		return false;
	}

	// Convert Base64Url to Base64
	FString payloadString = jwtParts[1];
	payloadString.ReplaceInline(TEXT("-"), TEXT("+"));
	payloadString.ReplaceInline(TEXT("_"), TEXT("/"));

	// Handle padding
	int32 mod = payloadString.Len() % 4;
	if (mod != 0) {
		for (int32 i = 0; i < (4 - mod); ++i) {
			payloadString += TEXT("=");
		}
	}

	// Decode to bytes
	TArray<uint8> decodedBytes;
	FBase64::Decode(payloadString, decodedBytes);

	// Ensure null termination
	decodedBytes.Add(0);

	// Convert UTF-8 bytes to FString to handle special characters
	FString decodedPayloadString = FString(UTF8_TO_TCHAR(reinterpret_cast<const ANSICHAR*>(decodedBytes.GetData())));

	// Parse the decoded payload as a JSON object
	TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(decodedPayloadString);
	if (!FJsonSerializer::Deserialize(reader, payloadJson))
	{
		// Failed to parse JSON
		return false;
	}

	return true;
}
