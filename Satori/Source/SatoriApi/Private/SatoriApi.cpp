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

#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Misc/Base64.h"
#include "Misc/DateTime.h"
#include "Modules/ModuleManager.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/MemoryWriter.h"
#include "Stats/Stats.h"

DEFINE_LOG_CATEGORY(LogSatori);

// Stat group: use "stat Satori" in console
DECLARE_STATS_GROUP(TEXT("Satori"), STATGROUP_Satori, STATCAT_Advanced);
DECLARE_CYCLE_STAT(TEXT("MakeRequest Dispatch"), STAT_Satori_MakeRequest_Dispatch, STATGROUP_Satori);
DECLARE_CYCLE_STAT(TEXT("OnResponse"), STAT_Satori_OnResponse, STATGROUP_Satori);
DECLARE_CYCLE_STAT(TEXT("JsonSerialize"), STAT_Satori_JsonSerialize, STATGROUP_Satori);
DECLARE_CYCLE_STAT(TEXT("JsonDeserialize"), STAT_Satori_JsonDeserialize, STATGROUP_Satori);
DECLARE_DWORD_ACCUMULATOR_STAT(TEXT("ActiveRequests"), STAT_Satori_ActiveRequests, STATGROUP_Satori);
DECLARE_DWORD_ACCUMULATOR_STAT(TEXT("TotalRequests"), STAT_Satori_TotalRequests, STATGROUP_Satori);
DECLARE_DWORD_ACCUMULATOR_STAT(TEXT("TotalErrors"), STAT_Satori_TotalErrors, STATGROUP_Satori);

// --- FSatoriSession JWT helpers ---

bool FSatoriSession::ParseJwtPayload(const FString& Jwt, TSharedPtr<FJsonObject>& Out)
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

void FSatoriSession::ParseTokens()
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

bool FSatoriSession::IsExpired(int64 BufferSeconds) const
{
	if (TokenExpiresAt == 0)
	{
		return true;
	}
	return (TokenExpiresAt - BufferSeconds) <= FDateTime::UtcNow().ToUnixTimestamp();
}

bool FSatoriSession::IsRefreshExpired(int64 BufferSeconds) const
{
	if (RefreshTokenExpiresAt == 0)
	{
		return true;
	}
	return (RefreshTokenExpiresAt - BufferSeconds) <= FDateTime::UtcNow().ToUnixTimestamp();
}

void FSatoriSession::Update(const FString& NewToken, const FString& NewRefreshToken)
{
	Token = NewToken;
	RefreshToken = NewRefreshToken;
	ParseTokens();
}

FSatoriAuthenticateLogoutRequest FSatoriAuthenticateLogoutRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
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

TSharedPtr<FJsonObject> FSatoriAuthenticateLogoutRequest::ToJson() const
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

FSatoriAuthenticateRefreshRequest FSatoriAuthenticateRefreshRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
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

TSharedPtr<FJsonObject> FSatoriAuthenticateRefreshRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!RefreshToken.IsEmpty())
	{
		Json->SetStringField(TEXT("refresh_token"), RefreshToken);
	}
	return Json;
}

FSatoriAuthenticateRequest FSatoriAuthenticateRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
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

TSharedPtr<FJsonObject> FSatoriAuthenticateRequest::ToJson() const
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

FSatoriDeleteMessageRequest FSatoriDeleteMessageRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
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

TSharedPtr<FJsonObject> FSatoriDeleteMessageRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Id.IsEmpty())
	{
		Json->SetStringField(TEXT("id"), Id);
	}
	return Json;
}

FSatoriEvent FSatoriEvent::FromJson(const TSharedPtr<FJsonObject>& Json)
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

TSharedPtr<FJsonObject> FSatoriEvent::ToJson() const
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

FSatoriEventRequest FSatoriEventRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
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

TSharedPtr<FJsonObject> FSatoriEventRequest::ToJson() const
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

FSatoriExperiment FSatoriExperiment::FromJson(const TSharedPtr<FJsonObject>& Json)
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

TSharedPtr<FJsonObject> FSatoriExperiment::ToJson() const
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

FSatoriExperimentList FSatoriExperimentList::FromJson(const TSharedPtr<FJsonObject>& Json)
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

TSharedPtr<FJsonObject> FSatoriExperimentList::ToJson() const
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

FSatoriFlag FSatoriFlag::FromJson(const TSharedPtr<FJsonObject>& Json)
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

TSharedPtr<FJsonObject> FSatoriFlag::ToJson() const
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

FSatoriValueChangeReason FSatoriValueChangeReason::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FSatoriValueChangeReason Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("type")))
	{
		const TSharedPtr<FJsonObject>* NestedObj;
		if (Json->TryGetObjectField(TEXT("type"), NestedObj))
		{
			Result.Type = FSatoriType::FromJson(*NestedObj);
		}
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

TSharedPtr<FJsonObject> FSatoriValueChangeReason::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetObjectField(TEXT("type"), Type.ToJson());
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

FSatoriFlagList FSatoriFlagList::FromJson(const TSharedPtr<FJsonObject>& Json)
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

TSharedPtr<FJsonObject> FSatoriFlagList::ToJson() const
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

FSatoriFlagOverride FSatoriFlagOverride::FromJson(const TSharedPtr<FJsonObject>& Json)
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
					Result.Overrides.Add(FSatoriValue::FromJson(*ItemObj));
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

TSharedPtr<FJsonObject> FSatoriFlagOverride::ToJson() const
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

FSatoriValue FSatoriValue::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FSatoriValue Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("type")))
	{
		const TSharedPtr<FJsonObject>* NestedObj;
		if (Json->TryGetObjectField(TEXT("type"), NestedObj))
		{
			Result.Type = FSatoriType::FromJson(*NestedObj);
		}
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

TSharedPtr<FJsonObject> FSatoriValue::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetObjectField(TEXT("type"), Type.ToJson());
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

FSatoriFlagOverrideList FSatoriFlagOverrideList::FromJson(const TSharedPtr<FJsonObject>& Json)
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

TSharedPtr<FJsonObject> FSatoriFlagOverrideList::ToJson() const
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

FSatoriGetExperimentsRequest FSatoriGetExperimentsRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
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

TSharedPtr<FJsonObject> FSatoriGetExperimentsRequest::ToJson() const
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

FSatoriGetFlagsRequest FSatoriGetFlagsRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
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

TSharedPtr<FJsonObject> FSatoriGetFlagsRequest::ToJson() const
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

FSatoriGetLiveEventsRequest FSatoriGetLiveEventsRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
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

TSharedPtr<FJsonObject> FSatoriGetLiveEventsRequest::ToJson() const
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

FSatoriGetMessageListRequest FSatoriGetMessageListRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
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

TSharedPtr<FJsonObject> FSatoriGetMessageListRequest::ToJson() const
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

FSatoriGetMessageListResponse FSatoriGetMessageListResponse::FromJson(const TSharedPtr<FJsonObject>& Json)
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

TSharedPtr<FJsonObject> FSatoriGetMessageListResponse::ToJson() const
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

FSatoriIdentifyRequest FSatoriIdentifyRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
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

TSharedPtr<FJsonObject> FSatoriIdentifyRequest::ToJson() const
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

FSatoriJoinLiveEventRequest FSatoriJoinLiveEventRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
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

TSharedPtr<FJsonObject> FSatoriJoinLiveEventRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Id.IsEmpty())
	{
		Json->SetStringField(TEXT("id"), Id);
	}
	return Json;
}

FSatoriLiveEvent FSatoriLiveEvent::FromJson(const TSharedPtr<FJsonObject>& Json)
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
		const TSharedPtr<FJsonObject>* NestedObj;
		if (Json->TryGetObjectField(TEXT("status"), NestedObj))
		{
			Result.Status = FSatoriStatus::FromJson(*NestedObj);
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

TSharedPtr<FJsonObject> FSatoriLiveEvent::ToJson() const
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
	Json->SetObjectField(TEXT("status"), Status.ToJson());
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

FSatoriLiveEventList FSatoriLiveEventList::FromJson(const TSharedPtr<FJsonObject>& Json)
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

TSharedPtr<FJsonObject> FSatoriLiveEventList::ToJson() const
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

FSatoriMessage FSatoriMessage::FromJson(const TSharedPtr<FJsonObject>& Json)
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

TSharedPtr<FJsonObject> FSatoriMessage::ToJson() const
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

FSatoriProperties FSatoriProperties::FromJson(const TSharedPtr<FJsonObject>& Json)
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

TSharedPtr<FJsonObject> FSatoriProperties::ToJson() const
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

FSatoriSession FSatoriSession::FromJson(const TSharedPtr<FJsonObject>& Json)
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

TSharedPtr<FJsonObject> FSatoriSession::ToJson() const
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

FSatoriUpdatePropertiesRequest FSatoriUpdatePropertiesRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
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

TSharedPtr<FJsonObject> FSatoriUpdatePropertiesRequest::ToJson() const
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

FSatoriUpdateMessageRequest FSatoriUpdateMessageRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
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

TSharedPtr<FJsonObject> FSatoriUpdateMessageRequest::ToJson() const
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

// --- FSatoriApiConfig ---

FString FSatoriApiConfig::GetBaseUrl() const
{
	const FString Scheme = bUseSSL ? TEXT("https") : TEXT("http");
	return FString::Printf(TEXT("%s://%s:%d"), *Scheme, *Host, Port);
}


// --- File-local HTTP helpers ---

namespace
{

void DoHttpRequest(
	const FSatoriApiConfig& Config,
	const FString& Endpoint,
	const FString& Method,
	const FString& BodyString,
	ESatoriRequestAuth AuthType,
	const FString& TokenString,
	TFunction<void(TSharedPtr<FJsonObject>)> OnSuccess,
	TFunction<void(const FSatoriError&)> OnError,
	FSatoriCancellationTokenPtr CancellationToken)
{
	SCOPE_CYCLE_COUNTER(STAT_Satori_MakeRequest_Dispatch);
	TRACE_CPUPROFILER_EVENT_SCOPE(Satori_MakeRequest);
	INC_DWORD_STAT(STAT_Satori_ActiveRequests);
	INC_DWORD_STAT(STAT_Satori_TotalRequests);

	const FString Url = Config.GetBaseUrl() + Endpoint;

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(Url);
	Request->SetVerb(Method);
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("Accept"), TEXT("application/json"));

	switch (AuthType)
	{
	case ESatoriRequestAuth::Basic:
		{
			const FString Auth = FString::Printf(TEXT("%s:"), *Config.ServerKey);
			Request->SetHeader(TEXT("Authorization"), FString::Printf(TEXT("Basic %s"), *FBase64::Encode(Auth)));
		}
		break;
	case ESatoriRequestAuth::Bearer:
		if (!TokenString.IsEmpty())
		{
			Request->SetHeader(TEXT("Authorization"), FString::Printf(TEXT("Bearer %s"), *TokenString));
		}
		break;
	case ESatoriRequestAuth::None:
	default:
		break;
	}

	if (!BodyString.IsEmpty() && Method != TEXT("GET"))
	{
		Request->SetContentAsString(BodyString);
		UE_LOG(LogSatori, Log, TEXT("Request %s %s: %s"), *Method, *Url, *BodyString);
	}
	else
	{
		UE_LOG(LogSatori, Log, TEXT("Request %s %s"), *Method, *Url);
	}

	Request->SetTimeout(Config.Timeout);

	Request->OnProcessRequestComplete().BindLambda(
		[OnSuccess, OnError, CancellationToken](FHttpRequestPtr Req, FHttpResponsePtr Res, bool bSuccess)
		{
			SCOPE_CYCLE_COUNTER(STAT_Satori_OnResponse);
			TRACE_CPUPROFILER_EVENT_SCOPE(Satori_OnResponse);
			DEC_DWORD_STAT(STAT_Satori_ActiveRequests);

			if (CancellationToken && CancellationToken->IsCancelled())
			{
				if (OnError)
				{
					OnError(FSatoriError(TEXT("Request cancelled"), -1));
				}
				return;
			}

			if (!bSuccess || !Res.IsValid())
			{
				INC_DWORD_STAT(STAT_Satori_TotalErrors);
				if (OnError)
				{
					OnError(FSatoriError(TEXT("Connection failed"), 0));
				}
				return;
			}

			const int32 Code = Res->GetResponseCode();
			const FString Content = Res->GetContentAsString();

			UE_LOG(LogSatori, Log, TEXT("Response %d: %s"), Code, *Content);

			if (Code < 200 || Code >= 300)
			{
				INC_DWORD_STAT(STAT_Satori_TotalErrors);
				FString ErrorMsg = FString::Printf(TEXT("HTTP %d"), Code);
				TSharedPtr<FJsonObject> Json;
				if (FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Content), Json) && Json.IsValid())
				{
					if (Json->HasField(TEXT("message")))
					{
						ErrorMsg = Json->GetStringField(TEXT("message"));
					}
				}
				if (OnError)
				{
					OnError(FSatoriError(ErrorMsg, Code));
				}
				return;
			}

			TSharedPtr<FJsonObject> Json;
			if (!Content.IsEmpty())
			{
				SCOPE_CYCLE_COUNTER(STAT_Satori_JsonDeserialize);
				if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Content), Json) || !Json.IsValid())
				{
					INC_DWORD_STAT(STAT_Satori_TotalErrors);
					if (OnError)
					{
						OnError(FSatoriError(TEXT("Invalid JSON response"), 500));
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

void SendRequest(
	const FSatoriApiConfig& Config,
	const FString& Endpoint,
	const FString& Method,
	const FString& BodyString,
	ESatoriRequestAuth AuthType,
	FSatoriSessionPtr Session,
	const FString& AuthValue,
	TFunction<void(TSharedPtr<FJsonObject>)> OnSuccess,
	TFunction<void(const FSatoriError&)> OnError,
	FSatoriCancellationTokenPtr CancellationToken)
{
	// Early cancellation check
	if (CancellationToken && CancellationToken->IsCancelled())
	{
		if (OnError)
		{
			OnError(FSatoriError(TEXT("Request cancelled"), -1));
		}
		return;
	}

	// Determine token string
	FString TokenString;
	if (AuthType == ESatoriRequestAuth::Bearer && Session.IsValid())
	{
		TokenString = Session->Token;
	}
	else
	{
		TokenString = AuthValue;
	}

	DoHttpRequest(Config, Endpoint, Method, BodyString, AuthType, TokenString, OnSuccess, OnError, CancellationToken);
}
FString SerializeJsonToString(const TSharedPtr<FJsonObject>& Json)
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

FString SerializeJsonEscaped(const TSharedPtr<FJsonObject>& Json)
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

void MakeRequest(
	const FSatoriApiConfig& Config,
	const FString& Endpoint,
	const FString& Method,
	const TSharedPtr<FJsonObject>& Body,
	ESatoriRequestAuth AuthType,
	FSatoriSessionPtr Session,
	const FString& AuthValue,
	TFunction<void(TSharedPtr<FJsonObject>)> OnSuccess,
	TFunction<void(const FSatoriError&)> OnError,
	FSatoriCancellationTokenPtr CancellationToken)
{
	FString BodyString;
	if (Body.IsValid() && Method != TEXT("GET"))
	{
		SCOPE_CYCLE_COUNTER(STAT_Satori_JsonSerialize);
		BodyString = SerializeJsonToString(Body);
	}
	SendRequest(Config, Endpoint, Method, BodyString, AuthType, Session, AuthValue, OnSuccess, OnError, CancellationToken);
}

} // anonymous namespace

void SatoriApi::Authenticate(
	const FSatoriApiConfig& Config,
	FString Id,
	bool NoSession,
	const TMap<FString, FString>& Default,
	const TMap<FString, FString>& Custom,
	TFunction<void(const FSatoriSession&)> OnSuccess,
	TFunction<void(const FSatoriError&)> OnError,
	FSatoriCancellationTokenPtr CancellationToken)
{
	FString Endpoint = TEXT("/v1/authenticate");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ESatoriRequestAuth AuthType = ESatoriRequestAuth::Basic;TSharedPtr<FJsonObject> Body;
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

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, nullptr, TEXT(""),
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FSatoriSession Result = FSatoriSession::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, CancellationToken);
}

void SatoriApi::AuthenticateLogout(
	const FSatoriApiConfig& Config,
	FString Token,
	FString RefreshToken,
	TFunction<void()> OnSuccess,
	TFunction<void(const FSatoriError&)> OnError,
	FSatoriCancellationTokenPtr CancellationToken)
{
	FString Endpoint = TEXT("/v1/authenticate/logout");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ESatoriRequestAuth AuthType = ESatoriRequestAuth::Basic;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Token.IsEmpty())
	{
		Body->SetStringField(TEXT("token"), Token);
	}
	if (!RefreshToken.IsEmpty())
	{
		Body->SetStringField(TEXT("refresh_token"), RefreshToken);
	}

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, nullptr, TEXT(""),
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, CancellationToken);
}

void SatoriApi::AuthenticateRefresh(
	const FSatoriApiConfig& Config,
	FString RefreshToken,
	TFunction<void(const FSatoriSession&)> OnSuccess,
	TFunction<void(const FSatoriError&)> OnError,
	FSatoriCancellationTokenPtr CancellationToken)
{
	FString Endpoint = TEXT("/v1/authenticate/refresh");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ESatoriRequestAuth AuthType = ESatoriRequestAuth::Basic;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!RefreshToken.IsEmpty())
	{
		Body->SetStringField(TEXT("refresh_token"), RefreshToken);
	}

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, nullptr, TEXT(""),
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FSatoriSession Result = FSatoriSession::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, CancellationToken);
}

void SatoriApi::DeleteIdentity(
	const FSatoriApiConfig& Config,
	FSatoriSessionPtr Session,
	TFunction<void()> OnSuccess,
	TFunction<void(const FSatoriError&)> OnError,
	FSatoriCancellationTokenPtr CancellationToken)
{
	FString Endpoint = TEXT("/v1/identity");

	ESatoriRequestAuth AuthType = ESatoriRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("DELETE"), Body, AuthType, Session, TEXT(""),
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, CancellationToken);
}

void SatoriApi::Event(
	const FSatoriApiConfig& Config,
	FSatoriSessionPtr Session,
	const TArray<FSatoriEvent>& Events,
	TFunction<void()> OnSuccess,
	TFunction<void(const FSatoriError&)> OnError,
	FSatoriCancellationTokenPtr CancellationToken)
{
	FString Endpoint = TEXT("/v1/event");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ESatoriRequestAuth AuthType = ESatoriRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
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

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session, TEXT(""),
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, CancellationToken);
}

void SatoriApi::ServerEvent(
	const FSatoriApiConfig& Config,
	FSatoriSessionPtr Session,
	const TArray<FSatoriEvent>& Events,
	TFunction<void()> OnSuccess,
	TFunction<void(const FSatoriError&)> OnError,
	FSatoriCancellationTokenPtr CancellationToken)
{
	FString Endpoint = TEXT("/v1/server-event");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ESatoriRequestAuth AuthType = ESatoriRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
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

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session, TEXT(""),
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, CancellationToken);
}

void SatoriApi::GetExperiments(
	const FSatoriApiConfig& Config,
	FSatoriSessionPtr Session,
	const TArray<FString>& Names,
	const TArray<FString>& Labels,
	TFunction<void(const FSatoriExperimentList&)> OnSuccess,
	TFunction<void(const FSatoriError&)> OnError,
	FSatoriCancellationTokenPtr CancellationToken)
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

	ESatoriRequestAuth AuthType = ESatoriRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, AuthType, Session, TEXT(""),
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FSatoriExperimentList Result = FSatoriExperimentList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, CancellationToken);
}

void SatoriApi::GetFlagOverrides(
	const FSatoriApiConfig& Config,
	FSatoriSessionPtr Session,
	const TArray<FString>& Names,
	const TArray<FString>& Labels,
	TFunction<void(const FSatoriFlagOverrideList&)> OnSuccess,
	TFunction<void(const FSatoriError&)> OnError,
	FSatoriCancellationTokenPtr CancellationToken)
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

	ESatoriRequestAuth AuthType = ESatoriRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, AuthType, Session, TEXT(""),
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FSatoriFlagOverrideList Result = FSatoriFlagOverrideList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, CancellationToken);
}

void SatoriApi::GetFlags(
	const FSatoriApiConfig& Config,
	FSatoriSessionPtr Session,
	const TArray<FString>& Names,
	const TArray<FString>& Labels,
	TFunction<void(const FSatoriFlagList&)> OnSuccess,
	TFunction<void(const FSatoriError&)> OnError,
	FSatoriCancellationTokenPtr CancellationToken)
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

	ESatoriRequestAuth AuthType = ESatoriRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, AuthType, Session, TEXT(""),
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FSatoriFlagList Result = FSatoriFlagList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, CancellationToken);
}

void SatoriApi::GetLiveEvents(
	const FSatoriApiConfig& Config,
	FSatoriSessionPtr Session,
	const TArray<FString>& Names,
	const TArray<FString>& Labels,
	int32 PastRunCount,
	int32 FutureRunCount,
	int64 StartTimeSec,
	int64 EndTimeSec,
	TFunction<void(const FSatoriLiveEventList&)> OnSuccess,
	TFunction<void(const FSatoriError&)> OnError,
	FSatoriCancellationTokenPtr CancellationToken)
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

	ESatoriRequestAuth AuthType = ESatoriRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, AuthType, Session, TEXT(""),
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FSatoriLiveEventList Result = FSatoriLiveEventList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, CancellationToken);
}

void SatoriApi::JoinLiveEvent(
	const FSatoriApiConfig& Config,
	FSatoriSessionPtr Session,
	FString Id,
	TFunction<void()> OnSuccess,
	TFunction<void(const FSatoriError&)> OnError,
	FSatoriCancellationTokenPtr CancellationToken)
{
	FString Endpoint = TEXT("/v1/live-event/{id}/participation");
	Endpoint = Endpoint.Replace(TEXT("{id}"), *Id);
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ESatoriRequestAuth AuthType = ESatoriRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("POST"), Body, AuthType, Session, TEXT(""),
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, CancellationToken);
}

void SatoriApi::Healthcheck(
	const FSatoriApiConfig& Config,
	FSatoriSessionPtr Session,
	TFunction<void()> OnSuccess,
	TFunction<void(const FSatoriError&)> OnError,
	FSatoriCancellationTokenPtr CancellationToken)
{
	FString Endpoint = TEXT("/healthcheck");

	ESatoriRequestAuth AuthType = ESatoriRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, AuthType, Session, TEXT(""),
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, CancellationToken);
}

void SatoriApi::Identify(
	const FSatoriApiConfig& Config,
	FSatoriSessionPtr Session,
	FString Id,
	const TMap<FString, FString>& Default,
	const TMap<FString, FString>& Custom,
	TFunction<void(const FSatoriSession&)> OnSuccess,
	TFunction<void(const FSatoriError&)> OnError,
	FSatoriCancellationTokenPtr CancellationToken)
{
	FString Endpoint = TEXT("/v1/identify");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ESatoriRequestAuth AuthType = ESatoriRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
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

	MakeRequest(Config, Endpoint, TEXT("PUT"), Body, AuthType, Session, TEXT(""),
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FSatoriSession Result = FSatoriSession::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, CancellationToken);
}

void SatoriApi::ListProperties(
	const FSatoriApiConfig& Config,
	FSatoriSessionPtr Session,
	TFunction<void(const FSatoriProperties&)> OnSuccess,
	TFunction<void(const FSatoriError&)> OnError,
	FSatoriCancellationTokenPtr CancellationToken)
{
	FString Endpoint = TEXT("/v1/properties");

	ESatoriRequestAuth AuthType = ESatoriRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, AuthType, Session, TEXT(""),
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FSatoriProperties Result = FSatoriProperties::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, CancellationToken);
}

void SatoriApi::Readycheck(
	const FSatoriApiConfig& Config,
	FSatoriSessionPtr Session,
	TFunction<void()> OnSuccess,
	TFunction<void(const FSatoriError&)> OnError,
	FSatoriCancellationTokenPtr CancellationToken)
{
	FString Endpoint = TEXT("/readycheck");

	ESatoriRequestAuth AuthType = ESatoriRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, AuthType, Session, TEXT(""),
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, CancellationToken);
}

void SatoriApi::UpdateProperties(
	const FSatoriApiConfig& Config,
	FSatoriSessionPtr Session,
	bool Recompute,
	const TMap<FString, FString>& Default,
	const TMap<FString, FString>& Custom,
	TFunction<void()> OnSuccess,
	TFunction<void(const FSatoriError&)> OnError,
	FSatoriCancellationTokenPtr CancellationToken)
{
	FString Endpoint = TEXT("/v1/properties");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ESatoriRequestAuth AuthType = ESatoriRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
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

	MakeRequest(Config, Endpoint, TEXT("PUT"), Body, AuthType, Session, TEXT(""),
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, CancellationToken);
}

void SatoriApi::GetMessageList(
	const FSatoriApiConfig& Config,
	FSatoriSessionPtr Session,
	int32 Limit,
	bool Forward,
	FString Cursor,
	const TArray<FString>& MessageIds,
	TFunction<void(const FSatoriGetMessageListResponse&)> OnSuccess,
	TFunction<void(const FSatoriError&)> OnError,
	FSatoriCancellationTokenPtr CancellationToken)
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

	ESatoriRequestAuth AuthType = ESatoriRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("GET"), Body, AuthType, Session, TEXT(""),
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			FSatoriGetMessageListResponse Result = FSatoriGetMessageListResponse::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError, CancellationToken);
}

void SatoriApi::UpdateMessage(
	const FSatoriApiConfig& Config,
	FSatoriSessionPtr Session,
	FString Id,
	int64 ReadTime,
	int64 ConsumeTime,
	TFunction<void()> OnSuccess,
	TFunction<void(const FSatoriError&)> OnError,
	FSatoriCancellationTokenPtr CancellationToken)
{
	FString Endpoint = TEXT("/v1/message/{id}");
	Endpoint = Endpoint.Replace(TEXT("{id}"), *Id);
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ESatoriRequestAuth AuthType = ESatoriRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();
	if (!Id.IsEmpty())
	{
		Body->SetStringField(TEXT("id"), Id);
	}
	Body->SetNumberField(TEXT("read_time"), ReadTime);
	Body->SetNumberField(TEXT("consume_time"), ConsumeTime);

	MakeRequest(Config, Endpoint, TEXT("PUT"), Body, AuthType, Session, TEXT(""),
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, CancellationToken);
}

void SatoriApi::DeleteMessage(
	const FSatoriApiConfig& Config,
	FSatoriSessionPtr Session,
	FString Id,
	TFunction<void()> OnSuccess,
	TFunction<void(const FSatoriError&)> OnError,
	FSatoriCancellationTokenPtr CancellationToken)
{
	FString Endpoint = TEXT("/v1/message/{id}");
	Endpoint = Endpoint.Replace(TEXT("{id}"), *Id);
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}

	ESatoriRequestAuth AuthType = ESatoriRequestAuth::Bearer;TSharedPtr<FJsonObject> Body;

	MakeRequest(Config, Endpoint, TEXT("DELETE"), Body, AuthType, Session, TEXT(""),
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError, CancellationToken);
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
