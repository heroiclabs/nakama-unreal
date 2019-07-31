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

#include "NOnlineSubsystem/NOnlineSubsystem.h"
#include "NOnlineSubsystem/NOnlinePartySystem.h"
#include "NOnlineSubsystem/NUniqueNetId.h"
#include "NOnlineSubsystem/NOnlinePartyJoinInfo.h"

namespace Nakama {

    TSharedPtr<IOnlinePartySystem> NOnlineSubsystem::createOnlinePartySystem(NClientPtr client, NRtClientPtr rtClient, NSessionPtr session)
    {
        return TSharedPtr<IOnlinePartySystem>(new NOnlinePartySystem(client, rtClient, session));
    }

    TSharedRef<const FUniqueNetId> NOnlineSubsystem::getPlayerId(NSessionPtr session)
    {
        return TSharedRef<const FUniqueNetId>(new NUniqueNetId(session->getUserId().c_str()));
    }

    TSharedPtr<INakamaOnlinePartyJoinInfo> NOnlineSubsystem::createPartyJoinInfo()
    {
        return TSharedRef<INakamaOnlinePartyJoinInfo>(new NOnlinePartyJoinInfo());
    }

}
