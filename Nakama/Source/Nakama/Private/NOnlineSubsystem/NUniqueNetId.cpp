#include "NOnlineSubsystem/NUniqueNetId.h"

namespace Nakama {

    const uint8 * NUniqueNetId::GetBytes() const
    {
        return nullptr;
    }

    int32 NUniqueNetId::GetSize() const
    {
        return int32();
    }

    bool NUniqueNetId::IsValid() const
    {
        return false;
    }

    FString NUniqueNetId::ToString() const
    {
        return FString();
    }

    FString NUniqueNetId::ToDebugString() const
    {
        return FString();
    }

}
