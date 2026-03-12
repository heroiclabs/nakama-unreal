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

/* This code is auto-generated. DO NOT EDIT. */

#include "SatoriApi.h"
#include "NakamaHttpHelper.h"

#include "Modules/ModuleManager.h"

DEFINE_LOG_CATEGORY(LogSatori);

using namespace NakamaHttpInternal;

// Adapts FNakamaError -> FSatoriError for use with Satori RPC OnError callbacks.
namespace
{
	inline TFunction<void(const FNakamaError&)> MakeSatoriErrorAdapter(TFunction<void(const FSatoriError&)> OnError)
	{
		return [OnError = MoveTemp(OnError)](const FNakamaError& E)
		{
			if (OnError)
			{
				OnError(FSatoriError{E.Message, E.Code});
			}
		};
	}

	inline FNakamaClientConfig ToNakamaConfig(const FSatoriClientConfig& Cfg)
	{
		FNakamaClientConfig Out;
		Out.ServerKey = Cfg.ServerKey;
		Out.Host = Cfg.Host;
		Out.Port = Cfg.Port;
		Out.bUseSSL = Cfg.bUseSSL;
		return Out;
	}
} // anonymous namespace

// --- FSatoriSession JWT helpers ---

bool FSatoriSession::ParseJwtPayload(const FString& Jwt, TSharedPtr<FJsonObject>& Out) noexcept
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

void FSatoriSession::ParseTokens() noexcept
{
	IdentityId.Empty();
	TokenExpiresAt = 0;
	TokenIssuedAt = 0;
	RefreshTokenExpiresAt = 0;

	// Parse auth token
	TSharedPtr<FJsonObject> TokenPayload;
	if (!Token.IsEmpty() && ParseJwtPayload(Token, TokenPayload))
	{
		if (TokenPayload->HasField(TEXT("iid")))
		{
			IdentityId = TokenPayload->GetStringField(TEXT("iid"));
		}
		if (TokenPayload->HasField(TEXT("exp")))
		{
			TokenExpiresAt = static_cast<int64>(TokenPayload->GetNumberField(TEXT("exp")));
		}
		if (TokenPayload->HasField(TEXT("iat")))
		{
			TokenIssuedAt = static_cast<int64>(TokenPayload->GetNumberField(TEXT("iat")));
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

bool FSatoriSession::IsExpired(int64 BufferSeconds) const noexcept
{
	if (TokenExpiresAt == 0)
	{
		return true;
	}
	return (TokenExpiresAt - BufferSeconds) <= FDateTime::UtcNow().ToUnixTimestamp();
}

bool FSatoriSession::IsRefreshExpired(int64 BufferSeconds) const noexcept
{
	if (RefreshTokenExpiresAt == 0)
	{
		return true;
	}
	return (RefreshTokenExpiresAt - BufferSeconds) <= FDateTime::UtcNow().ToUnixTimestamp();
}

void FSatoriSession::Update(const FString& NewToken, const FString& NewRefreshToken) noexcept
{
	Token = NewToken;
	RefreshToken = NewRefreshToken;
	ParseTokens();
}

FSatoriAuthenticateLogoutRequest FSatoriAuthenticateLogoutRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
	FSatoriAuthenticateLogoutRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("token")))
	{
		Result.Token = Json->GetStringField(TEXT("token"));
	}
	if (Json->HasField(TEXT("refresh_token")))
	{
		Result.RefreshToken = Json->GetStringField(TEXT("refresh_token"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FSatoriAuthenticateLogoutRequest::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
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

FSatoriAuthenticateRefreshRequest FSatoriAuthenticateRefreshRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
	FSatoriAuthenticateRefreshRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("refresh_token")))
	{
		Result.RefreshToken = Json->GetStringField(TEXT("refresh_token"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FSatoriAuthenticateRefreshRequest::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!RefreshToken.IsEmpty())
	{
		Json->SetStringField(TEXT("refresh_token"), RefreshToken);
	}
	return Json;
}

FSatoriAuthenticateRequest FSatoriAuthenticateRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
	FSatoriAuthenticateRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("id")))
	{
		Result.Id = Json->GetStringField(TEXT("id"));
	}
	if (Json->HasField(TEXT("no_session")))
	{
		Result.NoSession = Json->GetBoolField(TEXT("no_session"));
	}
	if (Json->HasField(TEXT("default")))
	{
		const TSharedPtr<FJsonObject>* MapObj;
		if (Json->TryGetObjectField(TEXT("default"), MapObj))
		{
			for (const auto& Pair : (*MapObj)->Values)
			{
				Result.Default.Add(Pair.Key, Pair.Value->AsString());
			}
		}
	}
	if (Json->HasField(TEXT("custom")))
	{
		const TSharedPtr<FJsonObject>* MapObj;
		if (Json->TryGetObjectField(TEXT("custom"), MapObj))
		{
			for (const auto& Pair : (*MapObj)->Values)
			{
				Result.Custom.Add(Pair.Key, Pair.Value->AsString());
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FSatoriAuthenticateRequest::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Id.IsEmpty())
	{
		Json->SetStringField(TEXT("id"), Id);
	}
	Json->SetBoolField(TEXT("no_session"), NoSession);
	if (Default.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Default)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Json->SetObjectField(TEXT("default"), MapObj);
	}
	if (Custom.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Custom)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Json->SetObjectField(TEXT("custom"), MapObj);
	}
	return Json;
}

FSatoriDeleteMessageRequest FSatoriDeleteMessageRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
	FSatoriDeleteMessageRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("id")))
	{
		Result.Id = Json->GetStringField(TEXT("id"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FSatoriDeleteMessageRequest::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Id.IsEmpty())
	{
		Json->SetStringField(TEXT("id"), Id);
	}
	return Json;
}

FSatoriEvent FSatoriEvent::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
	FSatoriEvent Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("name")))
	{
		Result.Name = Json->GetStringField(TEXT("name"));
	}
	if (Json->HasField(TEXT("id")))
	{
		Result.Id = Json->GetStringField(TEXT("id"));
	}
	if (Json->HasField(TEXT("value")))
	{
		Result.Value = Json->GetStringField(TEXT("value"));
	}
	if (Json->HasField(TEXT("timestamp")))
	{
		Result.Timestamp = Json->GetStringField(TEXT("timestamp"));
	}
	if (Json->HasField(TEXT("identity_id")))
	{
		Result.IdentityId = Json->GetStringField(TEXT("identity_id"));
	}
	if (Json->HasField(TEXT("session_id")))
	{
		Result.SessionId = Json->GetStringField(TEXT("session_id"));
	}
	if (Json->HasField(TEXT("session_issued_at")))
	{
		Result.SessionIssuedAt = static_cast<int64>(Json->GetNumberField(TEXT("session_issued_at")));
	}
	if (Json->HasField(TEXT("session_expires_at")))
	{
		Result.SessionExpiresAt = static_cast<int64>(Json->GetNumberField(TEXT("session_expires_at")));
	}
	if (Json->HasField(TEXT("metadata")))
	{
		const TSharedPtr<FJsonObject>* MapObj;
		if (Json->TryGetObjectField(TEXT("metadata"), MapObj))
		{
			for (const auto& Pair : (*MapObj)->Values)
			{
				Result.Metadata.Add(Pair.Key, Pair.Value->AsString());
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FSatoriEvent::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Name.IsEmpty())
	{
		Json->SetStringField(TEXT("name"), Name);
	}
	if (!Id.IsEmpty())
	{
		Json->SetStringField(TEXT("id"), Id);
	}
	if (!Value.IsEmpty())
	{
		Json->SetStringField(TEXT("value"), Value);
	}
	if (!Timestamp.IsEmpty())
	{
		Json->SetStringField(TEXT("timestamp"), Timestamp);
	}
	if (!IdentityId.IsEmpty())
	{
		Json->SetStringField(TEXT("identity_id"), IdentityId);
	}
	if (!SessionId.IsEmpty())
	{
		Json->SetStringField(TEXT("session_id"), SessionId);
	}
	Json->SetNumberField(TEXT("session_issued_at"), SessionIssuedAt);
	Json->SetNumberField(TEXT("session_expires_at"), SessionExpiresAt);
	if (Metadata.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Metadata)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Json->SetObjectField(TEXT("metadata"), MapObj);
	}
	return Json;
}

FSatoriEventRequest FSatoriEventRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
	FSatoriEventRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("events")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("events"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				const TSharedPtr<FJsonObject>* ItemObj = nullptr;
				if (Item->TryGetObject(ItemObj) && ItemObj)
				{
					Result.Events.Add(FSatoriEvent::FromJson(*ItemObj));
				}
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FSatoriEventRequest::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (Events.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Events)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("events"), Array);
	}
	return Json;
}

FSatoriExperiment FSatoriExperiment::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
	FSatoriExperiment Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("name")))
	{
		Result.Name = Json->GetStringField(TEXT("name"));
	}
	if (Json->HasField(TEXT("value")))
	{
		Result.Value = Json->GetStringField(TEXT("value"));
	}
	if (Json->HasField(TEXT("labels")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("labels"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				Result.Labels.Add(Item->AsString());
			}
		}
	}
	if (Json->HasField(TEXT("phase_name")))
	{
		Result.PhaseName = Json->GetStringField(TEXT("phase_name"));
	}
	if (Json->HasField(TEXT("phase_variant_name")))
	{
		Result.PhaseVariantName = Json->GetStringField(TEXT("phase_variant_name"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FSatoriExperiment::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Name.IsEmpty())
	{
		Json->SetStringField(TEXT("name"), Name);
	}
	if (!Value.IsEmpty())
	{
		Json->SetStringField(TEXT("value"), Value);
	}
	if (Labels.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Labels)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Json->SetArrayField(TEXT("labels"), Array);
	}
	if (!PhaseName.IsEmpty())
	{
		Json->SetStringField(TEXT("phase_name"), PhaseName);
	}
	if (!PhaseVariantName.IsEmpty())
	{
		Json->SetStringField(TEXT("phase_variant_name"), PhaseVariantName);
	}
	return Json;
}

FSatoriExperimentList FSatoriExperimentList::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
	FSatoriExperimentList Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("experiments")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("experiments"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				const TSharedPtr<FJsonObject>* ItemObj = nullptr;
				if (Item->TryGetObject(ItemObj) && ItemObj)
				{
					Result.Experiments.Add(FSatoriExperiment::FromJson(*ItemObj));
				}
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FSatoriExperimentList::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (Experiments.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Experiments)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("experiments"), Array);
	}
	return Json;
}

FSatoriValueChangeReason FSatoriValueChangeReason::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
	FSatoriValueChangeReason Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("type")))
	{
		Result.Type = Json->GetIntegerField(TEXT("type"));
	}
	if (Json->HasField(TEXT("name")))
	{
		Result.Name = Json->GetStringField(TEXT("name"));
	}
	if (Json->HasField(TEXT("variant_name")))
	{
		Result.VariantName = Json->GetStringField(TEXT("variant_name"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FSatoriValueChangeReason::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetNumberField(TEXT("type"), Type);
	if (!Name.IsEmpty())
	{
		Json->SetStringField(TEXT("name"), Name);
	}
	if (!VariantName.IsEmpty())
	{
		Json->SetStringField(TEXT("variant_name"), VariantName);
	}
	return Json;
}

FSatoriFlag FSatoriFlag::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
	FSatoriFlag Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("name")))
	{
		Result.Name = Json->GetStringField(TEXT("name"));
	}
	if (Json->HasField(TEXT("value")))
	{
		Result.Value = Json->GetStringField(TEXT("value"));
	}
	if (Json->HasField(TEXT("condition_changed")))
	{
		Result.ConditionChanged = Json->GetBoolField(TEXT("condition_changed"));
	}
	if (Json->HasField(TEXT("change_reason")))
	{
		const TSharedPtr<FJsonObject>* NestedObj;
		if (Json->TryGetObjectField(TEXT("change_reason"), NestedObj))
		{
			Result.ChangeReason = FSatoriValueChangeReason::FromJson(*NestedObj);
		}
	}
	if (Json->HasField(TEXT("labels")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("labels"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				Result.Labels.Add(Item->AsString());
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FSatoriFlag::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Name.IsEmpty())
	{
		Json->SetStringField(TEXT("name"), Name);
	}
	if (!Value.IsEmpty())
	{
		Json->SetStringField(TEXT("value"), Value);
	}
	Json->SetBoolField(TEXT("condition_changed"), ConditionChanged);
	Json->SetObjectField(TEXT("change_reason"), ChangeReason.ToJson());
	if (Labels.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Labels)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Json->SetArrayField(TEXT("labels"), Array);
	}
	return Json;
}

FSatoriFlagList FSatoriFlagList::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
	FSatoriFlagList Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("flags")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("flags"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				const TSharedPtr<FJsonObject>* ItemObj = nullptr;
				if (Item->TryGetObject(ItemObj) && ItemObj)
				{
					Result.Flags.Add(FSatoriFlag::FromJson(*ItemObj));
				}
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FSatoriFlagList::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (Flags.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Flags)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("flags"), Array);
	}
	return Json;
}

FSatoriFlagOverrideValue FSatoriFlagOverrideValue::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
	FSatoriFlagOverrideValue Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("type")))
	{
		Result.Type = Json->GetIntegerField(TEXT("type"));
	}
	if (Json->HasField(TEXT("name")))
	{
		Result.Name = Json->GetStringField(TEXT("name"));
	}
	if (Json->HasField(TEXT("variant_name")))
	{
		Result.VariantName = Json->GetStringField(TEXT("variant_name"));
	}
	if (Json->HasField(TEXT("value")))
	{
		Result.Value = Json->GetStringField(TEXT("value"));
	}
	if (Json->HasField(TEXT("create_time_sec")))
	{
		Result.CreateTimeSec = static_cast<int64>(Json->GetNumberField(TEXT("create_time_sec")));
	}
	return Result;
}

TSharedPtr<FJsonObject> FSatoriFlagOverrideValue::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetNumberField(TEXT("type"), Type);
	if (!Name.IsEmpty())
	{
		Json->SetStringField(TEXT("name"), Name);
	}
	if (!VariantName.IsEmpty())
	{
		Json->SetStringField(TEXT("variant_name"), VariantName);
	}
	if (!Value.IsEmpty())
	{
		Json->SetStringField(TEXT("value"), Value);
	}
	Json->SetNumberField(TEXT("create_time_sec"), CreateTimeSec);
	return Json;
}

FSatoriFlagOverride FSatoriFlagOverride::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
	FSatoriFlagOverride Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("flag_name")))
	{
		Result.FlagName = Json->GetStringField(TEXT("flag_name"));
	}
	if (Json->HasField(TEXT("overrides")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("overrides"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				const TSharedPtr<FJsonObject>* ItemObj = nullptr;
				if (Item->TryGetObject(ItemObj) && ItemObj)
				{
					Result.Overrides.Add(FSatoriFlagOverrideValue::FromJson(*ItemObj));
				}
			}
		}
	}
	if (Json->HasField(TEXT("labels")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("labels"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				Result.Labels.Add(Item->AsString());
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FSatoriFlagOverride::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!FlagName.IsEmpty())
	{
		Json->SetStringField(TEXT("flag_name"), FlagName);
	}
	if (Overrides.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Overrides)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("overrides"), Array);
	}
	if (Labels.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Labels)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Json->SetArrayField(TEXT("labels"), Array);
	}
	return Json;
}

FSatoriFlagOverrideList FSatoriFlagOverrideList::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
	FSatoriFlagOverrideList Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("flags")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("flags"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				const TSharedPtr<FJsonObject>* ItemObj = nullptr;
				if (Item->TryGetObject(ItemObj) && ItemObj)
				{
					Result.Flags.Add(FSatoriFlagOverride::FromJson(*ItemObj));
				}
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FSatoriFlagOverrideList::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (Flags.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Flags)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("flags"), Array);
	}
	return Json;
}

FSatoriGetExperimentsRequest FSatoriGetExperimentsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
	FSatoriGetExperimentsRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("names")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("names"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				Result.Names.Add(Item->AsString());
			}
		}
	}
	if (Json->HasField(TEXT("labels")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("labels"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				Result.Labels.Add(Item->AsString());
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FSatoriGetExperimentsRequest::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (Names.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Names)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Json->SetArrayField(TEXT("names"), Array);
	}
	if (Labels.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Labels)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Json->SetArrayField(TEXT("labels"), Array);
	}
	return Json;
}

FSatoriGetFlagsRequest FSatoriGetFlagsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
	FSatoriGetFlagsRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("names")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("names"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				Result.Names.Add(Item->AsString());
			}
		}
	}
	if (Json->HasField(TEXT("labels")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("labels"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				Result.Labels.Add(Item->AsString());
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FSatoriGetFlagsRequest::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (Names.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Names)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Json->SetArrayField(TEXT("names"), Array);
	}
	if (Labels.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Labels)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Json->SetArrayField(TEXT("labels"), Array);
	}
	return Json;
}

FSatoriGetLiveEventsRequest FSatoriGetLiveEventsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
	FSatoriGetLiveEventsRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("names")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("names"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				Result.Names.Add(Item->AsString());
			}
		}
	}
	if (Json->HasField(TEXT("labels")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("labels"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				Result.Labels.Add(Item->AsString());
			}
		}
	}
	if (Json->HasField(TEXT("past_run_count")))
	{
		Result.PastRunCount = Json->GetIntegerField(TEXT("past_run_count"));
	}
	if (Json->HasField(TEXT("future_run_count")))
	{
		Result.FutureRunCount = Json->GetIntegerField(TEXT("future_run_count"));
	}
	if (Json->HasField(TEXT("start_time_sec")))
	{
		Result.StartTimeSec = static_cast<int64>(Json->GetNumberField(TEXT("start_time_sec")));
	}
	if (Json->HasField(TEXT("end_time_sec")))
	{
		Result.EndTimeSec = static_cast<int64>(Json->GetNumberField(TEXT("end_time_sec")));
	}
	return Result;
}

TSharedPtr<FJsonObject> FSatoriGetLiveEventsRequest::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (Names.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Names)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Json->SetArrayField(TEXT("names"), Array);
	}
	if (Labels.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Labels)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Json->SetArrayField(TEXT("labels"), Array);
	}
	Json->SetNumberField(TEXT("past_run_count"), PastRunCount);
	Json->SetNumberField(TEXT("future_run_count"), FutureRunCount);
	Json->SetNumberField(TEXT("start_time_sec"), StartTimeSec);
	Json->SetNumberField(TEXT("end_time_sec"), EndTimeSec);
	return Json;
}

FSatoriMessage FSatoriMessage::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
	FSatoriMessage Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("schedule_id")))
	{
		Result.ScheduleId = Json->GetStringField(TEXT("schedule_id"));
	}
	if (Json->HasField(TEXT("send_time")))
	{
		Result.SendTime = static_cast<int64>(Json->GetNumberField(TEXT("send_time")));
	}
	if (Json->HasField(TEXT("create_time")))
	{
		Result.CreateTime = static_cast<int64>(Json->GetNumberField(TEXT("create_time")));
	}
	if (Json->HasField(TEXT("update_time")))
	{
		Result.UpdateTime = static_cast<int64>(Json->GetNumberField(TEXT("update_time")));
	}
	if (Json->HasField(TEXT("read_time")))
	{
		Result.ReadTime = static_cast<int64>(Json->GetNumberField(TEXT("read_time")));
	}
	if (Json->HasField(TEXT("consume_time")))
	{
		Result.ConsumeTime = static_cast<int64>(Json->GetNumberField(TEXT("consume_time")));
	}
	if (Json->HasField(TEXT("text")))
	{
		Result.Text = Json->GetStringField(TEXT("text"));
	}
	if (Json->HasField(TEXT("id")))
	{
		Result.Id = Json->GetStringField(TEXT("id"));
	}
	if (Json->HasField(TEXT("title")))
	{
		Result.Title = Json->GetStringField(TEXT("title"));
	}
	if (Json->HasField(TEXT("image_url")))
	{
		Result.ImageUrl = Json->GetStringField(TEXT("image_url"));
	}
	if (Json->HasField(TEXT("metadata")))
	{
		const TSharedPtr<FJsonObject>* MapObj;
		if (Json->TryGetObjectField(TEXT("metadata"), MapObj))
		{
			for (const auto& Pair : (*MapObj)->Values)
			{
				Result.Metadata.Add(Pair.Key, Pair.Value->AsString());
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FSatoriMessage::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!ScheduleId.IsEmpty())
	{
		Json->SetStringField(TEXT("schedule_id"), ScheduleId);
	}
	Json->SetNumberField(TEXT("send_time"), SendTime);
	Json->SetNumberField(TEXT("create_time"), CreateTime);
	Json->SetNumberField(TEXT("update_time"), UpdateTime);
	Json->SetNumberField(TEXT("read_time"), ReadTime);
	Json->SetNumberField(TEXT("consume_time"), ConsumeTime);
	if (!Text.IsEmpty())
	{
		Json->SetStringField(TEXT("text"), Text);
	}
	if (!Id.IsEmpty())
	{
		Json->SetStringField(TEXT("id"), Id);
	}
	if (!Title.IsEmpty())
	{
		Json->SetStringField(TEXT("title"), Title);
	}
	if (!ImageUrl.IsEmpty())
	{
		Json->SetStringField(TEXT("image_url"), ImageUrl);
	}
	if (Metadata.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Metadata)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Json->SetObjectField(TEXT("metadata"), MapObj);
	}
	return Json;
}

FSatoriGetMessageListRequest FSatoriGetMessageListRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
	FSatoriGetMessageListRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("limit")))
	{
		Result.Limit = Json->GetIntegerField(TEXT("limit"));
	}
	if (Json->HasField(TEXT("forward")))
	{
		Result.Forward = Json->GetBoolField(TEXT("forward"));
	}
	if (Json->HasField(TEXT("cursor")))
	{
		Result.Cursor = Json->GetStringField(TEXT("cursor"));
	}
	if (Json->HasField(TEXT("message_ids")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("message_ids"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				Result.MessageIds.Add(Item->AsString());
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FSatoriGetMessageListRequest::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetNumberField(TEXT("limit"), Limit);
	Json->SetBoolField(TEXT("forward"), Forward);
	if (!Cursor.IsEmpty())
	{
		Json->SetStringField(TEXT("cursor"), Cursor);
	}
	if (MessageIds.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : MessageIds)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Json->SetArrayField(TEXT("message_ids"), Array);
	}
	return Json;
}

FSatoriGetMessageListResponse FSatoriGetMessageListResponse::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
	FSatoriGetMessageListResponse Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("messages")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("messages"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				const TSharedPtr<FJsonObject>* ItemObj = nullptr;
				if (Item->TryGetObject(ItemObj) && ItemObj)
				{
					Result.Messages.Add(FSatoriMessage::FromJson(*ItemObj));
				}
			}
		}
	}
	if (Json->HasField(TEXT("next_cursor")))
	{
		Result.NextCursor = Json->GetStringField(TEXT("next_cursor"));
	}
	if (Json->HasField(TEXT("prev_cursor")))
	{
		Result.PrevCursor = Json->GetStringField(TEXT("prev_cursor"));
	}
	if (Json->HasField(TEXT("cacheable_cursor")))
	{
		Result.CacheableCursor = Json->GetStringField(TEXT("cacheable_cursor"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FSatoriGetMessageListResponse::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (Messages.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Messages)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("messages"), Array);
	}
	if (!NextCursor.IsEmpty())
	{
		Json->SetStringField(TEXT("next_cursor"), NextCursor);
	}
	if (!PrevCursor.IsEmpty())
	{
		Json->SetStringField(TEXT("prev_cursor"), PrevCursor);
	}
	if (!CacheableCursor.IsEmpty())
	{
		Json->SetStringField(TEXT("cacheable_cursor"), CacheableCursor);
	}
	return Json;
}

FSatoriIdentifyRequest FSatoriIdentifyRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
	FSatoriIdentifyRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("id")))
	{
		Result.Id = Json->GetStringField(TEXT("id"));
	}
	if (Json->HasField(TEXT("default")))
	{
		const TSharedPtr<FJsonObject>* MapObj;
		if (Json->TryGetObjectField(TEXT("default"), MapObj))
		{
			for (const auto& Pair : (*MapObj)->Values)
			{
				Result.Default.Add(Pair.Key, Pair.Value->AsString());
			}
		}
	}
	if (Json->HasField(TEXT("custom")))
	{
		const TSharedPtr<FJsonObject>* MapObj;
		if (Json->TryGetObjectField(TEXT("custom"), MapObj))
		{
			for (const auto& Pair : (*MapObj)->Values)
			{
				Result.Custom.Add(Pair.Key, Pair.Value->AsString());
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FSatoriIdentifyRequest::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Id.IsEmpty())
	{
		Json->SetStringField(TEXT("id"), Id);
	}
	if (Default.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Default)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Json->SetObjectField(TEXT("default"), MapObj);
	}
	if (Custom.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Custom)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Json->SetObjectField(TEXT("custom"), MapObj);
	}
	return Json;
}

FSatoriJoinLiveEventRequest FSatoriJoinLiveEventRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
	FSatoriJoinLiveEventRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("id")))
	{
		Result.Id = Json->GetStringField(TEXT("id"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FSatoriJoinLiveEventRequest::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Id.IsEmpty())
	{
		Json->SetStringField(TEXT("id"), Id);
	}
	return Json;
}

FSatoriLiveEvent FSatoriLiveEvent::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
	FSatoriLiveEvent Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("name")))
	{
		Result.Name = Json->GetStringField(TEXT("name"));
	}
	if (Json->HasField(TEXT("description")))
	{
		Result.Description = Json->GetStringField(TEXT("description"));
	}
	if (Json->HasField(TEXT("value")))
	{
		Result.Value = Json->GetStringField(TEXT("value"));
	}
	if (Json->HasField(TEXT("active_start_time_sec")))
	{
		Result.ActiveStartTimeSec = static_cast<int64>(Json->GetNumberField(TEXT("active_start_time_sec")));
	}
	if (Json->HasField(TEXT("active_end_time_sec")))
	{
		Result.ActiveEndTimeSec = static_cast<int64>(Json->GetNumberField(TEXT("active_end_time_sec")));
	}
	if (Json->HasField(TEXT("id")))
	{
		Result.Id = Json->GetStringField(TEXT("id"));
	}
	if (Json->HasField(TEXT("start_time_sec")))
	{
		Result.StartTimeSec = static_cast<int64>(Json->GetNumberField(TEXT("start_time_sec")));
	}
	if (Json->HasField(TEXT("end_time_sec")))
	{
		Result.EndTimeSec = static_cast<int64>(Json->GetNumberField(TEXT("end_time_sec")));
	}
	if (Json->HasField(TEXT("duration_sec")))
	{
		Result.DurationSec = static_cast<int64>(Json->GetNumberField(TEXT("duration_sec")));
	}
	if (Json->HasField(TEXT("reset_cron")))
	{
		Result.ResetCron = Json->GetStringField(TEXT("reset_cron"));
	}
	if (Json->HasField(TEXT("status")))
	{
		Result.Status = Json->GetIntegerField(TEXT("status"));
	}
	if (Json->HasField(TEXT("labels")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("labels"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				Result.Labels.Add(Item->AsString());
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FSatoriLiveEvent::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Name.IsEmpty())
	{
		Json->SetStringField(TEXT("name"), Name);
	}
	if (!Description.IsEmpty())
	{
		Json->SetStringField(TEXT("description"), Description);
	}
	if (!Value.IsEmpty())
	{
		Json->SetStringField(TEXT("value"), Value);
	}
	Json->SetNumberField(TEXT("active_start_time_sec"), ActiveStartTimeSec);
	Json->SetNumberField(TEXT("active_end_time_sec"), ActiveEndTimeSec);
	if (!Id.IsEmpty())
	{
		Json->SetStringField(TEXT("id"), Id);
	}
	Json->SetNumberField(TEXT("start_time_sec"), StartTimeSec);
	Json->SetNumberField(TEXT("end_time_sec"), EndTimeSec);
	Json->SetNumberField(TEXT("duration_sec"), DurationSec);
	if (!ResetCron.IsEmpty())
	{
		Json->SetStringField(TEXT("reset_cron"), ResetCron);
	}
	Json->SetNumberField(TEXT("status"), Status);
	if (Labels.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Labels)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Json->SetArrayField(TEXT("labels"), Array);
	}
	return Json;
}

FSatoriLiveEventList FSatoriLiveEventList::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
	FSatoriLiveEventList Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("live_events")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("live_events"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				const TSharedPtr<FJsonObject>* ItemObj = nullptr;
				if (Item->TryGetObject(ItemObj) && ItemObj)
				{
					Result.LiveEvents.Add(FSatoriLiveEvent::FromJson(*ItemObj));
				}
			}
		}
	}
	if (Json->HasField(TEXT("explicit_join_live_events")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("explicit_join_live_events"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				const TSharedPtr<FJsonObject>* ItemObj = nullptr;
				if (Item->TryGetObject(ItemObj) && ItemObj)
				{
					Result.ExplicitJoinLiveEvents.Add(FSatoriLiveEvent::FromJson(*ItemObj));
				}
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FSatoriLiveEventList::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (LiveEvents.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : LiveEvents)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("live_events"), Array);
	}
	if (ExplicitJoinLiveEvents.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : ExplicitJoinLiveEvents)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("explicit_join_live_events"), Array);
	}
	return Json;
}

FSatoriProperties FSatoriProperties::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
	FSatoriProperties Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("default")))
	{
		const TSharedPtr<FJsonObject>* MapObj;
		if (Json->TryGetObjectField(TEXT("default"), MapObj))
		{
			for (const auto& Pair : (*MapObj)->Values)
			{
				Result.Default.Add(Pair.Key, Pair.Value->AsString());
			}
		}
	}
	if (Json->HasField(TEXT("computed")))
	{
		const TSharedPtr<FJsonObject>* MapObj;
		if (Json->TryGetObjectField(TEXT("computed"), MapObj))
		{
			for (const auto& Pair : (*MapObj)->Values)
			{
				Result.Computed.Add(Pair.Key, Pair.Value->AsString());
			}
		}
	}
	if (Json->HasField(TEXT("custom")))
	{
		const TSharedPtr<FJsonObject>* MapObj;
		if (Json->TryGetObjectField(TEXT("custom"), MapObj))
		{
			for (const auto& Pair : (*MapObj)->Values)
			{
				Result.Custom.Add(Pair.Key, Pair.Value->AsString());
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FSatoriProperties::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (Default.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Default)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Json->SetObjectField(TEXT("default"), MapObj);
	}
	if (Computed.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Computed)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Json->SetObjectField(TEXT("computed"), MapObj);
	}
	if (Custom.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Custom)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Json->SetObjectField(TEXT("custom"), MapObj);
	}
	return Json;
}

FSatoriSession FSatoriSession::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
	FSatoriSession Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("token")))
	{
		Result.Token = Json->GetStringField(TEXT("token"));
	}
	if (Json->HasField(TEXT("refresh_token")))
	{
		Result.RefreshToken = Json->GetStringField(TEXT("refresh_token"));
	}
	if (Json->HasField(TEXT("properties")))
	{
		const TSharedPtr<FJsonObject>* NestedObj;
		if (Json->TryGetObjectField(TEXT("properties"), NestedObj))
		{
			Result.Properties = FSatoriProperties::FromJson(*NestedObj);
		}
	}
	Result.ParseTokens();
	return Result;
}

TSharedPtr<FJsonObject> FSatoriSession::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Token.IsEmpty())
	{
		Json->SetStringField(TEXT("token"), Token);
	}
	if (!RefreshToken.IsEmpty())
	{
		Json->SetStringField(TEXT("refresh_token"), RefreshToken);
	}
	Json->SetObjectField(TEXT("properties"), Properties.ToJson());
	return Json;
}

FSatoriUpdatePropertiesRequest FSatoriUpdatePropertiesRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
	FSatoriUpdatePropertiesRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("recompute")))
	{
		Result.Recompute = Json->GetBoolField(TEXT("recompute"));
	}
	if (Json->HasField(TEXT("default")))
	{
		const TSharedPtr<FJsonObject>* MapObj;
		if (Json->TryGetObjectField(TEXT("default"), MapObj))
		{
			for (const auto& Pair : (*MapObj)->Values)
			{
				Result.Default.Add(Pair.Key, Pair.Value->AsString());
			}
		}
	}
	if (Json->HasField(TEXT("custom")))
	{
		const TSharedPtr<FJsonObject>* MapObj;
		if (Json->TryGetObjectField(TEXT("custom"), MapObj))
		{
			for (const auto& Pair : (*MapObj)->Values)
			{
				Result.Custom.Add(Pair.Key, Pair.Value->AsString());
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FSatoriUpdatePropertiesRequest::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetBoolField(TEXT("recompute"), Recompute);
	if (Default.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Default)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Json->SetObjectField(TEXT("default"), MapObj);
	}
	if (Custom.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Custom)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Json->SetObjectField(TEXT("custom"), MapObj);
	}
	return Json;
}

FSatoriUpdateMessageRequest FSatoriUpdateMessageRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
	FSatoriUpdateMessageRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("id")))
	{
		Result.Id = Json->GetStringField(TEXT("id"));
	}
	if (Json->HasField(TEXT("read_time")))
	{
		Result.ReadTime = static_cast<int64>(Json->GetNumberField(TEXT("read_time")));
	}
	if (Json->HasField(TEXT("consume_time")))
	{
		Result.ConsumeTime = static_cast<int64>(Json->GetNumberField(TEXT("consume_time")));
	}
	return Result;
}

TSharedPtr<FJsonObject> FSatoriUpdateMessageRequest::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Id.IsEmpty())
	{
		Json->SetStringField(TEXT("id"), Id);
	}
	Json->SetNumberField(TEXT("read_time"), ReadTime);
	Json->SetNumberField(TEXT("consume_time"), ConsumeTime);
	return Json;
}

// --- FSatoriClientConfig ---

FString FSatoriClientConfig::GetBaseUrl() const noexcept
{
	const FString Scheme = bUseSSL ? TEXT("https") : TEXT("http");
	return FString::Printf(TEXT("%s://%s:%d"), *Scheme, *Host, Port);
}

void SatoriApi::Authenticate(
	const FSatoriClientConfig& Config,
	FString Id,
	bool NoSession,
	const TMap<FString, FString>& Default,
	const TMap<FString, FString>& Custom,
	TFunction<void(const FSatoriSession&)> OnSuccess,
	TFunction<void(const FSatoriError&)> OnError,
	float Timeout,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v1/authenticate");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Basic;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Id.IsEmpty())
	{
		Body->SetStringField(TEXT("id"), Id);
	}
	Body->SetBoolField(TEXT("no_session"), NoSession);
	if (Default.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Default)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("default"), MapObj);
	}
	if (Custom.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Custom)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("custom"), MapObj);
	}

	MakeRequest(ToNakamaConfig(Config), Endpoint, TEXT("POST"), Body, AuthType, TEXT(""),
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FSatoriSession Result = FSatoriSession::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		MakeSatoriErrorAdapter(OnError), Timeout, CancellationToken);
}

void SatoriApi::AuthenticateLogout(
	const FSatoriClientConfig& Config,
	FString Token,
	FString RefreshToken,
	TFunction<void()> OnSuccess,
	TFunction<void(const FSatoriError&)> OnError,
	float Timeout,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v1/authenticate/logout");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Token.IsEmpty())
	{
		Body->SetStringField(TEXT("token"), Token);
	}
	if (!RefreshToken.IsEmpty())
	{
		Body->SetStringField(TEXT("refresh_token"), RefreshToken);
	}

	MakeRequest(ToNakamaConfig(Config), Endpoint, TEXT("POST"), Body, AuthType, Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		MakeSatoriErrorAdapter(OnError), Timeout, CancellationToken);
}

void SatoriApi::AuthenticateRefresh(
	const FSatoriClientConfig& Config,
	FString RefreshToken,
	TFunction<void(const FSatoriSession&)> OnSuccess,
	TFunction<void(const FSatoriError&)> OnError,
	float Timeout,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v1/authenticate/refresh");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Basic;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!RefreshToken.IsEmpty())
	{
		Body->SetStringField(TEXT("refresh_token"), RefreshToken);
	}

	MakeRequest(ToNakamaConfig(Config), Endpoint, TEXT("POST"), Body, AuthType, TEXT(""),
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FSatoriSession Result = FSatoriSession::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		MakeSatoriErrorAdapter(OnError), Timeout, CancellationToken);
}

void SatoriApi::DeleteIdentity(
	const FSatoriClientConfig& Config,
	const FSatoriSession& Session,
	TFunction<void()> OnSuccess,
	TFunction<void(const FSatoriError&)> OnError,
	float Timeout,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v1/identity");

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(ToNakamaConfig(Config), Endpoint, TEXT("DELETE"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		MakeSatoriErrorAdapter(OnError), Timeout, CancellationToken);
}

void SatoriApi::Event(
	const FSatoriClientConfig& Config,
	const FSatoriSession& Session,
	const TArray<FSatoriEvent>& Events,
	TFunction<void()> OnSuccess,
	TFunction<void(const FSatoriError&)> OnError,
	float Timeout,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v1/event");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (Events.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Events)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Body->SetArrayField(TEXT("events"), Array);
	}

	MakeRequest(ToNakamaConfig(Config), Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		MakeSatoriErrorAdapter(OnError), Timeout, CancellationToken);
}

void SatoriApi::ServerEvent(
	const FSatoriClientConfig& Config,
	const FSatoriSession& Session,
	const TArray<FSatoriEvent>& Events,
	TFunction<void()> OnSuccess,
	TFunction<void(const FSatoriError&)> OnError,
	float Timeout,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v1/server-event");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (Events.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Events)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Body->SetArrayField(TEXT("events"), Array);
	}

	MakeRequest(ToNakamaConfig(Config), Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		MakeSatoriErrorAdapter(OnError), Timeout, CancellationToken);
}

void SatoriApi::GetExperiments(
	const FSatoriClientConfig& Config,
	const FSatoriSession& Session,
	const TArray<FString>& Names,
	const TArray<FString>& Labels,
	TFunction<void(const FSatoriExperimentList&)> OnSuccess,
	TFunction<void(const FSatoriError&)> OnError,
	float Timeout,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v1/experiment");
	TArray<FString> QueryParams;
	for (const FString& Item : Names)
	{
		QueryParams.Add(FString::Printf(TEXT("names=%s"), *Item));
	}
	for (const FString& Item : Labels)
	{
		QueryParams.Add(FString::Printf(TEXT("labels=%s"), *Item));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(ToNakamaConfig(Config), Endpoint, TEXT("GET"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FSatoriExperimentList Result = FSatoriExperimentList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		MakeSatoriErrorAdapter(OnError), Timeout, CancellationToken);
}

void SatoriApi::GetFlagOverrides(
	const FSatoriClientConfig& Config,
	const FSatoriSession& Session,
	const TArray<FString>& Names,
	const TArray<FString>& Labels,
	TFunction<void(const FSatoriFlagOverrideList&)> OnSuccess,
	TFunction<void(const FSatoriError&)> OnError,
	float Timeout,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v1/flag/override");
	TArray<FString> QueryParams;
	for (const FString& Item : Names)
	{
		QueryParams.Add(FString::Printf(TEXT("names=%s"), *Item));
	}
	for (const FString& Item : Labels)
	{
		QueryParams.Add(FString::Printf(TEXT("labels=%s"), *Item));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(ToNakamaConfig(Config), Endpoint, TEXT("GET"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FSatoriFlagOverrideList Result = FSatoriFlagOverrideList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		MakeSatoriErrorAdapter(OnError), Timeout, CancellationToken);
}

void SatoriApi::GetFlags(
	const FSatoriClientConfig& Config,
	const FSatoriSession& Session,
	const TArray<FString>& Names,
	const TArray<FString>& Labels,
	TFunction<void(const FSatoriFlagList&)> OnSuccess,
	TFunction<void(const FSatoriError&)> OnError,
	float Timeout,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v1/flag");
	TArray<FString> QueryParams;
	for (const FString& Item : Names)
	{
		QueryParams.Add(FString::Printf(TEXT("names=%s"), *Item));
	}
	for (const FString& Item : Labels)
	{
		QueryParams.Add(FString::Printf(TEXT("labels=%s"), *Item));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(ToNakamaConfig(Config), Endpoint, TEXT("GET"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FSatoriFlagList Result = FSatoriFlagList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		MakeSatoriErrorAdapter(OnError), Timeout, CancellationToken);
}

void SatoriApi::GetLiveEvents(
	const FSatoriClientConfig& Config,
	const FSatoriSession& Session,
	const TArray<FString>& Names,
	const TArray<FString>& Labels,
	int32 PastRunCount,
	int32 FutureRunCount,
	int64 StartTimeSec,
	int64 EndTimeSec,
	TFunction<void(const FSatoriLiveEventList&)> OnSuccess,
	TFunction<void(const FSatoriError&)> OnError,
	float Timeout,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v1/live-event");
	TArray<FString> QueryParams;
	for (const FString& Item : Names)
	{
		QueryParams.Add(FString::Printf(TEXT("names=%s"), *Item));
	}
	for (const FString& Item : Labels)
	{
		QueryParams.Add(FString::Printf(TEXT("labels=%s"), *Item));
	}
	if (PastRunCount != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("past_run_count=%d"), PastRunCount));
	}
	if (FutureRunCount != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("future_run_count=%d"), FutureRunCount));
	}
	if (StartTimeSec != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("start_time_sec=%lld"), StartTimeSec));
	}
	if (EndTimeSec != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("end_time_sec=%lld"), EndTimeSec));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(ToNakamaConfig(Config), Endpoint, TEXT("GET"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FSatoriLiveEventList Result = FSatoriLiveEventList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		MakeSatoriErrorAdapter(OnError), Timeout, CancellationToken);
}

void SatoriApi::JoinLiveEvent(
	const FSatoriClientConfig& Config,
	const FSatoriSession& Session,
	FString Id,
	TFunction<void()> OnSuccess,
	TFunction<void(const FSatoriError&)> OnError,
	float Timeout,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v1/live-event/{id}/participation");
	Endpoint = Endpoint.Replace(TEXT("{id}"), *Id);
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(ToNakamaConfig(Config), Endpoint, TEXT("POST"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		MakeSatoriErrorAdapter(OnError), Timeout, CancellationToken);
}

void SatoriApi::Healthcheck(
	const FSatoriClientConfig& Config,
	const FSatoriSession& Session,
	TFunction<void()> OnSuccess,
	TFunction<void(const FSatoriError&)> OnError,
	float Timeout,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/healthcheck");

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(ToNakamaConfig(Config), Endpoint, TEXT("GET"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		MakeSatoriErrorAdapter(OnError), Timeout, CancellationToken);
}

void SatoriApi::Identify(
	const FSatoriClientConfig& Config,
	const FSatoriSession& Session,
	FString Id,
	const TMap<FString, FString>& Default,
	const TMap<FString, FString>& Custom,
	TFunction<void(const FSatoriSession&)> OnSuccess,
	TFunction<void(const FSatoriError&)> OnError,
	float Timeout,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v1/identify");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Id.IsEmpty())
	{
		Body->SetStringField(TEXT("id"), Id);
	}
	if (Default.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Default)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("default"), MapObj);
	}
	if (Custom.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Custom)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("custom"), MapObj);
	}

	MakeRequest(ToNakamaConfig(Config), Endpoint, TEXT("PUT"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FSatoriSession Result = FSatoriSession::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		MakeSatoriErrorAdapter(OnError), Timeout, CancellationToken);
}

void SatoriApi::ListProperties(
	const FSatoriClientConfig& Config,
	const FSatoriSession& Session,
	TFunction<void(const FSatoriProperties&)> OnSuccess,
	TFunction<void(const FSatoriError&)> OnError,
	float Timeout,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v1/properties");

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(ToNakamaConfig(Config), Endpoint, TEXT("GET"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FSatoriProperties Result = FSatoriProperties::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		MakeSatoriErrorAdapter(OnError), Timeout, CancellationToken);
}

void SatoriApi::Readycheck(
	const FSatoriClientConfig& Config,
	const FSatoriSession& Session,
	TFunction<void()> OnSuccess,
	TFunction<void(const FSatoriError&)> OnError,
	float Timeout,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/readycheck");

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(ToNakamaConfig(Config), Endpoint, TEXT("GET"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		MakeSatoriErrorAdapter(OnError), Timeout, CancellationToken);
}

void SatoriApi::UpdateProperties(
	const FSatoriClientConfig& Config,
	const FSatoriSession& Session,
	bool Recompute,
	const TMap<FString, FString>& Default,
	const TMap<FString, FString>& Custom,
	TFunction<void()> OnSuccess,
	TFunction<void(const FSatoriError&)> OnError,
	float Timeout,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v1/properties");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	Body->SetBoolField(TEXT("recompute"), Recompute);
	if (Default.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Default)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("default"), MapObj);
	}
	if (Custom.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Custom)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("custom"), MapObj);
	}

	MakeRequest(ToNakamaConfig(Config), Endpoint, TEXT("PUT"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		MakeSatoriErrorAdapter(OnError), Timeout, CancellationToken);
}

void SatoriApi::GetMessageList(
	const FSatoriClientConfig& Config,
	const FSatoriSession& Session,
	int32 Limit,
	bool Forward,
	FString Cursor,
	const TArray<FString>& MessageIds,
	TFunction<void(const FSatoriGetMessageListResponse&)> OnSuccess,
	TFunction<void(const FSatoriError&)> OnError,
	float Timeout,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v1/message");
	TArray<FString> QueryParams;
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	QueryParams.Add(FString::Printf(TEXT("forward=%s"), Forward ? TEXT("true") : TEXT("false")));
	if (!Cursor.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("cursor=%s"), *Cursor));
	}
	for (const FString& Item : MessageIds)
	{
		QueryParams.Add(FString::Printf(TEXT("message_ids=%s"), *Item));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(ToNakamaConfig(Config), Endpoint, TEXT("GET"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FSatoriGetMessageListResponse Result = FSatoriGetMessageListResponse::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		MakeSatoriErrorAdapter(OnError), Timeout, CancellationToken);
}

void SatoriApi::UpdateMessage(
	const FSatoriClientConfig& Config,
	const FSatoriSession& Session,
	FString Id,
	int64 ReadTime,
	int64 ConsumeTime,
	TFunction<void()> OnSuccess,
	TFunction<void(const FSatoriError&)> OnError,
	float Timeout,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v1/message/{id}");
	Endpoint = Endpoint.Replace(TEXT("{id}"), *Id);
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Id.IsEmpty())
	{
		Body->SetStringField(TEXT("id"), Id);
	}
	Body->SetNumberField(TEXT("read_time"), ReadTime);
	Body->SetNumberField(TEXT("consume_time"), ConsumeTime);

	MakeRequest(ToNakamaConfig(Config), Endpoint, TEXT("PUT"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		MakeSatoriErrorAdapter(OnError), Timeout, CancellationToken);
}

void SatoriApi::DeleteMessage(
	const FSatoriClientConfig& Config,
	const FSatoriSession& Session,
	FString Id,
	TFunction<void()> OnSuccess,
	TFunction<void(const FSatoriError&)> OnError,
	float Timeout,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	FString Endpoint = TEXT("/v1/message/{id}");
	Endpoint = Endpoint.Replace(TEXT("{id}"), *Id);
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(ToNakamaConfig(Config), Endpoint, TEXT("DELETE"), Body, AuthType, Session.Token,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		MakeSatoriErrorAdapter(OnError), Timeout, CancellationToken);
}

// Module implementation
class FSatoriApiModule : public IModuleInterface
{
public:
	virtual void StartupModule() override
	{
		UE_LOG(LogSatori, Log, TEXT("SatoriApi module starting"));
	}

	virtual void ShutdownModule() override
	{
		UE_LOG(LogSatori, Log, TEXT("SatoriApi module shutting down"));
	}
};

IMPLEMENT_MODULE(FSatoriApiModule, SatoriApi)
