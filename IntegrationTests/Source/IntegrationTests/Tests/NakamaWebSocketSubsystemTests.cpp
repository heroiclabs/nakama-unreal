/**
 * Nakama Realtime (WebSocket) Integration Test Suite
 *
 * Tests UNakamaWebSocketSubsystem connection lifecycle, request/response round-trips,
 * delegate notifications, reconnection, error paths, and concurrent requests.
 *
 * Requires a running Nakama server (IntegrationTests/server/docker-compose.yml).
 *
 * Run with:
 *   -ExecCmds="Automation RunTests IntegrationTests.NakamaWebSocketSubsystem"
 */

#include <atomic>
#include "Misc/AutomationTest.h"
#include "Misc/Guid.h"
#include "Dom/JsonObject.h"
#include "Nakama.h"
#include "NakamaWebSocketSubsystem.h"
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
    FNakamaWebSocketConnectionParams MakeConnParams(const FNakamaSession& Session,
                                             int32 OverridePort = RtPort)
    {
        FNakamaWebSocketConnectionParams P;
        P.Host                = RtHost;
        P.Port                = OverridePort;
        P.Token               = Session.Token;
        P.PingIntervalSeconds = 60.0f;
        P.bUseSSL             = false;
        return P;
    }

    /** Create a standalone UNakamaWebSocketSubsystem for testing.
     *
     *  UNakamaWebSocketSubsystem::Initialize() only loads the WebSockets module;
     *  none of its actual Connect/Send/Close logic depends on a UGameInstance
     *  outer.  We therefore create the object directly and ensure the module is
     *  loaded, skipping the subsystem-collection machinery entirely.
     *
     *  The caller must AddToRoot() the returned object and RemoveFromRoot()
     *  after use. */
    UNakamaWebSocketSubsystem* CreateTestSubsystem()
    {
        if (!FModuleManager::Get().IsModuleLoaded(TEXT("WebSockets")))
        {
            FModuleManager::Get().LoadModule(TEXT("WebSockets"));
        }
        // UNakamaWebSocketSubsystem has ClassWithin=UGameInstance (UGameInstanceSubsystem),
        // so it must have a UGameInstance outer to satisfy UE's ensure.
        UGameInstance* TempInstance = NewObject<UGameInstance>(GetTransientPackage());
        return NewObject<UNakamaWebSocketSubsystem>(TempInstance);
    }
}

/**
 * Fails the current test and calls Done when a FNakamaWebSocketResponse carries an
 * error.  Use inside a .Next() callback that expects success.
 */
#define WSS_FAIL_ON_ERROR(Resp, Done)                                                    \
    if ((Resp).ErrorCode != ENakamaWebSocketError::None) {                              \
        AddError(TEXT("Unexpected realtime error in response"));                        \
        (Done).Execute();                                                               \
        return;                                                                         \
    }

// ============================================================================
// CONNECTION TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaWebSocketSubsystemConnectionSpec, "IntegrationTests.NakamaWebSocketSubsystem.Connection",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

    FNakamaClientConfig  ClientConfig;
    FNakamaSession       Session;
    UNakamaWebSocketSubsystem* WSSub = nullptr;

    FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaWebSocketSubsystemConnectionSpec)

void FNakamaWebSocketSubsystemConnectionSpec::Define()
{
    BeforeEach([this]()
    {
        ClientConfig = FNakamaClientConfig{ RtServerKey, RtHost, RtPort, false };
        WSSub = CreateTestSubsystem();
        WSSub->AddToRoot();
    });

    LatentBeforeEach([this](const FDoneDelegate& Done)
    {
        Nakama::AuthenticateCustom(ClientConfig, GenerateId(), true, TEXT(""))
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

    LatentAfterEach([this](const FDoneDelegate& Done)
    {
        if (WSSub)
        {
            WSSub->Close();
            WSSub->RemoveFromRoot();
            WSSub = nullptr;
        }

        if (Session.Token.IsEmpty()) { Done.Execute(); return; }
        Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
    });

    // -----------------------------------------------------------------------
    // Success path
    // -----------------------------------------------------------------------

    Describe("Success", [this]()
    {
        LatentIt("should connect with a valid session token", [this](const FDoneDelegate& Done)
        {
            WSSub->Connect(MakeConnParams(Session)).Next([this, Done](FNakamaWebSocketConnectionResult Result)
            {
                TestFalse("Connection should succeed (bError = false)", Result.ErrorCode != ENakamaWebSocketError::None);
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
            FNakamaWebSocketConnectionParams Bad = MakeConnParams(Session);
            Bad.Token = TEXT("not.a.valid.jwt");

            WSSub->Connect(Bad).Next([this, Done](FNakamaWebSocketConnectionResult Result)
            {
                TestTrue("Connection with invalid token should report error", Result.ErrorCode != ENakamaWebSocketError::None);
                Done.Execute();
            });
        });

        LatentIt("should fail with an empty token", [this](const FDoneDelegate& Done)
        {
            FNakamaWebSocketConnectionParams Bad = MakeConnParams(Session);
            Bad.Token = TEXT("");

            WSSub->Connect(Bad).Next([this, Done](FNakamaWebSocketConnectionResult Result)
            {
                TestTrue("Connection with empty token should report error", Result.ErrorCode != ENakamaWebSocketError::None);
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
            FNakamaWebSocketConnectionParams Bad = MakeConnParams(Session, 19999);

            WSSub->Connect(Bad).Next([this, Done](FNakamaWebSocketConnectionResult Result)
            {
                TestTrue("Connection to unreachable port should report error", Result.ErrorCode != ENakamaWebSocketError::None);
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
            WSSub->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult First) -> TNakamaFuture<FNakamaWebSocketConnectionResult>
                {
                    TestFalse("First connection should succeed", First.ErrorCode != ENakamaWebSocketError::None);
                    WSSub->Close();
                    return WSSub->Connect(MakeConnParams(Session));
                })
                .Next([this, Done](FNakamaWebSocketConnectionResult Second)
                {
                    TestFalse("Connection after explicit Close should succeed", Second.ErrorCode != ENakamaWebSocketError::None);
                    Done.Execute();
                });
        });

        LatentIt("should accept a new Connect while already connected", [this](const FDoneDelegate& Done)
        {
            // A second Connect while already connected — the subsystem should
            // auto-close the old socket and open a new one.
            WSSub->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult First) -> TNakamaFuture<FNakamaWebSocketConnectionResult>
                {
                    TestFalse("First connection should succeed", First.ErrorCode != ENakamaWebSocketError::None);
                    return WSSub->Connect(MakeConnParams(Session));
                })
                .Next([this, Done](FNakamaWebSocketConnectionResult Second)
                {
                    TestFalse("Second Connect while already connected should succeed", Second.ErrorCode != ENakamaWebSocketError::None);
                    Done.Execute();
                });
        });

        LatentIt("should be usable after reconnect (ping round-trip)", [this](const FDoneDelegate& Done)
        {
            WSSub->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult First) -> TNakamaFuture<FNakamaWebSocketConnectionResult>
                {
                    TestFalse("First connection", First.ErrorCode != ENakamaWebSocketError::None);
                    WSSub->Close();
                    return WSSub->Connect(MakeConnParams(Session));
                })
                .Next([this](FNakamaWebSocketConnectionResult Second) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    TestFalse("Reconnection", Second.ErrorCode != ENakamaWebSocketError::None);
                    return WSSub->Send(TEXT("ping"), MakeShared<FJsonObject>());
                })
                .Next([this, Done](FNakamaWebSocketResponse Resp)
                {
                    TestFalse("Ping after reconnect should succeed", Resp.ErrorCode != ENakamaWebSocketError::None);
                    Done.Execute();
                });
        });
    });
}

// ============================================================================
// PING TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaWebSocketSubsystemPingSpec, "IntegrationTests.NakamaWebSocketSubsystem.Ping",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

    FNakamaClientConfig  ClientConfig;
    FNakamaSession       Session;
    UNakamaWebSocketSubsystem* WSSub = nullptr;

    FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaWebSocketSubsystemPingSpec)

void FNakamaWebSocketSubsystemPingSpec::Define()
{
    BeforeEach([this]()
    {
        ClientConfig = FNakamaClientConfig{ RtServerKey, RtHost, RtPort, false };
        WSSub = CreateTestSubsystem();
        WSSub->AddToRoot();
    });

    LatentBeforeEach([this](const FDoneDelegate& Done)
    {
        Nakama::AuthenticateCustom(ClientConfig, GenerateId(), true, TEXT(""))
            .Next([this, Done](FNakamaSessionResult R)
            {
                if (R.bIsError) { AddError(FString::Printf(TEXT("Auth: %s"), *R.Error.Message)); Done.Execute(); return; }
                Session = R.Value;
                Done.Execute();
            });
    });

    LatentAfterEach([this](const FDoneDelegate& Done)
    {
        if (WSSub)
        {
            WSSub->Close();
            WSSub->RemoveFromRoot();
            WSSub = nullptr;
        }

        if (Session.Token.IsEmpty()) { Done.Execute(); return; }
        Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
    });

    Describe("Single", [this]()
    {
        LatentIt("should receive a pong response to a single ping", [this](const FDoneDelegate& Done)
        {
            WSSub->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return WSSub->Send(TEXT("ping"), MakeShared<FJsonObject>());
                })
                .Next([this, Done](FNakamaWebSocketResponse Resp)
                {
                    TestFalse("Ping should receive a non-error pong response", Resp.ErrorCode != ENakamaWebSocketError::None);
                    Done.Execute();
                });
        });
    });

    Describe("AutoPing", [this]()
    {
        LatentIt("should not accumulate pending requests (memory leak regression)", [this](const FDoneDelegate& Done)
        {
            // Use a fast ping interval so ~10 pings fire within 1 second.
            FNakamaWebSocketConnectionParams P = MakeConnParams(Session);
            P.PingIntervalSeconds = 0.1f;

            WSSub->Connect(P).Next([this, Done](FNakamaWebSocketConnectionResult CR)
            {
                TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                if (CR.ErrorCode != ENakamaWebSocketError::None) { Done.Execute(); return; }

                // After 1 s, ~10 auto-pings will have fired. Requests must still be empty.
                TWeakObjectPtr<UNakamaWebSocketSubsystem> WeakSub = WSSub;
                FTSTicker::GetCoreTicker().AddTicker(
                    FTickerDelegate::CreateLambda([this, Done, WeakSub](float) -> bool
                    {
                        if (UNakamaWebSocketSubsystem* Sub = WeakSub.Get())
                        {
                            TestEqual(TEXT("Auto-ping must not leak entries into Requests"), Sub->GetPendingRequestCount(), 0);
                        }
                        Done.Execute();
                        return false;
                    }),
                    1.0f
                );
            });
        });
    });

    Describe("Concurrent", [this]()
    {
        LatentIt("should handle multiple concurrent pings and resolve all of them", [this](const FDoneDelegate& Done)
        {
            WSSub->Connect(MakeConnParams(Session))
                .Next([this, Done](FNakamaWebSocketConnectionResult CR)
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);

                    // Fire several pings simultaneously; track completions with a shared counter.
                    constexpr int32 NumPings = 5;
                    TSharedRef<std::atomic<int32>> Remaining = MakeShared<std::atomic<int32>>(NumPings);

                    for (int32 i = 0; i < NumPings; ++i)
                    {
                        WSSub->Send(TEXT("ping"), MakeShared<FJsonObject>())
                            .Next([this, Done, Remaining](FNakamaWebSocketResponse Resp)
                            {
                                if (Resp.ErrorCode != ENakamaWebSocketError::None)
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
            WSSub->Connect(MakeConnParams(Session))
                .Next([this, Done](FNakamaWebSocketConnectionResult CR)
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);

                    // Send a match_create and two pings simultaneously; all three
                    // must resolve without error.
                    TSharedRef<std::atomic<int32>> Remaining = MakeShared<std::atomic<int32>>(3);

                    auto Decrement = [this, Done, Remaining](FNakamaWebSocketResponse Resp)
                    {
                        if (Resp.ErrorCode != ENakamaWebSocketError::None) AddError(TEXT("Interleaved request returned an error"));
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

BEGIN_DEFINE_SPEC(FNakamaWebSocketSubsystemChannelSpec, "IntegrationTests.NakamaWebSocketSubsystem.Channel",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

    FNakamaClientConfig  ClientConfig;
    FNakamaSession       Session;
    UNakamaWebSocketSubsystem* WSSub = nullptr;

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

    FString ExtractChannelId(const FNakamaWebSocketResponse& Resp) const
    {
        FString Id;
        const TSharedPtr<FJsonObject>* ChannelObj;
        if (Resp.Data.IsValid() && Resp.Data->TryGetObjectField(TEXT("channel"), ChannelObj))
        {
            (*ChannelObj)->TryGetStringField(TEXT("id"), Id);
        }
        return Id;
    }

END_DEFINE_SPEC(FNakamaWebSocketSubsystemChannelSpec)

void FNakamaWebSocketSubsystemChannelSpec::Define()
{
    BeforeEach([this]()
    {
        ClientConfig = FNakamaClientConfig{ RtServerKey, RtHost, RtPort, false };
        WSSub = CreateTestSubsystem();
        WSSub->AddToRoot();
    });

    LatentBeforeEach([this](const FDoneDelegate& Done)
    {
        Nakama::AuthenticateCustom(ClientConfig,  GenerateId(), true, TEXT(""))
            .Next([this, Done](FNakamaSessionResult R)
            {
                if (R.bIsError) { AddError(FString::Printf(TEXT("Auth: %s"), *R.Error.Message)); Done.Execute(); return; }
                Session = R.Value;
                Done.Execute();
            });
    });

    LatentAfterEach([this](const FDoneDelegate& Done)
    {
        if (WSSub)
        {
            WSSub->Close();
            WSSub->RemoveFromRoot();
            WSSub = nullptr;
        }

        if (Session.Token.IsEmpty()) { Done.Execute(); return; }
        Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
    });

    Describe("Join", [this]()
    {
        LatentIt("should join a room channel and receive a channel response", [this](const FDoneDelegate& Done)
        {
            WSSub->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return WSSub->Send(TEXT("channel_join"), MakeChannelJoinJson(GenerateRoomName()));
                })
                .Next([this, Done](FNakamaWebSocketResponse Resp)
                {
                    WSS_FAIL_ON_ERROR(Resp, Done);
                    FString ChannelId = ExtractChannelId(Resp);
                    TestFalse("Joined channel should have a non-empty ID", ChannelId.IsEmpty());
                    Done.Execute();
                });
        });
    });

    Describe("SendMessage", [this]()
    {
        LatentIt("should send a message to a room channel and receive an ack", [this](const FDoneDelegate& Done)
        {
            WSSub->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return WSSub->Send(TEXT("channel_join"), MakeChannelJoinJson(GenerateRoomName()));
                })
                .Next([this](FNakamaWebSocketResponse JoinResp) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    if (JoinResp.ErrorCode != ENakamaWebSocketError::None)
                    {
                        AddError(TEXT("channel_join failed"));
                        return MakeCompletedFuture<FNakamaWebSocketResponse>(JoinResp);
                    }
                    FString ChannelId = ExtractChannelId(JoinResp);
                    TestFalse("Channel ID from join", ChannelId.IsEmpty());

                    TSharedPtr<FJsonObject> SendJson = MakeShared<FJsonObject>();
                    SendJson->SetStringField(TEXT("channel_id"), ChannelId);
                    SendJson->SetStringField(TEXT("content"),    TEXT("{\"msg\":\"hello\"}"));
                    return WSSub->Send(TEXT("channel_message_send"), SendJson);
                })
                .Next([this, Done](FNakamaWebSocketResponse SendResp)
                {
                    WSS_FAIL_ON_ERROR(SendResp, Done);
                    TestTrue("Send ack response has data", SendResp.Data.IsValid());
                    Done.Execute();
                });
        });
    });

    Describe("Leave", [this]()
    {
        LatentIt("should leave a channel successfully", [this](const FDoneDelegate& Done)
        {
            WSSub->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return WSSub->Send(TEXT("channel_join"), MakeChannelJoinJson(GenerateRoomName()));
                })
                .Next([this](FNakamaWebSocketResponse JoinResp) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    if (JoinResp.ErrorCode != ENakamaWebSocketError::None)
                    {
                        AddError(TEXT("channel_join failed"));
                        return MakeCompletedFuture<FNakamaWebSocketResponse>(JoinResp);
                    }
                    FString ChannelId = ExtractChannelId(JoinResp);
                    TestFalse("Channel ID from join", ChannelId.IsEmpty());

                    TSharedPtr<FJsonObject> LeaveJson = MakeShared<FJsonObject>();
                    LeaveJson->SetStringField(TEXT("channel_id"), ChannelId);
                    return WSSub->Send(TEXT("channel_leave"), LeaveJson);
                })
                .Next([this, Done](FNakamaWebSocketResponse LeaveResp)
                {
                    WSS_FAIL_ON_ERROR(LeaveResp, Done);
                    Done.Execute();
                });
        });
    });
}

// ============================================================================
// MATCH TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaWebSocketSubsystemMatchSpec, "IntegrationTests.NakamaWebSocketSubsystem.Match",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

    FNakamaClientConfig  ClientConfig;
    FNakamaSession       Session;
    UNakamaWebSocketSubsystem* WSSub = nullptr;

    FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

    FString ExtractMatchId(const FNakamaWebSocketResponse& Resp) const
    {
        FString Id;
        const TSharedPtr<FJsonObject>* MatchObj;
        if (Resp.Data.IsValid() && Resp.Data->TryGetObjectField(TEXT("match"), MatchObj))
        {
            (*MatchObj)->TryGetStringField(TEXT("match_id"), Id);
        }
        return Id;
    }

END_DEFINE_SPEC(FNakamaWebSocketSubsystemMatchSpec)

void FNakamaWebSocketSubsystemMatchSpec::Define()
{
    BeforeEach([this]()
    {
        ClientConfig = FNakamaClientConfig{ RtServerKey, RtHost, RtPort, false };
        WSSub = CreateTestSubsystem();
        WSSub->AddToRoot();
    });

    LatentBeforeEach([this](const FDoneDelegate& Done)
    {
        Nakama::AuthenticateCustom(ClientConfig,  GenerateId(), true, TEXT(""))
            .Next([this, Done](FNakamaSessionResult R)
            {
                if (R.bIsError) { AddError(FString::Printf(TEXT("Auth: %s"), *R.Error.Message)); Done.Execute(); return; }
                Session = R.Value;
                Done.Execute();
            });
    });

    LatentAfterEach([this](const FDoneDelegate& Done)
    {
        if (WSSub)
        {
            WSSub->Close();
            WSSub->RemoveFromRoot();
            WSSub = nullptr;
        }

        if (Session.Token.IsEmpty()) { Done.Execute(); return; }
        Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
    });

    Describe("Create", [this]()
    {
        LatentIt("should create a relayed match and receive a match_id", [this](const FDoneDelegate& Done)
        {
            WSSub->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return WSSub->Send(TEXT("match_create"), MakeShared<FJsonObject>());
                })
                .Next([this, Done](FNakamaWebSocketResponse Resp)
                {
                    WSS_FAIL_ON_ERROR(Resp, Done);
                    FString MatchId = ExtractMatchId(Resp);
                    TestFalse("Created match should have a non-empty match_id", MatchId.IsEmpty());
                    Done.Execute();
                });
        });
    });

    Describe("Leave", [this]()
    {
        LatentIt("should leave a match without error", [this](const FDoneDelegate& Done)
        {
            WSSub->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return WSSub->Send(TEXT("match_create"), MakeShared<FJsonObject>());
                })
                .Next([this](FNakamaWebSocketResponse CreateResp) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    if (CreateResp.ErrorCode != ENakamaWebSocketError::None)
                    {
                        AddError(TEXT("match_create failed"));
                        return MakeCompletedFuture<FNakamaWebSocketResponse>(CreateResp);
                    }
                    FString MatchId = ExtractMatchId(CreateResp);
                    TestFalse("Match ID from create", MatchId.IsEmpty());

                    TSharedPtr<FJsonObject> LeaveJson = MakeShared<FJsonObject>();
                    LeaveJson->SetStringField(TEXT("match_id"), MatchId);
                    return WSSub->Send(TEXT("match_leave"), LeaveJson);
                })
                .Next([this, Done](FNakamaWebSocketResponse LeaveResp)
                {
                    WSS_FAIL_ON_ERROR(LeaveResp, Done);
                    Done.Execute();
                });
        });
    });
}

// ============================================================================
// MATCHMAKER TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaWebSocketSubsystemMatchmakerSpec, "IntegrationTests.NakamaWebSocketSubsystem.Matchmaker",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

    FNakamaClientConfig  ClientConfig;
    FNakamaSession       Session;
    UNakamaWebSocketSubsystem* WSSub = nullptr;

    FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

    TSharedPtr<FJsonObject> MakeMatchmakerAddJson() const
    {
        TSharedPtr<FJsonObject> J = MakeShared<FJsonObject>();
        J->SetNumberField(TEXT("min_count"), 2);
        J->SetNumberField(TEXT("max_count"), 4);
        J->SetStringField(TEXT("query"),     TEXT("*"));
        return J;
    }

    FString ExtractTicket(const FNakamaWebSocketResponse& Resp) const
    {
        FString Ticket;
        const TSharedPtr<FJsonObject>* TicketObj;
        if (Resp.Data.IsValid() && Resp.Data->TryGetObjectField(TEXT("matchmaker_ticket"), TicketObj))
        {
            (*TicketObj)->TryGetStringField(TEXT("ticket"), Ticket);
        }
        return Ticket;
    }

END_DEFINE_SPEC(FNakamaWebSocketSubsystemMatchmakerSpec)

void FNakamaWebSocketSubsystemMatchmakerSpec::Define()
{
    BeforeEach([this]()
    {
        ClientConfig = FNakamaClientConfig{ RtServerKey, RtHost, RtPort, false };
        WSSub = CreateTestSubsystem();
        WSSub->AddToRoot();
    });

    LatentBeforeEach([this](const FDoneDelegate& Done)
    {
        Nakama::AuthenticateCustom(ClientConfig,  GenerateId(), true, TEXT(""))
            .Next([this, Done](FNakamaSessionResult R)
            {
                if (R.bIsError) { AddError(FString::Printf(TEXT("Auth: %s"), *R.Error.Message)); Done.Execute(); return; }
                Session = R.Value;
                Done.Execute();
            });
    });

    LatentAfterEach([this](const FDoneDelegate& Done)
    {
        if (WSSub)
        {
            WSSub->Close();
            WSSub->RemoveFromRoot();
            WSSub = nullptr;
        }

        if (Session.Token.IsEmpty()) { Done.Execute(); return; }
        Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
    });

    Describe("Add", [this]()
    {
        LatentIt("should add to matchmaker and receive a ticket", [this](const FDoneDelegate& Done)
        {
            WSSub->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return WSSub->Send(TEXT("matchmaker_add"), MakeMatchmakerAddJson());
                })
                .Next([this, Done](FNakamaWebSocketResponse Resp)
                {
                    WSS_FAIL_ON_ERROR(Resp, Done);
                    FString Ticket = ExtractTicket(Resp);
                    TestFalse("Matchmaker ticket should not be empty", Ticket.IsEmpty());
                    Done.Execute();
                });
        });
    });

    Describe("Remove", [this]()
    {
        LatentIt("should add to matchmaker and then cancel with the ticket", [this](const FDoneDelegate& Done)
        {
            WSSub->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return WSSub->Send(TEXT("matchmaker_add"), MakeMatchmakerAddJson());
                })
                .Next([this](FNakamaWebSocketResponse AddResp) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    if (AddResp.ErrorCode != ENakamaWebSocketError::None)
                    {
                        AddError(TEXT("matchmaker_add failed"));
                        return MakeCompletedFuture<FNakamaWebSocketResponse>(AddResp);
                    }
                    FString Ticket = ExtractTicket(AddResp);
                    TestFalse("Ticket before remove", Ticket.IsEmpty());

                    TSharedPtr<FJsonObject> RemoveJson = MakeShared<FJsonObject>();
                    RemoveJson->SetStringField(TEXT("ticket"), Ticket);
                    return WSSub->Send(TEXT("matchmaker_remove"), RemoveJson);
                })
                .Next([this, Done](FNakamaWebSocketResponse RemoveResp)
                {
                    WSS_FAIL_ON_ERROR(RemoveResp, Done);
                    Done.Execute();
                });
        });
    });
}

// ============================================================================
// STATUS TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaWebSocketSubsystemStatusSpec, "IntegrationTests.NakamaWebSocketSubsystem.Status",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

    FNakamaClientConfig  ClientConfig;
    FNakamaSession       Session;
    UNakamaWebSocketSubsystem* WSSub = nullptr;

    FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaWebSocketSubsystemStatusSpec)

void FNakamaWebSocketSubsystemStatusSpec::Define()
{
    BeforeEach([this]()
    {
        ClientConfig = FNakamaClientConfig{ RtServerKey, RtHost, RtPort, false };
        WSSub = CreateTestSubsystem();
        WSSub->AddToRoot();
    });

    LatentBeforeEach([this](const FDoneDelegate& Done)
    {
        Nakama::AuthenticateCustom(ClientConfig,  GenerateId(), true, TEXT(""))
            .Next([this, Done](FNakamaSessionResult R)
            {
                if (R.bIsError) { AddError(FString::Printf(TEXT("Auth: %s"), *R.Error.Message)); Done.Execute(); return; }
                Session = R.Value;
                Done.Execute();
            });
    });

    LatentAfterEach([this](const FDoneDelegate& Done)
    {
        if (WSSub)
        {
            WSSub->Close();
            WSSub->RemoveFromRoot();
            WSSub = nullptr;
        }

        if (Session.Token.IsEmpty()) { Done.Execute(); return; }
        Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
    });

    Describe("Update", [this]()
    {
        LatentIt("should set a user status string", [this](const FDoneDelegate& Done)
        {
            TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
            Json->SetStringField(TEXT("status"), TEXT("Playing a game"));

            WSSub->Connect(MakeConnParams(Session))
                .Next([this, Json](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return WSSub->Send(TEXT("status_update"), Json);
                })
                .Next([this, Done](FNakamaWebSocketResponse Resp)
                {
                    WSS_FAIL_ON_ERROR(Resp, Done);
                    Done.Execute();
                });
        });

        LatentIt("should clear user status by omitting the status field", [this](const FDoneDelegate& Done)
        {
            // Sending status_update with no "status" field signals going offline.
            WSSub->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return WSSub->Send(TEXT("status_update"), MakeShared<FJsonObject>());
                })
                .Next([this, Done](FNakamaWebSocketResponse Resp)
                {
                    WSS_FAIL_ON_ERROR(Resp, Done);
                    Done.Execute();
                });
        });
    });

    Describe("Follow", [this]()
    {
        LatentIt("should follow a user ID without error", [this](const FDoneDelegate& Done)
        {
            // Use a random UUID — Nakama accepts follow requests for
            // non-existent users and returns an empty presence list.
            TArray<TSharedPtr<FJsonValue>> Ids;
            Ids.Add(MakeShared<FJsonValueString>(GenerateId()));
            TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
            Json->SetArrayField(TEXT("user_ids"), Ids);

            WSSub->Connect(MakeConnParams(Session))
                .Next([this, Json](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return WSSub->Send(TEXT("status_follow"), Json);
                })
                .Next([this, Done](FNakamaWebSocketResponse Resp)
                {
                    WSS_FAIL_ON_ERROR(Resp, Done);
                    Done.Execute();
                });
        });

        LatentIt("should follow and then unfollow a user ID", [this](const FDoneDelegate& Done)
        {
            FString FakeUserId = GenerateId();

            TArray<TSharedPtr<FJsonValue>> FollowIds;
            FollowIds.Add(MakeShared<FJsonValueString>(FakeUserId));
            TSharedPtr<FJsonObject> FollowJson = MakeShared<FJsonObject>();
            FollowJson->SetArrayField(TEXT("user_ids"), FollowIds);

            WSSub->Connect(MakeConnParams(Session))
                .Next([this, FollowJson](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return WSSub->Send(TEXT("status_follow"), FollowJson);
                })
                .Next([this, FakeUserId](FNakamaWebSocketResponse FollowResp) -> TNakamaFuture<FNakamaWebSocketResponse>
                {
                    if (FollowResp.ErrorCode != ENakamaWebSocketError::None)
                    {
                        AddError(TEXT("status_follow failed"));
                        return MakeCompletedFuture<FNakamaWebSocketResponse>(FollowResp);
                    }
                    TArray<TSharedPtr<FJsonValue>> UnfollowIds;
                    UnfollowIds.Add(MakeShared<FJsonValueString>(FakeUserId));
                    TSharedPtr<FJsonObject> UnfollowJson = MakeShared<FJsonObject>();
                    UnfollowJson->SetArrayField(TEXT("user_ids"), UnfollowIds);
                    return WSSub->Send(TEXT("status_unfollow"), UnfollowJson);
                })
                .Next([this, Done](FNakamaWebSocketResponse UnfollowResp)
                {
                    WSS_FAIL_ON_ERROR(UnfollowResp, Done);
                    Done.Execute();
                });
        });
    });
}

// ============================================================================
// DELEGATE TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaWebSocketSubsystemDelegatesSpec, "IntegrationTests.NakamaWebSocketSubsystem.Delegates",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

    FNakamaClientConfig  ClientConfig;
    FNakamaSession       Session;
    UNakamaWebSocketSubsystem* WSSub = nullptr;

    FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaWebSocketSubsystemDelegatesSpec)

void FNakamaWebSocketSubsystemDelegatesSpec::Define()
{
    BeforeEach([this]()
    {
        ClientConfig = FNakamaClientConfig{ RtServerKey, RtHost, RtPort, false };
        WSSub = CreateTestSubsystem();
        WSSub->AddToRoot();
    });

    LatentBeforeEach([this](const FDoneDelegate& Done)
    {
        Nakama::AuthenticateCustom(ClientConfig,  GenerateId(), true, TEXT(""))
            .Next([this, Done](FNakamaSessionResult R)
            {
                if (R.bIsError) { AddError(FString::Printf(TEXT("Auth: %s"), *R.Error.Message)); Done.Execute(); return; }
                Session = R.Value;
                Done.Execute();
            });
    });

    LatentAfterEach([this](const FDoneDelegate& Done)
    {
        if (WSSub)
        {
            WSSub->Close();
            WSSub->RemoveFromRoot();
            WSSub = nullptr;
        }

        if (Session.Token.IsEmpty()) { Done.Execute(); return; }
        Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
    });

    Describe("MessageSent", [this]()
    {
        LatentIt("should fire the MessageSent delegate when a message is dispatched", [this](const FDoneDelegate& Done)
        {
            WSSub->Connect(MakeConnParams(Session))
                .Next([this, Done](FNakamaWebSocketConnectionResult CR)
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);

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
            WSSub->Connect(MakeConnParams(Session))
                .Next([this, Done](FNakamaWebSocketConnectionResult CR)
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);

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

                    WSSub->Send(TEXT("match_create"), MakeShared<FJsonObject>());
                });
        });

        LatentIt("should fire ServerResponseReceived for every distinct response", [this](const FDoneDelegate& Done)
        {
            WSSub->Connect(MakeConnParams(Session))
                .Next([this, Done](FNakamaWebSocketConnectionResult CR)
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);

                    constexpr int32 NumSends = 3;
                    TSharedRef<std::atomic<int32>> FireCount = MakeShared<std::atomic<int32>>(0);
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
                        WSSub->Send(TEXT("match_create"), MakeShared<FJsonObject>());
                    }
                });
        });
    });
}

// ============================================================================
// DATA RACE REGRESSION TEST
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaWebSocketSubsystemDataRaceSpec,
    "IntegrationTests.NakamaWebSocketSubsystem.DataRace",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

    FNakamaClientConfig  ClientConfig;
    FNakamaSession       Session;
    UNakamaWebSocketSubsystem* WSSub = nullptr;

    FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaWebSocketSubsystemDataRaceSpec)

void FNakamaWebSocketSubsystemDataRaceSpec::Define()
{
    BeforeEach([this]()
    {
        ClientConfig = FNakamaClientConfig{ RtServerKey, RtHost, RtPort, false };
        WSSub = CreateTestSubsystem();
        WSSub->AddToRoot();
    });

    LatentBeforeEach([this](const FDoneDelegate& Done)
    {
        Nakama::AuthenticateCustom(ClientConfig,  GenerateId(), true, TEXT(""))
            .Next([this, Done](FNakamaSessionResult R)
            {
                if (R.bIsError) { AddError(FString::Printf(TEXT("Auth: %s"), *R.Error.Message)); Done.Execute(); return; }
                Session = R.Value;
                Done.Execute();
            });
    });

    LatentAfterEach([this](const FDoneDelegate& Done)
    {
        if (WSSub)
        {
            WSSub->Close();
            WSSub->RemoveFromRoot();
            WSSub = nullptr;
        }
        if (Session.Token.IsEmpty()) { Done.Execute(); return; }
        Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
    });

    Describe("bIsConnected", [this]()
    {
        LatentIt("should not crash when Send races with Connect on bIsConnected",
            [this](const FDoneDelegate& Done)
        {
            // Stress test: Connect fires on the WS thread while the game thread
            // hammers Send(). With std::atomic<bool> bIsConnected this is safe;
            // with a plain bool it would be a C++11 data race (UB).
            WSSub->Connect(MakeConnParams(Session));

            constexpr int32 Iterations = 500;
            for (int32 i = 0; i < Iterations; ++i)
            {
                WSSub->Send(TEXT("match_create"), MakeShared<FJsonObject>());
                FPlatformProcess::SleepNoStats(0.0f);
            }

            WSSub->Close();
            Done.Execute();
        });
    });
}
