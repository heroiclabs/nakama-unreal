// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NakamaRealtimeClient.h"
#include "UObject/NoExportTypes.h"
#include "NakamaRealtimeClientListener.generated.h"


/**
 * 
 */
UCLASS()
class NAKAMAUNREAL_API UNakamaRealtimeClientListener : public UObject
{
	GENERATED_BODY()

public:
    UNakamaRealtimeClientListener();

	UFUNCTION(BlueprintCallable, Category = "Nakama")
	static UNakamaRealtimeClientListener* CreateRealtimeClientListener();

	// These should be used when binding to the delegates
	void SetConnectCallback(const TFunction<void()>& Callback);
	void SetConnectionErrorCallback(const TFunction<void(const FNakamaRtError&)>& Callback);
	void SetDisconnectCallback(const TFunction<void(const FNakamaDisconnectInfo&)>& Callback);
	void SetErrorCallback(const TFunction<void(const FNakamaRtError&)>& Callback);
	void SetChannelMessageCallback(const TFunction<void(const FNakamaChannelMessage&)>& Callback);
	void SetChannelPresenceCallback(const TFunction<void(const FNakamaChannelPresenceEvent&)>& Callback);
	void SetMatchmakerMatchedCallback(const TFunction<void(const FNakamaMatchmakerMatched&)>& Callback);
	void SetMatchDataCallback(const TFunction<void(const FNakamaMatchData&)>& Callback);
	void SetMatchPresenceCallback(const TFunction<void(const FNakamaMatchPresenceEvent&)>& Callback);
	void SetNotificationsCallback(const TFunction<void(const FNakamaNotificationList&)>& Callback);
	void SetPartyCallback(const TFunction<void(const FNakamaParty&)>& Callback);
	void SetPartyCloseCallback(const TFunction<void(const FNakamaPartyClose&)>& Callback);
	void SetPartyDataCallback(const TFunction<void(const FNakamaPartyData&)>& Callback);
	void SetPartyJoinRequestCallback(const TFunction<void(const FNakamaPartyJoinRequest&)>& Callback);
	void SetPartyLeaderCallback(const TFunction<void(const FNakamaPartyLeader&)>& Callback);
	void SetPartyMatchmakerTicketCallback(const TFunction<void(const FNakamaPartyMatchmakerTicket&)>& Callback);
	void SetPartyPresenceCallback(const TFunction<void(const FNakamaPartyPresenceEvent&)>& Callback);
	void SetStatusPresenceCallback(const TFunction<void(const FNakamaStatusPresenceEvent&)>& Callback);
	void SetStreamPresenceCallback(const TFunction<void(const FNakamaStreamPresenceEvent&)>& Callback);
	void SetStreamDataCallback(const TFunction<void(const FNakamaStreamData&)>& Callback);

public:

	// These should be private, but has to be used by UNakamaRealtimeClient (so made them public)
    TFunction<void()> OnConnect;
	TFunction<void(const FNakamaRtError&)> OnConnectionError;
    TFunction<void(const FNakamaDisconnectInfo&)> OnDisconnect;
    TFunction<void(const FNakamaRtError&)> OnError;
    TFunction<void(const FNakamaChannelMessage&)> OnChannelMessage;
    TFunction<void(const FNakamaChannelPresenceEvent&)> OnChannelPresenceEvent;
    TFunction<void(const FNakamaMatchmakerMatched&)> OnMatchmakerMatched;
    TFunction<void(const FNakamaMatchPresenceEvent&)> OnMatchPresenceEvent;
    TFunction<void(const FNakamaMatchData&)> OnMatchData;
    TFunction<void(const FNakamaNotificationList&)> OnNotifications;
    TFunction<void(const FNakamaStatusPresenceEvent&)> OnStatusPresenceEvent;
    TFunction<void(const FNakamaStreamPresenceEvent&)> OnStreamPresenceEvent;
    TFunction<void(const FNakamaStreamData&)> OnStreamData;
    TFunction<void(const FNakamaParty&)> OnParty;
    TFunction<void(const FNakamaPartyClose&)> OnPartyClose;
    TFunction<void(const FNakamaPartyData&)> OnPartyData;
    TFunction<void(const FNakamaPartyJoinRequest&)> OnPartyJoinRequest;
    TFunction<void(const FNakamaPartyLeader&)> OnPartyLeader;
    TFunction<void(const FNakamaPartyMatchmakerTicket&)> OnPartyMatchmakerTicket;
    TFunction<void(const FNakamaPartyPresenceEvent&)> OnPartyPresenceEvent;
};
