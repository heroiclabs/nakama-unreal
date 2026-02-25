/**
 * Satori Blueprint Async Action Test Suite
 *
 * Tests for SatoriBlueprints module UBlueprintAsyncActionBase subclasses.
 * Each test fires a BP async action, then verifies the server-side effect
 * through the C++ client (which supports lambda callbacks natively).
 *
 * Mirrors the Nakama BP test pattern from NakamaBlueprintTests.cpp.
 */

#include "Misc/AutomationTest.h"
#include "SatoriApi.h"
#include "SatoriClientBlueprintLibrary.h"
#include "Misc/Guid.h"
#include "Containers/Ticker.h"

// Helper: poll until the BP action's async work completes, then run verification.
// Actions self-root in Activate() and self-unroot when done, so IsRooted()==false
// signals completion. Polls every tick (~0s delay) for minimal latency.
static void VerifyWhenComplete(UBlueprintAsyncActionBase* Action, TFunction<void()> VerifyFunc)
{
	TWeakObjectPtr<UBlueprintAsyncActionBase> WeakAction(Action);

	FTSTicker::GetCoreTicker().AddTicker(
		FTickerDelegate::CreateLambda([WeakAction, VerifyFunc = MoveTemp(VerifyFunc)](float) -> bool
		{
			if (WeakAction.IsValid() && WeakAction->IsRooted())
			{
				return true; // keep ticking
			}
			VerifyFunc();
			return false;
		}),
		0.0f
	);
}

// ============================================================================
// HEALTHCHECK TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FSatoriBPHealthcheckSpec, "IntegrationTests.SatoriBlueprint.Healthcheck",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FSatoriSession Session;
	FSatoriClientConfig ClientConfig;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7450;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FSatoriBPHealthcheckSpec)

const FString FSatoriBPHealthcheckSpec::ServerKey = TEXT("defaultkey");
const FString FSatoriBPHealthcheckSpec::Host = TEXT("127.0.0.1");

void FSatoriBPHealthcheckSpec::Define()
{
	BeforeEach([this]()
	{
		ClientConfig = FSatoriClientConfig{ServerKey, Host, Port, false};
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		SatoriApi::Authenticate(ClientConfig, GenerateId(), false, {}, {},
			[this, Done](const FSatoriSession& Result)
			{
				Session = Result;
				Done.Execute();
			},
			[this, Done](const FSatoriError& Error)
			{
				AddError(FString::Printf(TEXT("Setup auth failed: %s"), *Error.Message));
				Done.Execute();
			}
		);
	});

	Describe("Healthcheck", [this]()
	{
		LatentIt("should pass healthcheck", [this](const FDoneDelegate& Done)
		{
			auto* Action = USatoriClientHealthcheck::Healthcheck(nullptr, ClientConfig, Session);
			Action->Activate();

			VerifyWhenComplete(Action, [this, Done]()
			{
				SatoriApi::Healthcheck(ClientConfig, Session,
					[Done]() { Done.Execute(); },
					[this, Done](const FSatoriError& Error)
					{
						AddError(FString::Printf(TEXT("Healthcheck failed: %s"), *Error.Message));
						Done.Execute();
					}
				);
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
				SatoriApi::Readycheck(ClientConfig, Session,
					[Done]() { Done.Execute(); },
					[this, Done](const FSatoriError& Error)
					{
						AddError(FString::Printf(TEXT("Readycheck failed: %s"), *Error.Message));
						Done.Execute();
					}
				);
			});
		});
	});
}

// ============================================================================
// AUTHENTICATION TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FSatoriBPAuthSpec, "IntegrationTests.SatoriBlueprint.Auth",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FSatoriClientConfig ClientConfig;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7450;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FSatoriBPAuthSpec)

const FString FSatoriBPAuthSpec::ServerKey = TEXT("defaultkey");
const FString FSatoriBPAuthSpec::Host = TEXT("127.0.0.1");

void FSatoriBPAuthSpec::Define()
{
	BeforeEach([this]()
	{
		ClientConfig = FSatoriClientConfig{ServerKey, Host, Port, false};
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
				SatoriApi::Authenticate(ClientConfig, Id, false, {}, {},
					[this, Done](const FSatoriSession& Result)
					{
						TestTrue("Session has token", !Result.Token.IsEmpty());
						Done.Execute();
					},
					[this, Done](const FSatoriError& Error)
					{
						AddError(FString::Printf(TEXT("Re-auth failed: %s"), *Error.Message));
						Done.Execute();
					}
				);
			});
		});
	});

	Describe("AuthenticateRefresh", [this]()
	{
		LatentIt("should refresh a session via BP action", [this](const FDoneDelegate& Done)
		{
			// Setup: authenticate via C++ to get a refresh token
			SatoriApi::Authenticate(ClientConfig, GenerateId(), false, {}, {},
				[this, Done](const FSatoriSession& Result)
				{
					auto* Action = USatoriClientAuthenticateRefresh::AuthenticateRefresh(
						nullptr, ClientConfig, Result.RefreshToken);
					Action->Activate();

					// Verify: server still responds to healthcheck
					VerifyWhenComplete(Action, [this, Done]()
					{
						SatoriApi::Healthcheck(ClientConfig, FSatoriSession{},
							[Done]() { Done.Execute(); },
							[this, Done](const FSatoriError& Error)
							{
								AddError(FString::Printf(TEXT("Healthcheck failed: %s"), *Error.Message));
								Done.Execute();
							}
						);
					});
				},
				[this, Done](const FSatoriError& Error)
				{
					AddError(FString::Printf(TEXT("Setup auth failed: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});
	});

	Describe("AuthenticateLogout", [this]()
	{
		LatentIt("should logout a session via BP action", [this](const FDoneDelegate& Done)
		{
			// Setup: authenticate via C++ to get tokens
			SatoriApi::Authenticate(ClientConfig, GenerateId(), false, {}, {},
				[this, Done](const FSatoriSession& Result)
				{
					auto* Action = USatoriClientAuthenticateLogout::AuthenticateLogout(
						nullptr, ClientConfig, Result.Token, Result.RefreshToken);
					Action->Activate();

					// Verify: action completed; server still responds
					VerifyWhenComplete(Action, [this, Done]()
					{
						SatoriApi::Healthcheck(ClientConfig, FSatoriSession{},
							[Done]() { Done.Execute(); },
							[this, Done](const FSatoriError& Error)
							{
								AddError(FString::Printf(TEXT("Healthcheck failed: %s"), *Error.Message));
								Done.Execute();
							}
						);
					});
				},
				[this, Done](const FSatoriError& Error)
				{
					AddError(FString::Printf(TEXT("Setup auth failed: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});
	});
}

// ============================================================================
// IDENTITY TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FSatoriBPIdentitySpec, "IntegrationTests.SatoriBlueprint.Identity",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FSatoriClientConfig ClientConfig;
	FSatoriSession Session;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7450;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FSatoriBPIdentitySpec)

const FString FSatoriBPIdentitySpec::ServerKey = TEXT("defaultkey");
const FString FSatoriBPIdentitySpec::Host = TEXT("127.0.0.1");

void FSatoriBPIdentitySpec::Define()
{
	BeforeEach([this]()
	{
		ClientConfig = FSatoriClientConfig{ServerKey, Host, Port, false};
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		SatoriApi::Authenticate(ClientConfig, GenerateId(), false, {}, {},
			[this, Done](const FSatoriSession& Result)
			{
				Session = Result;
				Done.Execute();
			},
			[this, Done](const FSatoriError& Error)
			{
				AddError(FString::Printf(TEXT("Setup auth failed: %s"), *Error.Message));
				Done.Execute();
			}
		);
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

BEGIN_DEFINE_SPEC(FSatoriBPPropertiesSpec, "IntegrationTests.SatoriBlueprint.Properties",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FSatoriClientConfig ClientConfig;
	FSatoriSession Session;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7450;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FSatoriBPPropertiesSpec)

const FString FSatoriBPPropertiesSpec::ServerKey = TEXT("defaultkey");
const FString FSatoriBPPropertiesSpec::Host = TEXT("127.0.0.1");

void FSatoriBPPropertiesSpec::Define()
{
	BeforeEach([this]()
	{
		ClientConfig = FSatoriClientConfig{ServerKey, Host, Port, false};
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		SatoriApi::Authenticate(ClientConfig, GenerateId(), false, {}, {},
			[this, Done](const FSatoriSession& Result)
			{
				Session = Result;
				Done.Execute();
			},
			[this, Done](const FSatoriError& Error)
			{
				AddError(FString::Printf(TEXT("Setup auth failed: %s"), *Error.Message));
				Done.Execute();
			}
		);
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
				SatoriApi::ListProperties(ClientConfig, Session,
					[this, Done](const FSatoriProperties&)
					{
						Done.Execute();
					},
					[this, Done](const FSatoriError& Error)
					{
						AddError(FString::Printf(TEXT("ListProperties failed: %s"), *Error.Message));
						Done.Execute();
					}
				);
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
				SatoriApi::ListProperties(ClientConfig, Session,
					[this, Done](const FSatoriProperties& Props)
					{
						TestEqual("Custom level", Props.Custom.FindRef(TEXT("level")), TEXT("5"));
						Done.Execute();
					},
					[this, Done](const FSatoriError& Error)
					{
						AddError(FString::Printf(TEXT("ListProperties failed: %s"), *Error.Message));
						Done.Execute();
					}
				);
			});
		});
	});
}

// ============================================================================
// EVENT TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FSatoriBPEventSpec, "IntegrationTests.SatoriBlueprint.Event",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FSatoriClientConfig ClientConfig;
	FSatoriSession Session;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7450;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FSatoriBPEventSpec)

const FString FSatoriBPEventSpec::ServerKey = TEXT("defaultkey");
const FString FSatoriBPEventSpec::Host = TEXT("127.0.0.1");

void FSatoriBPEventSpec::Define()
{
	BeforeEach([this]()
	{
		ClientConfig = FSatoriClientConfig{ServerKey, Host, Port, false};
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		SatoriApi::Authenticate(ClientConfig, GenerateId(), false, {}, {},
			[this, Done](const FSatoriSession& Result)
			{
				Session = Result;
				Done.Execute();
			},
			[this, Done](const FSatoriError& Error)
			{
				AddError(FString::Printf(TEXT("Setup auth failed: %s"), *Error.Message));
				Done.Execute();
			}
		);
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
				SatoriApi::Healthcheck(ClientConfig, Session,
					[Done]() { Done.Execute(); },
					[this, Done](const FSatoriError& Error)
					{
						AddError(FString::Printf(TEXT("Healthcheck failed: %s"), *Error.Message));
						Done.Execute();
					}
				);
			});
		});
	});
}

// ============================================================================
// FLAGS TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FSatoriBPFlagsSpec, "IntegrationTests.SatoriBlueprint.Flags",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FSatoriClientConfig ClientConfig;
	FSatoriSession Session;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7450;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FSatoriBPFlagsSpec)

const FString FSatoriBPFlagsSpec::ServerKey = TEXT("defaultkey");
const FString FSatoriBPFlagsSpec::Host = TEXT("127.0.0.1");

void FSatoriBPFlagsSpec::Define()
{
	BeforeEach([this]()
	{
		ClientConfig = FSatoriClientConfig{ServerKey, Host, Port, false};
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		SatoriApi::Authenticate(ClientConfig, GenerateId(), false, {}, {},
			[this, Done](const FSatoriSession& Result)
			{
				Session = Result;
				Done.Execute();
			},
			[this, Done](const FSatoriError& Error)
			{
				AddError(FString::Printf(TEXT("Setup auth failed: %s"), *Error.Message));
				Done.Execute();
			}
		);
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
				SatoriApi::GetFlags(ClientConfig, Session, {}, {},
					[this, Done](const FSatoriFlagList&)
					{
						Done.Execute();
					},
					[this, Done](const FSatoriError& Error)
					{
						AddError(FString::Printf(TEXT("GetFlags failed: %s"), *Error.Message));
						Done.Execute();
					}
				);
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
				SatoriApi::GetFlagOverrides(ClientConfig, Session, {}, {},
					[this, Done](const FSatoriFlagOverrideList&)
					{
						Done.Execute();
					},
					[this, Done](const FSatoriError& Error)
					{
						AddError(FString::Printf(TEXT("GetFlagOverrides failed: %s"), *Error.Message));
						Done.Execute();
					}
				);
			});
		});
	});
}

// ============================================================================
// EXPERIMENTS TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FSatoriBPExperimentsSpec, "IntegrationTests.SatoriBlueprint.Experiments",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FSatoriClientConfig ClientConfig;
	FSatoriSession Session;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7450;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FSatoriBPExperimentsSpec)

const FString FSatoriBPExperimentsSpec::ServerKey = TEXT("defaultkey");
const FString FSatoriBPExperimentsSpec::Host = TEXT("127.0.0.1");

void FSatoriBPExperimentsSpec::Define()
{
	BeforeEach([this]()
	{
		ClientConfig = FSatoriClientConfig{ServerKey, Host, Port, false};
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		SatoriApi::Authenticate(ClientConfig, GenerateId(), false, {}, {},
			[this, Done](const FSatoriSession& Result)
			{
				Session = Result;
				Done.Execute();
			},
			[this, Done](const FSatoriError& Error)
			{
				AddError(FString::Printf(TEXT("Setup auth failed: %s"), *Error.Message));
				Done.Execute();
			}
		);
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
				SatoriApi::GetExperiments(ClientConfig, Session, {}, {},
					[this, Done](const FSatoriExperimentList&)
					{
						Done.Execute();
					},
					[this, Done](const FSatoriError& Error)
					{
						AddError(FString::Printf(TEXT("GetExperiments failed: %s"), *Error.Message));
						Done.Execute();
					}
				);
			});
		});
	});
}

// ============================================================================
// LIVE EVENTS TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FSatoriBPLiveEventsSpec, "IntegrationTests.SatoriBlueprint.LiveEvents",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FSatoriClientConfig ClientConfig;
	FSatoriSession Session;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7450;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FSatoriBPLiveEventsSpec)

const FString FSatoriBPLiveEventsSpec::ServerKey = TEXT("defaultkey");
const FString FSatoriBPLiveEventsSpec::Host = TEXT("127.0.0.1");

void FSatoriBPLiveEventsSpec::Define()
{
	BeforeEach([this]()
	{
		ClientConfig = FSatoriClientConfig{ServerKey, Host, Port, false};
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		SatoriApi::Authenticate(ClientConfig, GenerateId(), false, {}, {},
			[this, Done](const FSatoriSession& Result)
			{
				Session = Result;
				Done.Execute();
			},
			[this, Done](const FSatoriError& Error)
			{
				AddError(FString::Printf(TEXT("Setup auth failed: %s"), *Error.Message));
				Done.Execute();
			}
		);
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
				SatoriApi::GetLiveEvents(ClientConfig, Session, {}, {}, 0, 0, 0, 0,
					[this, Done](const FSatoriLiveEventList&)
					{
						Done.Execute();
					},
					[this, Done](const FSatoriError& Error)
					{
						AddError(FString::Printf(TEXT("GetLiveEvents failed: %s"), *Error.Message));
						Done.Execute();
					}
				);
			});
		});
	});
}

// ============================================================================
// MESSAGES TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FSatoriBPMessagesSpec, "IntegrationTests.SatoriBlueprint.Messages",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FSatoriClientConfig ClientConfig;
	FSatoriSession Session;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7450;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FSatoriBPMessagesSpec)

const FString FSatoriBPMessagesSpec::ServerKey = TEXT("defaultkey");
const FString FSatoriBPMessagesSpec::Host = TEXT("127.0.0.1");

void FSatoriBPMessagesSpec::Define()
{
	BeforeEach([this]()
	{
		ClientConfig = FSatoriClientConfig{ServerKey, Host, Port, false};
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		SatoriApi::Authenticate(ClientConfig, GenerateId(), false, {}, {},
			[this, Done](const FSatoriSession& Result)
			{
				Session = Result;
				Done.Execute();
			},
			[this, Done](const FSatoriError& Error)
			{
				AddError(FString::Printf(TEXT("Setup auth failed: %s"), *Error.Message));
				Done.Execute();
			}
		);
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
				SatoriApi::GetMessageList(ClientConfig, Session, 10, true, TEXT(""), {},
					[this, Done](const FSatoriGetMessageListResponse& Result)
					{
						TestEqual("No messages for fresh identity", Result.Messages.Num(), 0);
						Done.Execute();
					},
					[this, Done](const FSatoriError& Error)
					{
						AddError(FString::Printf(TEXT("GetMessageList failed: %s"), *Error.Message));
						Done.Execute();
					}
				);
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
