/*
 * Copyright 2019 The Nakama Authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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
