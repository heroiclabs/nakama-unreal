#include "NOnlineSubsystem/NOnlinePartyJoinInfo.h"

namespace Nakama {

    NOnlinePartyJoinInfo::NOnlinePartyJoinInfo()
        : m_onlinePartyId(MakeShared<const NOnlinePartyId>())
        , m_uniqueNetId(MakeShared<const NUniqueNetId>())
    {
    }

    bool NOnlinePartyJoinInfo::IsValid() const
    {
        return false;
    }

    const TSharedRef<const FOnlinePartyId>& NOnlinePartyJoinInfo::GetPartyId() const
    {
        return m_onlinePartyId;
    }

    const FOnlinePartyTypeId NOnlinePartyJoinInfo::GetPartyTypeId() const
    {
        return FOnlinePartyTypeId();
    }

    const TSharedRef<const FUniqueNetId>& NOnlinePartyJoinInfo::GetSourceUserId() const
    {
        return m_uniqueNetId;
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
