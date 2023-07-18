// Copyright 2023 The Nakama Authors.

#include "CoreMinimal.h"
//#include "nakama-test/NTestLib.h"
#include "NakamaCoreClientFactory.h"

#define SERVER_KEY           "defaultkey"
#define SERVER_HTTP_KEY      "defaulthttpkey"
#define SERVER_HOST          "127.0.0.1"
#define SERVER_HTTP_PORT     7350
#define SERVER_SSL           false
#define SERVER_PORT SERVER_HTTP_PORT

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FNakamaTestCore, "NakamaTest.Core", EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

bool FNakamaTestCore::RunTest(const FString& Parameters)
{
	/*
    std::function<Nakama::NClientPtr(Nakama::NClientParameters)> clientFactory = [](Nakama::NClientParameters parameters) -> Nakama::NClientPtr {
        return NakamaCoreClientFactory::createNakamaClient(parameters, Nakama::NLogLevel::Debug);
    };

    auto rtClientFactory = [](Nakama::NClientPtr client) -> Nakama::NRtClientPtr {
        return NakamaCoreClientFactory::createNakamaRtClient(client);
    };

    int allTestsResult = Nakama::Test::runAllTests(clientFactory, rtClientFactory, {SERVER_KEY, SERVER_HOST, SERVER_PORT, SERVER_SSL}, SERVER_HTTP_KEY);

	return allTestsResult == 0;
	*/
	return 0;
}