#include "UnrealLogSink.h"
#include "NakamaCore.h"
#include "http.h"
#include "UnrealWsTransport.h"

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

NRtClientPtr createNakamaRtClient(const NClientPtr& client)
{
   return client->createRtClient(NRtTransportPtr(new UnrealWsTransport()));
}

}
}