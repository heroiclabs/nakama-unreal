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

#include "NakamaSession.h"

bool FNakamaSession::ParseJwtPayload(const FString& Jwt, TSharedPtr<FJsonObject>& Out) noexcept
{
	TArray<FString> Parts;
	Jwt.ParseIntoArray(Parts, TEXT("."));
	if (Parts.Num() < 2)
	{
		return false;
	}

	// Base64url -> standard Base64
	FString Payload = Parts[1];
	Payload.ReplaceInline(TEXT("-"), TEXT("+"));
	Payload.ReplaceInline(TEXT("_"), TEXT("/"));

	// Pad to multiple of 4
	while (Payload.Len() % 4 != 0)
	{
		Payload += TEXT("=");
	}

	TArray<uint8> DecodedBytes;
	if (!FBase64::Decode(Payload, DecodedBytes))
	{
		return false;
	}

	const FUTF8ToTCHAR Converter(reinterpret_cast<const ANSICHAR*>(DecodedBytes.GetData()), DecodedBytes.Num());
	FString JsonString(Converter.Length(), Converter.Get());

	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
	return FJsonSerializer::Deserialize(Reader, Out) && Out.IsValid();
}

void FNakamaSession::ParseTokens() noexcept
{
	UserId.Empty();
	Username.Empty();
	TokenExpiresAt = 0;
	TokenIssuedAt = 0;
	RefreshTokenExpiresAt = 0;
	Vars.Empty();

	// Parse auth token
	TSharedPtr<FJsonObject> TokenPayload;
	if (!Token.IsEmpty() && ParseJwtPayload(Token, TokenPayload))
	{
		if (TokenPayload->HasField(TEXT("uid")))
		{
			UserId = TokenPayload->GetStringField(TEXT("uid"));
		}
		if (TokenPayload->HasField(TEXT("usn")))
		{
			Username = TokenPayload->GetStringField(TEXT("usn"));
		}
		if (TokenPayload->HasField(TEXT("exp")))
		{
			TokenExpiresAt = static_cast<int64>(TokenPayload->GetNumberField(TEXT("exp")));
		}
		if (TokenPayload->HasField(TEXT("iat")))
		{
			TokenIssuedAt = static_cast<int64>(TokenPayload->GetNumberField(TEXT("iat")));
		}
		if (TokenPayload->HasField(TEXT("vrs")))
		{
			const TSharedPtr<FJsonObject>* VrsObj;
			if (TokenPayload->TryGetObjectField(TEXT("vrs"), VrsObj))
			{
				for (const auto& Pair : (*VrsObj)->Values)
				{
					Vars.Add(Pair.Key, Pair.Value->AsString());
				}
			}
		}
	}

	// Parse refresh token
	TSharedPtr<FJsonObject> RefreshPayload;
	if (!RefreshToken.IsEmpty() && ParseJwtPayload(RefreshToken, RefreshPayload))
	{
		if (RefreshPayload->HasField(TEXT("exp")))
		{
			RefreshTokenExpiresAt = static_cast<int64>(RefreshPayload->GetNumberField(TEXT("exp")));
		}
	}
}

bool FNakamaSession::IsExpired(int64 BufferSeconds) const noexcept
{
	if (TokenExpiresAt == 0)
	{
		return true;
	}
	return (TokenExpiresAt - BufferSeconds) <= FDateTime::UtcNow().ToUnixTimestamp();
}

bool FNakamaSession::IsRefreshExpired(int64 BufferSeconds) const noexcept
{
	if (RefreshTokenExpiresAt == 0)
	{
		return true;
	}
	return (RefreshTokenExpiresAt - BufferSeconds) <= FDateTime::UtcNow().ToUnixTimestamp();
}

void FNakamaSession::Update(const FString& NewToken, const FString& NewRefreshToken) noexcept
{
	Token = NewToken;
	RefreshToken = NewRefreshToken;
	ParseTokens();
}

FNakamaSession FNakamaSession::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
	FNakamaSession Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("created")))
	{
		Result.Created = Json->GetBoolField(TEXT("created"));
	}
	if (Json->HasField(TEXT("token")))
	{
		Result.Token = Json->GetStringField(TEXT("token"));
	}
	if (Json->HasField(TEXT("refresh_token")))
	{
		Result.RefreshToken = Json->GetStringField(TEXT("refresh_token"));
	}
	Result.ParseTokens();
	return Result;
}

TSharedPtr<FJsonObject> FNakamaSession::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetBoolField(TEXT("created"), Created);
	if (!Token.IsEmpty())
	{
		Json->SetStringField(TEXT("token"), Token);
	}
	if (!RefreshToken.IsEmpty())
	{
		Json->SetStringField(TEXT("refresh_token"), RefreshToken);
	}
	return Json;
}
