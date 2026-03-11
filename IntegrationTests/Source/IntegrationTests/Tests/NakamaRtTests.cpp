/**
 * NakamaRealtimeClient Integration Test Suite
 *
 * Tests the typed NakamaRealtimeClient API layer: ChannelJoin, MatchCreate,
 * MatchmakerAdd, StatusUpdate, PartyCreate, and Ping.
 *
 * Each spec creates an isolated UGameInstance (via Init()) so the
 * UNakamaWebSocketSubsystem is fresh per test, matching the isolation strategy
 * used in NakamaWebSocketSubsystemTests.cpp.
 *
 * Requires a running Nakama server (IntegrationTests/server/docker-compose.yml).
 *
 * Run with:
 *   -ExecCmds="Automation RunTests IntegrationTests.NakamaRt"
 */

#include "Misc/AutomationTest.h"
#include "Misc/Guid.h"
#include "Dom/JsonObject.h"
#include "Nakama.h"
#include "NakamaRt.h"
#include "NakamaWebSocketSubsystem.h"
#include "WebSocketsModule.h"
#include "Engine/Engine.h"
#include "Engine/GameInstance.h"

// ---------------------------------------------------------------------------
// Shared constants and helpers (file-local)
// ---------------------------------------------------------------------------

namespace
{
    static const FString RtServerKey = TEXT("defaultkey");
    static const FString RtHost      = TEXT("127.0.0.1");
    static constexpr int32 RtPort    = 7350;

    FNakamaWebSocketConnectionParams MakeConnParams(const FNakamaSession& Session)
    {
        FNakamaWebSocketConnectionParams P;
        P.Host                = RtHost;
        P.Port                = RtPort;
        P.Token               = Session.Token;
        P.PingIntervalSeconds = 60.0f;
        P.bUseSSL             = false;
        return P;
    }

    /** Create a UGameInstance with a fully-initialised subsystem collection.
     *
     *  Calling Init() triggers SubsystemCollection.Initialize(), which
     *  auto-discovers and registers UNakamaWebSocketSubsystem (and any other
     *  UGameInstanceSubsystem subclasses).  The caller must AddToRoot() the
     *  returned instance and call Shutdown() + RemoveFromRoot() after use. */
    UGameInstance* CreateTestGameInstance()
    {
        if (!FModuleManager::Get().IsModuleLoaded(TEXT("WebSockets")))
        {
            FModuleManager::Get().LoadModule(TEXT("WebSockets"));
        }
        UGameInstance* GI = NewObject<UGameInstance>(GetTransientPackage());
        GI->Init();
        return GI;
    }
}

/**
 * Fails the current test and calls Done when a FNakamaWebSocketResponse carries
 * an error.  Use only in terminal .Next() callbacks (it contains a bare return).
 */
#define RT_FAIL_ON_ERROR(Resp, Done)                                                                  \
    if ((Resp).ErrorCode != ENakamaWebSocketError::None) {                                            \
        AddError(FString::Printf(TEXT("Unexpected realtime error in response: %d"), Resp.ErrorCode)); \
        (Done).Execute();                                                                             \
        return;                                                                                       \
    }

// ============================================================================
// PING TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaRtPingSpec, "IntegrationTests.NakamaRt.Ping",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

    FNakamaClientConfig ClientConfig;
    FNakamaSession      Session;
    UGameInstance*      GI      = nullptr;
    TUniquePtr<Nakama::NakamaRealtimeClient> RtClient;

    FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaRtPingSpec)

void FNakamaRtPingSpec::Define()
{
    BeforeEach([this]()
    {
        ClientConfig = FNakamaClientConfig{ RtServerKey, RtHost, RtPort, false };
        GI = CreateTestGameInstance();
        GI->AddToRoot();
    });

    LatentBeforeEach([this](const FDoneDelegate& Done)
    {
        FNakamaAccountCustom Account;
        Account.Id = GenerateId();
        Nakama::AuthenticateCustom(ClientConfig, Account, true, TEXT(""))
            .Next([this, Done](FNakamaSessionResult R)
            {
                if (R.bIsError) { AddError(FString::Printf(TEXT("Auth: %s"), *R.Error.Message)); Done.Execute(); return; }
                Session = R.Value;
                Done.Execute();
            });
    });

    LatentAfterEach([this](const FDoneDelegate& Done)
    {
        RtClient.Reset();
        if (GI) { GI->Shutdown(); GI->RemoveFromRoot(); GI = nullptr; }

        if (Session.Token.IsEmpty()) { Done.Execute(); return; }
        Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
    });

    Describe("Single", [this]()
    {
        LatentIt("should receive a pong from Ping()", [this](const FDoneDelegate& Done)
        {
            RtClient = MakeUnique<Nakama::NakamaRealtimeClient>(GI);
            RtClient->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return RtClient->Ping();
                })
                .Next([this, Done](FNakamaWebSocketResponse Resp)
                {
                    RT_FAIL_ON_ERROR(Resp, Done);
                    Done.Execute();
                });
        });
    });
}

// ============================================================================
// CHANNEL TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaRtChannelSpec, "IntegrationTests.NakamaRt.Channel",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

    FNakamaClientConfig ClientConfig;
    FNakamaSession      Session;
    UGameInstance*      GI      = nullptr;
    TUniquePtr<Nakama::NakamaRealtimeClient> RtClient;

    FString GenerateId()       { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }
    FString GenerateRoomName() { return TEXT("rt-test-") + FGuid::NewGuid().ToString(EGuidFormats::Short).Left(8); }

    FString ExtractChannelId(const FNakamaWebSocketResponse& Resp) const
    {
        FString Id;
        const TSharedPtr<FJsonObject>* Obj;
        if (Resp.Data.IsValid() && Resp.Data->TryGetObjectField(TEXT("channel"), Obj))
        {
            (*Obj)->TryGetStringField(TEXT("id"), Id);
        }
        return Id;
    }

    FString ExtractMessageId(const FNakamaWebSocketResponse& Resp) const
    {
        FString Id;
        const TSharedPtr<FJsonObject>* Obj;
        if (Resp.Data.IsValid() && Resp.Data->TryGetObjectField(TEXT("channel_message_ack"), Obj))
        {
            (*Obj)->TryGetStringField(TEXT("message_id"), Id);
        }
        return Id;
    }

END_DEFINE_SPEC(FNakamaRtChannelSpec)

void FNakamaRtChannelSpec::Define()
{
    BeforeEach([this]()
    {
        ClientConfig = FNakamaClientConfig{ RtServerKey, RtHost, RtPort, false };
        GI = CreateTestGameInstance();
        GI->AddToRoot();
    });

    LatentBeforeEach([this](const FDoneDelegate& Done)
    {
        FNakamaAccountCustom Account;
        Account.Id = GenerateId();
        Nakama::AuthenticateCustom(ClientConfig, Account, true, TEXT(""))
            .Next([this, Done](FNakamaSessionResult R)
            {
                if (R.bIsError) { AddError(FString::Printf(TEXT("Auth: %s"), *R.Error.Message)); Done.Execute(); return; }
                Session = R.Value;
                Done.Execute();
            });
    });

    LatentAfterEach([this](const FDoneDelegate& Done)
    {
        RtClient.Reset();
        if (GI) { GI->Shutdown(); GI->RemoveFromRoot(); GI = nullptr; }

        if (Session.Token.IsEmpty()) { Done.Execute(); return; }
        Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
    });

    // -----------------------------------------------------------------------

    Describe("Join", [this]()
    {
        LatentIt("should join a room channel and receive a channel ID", [this](const FDoneDelegate& Done)
        {
            RtClient = MakeUnique<Nakama::NakamaRealtimeClient>(GI);
            RtClient->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return RtClient->ChannelJoin(GenerateRoomName(), 1, false, false);
                })
                .Next([this, Done](FNakamaWebSocketResponse Resp)
                {
                    RT_FAIL_ON_ERROR(Resp, Done);
                    TestFalse("Joined channel should have a non-empty ID", ExtractChannelId(Resp).IsEmpty());
                    Done.Execute();
                });
        });
    });

    Describe("SendMessage", [this]()
    {
        LatentIt("should send a message and receive an ack with a message_id", [this](const FDoneDelegate& Done)
        {
            RtClient = MakeUnique<Nakama::NakamaRealtimeClient>(GI);
            RtClient->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return RtClient->ChannelJoin(GenerateRoomName(), 1, true, false);
                })
                .Next([this](FNakamaWebSocketResponse JoinResp) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    if (JoinResp.ErrorCode != ENakamaWebSocketError::None)
                    {
                        AddError(TEXT("ChannelJoin failed"));
                        return MakeCompletedFuture<FNakamaWebSocketResponse>(JoinResp);
                    }
                    FString ChannelId = ExtractChannelId(JoinResp);
                    TestFalse("Channel ID from join", ChannelId.IsEmpty());
                    return RtClient->ChannelMessageSend(ChannelId, TEXT("{\"msg\":\"hello\"}"));
                })
                .Next([this, Done](FNakamaWebSocketResponse Resp)
                {
                    RT_FAIL_ON_ERROR(Resp, Done);
                    TestFalse("Ack should contain a message_id", ExtractMessageId(Resp).IsEmpty());
                    Done.Execute();
                });
        });
    });

    Describe("UpdateMessage", [this]()
    {
        LatentIt("should update a sent message without error", [this](const FDoneDelegate& Done)
        {
            RtClient = MakeUnique<Nakama::NakamaRealtimeClient>(GI);
            FString ChannelId;
            RtClient->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return RtClient->ChannelJoin(GenerateRoomName(), 1, true, false);
                })
                .Next([this](FNakamaWebSocketResponse JoinResp) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    if (JoinResp.ErrorCode != ENakamaWebSocketError::None)
                    {
                        AddError(TEXT("ChannelJoin failed"));
                        return MakeCompletedFuture<FNakamaWebSocketResponse>(JoinResp);
                    }
                    return RtClient->ChannelMessageSend(ExtractChannelId(JoinResp), TEXT("{\"msg\":\"original\"}"));
                })
                .Next([this](FNakamaWebSocketResponse SendResp) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    if (SendResp.ErrorCode != ENakamaWebSocketError::None)
                    {
                        AddError(TEXT("ChannelMessageSend failed"));
                        return MakeCompletedFuture<FNakamaWebSocketResponse>(SendResp);
                    }
                    // Extract both channel_id and message_id from the ack
                    FString MsgId = ExtractMessageId(SendResp);
                    FString ChId;
                    const TSharedPtr<FJsonObject>* Ack;
                    if (SendResp.Data.IsValid() && SendResp.Data->TryGetObjectField(TEXT("channel_message_ack"), Ack))
                    {
                        (*Ack)->TryGetStringField(TEXT("channel_id"), ChId);
                    }
                    TestFalse("Message ID before update", MsgId.IsEmpty());
                    return RtClient->ChannelMessageUpdate(ChId, MsgId, TEXT("{\"msg\":\"updated\"}"));
                })
                .Next([this, Done](FNakamaWebSocketResponse Resp)
                {
                    RT_FAIL_ON_ERROR(Resp, Done);
                    Done.Execute();
                });
        });
    });

    Describe("RemoveMessage", [this]()
    {
        LatentIt("should remove a sent message without error", [this](const FDoneDelegate& Done)
        {
            RtClient = MakeUnique<Nakama::NakamaRealtimeClient>(GI);
            RtClient->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return RtClient->ChannelJoin(GenerateRoomName(), 1, true, false);
                })
                .Next([this](FNakamaWebSocketResponse JoinResp) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    if (JoinResp.ErrorCode != ENakamaWebSocketError::None)
                    {
                        AddError(TEXT("ChannelJoin failed"));
                        return MakeCompletedFuture<FNakamaWebSocketResponse>(JoinResp);
                    }
                    return RtClient->ChannelMessageSend(ExtractChannelId(JoinResp), TEXT("{\"msg\":\"to delete\"}"));
                })
                .Next([this](FNakamaWebSocketResponse SendResp) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    if (SendResp.ErrorCode != ENakamaWebSocketError::None)
                    {
                        AddError(TEXT("ChannelMessageSend failed"));
                        return MakeCompletedFuture<FNakamaWebSocketResponse>(SendResp);
                    }
                    FString MsgId = ExtractMessageId(SendResp);
                    FString ChId;
                    const TSharedPtr<FJsonObject>* Ack;
                    if (SendResp.Data.IsValid() && SendResp.Data->TryGetObjectField(TEXT("channel_message_ack"), Ack))
                    {
                        (*Ack)->TryGetStringField(TEXT("channel_id"), ChId);
                    }
                    return RtClient->ChannelMessageRemove(ChId, MsgId);
                })
                .Next([this, Done](FNakamaWebSocketResponse Resp)
                {
                    RT_FAIL_ON_ERROR(Resp, Done);
                    Done.Execute();
                });
        });
    });

    Describe("Leave", [this]()
    {
        LatentIt("should leave a channel without error", [this](const FDoneDelegate& Done)
        {
            RtClient = MakeUnique<Nakama::NakamaRealtimeClient>(GI);
            RtClient->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return RtClient->ChannelJoin(GenerateRoomName(), 1, false, false);
                })
                .Next([this](FNakamaWebSocketResponse JoinResp) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    if (JoinResp.ErrorCode != ENakamaWebSocketError::None)
                    {
                        AddError(TEXT("ChannelJoin failed"));
                        return MakeCompletedFuture<FNakamaWebSocketResponse>(JoinResp);
                    }
                    return RtClient->ChannelLeave(ExtractChannelId(JoinResp));
                })
                .Next([this, Done](FNakamaWebSocketResponse Resp)
                {
                    RT_FAIL_ON_ERROR(Resp, Done);
                    Done.Execute();
                });
        });
    });
}

// ============================================================================
// MATCH TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaRtMatchSpec, "IntegrationTests.NakamaRt.Match",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

    FNakamaClientConfig ClientConfig;
    FNakamaSession      Session;
    UGameInstance*      GI      = nullptr;
    TUniquePtr<Nakama::NakamaRealtimeClient> RtClient;

    FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

    FString ExtractMatchId(const FNakamaWebSocketResponse& Resp) const
    {
        FString Id;
        const TSharedPtr<FJsonObject>* Obj;
        if (Resp.Data.IsValid() && Resp.Data->TryGetObjectField(TEXT("match"), Obj))
        {
            (*Obj)->TryGetStringField(TEXT("match_id"), Id);
        }
        return Id;
    }

END_DEFINE_SPEC(FNakamaRtMatchSpec)

void FNakamaRtMatchSpec::Define()
{
    BeforeEach([this]()
    {
        ClientConfig = FNakamaClientConfig{ RtServerKey, RtHost, RtPort, false };
        GI = CreateTestGameInstance();
        GI->AddToRoot();
    });

    LatentBeforeEach([this](const FDoneDelegate& Done)
    {
        FNakamaAccountCustom Account;
        Account.Id = GenerateId();
        Nakama::AuthenticateCustom(ClientConfig, Account, true, TEXT(""))
            .Next([this, Done](FNakamaSessionResult R)
            {
                if (R.bIsError) { AddError(FString::Printf(TEXT("Auth: %s"), *R.Error.Message)); Done.Execute(); return; }
                Session = R.Value;
                Done.Execute();
            });
    });

    LatentAfterEach([this](const FDoneDelegate& Done)
    {
        RtClient.Reset();
        if (GI) { GI->Shutdown(); GI->RemoveFromRoot(); GI = nullptr; }

        if (Session.Token.IsEmpty()) { Done.Execute(); return; }
        Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
    });

    // -----------------------------------------------------------------------

    Describe("Create", [this]()
    {
        LatentIt("should create a relayed match and receive a match_id", [this](const FDoneDelegate& Done)
        {
            RtClient = MakeUnique<Nakama::NakamaRealtimeClient>(GI);
            RtClient->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return RtClient->MatchCreate(TEXT(""));
                })
                .Next([this, Done](FNakamaWebSocketResponse Resp)
                {
                    RT_FAIL_ON_ERROR(Resp, Done);
                    TestFalse("match_id should not be empty", ExtractMatchId(Resp).IsEmpty());
                    Done.Execute();
                });
        });
    });

    Describe("Leave", [this]()
    {
        LatentIt("should leave a match without error", [this](const FDoneDelegate& Done)
        {
            RtClient = MakeUnique<Nakama::NakamaRealtimeClient>(GI);
            RtClient->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return RtClient->MatchCreate(TEXT(""));
                })
                .Next([this](FNakamaWebSocketResponse CreateResp) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    if (CreateResp.ErrorCode != ENakamaWebSocketError::None)
                    {
                        AddError(TEXT("MatchCreate failed"));
                        return MakeCompletedFuture<FNakamaWebSocketResponse>(CreateResp);
                    }
                    FString MatchId = ExtractMatchId(CreateResp);
                    TestFalse("Match ID before leave", MatchId.IsEmpty());
                    return RtClient->MatchLeave(MatchId);
                })
                .Next([this, Done](FNakamaWebSocketResponse Resp)
                {
                    RT_FAIL_ON_ERROR(Resp, Done);
                    Done.Execute();
                });
        });
    });

    Describe("SendData", [this]()
    {
        LatentIt("should send match data without error", [this](const FDoneDelegate& Done)
        {
            RtClient = MakeUnique<Nakama::NakamaRealtimeClient>(GI);
            RtClient->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return RtClient->MatchCreate(TEXT(""));
                })
                .Next([this, Done](FNakamaWebSocketResponse CreateResp)
                {
                    RT_FAIL_ON_ERROR(CreateResp, Done);
                    FString MatchId = ExtractMatchId(CreateResp);
                    TArray<uint8> Payload = { 1, 2, 3 };
                    // MatchDataSend is fire-and-forget — the server sends no response.
                    RtClient->MatchDataSend(MatchId, 1, Payload, {}, true);
                    Done.Execute();
                });
        });
    });
}

// ============================================================================
// MATCHMAKER TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaRtMatchmakerSpec, "IntegrationTests.NakamaRt.Matchmaker",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

    FNakamaClientConfig ClientConfig;
    FNakamaSession      Session;
    UGameInstance*      GI      = nullptr;
    TUniquePtr<Nakama::NakamaRealtimeClient> RtClient;

    FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

    FString ExtractTicket(const FNakamaWebSocketResponse& Resp) const
    {
        FString Ticket;
        const TSharedPtr<FJsonObject>* Obj;
        if (Resp.Data.IsValid() && Resp.Data->TryGetObjectField(TEXT("matchmaker_ticket"), Obj))
        {
            (*Obj)->TryGetStringField(TEXT("ticket"), Ticket);
        }
        return Ticket;
    }

END_DEFINE_SPEC(FNakamaRtMatchmakerSpec)

void FNakamaRtMatchmakerSpec::Define()
{
    BeforeEach([this]()
    {
        ClientConfig = FNakamaClientConfig{ RtServerKey, RtHost, RtPort, false };
        GI = CreateTestGameInstance();
        GI->AddToRoot();
    });

    LatentBeforeEach([this](const FDoneDelegate& Done)
    {
        FNakamaAccountCustom Account;
        Account.Id = GenerateId();
        Nakama::AuthenticateCustom(ClientConfig, Account, true, TEXT(""))
            .Next([this, Done](FNakamaSessionResult R)
            {
                if (R.bIsError) { AddError(FString::Printf(TEXT("Auth: %s"), *R.Error.Message)); Done.Execute(); return; }
                Session = R.Value;
                Done.Execute();
            });
    });

    LatentAfterEach([this](const FDoneDelegate& Done)
    {
        RtClient.Reset();
        if (GI) { GI->Shutdown(); GI->RemoveFromRoot(); GI = nullptr; }

        if (Session.Token.IsEmpty()) { Done.Execute(); return; }
        Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
    });

    // -----------------------------------------------------------------------

    Describe("Add", [this]()
    {
        LatentIt("should add to matchmaker and receive a ticket", [this](const FDoneDelegate& Done)
        {
            RtClient = MakeUnique<Nakama::NakamaRealtimeClient>(GI);
            RtClient->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return RtClient->MatchmakerAdd(2, 4, TEXT("*"), 2, {}, {});
                })
                .Next([this, Done](FNakamaWebSocketResponse Resp)
                {
                    RT_FAIL_ON_ERROR(Resp, Done);
                    TestFalse("Matchmaker ticket should not be empty", ExtractTicket(Resp).IsEmpty());
                    Done.Execute();
                });
        });
    });

    Describe("Remove", [this]()
    {
        LatentIt("should cancel matchmaking with the returned ticket", [this](const FDoneDelegate& Done)
        {
            RtClient = MakeUnique<Nakama::NakamaRealtimeClient>(GI);
            RtClient->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return RtClient->MatchmakerAdd(2, 4, TEXT("*"), 2, {}, {});
                })
                .Next([this](FNakamaWebSocketResponse AddResp) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    if (AddResp.ErrorCode != ENakamaWebSocketError::None)
                    {
                        AddError(TEXT("MatchmakerAdd failed"));
                        return MakeCompletedFuture<FNakamaWebSocketResponse>(AddResp);
                    }
                    FString Ticket = ExtractTicket(AddResp);
                    TestFalse("Ticket before remove", Ticket.IsEmpty());
                    return RtClient->MatchmakerRemove(Ticket);
                })
                .Next([this, Done](FNakamaWebSocketResponse Resp)
                {
                    RT_FAIL_ON_ERROR(Resp, Done);
                    Done.Execute();
                });
        });
    });
}

// ============================================================================
// STATUS TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaRtStatusSpec, "IntegrationTests.NakamaRt.Status",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

    FNakamaClientConfig ClientConfig;
    FNakamaSession      Session;
    UGameInstance*      GI      = nullptr;
    TUniquePtr<Nakama::NakamaRealtimeClient> RtClient;

    FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaRtStatusSpec)

void FNakamaRtStatusSpec::Define()
{
    BeforeEach([this]()
    {
        ClientConfig = FNakamaClientConfig{ RtServerKey, RtHost, RtPort, false };
        GI = CreateTestGameInstance();
        GI->AddToRoot();
    });

    LatentBeforeEach([this](const FDoneDelegate& Done)
    {
        FNakamaAccountCustom Account;
        Account.Id = GenerateId();
        Nakama::AuthenticateCustom(ClientConfig, Account, true, TEXT(""))
            .Next([this, Done](FNakamaSessionResult R)
            {
                if (R.bIsError) { AddError(FString::Printf(TEXT("Auth: %s"), *R.Error.Message)); Done.Execute(); return; }
                Session = R.Value;
                Done.Execute();
            });
    });

    LatentAfterEach([this](const FDoneDelegate& Done)
    {
        RtClient.Reset();
        if (GI) { GI->Shutdown(); GI->RemoveFromRoot(); GI = nullptr; }

        if (Session.Token.IsEmpty()) { Done.Execute(); return; }
        Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
    });

    // -----------------------------------------------------------------------

    Describe("Update", [this]()
    {
        LatentIt("should set a status string without error", [this](const FDoneDelegate& Done)
        {
            RtClient = MakeUnique<Nakama::NakamaRealtimeClient>(GI);
            RtClient->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return RtClient->StatusUpdate(TEXT("Playing a game"));
                })
                .Next([this, Done](FNakamaWebSocketResponse Resp)
                {
                    RT_FAIL_ON_ERROR(Resp, Done);
                    Done.Execute();
                });
        });

        LatentIt("should clear status by passing an empty string", [this](const FDoneDelegate& Done)
        {
            RtClient = MakeUnique<Nakama::NakamaRealtimeClient>(GI);
            RtClient->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return RtClient->StatusUpdate(TEXT(""));
                })
                .Next([this, Done](FNakamaWebSocketResponse Resp)
                {
                    RT_FAIL_ON_ERROR(Resp, Done);
                    Done.Execute();
                });
        });
    });

    Describe("Follow", [this]()
    {
        LatentIt("should follow a user ID without error", [this](const FDoneDelegate& Done)
        {
            // Nakama accepts follow requests for non-existent users and returns
            // an empty presence list, so a random UUID is fine here.
            RtClient = MakeUnique<Nakama::NakamaRealtimeClient>(GI);
            RtClient->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return RtClient->StatusFollow({ GenerateId() }, {});
                })
                .Next([this, Done](FNakamaWebSocketResponse Resp)
                {
                    RT_FAIL_ON_ERROR(Resp, Done);
                    Done.Execute();
                });
        });

        LatentIt("should follow and then unfollow a user ID", [this](const FDoneDelegate& Done)
        {
            FString FakeUserId = GenerateId();
            RtClient = MakeUnique<Nakama::NakamaRealtimeClient>(GI);
            RtClient->Connect(MakeConnParams(Session))
                .Next([this, FakeUserId](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return RtClient->StatusFollow({ FakeUserId }, {});
                })
                .Next([this, FakeUserId](FNakamaWebSocketResponse FollowResp) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    if (FollowResp.ErrorCode != ENakamaWebSocketError::None)
                    {
                        AddError(TEXT("StatusFollow failed"));
                        return MakeCompletedFuture<FNakamaWebSocketResponse>(FollowResp);
                    }
                    return RtClient->StatusUnfollow({ FakeUserId });
                })
                .Next([this, Done](FNakamaWebSocketResponse Resp)
                {
                    RT_FAIL_ON_ERROR(Resp, Done);
                    Done.Execute();
                });
        });
    });
}

// ============================================================================
// PARTY TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaRtPartySpec, "IntegrationTests.NakamaRt.Party",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

    FNakamaClientConfig ClientConfig;
    FNakamaSession      Session;
    UGameInstance*      GI      = nullptr;
    TUniquePtr<Nakama::NakamaRealtimeClient> RtClient;

    FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

    FString ExtractPartyId(const FNakamaWebSocketResponse& Resp) const
    {
        FString Id;
        const TSharedPtr<FJsonObject>* Obj;
        if (Resp.Data.IsValid() && Resp.Data->TryGetObjectField(TEXT("party"), Obj))
        {
            (*Obj)->TryGetStringField(TEXT("party_id"), Id);
        }
        return Id;
    }

END_DEFINE_SPEC(FNakamaRtPartySpec)

void FNakamaRtPartySpec::Define()
{
    BeforeEach([this]()
    {
        ClientConfig = FNakamaClientConfig{ RtServerKey, RtHost, RtPort, false };
        GI = CreateTestGameInstance();
        GI->AddToRoot();
    });

    LatentBeforeEach([this](const FDoneDelegate& Done)
    {
        FNakamaAccountCustom Account;
        Account.Id = GenerateId();
        Nakama::AuthenticateCustom(ClientConfig, Account, true, TEXT(""))
            .Next([this, Done](FNakamaSessionResult R)
            {
                if (R.bIsError) { AddError(FString::Printf(TEXT("Auth: %s"), *R.Error.Message)); Done.Execute(); return; }
                Session = R.Value;
                Done.Execute();
            });
    });

    LatentAfterEach([this](const FDoneDelegate& Done)
    {
        RtClient.Reset();
        if (GI) { GI->Shutdown(); GI->RemoveFromRoot(); GI = nullptr; }

        if (Session.Token.IsEmpty()) { Done.Execute(); return; }
        Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
    });

    // -----------------------------------------------------------------------

    Describe("Create", [this]()
    {
        LatentIt("should create a party and receive a party_id", [this](const FDoneDelegate& Done)
        {
            RtClient = MakeUnique<Nakama::NakamaRealtimeClient>(GI);
            RtClient->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return RtClient->PartyCreate(true, 4, TEXT(""), false);
                })
                .Next([this, Done](FNakamaWebSocketResponse Resp)
                {
                    RT_FAIL_ON_ERROR(Resp, Done);
                    TestFalse("party_id should not be empty", ExtractPartyId(Resp).IsEmpty());
                    Done.Execute();
                });
        });
    });

    Describe("Close", [this]()
    {
        LatentIt("should close a party without error", [this](const FDoneDelegate& Done)
        {
            RtClient = MakeUnique<Nakama::NakamaRealtimeClient>(GI);
            RtClient->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return RtClient->PartyCreate(true, 4, TEXT(""), false);
                })
                .Next([this](FNakamaWebSocketResponse CreateResp) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    if (CreateResp.ErrorCode != ENakamaWebSocketError::None)
                    {
                        AddError(TEXT("PartyCreate failed"));
                        return MakeCompletedFuture<FNakamaWebSocketResponse>(CreateResp);
                    }
                    FString PartyId = ExtractPartyId(CreateResp);
                    TestFalse("Party ID before close", PartyId.IsEmpty());
                    return RtClient->PartyClose(PartyId);
                })
                .Next([this, Done](FNakamaWebSocketResponse Resp)
                {
                    RT_FAIL_ON_ERROR(Resp, Done);
                    Done.Execute();
                });
        });
    });
}
