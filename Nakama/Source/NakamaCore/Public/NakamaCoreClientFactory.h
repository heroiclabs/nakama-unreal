#pragma once

#include <nakama-cpp/Nakama.h>

class NAKAMACORE_API NakamaCoreClientFactory {

public:
	static void initLogging(Nakama::NLogLevel level);
	static Nakama::NClientPtr createNakamaClient(const Nakama::NClientParameters& parameters, Nakama::NLogLevel level);
	static Nakama::NRtClientPtr createNakamaRtClient(const Nakama::NClientPtr& client, int32_t port);
	static Nakama::NRtClientPtr createNakamaRtClient(const Nakama::NClientPtr& client, const Nakama::RtClientParameters& params);
};