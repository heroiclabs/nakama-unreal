#include "NOnlineSubsystem/NOnlineSubsystem.h"
#include "NOnlineSubsystem/NOnlinePartySystem.h"

namespace Nakama {

    TSharedPtr<IOnlinePartySystem> createOnlinePartySystem()
    {
        return TSharedPtr<IOnlinePartySystem>(new NOnlinePartySystem());
    }

}
