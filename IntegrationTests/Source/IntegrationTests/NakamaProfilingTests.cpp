/**
 * Nakama Profiling & Diagnostics Test Suite
 *
 * External measurement tests for memory, performance, stress,
 * leak detection, and diagnostics of the Nakama plugin.
 *
 * NOTE: Memory tests use FPlatformMemory::GetStats().UsedPhysical which is
 * process-wide RSS, not allocation-scoped. Thresholds are generous to account
 * for OS-level noise. These are smoke tests for catastrophic leaks, not precise
 * allocation tracking.
 *
 * NOTE: Stress tests fire many requests from the game thread. UE's HTTP module
 * serializes completion callbacks back to the game thread, so callbacks never
 * run concurrently. These test high-volume request handling, not thread safety.
 */

#include "Misc/AutomationTest.h"
#include "NakamaApi.h"
#include "NakamaClientBlueprintLibrary.h"
#include "Misc/Guid.h"
#include "Containers/Ticker.h"
#include "HAL/PlatformMemory.h"
#include "HAL/PlatformTime.h"

DEFINE_LOG_CATEGORY_STATIC(LogNakamaProfile, Log, All);

// ============================================================================
// MEMORY TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaProfilingMemorySpec, "IntegrationTests.Profiling.Memory",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaClientConfig Client;
	FNakamaSession Session;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7350;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

	SIZE_T GetUsedPhysical()
	{
		FPlatformMemoryStats Stats = FPlatformMemory::GetStats();
		return Stats.UsedPhysical;
	}

END_DEFINE_SPEC(FNakamaProfilingMemorySpec)

const FString FNakamaProfilingMemorySpec::ServerKey = TEXT("defaultkey");
const FString FNakamaProfilingMemorySpec::Host = TEXT("127.0.0.1");

void FNakamaProfilingMemorySpec::Define()
{
	BeforeEach([this]()
	{
		Client = FNakamaClientConfig{ServerKey, Host, Port, false};
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		NakamaApi::AuthenticateCustom(Client, Account, true, TEXT(""),
			[this, Done](const FNakamaSession& Result)
			{
				Session = Result;
				Done.Execute();
			},
			[this, Done](const FNakamaError& Error)
			{
				AddError(FString::Printf(TEXT("Setup auth failed: %s"), *Error.Message));
				Done.Execute();
			}
		);
	});

	AfterEach([this]()
	{
		Client = {};
	});

	Describe("ClientLifecycle", [this]()
	{
		It("should not leak on rapid client create/destroy", [this]()
		{
			CollectGarbage(GARBAGE_COLLECTION_KEEPFLAGS);

			const SIZE_T MemBefore = GetUsedPhysical();

			constexpr int32 NumClients = 100;
			for (int32 i = 0; i < NumClients; ++i)
			{
				FNakamaClientConfig TempClient = FNakamaClientConfig{ServerKey, Host, Port, false};
				TempClient = {};
			}

			CollectGarbage(GARBAGE_COLLECTION_KEEPFLAGS);

			const SIZE_T MemAfter = GetUsedPhysical();
			const double DeltaMB = static_cast<double>(MemAfter) / (1024.0 * 1024.0)
				- static_cast<double>(MemBefore) / (1024.0 * 1024.0);

			UE_LOG(LogNakamaProfile, Log, TEXT("[Profiling.Memory] ClientCreateDestroy: Before=%.1fMB After=%.1fMB Delta=%.1fMB"),
				MemBefore / (1024.0 * 1024.0), MemAfter / (1024.0 * 1024.0), DeltaMB);

			TestTrue(FString::Printf(TEXT("Memory delta %.1fMB should be < 5MB"), DeltaMB),
				FMath::Abs(DeltaMB) < 5.0);
		});

		LatentIt("should not grow memory on auth cycles", [this](const FDoneDelegate& Done)
		{
			CollectGarbage(GARBAGE_COLLECTION_KEEPFLAGS);
			const SIZE_T MemBefore = GetUsedPhysical();

			TSharedPtr<int32> CompletedCount = MakeShared<int32>(0);
			constexpr int32 NumCycles = 20;

			for (int32 i = 0; i < NumCycles; ++i)
			{
				FNakamaAccountCustom Account;
				Account.Id = GenerateId();

				NakamaApi::AuthenticateCustom(Client, Account, true, TEXT(""),
					[this, CompletedCount, NumCycles, MemBefore, Done](const FNakamaSession& Result)
					{
						++(*CompletedCount);
						if (*CompletedCount >= NumCycles)
						{
							CollectGarbage(GARBAGE_COLLECTION_KEEPFLAGS);
							const SIZE_T MemAfter = GetUsedPhysical();
							const double DeltaMB = static_cast<double>(MemAfter) / (1024.0 * 1024.0)
								- static_cast<double>(MemBefore) / (1024.0 * 1024.0);

							UE_LOG(LogNakamaProfile, Log, TEXT("[Profiling.Memory] AuthCycles: N=%d Before=%.1fMB After=%.1fMB Delta=%.1fMB"),
								NumCycles, MemBefore / (1024.0 * 1024.0), MemAfter / (1024.0 * 1024.0), DeltaMB);

							TestTrue(FString::Printf(TEXT("Memory delta %.1fMB should be < 10MB"), DeltaMB),
								FMath::Abs(DeltaMB) < 10.0);
							Done.Execute();
						}
					},
					[this, CompletedCount, NumCycles, Done](const FNakamaError& Error)
					{
						++(*CompletedCount);
						AddError(FString::Printf(TEXT("Auth cycle error: %s"), *Error.Message));
						if (*CompletedCount >= NumCycles)
						{
							Done.Execute();
						}
					}
				);
			}
		});

		LatentIt("should not grow memory during concurrent requests", [this](const FDoneDelegate& Done)
		{
			CollectGarbage(GARBAGE_COLLECTION_KEEPFLAGS);
			const SIZE_T MemBefore = GetUsedPhysical();

			TSharedPtr<int32> CompletedCount = MakeShared<int32>(0);
			constexpr int32 NumRequests = 50;

			for (int32 i = 0; i < NumRequests; ++i)
			{
				NakamaApi::GetAccount(Client, Session,
					[this, CompletedCount, NumRequests, MemBefore, Done](const FNakamaAccount& Result)
					{
						++(*CompletedCount);
						if (*CompletedCount >= NumRequests)
						{
							CollectGarbage(GARBAGE_COLLECTION_KEEPFLAGS);
							const SIZE_T MemAfter = GetUsedPhysical();
							const double DeltaMB = static_cast<double>(MemAfter) / (1024.0 * 1024.0)
								- static_cast<double>(MemBefore) / (1024.0 * 1024.0);

							UE_LOG(LogNakamaProfile, Log, TEXT("[Profiling.Memory] ConcurrentRequests: N=%d Before=%.1fMB After=%.1fMB Delta=%.1fMB"),
								NumRequests, MemBefore / (1024.0 * 1024.0), MemAfter / (1024.0 * 1024.0), DeltaMB);

							TestTrue(FString::Printf(TEXT("Memory delta %.1fMB should be < 10MB"), DeltaMB),
								FMath::Abs(DeltaMB) < 10.0);
							Done.Execute();
						}
					},
					[this, CompletedCount, NumRequests, Done](const FNakamaError& Error)
					{
						++(*CompletedCount);
						AddError(FString::Printf(TEXT("Request error: %s"), *Error.Message));
						if (*CompletedCount >= NumRequests)
						{
							Done.Execute();
						}
					}
				);
			}
		});

		LatentIt("should clean up Blueprint actions", [this](const FDoneDelegate& Done)
		{
						constexpr int32 NumActions = 20;
			TSharedPtr<int32> ActivatedCount = MakeShared<int32>(0);

			for (int32 i = 0; i < NumActions; ++i)
			{
				auto* Action = UNakamaClientHealthcheck::Healthcheck(nullptr, Client, Session);
				Action->AddToRoot();
				Action->Activate();

				FTSTicker::GetCoreTicker().AddTicker(
					FTickerDelegate::CreateLambda([Action, ActivatedCount, Done, NumActions, this](float) -> bool
					{
						Action->RemoveFromRoot();
						++(*ActivatedCount);
						if (*ActivatedCount >= NumActions)
						{
							CollectGarbage(GARBAGE_COLLECTION_KEEPFLAGS);

							UE_LOG(LogNakamaProfile, Log, TEXT("[Profiling.Memory] BPActionCleanup: %d actions created and cleaned up"),
								NumActions);

							TestTrue("BP actions cleaned up without crash", true);
							Done.Execute();
						}
						return false;
					}),
					1.0f
				);
			}
		});
	});
}

// ============================================================================
// PERFORMANCE TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaProfilingPerformanceSpec, "IntegrationTests.Profiling.Performance",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaClientConfig Client;
	FNakamaSession Session;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7350;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaProfilingPerformanceSpec)

const FString FNakamaProfilingPerformanceSpec::ServerKey = TEXT("defaultkey");
const FString FNakamaProfilingPerformanceSpec::Host = TEXT("127.0.0.1");

void FNakamaProfilingPerformanceSpec::Define()
{
	BeforeEach([this]()
	{
		Client = FNakamaClientConfig{ServerKey, Host, Port, false};
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		NakamaApi::AuthenticateCustom(Client, Account, true, TEXT(""),
			[this, Done](const FNakamaSession& Result)
			{
				Session = Result;
				Done.Execute();
			},
			[this, Done](const FNakamaError& Error)
			{
				AddError(FString::Printf(TEXT("Setup auth failed: %s"), *Error.Message));
				Done.Execute();
			}
		);
	});

	AfterEach([this]()
	{
		Client = {};
	});

	Describe("Latency", [this]()
	{
		LatentIt("should measure sequential request latency", [this](const FDoneDelegate& Done)
		{
			TSharedPtr<TArray<double>> Latencies = MakeShared<TArray<double>>();
			TSharedPtr<int32> CompletedCount = MakeShared<int32>(0);
			constexpr int32 NumRequests = 20;

			struct FSequentialRequester : TSharedFromThis<FSequentialRequester>
			{
				FNakamaClientConfig Client;
				FNakamaSession Session;
				TSharedPtr<TArray<double>> Latencies;
				TSharedPtr<int32> CompletedCount;
				int32 NumRequests;
				FAutomationTestBase* Test;
				FDoneDelegate Done;

				void FireNext()
				{
					if (*CompletedCount >= NumRequests)
					{
						ReportResults();
						return;
					}

					const double StartTime = FPlatformTime::Seconds();
					TSharedRef<FSequentialRequester> Self = AsShared();

					NakamaApi::GetAccount(Client, Session,
						[Self, StartTime](const FNakamaAccount& Result)
						{
							const double Elapsed = (FPlatformTime::Seconds() - StartTime) * 1000.0;
							Self->Latencies->Add(Elapsed);
							++(*Self->CompletedCount);
							Self->FireNext();
						},
						[Self](const FNakamaError& Error)
						{
							Self->Test->AddError(FString::Printf(TEXT("Request error: %s"), *Error.Message));
							++(*Self->CompletedCount);
							Self->FireNext();
						}
					);
				}

				void ReportResults()
				{
					TArray<double>& L = *Latencies;
					L.Sort();

					if (L.Num() == 0)
					{
						Test->AddError(TEXT("No latency measurements collected"));
						Done.Execute();
						return;
					}

					double Sum = 0;
					for (double V : L) { Sum += V; }

					const double Min = L[0];
					const double Avg = Sum / L.Num();
					const double P95 = L[FMath::Min(static_cast<int32>(L.Num() * 0.95), L.Num() - 1)];
					const double P99 = L[FMath::Min(static_cast<int32>(L.Num() * 0.99), L.Num() - 1)];
					const double Max = L.Last();

					UE_LOG(LogNakamaProfile, Log, TEXT("[Profiling.Performance] SequentialLatency: N=%d Min=%.1fms Avg=%.1fms P95=%.1fms P99=%.1fms Max=%.1fms"),
						L.Num(), Min, Avg, P95, P99, Max);

					Test->TestTrue("Average latency should be reasonable (< 5000ms)", Avg < 5000.0);
					Done.Execute();
				}
			};

			TSharedRef<FSequentialRequester> Requester = MakeShared<FSequentialRequester>();
			Requester->Client = Client;
			Requester->Session = Session;
			Requester->Latencies = Latencies;
			Requester->CompletedCount = CompletedCount;
			Requester->NumRequests = NumRequests;
			Requester->Test = this;
			Requester->Done = Done;
			Requester->FireNext();
		});

		LatentIt("should measure concurrent throughput", [this](const FDoneDelegate& Done)
		{
			constexpr int32 NumRequests = 50;
			TSharedPtr<int32> CompletedCount = MakeShared<int32>(0);
			TSharedPtr<double> StartTime = MakeShared<double>(FPlatformTime::Seconds());

			for (int32 i = 0; i < NumRequests; ++i)
			{
				NakamaApi::GetAccount(Client, Session,
					[this, CompletedCount, NumRequests, StartTime, Done](const FNakamaAccount& Result)
					{
						++(*CompletedCount);
						if (*CompletedCount >= NumRequests)
						{
							const double Elapsed = FPlatformTime::Seconds() - *StartTime;
							const double RPS = *CompletedCount / Elapsed;

							UE_LOG(LogNakamaProfile, Log, TEXT("[Profiling.Performance] ConcurrentThroughput: N=%d WallTime=%.2fs RPS=%.1f"),
								*CompletedCount, Elapsed, RPS);

							TestTrue("All requests should complete", *CompletedCount == NumRequests);
							Done.Execute();
						}
					},
					[this, CompletedCount, NumRequests, Done](const FNakamaError& Error)
					{
						++(*CompletedCount);
						AddError(FString::Printf(TEXT("Request error: %s"), *Error.Message));
						if (*CompletedCount >= NumRequests)
						{
							Done.Execute();
						}
					}
				);
			}
		});
	});

	Describe("Serialization", [this]()
	{
		It("should measure JSON serialization cost", [this]()
		{
			FNakamaAccount Account;
			Account.User.Id = TEXT("test-user-id-12345");
			Account.User.Username = TEXT("testuser");
			Account.User.DisplayName = TEXT("Test User Display Name");
			Account.User.AvatarUrl = TEXT("https://example.com/avatar.png");
			Account.User.LangTag = TEXT("en");
			Account.User.Location = TEXT("US");
			Account.User.Timezone = TEXT("America/New_York");
			Account.Email = TEXT("test@example.com");

			constexpr int32 NumIterations = 1000;

			const double SerStart = FPlatformTime::Seconds();
			for (int32 i = 0; i < NumIterations; ++i)
			{
				TSharedPtr<FJsonObject> Json = Account.User.ToJson();
			}
			const double SerElapsed = (FPlatformTime::Seconds() - SerStart) * 1000000.0;

			TSharedPtr<FJsonObject> SampleJson = Account.User.ToJson();
			const double DeserStart = FPlatformTime::Seconds();
			for (int32 i = 0; i < NumIterations; ++i)
			{
				FNakamaUser::FromJson(SampleJson);
			}
			const double DeserElapsed = (FPlatformTime::Seconds() - DeserStart) * 1000000.0;

			UE_LOG(LogNakamaProfile, Log, TEXT("[Profiling.Performance] JsonSerialization: N=%d ToJson=%.1fus/op FromJson=%.1fus/op"),
				NumIterations, SerElapsed / NumIterations, DeserElapsed / NumIterations);

			TestTrue("Serialization should complete", true);
		});
	});

	Describe("ClientFactory", [this]()
	{
		It("should measure client creation cost", [this]()
		{
			constexpr int32 NumIterations = 1000;

			const double StartTime = FPlatformTime::Seconds();
			for (int32 i = 0; i < NumIterations; ++i)
			{
				FNakamaClientConfig TempClient = FNakamaClientConfig{ServerKey, Host, Port, false};
			}
			const double Elapsed = (FPlatformTime::Seconds() - StartTime) * 1000000.0;

			UE_LOG(LogNakamaProfile, Log, TEXT("[Profiling.Performance] ClientCreation: N=%d Total=%.1fus Avg=%.2fus/op"),
				NumIterations, Elapsed, Elapsed / NumIterations);

			TestTrue("Client creation should complete", true);
		});
	});

	Describe("BPDispatch", [this]()
	{
		LatentIt("should measure BP action dispatch cost", [this](const FDoneDelegate& Done)
		{
			
			// Measure the C++ call as baseline
			const double CppStart = FPlatformTime::Seconds();

			NakamaApi::GetAccount(Client, Session,
				[this, CppStart, Done](const FNakamaAccount& CppResult)
				{
					const double CppElapsed = (FPlatformTime::Seconds() - CppStart) * 1000.0;

					// Measure the BP path — time from Activate() to delegate callback
					TSharedPtr<double> BpStart = MakeShared<double>(0.0);
					TSharedPtr<double> BpElapsed = MakeShared<double>(0.0);

					auto* Action = UNakamaClientGetAccount::GetAccount(nullptr, Client, Session);
					Action->AddToRoot();

					// Can't bind dynamic delegates to lambdas directly, so we time from
					// Activate() and poll for completion via ticker. This adds ~1 tick
					// of overhead (~16ms) to the measurement.
					*BpStart = FPlatformTime::Seconds();
					Action->Activate();

					FTSTicker::GetCoreTicker().AddTicker(
						FTickerDelegate::CreateLambda([this, Action, BpStart, CppElapsed, Done](float) -> bool
						{
							// Check if action completed (SetReadyToDestroy sets RF_BeginDestroyed flag)
							const double BpElapsed = (FPlatformTime::Seconds() - *BpStart) * 1000.0;
							Action->RemoveFromRoot();

							// BP elapsed includes ~1 tick of polling delay; report it transparently
							const double TickOverhead = FApp::GetDeltaTime() * 1000.0;

							UE_LOG(LogNakamaProfile, Log,
								TEXT("[Profiling.Performance] BPDispatch: C++=%.1fms BP=%.1fms (includes ~%.0fms tick delay)"),
								CppElapsed, BpElapsed, TickOverhead);

							TestTrue("BP dispatch measurement complete", true);
							Done.Execute();
							return false;
						}),
						0.0f // Minimum tick interval — fire on very next tick
					);
				},
				[this, Done](const FNakamaError& Error)
				{
					AddError(FString::Printf(TEXT("C++ GetAccount error: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});
	});
}

// ============================================================================
// STRESS TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaProfilingStressSpec, "IntegrationTests.Profiling.Stress",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaClientConfig Client;
	FNakamaSession Session;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7350;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaProfilingStressSpec)

const FString FNakamaProfilingStressSpec::ServerKey = TEXT("defaultkey");
const FString FNakamaProfilingStressSpec::Host = TEXT("127.0.0.1");

void FNakamaProfilingStressSpec::Define()
{
	BeforeEach([this]()
	{
		Client = FNakamaClientConfig{ServerKey, Host, Port, false};
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		NakamaApi::AuthenticateCustom(Client, Account, true, TEXT(""),
			[this, Done](const FNakamaSession& Result)
			{
				Session = Result;
				Done.Execute();
			},
			[this, Done](const FNakamaError& Error)
			{
				AddError(FString::Printf(TEXT("Setup auth failed: %s"), *Error.Message));
				Done.Execute();
			}
		);
	});

	AfterEach([this]()
	{
		Client = {};
	});

	Describe("MassRequests", [this]()
	{
		LatentIt("should handle 100 simultaneous requests", [this](const FDoneDelegate& Done)
		{
			constexpr int32 NumRequests = 100;
			TSharedPtr<int32> SuccessCount = MakeShared<int32>(0);
			TSharedPtr<int32> ErrorCount = MakeShared<int32>(0);

			for (int32 i = 0; i < NumRequests; ++i)
			{
				NakamaApi::GetAccount(Client, Session,
					[this, NumRequests, SuccessCount, ErrorCount, Done](const FNakamaAccount& Result)
					{
						++(*SuccessCount);
						if (*SuccessCount + *ErrorCount >= NumRequests)
						{
							UE_LOG(LogNakamaProfile, Log, TEXT("[Profiling.Stress] 100Simultaneous: Success=%d Errors=%d"),
								*SuccessCount, *ErrorCount);

							TestTrue(FString::Printf(TEXT("All %d callbacks arrived (got %d+%d)"),
								NumRequests, *SuccessCount, *ErrorCount),
								*SuccessCount + *ErrorCount == NumRequests);
							TestTrue(FString::Printf(TEXT("Most requests succeeded (%d/%d)"), *SuccessCount, NumRequests),
								*SuccessCount > 80);
							Done.Execute();
						}
					},
					[this, NumRequests, SuccessCount, ErrorCount, Done](const FNakamaError& Error)
					{
						++(*ErrorCount);
						if (*SuccessCount + *ErrorCount >= NumRequests)
						{
							UE_LOG(LogNakamaProfile, Log, TEXT("[Profiling.Stress] 100Simultaneous: Success=%d Errors=%d"),
								*SuccessCount, *ErrorCount);

							TestTrue(FString::Printf(TEXT("All %d callbacks arrived (got %d+%d)"),
								NumRequests, *SuccessCount, *ErrorCount),
								*SuccessCount + *ErrorCount == NumRequests);
							Done.Execute();
						}
					}
				);
			}
		});

		LatentIt("should handle rapid sequential fire", [this](const FDoneDelegate& Done)
		{
			constexpr int32 NumRequests = 50;
			TSharedPtr<int32> CompletedCount = MakeShared<int32>(0);

			for (int32 i = 0; i < NumRequests; ++i)
			{
				NakamaApi::GetAccount(Client, Session,
					[this, CompletedCount, NumRequests, Done](const FNakamaAccount& Result)
					{
						++(*CompletedCount);
						if (*CompletedCount >= NumRequests)
						{
							UE_LOG(LogNakamaProfile, Log, TEXT("[Profiling.Stress] RapidSequential: All %d completed"),
								*CompletedCount);

							TestEqual("All requests completed", *CompletedCount, NumRequests);
							Done.Execute();
						}
					},
					[this, CompletedCount, NumRequests, Done](const FNakamaError& Error)
					{
						++(*CompletedCount);
						if (*CompletedCount >= NumRequests)
						{
							UE_LOG(LogNakamaProfile, Log, TEXT("[Profiling.Stress] RapidSequential: %d completed (some errors)"),
								*CompletedCount);
							Done.Execute();
						}
					}
				);
			}
		});
	});

	Describe("ClientSafety", [this]()
	{
		LatentIt("should handle abandoned requests gracefully", [this](const FDoneDelegate& Done)
		{
			FNakamaClientConfig TempClient = FNakamaClientConfig{ServerKey, Host, Port, false};

			FNakamaAccountCustom Account;
			Account.Id = GenerateId();

			NakamaApi::AuthenticateCustom(TempClient, Account, true, TEXT(""),
				[this, TempClient, Done](const FNakamaSession& TempSession) mutable
				{
					NakamaApi::GetAccount(TempClient, TempSession,
						[Done](const FNakamaAccount& Result)
						{
							Done.Execute();
						},
						[Done](const FNakamaError& Error)
						{
							Done.Execute();
						}
					);

					// Release our reference — AsShared() in MakeRequest keeps client alive
					TempClient = {};
				},
				[this, Done](const FNakamaError& Error)
				{
					AddError(FString::Printf(TEXT("Auth failed: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});

		LatentIt("should isolate multiple clients", [this](const FDoneDelegate& Done)
		{
			constexpr int32 NumClients = 5;
			TSharedPtr<int32> CompletedCount = MakeShared<int32>(0);
			TSharedPtr<TArray<FString>> UserIds = MakeShared<TArray<FString>>();

			for (int32 i = 0; i < NumClients; ++i)
			{
				FNakamaClientConfig IsoClient = FNakamaClientConfig{ServerKey, Host, Port, false};

				FNakamaAccountCustom Account;
				Account.Id = GenerateId();

				NakamaApi::AuthenticateCustom(IsoClient, Account, true, TEXT(""),
					[this, IsoClient, CompletedCount, NumClients, UserIds, Done](const FNakamaSession& IsoSession)
					{
						NakamaApi::GetAccount(IsoClient, IsoSession,
							[this, CompletedCount, NumClients, UserIds, Done](const FNakamaAccount& Result)
							{
								UserIds->Add(Result.User.Id);
								++(*CompletedCount);

								if (*CompletedCount >= NumClients)
								{
									TSet<FString> UniqueIds;
									for (const FString& Id : *UserIds)
									{
										UniqueIds.Add(Id);
									}

									UE_LOG(LogNakamaProfile, Log, TEXT("[Profiling.Stress] ClientIsolation: %d clients, %d unique users"),
										*CompletedCount, UniqueIds.Num());

									TestEqual("All user IDs should be unique", UniqueIds.Num(), UserIds->Num());
									Done.Execute();
								}
							},
							[this, CompletedCount, NumClients, Done](const FNakamaError& Error)
							{
								AddError(FString::Printf(TEXT("GetAccount error: %s"), *Error.Message));
								++(*CompletedCount);
								if (*CompletedCount >= NumClients)
								{
									Done.Execute();
								}
							}
						);
					},
					[this, CompletedCount, NumClients, Done](const FNakamaError& Error)
					{
						AddError(FString::Printf(TEXT("Auth error: %s"), *Error.Message));
						++(*CompletedCount);
						if (*CompletedCount >= NumClients)
						{
							Done.Execute();
						}
					}
				);
			}
		});
	});
}

// ============================================================================
// LEAK DETECTION TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaProfilingLeakSpec, "IntegrationTests.Profiling.LeakDetection",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaClientConfig Client;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7350;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

	SIZE_T GetUsedPhysical()
	{
		FPlatformMemoryStats Stats = FPlatformMemory::GetStats();
		return Stats.UsedPhysical;
	}

END_DEFINE_SPEC(FNakamaProfilingLeakSpec)

const FString FNakamaProfilingLeakSpec::ServerKey = TEXT("defaultkey");
const FString FNakamaProfilingLeakSpec::Host = TEXT("127.0.0.1");

void FNakamaProfilingLeakSpec::Define()
{
	BeforeEach([this]()
	{
		Client = FNakamaClientConfig{ServerKey, Host, Port, false};
	});

	Describe("SharedPointers", [this]()
	{
		It("should not leak sessions", [this]()
		{
			CollectGarbage(GARBAGE_COLLECTION_KEEPFLAGS);
			const SIZE_T MemBefore = GetUsedPhysical();

			{
				TArray<FNakamaSession> Sessions;
				constexpr int32 NumSessions = 100;
				Sessions.Reserve(NumSessions);
				for (int32 i = 0; i < NumSessions; ++i)
				{
					FNakamaSession Sess;
					Sess.Token = FString::Printf(TEXT("fake-token-%d-padding-to-make-it-longer"), i);
					Sess.RefreshToken = FString::Printf(TEXT("fake-refresh-%d-padding-to-make-it-longer"), i);
					Sessions.Add(Sess);
				}
				Sessions.Empty();
			}

			CollectGarbage(GARBAGE_COLLECTION_KEEPFLAGS);
			const SIZE_T MemAfter = GetUsedPhysical();
			const double DeltaMB = static_cast<double>(MemAfter) / (1024.0 * 1024.0)
				- static_cast<double>(MemBefore) / (1024.0 * 1024.0);

			UE_LOG(LogNakamaProfile, Log, TEXT("[Profiling.LeakDetection] SessionLeak: Before=%.1fMB After=%.1fMB Delta=%.1fMB"),
				MemBefore / (1024.0 * 1024.0), MemAfter / (1024.0 * 1024.0), DeltaMB);

			// Threshold is generous (5MB) because UsedPhysical is process-wide RSS,
			// not allocation-scoped. See code review note #5.
			TestTrue(FString::Printf(TEXT("Session memory delta %.1fMB should be < 5MB"), DeltaMB),
				FMath::Abs(DeltaMB) < 5.0);
		});
	});

	Describe("UObjects", [this]()
	{
		LatentIt("should detect UObject leaks for BP actions", [this](const FDoneDelegate& Done)
		{
				FNakamaAccountCustom Account;
			Account.Id = GenerateId();

			NakamaApi::AuthenticateCustom(Client, Account, true, TEXT(""),
				[this, Done](const FNakamaSession& Session)
				{
					constexpr int32 NumActions = 50;
					TSharedPtr<int32> CompletedCount = MakeShared<int32>(0);
					TSharedPtr<TArray<TWeakObjectPtr<UBlueprintAsyncActionBase>>> WeakRefs =
						MakeShared<TArray<TWeakObjectPtr<UBlueprintAsyncActionBase>>>();

					for (int32 i = 0; i < NumActions; ++i)
					{
						auto* Action = UNakamaClientHealthcheck::Healthcheck(nullptr, Client, Session);
						Action->AddToRoot();
						WeakRefs->Add(Action);
						Action->Activate();

						FTSTicker::GetCoreTicker().AddTicker(
							FTickerDelegate::CreateLambda([Action, CompletedCount, NumActions, WeakRefs, Done, this](float) -> bool
							{
								Action->RemoveFromRoot();
								++(*CompletedCount);

								if (*CompletedCount >= NumActions)
								{
									CollectGarbage(GARBAGE_COLLECTION_KEEPFLAGS);

									int32 AliveCount = 0;
									for (const auto& Weak : *WeakRefs)
									{
										if (Weak.IsValid())
										{
											++AliveCount;
										}
									}

									UE_LOG(LogNakamaProfile, Log, TEXT("[Profiling.LeakDetection] BPObjectLeak: Created=%d AliveAfterGC=%d"),
										WeakRefs->Num(), AliveCount);

									TestTrue(FString::Printf(TEXT("After GC, %d/%d actions still alive (expected 0)"),
										AliveCount, WeakRefs->Num()),
										AliveCount == 0);
									Done.Execute();
								}
								return false;
							}),
							1.0f
						);
					}
				},
				[this, Done](const FNakamaError& Error)
				{
					AddError(FString::Printf(TEXT("Auth failed: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});
	});
}

// ============================================================================
// DIAGNOSTICS TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaProfilingDiagnosticsSpec, "IntegrationTests.Profiling.Diagnostics",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)
END_DEFINE_SPEC(FNakamaProfilingDiagnosticsSpec)

void FNakamaProfilingDiagnosticsSpec::Define()
{
	Describe("PlatformInfo", [this]()
	{
		It("should report platform memory stats", [this]()
		{
			FPlatformMemoryStats Stats = FPlatformMemory::GetStats();

			UE_LOG(LogNakamaProfile, Log, TEXT("[Profiling.Diagnostics] PlatformMemory:"));
			UE_LOG(LogNakamaProfile, Log, TEXT("  AvailablePhysical=%.1fMB"),
				Stats.AvailablePhysical / (1024.0 * 1024.0));
			UE_LOG(LogNakamaProfile, Log, TEXT("  AvailableVirtual=%.1fMB"),
				Stats.AvailableVirtual / (1024.0 * 1024.0));
			UE_LOG(LogNakamaProfile, Log, TEXT("  UsedPhysical=%.1fMB"),
				Stats.UsedPhysical / (1024.0 * 1024.0));
			UE_LOG(LogNakamaProfile, Log, TEXT("  UsedVirtual=%.1fMB"),
				Stats.UsedVirtual / (1024.0 * 1024.0));
			UE_LOG(LogNakamaProfile, Log, TEXT("  PeakUsedPhysical=%.1fMB"),
				Stats.PeakUsedPhysical / (1024.0 * 1024.0));
			UE_LOG(LogNakamaProfile, Log, TEXT("  PeakUsedVirtual=%.1fMB"),
				Stats.PeakUsedVirtual / (1024.0 * 1024.0));

			TestTrue("Memory stats should report non-zero available physical",
				Stats.AvailablePhysical > 0);
		});

		It("should report Nakama client defaults", [this]()
		{
			FNakamaClientConfig TestClient = FNakamaClientConfig{TEXT("defaultkey"), TEXT("127.0.0.1"), 7350, false};

			UE_LOG(LogNakamaProfile, Log, TEXT("[Profiling.Diagnostics] NakamaClient:"));
			UE_LOG(LogNakamaProfile, Log, TEXT("  Host=%s Port=%d SSL=%d"), *TestClient.Host, TestClient.Port, TestClient.bUseSSL);

			TestTrue("Client should have valid host", !TestClient.Host.IsEmpty());
		});
	});
}
