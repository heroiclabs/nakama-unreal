#pragma once

//#include "NOnlineSubsystem/NOnlineSubsystem.h"
#include "OnlinePartyInterface.h"

namespace Nakama {

    ///
    /// Interface definition for the online party services.
    /// Allows for forming a party and communicating with party members.
    ///
    class NOnlinePartySystem : public IOnlinePartySystem
    {
    public:
        /**
         * Create a new party
         *
         * @param LocalUserId - user making the request
         * @param PartyConfig - configuration for the party (can be updated later)
         * @param Delegate - called on completion
         * @param UserRoomId - this forces the name of the room to be this value
         *
         * @return true if task was started
         */
        bool CreateParty(const FUniqueNetId& LocalUserId, const FOnlinePartyTypeId PartyTypeId, const FPartyConfiguration& PartyConfig, const FOnCreatePartyComplete& Delegate = FOnCreatePartyComplete()) override;

        /**
         * Update an existing party with new configuration
         *
         * @param LocalUserId - user making the request
         * @param PartyConfig - configuration for the party
         * @param Delegate - called on completion
         *
         * @return true if task was started
         */
        bool UpdateParty(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FPartyConfiguration& PartyConfig, bool bShouldRegenerateReservationKey = false, const FOnUpdatePartyComplete& Delegate = FOnUpdatePartyComplete()) override;

        /**
         * Join an existing party
         *
         * @param LocalUserId - user making the request
         * @param OnlinePartyJoinInfo - join information containing data such as party id, leader id
         * @param Delegate - called on completion
         *
         * @return true if task was started
         */
        bool JoinParty(const FUniqueNetId& LocalUserId, const IOnlinePartyJoinInfo& OnlinePartyJoinInfo, const FOnJoinPartyComplete& Delegate = FOnJoinPartyComplete()) override;

        /**
        * Join an existing game session from within a party
        *
        * @param LocalUserId - user making the request
        * @param OnlinePartyJoinInfo - join information containing data such as party id, leader id
        * @param Delegate - called on completion
        *
        * @return true if task was started
        */
        bool JIPFromWithinParty(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FUniqueNetId& PartyLeaderId) override;

        /**
         * Query a party to check it's current joinability
         * Intended to be used before a call to LeaveParty (to leave your existing party, which would then be followed by JoinParty)
         * Note that the party's joinability can change from moment to moment so a successful response for this does not guarantee a successful JoinParty
         *
         * @param LocalUserId - user making the request
         * @param OnlinePartyJoinInfo - join information containing data such as party id, leader id
         * @param Delegate - called on completion
         */
        void QueryPartyJoinability(const FUniqueNetId& LocalUserId, const IOnlinePartyJoinInfo& OnlinePartyJoinInfo, const FOnQueryPartyJoinabilityComplete& Delegate = FOnQueryPartyJoinabilityComplete()) override;

        /**
         * Attempt to rejoin a former party
         *
         * @param LocalUserId - user making the request
         * @param PartyId - id of the party you want to rejoin
         * @param PartyTypeId - type id of the party you want to rejoin
         * @param FormerMembers - array of former member ids that we can contact to try to rejoin the party
         * @param Delegate - called on completion
         *
         * @return true if task was started
         */
        bool RejoinParty(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FOnlinePartyTypeId& PartyTypeId, const TArray<TSharedRef<const FUniqueNetId>>& FormerMembers, const FOnJoinPartyComplete& Delegate = FOnJoinPartyComplete()) override;

        /**
         * Leave an existing party
         * All existing party members notified of member leaving (see FOnPartyMemberLeft)
         *
         * @param LocalUserId - user making the request
         * @param PartyId - id of an existing party
         * @param Delegate - called on completion
         *
         * @return true if task was started
         */
        bool LeaveParty(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FOnLeavePartyComplete& Delegate = FOnLeavePartyComplete()) override;

        /**
        * Approve a request to join a party
        *
        * @param LocalUserId - user making the request
        * @param PartyId - id of an existing party
        * @param RecipientId - id of the user being invited
        * @param bIsApproved - whether the join request was approved or not
        * @param DeniedResultCode - used when bIsApproved is false - client defined value to return when leader denies approval
        *
        * @return true if task was started
        */
        bool ApproveJoinRequest(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FUniqueNetId& RecipientId, bool bIsApproved, int32 DeniedResultCode = 0) override;

        /**
        * Approve a request to join the JIP match a party is in.
        *
        * @param LocalUserId - user making the request
        * @param PartyId - id of an existing party
        * @param RecipientId - id of the user being invited
        * @param bIsApproved - whether the join request was approved or not
        * @param DeniedResultCode - used when bIsApproved is false - client defined value to return when leader denies approval
        *
        * @return true if task was started
        */
        bool ApproveJIPRequest(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FUniqueNetId& RecipientId, bool bIsApproved, int32 DeniedResultCode = 0) override;

        /**
         * Respond to a query joinability request.  This reflects the current party's joinability state and can change from moment to moment, and therefore does not guarantee a successful join.
         *
         * @param LocalUserId - user making the request
         * @param PartyId - id of an existing party
         * @param RecipientId - id of the user being invited
         * @param bCanJoin - whether the player can attempt to join or not
         * @param DeniedResultCode - used when bCanJoin is false - client defined value to return when leader denies approval
         */
        void RespondToQueryJoinability(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FUniqueNetId& RecipientId, bool bCanJoin, int32 DeniedResultCode = 0) override;

        /**
         * sends an invitation to a user that could not otherwise join a party
         * if the player accepts the invite they will be sent the data needed to trigger a call to RequestReservation
         *
         * @param LocalUserId - user making the request
         * @param PartyId - id of an existing party
         * @param Recipient - structure specifying the recipient of the invitation
         * @param Delegate - called on completion
         *
         * @return true if task was started
         */
        bool SendInvitation(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FPartyInvitationRecipient& Recipient, const FOnSendPartyInvitationComplete& Delegate = FOnSendPartyInvitationComplete()) override;

        /**
         * Accept an invite to a party. NOTE this does not initiate a join.
         *
         * @param LocalUserId - user making the request
         * @param SenderId - id of the sender
         *
         * @return true if task was started
         */
        bool AcceptInvitation(const FUniqueNetId& LocalUserId, const FUniqueNetId& SenderId) override;

        /**
         * Reject an invite to a party
         *
         * @param LocalUserId - user making the request
         * @param SenderId - id of the sender
         *
         * @return true if task was started
         */
        bool RejectInvitation(const FUniqueNetId& LocalUserId, const FUniqueNetId& SenderId) override;

        /**
         * Clear invitations from a user because the invitations were handled by the application
         *
         * @param LocalUserId - user making the request
         * @param SenderId - id of the sender
         * @param PartyId - optional, if specified will clear only the one invitation, if blank all invitations from the sender will be cleared
         *
         * @return true if task was started
         */
        void ClearInvitations(const FUniqueNetId& LocalUserId, const FUniqueNetId& SenderId, const FOnlinePartyId* PartyId = nullptr) override;

        /**
         * Mark a user as approved to attempt to rejoin our party
         *
         * @param LocalUserId - user making the request
         * @param PartyId - party the player is approved to rejoin the party
         * @param ApprovedUserId - the user that has been approved to attempt to rejoin the party (does not need to be in the party now)
         */
        void ApproveUserForRejoin(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FUniqueNetId& ApprovedUserId) override;

        /**
         * Unmark a user as approved to attempt to rejoin our party
         *
         * @param LocalUserId - user making the request
         * @param PartyId - party the player is approved to rejoin the party
         * @param RemovedUserId - the user that has lost approval to attempt to rejoin the party
         */
        void RemoveUserForRejoin(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FUniqueNetId& RemovedUserId) override;

        /**
         * Get a list of users that have been approved for rejoining
         *
         * @param LocalUserId - user making the request
         * @param PartyId - party the player is approved to rejoin the party
         * @param OutApprovedUserIds - list of users that have been approved
         */
        void GetUsersApprovedForRejoin(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, TArray<TSharedRef<const FUniqueNetId>>& OutApprovedUserIds) override;

        /**
         * Kick a user from an existing party
         * Only admin can kick a party member
         *
         * @param LocalUserId - user making the request
         * @param PartyId - id of an existing party
         * @param MemberId - id of the user being kicked
         * @param Delegate - called on completion
         *
         * @return true if task was started
         */
        bool KickMember(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FUniqueNetId& TargetMemberId, const FOnKickPartyMemberComplete& Delegate = FOnKickPartyMemberComplete()) override;

        /**
         * Promote a user from an existing party to be admin
         * All existing party members notified of promoted member (see FOnPartyMemberPromoted)
         *
         * @param LocalUserId - user making the request
         * @param PartyId - id of an existing party
         * @param MemberId - id of the user being promoted
         * @param Delegate - called on completion
         *
         * @return true if task was started
         */
        bool PromoteMember(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FUniqueNetId& TargetMemberId, const FOnPromotePartyMemberComplete& Delegate = FOnPromotePartyMemberComplete()) override;

        /**
         * Set party data and broadcast to all members
         * Only current data can be set and no history of past party data is preserved
         * Party members notified of new data (see FOnPartyDataReceived)
         *
         * @param LocalUserId - user making the request
         * @param PartyId - id of an existing party
         * @param PartyData - data to send to all party members
         * @param Delegate - called on completion
         *
         * @return true if task was started
         */
        bool UpdatePartyData(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FOnlinePartyData& PartyData) override;

        /**
         * Set party data for a single party member and broadcast to all members
         * Only current data can be set and no history of past party member data is preserved
         * Party members notified of new data (see FOnPartyMemberDataReceived)
         *
         * @param LocalUserId - user making the request
         * @param PartyId - id of an existing party
         * @param PartyMemberData - member data to send to all party members
         * @param Delegate - called on completion
         *
         * @return true if task was started
         */
        bool UpdatePartyMemberData(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FOnlinePartyData& PartyMemberData) override;

        /**
         * returns true if the user specified by MemberId is the leader of the party specified by PartyId
         *
         * @param LocalUserId - user making the request
         * @param PartyId     - id of an existing party
         * @param MemberId    - id of member to test
         *
         */
        bool IsMemberLeader(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FUniqueNetId& MemberId) const override;

        /**
         * returns the number of players in a given party
         *
         * @param LocalUserId - user making the request
         * @param PartyId     - id of an existing party
         *
         */
        uint32 GetPartyMemberCount(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId) const override;

        /**
         * Get info associated with a party
         *
         * @param LocalUserId - user making the request
         * @param PartyId     - id of an existing party
         *
         * @return party info or nullptr if not found
         */
        TSharedPtr<const FOnlineParty> GetParty(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId) const override;

        /**
         * Get info associated with a party
         *
         * @param LocalUserId - user making the request
         * @param PartyTypeId - type of an existing party
         *
         * @return party info or nullptr if not found
         */
        TSharedPtr<const FOnlineParty> GetParty(const FUniqueNetId& LocalUserId, const FOnlinePartyTypeId& PartyTypeId) const override;

        /**
         * Get a party member by id
         *
         * @param LocalUserId - user making the request
         * @param PartyId     - id of an existing party
         * @param MemberId    - id of member to find
         *
         * @return party member info or nullptr if not found
         */
        TSharedPtr<FOnlinePartyMember> GetPartyMember(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FUniqueNetId& MemberId) const override;

        /**
         * Get current cached data associated with a party
         * FOnPartyDataReceived notification called whenever this data changes
         *
         * @param LocalUserId - user making the request
         * @param PartyId     - id of an existing party
         *
         * @return party data or nullptr if not found
         */
        TSharedPtr<FOnlinePartyData> GetPartyData(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId) const override;

        /**
         * Get current cached data associated with a party member
         * FOnPartyMemberDataReceived notification called whenever this data changes
         *
         * @param LocalUserId - user making the request
         * @param PartyId     - id of an existing party
         * @param MemberId    - id of member to find data for
         *
         * @return party member data or nullptr if not found
         */
        TSharedPtr<FOnlinePartyData> GetPartyMemberData(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FUniqueNetId& MemberId) const override;

        /**
         * Get the join info of the specified user and party type
         *
         * @param LocalUserId       - user making the request
         * @param UserId            - user to check
         * @param PartyTypeId       - type of party to query
         *
         * @return shared pointer to the join info if the user is advertising for that party type
         */
        TSharedPtr<IOnlinePartyJoinInfo> GetAdvertisedParty(const FUniqueNetId& LocalUserId, const FUniqueNetId& UserId, const FOnlinePartyTypeId PartyTypeId) const override;

        /**
         * Get a list of currently joined parties for the user
         *
         * @param LocalUserId     - user making the request
         * @param OutPartyIdArray - list of party ids joined by the current user
         *
         * @return true if entries found
         */
        bool GetJoinedParties(const FUniqueNetId& LocalUserId, TArray<TSharedRef<const FOnlinePartyId>>& OutPartyIdArray) const override;

        /**
         * Get list of current party members
         *
         * @param LocalUserId          - user making the request
         * @param PartyId              - id of an existing party
         * @param OutPartyMembersArray - list of party members currently in the party
         *
         * @return true if entries found
         */
        bool GetPartyMembers(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, TArray<TSharedRef<FOnlinePartyMember>>& OutPartyMembersArray) const override;

        /**
         * Get a list of parties the user has been invited to
         *
         * @param LocalUserId            - user making the request
         * @param OutPendingInvitesArray - list of party info needed to join the party
         *
         * @return true if entries found
         */
        bool GetPendingInvites(const FUniqueNetId& LocalUserId, TArray<TSharedRef<IOnlinePartyJoinInfo>>& OutPendingInvitesArray) const override;

        /**
         * Get list of users requesting to join the party
         *
         * @param LocalUserId           - user making the request
         * @param PartyId               - id of an existing party
         * @param OutPendingUserIdArray - list of pending party members
         *
         * @return true if entries found
         */
        bool GetPendingJoinRequests(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, TArray<TSharedRef<IOnlinePartyPendingJoinRequestInfo>>& OutPendingJoinRequestArray) const override;

        /**
         * Get list of users invited to a party that have not yet responded
         *
         * @param LocalUserId                - user making the request
         * @param PartyId                    - id of an existing party
         * @param OutPendingInvitedUserArray - list of user that have pending invites
         *
         * @return true if entries found
         */
        bool GetPendingInvitedUsers(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, TArray<TSharedRef<const FUniqueNetId>>& OutPendingInvitedUserArray) const override;

        /**
         * returns the json version of a join info for a current party
         *
         * @param LocalUserId       - user making the request
         * @param PartyId           - party to make the json from
         *
         */
        FString MakeJoinInfoJson(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId) override;

        /**
         * returns a valid join info object from a json blob
         *
         * @param JoinInfoJson       - json blob to convert
         *
         */
        TSharedPtr<IOnlinePartyJoinInfo> MakeJoinInfoFromJson(const FString& JoinInfoJson) override;

        /**
         * Creates a command line token from a IOnlinePartyJoinInfo object
         *
         * @param JoinInfo - the IOnlinePartyJoinInfo object to convert
         *
         * return the new IOnlinePartyJoinInfo object
         */
        FString MakeTokenFromJoinInfo(const IOnlinePartyJoinInfo& JoinInfo) const override;

        /**
         * Creates a IOnlinePartyJoinInfo object from a command line token
         *
         * @param Token - the token string
         *
         * return the new IOnlinePartyJoinInfo object
         */
        TSharedRef<IOnlinePartyJoinInfo> MakeJoinInfoFromToken(const FString& Token) const override;

        /**
         * Checks to see if there is a pending command line invite and consumes it
         *
         * return the pending IOnlinePartyJoinInfo object
         */
        TSharedPtr<IOnlinePartyJoinInfo> ConsumePendingCommandLineInvite() override;

        /**
         * Dump out party state for all known parties
         */
        void DumpPartyState() override;

    };

}
