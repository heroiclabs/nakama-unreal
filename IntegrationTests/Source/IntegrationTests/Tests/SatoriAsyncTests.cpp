/**
 * Satori API Integration Test Suite
 */

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "SatoriClient.h"
#include "SatoriEvent.h"
#include "SatoriConsoleHelper.h"

// ============================================================================
// SERVER EVENT TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FSatoriServerEventSpec, "Satori.ServerEvents",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

	USatoriClient* Client;

	static FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7450;

END_DEFINE_SPEC(FSatoriServerEventSpec)

FString FSatoriServerEventSpec::ServerKey;
const FString FSatoriServerEventSpec::Host = TEXT("127.0.0.1");

void FSatoriServerEventSpec::Define()
{
	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		GetSatoriApiKey().Next([this, Done](FString Key)
		{
			if (Key.IsEmpty())
			{
				AddError(TEXT("Failed to retrieve Satori API key from console"));
				Done.Execute();
				return Key;
			}
			ServerKey = Key;
			Client = USatoriClient::CreateDefaultClient(Key, Host, Port, false, true);
			Done.Execute();
			return Key;
		});
	});

	LatentIt("should post a basic server event", [this](const FDoneDelegate& Done)
	{
		FSatoriEvent Event;
		Event.Name = TEXT("gameStarted");
		Event.Value = TEXT("test-game");
		Event.Timestamp = FDateTime::UtcNow();

		Client->PostServerEvent({Event},
			[Done]() { Done.Execute(); },
			[this, Done](const FSatoriError& Error)
			{
				AddError(FString::Printf(TEXT("PostServerEvent failed: %s"), *Error.Message));
				Done.Execute();
			});
	});

	LatentIt("should post a server event with metadata and value", [this](const FDoneDelegate& Done)
	{
		FSatoriEvent Event;
		Event.Name = TEXT("purchaseCompleted");
		Event.Value = TEXT("100");
		Event.Metadata.Add(TEXT("platform"), TEXT("windows"));
		Event.Metadata.Add(TEXT("version"), TEXT("1.0"));
		Event.Timestamp = FDateTime::UtcNow();

		Client->PostServerEvent({Event},
			[Done]() { Done.Execute(); },
			[this, Done](const FSatoriError& Error)
			{
				AddError(FString::Printf(TEXT("PostServerEvent with metadata failed: %s"), *Error.Message));
				Done.Execute();
			});
	});

	LatentIt("should post multiple server events in one call", [this](const FDoneDelegate& Done)
	{
		FSatoriEvent Event1;
		Event1.Name = TEXT("gameStarted");
		Event1.Value = TEXT("test-game");
		Event1.Timestamp = FDateTime::UtcNow();

		FSatoriEvent Event2;
		Event2.Name = TEXT("screenViewed");
		Event2.Value = TEXT("main_menu");
		Event2.Timestamp = FDateTime::UtcNow();

		Client->PostServerEvent({Event1, Event2},
			[Done]() { Done.Execute(); },
			[this, Done](const FSatoriError& Error)
			{
				AddError(FString::Printf(TEXT("PostServerEvent with multiple events failed: %s"), *Error.Message));
				Done.Execute();
			});
	});
}
