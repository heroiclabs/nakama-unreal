/**
 * Satori Async API Integration Test Suite
 *
 * Tests for all Satori REST API endpoints using the TFuture-based Satori:: free-function API.
 * Mirrors the Nakama async test pattern: each spec authenticates in BeforeEach, then tests
 * individual endpoints.
 */

#include "Satori.h"
#include "Misc/Guid.h"

/**
 * Helper macro: early-return on unexpected error inside a .Next() callback.
 */
#define SATORI_FAIL_ON_ERROR(Result, Done) \
	if (Result.bIsError) { \
		AddError(FString::Printf(TEXT("Unexpected error %d: %s"), Result.Error.Code, *Result.Error.Message)); \
		Done.Execute(); \
		return; \
	}

// ============================================================================
// AUTHENTICATION TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FSatoriAsyncAuthSpec, "IntegrationTests.Satori.Auth",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FSatoriClient Client;
	FString TestIdentityId;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7450;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FSatoriAsyncAuthSpec)

const FString FSatoriAsyncAuthSpec::ServerKey = TEXT("defaultkey");
const FString FSatoriAsyncAuthSpec::Host = TEXT("127.0.0.1");

void FSatoriAsyncAuthSpec::Define()
{
	BeforeEach([this]()
	{
		Client = FSatoriClient{FSatoriApiConfig{ServerKey, Host, Port, false, 10.0f}};
		TestIdentityId = GenerateId();
	});

	Describe("Authenticate", [this]()
	{
		LatentIt("should authenticate with valid identity ID", [this](const FDoneDelegate& Done)
		{
			Satori::Authenticate(Client, TestIdentityId, false, {}, {}).Next([this, Done](FSatoriSessionResult Result)
			{
				SATORI_FAIL_ON_ERROR(Result, Done);
				TestTrue("Session has token", !Result.Value.Token.IsEmpty());
				TestTrue("Session has refresh token", !Result.Value.RefreshToken.IsEmpty());
				Done.Execute();
			});
		});

		LatentIt("should authenticate with no_session flag", [this](const FDoneDelegate& Done)
		{
			Satori::Authenticate(Client, TestIdentityId, true, {}, {}).Next([this, Done](FSatoriSessionResult Result)
			{
				SATORI_FAIL_ON_ERROR(Result, Done);
				TestTrue("Token is empty with no_session", Result.Value.Token.IsEmpty());
				Done.Execute();
			});
		});

		LatentIt("should authenticate with default properties", [this](const FDoneDelegate& Done)
		{
			TMap<FString, FString> Defaults;
			Defaults.Add(TEXT("platform"), TEXT("windows"));
			Defaults.Add(TEXT("version"), TEXT("1.0"));

			Satori::Authenticate(Client, TestIdentityId, false, Defaults, {}).Next([this, Done](FSatoriSessionResult Result)
			{
				SATORI_FAIL_ON_ERROR(Result, Done);
				TestTrue("Session has token", !Result.Value.Token.IsEmpty());
				Done.Execute();
			});
		});

		LatentIt("should authenticate with custom properties", [this](const FDoneDelegate& Done)
		{
			TMap<FString, FString> Custom;
			Custom.Add(TEXT("preferred_mode"), TEXT("ranked"));

			Satori::Authenticate(Client, TestIdentityId, false, {}, Custom).Next([this, Done](FSatoriSessionResult Result)
			{
				SATORI_FAIL_ON_ERROR(Result, Done);
				TestTrue("Session has token", !Result.Value.Token.IsEmpty());
				Done.Execute();
			});
		});

		LatentIt("should fail with empty identity ID", [this](const FDoneDelegate& Done)
		{
			Satori::Authenticate(Client, TEXT(""), false, {}, {}).Next([this, Done](FSatoriSessionResult Result)
			{
				TestTrue("Expected error", Result.bIsError);
				Done.Execute();
			});
		});

		LatentIt("should fail with identity ID too short", [this](const FDoneDelegate& Done)
		{
			Satori::Authenticate(Client, TEXT("abc"), false, {}, {}).Next([this, Done](FSatoriSessionResult Result)
			{
				TestTrue("Expected error", Result.bIsError);
				Done.Execute();
			});
		});
	});

	Describe("AuthenticateRefresh", [this]()
	{
		LatentIt("should refresh a valid session", [this](const FDoneDelegate& Done)
		{
			Satori::Authenticate(Client, TestIdentityId, false, {}, {}).Next([this, Done](FSatoriSessionResult Result)
			{
				SATORI_FAIL_ON_ERROR(Result, Done);
				const FString RefreshToken = Result.Value.RefreshToken;

				Satori::AuthenticateRefresh(Client, RefreshToken).Next([this, Done](FSatoriSessionResult Result)
				{
					SATORI_FAIL_ON_ERROR(Result, Done);
					TestTrue("Refreshed session has token", !Result.Value.Token.IsEmpty());
					TestTrue("Refreshed session has refresh token", !Result.Value.RefreshToken.IsEmpty());
					Done.Execute();
				});
			});
		});

		LatentIt("should fail with invalid refresh token", [this](const FDoneDelegate& Done)
		{
			Satori::AuthenticateRefresh(Client, TEXT("invalid-token")).Next([this, Done](FSatoriSessionResult Result)
			{
				TestTrue("Expected error", Result.bIsError);
				Done.Execute();
			});
		});
	});

	Describe("AuthenticateLogout", [this]()
	{
		LatentIt("should log out a valid session", [this](const FDoneDelegate& Done)
		{
			Satori::Authenticate(Client, TestIdentityId, false, {}, {}).Next([this, Done](FSatoriSessionResult Result)
			{
				SATORI_FAIL_ON_ERROR(Result, Done);
				const FString Token = Result.Value.Token;
				const FString RefreshToken = Result.Value.RefreshToken;

				Satori::AuthenticateLogout(Client, Token, RefreshToken).Next([this, Done](FSatoriVoidResult Result)
				{
					SATORI_FAIL_ON_ERROR(Result, Done);
					Done.Execute();
				});
			});
		});
	});
}

// ============================================================================
// HEALTHCHECK TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FSatoriAsyncHealthcheckSpec, "IntegrationTests.Satori.Healthcheck",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FSatoriClient Client;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7450;

END_DEFINE_SPEC(FSatoriAsyncHealthcheckSpec)

const FString FSatoriAsyncHealthcheckSpec::ServerKey = TEXT("defaultkey");
const FString FSatoriAsyncHealthcheckSpec::Host = TEXT("127.0.0.1");

void FSatoriAsyncHealthcheckSpec::Define()
{
	BeforeEach([this]()
	{
		Client = FSatoriClient{FSatoriApiConfig{ServerKey, Host, Port, false, 10.0f}};
	});

	LatentIt("should return healthy", [this](const FDoneDelegate& Done)
	{
		Satori::Healthcheck(Client, nullptr).Next([this, Done](FSatoriVoidResult Result)
		{
			SATORI_FAIL_ON_ERROR(Result, Done);
			Done.Execute();
		});
	});

	LatentIt("readycheck should return ready", [this](const FDoneDelegate& Done)
	{
		Satori::Readycheck(Client, nullptr).Next([this, Done](FSatoriVoidResult Result)
		{
			SATORI_FAIL_ON_ERROR(Result, Done);
			Done.Execute();
		});
	});
}

// ============================================================================
// IDENTITY TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FSatoriAsyncIdentitySpec, "IntegrationTests.Satori.Identity",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FSatoriClient Client;
	FSatoriSessionPtr Session;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7450;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FSatoriAsyncIdentitySpec)

const FString FSatoriAsyncIdentitySpec::ServerKey = TEXT("defaultkey");
const FString FSatoriAsyncIdentitySpec::Host = TEXT("127.0.0.1");

void FSatoriAsyncIdentitySpec::Define()
{
	BeforeEach([this]()
	{
		Client = FSatoriClient{FSatoriApiConfig{ServerKey, Host, Port, false, 10.0f}};
		Session = nullptr;
	});

	Describe("Identify", [this]()
	{
		LatentIt("should enrich session with a new identity", [this](const FDoneDelegate& Done)
		{
			const FString InitialId = GenerateId();
			const FString NewId = GenerateId();

			Satori::Authenticate(Client, InitialId, false, {}, {}).Next([this, NewId](const FSatoriSession& Sess)
			{
				Session = MakeShared<FSatoriSession>(Sess);
				return Satori::Identify(Client, Session, NewId, {}, {});
			}).Next([this, Done](FSatoriSessionResult Result)
			{
				SATORI_FAIL_ON_ERROR(Result, Done);
				TestTrue("New session has token", !Result.Value.Token.IsEmpty());
				Done.Execute();
			});
		});
	});

	Describe("DeleteIdentity", [this]()
	{
		LatentIt("should delete an identity", [this](const FDoneDelegate& Done)
		{
			const FString Id = GenerateId();

			Satori::Authenticate(Client, Id, false, {}, {}).Next([this](const FSatoriSession& Sess)
			{
				Session = MakeShared<FSatoriSession>(Sess);
				return Satori::DeleteIdentity(Client, Session);
			}).Next([this, Done](FSatoriVoidResult Result)
			{
				SATORI_FAIL_ON_ERROR(Result, Done);
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// PROPERTIES TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FSatoriAsyncPropertiesSpec, "IntegrationTests.Satori.Properties",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FSatoriClient Client;
	FSatoriSessionPtr Session;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7450;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FSatoriAsyncPropertiesSpec)

const FString FSatoriAsyncPropertiesSpec::ServerKey = TEXT("defaultkey");
const FString FSatoriAsyncPropertiesSpec::Host = TEXT("127.0.0.1");

void FSatoriAsyncPropertiesSpec::Define()
{
	BeforeEach([this]()
	{
		Client = FSatoriClient{FSatoriApiConfig{ServerKey, Host, Port, false, 10.0f}};
		Session = nullptr;
	});

	Describe("ListProperties", [this]()
	{
		LatentIt("should list properties for authenticated identity", [this](const FDoneDelegate& Done)
		{
			const FString Id = GenerateId();
			TMap<FString, FString> Defaults;
			Defaults.Add(TEXT("platform"), TEXT("windows"));

			Satori::Authenticate(Client, Id, false, Defaults, {}).Next([this](const FSatoriSession& Sess)
			{
				Session = MakeShared<FSatoriSession>(Sess);
				return Satori::ListProperties(Client, Session);
			}).Next([this, Done](FSatoriPropertiesResult Result)
			{
				SATORI_FAIL_ON_ERROR(Result, Done);
				const auto& Props = Result.Value;
				TestTrue("Default properties contain platform", Props.Default.Contains(TEXT("platform")));
				Done.Execute();
			});
		});
	});

	Describe("UpdateProperties", [this]()
	{
		LatentIt("should update custom properties", [this](const FDoneDelegate& Done)
		{
			const FString Id = GenerateId();

			Satori::Authenticate(Client, Id, false, {}, {}).Next([this](const FSatoriSession& Sess)
			{
				Session = MakeShared<FSatoriSession>(Sess);

				TMap<FString, FString> Custom;
				Custom.Add(TEXT("level"), TEXT("5"));
				Custom.Add(TEXT("rank"), TEXT("gold"));
				return Satori::UpdateProperties(Client, Session, false, {}, Custom);
			}).Next([this](const FSatoriVoid&)
			{
				return Satori::ListProperties(Client, Session);
			}).Next([this, Done](FSatoriPropertiesResult Result)
			{
				SATORI_FAIL_ON_ERROR(Result, Done);
				const auto& Props = Result.Value;
				TestEqual("Custom level", Props.Custom.FindRef(TEXT("level")), TEXT("5"));
				TestEqual("Custom rank", Props.Custom.FindRef(TEXT("rank")), TEXT("gold"));
				Done.Execute();
			});
		});

		LatentIt("should update default properties", [this](const FDoneDelegate& Done)
		{
			const FString Id = GenerateId();

			Satori::Authenticate(Client, Id, false, {}, {}).Next([this](const FSatoriSession& Sess)
			{
				Session = MakeShared<FSatoriSession>(Sess);

				TMap<FString, FString> Defaults;
				Defaults.Add(TEXT("region"), TEXT("eu-west"));
				return Satori::UpdateProperties(Client, Session, false, Defaults, {});
			}).Next([this](const FSatoriVoid&)
			{
				return Satori::ListProperties(Client, Session);
			}).Next([this, Done](FSatoriPropertiesResult Result)
			{
				SATORI_FAIL_ON_ERROR(Result, Done);
				TestEqual("Default region", Result.Value.Default.FindRef(TEXT("region")), TEXT("eu-west"));
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// EVENT TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FSatoriAsyncEventSpec, "IntegrationTests.Satori.Event",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FSatoriClient Client;
	FSatoriSessionPtr Session;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7450;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FSatoriAsyncEventSpec)

const FString FSatoriAsyncEventSpec::ServerKey = TEXT("defaultkey");
const FString FSatoriAsyncEventSpec::Host = TEXT("127.0.0.1");

void FSatoriAsyncEventSpec::Define()
{
	BeforeEach([this]()
	{
		Client = FSatoriClient{FSatoriApiConfig{ServerKey, Host, Port, false, 10.0f}};
		Session = nullptr;
	});

	Describe("Event", [this]()
	{
		LatentIt("should publish a single event", [this](const FDoneDelegate& Done)
		{
			Satori::Authenticate(Client, GenerateId(), false, {}, {}).Next([this](const FSatoriSession& Sess)
			{
				Session = MakeShared<FSatoriSession>(Sess);

				FSatoriEvent Evt;
				Evt.Name = TEXT("game_start");
				Evt.Value = TEXT("tutorial");

				return Satori::Event(Client, Session, {Evt});
			}).Next([this, Done](FSatoriVoidResult Result)
			{
				SATORI_FAIL_ON_ERROR(Result, Done);
				Done.Execute();
			});
		});

		LatentIt("should publish multiple events", [this](const FDoneDelegate& Done)
		{
			Satori::Authenticate(Client, GenerateId(), false, {}, {}).Next([this](const FSatoriSession& Sess)
			{
				Session = MakeShared<FSatoriSession>(Sess);

				FSatoriEvent Evt1;
				Evt1.Name = TEXT("game_start");
				Evt1.Value = TEXT("pvp");

				FSatoriEvent Evt2;
				Evt2.Name = TEXT("level_complete");
				Evt2.Value = TEXT("3");
				Evt2.Metadata.Add(TEXT("score"), TEXT("1500"));

				return Satori::Event(Client, Session, {Evt1, Evt2});
			}).Next([this, Done](FSatoriVoidResult Result)
			{
				SATORI_FAIL_ON_ERROR(Result, Done);
				Done.Execute();
			});
		});

		LatentIt("should publish event with metadata", [this](const FDoneDelegate& Done)
		{
			Satori::Authenticate(Client, GenerateId(), false, {}, {}).Next([this](const FSatoriSession& Sess)
			{
				Session = MakeShared<FSatoriSession>(Sess);

				FSatoriEvent Evt;
				Evt.Name = TEXT("purchase");
				Evt.Value = TEXT("gem_pack_100");
				Evt.Metadata.Add(TEXT("currency"), TEXT("USD"));
				Evt.Metadata.Add(TEXT("amount"), TEXT("9.99"));

				return Satori::Event(Client, Session, {Evt});
			}).Next([this, Done](FSatoriVoidResult Result)
			{
				SATORI_FAIL_ON_ERROR(Result, Done);
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// FLAGS TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FSatoriAsyncFlagsSpec, "IntegrationTests.Satori.Flags",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FSatoriClient Client;
	FSatoriSessionPtr Session;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7450;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FSatoriAsyncFlagsSpec)

const FString FSatoriAsyncFlagsSpec::ServerKey = TEXT("defaultkey");
const FString FSatoriAsyncFlagsSpec::Host = TEXT("127.0.0.1");

void FSatoriAsyncFlagsSpec::Define()
{
	BeforeEach([this]()
	{
		Client = FSatoriClient{FSatoriApiConfig{ServerKey, Host, Port, false, 10.0f}};
		Session = nullptr;
	});

	Describe("GetFlags", [this]()
	{
		LatentIt("should list all flags", [this](const FDoneDelegate& Done)
		{
			Satori::Authenticate(Client, GenerateId(), false, {}, {}).Next([this](const FSatoriSession& Sess)
			{
				Session = MakeShared<FSatoriSession>(Sess);
				return Satori::GetFlags(Client, Session, {}, {});
			}).Next([this, Done](FSatoriFlagListResult Result)
			{
				SATORI_FAIL_ON_ERROR(Result, Done);
				// Fresh server may have no flags configured, but the call should succeed
				Done.Execute();
			});
		});

		LatentIt("should filter flags by name", [this](const FDoneDelegate& Done)
		{
			Satori::Authenticate(Client, GenerateId(), false, {}, {}).Next([this](const FSatoriSession& Sess)
			{
				Session = MakeShared<FSatoriSession>(Sess);
				return Satori::GetFlags(Client, Session, {TEXT("nonexistent_flag")}, {});
			}).Next([this, Done](FSatoriFlagListResult Result)
			{
				SATORI_FAIL_ON_ERROR(Result, Done);
				TestEqual("No flags returned for nonexistent name", Result.Value.Flags.Num(), 0);
				Done.Execute();
			});
		});
	});

	Describe("GetFlagOverrides", [this]()
	{
		LatentIt("should list all flag overrides", [this](const FDoneDelegate& Done)
		{
			Satori::Authenticate(Client, GenerateId(), false, {}, {}).Next([this](const FSatoriSession& Sess)
			{
				Session = MakeShared<FSatoriSession>(Sess);
				return Satori::GetFlagOverrides(Client, Session, {}, {});
			}).Next([this, Done](FSatoriFlagOverrideListResult Result)
			{
				SATORI_FAIL_ON_ERROR(Result, Done);
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// EXPERIMENTS TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FSatoriAsyncExperimentsSpec, "IntegrationTests.Satori.Experiments",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FSatoriClient Client;
	FSatoriSessionPtr Session;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7450;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FSatoriAsyncExperimentsSpec)

const FString FSatoriAsyncExperimentsSpec::ServerKey = TEXT("defaultkey");
const FString FSatoriAsyncExperimentsSpec::Host = TEXT("127.0.0.1");

void FSatoriAsyncExperimentsSpec::Define()
{
	BeforeEach([this]()
	{
		Client = FSatoriClient{FSatoriApiConfig{ServerKey, Host, Port, false, 10.0f}};
		Session = nullptr;
	});

	Describe("GetExperiments", [this]()
	{
		LatentIt("should list all experiments", [this](const FDoneDelegate& Done)
		{
			Satori::Authenticate(Client, GenerateId(), false, {}, {}).Next([this](const FSatoriSession& Sess)
			{
				Session = MakeShared<FSatoriSession>(Sess);
				return Satori::GetExperiments(Client, Session, {}, {});
			}).Next([this, Done](FSatoriExperimentListResult Result)
			{
				SATORI_FAIL_ON_ERROR(Result, Done);
				Done.Execute();
			});
		});

		LatentIt("should filter experiments by name", [this](const FDoneDelegate& Done)
		{
			Satori::Authenticate(Client, GenerateId(), false, {}, {}).Next([this](const FSatoriSession& Sess)
			{
				Session = MakeShared<FSatoriSession>(Sess);
				return Satori::GetExperiments(Client, Session, {TEXT("nonexistent_experiment")}, {});
			}).Next([this, Done](FSatoriExperimentListResult Result)
			{
				SATORI_FAIL_ON_ERROR(Result, Done);
				TestEqual("No experiments for nonexistent name", Result.Value.Experiments.Num(), 0);
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// LIVE EVENTS TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FSatoriAsyncLiveEventsSpec, "IntegrationTests.Satori.LiveEvents",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FSatoriClient Client;
	FSatoriSessionPtr Session;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7450;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FSatoriAsyncLiveEventsSpec)

const FString FSatoriAsyncLiveEventsSpec::ServerKey = TEXT("defaultkey");
const FString FSatoriAsyncLiveEventsSpec::Host = TEXT("127.0.0.1");

void FSatoriAsyncLiveEventsSpec::Define()
{
	BeforeEach([this]()
	{
		Client = FSatoriClient{FSatoriApiConfig{ServerKey, Host, Port, false, 10.0f}};
		Session = nullptr;
	});

	Describe("GetLiveEvents", [this]()
	{
		LatentIt("should list all live events", [this](const FDoneDelegate& Done)
		{
			Satori::Authenticate(Client, GenerateId(), false, {}, {}).Next([this](const FSatoriSession& Sess)
			{
				Session = MakeShared<FSatoriSession>(Sess);
				return Satori::GetLiveEvents(Client, Session, {}, {}, 0, 0, 0, 0);
			}).Next([this, Done](FSatoriLiveEventListResult Result)
			{
				SATORI_FAIL_ON_ERROR(Result, Done);
				Done.Execute();
			});
		});

		LatentIt("should filter live events by name", [this](const FDoneDelegate& Done)
		{
			Satori::Authenticate(Client, GenerateId(), false, {}, {}).Next([this](const FSatoriSession& Sess)
			{
				Session = MakeShared<FSatoriSession>(Sess);
				return Satori::GetLiveEvents(Client, Session, {TEXT("nonexistent_event")}, {}, 0, 0, 0, 0);
			}).Next([this, Done](FSatoriLiveEventListResult Result)
			{
				SATORI_FAIL_ON_ERROR(Result, Done);
				TestEqual("No live events for nonexistent name", Result.Value.LiveEvents.Num(), 0);
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// MESSAGES TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FSatoriAsyncMessagesSpec, "IntegrationTests.Satori.Messages",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FSatoriClient Client;
	FSatoriSessionPtr Session;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7450;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FSatoriAsyncMessagesSpec)

const FString FSatoriAsyncMessagesSpec::ServerKey = TEXT("defaultkey");
const FString FSatoriAsyncMessagesSpec::Host = TEXT("127.0.0.1");

void FSatoriAsyncMessagesSpec::Define()
{
	BeforeEach([this]()
	{
		Client = FSatoriClient{FSatoriApiConfig{ServerKey, Host, Port, false, 10.0f}};
		Session = nullptr;
	});

	Describe("GetMessageList", [this]()
	{
		LatentIt("should list messages for identity", [this](const FDoneDelegate& Done)
		{
			Satori::Authenticate(Client, GenerateId(), false, {}, {}).Next([this](const FSatoriSession& Sess)
			{
				Session = MakeShared<FSatoriSession>(Sess);
				return Satori::GetMessageList(Client, Session, 10, true, TEXT(""), {});
			}).Next([this, Done](FSatoriGetMessageListResponseResult Result)
			{
				SATORI_FAIL_ON_ERROR(Result, Done);
				// Fresh identity has no messages
				TestEqual("No messages for fresh identity", Result.Value.Messages.Num(), 0);
				Done.Execute();
			});
		});

		LatentIt("should list messages in reverse order", [this](const FDoneDelegate& Done)
		{
			Satori::Authenticate(Client, GenerateId(), false, {}, {}).Next([this](const FSatoriSession& Sess)
			{
				Session = MakeShared<FSatoriSession>(Sess);
				return Satori::GetMessageList(Client, Session, 10, false, TEXT(""), {});
			}).Next([this, Done](FSatoriGetMessageListResponseResult Result)
			{
				SATORI_FAIL_ON_ERROR(Result, Done);
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// SESSION LIFECYCLE TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FSatoriAsyncSessionSpec, "IntegrationTests.Satori.Session",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FSatoriClient Client;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7450;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FSatoriAsyncSessionSpec)

const FString FSatoriAsyncSessionSpec::ServerKey = TEXT("defaultkey");
const FString FSatoriAsyncSessionSpec::Host = TEXT("127.0.0.1");

void FSatoriAsyncSessionSpec::Define()
{
	BeforeEach([this]()
	{
		Client = FSatoriClient{FSatoriApiConfig{ServerKey, Host, Port, false, 10.0f}};
	});

	Describe("Full lifecycle", [this]()
	{
		LatentIt("should authenticate, use API, refresh, and logout", [this](const FDoneDelegate& Done)
		{
			const FString Id = GenerateId();
			FSatoriSessionPtr Session;

			Satori::Authenticate(Client, Id, false, {}, {}).Next([this, &Session](const FSatoriSession& Sess)
			{
				Session = MakeShared<FSatoriSession>(Sess);
				return Satori::GetFlags(Client, Session, {}, {});
			}).Next([this, &Session](const FSatoriFlagList&)
			{
				return Satori::AuthenticateRefresh(Client, Session->RefreshToken);
			}).Next([this, Done](FSatoriSessionResult Result)
			{
				SATORI_FAIL_ON_ERROR(Result, Done);
				const FString Token = Result.Value.Token;
				const FString RefreshToken = Result.Value.RefreshToken;

				Satori::AuthenticateLogout(Client, Token, RefreshToken).Next([this, Done](FSatoriVoidResult Result)
				{
					SATORI_FAIL_ON_ERROR(Result, Done);
					Done.Execute();
				});
			});
		});
	});

	Describe("Expired session", [this]()
	{
		LatentIt("should fail API call with invalid bearer token", [this](const FDoneDelegate& Done)
		{
			auto FakeSession = MakeShared<FSatoriSession>();
			FakeSession->Token = TEXT("invalid.bearer.token");
			FakeSession->RefreshToken = TEXT("invalid.refresh.token");

			Satori::GetFlags(Client, FakeSession, {}, {}).Next([this, Done](FSatoriFlagListResult Result)
			{
				TestTrue("Expected error with invalid session", Result.bIsError);
				Done.Execute();
			});
		});
	});
}
