#include "NakamaCoreClientFactory.h"
#include "UnrealLogSink.h"
#include "http.h"
#include "UnrealWsTransport.h"
#include "WebSocketsModule.h"

void NakamaCoreClientFactory::initLogging(Nakama::NLogLevel level)
{
	Nakama::NLogger::init(std::make_shared<Nakama::NUnrealLogSink>(), level);
}

Nakama::NClientPtr NakamaCoreClientFactory::createNakamaClient(const Nakama::NClientParameters& parameters, Nakama::NLogLevel level)
{
	initLogging(level);
	return Nakama::createRestClient(parameters, Nakama::NHttpTransportPtr(new Nakama::Unreal::UnrealHttpTransport()));
}

Nakama::NRtClientPtr NakamaCoreClientFactory::createNakamaRtClient(const Nakama::NClientPtr& client)
{
	return client->createRtClient(Nakama::NRtTransportPtr(new Nakama::Unreal::UnrealWsTransport()));
}
