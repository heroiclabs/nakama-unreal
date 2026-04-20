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

#include "SatoriTypes.h"

FSatoriAuthenticateLogoutRequest FSatoriAuthenticateLogoutRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FSatoriAuthenticateLogoutRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("token")))
  {
      Result.Token = Json->GetStringField(TEXT("token"))
  }
  if (Json->HasField(TEXT("refresh_token")))
  {
      Result.RefreshToken = Json->GetStringField(TEXT("refresh_token"))
  }
  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FSatoriAuthenticateLogoutRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Token.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("token"), Token);
  }
  if (RefreshToken.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("refresh_token"), RefreshToken);
  }
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
      Result.RefreshToken = Json->GetStringField(TEXT("refresh_token"))
  }
  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FSatoriAuthenticateRefreshRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (RefreshToken.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("refresh_token"), RefreshToken);
  }
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
      Result.Id = Json->GetStringField(TEXT("id"))
  }
  if (Json->HasField(TEXT("no_session")))
  {
      Result.NoSession = Json->GetBoolField(TEXT("no_session"))
  }
  if (Json->HasField(TEXT("default")))
  {
      const TSharedPtr<FJsonObject>* MapObj;
      if (Json->TryGetObjectField(TEXT("default"), MapObj))
      {
        for (const auto& Pair : (*MapObj)->Values)
        {
          Result.Default_.Add(Pair.Key, Pair.Value->AsString());
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
  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FSatoriAuthenticateRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Id.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("id"), Id);
  }
  if (NoSession.None() == false)
  {
    Json->SetBoolField(TEXT("no_session"), NoSession);
  }
  if (Default_.Num() > 0)
  {
    TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
    for (const auto& Pair : Default_)
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
      Result.Id = Json->GetStringField(TEXT("id"))
  }
  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FSatoriDeleteMessageRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Id.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("id"), Id);
  }
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
      Result.Name = Json->GetStringField(TEXT("name"))
  }
  if (Json->HasField(TEXT("id")))
  {
      Result.Id = Json->GetStringField(TEXT("id"))
  }
  if (Json->HasField(TEXT("value")))
  {
      Result.Value = Json->GetStringField(TEXT("value"))
  }
  if (Json->HasField(TEXT("timestamp")))
  {
      Result.Timestamp = Json->GetStringField(TEXT("timestamp"))
  }
  if (Json->HasField(TEXT("identity_id")))
  {
      Result.IdentityId = Json->GetStringField(TEXT("identity_id"))
  }
  if (Json->HasField(TEXT("session_id")))
  {
      Result.SessionId = Json->GetStringField(TEXT("session_id"))
  }
  if (Json->HasField(TEXT("session_issued_at")))
  {
      Result.SessionIssuedAt = Json->GetNumberField(TEXT("session_issued_at"))
  }
  if (Json->HasField(TEXT("session_expires_at")))
  {
      Result.SessionExpiresAt = Json->GetNumberField(TEXT("session_expires_at"))
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
  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FSatoriEvent::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Name.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("name"), Name);
  }
  if (Id.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("id"), Id);
  }
  if (Value.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("value"), Value);
  }
  if (Timestamp.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("timestamp"), Timestamp);
  }
  if (IdentityId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("identity_id"), IdentityId);
  }
  if (SessionId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("session_id"), SessionId);
  }
  if (SessionIssuedAt.NonZero() == false)
  {
    Json->SetNumberField(TEXT("session_issued_at"), SessionIssuedAt);
  }
  if (SessionExpiresAt.NonZero() == false)
  {
    Json->SetNumberField(TEXT("session_expires_at"), SessionExpiresAt);
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
            Result.Events.Add(FSatoriTArray<FSatoriEvent>::FromJson(*ItemObj));
          }
        }
      }
  }
  Result.ParseTokens();
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
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("events"), Array);
  }
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
      Result.Name = Json->GetStringField(TEXT("name"))
  }
  if (Json->HasField(TEXT("value")))
  {
      Result.Value = Json->GetStringField(TEXT("value"))
  }
  if (Json->HasField(TEXT("labels")))
  {
      const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
      if (Json->TryGetArrayField(TEXT("labels"), ArrayPtr))
      {
        for (const auto& Item : *ArrayPtr)
        {
          Result.Labels.Add((Item->AsString()));
        }
      }
  }
  if (Json->HasField(TEXT("phase_name")))
  {
      Result.PhaseName = Json->GetStringField(TEXT("phase_name"))
  }
  if (Json->HasField(TEXT("phase_variant_name")))
  {
      Result.PhaseVariantName = Json->GetStringField(TEXT("phase_variant_name"))
  }
  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FSatoriExperiment::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Name.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("name"), Name);
  }
  if (Value.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("value"), Value);
  }
  if (Labels.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Labels)
    {
      Array.Add(MakeShared<String>(Item));
    }
    Json->SetArrayField(TEXT("labels"), Array);
  }
  if (PhaseName.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("phase_name"), PhaseName);
  }
  if (PhaseVariantName.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("phase_variant_name"), PhaseVariantName);
  }
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
            Result.Experiments.Add(FSatoriTArray<FSatoriExperiment>::FromJson(*ItemObj));
          }
        }
      }
  }
  Result.ParseTokens();
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
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("experiments"), Array);
  }
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
      Result.Type = static_cast<FSatoriValueChangeReasonType>(Json->GetIntegerField(TEXT("type")));
  }
  if (Json->HasField(TEXT("name")))
  {
      Result.Name = Json->GetStringField(TEXT("name"))
  }
  if (Json->HasField(TEXT("variant_name")))
  {
      Result.VariantName = Json->GetStringField(TEXT("variant_name"))
  }
  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FSatoriValueChangeReason::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Type.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("type"), Type.ToJson());
  }
  if (Name.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("name"), Name);
  }
  if (VariantName.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("variant_name"), VariantName);
  }
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
      Result.Name = Json->GetStringField(TEXT("name"))
  }
  if (Json->HasField(TEXT("value")))
  {
      Result.Value = Json->GetStringField(TEXT("value"))
  }
  if (Json->HasField(TEXT("condition_changed")))
  {
      Result.ConditionChanged = Json->GetBoolField(TEXT("condition_changed"))
  }
  if (Json->HasField(TEXT("change_reason")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("change_reason"), NestedObj))
      {
        Result.ChangeReason.Add(FSatoriFSatoriValueChangeReason::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("labels")))
  {
      const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
      if (Json->TryGetArrayField(TEXT("labels"), ArrayPtr))
      {
        for (const auto& Item : *ArrayPtr)
        {
          Result.Labels.Add((Item->AsString()));
        }
      }
  }
  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FSatoriFlag::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Name.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("name"), Name);
  }
  if (Value.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("value"), Value);
  }
  if (ConditionChanged.None() == false)
  {
    Json->SetBoolField(TEXT("condition_changed"), ConditionChanged);
  }
  if (ChangeReason.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("change_reason"), ChangeReason.ToJson());
  }
  if (Labels.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Labels)
    {
      Array.Add(MakeShared<String>(Item));
    }
    Json->SetArrayField(TEXT("labels"), Array);
  }
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
            Result.Flags.Add(FSatoriTArray<FSatoriFlag>::FromJson(*ItemObj));
          }
        }
      }
  }
  Result.ParseTokens();
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
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("flags"), Array);
  }
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
      Result.Type = static_cast<FSatoriFlagOverrideType>(Json->GetIntegerField(TEXT("type")));
  }
  if (Json->HasField(TEXT("name")))
  {
      Result.Name = Json->GetStringField(TEXT("name"))
  }
  if (Json->HasField(TEXT("variant_name")))
  {
      Result.VariantName = Json->GetStringField(TEXT("variant_name"))
  }
  if (Json->HasField(TEXT("value")))
  {
      Result.Value = Json->GetStringField(TEXT("value"))
  }
  if (Json->HasField(TEXT("create_time_sec")))
  {
      Result.CreateTimeSec = Json->GetNumberField(TEXT("create_time_sec"))
  }
  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FSatoriFlagOverrideValue::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Type.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("type"), Type.ToJson());
  }
  if (Name.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("name"), Name);
  }
  if (VariantName.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("variant_name"), VariantName);
  }
  if (Value.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("value"), Value);
  }
  if (CreateTimeSec.NonZero() == false)
  {
    Json->SetNumberField(TEXT("create_time_sec"), CreateTimeSec);
  }
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
      Result.FlagName = Json->GetStringField(TEXT("flag_name"))
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
            Result.Overrides.Add(FSatoriTArray<FSatoriFlagOverrideValue>::FromJson(*ItemObj));
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
          Result.Labels.Add((Item->AsString()));
        }
      }
  }
  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FSatoriFlagOverride::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (FlagName.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("flag_name"), FlagName);
  }
  if (Overrides.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Overrides)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("overrides"), Array);
  }
  if (Labels.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Labels)
    {
      Array.Add(MakeShared<String>(Item));
    }
    Json->SetArrayField(TEXT("labels"), Array);
  }
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
            Result.Flags.Add(FSatoriTArray<FSatoriFlagOverride>::FromJson(*ItemObj));
          }
        }
      }
  }
  Result.ParseTokens();
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
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("flags"), Array);
  }
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
          Result.Names.Add((Item->AsString()));
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
          Result.Labels.Add((Item->AsString()));
        }
      }
  }
  Result.ParseTokens();
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
      Array.Add(MakeShared<String>(Item));
    }
    Json->SetArrayField(TEXT("names"), Array);
  }
  if (Labels.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Labels)
    {
      Array.Add(MakeShared<String>(Item));
    }
    Json->SetArrayField(TEXT("labels"), Array);
  }
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
          Result.Names.Add((Item->AsString()));
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
          Result.Labels.Add((Item->AsString()));
        }
      }
  }
  Result.ParseTokens();
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
      Array.Add(MakeShared<String>(Item));
    }
    Json->SetArrayField(TEXT("names"), Array);
  }
  if (Labels.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Labels)
    {
      Array.Add(MakeShared<String>(Item));
    }
    Json->SetArrayField(TEXT("labels"), Array);
  }
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
          Result.Names.Add((Item->AsString()));
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
          Result.Labels.Add((Item->AsString()));
        }
      }
  }
  if (Json->HasField(TEXT("past_run_count")))
  {
      Result.PastRunCount = Json->GetIntegerField(TEXT("past_run_count"))
  }
  if (Json->HasField(TEXT("future_run_count")))
  {
      Result.FutureRunCount = Json->GetIntegerField(TEXT("future_run_count"))
  }
  if (Json->HasField(TEXT("start_time_sec")))
  {
      Result.StartTimeSec = Json->GetNumberField(TEXT("start_time_sec"))
  }
  if (Json->HasField(TEXT("end_time_sec")))
  {
      Result.EndTimeSec = Json->GetNumberField(TEXT("end_time_sec"))
  }
  Result.ParseTokens();
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
      Array.Add(MakeShared<String>(Item));
    }
    Json->SetArrayField(TEXT("names"), Array);
  }
  if (Labels.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Labels)
    {
      Array.Add(MakeShared<String>(Item));
    }
    Json->SetArrayField(TEXT("labels"), Array);
  }
  if (PastRunCount.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("past_run_count"), PastRunCount);
  }
  if (FutureRunCount.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("future_run_count"), FutureRunCount);
  }
  if (StartTimeSec.NonZero() == false)
  {
    Json->SetNumberField(TEXT("start_time_sec"), StartTimeSec);
  }
  if (EndTimeSec.NonZero() == false)
  {
    Json->SetNumberField(TEXT("end_time_sec"), EndTimeSec);
  }
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
      Result.ScheduleId = Json->GetStringField(TEXT("schedule_id"))
  }
  if (Json->HasField(TEXT("send_time")))
  {
      Result.SendTime = Json->GetNumberField(TEXT("send_time"))
  }
  if (Json->HasField(TEXT("create_time")))
  {
      Result.CreateTime = Json->GetNumberField(TEXT("create_time"))
  }
  if (Json->HasField(TEXT("update_time")))
  {
      Result.UpdateTime = Json->GetNumberField(TEXT("update_time"))
  }
  if (Json->HasField(TEXT("read_time")))
  {
      Result.ReadTime = Json->GetNumberField(TEXT("read_time"))
  }
  if (Json->HasField(TEXT("consume_time")))
  {
      Result.ConsumeTime = Json->GetNumberField(TEXT("consume_time"))
  }
  if (Json->HasField(TEXT("text")))
  {
      Result.Text = Json->GetStringField(TEXT("text"))
  }
  if (Json->HasField(TEXT("id")))
  {
      Result.Id = Json->GetStringField(TEXT("id"))
  }
  if (Json->HasField(TEXT("title")))
  {
      Result.Title = Json->GetStringField(TEXT("title"))
  }
  if (Json->HasField(TEXT("image_url")))
  {
      Result.ImageUrl = Json->GetStringField(TEXT("image_url"))
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
  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FSatoriMessage::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (ScheduleId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("schedule_id"), ScheduleId);
  }
  if (SendTime.NonZero() == false)
  {
    Json->SetNumberField(TEXT("send_time"), SendTime);
  }
  if (CreateTime.NonZero() == false)
  {
    Json->SetNumberField(TEXT("create_time"), CreateTime);
  }
  if (UpdateTime.NonZero() == false)
  {
    Json->SetNumberField(TEXT("update_time"), UpdateTime);
  }
  if (ReadTime.NonZero() == false)
  {
    Json->SetNumberField(TEXT("read_time"), ReadTime);
  }
  if (ConsumeTime.NonZero() == false)
  {
    Json->SetNumberField(TEXT("consume_time"), ConsumeTime);
  }
  if (Text.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("text"), Text);
  }
  if (Id.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("id"), Id);
  }
  if (Title.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("title"), Title);
  }
  if (ImageUrl.IsEmpty() == false)
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
      Result.Limit = Json->GetIntegerField(TEXT("limit"))
  }
  if (Json->HasField(TEXT("forward")))
  {
      Result.Forward = Json->GetBoolField(TEXT("forward"))
  }
  if (Json->HasField(TEXT("cursor")))
  {
      Result.Cursor = Json->GetStringField(TEXT("cursor"))
  }
  if (Json->HasField(TEXT("message_ids")))
  {
      const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
      if (Json->TryGetArrayField(TEXT("message_ids"), ArrayPtr))
      {
        for (const auto& Item : *ArrayPtr)
        {
          Result.MessageIds.Add((Item->AsString()));
        }
      }
  }
  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FSatoriGetMessageListRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Limit.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("limit"), Limit);
  }
  if (Forward.None() == false)
  {
    Json->SetBoolField(TEXT("forward"), Forward);
  }
  if (Cursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("cursor"), Cursor);
  }
  if (MessageIds.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : MessageIds)
    {
      Array.Add(MakeShared<String>(Item));
    }
    Json->SetArrayField(TEXT("message_ids"), Array);
  }
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
            Result.Messages.Add(FSatoriTArray<FSatoriMessage>::FromJson(*ItemObj));
          }
        }
      }
  }
  if (Json->HasField(TEXT("next_cursor")))
  {
      Result.NextCursor = Json->GetStringField(TEXT("next_cursor"))
  }
  if (Json->HasField(TEXT("prev_cursor")))
  {
      Result.PrevCursor = Json->GetStringField(TEXT("prev_cursor"))
  }
  if (Json->HasField(TEXT("cacheable_cursor")))
  {
      Result.CacheableCursor = Json->GetStringField(TEXT("cacheable_cursor"))
  }
  Result.ParseTokens();
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
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("messages"), Array);
  }
  if (NextCursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("next_cursor"), NextCursor);
  }
  if (PrevCursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("prev_cursor"), PrevCursor);
  }
  if (CacheableCursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("cacheable_cursor"), CacheableCursor);
  }
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
      Result.Id = Json->GetStringField(TEXT("id"))
  }
  if (Json->HasField(TEXT("default")))
  {
      const TSharedPtr<FJsonObject>* MapObj;
      if (Json->TryGetObjectField(TEXT("default"), MapObj))
      {
        for (const auto& Pair : (*MapObj)->Values)
        {
          Result.Default_.Add(Pair.Key, Pair.Value->AsString());
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
  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FSatoriIdentifyRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Id.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("id"), Id);
  }
  if (Default_.Num() > 0)
  {
    TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
    for (const auto& Pair : Default_)
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
      Result.Id = Json->GetStringField(TEXT("id"))
  }
  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FSatoriJoinLiveEventRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Id.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("id"), Id);
  }
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
      Result.Name = Json->GetStringField(TEXT("name"))
  }
  if (Json->HasField(TEXT("description")))
  {
      Result.Description = Json->GetStringField(TEXT("description"))
  }
  if (Json->HasField(TEXT("value")))
  {
      Result.Value = Json->GetStringField(TEXT("value"))
  }
  if (Json->HasField(TEXT("active_start_time_sec")))
  {
      Result.ActiveStartTimeSec = Json->GetNumberField(TEXT("active_start_time_sec"))
  }
  if (Json->HasField(TEXT("active_end_time_sec")))
  {
      Result.ActiveEndTimeSec = Json->GetNumberField(TEXT("active_end_time_sec"))
  }
  if (Json->HasField(TEXT("id")))
  {
      Result.Id = Json->GetStringField(TEXT("id"))
  }
  if (Json->HasField(TEXT("start_time_sec")))
  {
      Result.StartTimeSec = Json->GetNumberField(TEXT("start_time_sec"))
  }
  if (Json->HasField(TEXT("end_time_sec")))
  {
      Result.EndTimeSec = Json->GetNumberField(TEXT("end_time_sec"))
  }
  if (Json->HasField(TEXT("duration_sec")))
  {
      Result.DurationSec = Json->GetNumberField(TEXT("duration_sec"))
  }
  if (Json->HasField(TEXT("reset_cron")))
  {
      Result.ResetCron = Json->GetStringField(TEXT("reset_cron"))
  }
  if (Json->HasField(TEXT("status")))
  {
      Result.Status = static_cast<FSatoriLiveEventStatus>(Json->GetIntegerField(TEXT("status")));
  }
  if (Json->HasField(TEXT("labels")))
  {
      const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
      if (Json->TryGetArrayField(TEXT("labels"), ArrayPtr))
      {
        for (const auto& Item : *ArrayPtr)
        {
          Result.Labels.Add((Item->AsString()));
        }
      }
  }
  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FSatoriLiveEvent::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Name.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("name"), Name);
  }
  if (Description.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("description"), Description);
  }
  if (Value.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("value"), Value);
  }
  if (ActiveStartTimeSec.NonZero() == false)
  {
    Json->SetNumberField(TEXT("active_start_time_sec"), ActiveStartTimeSec);
  }
  if (ActiveEndTimeSec.NonZero() == false)
  {
    Json->SetNumberField(TEXT("active_end_time_sec"), ActiveEndTimeSec);
  }
  if (Id.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("id"), Id);
  }
  if (StartTimeSec.NonZero() == false)
  {
    Json->SetNumberField(TEXT("start_time_sec"), StartTimeSec);
  }
  if (EndTimeSec.NonZero() == false)
  {
    Json->SetNumberField(TEXT("end_time_sec"), EndTimeSec);
  }
  if (DurationSec.NonZero() == false)
  {
    Json->SetNumberField(TEXT("duration_sec"), DurationSec);
  }
  if (ResetCron.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("reset_cron"), ResetCron);
  }
  if (Status.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("status"), Status.ToJson());
  }
  if (Labels.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Labels)
    {
      Array.Add(MakeShared<String>(Item));
    }
    Json->SetArrayField(TEXT("labels"), Array);
  }
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
            Result.LiveEvents.Add(FSatoriTArray<FSatoriLiveEvent>::FromJson(*ItemObj));
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
            Result.ExplicitJoinLiveEvents.Add(FSatoriTArray<FSatoriLiveEvent>::FromJson(*ItemObj));
          }
        }
      }
  }
  Result.ParseTokens();
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
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("live_events"), Array);
  }
  if (ExplicitJoinLiveEvents.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : ExplicitJoinLiveEvents)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("explicit_join_live_events"), Array);
  }
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
          Result.Default_.Add(Pair.Key, Pair.Value->AsString());
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
  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FSatoriProperties::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Default_.Num() > 0)
  {
    TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
    for (const auto& Pair : Default_)
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
      Result.Recompute = Json->GetBoolField(TEXT("recompute"))
  }
  if (Json->HasField(TEXT("default")))
  {
      const TSharedPtr<FJsonObject>* MapObj;
      if (Json->TryGetObjectField(TEXT("default"), MapObj))
      {
        for (const auto& Pair : (*MapObj)->Values)
        {
          Result.Default_.Add(Pair.Key, Pair.Value->AsString());
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
  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FSatoriUpdatePropertiesRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Recompute.None() == false)
  {
    Json->SetBoolField(TEXT("recompute"), Recompute);
  }
  if (Default_.Num() > 0)
  {
    TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
    for (const auto& Pair : Default_)
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
      Result.Id = Json->GetStringField(TEXT("id"))
  }
  if (Json->HasField(TEXT("read_time")))
  {
      Result.ReadTime = Json->GetNumberField(TEXT("read_time"))
  }
  if (Json->HasField(TEXT("consume_time")))
  {
      Result.ConsumeTime = Json->GetNumberField(TEXT("consume_time"))
  }
  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FSatoriUpdateMessageRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Id.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("id"), Id);
  }
  if (ReadTime.NonZero() == false)
  {
    Json->SetNumberField(TEXT("read_time"), ReadTime);
  }
  if (ConsumeTime.NonZero() == false)
  {
    Json->SetNumberField(TEXT("consume_time"), ConsumeTime);
  }
}

