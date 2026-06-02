/**
 * Object Ownership Tests
 *
 * Demonstrates bug: factory functions in NakamaClientBlueprintLibrary.cpp and
 * SatoriClientBlueprintLibrary.cpp call NewObject<T>() without an Outer, so
 * created async actions are stranded in GetTransientPackage() instead of being
 * owned by the WorldContextObject.
 *
 * All tests in this file are EXPECTED TO FAIL until the bug is fixed.
 * Fix: change NewObject<T>() -> NewObject<T>(WorldContextObject) in each factory.
 */

#include "Misc/AutomationTest.h"
#include "NakamaClientBlueprintLibrary.h"
#include "SatoriClientBlueprintLibrary.h"
#include "UObject/Package.h"
#include "Engine/Engine.h"

// ============================================================================
// Nakama — async action outer must be WorldContextObject, not transient package
// ============================================================================

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FNakamaAsyncActionOuterTest,
	"IntegrationTests.ObjectOwnership.NakamaAsyncActionOuter",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter
)

bool FNakamaAsyncActionOuterTest::RunTest(const FString& Parameters)
{
	// GEngine is a concrete, always-available UObject that is never GetTransientPackage().
	// UObject itself is abstract in UE5.5+ and cannot be directly instantiated.
	UObject* WorldContext = GEngine;

	FNakamaClientConfig Client{TEXT("defaultkey"), TEXT("127.0.0.1"), 7350, false};
	FNakamaSession Session;

	// Create the action — do NOT call Activate() so no network I/O occurs.
	UNakamaClientHealthcheck* Action =
		UNakamaClientHealthcheck::Healthcheck(WorldContext, Client, Session);

	// BUG: NewObject<UNakamaClientHealthcheck>() in the factory passes no Outer,
	// so GetOuter() returns GetTransientPackage() instead of WorldContext.
	// This test FAILS until the factory is fixed.
	TestNotEqual(
		TEXT("[BUG] Nakama async action outer is the transient package; expected WorldContextObject"),
		Action->GetOuter(),
		static_cast<UObject*>(GetTransientPackage())
	);

	// Also verify we can walk up to the world context via the outer chain.
	// GetTypedOuter returns nullptr when the outer chain doesn't pass through WorldContext.
	bool bFoundWorldContext = false;
	UObject* Outer = Action->GetOuter();
	while (Outer)
	{
		if (Outer == WorldContext) { bFoundWorldContext = true; break; }
		Outer = Outer->GetOuter();
	}
	TestTrue(
		TEXT("[BUG] WorldContextObject not reachable through async action outer chain"),
		bFoundWorldContext
	);

	return true;
}

// ============================================================================
// Satori — same bug in SatoriClientBlueprintLibrary factory functions
// ============================================================================

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FSatoriAsyncActionOuterTest,
	"IntegrationTests.ObjectOwnership.SatoriAsyncActionOuter",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter
)

bool FSatoriAsyncActionOuterTest::RunTest(const FString& Parameters)
{
	UObject* WorldContext = GEngine;

	FSatoriClientConfig Client;
	Client.Host       = TEXT("127.0.0.1");
	Client.Port       = 7480;
	Client.ServerKey  = TEXT("defaultkey");
	Client.bUseSSL    = false;

	// Create the action — do NOT Activate().
	USatoriClientAuthenticate* Action =
		USatoriClientAuthenticate::Authenticate(WorldContext, Client, TEXT("test-id"), false, {}, {});

	// BUG: same pattern — no Outer passed to NewObject.
	TestNotEqual(
		TEXT("[BUG] Satori async action outer is the transient package; expected WorldContextObject"),
		Action->GetOuter(),
		static_cast<UObject*>(GetTransientPackage())
	);

	bool bFoundWorldContext = false;
	UObject* Outer = Action->GetOuter();
	while (Outer)
	{
		if (Outer == WorldContext) { bFoundWorldContext = true; break; }
		Outer = Outer->GetOuter();
	}
	TestTrue(
		TEXT("[BUG] WorldContextObject not reachable through Satori async action outer chain"),
		bFoundWorldContext
	);

	return true;
}
