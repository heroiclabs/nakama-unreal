/**
 * Satori Async API Integration Test Suite
 *
 * Tests for all Satori REST API endpoints using the TFuture-based Satori:: free-function API.
 * Mirrors the Nakama async test pattern: each spec authenticates in BeforeEach, then tests
 * individual endpoints.
 */

#include "Satori.h"
#include "Misc/Guid.h"
#include "SatoriConsoleHelper.h"

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

	FSatoriClientConfig ClientConfig;
	FSatoriRetryConfig RetryConfig;
	FString TestIdentityId;

	static FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7450;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FSatoriAsyncAuthSpec)

FString FSatoriAsyncAuthSpec::ServerKey;
const FString FSatoriAsyncAuthSpec::Host = TEXT("127.0.0.1");

void FSatoriAsyncAuthSpec::Define()
{
	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		GetSatoriApiKey().Next([this, Done](FString Key)
		{
			ServerKey = Key;
			Done.Execute();
		});
	});

	BeforeEach([this]()
	{
		ClientConfig = FSatoriClientConfig{ServerKey, Host, Port, false};
		TestIdentityId = GenerateId();
	});

	Describe("Authenticate", [this]()
	{
		LatentIt("should authenticate with valid identity ID", [this](const FDoneDelegate& Done)
		{
			Satori::Authenticate(ClientConfig, TestIdentityId, false, {}, {}).Next([this, Done](FSatoriSessionResult Result)
			{
				SATORI_FAIL_ON_ERROR(Result, Done);
				TestTrue("Session has token", !Result.Value.Token.IsEmpty());
				TestTrue("Session has refresh token", !Result.Value.RefreshToken.IsEmpty());
				Done.Execute();
			});
		});

		LatentIt("should authenticate with no_session flag", [this](const FDoneDelegate& Done)
		{
			Satori::Authenticate(ClientConfig, TestIdentityId, true, {}, {}).Next([this, Done](FSatoriSessionResult Result)
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

			Satori::Authenticate(ClientConfig, TestIdentityId, false, Defaults, {}).Next([this, Done](FSatoriSessionResult Result)
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

			Satori::Authenticate(ClientConfig, TestIdentityId, false, {}, Custom).Next([this, Done](FSatoriSessionResult Result)
			{
				SATORI_FAIL_ON_ERROR(Result, Done);
				TestTrue("Session has token", !Result.Value.Token.IsEmpty());
				Done.Execute();
			});
		});

		LatentIt("should fail with empty identity ID", [this](const FDoneDelegate& Done)
		{
			Satori::Authenticate(ClientConfig, TEXT(""), false, {}, {}).Next([this, Done](FSatoriSessionResult Result)
			{
				TestTrue("Expected error", Result.bIsError);
				Done.Execute();
			});
		});

		LatentIt("should fail with identity ID too short", [this](const FDoneDelegate& Done)
		{
			Satori::Authenticate(ClientConfig, TEXT("abc"), false, {}, {}).Next([this, Done](FSatoriSessionResult Result)
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
			Satori::Authenticate(ClientConfig, TestIdentityId, false, {}, {}).Next([this, Done](FSatoriSessionResult Result)
			{
				SATORI_FAIL_ON_ERROR(Result, Done);
				const FString RefreshToken = Result.Value.RefreshToken;

				Satori::AuthenticateRefresh(ClientConfig, RefreshToken).Next([this, Done](FSatoriSessionResult Result)
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
			Satori::AuthenticateRefresh(ClientConfig, TEXT("invalid-token")).Next([this, Done](FSatoriSessionResult Result)
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
			Satori::Authenticate(ClientConfig, TestIdentityId, false, {}, {}).Next([this, Done](FSatoriSessionResult Result)
			{
				SATORI_FAIL_ON_ERROR(Result, Done);
				const FString Token = Result.Value.Token;
				const FString RefreshToken = Result.Value.RefreshToken;

				Satori::AuthenticateLogout(ClientConfig, Token, RefreshToken).Next([this, Done](FSatoriVoidResult Result)
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

	FSatoriClientConfig ClientConfig;
	FSatoriRetryConfig RetryConfig;

	static FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7450;

END_DEFINE_SPEC(FSatoriAsyncHealthcheckSpec)

FString FSatoriAsyncHealthcheckSpec::ServerKey;
const FString FSatoriAsyncHealthcheckSpec::Host = TEXT("127.0.0.1");

void FSatoriAsyncHealthcheckSpec::Define()
{
	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		GetSatoriApiKey().Next([this, Done](FString Key)
		{
			ServerKey = Key;
			Done.Execute();
		});
	});

	BeforeEach([this]()
	{
		ClientConfig = FSatoriClientConfig{ServerKey, Host, Port, false};
	});

	LatentIt("should return healthy", [this](const FDoneDelegate& Done)
	{
		Satori::Healthcheck(ClientConfig, FSatoriSession{}).Next([this, Done](FSatoriVoidResult Result)
		{
			SATORI_FAIL_ON_ERROR(Result, Done);
			Done.Execute();
		});
	});

	LatentIt("readycheck should return ready", [this](const FDoneDelegate& Done)
	{
		Satori::Readycheck(ClientConfig, FSatoriSession{}).Next([this, Done](FSatoriVoidResult Result)
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

	FSatoriClientConfig ClientConfig;
	FSatoriRetryConfig RetryConfig;
	FSatoriSession Session;

	static FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7450;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FSatoriAsyncIdentitySpec)

FString FSatoriAsyncIdentitySpec::ServerKey;
const FString FSatoriAsyncIdentitySpec::Host = TEXT("127.0.0.1");

void FSatoriAsyncIdentitySpec::Define()
{
	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		GetSatoriApiKey().Next([this, Done](FString Key)
		{
			ServerKey = Key;
			Done.Execute();
		});
	});

	BeforeEach([this]()
	{
		ClientConfig = FSatoriClientConfig{ServerKey, Host, Port, false};
		Session = FSatoriSession{};
	});

	Describe("Identify", [this]()
	{
		LatentIt("should enrich session with a new identity", [this](const FDoneDelegate& Done)
		{
			const FString InitialId = GenerateId();
			const FString NewId = GenerateId();

			Satori::Authenticate(ClientConfig, InitialId, false, {}, {}).Next([this, NewId](const FSatoriSession& Sess)
			{
				Session = Sess;
				return Satori::Identify(ClientConfig, Session, NewId, {}, {});
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

			Satori::Authenticate(ClientConfig, Id, false, {}, {}).Next([this](const FSatoriSession& Sess)
			{
				Session = Sess;
				return Satori::DeleteIdentity(ClientConfig, Session);
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

	FSatoriClientConfig ClientConfig;
	FSatoriRetryConfig RetryConfig;
	FSatoriSession Session;

	static FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7450;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FSatoriAsyncPropertiesSpec)

FString FSatoriAsyncPropertiesSpec::ServerKey;
const FString FSatoriAsyncPropertiesSpec::Host = TEXT("127.0.0.1");

void FSatoriAsyncPropertiesSpec::Define()
{
	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		GetSatoriApiKey().Next([this, Done](FString Key)
		{
			ServerKey = Key;
			Done.Execute();
		});
	});

	BeforeEach([this]()
	{
		ClientConfig = FSatoriClientConfig{ServerKey, Host, Port, false};
		Session = FSatoriSession{};
	});

	Describe("ListProperties", [this]()
	{
		LatentIt("should list properties for authenticated identity", [this](const FDoneDelegate& Done)
		{
			const FString Id = GenerateId();
			TMap<FString, FString> Defaults;
			Defaults.Add(TEXT("platform"), TEXT("windows"));

			Satori::Authenticate(ClientConfig, Id, false, Defaults, {}).Next([this](const FSatoriSession& Sess)
			{
				Session = Sess;
				return Satori::ListProperties(ClientConfig, Session);
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

			Satori::Authenticate(ClientConfig, Id, false, {}, {}).Next([this](const FSatoriSession& Sess)
			{
				Session = Sess;

				TMap<FString, FString> Custom;
				Custom.Add(TEXT("level"), TEXT("5"));
				Custom.Add(TEXT("rank"), TEXT("gold"));
				return Satori::UpdateProperties(ClientConfig, Session, false, {}, Custom);
			}).Next([this](const FSatoriVoid&)
			{
				return Satori::ListProperties(ClientConfig, Session);
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

			Satori::Authenticate(ClientConfig, Id, false, {}, {}).Next([this](const FSatoriSession& Sess)
			{
				Session = Sess;

				TMap<FString, FString> Defaults;
				Defaults.Add(TEXT("region"), TEXT("eu-west"));
				return Satori::UpdateProperties(ClientConfig, Session, false, Defaults, {});
			}).Next([this](const FSatoriVoid&)
			{
				return Satori::ListProperties(ClientConfig, Session);
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

	FSatoriClientConfig ClientConfig;
	FSatoriRetryConfig RetryConfig;
	FSatoriSession Session;

	static FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7450;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FSatoriAsyncEventSpec)

FString FSatoriAsyncEventSpec::ServerKey;
const FString FSatoriAsyncEventSpec::Host = TEXT("127.0.0.1");

void FSatoriAsyncEventSpec::Define()
{
	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		GetSatoriApiKey().Next([this, Done](FString Key)
		{
			ServerKey = Key;
			Done.Execute();
		});
	});

	BeforeEach([this]()
	{
		ClientConfig = FSatoriClientConfig{ServerKey, Host, Port, false};
		Session = FSatoriSession{};
	});

	Describe("Event", [this]()
	{
		LatentIt("should publish a single event", [this](const FDoneDelegate& Done)
		{
			Satori::Authenticate(ClientConfig, GenerateId(), false, {}, {}).Next([this](const FSatoriSession& Sess)
			{
				Session = Sess;

				FSatoriEvent Evt;
				Evt.Name = TEXT("game_start");
				Evt.Value = TEXT("tutorial");

				return Satori::Event(ClientConfig, Session, {Evt});
			}).Next([this, Done](FSatoriVoidResult Result)
			{
				SATORI_FAIL_ON_ERROR(Result, Done);
				Done.Execute();
			});
		});

		LatentIt("should publish multiple events", [this](const FDoneDelegate& Done)
		{
			Satori::Authenticate(ClientConfig, GenerateId(), false, {}, {}).Next([this](const FSatoriSession& Sess)
			{
				Session = Sess;

				FSatoriEvent Evt1;
				Evt1.Name = TEXT("game_start");
				Evt1.Value = TEXT("pvp");

				FSatoriEvent Evt2;
				Evt2.Name = TEXT("level_complete");
				Evt2.Value = TEXT("3");
				Evt2.Metadata.Add(TEXT("score"), TEXT("1500"));

				return Satori::Event(ClientConfig, Session, {Evt1, Evt2});
			}).Next([this, Done](FSatoriVoidResult Result)
			{
				SATORI_FAIL_ON_ERROR(Result, Done);
				Done.Execute();
			});
		});

		LatentIt("should publish event with metadata", [this](const FDoneDelegate& Done)
		{
			Satori::Authenticate(ClientConfig, GenerateId(), false, {}, {}).Next([this](const FSatoriSession& Sess)
			{
				Session = Sess;

				FSatoriEvent Evt;
				Evt.Name = TEXT("purchase");
				Evt.Value = TEXT("gem_pack_100");
				Evt.Metadata.Add(TEXT("currency"), TEXT("USD"));
				Evt.Metadata.Add(TEXT("amount"), TEXT("9.99"));

				return Satori::Event(ClientConfig, Session, {Evt});
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

	FSatoriClientConfig ClientConfig;
	FSatoriRetryConfig RetryConfig;
	FSatoriSession Session;

	static FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7450;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FSatoriAsyncFlagsSpec)

FString FSatoriAsyncFlagsSpec::ServerKey;
const FString FSatoriAsyncFlagsSpec::Host = TEXT("127.0.0.1");

void FSatoriAsyncFlagsSpec::Define()
{
	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		GetSatoriApiKey().Next([this, Done](FString Key)
		{
			ServerKey = Key;
			Done.Execute();
		});
	});

	BeforeEach([this]()
	{
		ClientConfig = FSatoriClientConfig{ServerKey, Host, Port, false};
		Session = FSatoriSession{};
	});

	Describe("GetFlags", [this]()
	{
		LatentIt("should list all flags", [this](const FDoneDelegate& Done)
		{
			Satori::Authenticate(ClientConfig, GenerateId(), false, {}, {}).Next([this](const FSatoriSession& Sess)
			{
				Session = Sess;
				return Satori::GetFlags(ClientConfig, Session, {}, {});
			}).Next([this, Done](FSatoriFlagListResult Result)
			{
				SATORI_FAIL_ON_ERROR(Result, Done);
				// Fresh server may have no flags configured, but the call should succeed
				Done.Execute();
			});
		});

		LatentIt("should filter flags by name", [this](const FDoneDelegate& Done)
		{
			Satori::Authenticate(ClientConfig, GenerateId(), false, {}, {}).Next([this](const FSatoriSession& Sess)
			{
				Session = Sess;
				return Satori::GetFlags(ClientConfig, Session, {TEXT("nonexistent_flag")}, {});
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
			Satori::Authenticate(ClientConfig, GenerateId(), false, {}, {}).Next([this](const FSatoriSession& Sess)
			{
				Session = Sess;
				return Satori::GetFlagOverrides(ClientConfig, Session, {}, {});
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

	FSatoriClientConfig ClientConfig;
	FSatoriRetryConfig RetryConfig;
	FSatoriSession Session;

	static FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7450;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FSatoriAsyncExperimentsSpec)

FString FSatoriAsyncExperimentsSpec::ServerKey;
const FString FSatoriAsyncExperimentsSpec::Host = TEXT("127.0.0.1");

void FSatoriAsyncExperimentsSpec::Define()
{
	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		GetSatoriApiKey().Next([this, Done](FString Key)
		{
			ServerKey = Key;
			Done.Execute();
		});
	});

	BeforeEach([this]()
	{
		ClientConfig = FSatoriClientConfig{ServerKey, Host, Port, false};
		Session = FSatoriSession{};
	});

	Describe("GetExperiments", [this]()
	{
		LatentIt("should list all experiments", [this](const FDoneDelegate& Done)
		{
			Satori::Authenticate(ClientConfig, GenerateId(), false, {}, {}).Next([this](const FSatoriSession& Sess)
			{
				Session = Sess;
				return Satori::GetExperiments(ClientConfig, Session, {}, {});
			}).Next([this, Done](FSatoriExperimentListResult Result)
			{
				SATORI_FAIL_ON_ERROR(Result, Done);
				Done.Execute();
			});
		});

		LatentIt("should filter experiments by name", [this](const FDoneDelegate& Done)
		{
			Satori::Authenticate(ClientConfig, GenerateId(), false, {}, {}).Next([this](const FSatoriSession& Sess)
			{
				Session = Sess;
				return Satori::GetExperiments(ClientConfig, Session, {TEXT("nonexistent_experiment")}, {});
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

	FSatoriClientConfig ClientConfig;
	FSatoriRetryConfig RetryConfig;
	FSatoriSession Session;

	static FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7450;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FSatoriAsyncLiveEventsSpec)

FString FSatoriAsyncLiveEventsSpec::ServerKey;
const FString FSatoriAsyncLiveEventsSpec::Host = TEXT("127.0.0.1");

void FSatoriAsyncLiveEventsSpec::Define()
{
	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		GetSatoriApiKey().Next([this, Done](FString Key)
		{
			ServerKey = Key;
			Done.Execute();
		});
	});

	BeforeEach([this]()
	{
		ClientConfig = FSatoriClientConfig{ServerKey, Host, Port, false};
		Session = FSatoriSession{};
	});

	Describe("GetLiveEvents", [this]()
	{
		LatentIt("should list all live events", [this](const FDoneDelegate& Done)
		{
			Satori::Authenticate(ClientConfig, GenerateId(), false, {}, {}).Next([this](const FSatoriSession& Sess)
			{
				Session = Sess;
				return Satori::GetLiveEvents(ClientConfig, Session, {}, {}, 0, 0, 0, 0);
			}).Next([this, Done](FSatoriLiveEventListResult Result)
			{
				SATORI_FAIL_ON_ERROR(Result, Done);
				Done.Execute();
			});
		});

		LatentIt("should filter live events by name", [this](const FDoneDelegate& Done)
		{
			Satori::Authenticate(ClientConfig, GenerateId(), false, {}, {}).Next([this](const FSatoriSession& Sess)
			{
				Session = Sess;
				return Satori::GetLiveEvents(ClientConfig, Session, {TEXT("nonexistent_event")}, {}, 0, 0, 0, 0);
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

	FSatoriClientConfig ClientConfig;
	FSatoriRetryConfig RetryConfig;
	FSatoriSession Session;

	static FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7450;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FSatoriAsyncMessagesSpec)

FString FSatoriAsyncMessagesSpec::ServerKey;
const FString FSatoriAsyncMessagesSpec::Host = TEXT("127.0.0.1");

void FSatoriAsyncMessagesSpec::Define()
{
	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		GetSatoriApiKey().Next([this, Done](FString Key)
		{
			ServerKey = Key;
			Done.Execute();
		});
	});

	BeforeEach([this]()
	{
		ClientConfig = FSatoriClientConfig{ServerKey, Host, Port, false};
		Session = FSatoriSession{};
	});

	Describe("GetMessageList", [this]()
	{
		LatentIt("should list messages for identity", [this](const FDoneDelegate& Done)
		{
			Satori::Authenticate(ClientConfig, GenerateId(), false, {}, {}).Next([this](const FSatoriSession& Sess)
			{
				Session = Sess;
				return Satori::GetMessageList(ClientConfig, Session, 10, true, TEXT(""), {});
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
			Satori::Authenticate(ClientConfig, GenerateId(), false, {}, {}).Next([this](const FSatoriSession& Sess)
			{
				Session = Sess;
				return Satori::GetMessageList(ClientConfig, Session, 10, false, TEXT(""), {});
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

	FSatoriClientConfig ClientConfig;
	FSatoriRetryConfig RetryConfig;
	FSatoriSession Session;

	static FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7450;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FSatoriAsyncSessionSpec)

FString FSatoriAsyncSessionSpec::ServerKey;
const FString FSatoriAsyncSessionSpec::Host = TEXT("127.0.0.1");

void FSatoriAsyncSessionSpec::Define()
{
	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		GetSatoriApiKey().Next([this, Done](FString Key)
		{
			ServerKey = Key;
			Done.Execute();
		});
	});

	BeforeEach([this]()
	{
		ClientConfig = FSatoriClientConfig{ServerKey, Host, Port, false};
	});

	Describe("Full lifecycle", [this]()
	{
		LatentIt("should authenticate, use API, refresh, and logout", [this](const FDoneDelegate& Done)
		{
			const FString Id = GenerateId();

			Satori::Authenticate(ClientConfig, Id, false, {}, {}).Next([this](const FSatoriSession& Sess)
			{
				Session = Sess;
				return Satori::GetFlags(ClientConfig, Session, {}, {});
			}).Next([this](const FSatoriFlagList&)
			{
				return Satori::AuthenticateRefresh(ClientConfig, Session.RefreshToken);
			}).Next([this, Done](FSatoriSessionResult Result)
			{
				SATORI_FAIL_ON_ERROR(Result, Done);
				const FString Token = Result.Value.Token;
				const FString RefreshToken = Result.Value.RefreshToken;

				Satori::AuthenticateLogout(ClientConfig, Token, RefreshToken).Next([this, Done](FSatoriVoidResult Result)
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
			FSatoriSession FakeSession;
			FakeSession.Token = TEXT("invalid.bearer.token");
			FakeSession.RefreshToken = TEXT("invalid.refresh.token");

			Satori::GetFlags(ClientConfig, FakeSession, {}, {}).Next([this, Done](FSatoriFlagListResult Result)
			{
				TestTrue("Expected error with invalid session", Result.bIsError);
				Done.Execute();
			});
		});
	});
}
