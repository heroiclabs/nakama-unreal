#pragma once

#include <nakama-cpp/Nakama.h>
#include "WebSocketsModule.h"

class NAKAMACORE_API NakamaCoreClientFactory {

public:
	static void initLogging(Nakama::NLogLevel level);
	static Nakama::NClientPtr createNakamaClient(const Nakama::NClientParameters& parameters, Nakama::NLogLevel level);
	static Nakama::NRtClientPtr createNakamaRtClient(const Nakama::NClientPtr& client);
};