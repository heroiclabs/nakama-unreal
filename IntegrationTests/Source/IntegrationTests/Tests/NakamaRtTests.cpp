/**
 * NakamaRt Integration Test Suite
 *
 * Tests the typed NakamaRt namespace API layer: ChannelJoin, MatchCreate,
 * MatchmakerAdd, StatusUpdate, PartyCreate, and Ping.
 *
 * Each spec creates an isolated FNakamaRtConnection so the connection is
 * fresh per test, matching the isolation strategy used in
 * NakamaWebSocketSubsystemTests.cpp.
 *
 * Requires a running Nakama server (IntegrationTests/server/docker-compose.yml).
 *
 * Run with:
 *   -ExecCmds="Automation RunTests IntegrationTests.NakamaRt"
 */

#include "NakamaClient.h"
#include "NakamaClientConfig.h"
#include "NakamaSession.h"
#include "Misc/AutomationTest.h"
#include "Misc/Guid.h"
#include "Modules/ModuleManager.h"
#include "NakamaRt.h"
#include "NakamaRtConnection.h"

using namespace Nakama;
using namespace NakamaRt;

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

    /** Ensure the WebSockets module is loaded before creating connections. */
    void EnsureWebSocketsLoaded()
    {
        if (!FModuleManager::Get().IsModuleLoaded(TEXT("WebSockets")))
        {
            FModuleManager::Get().LoadModule(TEXT("WebSockets"));
        }
    }
}

/**
 * Fails the current test and calls Done when a typed FNakamaRtResult carries
 * an error.  Use only in terminal .Next() callbacks (it contains a bare return).
 */
#define RT_FAIL_ON_ERROR(Result, Done)                                                                                    \
    if (!(Result).bIsSuccess) {                                                                                           \
        AddError(FString::Printf(TEXT("Unexpected realtime error: %s"),                                                   \
            *((Result).Error.IsSet() ? (Result).Error->Message : TEXT("unknown"))));                                      \
        (Done).Execute();                                                                                                  \
        return;                                                                                                            \
    }

// ============================================================================
// PING TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaRtPingSpec, "IntegrationTests.NakamaRtTests.Ping",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

    FNakamaClientConfig ClientConfig;
    FNakamaSession      Session;
    TSharedPtr<FNakamaRtConnection> Connection;

    FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaRtPingSpec)

void FNakamaRtPingSpec::Define()
{
    BeforeEach([this]()
    {
        ClientConfig = FNakamaClientConfig{ RtServerKey, RtHost, RtPort, false };
        EnsureWebSocketsLoaded();
        Connection = MakeShared<FNakamaRtConnection>();
    });

    LatentBeforeEach([this](const FDoneDelegate& Done)
    {
        Nakama::AuthenticateCustom(ClientConfig, true, TEXT(""), GenerateId())
            .Next([this, Done](FNakamaSessionResult R)
            {
                if (R.bIsError) { AddError(FString::Printf(TEXT("Auth: %s"), *R.Error.Message)); Done.Execute(); return; }
                Session = R.Value;
                Done.Execute();
            });
    });

    LatentAfterEach([this](const FDoneDelegate& Done)
    {
        if (Connection) { Connection->Close(); Connection.Reset(); }

        if (Session.Token.IsEmpty()) { Done.Execute(); return; }
        Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
    });

    Describe("Single", [this]()
    {
        LatentIt("should complete a round-trip status update", [this](const FDoneDelegate& Done)
        {
            Connection->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return NakamaRt::StatusUpdate(Connection, TEXT(""));
                })
                .Next([this, Done](FNakamaRtResult<FNakamaRtEmptyResponse> Resp)
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

BEGIN_DEFINE_SPEC(FNakamaRtChannelSpec, "IntegrationTests.NakamaRtTests.Channel",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

    FNakamaClientConfig ClientConfig;
    FNakamaSession      Session;
    TSharedPtr<FNakamaRtConnection> Connection;

    FString GenerateId()       { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }
    FString GenerateRoomName() { return TEXT("rt-test-") + FGuid::NewGuid().ToString(EGuidFormats::Short).Left(8); }

END_DEFINE_SPEC(FNakamaRtChannelSpec)

void FNakamaRtChannelSpec::Define()
{
    BeforeEach([this]()
    {
        ClientConfig = FNakamaClientConfig{ RtServerKey, RtHost, RtPort, false };
        EnsureWebSocketsLoaded();
        Connection = MakeShared<FNakamaRtConnection>();
    });

    LatentBeforeEach([this](const FDoneDelegate& Done)
    {
        Nakama::AuthenticateCustom(ClientConfig, true, TEXT(""), GenerateId())
            .Next([this, Done](FNakamaSessionResult R)
            {
                if (R.bIsError) { AddError(FString::Printf(TEXT("Auth: %s"), *R.Error.Message)); Done.Execute(); return; }
                Session = R.Value;
                Done.Execute();
            });
    });

    LatentAfterEach([this](const FDoneDelegate& Done)
    {
        if (Connection) { Connection->Close(); Connection.Reset(); }

        if (Session.Token.IsEmpty()) { Done.Execute(); return; }
        Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
    });

    // -----------------------------------------------------------------------

    Describe("Join", [this]()
    {
        LatentIt("should join a room channel and receive a channel ID", [this](const FDoneDelegate& Done)
        {
            Connection->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaRtResult<FNakamaRtChannel>>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return NakamaRt::ChannelJoin(Connection, GenerateRoomName(), 1, false, false);
                })
                .Next([this, Done](FNakamaRtResult<FNakamaRtChannel> Resp)
                {
                    RT_FAIL_ON_ERROR(Resp, Done);
                    TestFalse("Joined channel should have a non-empty ID", Resp.Data->Id.IsEmpty());
                    Done.Execute();
                });
        });

        LatentIt("should join with persistence=false and hidden=false as explicit Optional booleans", [this](const FDoneDelegate& Done)
        {
            Connection->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaRtResult<FNakamaRtChannel>>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return NakamaRt::ChannelJoin(Connection, GenerateRoomName(), 1, false, false);
                })
                .Next([this, Done](FNakamaRtResult<FNakamaRtChannel> Resp)
                {
                    RT_FAIL_ON_ERROR(Resp, Done);
                    TestFalse("Channel ID is non-empty", Resp.Data->Id.IsEmpty());
                    Done.Execute();
                });
        });
    });

    Describe("SendMessage", [this]()
    {
        LatentIt("should send a message and receive an ack with a message_id", [this](const FDoneDelegate& Done)
        {
            Connection->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaRtResult<FNakamaRtChannel>>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return NakamaRt::ChannelJoin(Connection, GenerateRoomName(), 1, true, false);
                })
                .Next([this, Done](auto JoinResp) -> TNakamaFuture<FNakamaRtResult<FNakamaRtChannelMessageAck>>
                {
                    if (!JoinResp.bIsSuccess)
                    {
                        AddError(TEXT("ChannelJoin failed"));
                        Done.Execute();
                        FNakamaRtError Err = JoinResp.Error.IsSet() ? *JoinResp.Error : FNakamaRtError{};
                        return MakeCompletedFuture(FNakamaRtResult<FNakamaRtChannelMessageAck>::Failure(Err));
                    }
                    TestFalse("Channel ID from join", JoinResp.Data->Id.IsEmpty());
                    return NakamaRt::ChannelMessageSend(Connection, JoinResp.Data->Id, TEXT("{\"msg\":\"hello\"}"));
                })
                .Next([this, Done](FNakamaRtResult<FNakamaRtChannelMessageAck> Resp)
                {
                    RT_FAIL_ON_ERROR(Resp, Done);
                    TestFalse("Ack should contain a message_id", Resp.Data->MessageId.IsEmpty());
                    Done.Execute();
                });
        });
    });

    Describe("UpdateMessage", [this]()
    {
        LatentIt("should update a sent message without error", [this](const FDoneDelegate& Done)
        {
            Connection->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaRtResult<FNakamaRtChannel>>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return NakamaRt::ChannelJoin(Connection, GenerateRoomName(), 1, true, false);
                })
                .Next([this, Done](auto JoinResp) -> TNakamaFuture<FNakamaRtResult<FNakamaRtChannelMessageAck>>
                {
                    if (!JoinResp.bIsSuccess)
                    {
                        AddError(TEXT("ChannelJoin failed"));
                        Done.Execute();
                        FNakamaRtError Err = JoinResp.Error.IsSet() ? *JoinResp.Error : FNakamaRtError{};
                        return MakeCompletedFuture(FNakamaRtResult<FNakamaRtChannelMessageAck>::Failure(Err));
                    }
                    return NakamaRt::ChannelMessageSend(Connection, JoinResp.Data->Id, TEXT("{\"msg\":\"original\"}"));
                })
                .Next([this, Done](auto SendResp) -> TNakamaFuture<FNakamaRtResult<FNakamaRtChannelMessageAck>>
                {
                    if (!SendResp.bIsSuccess)
                    {
                        AddError(TEXT("ChannelMessageSend failed"));
                        Done.Execute();
                        FNakamaRtError Err = SendResp.Error.IsSet() ? *SendResp.Error : FNakamaRtError{};
                        return MakeCompletedFuture(FNakamaRtResult<FNakamaRtChannelMessageAck>::Failure(Err));
                    }
                    TestFalse("Message ID before update", SendResp.Data->MessageId.IsEmpty());
                    return NakamaRt::ChannelMessageUpdate(Connection, SendResp.Data->ChannelId, SendResp.Data->MessageId, TEXT("{\"msg\":\"updated\"}"));
                })
                .Next([this, Done](FNakamaRtResult<FNakamaRtChannelMessageAck> Resp)
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
            Connection->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaRtResult<FNakamaRtChannel>>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return NakamaRt::ChannelJoin(Connection, GenerateRoomName(), 1, true, false);
                })
                .Next([this, Done](auto JoinResp) -> TNakamaFuture<FNakamaRtResult<FNakamaRtChannelMessageAck>>
                {
                    if (!JoinResp.bIsSuccess)
                    {
                        AddError(TEXT("ChannelJoin failed"));
                        Done.Execute();
                        FNakamaRtError Err = JoinResp.Error.IsSet() ? *JoinResp.Error : FNakamaRtError{};
                        return MakeCompletedFuture(FNakamaRtResult<FNakamaRtChannelMessageAck>::Failure(Err));
                    }
                    return NakamaRt::ChannelMessageSend(Connection, JoinResp.Data->Id, TEXT("{\"msg\":\"to delete\"}"));
                })
                .Next([this, Done](auto SendResp) -> TNakamaFuture<FNakamaRtResult<FNakamaRtChannelMessageAck>>
                {
                    if (!SendResp.bIsSuccess)
                    {
                        AddError(TEXT("ChannelMessageSend failed"));
                        Done.Execute();
                        FNakamaRtError Err = SendResp.Error.IsSet() ? *SendResp.Error : FNakamaRtError{};
                        return MakeCompletedFuture(FNakamaRtResult<FNakamaRtChannelMessageAck>::Failure(Err));
                    }
                    return NakamaRt::ChannelMessageRemove(Connection, SendResp.Data->ChannelId, SendResp.Data->MessageId);
                })
                .Next([this, Done](FNakamaRtResult<FNakamaRtChannelMessageAck> Resp)
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
            Connection->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaRtResult<FNakamaRtChannel>>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return NakamaRt::ChannelJoin(Connection, GenerateRoomName(), 1, false, false);
                })
                .Next([this, Done](auto JoinResp) -> TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>>
                {
                    if (!JoinResp.bIsSuccess)
                    {
                        AddError(TEXT("ChannelJoin failed"));
                        Done.Execute();
                        FNakamaRtError Err = JoinResp.Error.IsSet() ? *JoinResp.Error : FNakamaRtError{};
                        return MakeCompletedFuture(FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Err));
                    }
                    return NakamaRt::ChannelLeave(Connection, JoinResp.Data->Id);
                })
                .Next([this, Done](FNakamaRtResult<FNakamaRtEmptyResponse> Resp)
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

BEGIN_DEFINE_SPEC(FNakamaRtMatchSpec, "IntegrationTests.NakamaRtTests.Match",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

    FNakamaClientConfig ClientConfig;
    FNakamaSession      Session;
    TSharedPtr<FNakamaRtConnection> Connection;

    FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaRtMatchSpec)

void FNakamaRtMatchSpec::Define()
{
    BeforeEach([this]()
    {
        ClientConfig = FNakamaClientConfig{ RtServerKey, RtHost, RtPort, false };
        EnsureWebSocketsLoaded();
        Connection = MakeShared<FNakamaRtConnection>();
    });

    LatentBeforeEach([this](const FDoneDelegate& Done)
    {
        Nakama::AuthenticateCustom(ClientConfig, true, TEXT(""), GenerateId())
            .Next([this, Done](FNakamaSessionResult R)
            {
                if (R.bIsError) { AddError(FString::Printf(TEXT("Auth: %s"), *R.Error.Message)); Done.Execute(); return; }
                Session = R.Value;
                Done.Execute();
            });
    });

    LatentAfterEach([this](const FDoneDelegate& Done)
    {
        if (Connection) { Connection->Close(); Connection.Reset(); }

        if (Session.Token.IsEmpty()) { Done.Execute(); return; }
        Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
    });

    // -----------------------------------------------------------------------

    Describe("Create", [this]()
    {
        LatentIt("should create a relayed match and receive a match_id", [this](const FDoneDelegate& Done)
        {
            Connection->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaRtResult<FNakamaRtMatch>>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return NakamaRt::MatchCreate(Connection, TEXT(""));
                })
                .Next([this, Done](FNakamaRtResult<FNakamaRtMatch> Resp)
                {
                    RT_FAIL_ON_ERROR(Resp, Done);
                    TestFalse("match_id should not be empty", Resp.Data->MatchId.IsEmpty());
                    Done.Execute();
                });
        });
    });

    Describe("Leave", [this]()
    {
        LatentIt("should leave a match without error", [this](const FDoneDelegate& Done)
        {
            Connection->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaRtResult<FNakamaRtMatch>>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return NakamaRt::MatchCreate(Connection, TEXT(""));
                })
                .Next([this, Done](auto CreateResp) -> TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>>
                {
                    if (!CreateResp.bIsSuccess)
                    {
                        AddError(TEXT("MatchCreate failed"));
                        Done.Execute();
                        FNakamaRtError Err = CreateResp.Error.IsSet() ? *CreateResp.Error : FNakamaRtError{};
                        return MakeCompletedFuture(FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Err));
                    }
                    TestFalse("Match ID before leave", CreateResp.Data->MatchId.IsEmpty());
                    return NakamaRt::MatchLeave(Connection, CreateResp.Data->MatchId);
                })
                .Next([this, Done](FNakamaRtResult<FNakamaRtEmptyResponse> Resp)
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
            Connection->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaRtResult<FNakamaRtMatch>>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return NakamaRt::MatchCreate(Connection, TEXT(""));
                })
                .Next([this, Done](FNakamaRtResult<FNakamaRtMatch> CreateResp)
                {
                    RT_FAIL_ON_ERROR(CreateResp, Done);
                    // MatchDataSend is fire-and-forget — the server sends no response.
                    NakamaRt::MatchDataSend(Connection, CreateResp.Data->MatchId, 1, TArray<uint8>{0x48, 0x65, 0x6C, 0x6C, 0x6F}, {}, true);
                    Done.Execute();
                });
        });
    });
}

// ============================================================================
// MATCHMAKER TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaRtMatchmakerSpec, "IntegrationTests.NakamaRtTests.Matchmaker",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

    FNakamaClientConfig ClientConfig;
    FNakamaSession      Session;
    TSharedPtr<FNakamaRtConnection> Connection;

    FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaRtMatchmakerSpec)

void FNakamaRtMatchmakerSpec::Define()
{
    BeforeEach([this]()
    {
        ClientConfig = FNakamaClientConfig{ RtServerKey, RtHost, RtPort, false };
        EnsureWebSocketsLoaded();
        Connection = MakeShared<FNakamaRtConnection>();
    });

    LatentBeforeEach([this](const FDoneDelegate& Done)
    {
        Nakama::AuthenticateCustom(ClientConfig, true, TEXT(""), GenerateId())
            .Next([this, Done](FNakamaSessionResult R)
            {
                if (R.bIsError) { AddError(FString::Printf(TEXT("Auth: %s"), *R.Error.Message)); Done.Execute(); return; }
                Session = R.Value;
                Done.Execute();
            });
    });

    LatentAfterEach([this](const FDoneDelegate& Done)
    {
        if (Connection) { Connection->Close(); Connection.Reset(); }

        if (Session.Token.IsEmpty()) { Done.Execute(); return; }
        Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
    });

    // -----------------------------------------------------------------------

    Describe("Add", [this]()
    {
        LatentIt("should add to matchmaker and receive a ticket", [this](const FDoneDelegate& Done)
        {
            Connection->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaRtResult<FNakamaRtMatchmakerTicket>>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return NakamaRt::MatchmakerAdd(Connection, 2, 4, TEXT("*"), 2, {}, {});
                })
                .Next([this, Done](FNakamaRtResult<FNakamaRtMatchmakerTicket> Resp)
                {
                    RT_FAIL_ON_ERROR(Resp, Done);
                    TestFalse("Matchmaker ticket should not be empty", Resp.Data->Ticket.IsEmpty());
                    Done.Execute();
                });
        });
    });

    Describe("Remove", [this]()
    {
        LatentIt("should cancel matchmaking with the returned ticket", [this](const FDoneDelegate& Done)
        {
            Connection->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaRtResult<FNakamaRtMatchmakerTicket>>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return NakamaRt::MatchmakerAdd(Connection, 2, 4, TEXT("*"), 2, {}, {});
                })
                .Next([this, Done](auto AddResp) -> TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>>
                {
                    if (!AddResp.bIsSuccess)
                    {
                        AddError(TEXT("MatchmakerAdd failed"));
                        Done.Execute();
                        FNakamaRtError Err = AddResp.Error.IsSet() ? *AddResp.Error : FNakamaRtError{};
                        return MakeCompletedFuture(FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Err));
                    }
                    TestFalse("Ticket before remove", AddResp.Data->Ticket.IsEmpty());
                    return NakamaRt::MatchmakerRemove(Connection, AddResp.Data->Ticket);
                })
                .Next([this, Done](FNakamaRtResult<FNakamaRtEmptyResponse> Resp)
                {
                    RT_FAIL_ON_ERROR(Resp, Done);
                    Done.Execute();
                });
        });
    });
}

// ============================================================================
// MATCH JOIN TESTS  (two-client: match_id path and matchmaker-token path)
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaRtMatchJoinSpec, "IntegrationTests.NakamaRtTests.MatchJoin",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

    FNakamaClientConfig ClientConfig;

    // Client A — set up by BeforeEach
    FNakamaSession      Session;
    TSharedPtr<FNakamaRtConnection> Connection;

    // Client B — set up inline per test
    FNakamaSession      Session2;
    TSharedPtr<FNakamaRtConnection> Connection2;

    // Shared state threaded through the JoinByMatchId chain via a member
    FString PendingMatchId;

    // Counter used by the JoinByToken test — Done fires when both clients joined
    int32 MatchJoinedCount = 0;

    FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaRtMatchJoinSpec)

void FNakamaRtMatchJoinSpec::Define()
{
    BeforeEach([this]()
    {
        ClientConfig     = FNakamaClientConfig{ RtServerKey, RtHost, RtPort, false };
        EnsureWebSocketsLoaded();
        Connection       = MakeShared<FNakamaRtConnection>();
        PendingMatchId   = TEXT("");
        MatchJoinedCount = 0;
    });

    LatentBeforeEach([this](const FDoneDelegate& Done)
    {
        Nakama::AuthenticateCustom(ClientConfig, true, TEXT(""), GenerateId())
            .Next([this, Done](FNakamaSessionResult R)
            {
                if (R.bIsError) { AddError(FString::Printf(TEXT("Auth A: %s"), *R.Error.Message)); Done.Execute(); return; }
                Session = R.Value;
                Done.Execute();
            });
    });

    LatentAfterEach([this](const FDoneDelegate& Done)
    {
        if (Connection)  { Connection->Close();  Connection.Reset();  }
        if (Connection2) { Connection2->Close(); Connection2.Reset(); }

        if (Session.Token.IsEmpty()) { Done.Execute(); return; }
        Nakama::DeleteAccount(ClientConfig, Session)
            .Next([this, Done](FNakamaVoidResult)
            {
                Session = {};
                if (Session2.Token.IsEmpty()) { Done.Execute(); return; }
                Nakama::DeleteAccount(ClientConfig, Session2)
                    .Next([this, Done](FNakamaVoidResult) { Session2 = {}; Done.Execute(); });
            });
    });

    // -----------------------------------------------------------------------

    Describe("JoinByMatchId", [this]()
    {
        LatentIt("should join a relayed match created by another client using match_id", [this](const FDoneDelegate& Done)
        {
            // Chain: Connect A → Create Match → Auth B → Connect B → MatchJoin(match_id)
            // PendingMatchId threads the match_id through the chain via spec member state.
            Connection->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaRtResult<FNakamaRtMatch>>
                {
                    TestFalse("Connect A", CR.ErrorCode != ENakamaWebSocketError::None);
                    return NakamaRt::MatchCreate(Connection, TEXT(""));
                })
                .Next([this, Done](auto CreateResult) -> TNakamaFuture<FNakamaSessionResult>
                {
                    if (!CreateResult.bIsSuccess)
                    {
                        AddError(TEXT("MatchCreate failed"));
                        return MakeCompletedFuture<FNakamaSessionResult>(FNakamaSessionResult{});
                    }
                    PendingMatchId = CreateResult.Data->MatchId;
                    TestFalse("match_id from MatchCreate", PendingMatchId.IsEmpty());

                    FNakamaAccountCustom Account2;
                    Account2.Id = GenerateId();
                    return Nakama::AuthenticateCustom(ClientConfig, true, TEXT(""), Account2.Id);
                })
                .Next([this, Done](FNakamaSessionResult R2) -> TNakamaFuture<FNakamaWebSocketConnectionResult>
                {
                    if (R2.bIsError)
                    {
                        AddError(FString::Printf(TEXT("Auth B: %s"), *R2.Error.Message));
                        Done.Execute();
                        return MakeCompletedFuture<FNakamaWebSocketConnectionResult>(FNakamaWebSocketConnectionResult{});
                    }
                    Session2 = R2.Value;
                    Connection2 = MakeShared<FNakamaRtConnection>();
                    return Connection2->Connect(MakeConnParams(Session2));
                })
                .Next([this](FNakamaWebSocketConnectionResult CR2) -> TNakamaFuture<FNakamaRtResult<FNakamaRtMatch>>
                {
                    TestFalse("Connect B", CR2.ErrorCode != ENakamaWebSocketError::None);
                    return NakamaRt::MatchJoin(Connection2, PendingMatchId, TEXT(""), {});
                })
                .Next([this, Done](FNakamaRtResult<FNakamaRtMatch> JoinResult)
                {
                    RT_FAIL_ON_ERROR(JoinResult, Done);
                    TestFalse("Client B joined with non-empty match_id", JoinResult.Data->MatchId.IsEmpty());
                    Done.Execute();
                });
        });
    });

    Describe("JoinByToken", [this]()
    {
        LatentIt("should join a match via matchmaker token when two clients are matched", [this](const FDoneDelegate& Done)
        {
            // Chain: Auth B → Connect B → Connect A → set OnMatchmakerMatched → MatchmakerAdd A → MatchmakerAdd B
            // The server fires "matchmaker_matched" (no CID, push) to both clients.
            // OnMatchmakerMatched handlers extract the token and call MatchJoin;
            // Done fires when both clients have joined (MatchJoinedCount reaches 2).
            FNakamaAccountCustom Account2;
            Account2.Id = GenerateId();
            Nakama::AuthenticateCustom(ClientConfig, true, TEXT(""), Account2.Id)
                .Next([this, Done](FNakamaSessionResult R2) -> TNakamaFuture<FNakamaWebSocketConnectionResult>
                {
                    if (R2.bIsError) { AddError(FString::Printf(TEXT("Auth B: %s"), *R2.Error.Message)); Done.Execute(); return MakeCompletedFuture<FNakamaWebSocketConnectionResult>(FNakamaWebSocketConnectionResult{}); }
                    Session2 = R2.Value;
                    Connection2 = MakeShared<FNakamaRtConnection>();
                    return Connection2->Connect(MakeConnParams(Session2));
                })
                .Next([this, Done](FNakamaWebSocketConnectionResult CR2) -> TNakamaFuture<FNakamaWebSocketConnectionResult>
                {
                    TestFalse("Connect B", CR2.ErrorCode != ENakamaWebSocketError::None);
                    return Connection->Connect(MakeConnParams(Session));
                })
                .Next([this, Done](FNakamaWebSocketConnectionResult CR1) -> TNakamaFuture<FNakamaRtResult<FNakamaRtMatchmakerTicket>>
                {
                    TestFalse("Connect A", CR1.ErrorCode != ENakamaWebSocketError::None);

                    // Set up typed event callbacks before adding to the matchmaker queue.
                    Connection->MatchmakerMatched.AddLambda([this, Done](const FNakamaRtMatchmakerMatched& Matched)
                    {
                        NakamaRt::MatchJoin(Connection, TEXT(""), Matched.Token, {})
                            .Next([this, Done](FNakamaRtResult<FNakamaRtMatch> JoinResult)
                            {
                                if (!JoinResult.bIsSuccess)
                                {
                                    AddError(TEXT("Client A MatchJoin failed"));
                                    Done.Execute();
                                    return;
                                }
                                if (++MatchJoinedCount == 2) { Done.Execute(); }
                            });
                    });

                    Connection2->MatchmakerMatched.AddLambda([this, Done](const FNakamaRtMatchmakerMatched& Matched)
                    {
                        NakamaRt::MatchJoin(Connection2, TEXT(""), Matched.Token, {})
                            .Next([this, Done](FNakamaRtResult<FNakamaRtMatch> JoinResult)
                            {
                                if (!JoinResult.bIsSuccess)
                                {
                                    AddError(TEXT("Client B MatchJoin failed"));
                                    Done.Execute();
                                    return;
                                }
                                if (++MatchJoinedCount == 2) { Done.Execute(); }
                            });
                    });

                    return NakamaRt::MatchmakerAdd(Connection, 2, 2, TEXT("*"), {}, {}, {});
                })
                .Next([this, Done](auto AddAResp) -> TNakamaFuture<FNakamaRtResult<FNakamaRtMatchmakerTicket>>
                {
                    if (!AddAResp.bIsSuccess)
                    {
                        AddError(FString::Printf(TEXT("MatchmakerAdd A failed")));
                        Done.Execute();
                        FNakamaRtError Err = AddAResp.Error.IsSet() ? *AddAResp.Error : FNakamaRtError{};
                        return MakeCompletedFuture(FNakamaRtResult<FNakamaRtMatchmakerTicket>::Failure(Err));
                    }
                    return NakamaRt::MatchmakerAdd(Connection2, 2, 2, TEXT("*"), {}, {}, {});
                })
                .Next([this, Done](FNakamaRtResult<FNakamaRtMatchmakerTicket> AddBResp)
                {
                    if (!AddBResp.bIsSuccess)
                    {
                        AddError(FString::Printf(TEXT("MatchmakerAdd B failed")));
                        Done.Execute();
                    }
                    // Both clients are now queued. The server will push matchmaker_matched to each.
                    // The OnMatchmakerMatched callbacks extract the token, call MatchJoin, and
                    // call Done once MatchJoinedCount reaches 2.
                });
        });
    });
}

// ============================================================================
// SERVER-PUSH EVENT TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaRtEventSpec, "IntegrationTests.NakamaRtTests.Events",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

    FNakamaClientConfig ClientConfig;

    FNakamaSession Session;
    TSharedPtr<FNakamaRtConnection> Connection;

    FNakamaSession Session2;
    TSharedPtr<FNakamaRtConnection> Connection2;

    // Threaded through chains when two-step setup needs to pass an ID between lambdas.
    FString PendingId;

    FString GenerateId()       { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }
    FString GenerateRoomName() { return TEXT("rt-evt-") + FGuid::NewGuid().ToString(EGuidFormats::Short).Left(8); }

END_DEFINE_SPEC(FNakamaRtEventSpec)

void FNakamaRtEventSpec::Define()
{
    BeforeEach([this]()
    {
        ClientConfig = FNakamaClientConfig{ RtServerKey, RtHost, RtPort, false };
        EnsureWebSocketsLoaded();
        Connection = MakeShared<FNakamaRtConnection>();
        PendingId = TEXT("");
    });

    LatentBeforeEach([this](const FDoneDelegate& Done)
    {
        Nakama::AuthenticateCustom(ClientConfig, true, TEXT(""), GenerateId())
            .Next([this, Done](FNakamaSessionResult R)
            {
                if (R.bIsError) { AddError(FString::Printf(TEXT("Auth A: %s"), *R.Error.Message)); Done.Execute(); return; }
                Session = R.Value;
                Done.Execute();
            });
    });

    LatentAfterEach([this](const FDoneDelegate& Done)
    {
        if (Connection)  { Connection->Close();  Connection.Reset();  }
        if (Connection2) { Connection2->Close(); Connection2.Reset(); }

        if (Session.Token.IsEmpty()) { Done.Execute(); return; }
        Nakama::DeleteAccount(ClientConfig, Session)
            .Next([this, Done](FNakamaVoidResult)
            {
                Session = {};
                if (Session2.Token.IsEmpty()) { Done.Execute(); return; }
                Nakama::DeleteAccount(ClientConfig, Session2)
                    .Next([this, Done](FNakamaVoidResult) { Session2 = {}; Done.Execute(); });
            });
    });

    // -----------------------------------------------------------------------

    Describe("OnMatchPresenceEvent", [this]()
    {
        LatentIt("should fire when a second client joins the match", [this](const FDoneDelegate& Done)
        {
            // Client A creates a match and registers OnMatchPresenceEvent.
            // Client B authenticates, connects, and joins the same match.
            // Done fires when Client A's callback delivers a non-empty joins list.
            Connection->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaRtResult<FNakamaRtMatch>>
                {
                    TestFalse("Connect A", CR.ErrorCode != ENakamaWebSocketError::None);
                    return NakamaRt::MatchCreate(Connection, TEXT(""));
                })
                .Next([this, Done](auto CreateResult) -> TNakamaFuture<FNakamaSessionResult>
                {
                    if (!CreateResult.bIsSuccess)
                    {
                        AddError(TEXT("MatchCreate failed"));
                        return MakeCompletedFuture<FNakamaSessionResult>(FNakamaSessionResult{});
                    }
                    PendingId = CreateResult.Data->MatchId;

                    Connection->MatchPresenceEvent.AddLambda([this, Done](const FNakamaRtMatchPresenceEvent& Event)
                    {
                        TestEqual("Presence event match_id", Event.MatchId, PendingId);
                        TestFalse("Joins list should be non-empty", Event.Joins.IsEmpty());
                        Done.Execute();
                    });

                    return Nakama::AuthenticateCustom(ClientConfig, true, TEXT(""), GenerateId());
                })
                .Next([this, Done](FNakamaSessionResult R2) -> TNakamaFuture<FNakamaWebSocketConnectionResult>
                {
                    if (R2.bIsError) { AddError(FString::Printf(TEXT("Auth B: %s"), *R2.Error.Message)); Done.Execute(); return MakeCompletedFuture<FNakamaWebSocketConnectionResult>(FNakamaWebSocketConnectionResult{}); }
                    Session2 = R2.Value;
                    Connection2 = MakeShared<FNakamaRtConnection>();
                    return Connection2->Connect(MakeConnParams(Session2));
                })
                .Next([this, Done](FNakamaWebSocketConnectionResult CR2) -> TNakamaFuture<FNakamaRtResult<FNakamaRtMatch>>
                {
                    TestFalse("Connect B", CR2.ErrorCode != ENakamaWebSocketError::None);
                    return NakamaRt::MatchJoin(Connection2, PendingId, TEXT(""), {});
                })
                .Next([this, Done](FNakamaRtResult<FNakamaRtMatch> JoinResult)
                {
                    if (!JoinResult.bIsSuccess)
                    {
                        AddError(TEXT("Client B MatchJoin failed"));
                        Done.Execute();
                    }
                    // Done fires via MatchPresenceEvent on Client A, not here.
                });
        });
    });

    Describe("OnMatchData", [this]()
    {
        LatentIt("should fire when another client sends match data", [this](const FDoneDelegate& Done)
        {
            // Client A creates a match and registers OnMatchData.
            // Client B joins the match and sends a data packet.
            // Done fires when Client A's callback delivers the expected opcode.
            static constexpr int64 TestOpCode = 42;

            Connection->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaRtResult<FNakamaRtMatch>>
                {
                    TestFalse("Connect A", CR.ErrorCode != ENakamaWebSocketError::None);
                    return NakamaRt::MatchCreate(Connection, TEXT(""));
                })
                .Next([this, Done](auto CreateResult) -> TNakamaFuture<FNakamaSessionResult>
                {
                    if (!CreateResult.bIsSuccess)
                    {
                        AddError(TEXT("MatchCreate failed"));
                        return MakeCompletedFuture<FNakamaSessionResult>(FNakamaSessionResult{});
                    }
                    PendingId = CreateResult.Data->MatchId;

                    Connection->MatchData.AddLambda([this, Done](const FNakamaRtMatchData& MatchData)
                    {
                        TestEqual("MatchData match_id", MatchData.MatchId, PendingId);
                        TestEqual("MatchData opcode", MatchData.OpCode, TestOpCode);
                        Done.Execute();
                    });

                    return Nakama::AuthenticateCustom(ClientConfig, true, TEXT(""), GenerateId());
                })
                .Next([this, Done](FNakamaSessionResult R2) -> TNakamaFuture<FNakamaWebSocketConnectionResult>
                {
                    if (R2.bIsError) { AddError(FString::Printf(TEXT("Auth B: %s"), *R2.Error.Message)); Done.Execute(); return MakeCompletedFuture<FNakamaWebSocketConnectionResult>(FNakamaWebSocketConnectionResult{}); }
                    Session2 = R2.Value;
                    Connection2 = MakeShared<FNakamaRtConnection>();
                    return Connection2->Connect(MakeConnParams(Session2));
                })
                .Next([this, Done](FNakamaWebSocketConnectionResult CR2) -> TNakamaFuture<FNakamaRtResult<FNakamaRtMatch>>
                {
                    TestFalse("Connect B", CR2.ErrorCode != ENakamaWebSocketError::None);
                    return NakamaRt::MatchJoin(Connection2, PendingId, TEXT(""), {});
                })
                .Next([this, Done](FNakamaRtResult<FNakamaRtMatch> JoinResult)
                {
                    if (!JoinResult.bIsSuccess)
                    {
                        AddError(TEXT("Client B MatchJoin failed"));
                        Done.Execute();
                        return;
                    }
                    // Client B sends data; Client A will receive it via MatchData.
                    NakamaRt::MatchDataSend(Connection2, PendingId, TestOpCode, TArray<uint8>{'h','e','l','l','o'}, {}, true);
                });
        });

        LatentIt("should receive the correct bytes when another client sends match data", [this](const FDoneDelegate& Done)
        {
            // Client A creates a match and registers OnMatchData expecting specific bytes.
            // Client B joins the match and sends a known payload as TArray<uint8>.
            // Done fires when Client A's callback confirms the data bytes match.
            static constexpr int64 TestOpCode = 43;
            static const TArray<uint8> TestPayload = {0x01, 0x02, 0x03};

            Connection->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaRtResult<FNakamaRtMatch>>
                {
                    TestFalse("Connect A", CR.ErrorCode != ENakamaWebSocketError::None);
                    return NakamaRt::MatchCreate(Connection, TEXT(""));
                })
                .Next([this, Done](auto CreateResult) -> TNakamaFuture<FNakamaSessionResult>
                {
                    if (!CreateResult.bIsSuccess)
                    {
                        AddError(TEXT("MatchCreate failed"));
                        return MakeCompletedFuture<FNakamaSessionResult>(FNakamaSessionResult{});
                    }
                    PendingId = CreateResult.Data->MatchId;

                    Connection->MatchData.AddLambda([this, Done](const FNakamaRtMatchData& MatchData)
                    {
                        TestEqual("MatchData match_id", MatchData.MatchId, PendingId);
                        TestEqual("MatchData opcode", MatchData.OpCode, TestOpCode);
                        TestEqual("MatchData bytes", MatchData.Data, TestPayload);
                        Done.Execute();
                    });

                    return Nakama::AuthenticateCustom(ClientConfig, true, TEXT(""), GenerateId());
                })
                .Next([this, Done](FNakamaSessionResult R2) -> TNakamaFuture<FNakamaWebSocketConnectionResult>
                {
                    if (R2.bIsError) { AddError(FString::Printf(TEXT("Auth B: %s"), *R2.Error.Message)); Done.Execute(); return MakeCompletedFuture<FNakamaWebSocketConnectionResult>(FNakamaWebSocketConnectionResult{}); }
                    Session2 = R2.Value;
                    Connection2 = MakeShared<FNakamaRtConnection>();
                    return Connection2->Connect(MakeConnParams(Session2));
                })
                .Next([this, Done](FNakamaWebSocketConnectionResult CR2) -> TNakamaFuture<FNakamaRtResult<FNakamaRtMatch>>
                {
                    TestFalse("Connect B", CR2.ErrorCode != ENakamaWebSocketError::None);
                    return NakamaRt::MatchJoin(Connection2, PendingId, TEXT(""), {});
                })
                .Next([this, Done](FNakamaRtResult<FNakamaRtMatch> JoinResult)
                {
                    if (!JoinResult.bIsSuccess)
                    {
                        AddError(TEXT("Client B MatchJoin failed"));
                        Done.Execute();
                        return;
                    }
                    NakamaRt::MatchDataSend(Connection2, PendingId, TestOpCode, TestPayload, {}, true);
                });
        });
    });

    Describe("OnChannelPresenceEvent", [this]()
    {
        LatentIt("should fire when a second client joins the same channel", [this](const FDoneDelegate& Done)
        {
            // Client A joins a room channel and registers OnChannelPresenceEvent.
            // Client B joins the same room.
            // Done fires when Client A's callback delivers a non-empty joins list.
            FString RoomName = GenerateRoomName();

            Connection->Connect(MakeConnParams(Session))
                .Next([this, RoomName](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaRtResult<FNakamaRtChannel>>
                {
                    TestFalse("Connect A", CR.ErrorCode != ENakamaWebSocketError::None);
                    return NakamaRt::ChannelJoin(Connection, RoomName, 1, false, false);
                })
                .Next([this, Done](auto JoinResult) -> TNakamaFuture<FNakamaSessionResult>
                {
                    if (!JoinResult.bIsSuccess)
                    {
                        AddError(TEXT("ChannelJoin A failed"));
                        return MakeCompletedFuture<FNakamaSessionResult>(FNakamaSessionResult{});
                    }
                    PendingId = JoinResult.Data->Id;

                    Connection->ChannelPresenceEvent.AddLambda([this, Done](const FNakamaRtChannelPresenceEvent& Event)
                    {
                        TestEqual("Presence event channel_id", Event.ChannelId, PendingId);
                        TestFalse("Joins list should be non-empty", Event.Joins.IsEmpty());
                        Done.Execute();
                    });

                    return Nakama::AuthenticateCustom(ClientConfig, true, TEXT(""), GenerateId());
                })
                .Next([this, Done](FNakamaSessionResult R2) -> TNakamaFuture<FNakamaWebSocketConnectionResult>
                {
                    if (R2.bIsError) { AddError(FString::Printf(TEXT("Auth B: %s"), *R2.Error.Message)); Done.Execute(); return MakeCompletedFuture<FNakamaWebSocketConnectionResult>(FNakamaWebSocketConnectionResult{}); }
                    Session2 = R2.Value;
                    Connection2 = MakeShared<FNakamaRtConnection>();
                    return Connection2->Connect(MakeConnParams(Session2));
                })
                .Next([this, Done, RoomName](FNakamaWebSocketConnectionResult CR2) -> TNakamaFuture<FNakamaRtResult<FNakamaRtChannel>>
                {
                    TestFalse("Connect B", CR2.ErrorCode != ENakamaWebSocketError::None);
                    return NakamaRt::ChannelJoin(Connection2, RoomName, 1, false, false);
                })
                .Next([this, Done](FNakamaRtResult<FNakamaRtChannel> JoinResult)
                {
                    if (!JoinResult.bIsSuccess)
                    {
                        AddError(TEXT("Client B ChannelJoin failed"));
                        Done.Execute();
                    }
                    // Done fires via OnChannelPresenceEvent on Client A, not here.
                });
        });
    });
}

// ============================================================================
// STATUS TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaRtStatusSpec, "IntegrationTests.NakamaRtTests.Status",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

    FNakamaClientConfig ClientConfig;
    FNakamaSession      Session;
    TSharedPtr<FNakamaRtConnection> Connection;

    FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaRtStatusSpec)

void FNakamaRtStatusSpec::Define()
{
    BeforeEach([this]()
    {
        ClientConfig = FNakamaClientConfig{ RtServerKey, RtHost, RtPort, false };
        EnsureWebSocketsLoaded();
        Connection = MakeShared<FNakamaRtConnection>();
    });

    LatentBeforeEach([this](const FDoneDelegate& Done)
    {
        Nakama::AuthenticateCustom(ClientConfig, true, TEXT(""), GenerateId())
            .Next([this, Done](FNakamaSessionResult R)
            {
                if (R.bIsError) { AddError(FString::Printf(TEXT("Auth: %s"), *R.Error.Message)); Done.Execute(); return; }
                Session = R.Value;
                Done.Execute();
            });
    });

    LatentAfterEach([this](const FDoneDelegate& Done)
    {
        if (Connection) { Connection->Close(); Connection.Reset(); }

        if (Session.Token.IsEmpty()) { Done.Execute(); return; }
        Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
    });

    // -----------------------------------------------------------------------

    Describe("Update", [this]()
    {
        LatentIt("should set a status string without error", [this](const FDoneDelegate& Done)
        {
            Connection->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return NakamaRt::StatusUpdate(Connection, TEXT("Playing a game"));
                })
                .Next([this, Done](FNakamaRtResult<FNakamaRtEmptyResponse> Resp)
                {
                    RT_FAIL_ON_ERROR(Resp, Done);
                    Done.Execute();
                });
        });

        LatentIt("should clear status by passing an empty string", [this](const FDoneDelegate& Done)
        {
            Connection->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return NakamaRt::StatusUpdate(Connection, TEXT(""));
                })
                .Next([this, Done](FNakamaRtResult<FNakamaRtEmptyResponse> Resp)
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
            Connection->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaRtResult<FNakamaRtStatus>>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return NakamaRt::StatusFollow(Connection, { GenerateId() }, {});
                })
                .Next([this, Done](FNakamaRtResult<FNakamaRtStatus> Resp)
                {
                    RT_FAIL_ON_ERROR(Resp, Done);
                    Done.Execute();
                });
        });

        LatentIt("should follow and then unfollow a user ID", [this](const FDoneDelegate& Done)
        {
            FString FakeUserId = GenerateId();
            Connection->Connect(MakeConnParams(Session))
                .Next([this, FakeUserId](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaRtResult<FNakamaRtStatus>>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return NakamaRt::StatusFollow(Connection, { FakeUserId }, {});
                })
                .Next([this, FakeUserId, Done](auto FollowResp) -> TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>>
                {
                    if (!FollowResp.bIsSuccess)
                    {
                        AddError(TEXT("StatusFollow failed"));
                        Done.Execute();
                        FNakamaRtError Err = FollowResp.Error.IsSet() ? *FollowResp.Error : FNakamaRtError{};
                        return MakeCompletedFuture(FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Err));
                    }
                    return NakamaRt::StatusUnfollow(Connection, { FakeUserId });
                })
                .Next([this, Done](FNakamaRtResult<FNakamaRtEmptyResponse> Resp)
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

BEGIN_DEFINE_SPEC(FNakamaRtPartySpec, "IntegrationTests.NakamaRtTests.Party",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

    FNakamaClientConfig ClientConfig;
    FNakamaSession      Session;
    TSharedPtr<FNakamaRtConnection> Connection;

    FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaRtPartySpec)

void FNakamaRtPartySpec::Define()
{
    BeforeEach([this]()
    {
        ClientConfig = FNakamaClientConfig{ RtServerKey, RtHost, RtPort, false };
        EnsureWebSocketsLoaded();
        Connection = MakeShared<FNakamaRtConnection>();
    });

    LatentBeforeEach([this](const FDoneDelegate& Done)
    {
        Nakama::AuthenticateCustom(ClientConfig, true, TEXT(""), GenerateId())
            .Next([this, Done](FNakamaSessionResult R)
            {
                if (R.bIsError) { AddError(FString::Printf(TEXT("Auth: %s"), *R.Error.Message)); Done.Execute(); return; }
                Session = R.Value;
                Done.Execute();
            });
    });

    LatentAfterEach([this](const FDoneDelegate& Done)
    {
        if (Connection) { Connection->Close(); Connection.Reset(); }

        if (Session.Token.IsEmpty()) { Done.Execute(); return; }
        Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
    });

    // -----------------------------------------------------------------------

    Describe("Create", [this]()
    {
        LatentIt("should create a party and receive a party_id", [this](const FDoneDelegate& Done)
        {
            Connection->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaRtResult<FNakamaRtParty>>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return NakamaRt::PartyCreate(Connection, true, 4, TEXT(""), false);
                })
                .Next([this, Done](FNakamaRtResult<FNakamaRtParty> Resp)
                {
                    RT_FAIL_ON_ERROR(Resp, Done);
                    TestFalse("party_id should not be empty", Resp.Data->PartyId.IsEmpty());
                    Done.Execute();
                });
        });
    });

    Describe("Close", [this]()
    {
        LatentIt("should close a party without error", [this](const FDoneDelegate& Done)
        {
            Connection->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaRtResult<FNakamaRtParty>>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return NakamaRt::PartyCreate(Connection, true, 4, TEXT(""), false);
                })
                .Next([this, Done](auto CreateResp) -> TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>>
                {
                    if (!CreateResp.bIsSuccess)
                    {
                        AddError(TEXT("PartyCreate failed"));
                        Done.Execute();
                        FNakamaRtError Err = CreateResp.Error.IsSet() ? *CreateResp.Error : FNakamaRtError{};
                        return MakeCompletedFuture(FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Err));
                    }
                    TestFalse("Party ID before close", CreateResp.Data->PartyId.IsEmpty());
                    return NakamaRt::PartyClose(Connection, CreateResp.Data->PartyId);
                })
                .Next([this, Done](FNakamaRtResult<FNakamaRtEmptyResponse> Resp)
                {
                    RT_FAIL_ON_ERROR(Resp, Done);
                    Done.Execute();
                });
        });
    });
}

// ============================================================================
// SUBSYSTEM LIFETIME TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaRtSubsystemLifetimeSpec, "IntegrationTests.NakamaRtTests.SubsystemLifetime",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

END_DEFINE_SPEC(FNakamaRtSubsystemLifetimeSpec)

void FNakamaRtSubsystemLifetimeSpec::Define()
{
    Describe("StaledSubsystem", [this]()
    {
        LatentIt("should return an error future instead of crashing when subsystem is destroyed", [this](const FDoneDelegate& Done)
        {
            // 1. Create a local connection and immediately reset it to null,
            //    simulating a destroyed/stale connection pointer.
            TSharedPtr<FNakamaRtConnection> NullConnection = MakeShared<FNakamaRtConnection>();
            NullConnection.Reset();

            // 2. Call a method while the connection is null/stale.
            //    Without the validity guard the generated template emits
            //      Connection->Send(...)
            //    on a null pointer — guaranteed crash.
            //    After the fix it must immediately resolve to an error.
            NakamaRt::StatusUpdate(NullConnection, TEXT(""))
                .Next([this, Done](FNakamaRtResult<FNakamaRtEmptyResponse> Resp)
                {
                    TestFalse(
                        TEXT("Stale-subsystem call must return an error, not success"),
                        Resp.bIsSuccess);
                    Done.Execute();
                });
        });
    });
}

// ============================================================================
// PARTY (two-client)
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaRtPartyExtSpec, "IntegrationTests.NakamaRtTests.PartyExt",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

    FNakamaClientConfig ClientConfig;
    FNakamaSession      Session;
    FNakamaSession      Session2;
    TSharedPtr<FNakamaRtConnection> Connection;
    TSharedPtr<FNakamaRtConnection> Connection2;
    FString PendingPartyId;

    FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaRtPartyExtSpec)

void FNakamaRtPartyExtSpec::Define()
{
    BeforeEach([this]()
    {
        ClientConfig = FNakamaClientConfig{ RtServerKey, RtHost, RtPort, false };
        EnsureWebSocketsLoaded();
        Connection = MakeShared<FNakamaRtConnection>();
    });

    LatentBeforeEach([this](const FDoneDelegate& Done)
    {
        Nakama::AuthenticateCustom(ClientConfig, true, TEXT(""), GenerateId())
            .Next([this, Done](FNakamaSessionResult R)
            {
                if (R.bIsError) { AddError(FString::Printf(TEXT("Auth: %s"), *R.Error.Message)); Done.Execute(); return; }
                Session = R.Value;
                Done.Execute();
            });
    });

    LatentAfterEach([this](const FDoneDelegate& Done)
    {
        if (Connection)  { Connection->Close();  Connection.Reset(); }
        if (Connection2) { Connection2->Close(); Connection2.Reset(); }

        auto DeleteMain = [this, Done]()
        {
            if (Session.Token.IsEmpty()) { Done.Execute(); return; }
            Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
        };
        if (Session2.Token.IsEmpty()) { DeleteMain(); return; }
        Nakama::DeleteAccount(ClientConfig, Session2).Next([DeleteMain](FNakamaVoidResult) { DeleteMain(); });
    });

    Describe("PartyData", [this]()
    {
        LatentIt("should deliver party data sent by a second member", [this](const FDoneDelegate& Done)
        {
            static constexpr int64 TestOpCode = 7;
            static const TArray<uint8> TestPayload = {0xAA, 0xBB, 0xCC};

            Connection->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaRtResult<FNakamaRtParty>>
                {
                    TestFalse("Connect A", CR.ErrorCode != ENakamaWebSocketError::None);
                    return NakamaRt::PartyCreate(Connection, true /*open*/, 4, TEXT(""), false);
                })
                .Next([this, Done](FNakamaRtResult<FNakamaRtParty> CreateResult) -> TNakamaFuture<FNakamaSessionResult>
                {
                    if (!CreateResult.bIsSuccess) { AddError(TEXT("PartyCreate failed")); Done.Execute(); return MakeCompletedFuture<FNakamaSessionResult>(FNakamaSessionResult{}); }
                    PendingPartyId = CreateResult.Data->PartyId;

                    Connection->PartyData.AddLambda([this, Done](const FNakamaRtPartyData& PartyData)
                    {
                        TestEqual("PartyData party_id", PartyData.PartyId, PendingPartyId);
                        TestEqual("PartyData opcode", PartyData.OpCode, TestOpCode);
                        TestEqual("PartyData bytes", PartyData.Data, TestPayload);
                        Done.Execute();
                    });

                    return Nakama::AuthenticateCustom(ClientConfig, true, TEXT(""), GenerateId());
                })
                .Next([this, Done](FNakamaSessionResult R2) -> TNakamaFuture<FNakamaWebSocketConnectionResult>
                {
                    if (R2.bIsError) { AddError(FString::Printf(TEXT("Auth B: %s"), *R2.Error.Message)); Done.Execute(); return MakeCompletedFuture<FNakamaWebSocketConnectionResult>(FNakamaWebSocketConnectionResult{}); }
                    Session2 = R2.Value;
                    Connection2 = MakeShared<FNakamaRtConnection>();
                    return Connection2->Connect(MakeConnParams(Session2));
                })
                .Next([this, Done](FNakamaWebSocketConnectionResult CR2) -> TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>>
                {
                    TestFalse("Connect B", CR2.ErrorCode != ENakamaWebSocketError::None);
                    return NakamaRt::PartyJoin(Connection2, PendingPartyId);
                })
                .Next([this, Done](FNakamaRtResult<FNakamaRtEmptyResponse> JoinResult)
                {
                    if (!JoinResult.bIsSuccess) { AddError(TEXT("Client B PartyJoin failed")); Done.Execute(); return; }
                    // Client B sends party data; Client A receives it via the PartyData delegate.
                    NakamaRt::PartyDataSend(Connection2, PendingPartyId, TestOpCode, TestPayload);
                });
        });
    });

    Describe("JoinRequest", [this]()
    {
        LatentIt("should surface a join request when a client joins a closed party", [this](const FDoneDelegate& Done)
        {
            Connection->Connect(MakeConnParams(Session))
                .Next([this](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaRtResult<FNakamaRtParty>>
                {
                    TestFalse("Connect A", CR.ErrorCode != ENakamaWebSocketError::None);
                    return NakamaRt::PartyCreate(Connection, false /*closed*/, 4, TEXT(""), false);
                })
                .Next([this, Done](FNakamaRtResult<FNakamaRtParty> CreateResult) -> TNakamaFuture<FNakamaSessionResult>
                {
                    if (!CreateResult.bIsSuccess) { AddError(TEXT("PartyCreate failed")); Done.Execute(); return MakeCompletedFuture<FNakamaSessionResult>(FNakamaSessionResult{}); }
                    PendingPartyId = CreateResult.Data->PartyId;

                    Connection->PartyJoinRequest.AddLambda([this, Done](const FNakamaRtPartyJoinRequest& Request)
                    {
                        TestEqual("JoinRequest party_id", Request.PartyId, PendingPartyId);
                        TestTrue("JoinRequest carries the requesting presence", Request.Presences.Num() > 0);
                        Done.Execute();
                    });

                    return Nakama::AuthenticateCustom(ClientConfig, true, TEXT(""), GenerateId());
                })
                .Next([this, Done](FNakamaSessionResult R2) -> TNakamaFuture<FNakamaWebSocketConnectionResult>
                {
                    if (R2.bIsError) { AddError(FString::Printf(TEXT("Auth B: %s"), *R2.Error.Message)); Done.Execute(); return MakeCompletedFuture<FNakamaWebSocketConnectionResult>(FNakamaWebSocketConnectionResult{}); }
                    Session2 = R2.Value;
                    Connection2 = MakeShared<FNakamaRtConnection>();
                    return Connection2->Connect(MakeConnParams(Session2));
                })
                .Next([this, Done](FNakamaWebSocketConnectionResult CR2)
                {
                    TestFalse("Connect B", CR2.ErrorCode != ENakamaWebSocketError::None);
                    // Joining a closed party raises a join request Client A receives.
                    NakamaRt::PartyJoin(Connection2, PendingPartyId);
                });
        });
    });
}

// ============================================================================
// NOTIFICATIONS: socket delivery + list/delete round-trip
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaRtNotificationsExtSpec, "IntegrationTests.NakamaRtTests.NotificationsExt",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

    FNakamaClientConfig ClientConfig;
    FNakamaSession      Session;   // recipient (B)
    FNakamaSession      Sender;    // requester (A)
    TSharedPtr<FNakamaRtConnection> Connection;
    TArray<FString>     DeletedIds;

    FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaRtNotificationsExtSpec)

void FNakamaRtNotificationsExtSpec::Define()
{
    BeforeEach([this]()
    {
        ClientConfig = FNakamaClientConfig{ RtServerKey, RtHost, RtPort, false };
        EnsureWebSocketsLoaded();
        Connection = MakeShared<FNakamaRtConnection>();
    });

    LatentBeforeEach([this](const FDoneDelegate& Done)
    {
        Nakama::AuthenticateCustom(ClientConfig, true, TEXT(""), GenerateId())
            .Next([this](FNakamaSessionResult R) -> TNakamaFuture<FNakamaSessionResult>
            {
                Session = R.Value;
                return Nakama::AuthenticateCustom(ClientConfig, true, TEXT(""), GenerateId());
            })
            .Next([this, Done](FNakamaSessionResult R)
            {
                if (R.bIsError) { AddError(FString::Printf(TEXT("Auth: %s"), *R.Error.Message)); Done.Execute(); return; }
                Sender = R.Value;
                Done.Execute();
            });
    });

    LatentAfterEach([this](const FDoneDelegate& Done)
    {
        if (Connection) { Connection->Close(); Connection.Reset(); }

        auto DeleteRecipient = [this, Done]()
        {
            if (Session.Token.IsEmpty()) { Done.Execute(); return; }
            Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
        };
        if (Sender.Token.IsEmpty()) { DeleteRecipient(); return; }
        Nakama::DeleteAccount(ClientConfig, Sender).Next([DeleteRecipient](FNakamaVoidResult) { DeleteRecipient(); });
    });

    Describe("SocketDelivery", [this]()
    {
        LatentIt("should deliver a friend-request notification over the socket", [this](const FDoneDelegate& Done)
        {
            Connection->Connect(MakeConnParams(Session))
                .Next([this, Done](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaVoidResult>
                {
                    TestFalse("Connect recipient", CR.ErrorCode != ENakamaWebSocketError::None);

                    Connection->Notifications.AddLambda([this, Done](const FNakamaRtNotifications& Notifs)
                    {
                        TestTrue("Received at least one notification", Notifs.Notifications.Num() > 0);
                        Done.Execute();
                    });

                    // Sender (A) invites recipient (B); Nakama pushes a notification to B.
                    return Nakama::AddFriends(ClientConfig, Sender, {Session.UserId}, {}, TEXT(""));
                })
                .Next([this, Done](FNakamaVoidResult AddResult)
                {
                    if (AddResult.bIsError) { AddError(FString::Printf(TEXT("AddFriends failed: %s"), *AddResult.Error.Message)); Done.Execute(); }
                    // Otherwise wait for the Notifications delegate to fire.
                });
        });
    });

    Describe("ListAndDelete", [this]()
    {
        LatentIt("should list a received notification and then delete it", [this](const FDoneDelegate& Done)
        {
            DeletedIds.Empty();

            // A invites B, then B lists, deletes, and re-lists its notifications.
            Nakama::AddFriends(ClientConfig, Sender, {Session.UserId}, {}, TEXT(""))
                .Next([this](const FNakamaVoid&) -> TNakamaFuture<FNakamaNotificationListResult>
                {
                    return Nakama::ListNotifications(ClientConfig, Session, 100, TEXT(""));
                })
                .Next([this, Done](FNakamaNotificationListResult ListResult) -> TNakamaFuture<FNakamaVoidResult>
                {
                    if (ListResult.bIsError) { AddError(FString::Printf(TEXT("List failed: %s"), *ListResult.Error.Message)); Done.Execute(); return MakeCompletedFuture<FNakamaVoidResult>(FNakamaVoidResult{}); }

                    TestTrue("Recipient has at least one notification", ListResult.Value.Notifications.Num() > 0);
                    for (const FNakamaNotification& Notif : ListResult.Value.Notifications)
                    {
                        DeletedIds.Add(Notif.Id);
                    }
                    return Nakama::DeleteNotifications(ClientConfig, Session, DeletedIds);
                })
                .Next([this](FNakamaVoidResult DeleteResult) -> TNakamaFuture<FNakamaNotificationListResult>
                {
                    return Nakama::ListNotifications(ClientConfig, Session, 100, TEXT(""));
                })
                .Next([this, Done](FNakamaNotificationListResult AfterResult)
                {
                    if (AfterResult.bIsError) { AddError(FString::Printf(TEXT("Re-list failed: %s"), *AfterResult.Error.Message)); Done.Execute(); return; }

                    bool bAnyDeletedStillPresent = false;
                    for (const FNakamaNotification& Notif : AfterResult.Value.Notifications)
                    {
                        if (DeletedIds.Contains(Notif.Id)) { bAnyDeletedStillPresent = true; break; }
                    }
                    TestFalse("Deleted notifications no longer listed", bAnyDeletedStillPresent);
                    Done.Execute();
                });
        });
    });
}

// ============================================================================
// CHAT: group channel join
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaRtGroupChatSpec, "IntegrationTests.NakamaRtTests.GroupChat",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

    FNakamaClientConfig ClientConfig;
    FNakamaSession      Session;
    TSharedPtr<FNakamaRtConnection> Connection;
    FString PendingGroupId;

    FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }
    FString GenerateShortId() { return FGuid::NewGuid().ToString(EGuidFormats::Short).Left(8); }

END_DEFINE_SPEC(FNakamaRtGroupChatSpec)

void FNakamaRtGroupChatSpec::Define()
{
    // Nakama chat channel types: 1 = Room, 2 = DirectMessage, 3 = Group.
    static constexpr int32 ChannelTypeGroup = 3;

    BeforeEach([this]()
    {
        ClientConfig = FNakamaClientConfig{ RtServerKey, RtHost, RtPort, false };
        EnsureWebSocketsLoaded();
        Connection = MakeShared<FNakamaRtConnection>();
    });

    LatentBeforeEach([this](const FDoneDelegate& Done)
    {
        Nakama::AuthenticateCustom(ClientConfig, true, TEXT(""), GenerateId())
            .Next([this, Done](FNakamaSessionResult R)
            {
                if (R.bIsError) { AddError(FString::Printf(TEXT("Auth: %s"), *R.Error.Message)); Done.Execute(); return; }
                Session = R.Value;
                Done.Execute();
            });
    });

    LatentAfterEach([this](const FDoneDelegate& Done)
    {
        if (Connection) { Connection->Close(); Connection.Reset(); }
        if (Session.Token.IsEmpty()) { Done.Execute(); return; }
        Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
    });

    Describe("Join", [this]()
    {
        LatentIt("should join the chat channel of a group the user owns", [this](const FDoneDelegate& Done)
        {
            const FString GroupName = FString::Printf(TEXT("chat_group_%s"), *GenerateShortId());

            Nakama::CreateGroup(ClientConfig, Session, GroupName, TEXT("group chat test"), TEXT(""), TEXT("en"), true, 10)
                .Next([this, Done](FNakamaGroupResult GroupResult) -> TNakamaFuture<FNakamaWebSocketConnectionResult>
                {
                    if (GroupResult.bIsError) { AddError(FString::Printf(TEXT("CreateGroup failed: %s"), *GroupResult.Error.Message)); Done.Execute(); return MakeCompletedFuture<FNakamaWebSocketConnectionResult>(FNakamaWebSocketConnectionResult{}); }
                    PendingGroupId = GroupResult.Value.Id;
                    return Connection->Connect(MakeConnParams(Session));
                })
                .Next([this, Done](FNakamaWebSocketConnectionResult CR) -> TNakamaFuture<FNakamaRtResult<FNakamaRtChannel>>
                {
                    TestFalse("Connect", CR.ErrorCode != ENakamaWebSocketError::None);
                    return NakamaRt::ChannelJoin(Connection, PendingGroupId, ChannelTypeGroup, false, false);
                })
                .Next([this, Done](FNakamaRtResult<FNakamaRtChannel> Resp)
                {
                    RT_FAIL_ON_ERROR(Resp, Done);
                    TestFalse("Group channel has a non-empty ID", Resp.Data->Id.IsEmpty());
                    Done.Execute();
                });
        });
    });
}
