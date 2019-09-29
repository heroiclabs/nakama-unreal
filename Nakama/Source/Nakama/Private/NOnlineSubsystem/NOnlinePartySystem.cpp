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

#include "NOnlineSubsystem/NOnlinePartySystem.h"
#include "NOnlineSubsystem/NOnlinePartyJoinInfo.h"
#include "NOnlineSubsystem/NOnlinePartyId.h"
#include <sstream>

#define RAPIDJSON_HAS_STDSTRING 1
//#define RAPIDJSON_NAMESPACE Nakama::rapidjson
//#define RAPIDJSON_NAMESPACE_BEGIN namespace Nakama { namespace rapidjson {
//#define RAPIDJSON_NAMESPACE_END }}

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#undef NMODULE_NAME
#define NMODULE_NAME "NOnlinePartySystem"

NAKAMA_NAMESPACE_BEGIN

    template <typename T>
    std::string toStdString(const T& value)
    {
        std::stringstream ss;
        ss << value;
        return ss.str();
    }

    std::string toStdString(const FString& s)
    {
        return TCHAR_TO_UTF8(*s);
    }

    std::string jsonDocToStdStr(rapidjson::Document& document)
    {
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);
        return buffer.GetString();
    }

    NOnlinePartySystem::NOnlinePartySystem(NClientPtr client, NRtClientPtr rtClient, NSessionPtr session)
        : _client(client), _rtClient(rtClient), _session(session)
    {
        _rtClient->setListener(&_listener);

        _listener.setNotificationsCallback([this](const NNotificationList& notifications)
        {
            for (auto& notification : notifications.notifications)
            {
                if (notification.code == 100)
                {
                    handleJoinPartyResponse(notification.content);
                }
            }
        });
    }

    void NOnlinePartySystem::RestoreParties(const FUniqueNetId & LocalUserId, const FOnRestorePartiesComplete & CompletionDelegate)
    {
    }

    void NOnlinePartySystem::CleanupParties(const FUniqueNetId & LocalUserId, const FOnCleanupPartiesComplete & CompletionDelegate)
    {
    }

    std::string PartyConfigurationToJson(const FPartyConfiguration & PartyConfig)
    {
        rapidjson::Document document;
        document.SetObject();

        document.AddMember("JoinRequestAction", (int)PartyConfig.JoinRequestAction, document.GetAllocator());
        document.AddMember("PresencePermissions", (uint8)PartyConfig.PresencePermissions, document.GetAllocator());
        document.AddMember("InvitePermissions", (uint8)PartyConfig.InvitePermissions, document.GetAllocator());
        document.AddMember("bChatEnabled", PartyConfig.bChatEnabled, document.GetAllocator());
        document.AddMember("bShouldRemoveOnDisconnection", PartyConfig.bShouldRemoveOnDisconnection, document.GetAllocator());
        document.AddMember("bIsAcceptingMembers", PartyConfig.bIsAcceptingMembers, document.GetAllocator());
        document.AddMember("NotAcceptingMembersReason", PartyConfig.NotAcceptingMembersReason, document.GetAllocator());
        document.AddMember("MaxMembers", PartyConfig.MaxMembers, document.GetAllocator());
        document.AddMember("Nickname", toStdString(PartyConfig.Nickname), document.GetAllocator());
        document.AddMember("Description", toStdString(PartyConfig.Description), document.GetAllocator());
        document.AddMember("Password", toStdString(PartyConfig.Password), document.GetAllocator());

        return jsonDocToStdStr(document);
    }

    std::string OnlinePartyJoinInfoToJson(const IOnlinePartyJoinInfo & OnlinePartyJoinInfo)
    {
        rapidjson::Document document;
        document.SetObject();

        document.AddMember("party_id", toStdString(OnlinePartyJoinInfo.GetPartyId().Get().ToString()), document.GetAllocator());

        return jsonDocToStdStr(document);
    }

    bool NOnlinePartySystem::CreateParty(const FUniqueNetId & LocalUserId, const FOnlinePartyTypeId PartyTypeId, const FPartyConfiguration & PartyConfig, const FOnCreatePartyComplete & Delegate)
    {
        if (!_rtClient->isConnected())
        {
            NLOG_ERROR("RtClient is not connected");
            return false;
        }

        auto LocalUserIdPtr = LocalUserId.AsShared();

        auto successCallback = [LocalUserIdPtr, Delegate](const NRpc& rpc)
        {
            auto partyId = MakeShared<NOnlinePartyId>();
            ECreatePartyCompletionResult result = ECreatePartyCompletionResult::UnknownClientFailure;
            rapidjson::Document document;

            if (document.Parse(rpc.payload).HasParseError())
            {
                NLOG_ERROR("Failed parse json: " + rpc.payload);
            }
            else
            {
                auto& jsonPartyId = document["party_id"];
                auto& jsonResult  = document["create_party_completion_result"];

                if (jsonPartyId.IsString() && jsonResult.IsNumber())
                {
                    (*partyId).SetId(jsonPartyId.GetString());

                    result = (ECreatePartyCompletionResult)jsonResult.GetInt();
                }
                else
                {
                    NLOG_ERROR("No required fields in json: " + rpc.payload);
                }
            }

            Delegate.ExecuteIfBound(*LocalUserIdPtr, partyId, result);
        };

        auto errorCallback = [LocalUserIdPtr, Delegate](const NRtError& error)
        {
            auto partyId = MakeShared<NOnlinePartyId>();

            Delegate.ExecuteIfBound(*LocalUserIdPtr, partyId, ECreatePartyCompletionResult::UnknownClientFailure);
        };

        rapidjson::Document document;
        document.SetObject();

        document.AddMember("party_type_id", PartyTypeId.GetValue(), document.GetAllocator());
        document.AddMember("party_configuration", PartyConfigurationToJson(PartyConfig), document.GetAllocator());

        std::string payload(jsonDocToStdStr(document));

        _rtClient->rpc(
            "onlinepartysystem-createparty",
            payload,
            successCallback,
            errorCallback);

        return true;
    }

    bool NOnlinePartySystem::UpdateParty(const FUniqueNetId & LocalUserId, const FOnlinePartyId & PartyId, const FPartyConfiguration & PartyConfig, bool bShouldRegenerateReservationKey, const FOnUpdatePartyComplete & Delegate)
    {
        return false;
    }

    bool NOnlinePartySystem::JoinParty(const FUniqueNetId & LocalUserId, const IOnlinePartyJoinInfo & OnlinePartyJoinInfo, const FOnJoinPartyComplete & Delegate)
    {
        if (!_rtClient->isConnected())
        {
            NLOG_ERROR("RtClient is not connected");
            return false;
        }

        std::string partyId = toStdString(OnlinePartyJoinInfo.GetPartyId().Get().ToString());
        JoinPartyInfo& joinPartyInfo = _joinInfo[partyId];

        joinPartyInfo.delegate = Delegate;
        joinPartyInfo.localUserId = LocalUserId.AsShared();

        auto successCallback = [this](const NRpc& rpc)
        {
            handleJoinPartyResponse(rpc.payload);
        };

        auto errorCallback = [this, partyId](const NRtError& error)
        {
            joinPartyResult(partyId, EJoinPartyCompletionResult::UnknownClientFailure);
        };

        std::string payload(OnlinePartyJoinInfoToJson(OnlinePartyJoinInfo));

        _rtClient->rpc(
            "onlinepartysystem-joinparty",
            payload,
            successCallback,
            errorCallback);

        return true;
    }

#ifdef N_ENABLE_JIP
    bool NOnlinePartySystem::JIPFromWithinParty(const FUniqueNetId & LocalUserId, const FOnlinePartyId & PartyId, const FUniqueNetId & PartyLeaderId)
    {
        return false;
    }
#endif

    void NOnlinePartySystem::QueryPartyJoinability(const FUniqueNetId & LocalUserId, const IOnlinePartyJoinInfo & OnlinePartyJoinInfo, const FOnQueryPartyJoinabilityComplete & Delegate)
    {
    }

    bool NOnlinePartySystem::RejoinParty(const FUniqueNetId & LocalUserId, const FOnlinePartyId & PartyId, const FOnlinePartyTypeId & PartyTypeId, const TArray<TSharedRef<const FUniqueNetId>>& FormerMembers, const FOnJoinPartyComplete & Delegate)
    {
        return false;
    }

    bool NOnlinePartySystem::LeaveParty(const FUniqueNetId & LocalUserId, const FOnlinePartyId & PartyId, const FOnLeavePartyComplete & Delegate)
    {
        if (!_rtClient->isConnected())
        {
            NLOG_ERROR("RtClient is not connected");
            return false;
        }

        auto LocalUserIdPtr = LocalUserId.AsShared();
        auto PartyIdPtr = PartyId.AsShared();

        auto successCallback = [LocalUserIdPtr, PartyIdPtr, Delegate](const NRpc& rpc)
        {
            ELeavePartyCompletionResult result = ELeavePartyCompletionResult::UnknownClientFailure;
            rapidjson::Document document;

            if (document.Parse(rpc.payload).HasParseError())
            {
                NLOG_ERROR("Failed parse json: " + rpc.payload);
            }
            else
            {
                auto& jsonResult = document["leave_party_completion_result"];

                if (jsonResult.IsNumber())
                {
                    result = (ELeavePartyCompletionResult)jsonResult.GetInt();
                }
                else
                {
                    NLOG_ERROR("No required fields in json: " + rpc.payload);
                }
            }

            Delegate.ExecuteIfBound(*LocalUserIdPtr, *PartyIdPtr, result);
        };

        auto errorCallback = [LocalUserIdPtr, Delegate, PartyIdPtr](const NRtError& error)
        {
            Delegate.ExecuteIfBound(*LocalUserIdPtr, *PartyIdPtr, ELeavePartyCompletionResult::UnknownClientFailure);
        };

        rapidjson::Document document;
        document.SetObject();

        document.AddMember("party_id", toStdString(PartyId.ToString()), document.GetAllocator());

        std::string payload(jsonDocToStdStr(document));

        _rtClient->rpc(
            "onlinepartysystem-leaveparty",
            payload,
            successCallback,
            errorCallback);

        return true;
    }

    bool NOnlinePartySystem::ApproveJoinRequest(const FUniqueNetId & LocalUserId, const FOnlinePartyId & PartyId, const FUniqueNetId & RecipientId, bool bIsApproved, int32 DeniedResultCode)
    {
        return false;
    }

#ifdef N_ENABLE_JIP
    bool NOnlinePartySystem::ApproveJIPRequest(const FUniqueNetId & LocalUserId, const FOnlinePartyId & PartyId, const FUniqueNetId & RecipientId, bool bIsApproved, int32 DeniedResultCode)
    {
        return false;
    }
#endif

    void NOnlinePartySystem::RespondToQueryJoinability(const FUniqueNetId & LocalUserId, const FOnlinePartyId & PartyId, const FUniqueNetId & RecipientId, bool bCanJoin, int32 DeniedResultCode)
    {
    }

    bool NOnlinePartySystem::SendInvitation(const FUniqueNetId & LocalUserId, const FOnlinePartyId & PartyId, const FPartyInvitationRecipient & Recipient, const FOnSendPartyInvitationComplete & Delegate)
    {
        return false;
    }

    bool NOnlinePartySystem::RejectInvitation(const FUniqueNetId & LocalUserId, const FUniqueNetId & SenderId)
    {
        return false;
    }

    void NOnlinePartySystem::ClearInvitations(const FUniqueNetId & LocalUserId, const FUniqueNetId & SenderId, const FOnlinePartyId * PartyId)
    {
    }

    bool NOnlinePartySystem::KickMember(const FUniqueNetId & LocalUserId, const FOnlinePartyId & PartyId, const FUniqueNetId & TargetMemberId, const FOnKickPartyMemberComplete & Delegate)
    {
        return false;
    }

    bool NOnlinePartySystem::PromoteMember(const FUniqueNetId & LocalUserId, const FOnlinePartyId & PartyId, const FUniqueNetId & TargetMemberId, const FOnPromotePartyMemberComplete & Delegate)
    {
        return false;
    }

    bool NOnlinePartySystem::UpdatePartyData(const FUniqueNetId & LocalUserId, const FOnlinePartyId & PartyId, const FOnlinePartyData & PartyData)
    {
        return false;
    }

    bool NOnlinePartySystem::UpdatePartyMemberData(const FUniqueNetId & LocalUserId, const FOnlinePartyId & PartyId, const FOnlinePartyData & PartyMemberData)
    {
        return false;
    }

    bool NOnlinePartySystem::IsMemberLeader(const FUniqueNetId & LocalUserId, const FOnlinePartyId & PartyId, const FUniqueNetId & MemberId) const
    {
        return false;
    }

    uint32 NOnlinePartySystem::GetPartyMemberCount(const FUniqueNetId & LocalUserId, const FOnlinePartyId & PartyId) const
    {
        return uint32();
    }

    TSharedPtr<const FOnlineParty> NOnlinePartySystem::GetParty(const FUniqueNetId & LocalUserId, const FOnlinePartyId & PartyId) const
    {
        return TSharedPtr<const FOnlineParty>();
    }

    TSharedPtr<const FOnlineParty> NOnlinePartySystem::GetParty(const FUniqueNetId & LocalUserId, const FOnlinePartyTypeId & PartyTypeId) const
    {
        return TSharedPtr<const FOnlineParty>();
    }

    FOnlinePartyMemberConstPtr NOnlinePartySystem::GetPartyMember(const FUniqueNetId & LocalUserId, const FOnlinePartyId & PartyId, const FUniqueNetId & MemberId) const
    {
        return FOnlinePartyMemberConstPtr();
    }

    FOnlinePartyDataConstPtr NOnlinePartySystem::GetPartyData(const FUniqueNetId & LocalUserId, const FOnlinePartyId & PartyId) const
    {
        return FOnlinePartyDataConstPtr();
    }

    FOnlinePartyDataConstPtr NOnlinePartySystem::GetPartyMemberData(const FUniqueNetId & LocalUserId, const FOnlinePartyId & PartyId, const FUniqueNetId & MemberId) const
    {
        return FOnlinePartyDataConstPtr();
    }

    IOnlinePartyJoinInfoConstPtr NOnlinePartySystem::GetAdvertisedParty(const FUniqueNetId & LocalUserId, const FUniqueNetId & UserId, const FOnlinePartyTypeId PartyTypeId) const
    {
        return IOnlinePartyJoinInfoConstPtr();
    }

    bool NOnlinePartySystem::GetJoinedParties(const FUniqueNetId & LocalUserId, TArray<TSharedRef<const FOnlinePartyId>>& OutPartyIdArray) const
    {
        return false;
    }

    bool NOnlinePartySystem::GetPartyMembers(const FUniqueNetId & LocalUserId, const FOnlinePartyId & PartyId, TArray<FOnlinePartyMemberConstRef>& OutPartyMembersArray) const
    {
        return false;
    }

    bool NOnlinePartySystem::GetPendingInvites(const FUniqueNetId & LocalUserId, TArray<IOnlinePartyJoinInfoConstRef>& OutPendingInvitesArray) const
    {
        return false;
    }

    bool NOnlinePartySystem::GetPendingJoinRequests(const FUniqueNetId & LocalUserId, const FOnlinePartyId & PartyId, TArray<IOnlinePartyPendingJoinRequestInfoConstRef>& OutPendingJoinRequestArray) const
    {
        return false;
    }

    bool NOnlinePartySystem::GetPendingInvitedUsers(const FUniqueNetId & LocalUserId, const FOnlinePartyId & PartyId, TArray<TSharedRef<const FUniqueNetId>>& OutPendingInvitedUserArray) const
    {
        return false;
    }

    FString NOnlinePartySystem::MakeJoinInfoJson(const FUniqueNetId & LocalUserId, const FOnlinePartyId & PartyId)
    {
        return FString();
    }

    IOnlinePartyJoinInfoConstPtr NOnlinePartySystem::MakeJoinInfoFromJson(const FString & JoinInfoJson)
    {
        return IOnlinePartyJoinInfoConstPtr();
    }

    FString NOnlinePartySystem::MakeTokenFromJoinInfo(const IOnlinePartyJoinInfo & JoinInfo) const
    {
        return FString();
    }

    IOnlinePartyJoinInfoConstPtr NOnlinePartySystem::MakeJoinInfoFromToken(const FString & Token) const
    {
        return IOnlinePartyJoinInfoConstPtr();
    }

    IOnlinePartyJoinInfoConstPtr NOnlinePartySystem::ConsumePendingCommandLineInvite()
    {
        return IOnlinePartyJoinInfoConstPtr();
    }

    void NOnlinePartySystem::DumpPartyState()
    {
    }

    void NOnlinePartySystem::handleJoinPartyResponse(const std::string& content)
    {
        rapidjson::Document document;

        if (document.Parse(content).HasParseError())
        {
            NLOG_ERROR("Failed parse json: " + content);
        }
        else
        {
            auto& jsonPartyId = document["party_id"];
            auto& jsonResult = document["join_party_completion_result"];

            if (jsonPartyId.IsString() && jsonResult.IsNumber())
            {
                joinPartyResult(jsonPartyId.GetString(), (EJoinPartyCompletionResult)jsonResult.GetInt());
            }
            else
            {
                NLOG_ERROR("No required fields in json: " + content);
            }
        }
    }

    void NOnlinePartySystem::joinPartyResult(const std::string & partyId, EJoinPartyCompletionResult result)
    {
        auto it = _joinInfo.find(partyId);
        if (it != _joinInfo.end())
        {
            JoinPartyInfo& joinPartyInfo = it->second;
            NOnlinePartyId onlinePartyId(partyId.c_str());

            joinPartyInfo.delegate.ExecuteIfBound(*joinPartyInfo.localUserId, onlinePartyId, result, 0);

            _joinInfo.erase(it);
        }
        else
        {
            NLOG_ERROR("Join info not found by party id: " + partyId);
        }
    }

NAKAMA_NAMESPACE_END
