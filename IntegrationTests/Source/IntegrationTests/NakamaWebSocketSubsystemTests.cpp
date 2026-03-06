/**
 * Nakama Realtime (WebSocket) Integration Test Suite
 *
 * Tests UWebSocketSubsystem connection lifecycle, request/response round-trips,
 * delegate notifications, reconnection, error paths, and concurrent requests.
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
#include "WebSocketSubsystem.h"
#include "WebSocketsModule.h"
#include "Engine/Engine.h"
#include "Engine/GameInstance.h"

// ---------------------------------------------------------------------------
// Shared constants (file-local)
// ---------------------------------------------------------------------------

namespace
{
    static const FString RtServerKey = TEXT("defaultkey");
    static const FString RtHost      = TEXT("127.0.0.1");
    static constexpr int32 RtPort    = 7350;

    /** Build connection params with a long ping interval so auto-pings don't
     *  pollute test assertions. */
    FRealtimeConnectionParams MakeConnParams(const FNakamaSession& Session,
                                             int32 OverridePort = RtPort)
    {
        FRealtimeConnectionParams P;
        P.Host                = RtHost;
        P.Port                = OverridePort;
        P.Token               = Session.Token;
        P.PingIntervalSeconds = 60.0f;
        P.bUseSSL             = false;
        return P;
    }

    /** Create a standalone UWebSocketSubsystem for testing.
     *
     *  UWebSocketSubsystem::Initialize() only loads the WebSockets module;
     *  none of its actual Connect/Send/Close logic depends on a UGameInstance
     *  outer.  We therefore create the object directly and ensure the module is
     *  loaded, skipping the subsystem-collection machinery entirely.
     *
     *  The caller must AddToRoot() the returned object and RemoveFromRoot()
     *  after use. */
    UWebSocketSubsystem* CreateTestSubsystem()
    {
        if (!FModuleManager::Get().IsModuleLoaded(TEXT("WebSockets")))
        {
            FModuleManager::Get().LoadModule(TEXT("WebSockets"));
        }
        // UWebSocketSubsystem has ClassWithin=UGameInstance (UGameInstanceSubsystem),
        // so it must have a UGameInstance outer to satisfy UE's ensure.
        UGameInstance* TempInstance = NewObject<UGameInstance>(GetTransientPackage());
        return NewObject<UWebSocketSubsystem>(TempInstance);
    }
}

/**
 * Fails the current test and calls Done when a FRealtimeResponse carries an
 * error.  Use inside a .Next() callback that expects success.
 */
#define RT_FAIL_ON_ERROR(Resp, Done)                                    \
    if ((Resp).bError) {                                                \
        AddError(TEXT("Unexpected realtime error in response"));        \
        (Done).Execute();                                               \
        return;                                                         \
    }

// ============================================================================
// CONNECTION TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaRtConnectionSpec, "IntegrationTests.NakamaRt.Connection",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

    FNakamaClientConfig  ClientConfig;
    FNakamaSession       Session;
    UWebSocketSubsystem* WSSub = nullptr;

    FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaRtConnectionSpec)

void FNakamaRtConnectionSpec::Define()
{
    BeforeEach([this]()
    {
        ClientConfig = FNakamaClientConfig{ RtServerKey, RtHost, RtPort, false };
        WSSub = CreateTestSubsystem();
        WSSub->AddToRoot();
    });

    LatentBeforeEach([this](const FDoneDelegate& Done)
    {
        FNakamaAccountCustom Account;
        Account.Id = GenerateId();
        Nakama::AuthenticateCustom(ClientConfig, Account, true, TEXT(""))
            .Next([this, Done](FNakamaSessionResult Result)
            {
                if (Result.bIsError)
                {
                    AddError(FString::Printf(TEXT("Auth failed: %s"), *Result.Error.Message));
                    Done.Execute();
                    return;
                }
                Session = Result.Value;
                Done.Execute();
            });
    });

    AfterEach([this]()
    {
        if (WSSub)
        {
            WSSub->Close();
            WSSub->RemoveFromRoot();
            WSSub = nullptr;
        }
    });

    // -----------------------------------------------------------------------
    // Success path
    // -----------------------------------------------------------------------

    Describe("Success", [this]()
    {
        LatentIt("should connect with a valid session token", [this](const FDoneDelegate& Done)
        {
            WSSub->Connect(MakeConnParams(Session)).Next([this, Done](FRealtimeConnectionResult Result)
            {
                TestFalse("Connection should succeed (bError = false)", Result.bError);
                Done.Execute();
            });
        });
    });

    // -----------------------------------------------------------------------
    // Invalid token
    // -----------------------------------------------------------------------

    Describe("InvalidToken", [this]()
    {
        LatentIt("should fail with a malformed token", [this](const FDoneDelegate& Done)
        {
            FRealtimeConnectionParams Bad = MakeConnParams(Session);
            Bad.Token = TEXT("not.a.valid.jwt");

            WSSub->Connect(Bad).Next([this, Done](FRealtimeConnectionResult Result)
            {
                TestTrue("Connection with invalid token should report error", Result.bError);
                Done.Execute();
            });
        });

        LatentIt("should fail with an empty token", [this](const FDoneDelegate& Done)
        {
            FRealtimeConnectionParams Bad = MakeConnParams(Session);
            Bad.Token = TEXT("");

            WSSub->Connect(Bad).Next([this, Done](FRealtimeConnectionResult Result)
            {
                TestTrue("Connection with empty token should report error", Result.bError);
                Done.Execute();
            });
        });
    });

    // -----------------------------------------------------------------------
    // Wrong endpoint
    // -----------------------------------------------------------------------

    Describe("WrongEndpoint", [this]()
    {
        LatentIt("should fail when no server is listening on the target port", [this](const FDoneDelegate& Done)
        {
            // Port 19999 — nothing should be listening here.
            FRealtimeConnectionParams Bad = MakeConnParams(Session, 19999);

            WSSub->Connect(Bad).Next([this, Done](FRealtimeConnectionResult Result)
            {
                TestTrue("Connection to unreachable port should report error", Result.bError);
                Done.Execute();
            });
        });
    });

    // -----------------------------------------------------------------------
    // Reconnection
    // -----------------------------------------------------------------------

    Describe("Reconnect", [this]()
    {
        LatentIt("should reconnect successfully after an explicit Close", [this](const FDoneDelegate& Done)
        {
            WSSub->Connect(MakeConnParams(Session)).Next([this, Done](FRealtimeConnectionResult First)
            {
                if (!TestFalse("First connection should succeed", First.bError))
                {
                    Done.Execute();
                    return;
                }

                WSSub->Close();

                WSSub->Connect(MakeConnParams(Session)).Next([this, Done](FRealtimeConnectionResult Second)
                {
                    TestFalse("Connection after explicit Close should succeed", Second.bError);
                    Done.Execute();
                });
            });
        });

        LatentIt("should accept a new Connect while already connected", [this](const FDoneDelegate& Done)
        {
            WSSub->Connect(MakeConnParams(Session)).Next([this, Done](FRealtimeConnectionResult First)
            {
                if (!TestFalse("First connection should succeed", First.bError))
                {
                    Done.Execute();
                    return;
                }

                // A second Connect while already connected — the subsystem should
                // auto-close the old socket and open a new one.
                WSSub->Connect(MakeConnParams(Session)).Next([this, Done](FRealtimeConnectionResult Second)
                    {
                        TestFalse("Second Connect while already connected should succeed", Second.bError);
                        Done.Execute();
                    });
            });
        });

        LatentIt("should be usable after reconnect (ping round-trip)", [this](const FDoneDelegate& Done)
        {
            WSSub->Connect(MakeConnParams(Session)).Next([this, Done](FRealtimeConnectionResult First)
            {
                if (!TestFalse("First connection", First.bError)) { Done.Execute(); return; }

                WSSub->Close();

                WSSub->Connect(MakeConnParams(Session)).Next([this, Done](FRealtimeConnectionResult Second)
                {
                    if (!TestFalse("Reconnection", Second.bError)) { Done.Execute(); return; }

                    WSSub->Send(TEXT("ping"), MakeShared<FJsonObject>())
                        .Next([this, Done](FRealtimeResponse Resp)
                        {
                            TestFalse("Ping after reconnect should succeed", Resp.bError);
                            Done.Execute();
                        });
                });
            });
        });
    });
}

// ============================================================================
// PING TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaRtPingSpec, "IntegrationTests.NakamaRt.Ping",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

    FNakamaClientConfig  ClientConfig;
    FNakamaSession       Session;
    UWebSocketSubsystem* WSSub = nullptr;

    FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaRtPingSpec)

void FNakamaRtPingSpec::Define()
{
    BeforeEach([this]()
    {
        ClientConfig = FNakamaClientConfig{ RtServerKey, RtHost, RtPort, false };
        WSSub = CreateTestSubsystem();
        WSSub->AddToRoot();
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

    AfterEach([this]()
    {
        if (WSSub) { WSSub->Close(); WSSub->RemoveFromRoot(); WSSub = nullptr; }
    });

    Describe("Single", [this]()
    {
        LatentIt("should receive a pong response to a single ping", [this](const FDoneDelegate& Done)
        {
            WSSub->Connect(MakeConnParams(Session)).Next([this, Done](FRealtimeConnectionResult CR)
            {
                if (!TestFalse("Connect", CR.bError)) { Done.Execute(); return; }

                WSSub->Send(TEXT("ping"), MakeShared<FJsonObject>())
                    .Next([this, Done](FRealtimeResponse Resp)
                    {
                        TestFalse("Ping should receive a non-error pong response", Resp.bError);
                        Done.Execute();
                    });
            });
        });
    });

    Describe("Concurrent", [this]()
    {
        LatentIt("should handle multiple concurrent pings and resolve all of them", [this](const FDoneDelegate& Done)
        {
            WSSub->Connect(MakeConnParams(Session)).Next([this, Done](FRealtimeConnectionResult CR)
            {
                if (!TestFalse("Connect", CR.bError)) { Done.Execute(); return; }

                // Fire several pings simultaneously; track completions with a shared counter.
                constexpr int32 NumPings = 5;
                TSharedRef<TAtomic<int32>> Remaining = MakeShared<TAtomic<int32>>(NumPings);

                for (int32 i = 0; i < NumPings; ++i)
                {
                    WSSub->Send(TEXT("ping"), MakeShared<FJsonObject>())
                        .Next([this, Done, Remaining](FRealtimeResponse Resp)
                        {
                            if (Resp.bError)
                            {
                                AddError(TEXT("A concurrent ping returned an error"));
                            }
                            if (--(*Remaining) == 0)
                            {
                                Done.Execute();
                            }
                        });
                }
            });
        });

        LatentIt("should handle pings interleaved with other requests", [this](const FDoneDelegate& Done)
        {
            WSSub->Connect(MakeConnParams(Session)).Next([this, Done](FRealtimeConnectionResult CR)
            {
                if (!TestFalse("Connect", CR.bError)) { Done.Execute(); return; }

                // Send a match_create and two pings simultaneously; all three
                // must resolve without error.
                TSharedRef<TAtomic<int32>> Remaining = MakeShared<TAtomic<int32>>(3);

                auto Decrement = [this, Done, Remaining](FRealtimeResponse Resp)
                {
                    if (Resp.bError) AddError(TEXT("Interleaved request returned an error"));
                    if (--(*Remaining) == 0) Done.Execute();
                };

                WSSub->Send(TEXT("match_create"), MakeShared<FJsonObject>()).Next(Decrement);
                WSSub->Send(TEXT("ping"),         MakeShared<FJsonObject>()).Next(Decrement);
                WSSub->Send(TEXT("ping"),         MakeShared<FJsonObject>()).Next(Decrement);
            });
        });
    });
}

// ============================================================================
// CHANNEL TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaRtChannelSpec, "IntegrationTests.NakamaRt.Channel",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

    FNakamaClientConfig  ClientConfig;
    FNakamaSession       Session;
    UWebSocketSubsystem* WSSub = nullptr;

    FString GenerateId()      { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }
    FString GenerateRoomName(){ return TEXT("test-room-") + FGuid::NewGuid().ToString(EGuidFormats::Short).Left(8); }

    TSharedPtr<FJsonObject> MakeChannelJoinJson(const FString& RoomName) const
    {
        TSharedPtr<FJsonObject> J = MakeShared<FJsonObject>();
        J->SetStringField(TEXT("target"),      RoomName);
        J->SetNumberField(TEXT("type"),        1);     // 1 = room channel
        J->SetBoolField  (TEXT("persistence"), false);
        J->SetBoolField  (TEXT("hidden"),      false);
        return J;
    }

    FString ExtractChannelId(const FRealtimeResponse& Resp) const
    {
        FString Id;
        const TSharedPtr<FJsonObject>* ChannelObj;
        if (Resp.Data.IsValid() && Resp.Data->TryGetObjectField(TEXT("channel"), ChannelObj))
        {
            (*ChannelObj)->TryGetStringField(TEXT("id"), Id);
        }
        return Id;
    }

END_DEFINE_SPEC(FNakamaRtChannelSpec)

void FNakamaRtChannelSpec::Define()
{
    BeforeEach([this]()
    {
        ClientConfig = FNakamaClientConfig{ RtServerKey, RtHost, RtPort, false };
        WSSub = CreateTestSubsystem();
        WSSub->AddToRoot();
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

    AfterEach([this]()
    {
        if (WSSub) { WSSub->Close(); WSSub->RemoveFromRoot(); WSSub = nullptr; }
    });

    Describe("Join", [this]()
    {
        LatentIt("should join a room channel and receive a channel response", [this](const FDoneDelegate& Done)
        {
            WSSub->Connect(MakeConnParams(Session)).Next([this, Done](FRealtimeConnectionResult CR)
            {
                if (!TestFalse("Connect", CR.bError)) { Done.Execute(); return; }

                WSSub->Send(TEXT("channel_join"), MakeChannelJoinJson(GenerateRoomName()))
                    .Next([this, Done](FRealtimeResponse Resp)
                    {
                        RT_FAIL_ON_ERROR(Resp, Done);
                        FString ChannelId = ExtractChannelId(Resp);
                        TestFalse("Joined channel should have a non-empty ID", ChannelId.IsEmpty());
                        Done.Execute();
                    });
            });
        });
    });

    Describe("SendMessage", [this]()
    {
        LatentIt("should send a message to a room channel and receive an ack", [this](const FDoneDelegate& Done)
        {
            WSSub->Connect(MakeConnParams(Session)).Next([this, Done](FRealtimeConnectionResult CR)
            {
                if (!TestFalse("Connect", CR.bError)) { Done.Execute(); return; }

                WSSub->Send(TEXT("channel_join"), MakeChannelJoinJson(GenerateRoomName()))
                    .Next([this, Done](FRealtimeResponse JoinResp)
                    {
                        RT_FAIL_ON_ERROR(JoinResp, Done);

                        FString ChannelId = ExtractChannelId(JoinResp);
                        if (!TestFalse("Channel ID from join", ChannelId.IsEmpty())) { Done.Execute(); return; }

                        TSharedPtr<FJsonObject> SendJson = MakeShared<FJsonObject>();
                        SendJson->SetStringField(TEXT("channel_id"), ChannelId);
                        SendJson->SetStringField(TEXT("content"),    TEXT("{\"msg\":\"hello\"}"));

                        WSSub->Send(TEXT("channel_message_send"), SendJson)
                            .Next([this, Done](FRealtimeResponse SendResp)
                            {
                                RT_FAIL_ON_ERROR(SendResp, Done);
                                TestTrue("Send ack response has data", SendResp.Data.IsValid());
                                Done.Execute();
                            });
                    });
            });
        });
    });

    Describe("Leave", [this]()
    {
        LatentIt("should leave a channel successfully", [this](const FDoneDelegate& Done)
        {
            WSSub->Connect(MakeConnParams(Session)).Next([this, Done](FRealtimeConnectionResult CR)
            {
                if (!TestFalse("Connect", CR.bError)) { Done.Execute(); return; }

                WSSub->Send(TEXT("channel_join"), MakeChannelJoinJson(GenerateRoomName()))
                    .Next([this, Done](FRealtimeResponse JoinResp)
                    {
                        RT_FAIL_ON_ERROR(JoinResp, Done);

                        FString ChannelId = ExtractChannelId(JoinResp);
                        if (!TestFalse("Channel ID from join", ChannelId.IsEmpty())) { Done.Execute(); return; }

                        TSharedPtr<FJsonObject> LeaveJson = MakeShared<FJsonObject>();
                        LeaveJson->SetStringField(TEXT("channel_id"), ChannelId);

                        WSSub->Send(TEXT("channel_leave"), LeaveJson)
                            .Next([this, Done](FRealtimeResponse LeaveResp)
                            {
                                RT_FAIL_ON_ERROR(LeaveResp, Done);
                                Done.Execute();
                            });
                    });
            });
        });
    });
}

// ============================================================================
// MATCH TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaRtMatchSpec, "IntegrationTests.NakamaRt.Match",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

    FNakamaClientConfig  ClientConfig;
    FNakamaSession       Session;
    UWebSocketSubsystem* WSSub = nullptr;

    FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

    FString ExtractMatchId(const FRealtimeResponse& Resp) const
    {
        FString Id;
        const TSharedPtr<FJsonObject>* MatchObj;
        if (Resp.Data.IsValid() && Resp.Data->TryGetObjectField(TEXT("match"), MatchObj))
        {
            (*MatchObj)->TryGetStringField(TEXT("match_id"), Id);
        }
        return Id;
    }

END_DEFINE_SPEC(FNakamaRtMatchSpec)

void FNakamaRtMatchSpec::Define()
{
    BeforeEach([this]()
    {
        ClientConfig = FNakamaClientConfig{ RtServerKey, RtHost, RtPort, false };
        WSSub = CreateTestSubsystem();
        WSSub->AddToRoot();
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

    AfterEach([this]()
    {
        if (WSSub) { WSSub->Close(); WSSub->RemoveFromRoot(); WSSub = nullptr; }
    });

    Describe("Create", [this]()
    {
        LatentIt("should create a relayed match and receive a match_id", [this](const FDoneDelegate& Done)
        {
            WSSub->Connect(MakeConnParams(Session)).Next([this, Done](FRealtimeConnectionResult CR)
            {
                if (!TestFalse("Connect", CR.bError)) { Done.Execute(); return; }

                WSSub->Send(TEXT("match_create"), MakeShared<FJsonObject>())
                    .Next([this, Done](FRealtimeResponse Resp)
                    {
                        RT_FAIL_ON_ERROR(Resp, Done);
                        FString MatchId = ExtractMatchId(Resp);
                        TestFalse("Created match should have a non-empty match_id", MatchId.IsEmpty());
                        Done.Execute();
                    });
            });
        });
    });

    Describe("Leave", [this]()
    {
        LatentIt("should leave a match without error", [this](const FDoneDelegate& Done)
        {
            WSSub->Connect(MakeConnParams(Session)).Next([this, Done](FRealtimeConnectionResult CR)
            {
                if (!TestFalse("Connect", CR.bError)) { Done.Execute(); return; }

                WSSub->Send(TEXT("match_create"), MakeShared<FJsonObject>())
                    .Next([this, Done](FRealtimeResponse CreateResp)
                    {
                        RT_FAIL_ON_ERROR(CreateResp, Done);

                        FString MatchId = ExtractMatchId(CreateResp);
                        if (!TestFalse("Match ID from create", MatchId.IsEmpty())) { Done.Execute(); return; }

                        TSharedPtr<FJsonObject> LeaveJson = MakeShared<FJsonObject>();
                        LeaveJson->SetStringField(TEXT("match_id"), MatchId);

                        WSSub->Send(TEXT("match_leave"), LeaveJson)
                            .Next([this, Done](FRealtimeResponse LeaveResp)
                            {
                                RT_FAIL_ON_ERROR(LeaveResp, Done);
                                Done.Execute();
                            });
                    });
            });
        });
    });
}

// ============================================================================
// MATCHMAKER TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaRtMatchmakerSpec, "IntegrationTests.NakamaRt.Matchmaker",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

    FNakamaClientConfig  ClientConfig;
    FNakamaSession       Session;
    UWebSocketSubsystem* WSSub = nullptr;

    FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

    TSharedPtr<FJsonObject> MakeMatchmakerAddJson() const
    {
        TSharedPtr<FJsonObject> J = MakeShared<FJsonObject>();
        J->SetNumberField(TEXT("min_count"), 2);
        J->SetNumberField(TEXT("max_count"), 4);
        J->SetStringField(TEXT("query"),     TEXT("*"));
        return J;
    }

    FString ExtractTicket(const FRealtimeResponse& Resp) const
    {
        FString Ticket;
        const TSharedPtr<FJsonObject>* TicketObj;
        if (Resp.Data.IsValid() && Resp.Data->TryGetObjectField(TEXT("matchmaker_ticket"), TicketObj))
        {
            (*TicketObj)->TryGetStringField(TEXT("ticket"), Ticket);
        }
        return Ticket;
    }

END_DEFINE_SPEC(FNakamaRtMatchmakerSpec)

void FNakamaRtMatchmakerSpec::Define()
{
    BeforeEach([this]()
    {
        ClientConfig = FNakamaClientConfig{ RtServerKey, RtHost, RtPort, false };
        WSSub = CreateTestSubsystem();
        WSSub->AddToRoot();
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

    AfterEach([this]()
    {
        if (WSSub) { WSSub->Close(); WSSub->RemoveFromRoot(); WSSub = nullptr; }
    });

    Describe("Add", [this]()
    {
        LatentIt("should add to matchmaker and receive a ticket", [this](const FDoneDelegate& Done)
        {
            WSSub->Connect(MakeConnParams(Session)).Next([this, Done](FRealtimeConnectionResult CR)
            {
                if (!TestFalse("Connect", CR.bError)) { Done.Execute(); return; }

                WSSub->Send(TEXT("matchmaker_add"), MakeMatchmakerAddJson())
                    .Next([this, Done](FRealtimeResponse Resp)
                    {
                        RT_FAIL_ON_ERROR(Resp, Done);
                        FString Ticket = ExtractTicket(Resp);
                        TestFalse("Matchmaker ticket should not be empty", Ticket.IsEmpty());
                        Done.Execute();
                    });
            });
        });
    });

    Describe("Remove", [this]()
    {
        LatentIt("should add to matchmaker and then cancel with the ticket", [this](const FDoneDelegate& Done)
        {
            WSSub->Connect(MakeConnParams(Session)).Next([this, Done](FRealtimeConnectionResult CR)
            {
                if (!TestFalse("Connect", CR.bError)) { Done.Execute(); return; }

                WSSub->Send(TEXT("matchmaker_add"), MakeMatchmakerAddJson())
                    .Next([this, Done](FRealtimeResponse AddResp)
                    {
                        RT_FAIL_ON_ERROR(AddResp, Done);

                        FString Ticket = ExtractTicket(AddResp);
                        if (!TestFalse("Ticket before remove", Ticket.IsEmpty())) { Done.Execute(); return; }

                        TSharedPtr<FJsonObject> RemoveJson = MakeShared<FJsonObject>();
                        RemoveJson->SetStringField(TEXT("ticket"), Ticket);

                        WSSub->Send(TEXT("matchmaker_remove"), RemoveJson)
                            .Next([this, Done](FRealtimeResponse RemoveResp)
                            {
                                RT_FAIL_ON_ERROR(RemoveResp, Done);
                                Done.Execute();
                            });
                    });
            });
        });
    });
}

// ============================================================================
// STATUS TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaRtStatusSpec, "IntegrationTests.NakamaRt.Status",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

    FNakamaClientConfig  ClientConfig;
    FNakamaSession       Session;
    UWebSocketSubsystem* WSSub = nullptr;

    FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaRtStatusSpec)

void FNakamaRtStatusSpec::Define()
{
    BeforeEach([this]()
    {
        ClientConfig = FNakamaClientConfig{ RtServerKey, RtHost, RtPort, false };
        WSSub = CreateTestSubsystem();
        WSSub->AddToRoot();
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

    AfterEach([this]()
    {
        if (WSSub) { WSSub->Close(); WSSub->RemoveFromRoot(); WSSub = nullptr; }
    });

    Describe("Update", [this]()
    {
        LatentIt("should set a user status string", [this](const FDoneDelegate& Done)
        {
            WSSub->Connect(MakeConnParams(Session)).Next([this, Done](FRealtimeConnectionResult CR)
            {
                if (!TestFalse("Connect", CR.bError)) { Done.Execute(); return; }

                TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
                Json->SetStringField(TEXT("status"), TEXT("Playing a game"));

                WSSub->Send(TEXT("status_update"), Json)
                    .Next([this, Done](FRealtimeResponse Resp)
                    {
                        RT_FAIL_ON_ERROR(Resp, Done);
                        Done.Execute();
                    });
            });
        });

        LatentIt("should clear user status by omitting the status field", [this](const FDoneDelegate& Done)
        {
            WSSub->Connect(MakeConnParams(Session)).Next([this, Done](FRealtimeConnectionResult CR)
            {
                if (!TestFalse("Connect", CR.bError)) { Done.Execute(); return; }

                // Sending status_update with no "status" field signals going offline.
                WSSub->Send(TEXT("status_update"), MakeShared<FJsonObject>())
                    .Next([this, Done](FRealtimeResponse Resp)
                    {
                        RT_FAIL_ON_ERROR(Resp, Done);
                        Done.Execute();
                    });
            });
        });
    });

    Describe("Follow", [this]()
    {
        LatentIt("should follow a user ID without error", [this](const FDoneDelegate& Done)
        {
            WSSub->Connect(MakeConnParams(Session)).Next([this, Done](FRealtimeConnectionResult CR)
            {
                if (!TestFalse("Connect", CR.bError)) { Done.Execute(); return; }

                // Use a random UUID — Nakama accepts follow requests for
                // non-existent users and returns an empty presence list.
                TArray<TSharedPtr<FJsonValue>> Ids;
                Ids.Add(MakeShared<FJsonValueString>(GenerateId()));

                TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
                Json->SetArrayField(TEXT("user_ids"), Ids);

                WSSub->Send(TEXT("status_follow"), Json)
                    .Next([this, Done](FRealtimeResponse Resp)
                    {
                        RT_FAIL_ON_ERROR(Resp, Done);
                        Done.Execute();
                    });
            });
        });

        LatentIt("should follow and then unfollow a user ID", [this](const FDoneDelegate& Done)
        {
            WSSub->Connect(MakeConnParams(Session)).Next([this, Done](FRealtimeConnectionResult CR)
            {
                if (!TestFalse("Connect", CR.bError)) { Done.Execute(); return; }

                FString FakeUserId = GenerateId();

                TArray<TSharedPtr<FJsonValue>> FollowIds;
                FollowIds.Add(MakeShared<FJsonValueString>(FakeUserId));

                TSharedPtr<FJsonObject> FollowJson = MakeShared<FJsonObject>();
                FollowJson->SetArrayField(TEXT("user_ids"), FollowIds);

                WSSub->Send(TEXT("status_follow"), FollowJson)
                    .Next([this, Done, FakeUserId](FRealtimeResponse FollowResp)
                    {
                        RT_FAIL_ON_ERROR(FollowResp, Done);

                        TArray<TSharedPtr<FJsonValue>> UnfollowIds;
                        UnfollowIds.Add(MakeShared<FJsonValueString>(FakeUserId));

                        TSharedPtr<FJsonObject> UnfollowJson = MakeShared<FJsonObject>();
                        UnfollowJson->SetArrayField(TEXT("user_ids"), UnfollowIds);

                        WSSub->Send(TEXT("status_unfollow"), UnfollowJson)
                            .Next([this, Done](FRealtimeResponse UnfollowResp)
                            {
                                RT_FAIL_ON_ERROR(UnfollowResp, Done);
                                Done.Execute();
                            });
                    });
            });
        });
    });
}

// ============================================================================
// DELEGATE TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaRtDelegatesSpec, "IntegrationTests.NakamaRt.Delegates",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

    FNakamaClientConfig  ClientConfig;
    FNakamaSession       Session;
    UWebSocketSubsystem* WSSub = nullptr;

    FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaRtDelegatesSpec)

void FNakamaRtDelegatesSpec::Define()
{
    BeforeEach([this]()
    {
        ClientConfig = FNakamaClientConfig{ RtServerKey, RtHost, RtPort, false };
        WSSub = CreateTestSubsystem();
        WSSub->AddToRoot();
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

    AfterEach([this]()
    {
        if (WSSub) { WSSub->Close(); WSSub->RemoveFromRoot(); WSSub = nullptr; }
    });

    Describe("MessageSent", [this]()
    {
        LatentIt("should fire the MessageSent delegate when a message is dispatched", [this](const FDoneDelegate& Done)
        {
            WSSub->Connect(MakeConnParams(Session)).Next([this, Done](FRealtimeConnectionResult CR)
            {
                if (!TestFalse("Connect", CR.bError)) { Done.Execute(); return; }

                // Use a shared handle so we can self-remove; a shared bool prevents
                // double-completion if the delegate fires more than once during the test.
                TSharedRef<FDelegateHandle> Handle = MakeShared<FDelegateHandle>();
                TSharedRef<bool> bFired = MakeShared<bool>(false);

                *Handle = WSSub->MessageSent.AddLambda(
                    [this, Done, Handle, bFired](const FString& Message)
                    {
                        if (*bFired) return;
                        *bFired = true;
                        TestFalse("MessageSent payload should not be empty", Message.IsEmpty());
                        Done.Execute();
                    });

                // Trigger a send — we don't await the response future here.
                WSSub->Send(TEXT("ping"), MakeShared<FJsonObject>());
            });
        });
    });

    Describe("ServerResponseReceived", [this]()
    {
        LatentIt("should fire ServerResponseReceived when the server replies", [this](const FDoneDelegate& Done)
        {
            WSSub->Connect(MakeConnParams(Session)).Next([this, Done](FRealtimeConnectionResult CR)
            {
                if (!TestFalse("Connect", CR.bError)) { Done.Execute(); return; }

                TSharedRef<FDelegateHandle> Handle = MakeShared<FDelegateHandle>();
                TSharedRef<bool> bFired = MakeShared<bool>(false);

                *Handle = WSSub->ServerResponseReceived.AddLambda(
                    [this, Done, Handle, bFired](const FString& Message)
                    {
                        if (*bFired) return;
                        *bFired = true;
                        TestFalse("ServerResponseReceived payload should not be empty", Message.IsEmpty());
                        Done.Execute();
                    });

                WSSub->Send(TEXT("ping"), MakeShared<FJsonObject>());
            });
        });

        LatentIt("should fire ServerResponseReceived for every distinct response", [this](const FDoneDelegate& Done)
        {
            WSSub->Connect(MakeConnParams(Session)).Next([this, Done](FRealtimeConnectionResult CR)
            {
                if (!TestFalse("Connect", CR.bError)) { Done.Execute(); return; }

                constexpr int32 NumSends = 3;
                TSharedRef<TAtomic<int32>> FireCount = MakeShared<TAtomic<int32>>(0);
                TSharedRef<FDelegateHandle> Handle   = MakeShared<FDelegateHandle>();

                *Handle = WSSub->ServerResponseReceived.AddLambda(
                    [this, Done, Handle, FireCount](const FString&)
                    {
                        if (++(*FireCount) == NumSends)
                        {
                            Done.Execute();
                        }
                    });

                for (int32 i = 0; i < NumSends; ++i)
                {
                    WSSub->Send(TEXT("ping"), MakeShared<FJsonObject>());
                }
            });
        });
    });
}
