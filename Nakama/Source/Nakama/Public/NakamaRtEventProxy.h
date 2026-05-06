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
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NakamaRtEventProxy.generated.h"

USTRUCT(BlueprintType)
struct FNakamaRtClientHandle
{
  GENERATED_BODY()

  TSharedPtr<Nakama::FNakamaRtClient> RtClientPtr;

  FNakamaRtClientHandle() : RtClientPtr(nullptr) {}
  explicit FNakamaRtClientHandle(TSharedPtr<Nakama::FNakamaRtClient> InPtr) : RtClientPtr(InPtr) {}
};

UCLASS()
class NAKAMA_API UNakamaRtClientHandleUtils : public UBlueprintFunctionLibrary
{
  GENERATED_BODY()

public:
  UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime", meta = (WorldContext = "WorldContextObject"))
  static FNakamaRtClientHandle CreateFNakamaRtClientHandle(UObject* WorldContextObject)
  {
    if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
    {
      UGameInstance* GI = World->GetGameInstance();
      
      TSharedPtr<Nakama::FNakamaRtClient> RtClient = MakeShared<Nakama::FNakamaRtClient>(GI);
      return FNakamaRtClientHandle(RtClient);
    }
    return FNakamaRtClientHandle(nullptr);
  }
};

//
// Delegates for event callbacks
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnChannelMessageDynamic, const FNakamaRtChannelMessage&, Data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnChannelPresenceEventDynamic, const FNakamaRtChannelPresenceEvent&, Data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnMatchDataDynamic, const FNakamaRtMatchData&, Data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnMatchPresenceEventDynamic, const FNakamaRtMatchPresenceEvent&, Data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnMatchmakerMatchedDynamic, const FNakamaRtMatchmakerMatched&, Data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnNotificationsDynamic, const FNakamaRtNotifications&, Data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnPartyLeaderDynamic, const FNakamaRtPartyLeader&, Data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnPartyJoinRequestDynamic, const FNakamaRtPartyJoinRequest&, Data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnPartyDataDynamic, const FNakamaRtPartyData&, Data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnPartyPresenceEventDynamic, const FNakamaRtPartyPresenceEvent&, Data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnStatusPresenceEventDynamic, const FNakamaRtStatusPresenceEvent&, Data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnStreamDataDynamic, const FNakamaRtStreamData&, Data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOnStreamPresenceEventDynamic, const FNakamaRtStreamPresenceEvent&, Data);

UCLASS(Blueprintable)
class NAKAMA_API UNakamaRtEventProxy : public UObject
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnChannelMessageDynamic OnChannelMessage;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnChannelPresenceEventDynamic OnChannelPresenceEvent;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnMatchDataDynamic OnMatchData;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnMatchPresenceEventDynamic OnMatchPresenceEvent;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnMatchmakerMatchedDynamic OnMatchmakerMatched;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnNotificationsDynamic OnNotifications;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnPartyLeaderDynamic OnPartyLeader;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnPartyJoinRequestDynamic OnPartyJoinRequest;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnPartyDataDynamic OnPartyData;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnPartyPresenceEventDynamic OnPartyPresenceEvent;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnStatusPresenceEventDynamic OnStatusPresenceEvent;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnStreamDataDynamic OnStreamData;

  UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
  FDelegateOnStreamPresenceEventDynamic OnStreamPresenceEvent;

  UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime")
  void Initialize(FNakamaRtClientHandle RtClientHandle)
  {
    if (RtClientHandle.RtClientPtr.IsValid())
    {
      RtClientHandle.RtClientPtr->OnChannelMessage.AddUObject(this, &UNakamaRtEventProxy::HandleOnChannelMessage);
      RtClientHandle.RtClientPtr->OnChannelPresenceEvent.AddUObject(this, &UNakamaRtEventProxy::HandleOnChannelPresenceEvent);
      RtClientHandle.RtClientPtr->OnMatchData.AddUObject(this, &UNakamaRtEventProxy::HandleOnMatchData);
      RtClientHandle.RtClientPtr->OnMatchPresenceEvent.AddUObject(this, &UNakamaRtEventProxy::HandleOnMatchPresenceEvent);
      RtClientHandle.RtClientPtr->OnMatchmakerMatched.AddUObject(this, &UNakamaRtEventProxy::HandleOnMatchmakerMatched);
      RtClientHandle.RtClientPtr->OnNotifications.AddUObject(this, &UNakamaRtEventProxy::HandleOnNotifications);
      RtClientHandle.RtClientPtr->OnPartyLeader.AddUObject(this, &UNakamaRtEventProxy::HandleOnPartyLeader);
      RtClientHandle.RtClientPtr->OnPartyJoinRequest.AddUObject(this, &UNakamaRtEventProxy::HandleOnPartyJoinRequest);
      RtClientHandle.RtClientPtr->OnPartyData.AddUObject(this, &UNakamaRtEventProxy::HandleOnPartyData);
      RtClientHandle.RtClientPtr->OnPartyPresenceEvent.AddUObject(this, &UNakamaRtEventProxy::HandleOnPartyPresenceEvent);
      RtClientHandle.RtClientPtr->OnStatusPresenceEvent.AddUObject(this, &UNakamaRtEventProxy::HandleOnStatusPresenceEvent);
      RtClientHandle.RtClientPtr->OnStreamData.AddUObject(this, &UNakamaRtEventProxy::HandleOnStreamData);
      RtClientHandle.RtClientPtr->OnStreamPresenceEvent.AddUObject(this, &UNakamaRtEventProxy::HandleOnStreamPresenceEvent);
    }
  }
  
private:

  UFUNCTION()
  void HandleOnChannelMessage(const FNakamaRtChannelMessage& Data)
  {
    OnChannelMessage.Broadcast(Data);
  }

  UFUNCTION()
  void HandleOnChannelPresenceEvent(const FNakamaRtChannelPresenceEvent& Data)
  {
    OnChannelPresenceEvent.Broadcast(Data);
  }

  UFUNCTION()
  void HandleOnMatchData(const FNakamaRtMatchData& Data)
  {
    OnMatchData.Broadcast(Data);
  }

  UFUNCTION()
  void HandleOnMatchPresenceEvent(const FNakamaRtMatchPresenceEvent& Data)
  {
    OnMatchPresenceEvent.Broadcast(Data);
  }

  UFUNCTION()
  void HandleOnMatchmakerMatched(const FNakamaRtMatchmakerMatched& Data)
  {
    OnMatchmakerMatched.Broadcast(Data);
  }

  UFUNCTION()
  void HandleOnNotifications(const FNakamaRtNotifications& Data)
  {
    OnNotifications.Broadcast(Data);
  }

  UFUNCTION()
  void HandleOnPartyLeader(const FNakamaRtPartyLeader& Data)
  {
    OnPartyLeader.Broadcast(Data);
  }

  UFUNCTION()
  void HandleOnPartyJoinRequest(const FNakamaRtPartyJoinRequest& Data)
  {
    OnPartyJoinRequest.Broadcast(Data);
  }

  UFUNCTION()
  void HandleOnPartyData(const FNakamaRtPartyData& Data)
  {
    OnPartyData.Broadcast(Data);
  }

  UFUNCTION()
  void HandleOnPartyPresenceEvent(const FNakamaRtPartyPresenceEvent& Data)
  {
    OnPartyPresenceEvent.Broadcast(Data);
  }

  UFUNCTION()
  void HandleOnStatusPresenceEvent(const FNakamaRtStatusPresenceEvent& Data)
  {
    OnStatusPresenceEvent.Broadcast(Data);
  }

  UFUNCTION()
  void HandleOnStreamData(const FNakamaRtStreamData& Data)
  {
    OnStreamData.Broadcast(Data);
  }

  UFUNCTION()
  void HandleOnStreamPresenceEvent(const FNakamaRtStreamPresenceEvent& Data)
  {
    OnStreamPresenceEvent.Broadcast(Data);
  }
};
