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




#include "Satori.gen.h"
#include "SatoriHttpHelper.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "Misc/Base64.h"



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
  if (Token.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("token"), Token);
  }
  if (RefreshToken.IsEmpty() == false)
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
  if (RefreshToken.IsEmpty() == false)
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
  if (Id.IsEmpty() == false)
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
    FDateTime::ParseIso8601(*Json->GetStringField(TEXT("timestamp")), Result.Timestamp);
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
    Result.SessionIssuedAt = Json->GetNumberField(TEXT("session_issued_at"));
  }
  if (Json->HasField(TEXT("session_expires_at")))
  {
    Result.SessionExpiresAt = Json->GetNumberField(TEXT("session_expires_at"));
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
  Json->SetStringField(TEXT("timestamp"), Timestamp.ToIso8601());
  if (IdentityId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("identity_id"), IdentityId);
  }
  if (SessionId.IsEmpty() == false)
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
  if (Json->HasField(TEXT("flag_names")))
  {
    const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
    if (Json->TryGetArrayField(TEXT("flag_names"), ArrayPtr))
    {
      for (const auto& Item : *ArrayPtr)
      {
        Result.FlagNames.Add(Item->AsString());
      }
    }
  }
  return Result;
}

TSharedPtr<FJsonObject> FSatoriExperiment::ToJson() const
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
      Array.Add(MakeShared<FJsonValueString>(Item));
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
  if (FlagNames.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : FlagNames)
    {
      Array.Add(MakeShared<FJsonValueString>(Item));
    }
    Json->SetArrayField(TEXT("flag_names"), Array);
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
FSatoriFlagValueChangeReason FSatoriFlagValueChangeReason::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FSatoriFlagValueChangeReason Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("type")))
  {
    Result.Type = static_cast<ESatoriFlagValueChangeReasonType>(Json->GetNumberField(TEXT("type")));
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

TSharedPtr<FJsonObject> FSatoriFlagValueChangeReason::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  Json->SetNumberField(TEXT("type"), static_cast<int32>(Type));
  if (Name.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("name"), Name);
  }
  if (VariantName.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("variant_name"), VariantName);
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
      Result.ChangeReason = FSatoriFlagValueChangeReason::FromJson(*NestedObj);
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
  if (Name.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("name"), Name);
  }
  if (Value.IsEmpty() == false)
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
FSatoriFlagOverrideValue FSatoriFlagOverrideValue::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FSatoriFlagOverrideValue Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("type")))
  {
    Result.Type = static_cast<ESatoriFlagOverrideType>(Json->GetNumberField(TEXT("type")));
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
    Result.CreateTimeSec = Json->GetNumberField(TEXT("create_time_sec"));
  }
  return Result;
}

TSharedPtr<FJsonObject> FSatoriFlagOverrideValue::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  Json->SetNumberField(TEXT("type"), static_cast<int32>(Type));
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
  Json->SetNumberField(TEXT("create_time_sec"), CreateTimeSec);
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

TSharedPtr<FJsonObject> FSatoriFlagOverride::ToJson() const
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
    Result.PastRunCount = Json->GetNumberField(TEXT("past_run_count"));
  }
  if (Json->HasField(TEXT("future_run_count")))
  {
    Result.FutureRunCount = Json->GetNumberField(TEXT("future_run_count"));
  }
  if (Json->HasField(TEXT("start_time_sec")))
  {
    Result.StartTimeSec = Json->GetNumberField(TEXT("start_time_sec"));
  }
  if (Json->HasField(TEXT("end_time_sec")))
  {
    Result.EndTimeSec = Json->GetNumberField(TEXT("end_time_sec"));
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
  if (Id.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("id"), Id);
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
  if (Id.IsEmpty() == false)
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
    Result.ActiveStartTimeSec = Json->GetNumberField(TEXT("active_start_time_sec"));
  }
  if (Json->HasField(TEXT("active_end_time_sec")))
  {
    Result.ActiveEndTimeSec = Json->GetNumberField(TEXT("active_end_time_sec"));
  }
  if (Json->HasField(TEXT("id")))
  {
    Result.Id = Json->GetStringField(TEXT("id"));
  }
  if (Json->HasField(TEXT("start_time_sec")))
  {
    Result.StartTimeSec = Json->GetNumberField(TEXT("start_time_sec"));
  }
  if (Json->HasField(TEXT("end_time_sec")))
  {
    Result.EndTimeSec = Json->GetNumberField(TEXT("end_time_sec"));
  }
  if (Json->HasField(TEXT("duration_sec")))
  {
    Result.DurationSec = Json->GetNumberField(TEXT("duration_sec"));
  }
  if (Json->HasField(TEXT("reset_cron")))
  {
    Result.ResetCron = Json->GetStringField(TEXT("reset_cron"));
  }
  if (Json->HasField(TEXT("status")))
  {
    Result.Status = static_cast<ESatoriLiveEventStatus>(Json->GetNumberField(TEXT("status")));
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
  if (Json->HasField(TEXT("flag_names")))
  {
    const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
    if (Json->TryGetArrayField(TEXT("flag_names"), ArrayPtr))
    {
      for (const auto& Item : *ArrayPtr)
      {
        Result.FlagNames.Add(Item->AsString());
      }
    }
  }
  return Result;
}

TSharedPtr<FJsonObject> FSatoriLiveEvent::ToJson() const
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
  Json->SetNumberField(TEXT("active_start_time_sec"), ActiveStartTimeSec);
  Json->SetNumberField(TEXT("active_end_time_sec"), ActiveEndTimeSec);
  if (Id.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("id"), Id);
  }
  Json->SetNumberField(TEXT("start_time_sec"), StartTimeSec);
  Json->SetNumberField(TEXT("end_time_sec"), EndTimeSec);
  Json->SetNumberField(TEXT("duration_sec"), DurationSec);
  if (ResetCron.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("reset_cron"), ResetCron);
  }
  Json->SetNumberField(TEXT("status"), static_cast<int32>(Status));
  if (Labels.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Labels)
    {
      Array.Add(MakeShared<FJsonValueString>(Item));
    }
    Json->SetArrayField(TEXT("labels"), Array);
  }
  if (FlagNames.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : FlagNames)
    {
      Array.Add(MakeShared<FJsonValueString>(Item));
    }
    Json->SetArrayField(TEXT("flag_names"), Array);
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
  if (Recompute.IsEmpty() == false)
  {
    Json->SetBoolField(TEXT("recompute"), Recompute.GetValue());
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
FSatoriGetMessageListRequest FSatoriGetMessageListRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FSatoriGetMessageListRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("limit")))
  {
    Result.Limit = Json->GetNumberField(TEXT("limit"));
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
  if (Cursor.IsEmpty() == false)
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
    Result.SendTime = Json->GetNumberField(TEXT("send_time"));
  }
  if (Json->HasField(TEXT("create_time")))
  {
    Result.CreateTime = Json->GetNumberField(TEXT("create_time"));
  }
  if (Json->HasField(TEXT("update_time")))
  {
    Result.UpdateTime = Json->GetNumberField(TEXT("update_time"));
  }
  if (Json->HasField(TEXT("read_time")))
  {
    Result.ReadTime = Json->GetNumberField(TEXT("read_time"));
  }
  if (Json->HasField(TEXT("consume_time")))
  {
    Result.ConsumeTime = Json->GetNumberField(TEXT("consume_time"));
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
  if (ScheduleId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("schedule_id"), ScheduleId);
  }
  Json->SetNumberField(TEXT("send_time"), SendTime);
  Json->SetNumberField(TEXT("create_time"), CreateTime);
  Json->SetNumberField(TEXT("update_time"), UpdateTime);
  Json->SetNumberField(TEXT("read_time"), ReadTime);
  Json->SetNumberField(TEXT("consume_time"), ConsumeTime);
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
    Result.ReadTime = Json->GetNumberField(TEXT("read_time"));
  }
  if (Json->HasField(TEXT("consume_time")))
  {
    Result.ConsumeTime = Json->GetNumberField(TEXT("consume_time"));
  }
  return Result;
}

TSharedPtr<FJsonObject> FSatoriUpdateMessageRequest::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Id.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("id"), Id);
  }
  Json->SetNumberField(TEXT("read_time"), ReadTime);
  Json->SetNumberField(TEXT("consume_time"), ConsumeTime);
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
  if (Id.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("id"), Id);
  }
  return Json;
}



FSatoriApiRequestModel SatoriInternal::BuildAuthenticateRequest (
  const FSatoriAuthenticateRequest& Params
)
{
  FSatoriApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v1/authenticate");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (whole message, minus path params)
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = SatoriHttpInternal::SerializeJsonToString(BodyJson);

  return Request;
}

FSatoriApiRequestModel SatoriInternal::BuildAuthenticateLogoutRequest (
  const FSatoriAuthenticateLogoutRequest& Params
)
{
  FSatoriApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v1/authenticate/logout");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (whole message, minus path params)
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = SatoriHttpInternal::SerializeJsonToString(BodyJson);

  return Request;
}

FSatoriApiRequestModel SatoriInternal::BuildAuthenticateRefreshRequest (
  const FSatoriAuthenticateRefreshRequest& Params
)
{
  FSatoriApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v1/authenticate/refresh");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (whole message, minus path params)
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = SatoriHttpInternal::SerializeJsonToString(BodyJson);

  return Request;
}

FSatoriApiRequestModel SatoriInternal::BuildDeleteIdentityRequest (
)
{
  FSatoriApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v1/identity");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("DELETE");

  return Request;
}

FSatoriApiRequestModel SatoriInternal::BuildEventRequest (
  const FSatoriEventRequest& Params
)
{
  FSatoriApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v1/event");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (whole message, minus path params)
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = SatoriHttpInternal::SerializeJsonToString(BodyJson);

  return Request;
}

FSatoriApiRequestModel SatoriInternal::BuildServerEventRequest (
  const FSatoriEventRequest& Params
)
{
  FSatoriApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v1/server-event");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (whole message, minus path params)
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = SatoriHttpInternal::SerializeJsonToString(BodyJson);

  return Request;
}

FSatoriApiRequestModel SatoriInternal::BuildGetExperimentsRequest (
  const FSatoriGetExperimentsRequest& Params
)
{
  FSatoriApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v1/experiment");

  //
  // Query params
  TArray<TPair<FString, FString>> QueryParams;
  for (const FString& Item : Params.Names)
  {
    QueryParams.Add({TEXT("names"), Item});
  }
  for (const FString& Item : Params.Labels)
  {
    QueryParams.Add({TEXT("labels"), Item});
  }
  Url += SatoriHttpInternal::BuildQueryString(QueryParams);
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("GET");

  return Request;
}

FSatoriApiRequestModel SatoriInternal::BuildGetFlagOverridesRequest (
  const FSatoriGetFlagsRequest& Params
)
{
  FSatoriApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v1/flag/override");

  //
  // Query params
  TArray<TPair<FString, FString>> QueryParams;
  for (const FString& Item : Params.Names)
  {
    QueryParams.Add({TEXT("names"), Item});
  }
  for (const FString& Item : Params.Labels)
  {
    QueryParams.Add({TEXT("labels"), Item});
  }
  Url += SatoriHttpInternal::BuildQueryString(QueryParams);
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("GET");

  return Request;
}

FSatoriApiRequestModel SatoriInternal::BuildGetFlagsRequest (
  const FSatoriGetFlagsRequest& Params
)
{
  FSatoriApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v1/flag");

  //
  // Query params
  TArray<TPair<FString, FString>> QueryParams;
  for (const FString& Item : Params.Names)
  {
    QueryParams.Add({TEXT("names"), Item});
  }
  for (const FString& Item : Params.Labels)
  {
    QueryParams.Add({TEXT("labels"), Item});
  }
  Url += SatoriHttpInternal::BuildQueryString(QueryParams);
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("GET");

  return Request;
}

FSatoriApiRequestModel SatoriInternal::BuildGetLiveEventsRequest (
  const FSatoriGetLiveEventsRequest& Params
)
{
  FSatoriApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v1/live-event");

  //
  // Query params
  TArray<TPair<FString, FString>> QueryParams;
  for (const FString& Item : Params.Names)
  {
    QueryParams.Add({TEXT("names"), Item});
  }
  for (const FString& Item : Params.Labels)
  {
    QueryParams.Add({TEXT("labels"), Item});
  }
  Url += SatoriHttpInternal::BuildQueryString(QueryParams);
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("GET");

  return Request;
}

FSatoriApiRequestModel SatoriInternal::BuildJoinLiveEventRequest (
  const FSatoriJoinLiveEventRequest& Params
)
{
  FSatoriApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v1/live-event/{id}/participation");
  Url = Url.Replace(TEXT("{id}"), *FGenericPlatformHttp::UrlEncode(Params.Id));
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  return Request;
}

FSatoriApiRequestModel SatoriInternal::BuildHealthcheckRequest (
)
{
  FSatoriApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/healthcheck");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("GET");

  return Request;
}

FSatoriApiRequestModel SatoriInternal::BuildIdentifyRequest (
  const FSatoriIdentifyRequest& Params
)
{
  FSatoriApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v1/identify");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("PUT");

  //
  // Body (whole message, minus path params)
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = SatoriHttpInternal::SerializeJsonToString(BodyJson);

  return Request;
}

FSatoriApiRequestModel SatoriInternal::BuildListPropertiesRequest (
)
{
  FSatoriApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v1/properties");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("GET");

  return Request;
}

FSatoriApiRequestModel SatoriInternal::BuildReadycheckRequest (
)
{
  FSatoriApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/readycheck");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("GET");

  return Request;
}

FSatoriApiRequestModel SatoriInternal::BuildUpdatePropertiesRequest (
  const FSatoriUpdatePropertiesRequest& Params
)
{
  FSatoriApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v1/properties");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("PUT");

  //
  // Body (whole message, minus path params)
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = SatoriHttpInternal::SerializeJsonToString(BodyJson);

  return Request;
}

FSatoriApiRequestModel SatoriInternal::BuildGetMessageListRequest (
  const FSatoriGetMessageListRequest& Params
)
{
  FSatoriApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v1/message");

  //
  // Query params
  TArray<TPair<FString, FString>> QueryParams;
  if (Params.Cursor.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("cursor"), Params.Cursor});
  }
  for (const FString& Item : Params.MessageIds)
  {
    QueryParams.Add({TEXT("message_ids"), Item});
  }
  Url += SatoriHttpInternal::BuildQueryString(QueryParams);
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("GET");

  return Request;
}

FSatoriApiRequestModel SatoriInternal::BuildUpdateMessageRequest (
  const FSatoriUpdateMessageRequest& Params
)
{
  FSatoriApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v1/message/{id}");
  Url = Url.Replace(TEXT("{id}"), *FGenericPlatformHttp::UrlEncode(Params.Id));
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("PUT");

  //
  // Body (whole message, minus path params)
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  if (BodyJson.IsValid())
  {
    BodyJson->RemoveField(TEXT("id"));
  }
  Request.Body = SatoriHttpInternal::SerializeJsonToString(BodyJson);

  return Request;
}

FSatoriApiRequestModel SatoriInternal::BuildDeleteMessageRequest (
  const FSatoriDeleteMessageRequest& Params
)
{
  FSatoriApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v1/message/{id}");
  Url = Url.Replace(TEXT("{id}"), *FGenericPlatformHttp::UrlEncode(Params.Id));
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("DELETE");

  return Request;
}
