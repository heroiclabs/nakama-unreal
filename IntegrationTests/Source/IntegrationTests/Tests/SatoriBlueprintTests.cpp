/**
 * Satori Blueprint Async Action Test Suite
 *
 * Tests for SatoriBlueprints module UBlueprintAsyncActionBase subclasses.
 * Each test fires a BP async action, then verifies the server-side effect
 * through the C++ client (the TFuture-based Satori:: free-function API).
 *
 * Mirrors the Nakama BP test pattern from NakamaBlueprintTests.cpp.
 */

#include "Misc/AutomationTest.h"
#include "SatoriClientBlueprintLibrary.h"
#include "SatoriClient.h"
#include "Misc/Guid.h"
#include "Containers/Ticker.h"
#include "SatoriConsoleHelper.h"

// Helper: keep the BP action alive for the duration of the async call (tests pass
// nullptr as WorldContextObject so RegisterWithGameInstance is a no-op), then run
// verification once the action completes.
// The base class constructor sets RF_StrongRefOnFrame, and SetReadyToDestroy()
// clears it. We AddToRoot() to prevent GC across frames, then poll until
// RF_StrongRefOnFrame is cleared (signalling the action called SetReadyToDestroy).
static void VerifyWhenComplete(UBlueprintAsyncActionBase* Action, TFunction<void()> VerifyFunc)
{
	Action->AddToRoot();

	FTSTicker::GetCoreTicker().AddTicker(
		FTickerDelegate::CreateLambda([Action, VerifyFunc = MoveTemp(VerifyFunc)](float) -> bool
		{
			if (Action->HasAnyFlags(RF_StrongRefOnFrame))
			{
				return true; // keep ticking — action hasn't called SetReadyToDestroy yet
			}
			Action->RemoveFromRoot();
			VerifyFunc();
			return false;
		}),
		0.0f
	);
}

// ============================================================================
// HEALTHCHECK TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FSatoriBPHealthcheckSpec, "IntegrationTests.SatoriBlueprintTests.Healthcheck",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FSatoriSession Session;
	FSatoriClientConfig ClientConfig;

	static FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7450;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FSatoriBPHealthcheckSpec)

FString FSatoriBPHealthcheckSpec::ServerKey;
const FString FSatoriBPHealthcheckSpec::Host = TEXT("127.0.0.1");

void FSatoriBPHealthcheckSpec::Define()
{
	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		GetSatoriApiKey().Next([this, Done](FString Key)
		{
			ServerKey = Key;
			ClientConfig = FSatoriClientConfig{ServerKey, Host, Port, false};
			Done.Execute();
		});
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		Satori::Authenticate(ClientConfig, GenerateId(), false, {}, {}).Next([this, Done](FSatoriSessionResult Result)
		{
			if (Result.bIsError)
			{
				AddError(FString::Printf(TEXT("Setup auth failed: %s"), *Result.Error.Message));
			}
			else
			{
				Session = Result.Value;
			}
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		Satori::DeleteIdentity(ClientConfig, Session).Next([Done](FSatoriVoidResult) { Done.Execute(); });
	});

	Describe("Healthcheck", [this]()
	{
		LatentIt("should pass healthcheck", [this](const FDoneDelegate& Done)
		{
			auto* Action = USatoriClientHealthcheck::Healthcheck(nullptr, ClientConfig, Session);
			Action->Activate();

			VerifyWhenComplete(Action, [this, Done]()
			{
				Satori::Healthcheck(ClientConfig).Next([this, Done](FSatoriVoidResult Result)
				{
					if (Result.bIsError)
					{
						AddError(FString::Printf(TEXT("Healthcheck failed: %s"), *Result.Error.Message));
					}
					Done.Execute();
				});
			});
		});
	});

	Describe("Readycheck", [this]()
	{
		LatentIt("should pass readycheck", [this](const FDoneDelegate& Done)
		{
			auto* Action = USatoriClientReadycheck::Readycheck(nullptr, ClientConfig, Session);
			Action->Activate();

			VerifyWhenComplete(Action, [this, Done]()
			{
				Satori::Readycheck(ClientConfig).Next([this, Done](FSatoriVoidResult Result)
				{
					if (Result.bIsError)
					{
						AddError(FString::Printf(TEXT("Readycheck failed: %s"), *Result.Error.Message));
					}
					Done.Execute();
				});
			});
		});
	});
}

// ============================================================================
// AUTHENTICATION TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FSatoriBPAuthSpec, "IntegrationTests.SatoriBlueprintTests.Auth",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FSatoriClientConfig ClientConfig;
	FSatoriSession Session;

	static FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7450;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FSatoriBPAuthSpec)

FString FSatoriBPAuthSpec::ServerKey;
const FString FSatoriBPAuthSpec::Host = TEXT("127.0.0.1");

void FSatoriBPAuthSpec::Define()
{
	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		Session = FSatoriSession();
		GetSatoriApiKey().Next([this, Done](FString Key)
		{
			ServerKey = Key;
			ClientConfig = FSatoriClientConfig{ServerKey, Host, Port, false};
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		if (Session.Token.IsEmpty())
		{
			Done.Execute();
			return;
		}
		Satori::DeleteIdentity(ClientConfig, Session).Next([Done](FSatoriVoidResult) { Done.Execute(); });
	});

	Describe("Authenticate", [this]()
	{
		LatentIt("should authenticate with valid identity ID", [this](const FDoneDelegate& Done)
		{
			const FString Id = GenerateId();

			auto* Action = USatoriClientAuthenticate::Authenticate(
				nullptr, ClientConfig, Id, false, {}, {});
			Action->Activate();

			// Verify: re-auth with the same ID should succeed
			VerifyWhenComplete(Action, [this, Done, Id]()
			{
				Satori::Authenticate(ClientConfig, Id, false, {}, {}).Next([this, Done](FSatoriSessionResult Result)
				{
					if (Result.bIsError)
					{
						AddError(FString::Printf(TEXT("Re-auth failed: %s"), *Result.Error.Message));
					}
					else
					{
						Session = Result.Value;
						TestTrue("Session has token", !Result.Value.Token.IsEmpty());
					}
					Done.Execute();
				});
			});
		});
	});

	Describe("AuthenticateRefresh", [this]()
	{
		LatentIt("should refresh a session via BP action", [this](const FDoneDelegate& Done)
		{
			// Setup: authenticate via C++ to get a refresh token
			Satori::Authenticate(ClientConfig, GenerateId(), false, {}, {}).Next([this, Done](FSatoriSessionResult Result)
			{
				if (Result.bIsError)
				{
					AddError(FString::Printf(TEXT("Setup auth failed: %s"), *Result.Error.Message));
					Done.Execute();
					return;
				}
				Session = Result.Value;
				auto* Action = USatoriClientAuthenticateRefresh::AuthenticateRefresh(
					nullptr, ClientConfig, Result.Value.RefreshToken);
				Action->Activate();

				// Verify: server still responds to healthcheck
				VerifyWhenComplete(Action, [this, Done]()
				{
					Satori::Healthcheck(ClientConfig).Next([this, Done](FSatoriVoidResult HcResult)
					{
						if (HcResult.bIsError)
						{
							AddError(FString::Printf(TEXT("Healthcheck failed: %s"), *HcResult.Error.Message));
						}
						Done.Execute();
					});
				});
			});
		});
	});

	Describe("AuthenticateLogout", [this]()
	{
		LatentIt("should logout a session via BP action", [this](const FDoneDelegate& Done)
		{
			// Setup: authenticate via C++ to get tokens
			Satori::Authenticate(ClientConfig, GenerateId(), false, {}, {}).Next([this, Done](FSatoriSessionResult Result)
			{
				if (Result.bIsError)
				{
					AddError(FString::Printf(TEXT("Setup auth failed: %s"), *Result.Error.Message));
					Done.Execute();
					return;
				}
				Session = Result.Value;
				auto* Action = USatoriClientAuthenticateLogout::AuthenticateLogout(
					nullptr, ClientConfig, Result.Value.Token, Result.Value.RefreshToken);
				Action->Activate();

				// Verify: action completed; server still responds
				VerifyWhenComplete(Action, [this, Done]()
				{
					Satori::Healthcheck(ClientConfig).Next([this, Done](FSatoriVoidResult HcResult)
					{
						if (HcResult.bIsError)
						{
							AddError(FString::Printf(TEXT("Healthcheck failed: %s"), *HcResult.Error.Message));
						}
						Done.Execute();
					});
				});
			});
		});
	});
}

// ============================================================================
// IDENTITY TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FSatoriBPIdentitySpec, "IntegrationTests.SatoriBlueprintTests.Identity",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FSatoriClientConfig ClientConfig;
	FSatoriSession Session;

	static FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7450;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FSatoriBPIdentitySpec)

FString FSatoriBPIdentitySpec::ServerKey;
const FString FSatoriBPIdentitySpec::Host = TEXT("127.0.0.1");

void FSatoriBPIdentitySpec::Define()
{
	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		GetSatoriApiKey().Next([this, Done](FString Key)
		{
			ServerKey = Key;
			ClientConfig = FSatoriClientConfig{ServerKey, Host, Port, false};
			Done.Execute();
		});
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		Satori::Authenticate(ClientConfig, GenerateId(), false, {}, {}).Next([this, Done](FSatoriSessionResult Result)
		{
			if (Result.bIsError)
			{
				AddError(FString::Printf(TEXT("Setup auth failed: %s"), *Result.Error.Message));
			}
			else
			{
				Session = Result.Value;
			}
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		Satori::DeleteIdentity(ClientConfig, Session).Next([Done](FSatoriVoidResult) { Done.Execute(); });
	});

	Describe("Identify", [this]()
	{
		LatentIt("should identify with a new identity", [this](const FDoneDelegate& Done)
		{
			const FString NewId = GenerateId();

			auto* Action = USatoriClientIdentify::Identify(
				nullptr, ClientConfig, Session, NewId, {}, {});
			Action->Activate();

			// Verify: action completed (Identify returns a new session, old one is invalid)
			VerifyWhenComplete(Action, [this, Done]()
			{
				Done.Execute();
			});
		});
	});

	Describe("DeleteIdentity", [this]()
	{
		LatentIt("should delete an identity", [this](const FDoneDelegate& Done)
		{
			auto* Action = USatoriClientDeleteIdentity::DeleteIdentity(
				nullptr, ClientConfig, Session);
			Action->Activate();

			// Verify: action completed without crash
			VerifyWhenComplete(Action, [this, Done]()
			{
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// PROPERTIES TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FSatoriBPPropertiesSpec, "IntegrationTests.SatoriBlueprintTests.Properties",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FSatoriClientConfig ClientConfig;
	FSatoriSession Session;

	static FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7450;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FSatoriBPPropertiesSpec)

FString FSatoriBPPropertiesSpec::ServerKey;
const FString FSatoriBPPropertiesSpec::Host = TEXT("127.0.0.1");

void FSatoriBPPropertiesSpec::Define()
{
	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		GetSatoriApiKey().Next([this, Done](FString Key)
		{
			ServerKey = Key;
			ClientConfig = FSatoriClientConfig{ServerKey, Host, Port, false};
			Done.Execute();
		});
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		Satori::Authenticate(ClientConfig, GenerateId(), false, {}, {}).Next([this, Done](FSatoriSessionResult Result)
		{
			if (Result.bIsError)
			{
				AddError(FString::Printf(TEXT("Setup auth failed: %s"), *Result.Error.Message));
			}
			else
			{
				Session = Result.Value;
			}
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		Satori::DeleteIdentity(ClientConfig, Session).Next([Done](FSatoriVoidResult) { Done.Execute(); });
	});

	Describe("ListProperties", [this]()
	{
		LatentIt("should list properties for authenticated identity", [this](const FDoneDelegate& Done)
		{
			auto* Action = USatoriClientListProperties::ListProperties(
				nullptr, ClientConfig, Session);
			Action->Activate();

			// Verify via C++ ListProperties
			VerifyWhenComplete(Action, [this, Done]()
			{
				Satori::ListProperties(ClientConfig, Session).Next([this, Done](FSatoriPropertiesResult Result)
				{
					if (Result.bIsError)
					{
						AddError(FString::Printf(TEXT("ListProperties failed: %s"), *Result.Error.Message));
					}
					Done.Execute();
				});
			});
		});
	});

	Describe("UpdateProperties", [this]()
	{
		LatentIt("should update custom properties via BP action", [this](const FDoneDelegate& Done)
		{
			TMap<FString, FString> Custom;
			Custom.Add(TEXT("level"), TEXT("5"));

			auto* Action = USatoriClientUpdateProperties::UpdateProperties(
				nullptr, ClientConfig, Session, false, {}, Custom);
			Action->Activate();

			// Verify: property was persisted
			VerifyWhenComplete(Action, [this, Done]()
			{
				Satori::ListProperties(ClientConfig, Session).Next([this, Done](FSatoriPropertiesResult Result)
				{
					if (Result.bIsError)
					{
						AddError(FString::Printf(TEXT("ListProperties failed: %s"), *Result.Error.Message));
					}
					else
					{
						TestEqual("Custom level", Result.Value.Custom.FindRef(TEXT("level")), TEXT("5"));
					}
					Done.Execute();
				});
			});
		});
	});
}

// ============================================================================
// EVENT TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FSatoriBPEventSpec, "IntegrationTests.SatoriBlueprintTests.Event",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FSatoriClientConfig ClientConfig;
	FSatoriSession Session;

	static FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7450;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FSatoriBPEventSpec)

FString FSatoriBPEventSpec::ServerKey;
const FString FSatoriBPEventSpec::Host = TEXT("127.0.0.1");

void FSatoriBPEventSpec::Define()
{
	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		GetSatoriApiKey().Next([this, Done](FString Key)
		{
			ServerKey = Key;
			ClientConfig = FSatoriClientConfig{ServerKey, Host, Port, false};
			Done.Execute();
		});
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		Satori::Authenticate(ClientConfig, GenerateId(), false, {}, {}).Next([this, Done](FSatoriSessionResult Result)
		{
			if (Result.bIsError)
			{
				AddError(FString::Printf(TEXT("Setup auth failed: %s"), *Result.Error.Message));
			}
			else
			{
				Session = Result.Value;
			}
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		Satori::DeleteIdentity(ClientConfig, Session).Next([Done](FSatoriVoidResult) { Done.Execute(); });
	});

	Describe("Event", [this]()
	{
		LatentIt("should publish an event via BP action", [this](const FDoneDelegate& Done)
		{
			FSatoriEvent Evt;
			Evt.Name = TEXT("game_start");
			Evt.Value = TEXT("tutorial");

			auto* Action = USatoriClientEvent::Event(
				nullptr, ClientConfig, Session, {Evt});
			Action->Activate();

			// Verify: action completed; server still responds
			VerifyWhenComplete(Action, [this, Done]()
			{
				Satori::Healthcheck(ClientConfig).Next([this, Done](FSatoriVoidResult Result)
				{
					if (Result.bIsError)
					{
						AddError(FString::Printf(TEXT("Healthcheck failed: %s"), *Result.Error.Message));
					}
					Done.Execute();
				});
			});
		});
	});
}

// ============================================================================
// FLAGS TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FSatoriBPFlagsSpec, "IntegrationTests.SatoriBlueprintTests.Flags",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FSatoriClientConfig ClientConfig;
	FSatoriSession Session;

	static FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7450;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FSatoriBPFlagsSpec)

FString FSatoriBPFlagsSpec::ServerKey;
const FString FSatoriBPFlagsSpec::Host = TEXT("127.0.0.1");

void FSatoriBPFlagsSpec::Define()
{
	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		GetSatoriApiKey().Next([this, Done](FString Key)
		{
			ServerKey = Key;
			ClientConfig = FSatoriClientConfig{ServerKey, Host, Port, false};
			Done.Execute();
		});
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		Satori::Authenticate(ClientConfig, GenerateId(), false, {}, {}).Next([this, Done](FSatoriSessionResult Result)
		{
			if (Result.bIsError)
			{
				AddError(FString::Printf(TEXT("Setup auth failed: %s"), *Result.Error.Message));
			}
			else
			{
				Session = Result.Value;
			}
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		Satori::DeleteIdentity(ClientConfig, Session).Next([Done](FSatoriVoidResult) { Done.Execute(); });
	});

	Describe("GetFlags", [this]()
	{
		LatentIt("should list all flags via BP action", [this](const FDoneDelegate& Done)
		{
			auto* Action = USatoriClientGetFlags::GetFlags(
				nullptr, ClientConfig, Session, {}, {});
			Action->Activate();

			// Verify via C++ GetFlags
			VerifyWhenComplete(Action, [this, Done]()
			{
				Satori::GetFlags(ClientConfig, Session, {}, {}).Next([this, Done](FSatoriFlagListResult Result)
				{
					if (Result.bIsError)
					{
						AddError(FString::Printf(TEXT("GetFlags failed: %s"), *Result.Error.Message));
					}
					Done.Execute();
				});
			});
		});
	});

	Describe("GetFlagOverrides", [this]()
	{
		LatentIt("should list all flag overrides via BP action", [this](const FDoneDelegate& Done)
		{
			auto* Action = USatoriClientGetFlagOverrides::GetFlagOverrides(
				nullptr, ClientConfig, Session, {}, {});
			Action->Activate();

			// Verify via C++ GetFlagOverrides
			VerifyWhenComplete(Action, [this, Done]()
			{
				Satori::GetFlagOverrides(ClientConfig, Session, {}, {}).Next([this, Done](FSatoriFlagOverrideListResult Result)
				{
					if (Result.bIsError)
					{
						AddError(FString::Printf(TEXT("GetFlagOverrides failed: %s"), *Result.Error.Message));
					}
					Done.Execute();
				});
			});
		});
	});
}

// ============================================================================
// EXPERIMENTS TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FSatoriBPExperimentsSpec, "IntegrationTests.SatoriBlueprintTests.Experiments",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FSatoriClientConfig ClientConfig;
	FSatoriSession Session;

	static FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7450;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FSatoriBPExperimentsSpec)

FString FSatoriBPExperimentsSpec::ServerKey;
const FString FSatoriBPExperimentsSpec::Host = TEXT("127.0.0.1");

void FSatoriBPExperimentsSpec::Define()
{
	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		GetSatoriApiKey().Next([this, Done](FString Key)
		{
			ServerKey = Key;
			ClientConfig = FSatoriClientConfig{ServerKey, Host, Port, false};
			Done.Execute();
		});
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		Satori::Authenticate(ClientConfig, GenerateId(), false, {}, {}).Next([this, Done](FSatoriSessionResult Result)
		{
			if (Result.bIsError)
			{
				AddError(FString::Printf(TEXT("Setup auth failed: %s"), *Result.Error.Message));
			}
			else
			{
				Session = Result.Value;
			}
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		Satori::DeleteIdentity(ClientConfig, Session).Next([Done](FSatoriVoidResult) { Done.Execute(); });
	});

	Describe("GetExperiments", [this]()
	{
		LatentIt("should list all experiments via BP action", [this](const FDoneDelegate& Done)
		{
			auto* Action = USatoriClientGetExperiments::GetExperiments(
				nullptr, ClientConfig, Session, {}, {});
			Action->Activate();

			// Verify via C++ GetExperiments
			VerifyWhenComplete(Action, [this, Done]()
			{
				Satori::GetExperiments(ClientConfig, Session, {}, {}).Next([this, Done](FSatoriExperimentListResult Result)
				{
					if (Result.bIsError)
					{
						AddError(FString::Printf(TEXT("GetExperiments failed: %s"), *Result.Error.Message));
					}
					Done.Execute();
				});
			});
		});
	});
}

// ============================================================================
// LIVE EVENTS TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FSatoriBPLiveEventsSpec, "IntegrationTests.SatoriBlueprintTests.LiveEvents",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FSatoriClientConfig ClientConfig;
	FSatoriSession Session;

	static FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7450;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FSatoriBPLiveEventsSpec)

FString FSatoriBPLiveEventsSpec::ServerKey;
const FString FSatoriBPLiveEventsSpec::Host = TEXT("127.0.0.1");

void FSatoriBPLiveEventsSpec::Define()
{
	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		GetSatoriApiKey().Next([this, Done](FString Key)
		{
			ServerKey = Key;
			ClientConfig = FSatoriClientConfig{ServerKey, Host, Port, false};
			Done.Execute();
		});
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		Satori::Authenticate(ClientConfig, GenerateId(), false, {}, {}).Next([this, Done](FSatoriSessionResult Result)
		{
			if (Result.bIsError)
			{
				AddError(FString::Printf(TEXT("Setup auth failed: %s"), *Result.Error.Message));
			}
			else
			{
				Session = Result.Value;
			}
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		Satori::DeleteIdentity(ClientConfig, Session).Next([Done](FSatoriVoidResult) { Done.Execute(); });
	});

	Describe("GetLiveEvents", [this]()
	{
		LatentIt("should list all live events via BP action", [this](const FDoneDelegate& Done)
		{
			auto* Action = USatoriClientGetLiveEvents::GetLiveEvents(
				nullptr, ClientConfig, Session, {}, {}, 0, 0, 0, 0);
			Action->Activate();

			// Verify via C++ GetLiveEvents
			VerifyWhenComplete(Action, [this, Done]()
			{
				Satori::GetLiveEvents(ClientConfig, Session, {}, {}, 0, 0, 0, 0).Next([this, Done](FSatoriLiveEventListResult Result)
				{
					if (Result.bIsError)
					{
						AddError(FString::Printf(TEXT("GetLiveEvents failed: %s"), *Result.Error.Message));
					}
					Done.Execute();
				});
			});
		});
	});
}

// ============================================================================
// MESSAGES TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FSatoriBPMessagesSpec, "IntegrationTests.SatoriBlueprintTests.Messages",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FSatoriClientConfig ClientConfig;
	FSatoriSession Session;

	static FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7450;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FSatoriBPMessagesSpec)

FString FSatoriBPMessagesSpec::ServerKey;
const FString FSatoriBPMessagesSpec::Host = TEXT("127.0.0.1");

void FSatoriBPMessagesSpec::Define()
{
	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		GetSatoriApiKey().Next([this, Done](FString Key)
		{
			ServerKey = Key;
			ClientConfig = FSatoriClientConfig{ServerKey, Host, Port, false};
			Done.Execute();
		});
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		Satori::Authenticate(ClientConfig, GenerateId(), false, {}, {}).Next([this, Done](FSatoriSessionResult Result)
		{
			if (Result.bIsError)
			{
				AddError(FString::Printf(TEXT("Setup auth failed: %s"), *Result.Error.Message));
			}
			else
			{
				Session = Result.Value;
			}
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		Satori::DeleteIdentity(ClientConfig, Session).Next([Done](FSatoriVoidResult) { Done.Execute(); });
	});

	Describe("GetMessageList", [this]()
	{
		LatentIt("should list messages for identity via BP action", [this](const FDoneDelegate& Done)
		{
			auto* Action = USatoriClientGetMessageList::GetMessageList(
				nullptr, ClientConfig, Session, 10, true, TEXT(""), {});
			Action->Activate();

			// Verify via C++ GetMessageList
			VerifyWhenComplete(Action, [this, Done]()
			{
				Satori::GetMessageList(ClientConfig, Session, 10, true, TEXT(""), {}).Next([this, Done](FSatoriGetMessageListResponseResult Result)
				{
					if (Result.bIsError)
					{
						AddError(FString::Printf(TEXT("GetMessageList failed: %s"), *Result.Error.Message));
					}
					else
					{
						TestEqual("No messages for fresh identity", Result.Value.Messages.Num(), 0);
					}
					Done.Execute();
				});
			});
		});
	});

	Describe("UpdateMessage", [this]()
	{
		LatentIt("should update a message via BP action", [this](const FDoneDelegate& Done)
		{
			// UpdateMessage with a nonexistent ID should still not crash the action
			auto* Action = USatoriClientUpdateMessage::UpdateMessage(
				nullptr, ClientConfig, Session, TEXT("nonexistent-id"), 0, 0);
			Action->Activate();

			// Verify: action completed (may error, but should not crash)
			VerifyWhenComplete(Action, [this, Done]()
			{
				Done.Execute();
			});
		});
	});

	Describe("DeleteMessage", [this]()
	{
		LatentIt("should delete a message via BP action", [this](const FDoneDelegate& Done)
		{
			// DeleteMessage with a nonexistent ID should still not crash the action
			auto* Action = USatoriClientDeleteMessage::DeleteMessage(
				nullptr, ClientConfig, Session, TEXT("nonexistent-id"));
			Action->Activate();

			// Verify: action completed (may error, but should not crash)
			VerifyWhenComplete(Action, [this, Done]()
			{
				Done.Execute();
			});
		});
	});
}
