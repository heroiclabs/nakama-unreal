#include "NOnlineSubsystem/NOnlinePartyJoinInfo.h"

namespace Nakama {

    bool NOnlinePartyJoinInfo::IsValid() const
    {
        return false;
    }

    const TSharedRef<const FOnlinePartyId>& NOnlinePartyJoinInfo::GetPartyId() const
    {
        return MakeShared<const FOnlinePartyId>();
    }

    const FOnlinePartyTypeId NOnlinePartyJoinInfo::GetPartyTypeId() const
    {
        return FOnlinePartyTypeId();
    }

    const TSharedRef<const FUniqueNetId>& NOnlinePartyJoinInfo::GetSourceUserId() const
    {
        return MakeShared<const FUniqueNetId>();
    }

    const FString & NOnlinePartyJoinInfo::GetSourceDisplayName() const
    {
        return m_sourceDisplayName;
    }

    const FString & NOnlinePartyJoinInfo::GetSourcePlatform() const
    {
        return m_sourcePlatform;
    }

    bool NOnlinePartyJoinInfo::HasKey() const
    {
        return false;
    }

    bool NOnlinePartyJoinInfo::HasPassword() const
    {
        return false;
    }

    bool NOnlinePartyJoinInfo::IsAcceptingMembers() const
    {
        return false;
    }

    bool NOnlinePartyJoinInfo::IsPartyOfOne() const
    {
        return false;
    }

    int32 NOnlinePartyJoinInfo::GetNotAcceptingReason() const
    {
        return int32();
    }

    const FString & NOnlinePartyJoinInfo::GetAppId() const
    {
        return m_appId;
    }

    const FString & NOnlinePartyJoinInfo::GetBuildId() const
    {
        return m_buildId;
    }

    bool NOnlinePartyJoinInfo::CanJoin() const
    {
        return false;
    }

    bool NOnlinePartyJoinInfo::CanJoinWithPassword() const
    {
        return false;
    }

    bool NOnlinePartyJoinInfo::CanRequestAnInvite() const
    {
        return false;
    }

}
