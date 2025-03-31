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


void USatoriSession::SetupSession(const FString& AuthResponse)
{
    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
    const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(AuthResponse);

    if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
    {
        FString Token = JsonObject->GetStringField(TEXT("token"));
        FString RefreshToken = JsonObject->GetStringField(TEXT("refresh_token"));

    	SessionData.AuthToken = Token;
    	_AuthToken = Token;
    	SessionData.RefreshToken = RefreshToken;
    	_RefreshToken = RefreshToken;

		const TSharedPtr<FJsonObject>* PropertiesJson = nullptr;
    	if (JsonObject->TryGetObjectField(TEXT("properties"), PropertiesJson))
    	{
			FSatoriProperties Properties = FSatoriProperties(*PropertiesJson);
			SessionData.Properties = Properties;
    		_Properties = Properties;
    	}
    }
    else
    {
    	SATORI_LOG_ERROR(TEXT("Failed to deserialize Satori Session JSON object"));
    }
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

USatoriSession* USatoriSession::RestoreSession(FString Token, FString RefreshToken)
{
	USatoriSession* ResultSession = NewObject<USatoriSession>();
	ResultSession->SessionData.AuthToken = Token;
	ResultSession->_AuthToken = Token;
	ResultSession->SessionData.RefreshToken = RefreshToken;
	ResultSession->_RefreshToken = RefreshToken;
	return ResultSession;
}
