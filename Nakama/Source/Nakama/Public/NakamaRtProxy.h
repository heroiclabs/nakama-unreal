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

#pragma once

#include "CoreMinimal.h"
#include "NakamaRt.h"
#include "NakamaRtProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnWebSocketConnected, const FNakamaWebSocketConnectionResult&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FDelegateOnWebSocketClosed, int32, StatusCode, const FString&, Reason, bool, WasClean);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDelegateOnMessageError, EWebSocketMessageError, ErrorType, const FString&, Message);

//
// Delegates for event callbacks (dynamic = BlueprintAssignable; native = C++ AddLambda)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnChannelMessage, const FNakamaRtChannelMessage&, Data);
DECLARE_MULTICAST_DELEGATE_OneParam(FNativeDelegateOnChannelMessage, const FNakamaRtChannelMessage&);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnChannelPresenceEvent, const FNakamaRtChannelPresenceEvent&, Data);
DECLARE_MULTICAST_DELEGATE_OneParam(FNativeDelegateOnChannelPresenceEvent, const FNakamaRtChannelPresenceEvent&);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnMatchData, const FNakamaRtMatchData&, Data);
DECLARE_MULTICAST_DELEGATE_OneParam(FNativeDelegateOnMatchData, const FNakamaRtMatchData&);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnMatchPresenceEvent, const FNakamaRtMatchPresenceEvent&, Data);
DECLARE_MULTICAST_DELEGATE_OneParam(FNativeDelegateOnMatchPresenceEvent, const FNakamaRtMatchPresenceEvent&);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnMatchmakerMatched, const FNakamaRtMatchmakerMatched&, Data);
DECLARE_MULTICAST_DELEGATE_OneParam(FNativeDelegateOnMatchmakerMatched, const FNakamaRtMatchmakerMatched&);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnNotifications, const FNakamaRtNotifications&, Data);
DECLARE_MULTICAST_DELEGATE_OneParam(FNativeDelegateOnNotifications, const FNakamaRtNotifications&);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnPartyLeader, const FNakamaRtPartyLeader&, Data);
DECLARE_MULTICAST_DELEGATE_OneParam(FNativeDelegateOnPartyLeader, const FNakamaRtPartyLeader&);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnPartyJoinRequest, const FNakamaRtPartyJoinRequest&, Data);
DECLARE_MULTICAST_DELEGATE_OneParam(FNativeDelegateOnPartyJoinRequest, const FNakamaRtPartyJoinRequest&);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnPartyData, const FNakamaRtPartyData&, Data);
DECLARE_MULTICAST_DELEGATE_OneParam(FNativeDelegateOnPartyData, const FNakamaRtPartyData&);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnPartyPresenceEvent, const FNakamaRtPartyPresenceEvent&, Data);
DECLARE_MULTICAST_DELEGATE_OneParam(FNativeDelegateOnPartyPresenceEvent, const FNakamaRtPartyPresenceEvent&);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnStatusPresenceEvent, const FNakamaRtStatusPresenceEvent&, Data);
DECLARE_MULTICAST_DELEGATE_OneParam(FNativeDelegateOnStatusPresenceEvent, const FNakamaRtStatusPresenceEvent&);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnStreamData, const FNakamaRtStreamData&, Data);
DECLARE_MULTICAST_DELEGATE_OneParam(FNativeDelegateOnStreamData, const FNakamaRtStreamData&);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnStreamPresenceEvent, const FNakamaRtStreamPresenceEvent&, Data);
DECLARE_MULTICAST_DELEGATE_OneParam(FNativeDelegateOnStreamPresenceEvent, const FNakamaRtStreamPresenceEvent&);

UCLASS(BlueprintType)
class NAKAMA_API UNakamaRtProxy : public UObject
{
  GENERATED_BODY()

public:
  UPROPERTY(BlueprintReadonly, Category = "Nakama|Realtime")
  FNakamaRtConnectionHandle ConnectionHandle;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnWebSocketConnected OnConnected;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnWebSocketClosed OnClosed;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnMessageError OnMessageError;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnChannelMessage OnChannelMessage;

  FNativeDelegateOnChannelMessage OnChannelMessageNative;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnChannelPresenceEvent OnChannelPresenceEvent;

  FNativeDelegateOnChannelPresenceEvent OnChannelPresenceEventNative;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnMatchData OnMatchData;

  FNativeDelegateOnMatchData OnMatchDataNative;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnMatchPresenceEvent OnMatchPresenceEvent;

  FNativeDelegateOnMatchPresenceEvent OnMatchPresenceEventNative;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnMatchmakerMatched OnMatchmakerMatched;

  FNativeDelegateOnMatchmakerMatched OnMatchmakerMatchedNative;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnNotifications OnNotifications;

  FNativeDelegateOnNotifications OnNotificationsNative;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnPartyLeader OnPartyLeader;

  FNativeDelegateOnPartyLeader OnPartyLeaderNative;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnPartyJoinRequest OnPartyJoinRequest;

  FNativeDelegateOnPartyJoinRequest OnPartyJoinRequestNative;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnPartyData OnPartyData;

  FNativeDelegateOnPartyData OnPartyDataNative;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnPartyPresenceEvent OnPartyPresenceEvent;

  FNativeDelegateOnPartyPresenceEvent OnPartyPresenceEventNative;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnStatusPresenceEvent OnStatusPresenceEvent;

  FNativeDelegateOnStatusPresenceEvent OnStatusPresenceEventNative;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnStreamData OnStreamData;

  FNativeDelegateOnStreamData OnStreamDataNative;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnStreamPresenceEvent OnStreamPresenceEvent;

  FNativeDelegateOnStreamPresenceEvent OnStreamPresenceEventNative;

  UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime")
  static UNakamaRtProxy* CreateAndSetupNakamaRtConnection(const FNakamaWebSocketConnectionParams& Params);

  UFUNCTION(BlueprintCallable)
  int32 GetPendingRequestCount()
  {
    if (!ConnectionHandle.Connection.IsValid())
    {
      return 0;
    }
    return ConnectionHandle.Connection->GetPendingRequestCount();
  }
};

NAKAMA_API void SetupRtEventHandlers(const TSharedPtr<FNakamaRtConnection>& Connection, UNakamaRtProxy* Proxy);
NAKAMA_API void HandleServerEvent(UNakamaRtProxy* Proxy, const TSharedPtr<FJsonObject>& Envelope);
