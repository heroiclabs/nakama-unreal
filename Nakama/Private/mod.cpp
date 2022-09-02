#include "UnrealLogSink.h"
#include "NakamaUnreal.h"
#include "http.h"
#include "websocket.h"

#include "CoreMinimal.h"

DEFINE_LOG_CATEGORY(LogNakama);

namespace Nakama {
namespace Unreal {
   
void initLogging(NLogLevel level)
{
   Nakama::NLogger::init(std::make_shared<NUnrealLogSink>(), level);
}

NClientPtr createNakamaClient(const NClientParameters& parameters, NLogLevel level)
{
   initLogging(level);
   return Nakama::createRestClient(parameters, NHttpTransportPtr(new UnrealHttpTransport()));
}
   
NRtClientPtr createNakamaRtClient(const NClientPtr& client, int32_t port)
{
   return client->createRtClient(port, NRtTransportPtr(new UnrealWsTransport()));
}

NRtClientPtr createNakamaRtClient(const NClientPtr& client, const RtClientParameters& params)
{
   return client->createRtClient(params, NRtTransportPtr(new UnrealWsTransport()));
}

}
}