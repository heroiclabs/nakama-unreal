// Fill out your copyright notice in the Description page of Project Settings.


#include "NakamaSession.h"

#include "NakamaUtils.h"


void UNakamaSession::SetupSession(const FString& AuthResponse)
{
    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
    const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(AuthResponse);

    if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
    {
        FString Token = JsonObject->GetStringField("token");
        FString RefreshToken = JsonObject->GetStringField("refresh_token");
    	
    	SessionData.AuthToken = Token;
    	_AuthToken = Token;
    	SessionData.RefreshToken = RefreshToken;
    	_RefreshToken = RefreshToken;

    	// Check if the "created" field is available and set IsCreated accordingly
    	bool IsSessionCreated;
    	if (JsonObject->TryGetBoolField("created", IsSessionCreated))
    	{
    		SessionData.IsCreated = IsSessionCreated;
    		_IsCreated = IsSessionCreated;
    	}

        TSharedPtr<FJsonObject> PayloadJson;
        if (ParseJwtPayload(Token, PayloadJson))
        {
            FString UserId;
            FString Username;
            PayloadJson->TryGetStringField("uid", UserId);
            PayloadJson->TryGetStringField("usn", Username);
        	
            SessionData.Username = Username;
        	_Username = Username;
            SessionData.UserId = UserId;
        	_UserId = UserId;

            TMap<FString, FString> InVars;
            if (PayloadJson->HasField("vrs"))
            {
                const TSharedPtr<FJsonObject>& VarsJson = PayloadJson->GetObjectField("vrs");
                for (const auto& Entry : VarsJson->Values)
                {
                    FString Key = Entry.Key;
                    FString Value = Entry.Value->AsString();
                    SessionData.Variables.Add(Key, Value);
                	_Variables.Add(Key, Value);
                }
            }

            int64 Expires;
            if (PayloadJson->TryGetNumberField("exp", Expires))
            {
                FDateTime ExpireTime = FDateTime::FromUnixTimestamp(Expires);
                SessionData.ExpireTime = ExpireTime;
            	_ExpireTime = ExpireTime;
                SessionData.IsExpired = (FDateTime::UtcNow() >= ExpireTime);
            	_IsExpired = (FDateTime::UtcNow() >= ExpireTime);
            }

            // Parse and check expiration time of the refresh_token
            TSharedPtr<FJsonObject> RefreshPayloadJson;
            if (ParseJwtPayload(RefreshToken, RefreshPayloadJson))
            {
                int64 RefreshExpires;
                if (RefreshPayloadJson->TryGetNumberField("exp", RefreshExpires))
                {
                    FDateTime RefreshExpireTime = FDateTime::FromUnixTimestamp(RefreshExpires);
                    SessionData.RefreshExpireTime = RefreshExpireTime;
                	_RefreshExpireTime = RefreshExpireTime;
                    SessionData.IsRefreshExpired = (FDateTime::UtcNow() >= RefreshExpireTime);
                	_IsRefreshExpired = (FDateTime::UtcNow() >= RefreshExpireTime);
                }
            }
        	
            SessionData.CreateTime = FDateTime::UtcNow();
        	_CreateTime = FDateTime::UtcNow();
        }
        else
        {
        	NAKAMA_LOG_ERROR(TEXT("Failed to parse JWT payload"));
        }
    }
    else
    {
    	NAKAMA_LOG_ERROR(TEXT("Failed to deserialize Session JSON object"));
    }
}

const FString UNakamaSession::GetAuthToken()
{
	return _AuthToken;
}

const FString UNakamaSession::GetRefreshToken()
{
	return _RefreshToken;
}

bool UNakamaSession::IsCreated()
{
	return _IsCreated;
}

const FString UNakamaSession::GetUsername()
{
	return _Username;
}

const FString UNakamaSession::GetUserId()
{
	return _UserId;
}

const FDateTime UNakamaSession::GetCreateTime()
{
	return _CreateTime;
}

const FDateTime UNakamaSession::GetExpireTime()
{
	return _ExpireTime;
}

bool UNakamaSession::IsExpired() const
{
	return FDateTime::UtcNow() >= _ExpireTime;
}

bool UNakamaSession::IsExpiredTime(FDateTime Time) const
{
	return Time >= _ExpireTime;
}

bool UNakamaSession::IsRefreshExpired() const
{
	return FDateTime::UtcNow() >= _RefreshExpireTime;
}

bool UNakamaSession::IsRefreshExpiredTime(FDateTime Time) const
{
	return Time >= _RefreshExpireTime;
}

TMap<FString, FString> UNakamaSession::GetVariables()
{
	return _Variables;
}

FString UNakamaSession::GetVariable(FString Name)
{
	FString *Value = _Variables.Find(Name);
	return *Value;
}

UNakamaSession* UNakamaSession::RestoreSession(FString Token, FString RefreshToken)
{
	// Setup the request content
	const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
	ContentJson->SetStringField(TEXT("token"), Token);
	ContentJson->SetStringField(TEXT("refresh_token"), RefreshToken);
	ContentJson->SetBoolField(TEXT("created"), false);

	// Convert the JSON object to a JSON string
	FString JsonString;
	TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&JsonString);
	bool bSerializationSuccessful = FJsonSerializer::Serialize(ContentJson.ToSharedRef(), JsonWriter);

	// Check if serialization was successful
	if (bSerializationSuccessful)
	{
		UNakamaSession* ResultSession = NewObject<UNakamaSession>();
		ResultSession->SetupSession(JsonString);
		return ResultSession;
	}
	else
	{
		NAKAMA_LOG_ERROR("Restore Session: Failed to serialize Restore Session JSON object");
		return nullptr;
	}
}

bool UNakamaSession::ParseJwtPayload(const FString& jwt, TSharedPtr<FJsonObject>& payloadJson)
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

