/**
 * Future Threading Tests
 *
 * Demonstrates bug: TSatoriFuture terminal .Next() callbacks ran on the UE
 * background task thread pool instead of the game thread.
 *
 * Root cause (Satori.h, old TSatoriFuture:169-179): the terminal Next() overload
 * passed the user callback directly to UE::Tasks::Launch without any
 * AsyncTask(ENamedThreads::GameThread, ...) dispatch. Callers that touched
 * UObject*, fired delegates, or updated UI would therefore hit non-thread-safe
 * access and intermittent crashes.
 *
 * Fix: both TNakamaFuture and TSatoriFuture are now aliases for the shared
 * TAsyncFuture<> template (AsyncFuture.h / NakamaApi module), which dispatches
 * every user-visible callback — chaining and terminal — to the game thread.
 *
 * The Satori test below verifies the fix. The Nakama control test was already
 * passing before the consolidation.
 */

#include "Misc/AutomationTest.h"
#include "AsyncFuture.h"

// ============================================================================
// Satori: terminal .Next() must run on the game thread
// ============================================================================

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FSatoriTerminalNextOnGameThreadTest,
	"IntegrationTests.Threading.Satori.TerminalNextMustRunOnGameThread",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter
)

struct FSatoriThreadingTestResult
{
	bool bIsError = false;
};

bool FSatoriTerminalNextOnGameThreadTest::RunTest(const FString& Parameters)
{
	TSharedRef<TAtomic<bool>> bCallbackRanOnGameThread = MakeShared<TAtomic<bool>>(false);
	TSharedRef<TAtomic<bool>> bCallbackInvoked        = MakeShared<TAtomic<bool>>(false);

	MakeCompletedAsyncFuture(FSatoriThreadingTestResult{}).Next(
		[bCallbackRanOnGameThread, bCallbackInvoked](FSatoriThreadingTestResult)
		{
			bCallbackRanOnGameThread->Store(IsInGameThread());
			bCallbackInvoked->Store(true);
		});

	// Spin-wait up to 5 s, pumping the game-thread task queue each iteration
	// so the AsyncTask dispatch can actually execute.
	constexpr double TimeoutSeconds = 5.0;
	const double Deadline = FPlatformTime::Seconds() + TimeoutSeconds;
	while (!bCallbackInvoked->Load())
	{
		FTaskGraphInterface::Get().ProcessThreadUntilIdle(ENamedThreads::GameThread);
		if (FPlatformTime::Seconds() > Deadline)
		{
			AddError(TEXT("Timed out waiting for TSatoriFuture terminal .Next() callback"));
			return false;
		}
		FPlatformProcess::Sleep(0.01f);
	}

	TestTrue(
		TEXT("TSatoriFuture terminal .Next() callback must run on the game thread"),
		bCallbackRanOnGameThread->Load()
	);

	return true;
}

// ============================================================================
// Nakama: same guarantee, kept as a control / regression test
// ============================================================================

struct FNakamaThreadingTestResult
{
	bool bIsError = false;
};

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FNakamaTerminalNextOnGameThreadTest,
	"IntegrationTests.Threading.Nakama.TerminalNextMustRunOnGameThread",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter
)

bool FNakamaTerminalNextOnGameThreadTest::RunTest(const FString& Parameters)
{
	TSharedRef<TAtomic<bool>> bCallbackRanOnGameThread = MakeShared<TAtomic<bool>>(false);
	TSharedRef<TAtomic<bool>> bCallbackInvoked        = MakeShared<TAtomic<bool>>(false);

	MakeCompletedAsyncFuture(FNakamaThreadingTestResult{}).Next(
		[bCallbackRanOnGameThread, bCallbackInvoked](FNakamaThreadingTestResult)
		{
			bCallbackRanOnGameThread->Store(IsInGameThread());
			bCallbackInvoked->Store(true);
		});

	constexpr double TimeoutSeconds = 5.0;
	const double Deadline = FPlatformTime::Seconds() + TimeoutSeconds;
	while (!bCallbackInvoked->Load())
	{
		FTaskGraphInterface::Get().ProcessThreadUntilIdle(ENamedThreads::GameThread);
		if (FPlatformTime::Seconds() > Deadline)
		{
			AddError(TEXT("Timed out waiting for TNakamaFuture terminal .Next() callback"));
			return false;
		}
		FPlatformProcess::Sleep(0.01f);
	}

	TestTrue(
		TEXT("TNakamaFuture terminal .Next() callback must run on the game thread"),
		bCallbackRanOnGameThread->Load()
	);

	return true;
}
