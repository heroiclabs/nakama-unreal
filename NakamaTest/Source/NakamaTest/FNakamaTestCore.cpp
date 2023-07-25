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

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FNakamaTestCore, "NakamaTest.Core", EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

bool FNakamaTestCore::RunTest(const FString &Parameters)
{
	FWebSocketsModule* WebSocketsModule = &FModuleManager::LoadModuleChecked<FWebSocketsModule>(TEXT("WebSockets"));
	if (!WebSocketsModule)
	{
		return false;
	}

	// enqueue the test to run in a separate thread so it doesn't block the game thread, where requests come in on.
	FAutomationTestFramework::Get().EnqueueLatentCommand(MakeShareable(new FThreadedAutomationLatentCommand([WebSocketsModule]()
	{
		Nakama::Test::runAllTests(
			[](Nakama::NClientParameters parameters) -> Nakama::NClientPtr
			{
				return NakamaCoreClientFactory::createNakamaClient(parameters, Nakama::NLogLevel::Debug);
			},
			[WebSocketsModule](Nakama::NClientPtr client) -> Nakama::NRtClientPtr
			{
				return NakamaCoreClientFactory::createNakamaRtClient(client, WebSocketsModule);
			},
			{SERVER_KEY, SERVER_HOST, SERVER_PORT, SERVER_SSL}, SERVER_HTTP_KEY);
	})));

	return true;
}