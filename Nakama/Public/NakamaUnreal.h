#pragma once

#include <nakama-cpp/Nakama.h>

NAKAMA_NAMESPACE_BEGIN

namespace Unreal {

void initLogging(NLogLevel level);
NClientPtr createNakamaClient(const NClientParameters& parameters, NLogLevel level);
NRtClientPtr createNakamaRtClient(const NClientPtr& client, int32_t port);
NRtClientPtr createNakamaRtClient(const NClientPtr& client, const RtClientParameters& params);

}



NAKAMA_NAMESPACE_END