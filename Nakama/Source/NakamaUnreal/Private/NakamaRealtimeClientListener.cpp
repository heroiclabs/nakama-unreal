// Fill out your copyright notice in the Description page of Project Settings.


#include "NakamaRealtimeClientListener.h"

UNakamaRealtimeClientListener::UNakamaRealtimeClientListener()
{
    // Initialize the listener
}

UNakamaRealtimeClientListener* UNakamaRealtimeClientListener::CreateRealtimeClientListener()
{
    return NewObject<UNakamaRealtimeClientListener>();
}

void UNakamaRealtimeClientListener::SetConnectCallback(const TFunction<void()>& Callback)
{
    OnConnect = Callback;
}

void UNakamaRealtimeClientListener::SetConnectionErrorCallback(const TFunction<void(const FNakamaRtError&)>& Callback)
{
    OnConnectionError = Callback;
}

void UNakamaRealtimeClientListener::SetDisconnectCallback(const TFunction<void(const FNakamaDisconnectInfo&)>& Callback)
{
    OnDisconnect = Callback;
}

void UNakamaRealtimeClientListener::SetErrorCallback(const TFunction<void(const FNakamaRtError&)>& Callback)
{
    OnError = Callback;
}

void UNakamaRealtimeClientListener::SetChannelMessageCallback(const TFunction<void(const FNakamaChannelMessage&)>& Callback)
{
    OnChannelMessage = Callback;
}

void UNakamaRealtimeClientListener::SetChannelPresenceCallback(const TFunction<void(const FNakamaChannelPresenceEvent&)>& Callback)
{
    OnChannelPresenceEvent = Callback;
}

void UNakamaRealtimeClientListener::SetMatchmakerMatchedCallback(const TFunction<void(const FNakamaMatchmakerMatched&)>& Callback)
{
    OnMatchmakerMatched = Callback;
}

void UNakamaRealtimeClientListener::SetMatchDataCallback(const TFunction<void(const FNakamaMatchData&)>& Callback)
{
    OnMatchData = Callback;
}

void UNakamaRealtimeClientListener::SetMatchPresenceCallback(const TFunction<void(const FNakamaMatchPresenceEvent&)>& Callback)
{
    OnMatchPresenceEvent = Callback;
}

void UNakamaRealtimeClientListener::SetNotificationsCallback(const TFunction<void(const FNakamaNotificationList&)>& Callback)
{
    OnNotifications = Callback;
}

void UNakamaRealtimeClientListener::SetPartyCallback(const TFunction<void(const FNakamaParty&)>& Callback)
{
    OnParty = Callback;
}

void UNakamaRealtimeClientListener::SetPartyCloseCallback(const TFunction<void(const FNakamaPartyClose&)>& Callback)
{
    OnPartyClose = Callback;
}

void UNakamaRealtimeClientListener::SetPartyDataCallback(const TFunction<void(const FNakamaPartyData&)>& Callback)
{
    OnPartyData = Callback;
}

void UNakamaRealtimeClientListener::SetPartyJoinRequestCallback(const TFunction<void(const FNakamaPartyJoinRequest&)>& Callback)
{
    OnPartyJoinRequest = Callback;
}

void UNakamaRealtimeClientListener::SetPartyLeaderCallback(const TFunction<void(const FNakamaPartyLeader&)>& Callback)
{
    OnPartyLeader = Callback;
}

void UNakamaRealtimeClientListener::SetPartyMatchmakerTicketCallback(const TFunction<void(const FNakamaPartyMatchmakerTicket&)>& Callback)
{
    OnPartyMatchmakerTicket = Callback;
}

void UNakamaRealtimeClientListener::SetPartyPresenceCallback(const TFunction<void(const FNakamaPartyPresenceEvent&)>& Callback)
{
    OnPartyPresenceEvent = Callback;
}

void UNakamaRealtimeClientListener::SetStatusPresenceCallback(const TFunction<void(const FNakamaStatusPresenceEvent&)>& Callback)
{
    OnStatusPresenceEvent = Callback;
}

void UNakamaRealtimeClientListener::SetStreamPresenceCallback(const TFunction<void(const FNakamaStreamPresenceEvent&)>& Callback)
{
    OnStreamPresenceEvent = Callback;
}

void UNakamaRealtimeClientListener::SetStreamDataCallback(const TFunction<void(const FNakamaStreamData&)>& Callback)
{
    OnStreamData = Callback;
}