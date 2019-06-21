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

#pragma once

#include "OnlinePartyInterface.h"
#include "NOnlineSubsystem/NOnlinePartyId.h"
#include "NOnlineSubsystem/NUniqueNetId.h"

namespace Nakama {

    /**
     * Info needed to join a party
     */
    class NOnlinePartyJoinInfo : public IOnlinePartyJoinInfo
    {
    public:
        NOnlinePartyJoinInfo();

        bool IsValid() const override;

        /**
         * @return party id of party associated with this join invite
         */
        const TSharedRef<const FOnlinePartyId>& GetPartyId() const override;

        /**
         * @return party id of party associated with this join invite
         */
        const FOnlinePartyTypeId GetPartyTypeId() const override;

        /**
         * @return user id of where this join info came from
         */
        const TSharedRef<const FUniqueNetId>& GetSourceUserId() const override;

        /**
         * @return user id of where this join info came from
         */
        const FString& GetSourceDisplayName() const override;

        /**
         * @return source platform string
         */
        const FString& GetSourcePlatform() const override;

        /**
         * @return true if the join info has some form of key(does not guarantee the validity of that key)
         */
        bool HasKey() const override;

        /**
         * @return true if a password can be used to bypass generated access key
         */
        bool HasPassword() const override;

        /**
         * @return true if the party is known to be accepting members
         */
        bool IsAcceptingMembers() const override;

        /**
         * @return true if this is a party of one
         */
        bool IsPartyOfOne() const override;

        /**
         * @return why the party is not accepting members
         */
        int32 GetNotAcceptingReason() const override;

        /**
         * @return id of the client app associated with the sender of the party invite
         */
        const FString& GetAppId() const override;

        /**
        * @return id of the build associated with the sender of the party invite
        */
        const FString& GetBuildId() const override;

        /**
         * @return whether or not the join info can be used to join
         */
        bool CanJoin() const override;

        /**
         * @return whether or not the join info can be used to join with a password
         */
        bool CanJoinWithPassword() const override;

        /**
         * @return whether or not the join info has the info to request an invite
         */
        bool CanRequestAnInvite() const override;

    protected:
        FString m_sourceDisplayName;
        FString m_sourcePlatform;
        FString m_appId;
        FString m_buildId;
        TSharedRef<const FOnlinePartyId> m_onlinePartyId;
        TSharedRef<const FUniqueNetId> m_uniqueNetId;
    };

}
