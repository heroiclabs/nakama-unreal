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

#include "NOnlineSubsystem/NOnlinePartyId.h"

namespace Nakama {

    NOnlinePartyId::NOnlinePartyId()
    {
    }

    NOnlinePartyId::NOnlinePartyId(const FString& id) : _id(id)
    {
    }

    NOnlinePartyId::NOnlinePartyId(FString && id) : _id(std::move(id))
    {
    }

    const uint8 * NOnlinePartyId::GetBytes() const
    {
        return (const uint8 *)_id.GetCharArray().GetData();
    }

    int32 NOnlinePartyId::GetSize() const
    {
        return _id.Len();
    }

    bool NOnlinePartyId::IsValid() const
    {
        return !_id.IsEmpty();
    }

    FString NOnlinePartyId::ToString() const
    {
        return _id;
    }

    FString NOnlinePartyId::ToDebugString() const
    {
        return _id;
    }

    void NOnlinePartyId::SetId(const FString & id)
    {
        _id = id;
    }

    void NOnlinePartyId::SetId(FString && id)
    {
        _id = std::move(id);
    }

}
