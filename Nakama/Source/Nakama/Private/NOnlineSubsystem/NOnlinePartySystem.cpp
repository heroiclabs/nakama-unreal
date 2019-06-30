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

namespace Nakama {

    NOnlinePartySystem::NOnlinePartySystem(NClientPtr client, NRtClientPtr rtClient, NSessionPtr session)
        : _client(client), _rtClient(rtClient), _session(session)
    {
    }

    bool NOnlinePartySystem::CreateParty(const FUniqueNetId & LocalUserId, const FOnlinePartyTypeId PartyTypeId, const FPartyConfiguration & PartyConfig, const FOnCreatePartyComplete & Delegate)
    {
        auto LocalUserIdPtr = LocalUserId.AsShared();

        auto successCallback = [LocalUserIdPtr, Delegate](const NGroup& group)
        {
            auto partyId = MakeShared<NOnlinePartyId>();

            Delegate.ExecuteIfBound(*LocalUserIdPtr, partyId, ECreatePartyCompletionResult::Succeeded);
        };

        auto errorCallback = [LocalUserIdPtr, Delegate](const NError& error)
        {
            ECreatePartyCompletionResult partyResult;

            switch (error.code)
            {
            default:
            case ErrorCode::Unknown:          partyResult = ECreatePartyCompletionResult::UnknownClientFailure; break;
            case ErrorCode::NotFound:         partyResult = ECreatePartyCompletionResult::UnknownInternalFailure; break;
            case ErrorCode::AlreadyExists:    partyResult = ECreatePartyCompletionResult::AlreadyCreatingParty; break;
            case ErrorCode::InvalidArgument:  partyResult = ECreatePartyCompletionResult::UnknownClientFailure; break;
            case ErrorCode::Unauthenticated:  partyResult = ECreatePartyCompletionResult::LoggedOut; break;
            case ErrorCode::PermissionDenied: partyResult = ECreatePartyCompletionResult::UnknownClientFailure; break;
            case ErrorCode::ConnectionError:  partyResult = ECreatePartyCompletionResult::UnknownClientFailure; break;
            case ErrorCode::InternalError:    partyResult = ECreatePartyCompletionResult::UnknownInternalFailure; break;
            }

            auto partyId = MakeShared<NOnlinePartyId>();

            Delegate.ExecuteIfBound(*LocalUserIdPtr, partyId, partyResult);
        };

        //_client->listGroups(_session);
        _client->createGroup(
            _session,
            TCHAR_TO_UTF8(*PartyConfig.Nickname), // name
            TCHAR_TO_UTF8(*PartyConfig.Description), // description
            "",
            "",
            false,
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
        return false;
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
        return false;
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

    bool NOnlinePartySystem::AcceptInvitation(const FUniqueNetId & LocalUserId, const FUniqueNetId & SenderId)
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

    void NOnlinePartySystem::ApproveUserForRejoin(const FUniqueNetId & LocalUserId, const FOnlinePartyId & PartyId, const FUniqueNetId & ApprovedUserId)
    {
    }

    void NOnlinePartySystem::RemoveUserForRejoin(const FUniqueNetId & LocalUserId, const FOnlinePartyId & PartyId, const FUniqueNetId & RemovedUserId)
    {
    }

    void NOnlinePartySystem::GetUsersApprovedForRejoin(const FUniqueNetId & LocalUserId, const FOnlinePartyId & PartyId, TArray<TSharedRef<const FUniqueNetId>>& OutApprovedUserIds)
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

    TSharedPtr<FOnlinePartyMember> NOnlinePartySystem::GetPartyMember(const FUniqueNetId & LocalUserId, const FOnlinePartyId & PartyId, const FUniqueNetId & MemberId) const
    {
        return TSharedPtr<FOnlinePartyMember>();
    }

    TSharedPtr<FOnlinePartyData> NOnlinePartySystem::GetPartyData(const FUniqueNetId & LocalUserId, const FOnlinePartyId & PartyId) const
    {
        return TSharedPtr<FOnlinePartyData>();
    }

    TSharedPtr<FOnlinePartyData> NOnlinePartySystem::GetPartyMemberData(const FUniqueNetId & LocalUserId, const FOnlinePartyId & PartyId, const FUniqueNetId & MemberId) const
    {
        return TSharedPtr<FOnlinePartyData>();
    }

    TSharedPtr<IOnlinePartyJoinInfo> NOnlinePartySystem::GetAdvertisedParty(const FUniqueNetId & LocalUserId, const FUniqueNetId & UserId, const FOnlinePartyTypeId PartyTypeId) const
    {
        return TSharedPtr<IOnlinePartyJoinInfo>();
    }

    bool NOnlinePartySystem::GetJoinedParties(const FUniqueNetId & LocalUserId, TArray<TSharedRef<const FOnlinePartyId>>& OutPartyIdArray) const
    {
        return false;
    }

    bool NOnlinePartySystem::GetPartyMembers(const FUniqueNetId & LocalUserId, const FOnlinePartyId & PartyId, TArray<TSharedRef<FOnlinePartyMember>>& OutPartyMembersArray) const
    {
        return false;
    }

    bool NOnlinePartySystem::GetPendingInvites(const FUniqueNetId & LocalUserId, TArray<TSharedRef<IOnlinePartyJoinInfo>>& OutPendingInvitesArray) const
    {
        return false;
    }

    bool NOnlinePartySystem::GetPendingJoinRequests(const FUniqueNetId & LocalUserId, const FOnlinePartyId & PartyId, TArray<TSharedRef<IOnlinePartyPendingJoinRequestInfo>>& OutPendingJoinRequestArray) const
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

    TSharedPtr<IOnlinePartyJoinInfo> NOnlinePartySystem::MakeJoinInfoFromJson(const FString & JoinInfoJson)
    {
        return TSharedPtr<IOnlinePartyJoinInfo>();
    }

    FString NOnlinePartySystem::MakeTokenFromJoinInfo(const IOnlinePartyJoinInfo & JoinInfo) const
    {
        return FString();
    }

    TSharedRef<IOnlinePartyJoinInfo> NOnlinePartySystem::MakeJoinInfoFromToken(const FString & Token) const
    {
        return MakeShared<NOnlinePartyJoinInfo>();
    }

    TSharedPtr<IOnlinePartyJoinInfo> NOnlinePartySystem::ConsumePendingCommandLineInvite()
    {
        return MakeShared<NOnlinePartyJoinInfo>();
    }

    void NOnlinePartySystem::DumpPartyState()
    {
    }

}
