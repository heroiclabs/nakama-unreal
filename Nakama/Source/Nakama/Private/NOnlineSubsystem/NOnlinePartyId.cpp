#include "NOnlineSubsystem/NOnlinePartyId.h"

namespace Nakama {

    const uint8 * NOnlinePartyId::GetBytes() const
    {
        return nullptr;
    }

    int32 NOnlinePartyId::GetSize() const
    {
        return int32();
    }

    bool NOnlinePartyId::IsValid() const
    {
        return false;
    }

    FString NOnlinePartyId::ToString() const
    {
        return FString();
    }

    FString NOnlinePartyId::ToDebugString() const
    {
        return FString();
    }

}
