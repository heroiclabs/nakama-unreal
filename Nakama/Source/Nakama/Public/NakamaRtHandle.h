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

#pragma once

#include "CoreMinimal.h"
#include "NakamaRt.h"
#include "NakamaRtHandle.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnWebSocketConnectCompleted, const FNakamaWebSocketConnectionResult&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FDelegateOnWebSocketClosed, int32, StatusCode, const FString&, Reason, bool, WasClean);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDelegateOnMessageError, EWebSocketMessageError, ErrorType, const FString&, Message);

//
// Delegates for event callbacks (dynamic = BlueprintAssignable; native = C++ AddLambda)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnChannelMessage, const FNakamaChannelMessage&, Data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnChannelPresenceEvent, const FNakamaRtChannelPresenceEvent&, Data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnMatchData, const FNakamaRtMatchData&, Data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnMatchPresenceEvent, const FNakamaRtMatchPresenceEvent&, Data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnMatchmakerMatched, const FNakamaRtMatchmakerMatched&, Data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnNotifications, const FNakamaRtNotifications&, Data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnPartyLeader, const FNakamaRtPartyLeader&, Data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnPartyJoinRequest, const FNakamaRtPartyJoinRequest&, Data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnPartyData, const FNakamaRtPartyData&, Data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnPartyPresenceEvent, const FNakamaRtPartyPresenceEvent&, Data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnStatusPresenceEvent, const FNakamaRtStatusPresenceEvent&, Data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnStreamData, const FNakamaRtStreamData&, Data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnStreamPresenceEvent, const FNakamaRtStreamPresenceEvent&, Data);

UCLASS(BlueprintType)
class NAKAMA_API UNakamaRtHandle : public UObject
{
  GENERATED_BODY()

public:
  TSharedPtr<FNakamaRtConnection> Connection;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnWebSocketConnectCompleted ConnectCompleted;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnWebSocketClosed Closed;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnMessageError MessageError;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnChannelMessage ChannelMessage;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnChannelPresenceEvent ChannelPresenceEvent;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnMatchData MatchData;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnMatchPresenceEvent MatchPresenceEvent;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnMatchmakerMatched MatchmakerMatched;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnNotifications Notifications;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnPartyLeader PartyLeader;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnPartyJoinRequest PartyJoinRequest;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnPartyData PartyData;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnPartyPresenceEvent PartyPresenceEvent;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnStatusPresenceEvent StatusPresenceEvent;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnStreamData StreamData;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnStreamPresenceEvent StreamPresenceEvent;

  UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime")
  static UNakamaRtHandle* CreateNakamaRtConnection();

  UFUNCTION(BlueprintCallable)
  void Connect(const FNakamaWebSocketConnectionParams& Params);

  UFUNCTION(BlueprintCallable)
  int32 GetPendingRequestCount()
  {
    if (!Connection.IsValid())
    {
      return 0;
    }
    return Connection->GetPendingRequestCount();
  }

private:
  void SetupRtEventHandlers();
};

