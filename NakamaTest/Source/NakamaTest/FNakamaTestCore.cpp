// Copyright 2023 The Nakama Authors.

#include "CoreMinimal.h"
#include "nakama-test/NTestLib.h"
#include "NakamaCoreClientFactory.h"
#include "WebSocketsModule.h"

#define SERVER_KEY "defaultkey"
#define SERVER_HTTP_KEY "defaulthttpkey"
#define SERVER_HOST "127.0.0.1"
#define SERVER_HTTP_PORT 7350
#define SERVER_SSL false
#define SERVER_PORT SERVER_HTTP_PORT

DEFINE_LOG_CATEGORY_STATIC(NakamaTestLog, All, Log)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FNakamaTestCore, "NakamaTest.Core", EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

bool FNakamaTestCore::RunTest(const FString &Parameters)
{
	UE_LOG(LogTemp, Log, TEXT("%s"), "Running tests");

	// enqueue the test to run in a separate thread so it doesn't block the game thread, where requests come in on.
	FAutomationTestFramework::Get().EnqueueLatentCommand(MakeShareable(new FThreadedAutomationLatentCommand([]()
	{

		Nakama::Test::runAllTests(
			[](Nakama::NClientParameters parameters) -> Nakama::NClientPtr
			{
				return NakamaCoreClientFactory::createNakamaClient(parameters, Nakama::NLogLevel::Debug);
			},
			[](Nakama::NClientPtr client) -> Nakama::NRtClientPtr
			{
				return NakamaCoreClientFactory::createNakamaRtClient(client);
			},
			{SERVER_KEY, SERVER_HOST, SERVER_PORT, SERVER_SSL}, SERVER_HTTP_KEY);
	})));

	return true;
}