// Copyright 2019 The Nakama Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

package online_party_system

import (
	"context"
	"database/sql"
	"encoding/json"
	"strings"
	"time"

	"github.com/heroiclabs/nakama-common/runtime"
)

const (
	TickRate         = 1
	InitialJoinTicks = 60
)

const (
	OpCodeTerminate   = iota // Server -> client when the party is being terminated by the server.
	OpCodeJoinRequest        // Server -> client when a user requests to join the party.

	OpCodeApproveForRejoin
	OpCodeApproveJoinRequest
	OpCodeClearInvitations
	OpCodeGetPartyData
	OpCodeGetPartyMemberData
	OpCodeGetPendingInvitedUsers
	OpCodeGetPendingJoinRequests
	OpCodeGetUsersApprovedForRejoin
	OpCodeIsMemberLeader
	OpCodeKickMember
	OpCodePromoteMember
	OpCodeRejectInvitation
	OpCodeRemoveUserForRejoin
	OpCodeSendInvitation
	OpCodeUpdateParty
	OpCodeUpdatePartyData
	OpCodeUpdatePartyMemberData

	OpCodePartyMessageResponse
)

const (
	ResponseCodeSuccess = iota
	ResponseCodeNotPartyLeader
	ResponseCodeBadRequest
	ResponseCodeInternalError
	ResponseCodeUserOffline
	ResponseCodePresenceError
	ResponseCodeInvitePending
	ResponseCodeNoInvitePending
	ResponseCodeUserBlocked
)

type PartyMatchMessage struct {
	Id   *int64 `json:"id"`
	Data []byte `json:"data"`
}

type PartyMessageResponse struct {
	Id           int64 `json:"id"`
	ResponseCode int64 `json:"response_code"`
}

type PartyMatchLabel struct {
	OnlinePartyTypeId int64                        `json:"type_id,omitempty"`
	Members           []string                     `json:"members,omitempty"`
	Metadata          map[string]map[string]string `json:"metadata,omitempty"`
	Config            string                       `json:"config,omitempty"`
}

type PartyMatchState struct {
	version           string                       // Party version, all join requests must match if set or they'll be rejected
	leader            runtime.Presence             // Identity of the current party leader. May change over the lifetime of the party.
	presences         map[string]runtime.Presence  // Map of user IDs to presences. Keyed on user ID because multiple devices per user per party are not allowed.
	partyData         []byte                       // Arbitrary party data.
	partyMemberData   map[string][]byte            // Arbitrary party member data.
	approvedForRejoin map[string]struct{}          // User IDs approved for rejoin.
	invitations       map[string]time.Time         // User IDs to expiration time for users that have been invited.
	joinRequests      map[string]runtime.Presence  // User IDs that have requested to join the party.
	joinMetadata      map[string]map[string]string // User IDs to metadata mapping.

	blockedUsersCache map[string][]string // for each user a list of blocked users. Used to create the blockedUsersSet set below
	blockedUsersSet   map[string]struct{} // Set of users that are blocked from joining (this set is created from users blocked friends as they are invited)
	blockedUsersDirty bool                // Do we need to re-build the blocked-list (happens when a user leaves)

	label             *PartyMatchLabel // Label exposed to Nakama's match listing system.
	creator           string           // Party creator user ID, used to allow the user to automatically join when they create.
	initialEmptyTicks int              // Number of ticks the party has been empty on creation, to ensure parties are cleaned up if their creator never joins.
}

type PartyConfig struct {
	MaxSize                 int                     // Maximum number of members allowed in party
	InviteDuration          time.Duration           // Duration an invite should last before expiring. default 0 = no expiration
	MatchJoinMetadataFilter MatchJoinMetadataFilter //
	MatchEndHook            MatchEndHook            // Called when the party match is over
	MatchInitHook           MatchInitHook           // Called when the party match is initialized
	MatchJoinAttemptHook    MatchJoinAttemptHook    // Called when a user attempts to join the party
	MatchKickHook           MatchKickHook           // Called when a party member is kicked from the party
	MatchLeaveHook          MatchLeaveHook          // Called when a party member leaves the party
}

type PartyMatch struct {
	config PartyConfig
}

func getBlockedFriendsWithCache(ctx context.Context, logger runtime.Logger, nk runtime.NakamaModule, userID string, cache map[string][]string) []string {

	cached, ok := cache[userID]
	if ok {
		return cached
	}

	friendLimit := 100
	friendState := 3 // 3 is Friend_BLOCKED
	cursor := ""     // no cursor

	friendsPtrArray, cursor, err := nk.FriendsList(ctx, userID, friendLimit, &friendState, cursor)
	if err != nil {
		logger.Error("Error getting FriendsList: %v", err)
		return nil
	}

	blockedFriends := make([]string, 0, len(friendsPtrArray))

	for _, friendPtr := range friendsPtrArray {
		friend := *friendPtr
		user := friend.User
		userID := user.Id
		blockedFriends = append(blockedFriends, userID)
	}

	// store in cache
	cache[userID] = blockedFriends
	return blockedFriends
}

// a relevant user is someone 1. in the party or, 2. invited to the party or 3. approved for rejoin
func getRelevantUsers(s *PartyMatchState) map[string]struct{} {
	relevantUsers := make(map[string]struct{})
	for userID := range s.presences {
		relevantUsers[userID] = struct{}{}
	}

	for userID := range s.invitations {
		relevantUsers[userID] = struct{}{}
	}

	for userID := range s.approvedForRejoin {
		relevantUsers[userID] = struct{}{}
	}

	return relevantUsers
}

func isUnblocked(ctx context.Context, logger runtime.Logger, nk runtime.NakamaModule, userID string, s *PartyMatchState) (bool, string) {

	var relevantUsers map[string]struct{}

	// rebuild if dirty
	if s.blockedUsersDirty {
		s.blockedUsersDirty = false

		// re-set blockedUsers
		s.blockedUsersSet = make(map[string]struct{})

		// collect all users whose blocked-list should be considered (new users were invited or some left) (this is reused below if needed)
		relevantUsers = getRelevantUsers(s)
		for relevantUserID := range relevantUsers {
			blockedListFromRelevantUser := getBlockedFriendsWithCache(ctx, logger, nk, relevantUserID, s.blockedUsersCache)

			for _, blockedUser := range blockedListFromRelevantUser {
				s.blockedUsersSet[blockedUser] = struct{}{}
			}
		}
	}

	// Test if anyone "in" the party has blocked this user
	if _, ok := s.blockedUsersSet[userID]; ok {
		return false, "Someone in this party blocked you (re-phrase this)"
	}

	// Test if this user has blocked anyone invited to this party
	blockedListFromUser := getBlockedFriendsWithCache(ctx, logger, nk, userID, s.blockedUsersCache)

	// local set created from the list
	blockedSet := make(map[string]struct{})
	for _, userID := range blockedListFromUser {
		blockedSet[userID] = struct{}{}
	}

	if relevantUsers == nil {
		relevantUsers = getRelevantUsers(s)
	}

	for userID := range relevantUsers {
		if _, ok := blockedSet[userID]; ok {
			return false, "You have blocked someone in (or invited to) this party (re-phrase this)"
		}
	}

	return true, ""
}

func (p *PartyMatch) cleanupExpiredInvitations(ctx context.Context, nk runtime.NakamaModule, s *PartyMatchState) error {
	if p.config.InviteDuration.Nanoseconds() > 0 {
		now := time.Now()
		subject := "Party expired invitation"
		for memberId, expiration := range s.invitations {
			if now.After(expiration) {
				delete(s.invitations, memberId)
				content := map[string]interface{}{
					"party_id":  ctx.Value(runtime.RUNTIME_CTX_MATCH_ID).(string),
					"member_id": memberId,
				}
				if err := p.sendPartyNotification(ctx, nk, s, subject, content); err != nil {
					return err
				}
				if err := nk.NotificationSend(ctx, memberId, subject, content, 1, "", false); err != nil {
					return err
				}
			}
		}
	}
	return nil
}

func (p *PartyMatch) sendPartyNotification(ctx context.Context, nk runtime.NakamaModule, s *PartyMatchState, subject string, content map[string]interface{}) error {
	//Prepare notification for each presence
	notifications := make([]*runtime.NotificationSend, 0, len(s.presences))
	for _, presence := range s.presences {
		notification := &runtime.NotificationSend{
			UserID:     presence.GetUserId(),
			Subject:    subject,
			Content:    content,
			Code:       1,
			Persistent: false,
		}
		notifications = append(notifications, notification)
	}

	return nk.NotificationsSend(ctx, notifications)
}

func (p *PartyMatch) MatchInit(ctx context.Context, logger runtime.Logger, db *sql.DB, nk runtime.NakamaModule, params map[string]interface{}) (interface{}, int, string) {
	creator, ok := params["creator"].(string)
	if !ok {
		logger.Error("Error creating party, no creator in params")
		return nil, 0, ""
	}
	typeId, ok := params["type_id"].(int64)
	if !ok {
		logger.Error("Error creating party, no type_id in params")
		return nil, 0, ""
	}
	config, ok := params["config"].(string)
	if !ok {
		logger.Error("Error creating party, no config in params")
		return nil, 0, ""
	}

	label := &PartyMatchLabel{
		OnlinePartyTypeId: typeId,
		Members:           make([]string, 0, 5),
		Config:            config,
	}
	labelBytes, err := json.Marshal(label)
	if err != nil {
		logger.Error("Error creating party, cannot encode label: %v", err)
		return nil, 0, ""
	}

	state := &PartyMatchState{
		leader:            nil,
		presences:         make(map[string]runtime.Presence),
		partyData:         nil,
		partyMemberData:   make(map[string][]byte),
		approvedForRejoin: make(map[string]struct{}),
		invitations:       make(map[string]time.Time),
		joinRequests:      make(map[string]runtime.Presence),
		joinMetadata:      make(map[string]map[string]string),
		blockedUsersCache: make(map[string][]string),
		blockedUsersSet:   make(map[string]struct{}),
		blockedUsersDirty: false,

		label:             label,
		creator:           creator,
		initialEmptyTicks: 0,
	}
	if p.config.MatchInitHook != nil {
		matchID := ctx.Value(runtime.RUNTIME_CTX_MATCH_ID).(string)
		p.config.MatchInitHook(matchID, p.config, label)
	}
	return state, TickRate, string(labelBytes)
}

func (p *PartyMatch) MatchJoinAttempt(ctx context.Context, logger runtime.Logger, db *sql.DB, nk runtime.NakamaModule, dispatcher runtime.MatchDispatcher, tick int64, state interface{}, presence runtime.Presence, metadata map[string]string) (interface{}, bool, string) {
	s := state.(*PartyMatchState)

	// Ensure users can only join each party once concurrently.
	// This prevents concurrent joins from multiple devices, for example.
	if _, ok := s.presences[presence.GetUserId()]; ok {
		return s, false, "Party already joined"
	}

	// Implicitly allow the party creator to join for the first time.
	if s.creator != "" && presence.GetUserId() == s.creator {
		s.leader = presence
		s.creator = ""
		s.initialEmptyTicks = 0

		s.joinMetadata[presence.GetUserId()] = p.config.MatchJoinMetadataFilter(metadata)

		// Party leader determines the party version
		if version, ok := metadata["version"]; ok {
			s.version = version
		}

		// creator adds their blocked users to the party
		getBlockedFriendsWithCache(ctx, logger, nk, presence.GetUserId(), s.blockedUsersCache)
		s.blockedUsersDirty = true
		return s, true, ""
	}

	// Reject any joins that have a version mismatch
	if s.version != "" {
		version, ok := metadata["version"]
		if !ok || version != s.version {
			return s, false, "Bad version"
		}
	}

	// Reject any joins that would exceed party size
	if p.config.MaxSize > 0 && len(s.presences) >= p.config.MaxSize {
		return s, false, "Party is full"
	}

	// Ensure join metadata is stored to be used in MatchJoin callback.
	s.joinMetadata[presence.GetUserId()] = p.config.MatchJoinMetadataFilter(metadata)

	unblocked, blockedReason := isUnblocked(ctx, logger, nk, presence.GetUserId(), s)
	if !unblocked {
		return s, false, blockedReason
	}

	// Allow approved rejoins.
	if _, ok := s.approvedForRejoin[presence.GetUserId()]; ok {
		delete(s.approvedForRejoin, presence.GetUserId())
		return s, true, ""
	}

	// Allow users that have an unexpired invitation
	if err := p.cleanupExpiredInvitations(ctx, nk, s); err != nil {
		logger.Warn("Error sending expired invitation notifs: %v", err)
	}
	if _, ok := s.invitations[presence.GetUserId()]; ok {
		delete(s.invitations, presence.GetUserId())
		return s, true, ""
	}

	// Everyone else must be approved by the party leader.
	s.joinRequests[presence.GetUserId()] = presence
	if err := dispatcher.BroadcastMessage(OpCodeJoinRequest, nil, []runtime.Presence{s.leader}, presence, true); err != nil {
		logger.Warn("Error broadcasting join request to party leader: %v", err)
		return s, false, "Failed sending join request to leader"
	}
	if p.config.MatchJoinAttemptHook != nil {
		matchID := ctx.Value(runtime.RUNTIME_CTX_MATCH_ID).(string)
		allow, msg := p.config.MatchJoinAttemptHook(matchID, presence, metadata)
		return s, allow, msg
	}
	return s, false, "Join request sent"
}

func (p *PartyMatch) MatchJoin(ctx context.Context, logger runtime.Logger, db *sql.DB, nk runtime.NakamaModule, dispatcher runtime.MatchDispatcher, tick int64, state interface{}, presences []runtime.Presence) interface{} {
	s := state.(*PartyMatchState)

	// Reaching this stage means the party member join was either approved by the leader or implicitly by the rejoin list.
	for _, presence := range presences {
		userId := presence.GetUserId()
		s.presences[userId] = presence

		s.label.Members = append(s.label.Members, userId)
		if s.label.Metadata == nil {
			s.label.Metadata = make(map[string]map[string]string)
		}
		s.label.Metadata[userId] = s.joinMetadata[userId]

		delete(s.joinMetadata, userId)
	}

	// Update the match label.
	labelBytes, err := json.Marshal(s.label)
	if err != nil {
		logger.Warn("Error updating label on join, cannot encode label: %v", err)
		return s
	}
	if err := dispatcher.MatchLabelUpdate(string(labelBytes)); err != nil {
		logger.Warn("Error updating label on join, cannot update label: %v", err)
	}

	// NOTE: Join notifications are already sent automatically by the server.

	return s
}

func (p *PartyMatch) MatchLeave(ctx context.Context, logger runtime.Logger, db *sql.DB, nk runtime.NakamaModule, dispatcher runtime.MatchDispatcher, tick int64, state interface{}, presences []runtime.Presence) interface{} {
	s := state.(*PartyMatchState)

	// when usesr leave we need to update out blocked-list
	s.blockedUsersDirty = true

	// User has either left voluntarily or disconnected.
	for _, presence := range presences {
		leftUserId := presence.GetUserId()
		delete(s.presences, leftUserId)
		delete(s.partyMemberData, leftUserId)

		for i := 0; i < len(s.label.Members); i++ {
			if s.label.Members[i] == leftUserId {
				s.label.Members[i] = s.label.Members[len(s.label.Members)-1]
				s.label.Members = s.label.Members[:len(s.label.Members)-1]
				break
			}
		}
		delete(s.label.Metadata, leftUserId)

		// If this was the party leader elect a new one randomly.
		if leftUserId == s.leader.GetUserId() {
			for remainingUserId, remainingPresence := range s.presences {
				if remainingUserId != leftUserId {
					s.leader = remainingPresence
					// Notify the party about the new leader.
					if err := dispatcher.BroadcastMessage(OpCodePromoteMember, nil, nil, remainingPresence, true); err != nil {
						logger.Warn("Error broadcasting member promotion: %v", err)
					}
					break
				}
			}
		}

		if p.config.MatchLeaveHook != nil {
			matchID := ctx.Value(runtime.RUNTIME_CTX_MATCH_ID).(string)
			p.config.MatchLeaveHook(matchID, leftUserId)
		}
	}

	// If the party is now empty stop it now.
	if len(s.presences) == 0 {
		if p.config.MatchEndHook != nil {
			matchID := ctx.Value(runtime.RUNTIME_CTX_MATCH_ID).(string)
			p.config.MatchEndHook(matchID, p.config, s.label)
		}
		return nil
	}

	// Update the match label.
	labelBytes, err := json.Marshal(s.label)
	if err != nil {
		logger.Warn("Error updating label on leave, cannot encode label: %v", err)
		return s
	}
	if err := dispatcher.MatchLabelUpdate(string(labelBytes)); err != nil {
		logger.Warn("Error updating label on leave, cannot update label: %v", err)
	}

	return s
}

func (p *PartyMatch) MatchLoop(ctx context.Context, logger runtime.Logger, db *sql.DB, nk runtime.NakamaModule, dispatcher runtime.MatchDispatcher, tick int64, state interface{}, messages []runtime.MatchData) interface{} {
	s := state.(*PartyMatchState)

	// Check if the party has been sitting empty since creation.
	if s.creator != "" && len(s.presences) == 0 {
		s.initialEmptyTicks++
		if s.initialEmptyTicks >= InitialJoinTicks {
			if p.config.MatchEndHook != nil {
				matchID := ctx.Value(runtime.RUNTIME_CTX_MATCH_ID).(string)
				p.config.MatchEndHook(matchID, p.config, s.label)
			}
			return nil
		}
	}

	// Cleanup expired party invitations
	if err := p.cleanupExpiredInvitations(ctx, nk, s); err != nil {
		logger.Warn("Error sending expired invitation notifs: %v", err)
	}

	// Process messages one by one.
	// Currently any unknown, malformed, or unexpected messages are just ignored.
	for _, message := range messages {

		var partyMsg PartyMatchMessage
		err := json.Unmarshal(message.GetData(), &partyMsg)
		if err != nil {
			logger.Warn("Unable to unmarshal PartyMatchMessage: %v", err)
			continue
		}

		switch message.GetOpCode() {
		case OpCodeApproveForRejoin:
			// Leader only action.
			if s.leader.GetUserId() != message.GetUserId() {
				SendResponse(partyMsg, ResponseCodeNotPartyLeader, []runtime.Presence{message}, logger, dispatcher)
				continue
			}

			// can not approve a blocked user
			unblocked, _ := isUnblocked(ctx, logger, nk, string(partyMsg.Data), s)
			if !unblocked {
				SendResponse(partyMsg, ResponseCodeUserBlocked, []runtime.Presence{message}, logger, dispatcher)
				continue
			}

			// Expects message data payload to be a user ID string to be approved for rejoin.
			s.approvedForRejoin[string(partyMsg.Data)] = struct{}{}
			s.blockedUsersDirty = true

		case OpCodeApproveJoinRequest:
			// Leader only action.
			if s.leader.GetUserId() != message.GetUserId() {
				SendResponse(partyMsg, ResponseCodeNotPartyLeader, []runtime.Presence{message}, logger, dispatcher)
				continue
			}

			// Expects message data payload to be a user ID string to be approved for join.
			if presence, ok := s.joinRequests[string(partyMsg.Data)]; ok {
				delete(s.joinRequests, string(partyMsg.Data))
				// Note: do not remove entry from joinMetadata, it will be cleaned up when the join completes.

				// Add the user to the match stream. This will lead to MatchJoin being triggered.
				matchIdComponents := strings.SplitN(ctx.Value(runtime.RUNTIME_CTX_MATCH_ID).(string), ".", 2)
				if len(matchIdComponents) != 2 {
					logger.Error("Error parsing match ID into components")
					SendResponse(partyMsg, ResponseCodeInternalError, []runtime.Presence{message}, logger, dispatcher)
					continue
				}
				if _, err := nk.StreamUserJoin(6, matchIdComponents[0], "", matchIdComponents[1], presence.GetUserId(), presence.GetSessionId(), false, false, ""); err != nil {
					logger.Warn("Error adding user to match stream after party join request approved: %v", err)
					SendResponse(partyMsg, ResponseCodeInternalError, []runtime.Presence{message}, logger, dispatcher)
					continue
				}
			}
		case OpCodeClearInvitations:
			// Leader only action.
			if s.leader.GetUserId() != message.GetUserId() {
				SendResponse(partyMsg, ResponseCodeNotPartyLeader, []runtime.Presence{message}, logger, dispatcher)
				continue
			}

			s.invitations = make(map[string]time.Time)
			s.blockedUsersDirty = true
		case OpCodeGetPartyData:
			if err := dispatcher.BroadcastMessage(OpCodeGetPartyData, s.partyData, []runtime.Presence{message}, nil, true); err != nil {
				logger.Warn("Error broadcasting party data: %v", err)
				SendResponse(partyMsg, ResponseCodeInternalError, []runtime.Presence{message}, logger, dispatcher)
				continue
			}
		case OpCodeGetPartyMemberData:
			// Expects message data payload to be a user ID string to retrieve party member data for.
			presence, ok := s.presences[string(partyMsg.Data)]
			if !ok {
				SendResponse(partyMsg, ResponseCodeBadRequest, []runtime.Presence{message}, logger, dispatcher)
				continue
			}

			if err := dispatcher.BroadcastMessage(OpCodeGetPartyMemberData, s.partyMemberData[string(partyMsg.Data)], []runtime.Presence{message}, presence, true); err != nil {
				logger.Warn("Error broadcasting party member data: %v", err)
				SendResponse(partyMsg, ResponseCodeInternalError, []runtime.Presence{message}, logger, dispatcher)
				continue
			}
		case OpCodeGetPendingInvitedUsers:
			invitations := make([]string, 0, len(s.invitations))
			for userId, _ := range s.invitations {
				invitations = append(invitations, userId)
			}

			data, err := json.Marshal(invitations)
			if err != nil {
				logger.Warn("Error encoding invitations: %v", err)
				SendResponse(partyMsg, ResponseCodeInternalError, []runtime.Presence{message}, logger, dispatcher)
				continue
			}

			// Outgoing data payload will be a JSON array of user IDs.
			if err := dispatcher.BroadcastMessage(OpCodeGetPendingInvitedUsers, data, []runtime.Presence{message}, nil, true); err != nil {
				logger.Warn("Error broadcasting pending invited users: %v", err)
				SendResponse(partyMsg, ResponseCodeInternalError, []runtime.Presence{message}, logger, dispatcher)
				continue
			}
		case OpCodeGetPendingJoinRequests:
			joinRequests := make([]string, 0, len(s.joinRequests))
			for userId, _ := range s.joinRequests {
				joinRequests = append(joinRequests, userId)
			}

			data, err := json.Marshal(joinRequests)
			if err != nil {
				logger.Warn("Error encoding join requests: %v", err)
				SendResponse(partyMsg, ResponseCodeInternalError, []runtime.Presence{message}, logger, dispatcher)
				continue
			}

			// Outgoing data payload will be a JSON array of user IDs.
			if err := dispatcher.BroadcastMessage(OpCodeGetPendingJoinRequests, data, []runtime.Presence{message}, nil, true); err != nil {
				logger.Warn("Error broadcasting pending join requests: %v", err)
				SendResponse(partyMsg, ResponseCodeInternalError, []runtime.Presence{message}, logger, dispatcher)
				continue
			}
		case OpCodeGetUsersApprovedForRejoin:
			approvedRejoins := make([]string, 0, len(s.approvedForRejoin))
			for userId, _ := range s.approvedForRejoin {
				approvedRejoins = append(approvedRejoins, userId)
			}

			data, err := json.Marshal(approvedRejoins)
			if err != nil {
				logger.Warn("Error encoding approved for rejoin: %v", err)
				SendResponse(partyMsg, ResponseCodeInternalError, []runtime.Presence{message}, logger, dispatcher)
				continue
			}

			// Outgoing data payload will be a JSON array of user IDs.
			if err := dispatcher.BroadcastMessage(OpCodeGetUsersApprovedForRejoin, data, []runtime.Presence{message}, nil, true); err != nil {
				logger.Warn("Error broadcasting users approved for rejoin: %v", err)
				SendResponse(partyMsg, ResponseCodeInternalError, []runtime.Presence{message}, logger, dispatcher)
				continue
			}
		case OpCodeIsMemberLeader:
			// Expects message data payload to be a user ID string to check if it's the party leader.
			isPartyLeader := "false"
			if s.leader.GetUserId() == string(partyMsg.Data) {
				isPartyLeader = "true"
			}

			// Outgoing data payload will contain the strings "true" or "false".
			if err := dispatcher.BroadcastMessage(OpCodeIsMemberLeader, []byte(isPartyLeader), []runtime.Presence{message}, nil, true); err != nil {
				logger.Warn("Error broadcasting is member leader: %v", err)
				SendResponse(partyMsg, ResponseCodeInternalError, []runtime.Presence{message}, logger, dispatcher)
				continue
			}
		case OpCodeKickMember:
			// Leader only action.
			if s.leader.GetUserId() != message.GetUserId() {
				SendResponse(partyMsg, ResponseCodeNotPartyLeader, []runtime.Presence{message}, logger, dispatcher)
				continue
			}

			// Expects message data payload to be a user ID string to be kicked.
			if presence, ok := s.presences[string(partyMsg.Data)]; ok {
				if err := dispatcher.BroadcastMessage(OpCodeKickMember, nil, nil, presence, true); err != nil {
					logger.Warn("Error broadcasting party member kicked: %v", err)
					SendResponse(partyMsg, ResponseCodeInternalError, []runtime.Presence{message}, logger, dispatcher)
					continue
				}
				if err := dispatcher.MatchKick([]runtime.Presence{presence}); err != nil {
					logger.Warn("Error kicking party member: %v", err)
					SendResponse(partyMsg, ResponseCodeInternalError, []runtime.Presence{message}, logger, dispatcher)
					continue
				}

				delete(s.presences, presence.GetUserId())
				delete(s.partyMemberData, presence.GetUserId())

				if p.config.MatchKickHook != nil {
					matchID := ctx.Value(runtime.RUNTIME_CTX_MATCH_ID).(string)
					p.config.MatchKickHook(matchID, presence.GetUserId())
				}
			} else {
				logger.Warn("Error getting presence for kick: %s", string(partyMsg.Data))
				SendResponse(partyMsg, ResponseCodePresenceError, []runtime.Presence{message}, logger, dispatcher)
				continue
			}
		case OpCodePromoteMember:
			// Leader only action.
			if s.leader.GetUserId() != message.GetUserId() {
				SendResponse(partyMsg, ResponseCodeNotPartyLeader, []runtime.Presence{message}, logger, dispatcher)
				continue
			}

			// Expects message data payload to be a user ID string to be promoted.
			if presence, ok := s.presences[string(partyMsg.Data)]; ok {
				if err := dispatcher.BroadcastMessage(OpCodePromoteMember, nil, nil, presence, true); err != nil {
					logger.Warn("Error broadcasting party member promote: %v", err)
				}

				s.leader = presence
			}
		case OpCodeRejectInvitation:
			// Leader only action.
			if s.leader.GetUserId() != message.GetUserId() {
				SendResponse(partyMsg, ResponseCodeNotPartyLeader, []runtime.Presence{message}, logger, dispatcher)
				continue
			}

			userId := string(partyMsg.Data)
			if _, ok := s.invitations[userId]; !ok {
				// No invite to reject
				SendResponse(partyMsg, ResponseCodeNoInvitePending, []runtime.Presence{message}, logger, dispatcher)
				continue
			}
			delete(s.invitations, userId)
		case OpCodeRemoveUserForRejoin:
			// Leader only action.
			if s.leader.GetUserId() != message.GetUserId() {
				SendResponse(partyMsg, ResponseCodeNotPartyLeader, []runtime.Presence{message}, logger, dispatcher)
				continue
			}

			// Expects message data payload to be a user ID string to be removed for rejoin.
			delete(s.approvedForRejoin, string(partyMsg.Data))
			s.blockedUsersDirty = true
		case OpCodeSendInvitation:
			// Leader only action.
			if s.leader.GetUserId() != message.GetUserId() {
				SendResponse(partyMsg, ResponseCodeNotPartyLeader, []runtime.Presence{message}, logger, dispatcher)
				continue
			}

			var invitedUserId = string(partyMsg.Data)
			if s.leader.GetUserId() == invitedUserId {
				// Leader inviting itself, already ok to join, do not send notification
				SendResponse(partyMsg, ResponseCodeInternalError, []runtime.Presence{message}, logger, dispatcher)
				continue
			}

			if _, ok := s.invitations[invitedUserId]; ok {
				// Invite is already pending
				SendResponse(partyMsg, ResponseCodeInvitePending, []runtime.Presence{message}, logger, dispatcher)
				continue
			}

			// Check if user is online in the notification stream
			count, err := nk.StreamCount(0, invitedUserId, "", "")
			if err != nil {
				logger.Warn("Error counting stream presences during party invitation: %v", err)
				SendResponse(partyMsg, ResponseCodeInternalError, []runtime.Presence{message}, logger, dispatcher)
				continue
			}
			if count <= 0 {
				// User is not online. It's possible this user is not valid
				SendResponse(partyMsg, ResponseCodeUserOffline, []runtime.Presence{message}, logger, dispatcher)
				continue
			}

			// can not invite if have been blocked
			unblocked, _ := isUnblocked(ctx, logger, nk, invitedUserId, s)
			if !unblocked {
				SendResponse(partyMsg, ResponseCodeUserBlocked, []runtime.Presence{message}, logger, dispatcher)
				continue
			}

			// Expects message data payload to be a user ID string to be invited.
			content := map[string]interface{}{
				"match_id": ctx.Value(runtime.RUNTIME_CTX_MATCH_ID),
				"version":  s.version,
			}

			if err := nk.NotificationSend(ctx, invitedUserId, "Party invitation", content, 1, message.GetUserId(), false); err != nil {
				logger.Warn("Error sending party invitation: %v", err)
				SendResponse(partyMsg, ResponseCodeInternalError, []runtime.Presence{message}, logger, dispatcher)
				continue
			}

			s.invitations[invitedUserId] = time.Now().Add(p.config.InviteDuration)

			// add to blocked-friends cache
			getBlockedFriendsWithCache(ctx, logger, nk, invitedUserId, s.blockedUsersCache)
			s.blockedUsersDirty = true

		case OpCodeUpdateParty:
			// Leader only action.
			if s.leader.GetUserId() != message.GetUserId() {
				SendResponse(partyMsg, ResponseCodeNotPartyLeader, []runtime.Presence{message}, logger, dispatcher)
				continue
			}

			// Expects message data payload to be a new party configuration string <= 1024 bytes long.
			// TODO
		case OpCodeUpdatePartyData:
			// Leader only action.
			if s.leader.GetUserId() != message.GetUserId() {
				SendResponse(partyMsg, ResponseCodeNotPartyLeader, []runtime.Presence{message}, logger, dispatcher)
				continue
			}

			s.partyData = partyMsg.Data

			if err := dispatcher.BroadcastMessage(OpCodeUpdatePartyData, partyMsg.Data, nil, nil, true); err != nil {
				logger.Warn("Error broadcasting party data update: %v", err)
				SendResponse(partyMsg, ResponseCodeInternalError, []runtime.Presence{message}, logger, dispatcher)
				continue
			}
		case OpCodeUpdatePartyMemberData:
			// Users are allowed to change their own party member data at will.
			s.partyMemberData[message.GetUserId()] = partyMsg.Data

			if err := dispatcher.BroadcastMessage(OpCodeUpdatePartyMemberData, partyMsg.Data, nil, message, true); err != nil {
				logger.Warn("Error broadcasting party data update: %v", err)
				SendResponse(partyMsg, ResponseCodeInternalError, []runtime.Presence{message}, logger, dispatcher)
				continue
			}
		default:
			SendResponse(partyMsg, ResponseCodeBadRequest, []runtime.Presence{message}, logger, dispatcher)
			continue
		}

		SendResponse(partyMsg, ResponseCodeSuccess, []runtime.Presence{message}, logger, dispatcher)
	}

	return s
}

func (p *PartyMatch) MatchTerminate(ctx context.Context, logger runtime.Logger, db *sql.DB, nk runtime.NakamaModule, dispatcher runtime.MatchDispatcher, tick int64, state interface{}, graceSeconds int) interface{} {
	// Termination has been requested by the server, usually because it's shutting down.
	if err := dispatcher.BroadcastMessage(OpCodeTerminate, nil, nil, nil, true); err != nil {
		logger.Warn("Error broadcasting party terminate message: %v", err)
	}
	return nil
}

func SendResponse(partyMsg PartyMatchMessage, responseCode int64, to []runtime.Presence, logger runtime.Logger, dispatcher runtime.MatchDispatcher) {
	if partyMsg.Id != nil {
		response := PartyMessageResponse{
			Id:           *partyMsg.Id,
			ResponseCode: responseCode,
		}

		responseBytes, err := json.Marshal(response)
		if err != nil {
			logger.Error("Error marshalling party message response: %v", err)
			return
		}

		if err := dispatcher.BroadcastMessage(OpCodePartyMessageResponse, responseBytes, to, nil, true); err != nil {
			logger.Error("Error broadcasting party message response: %v", err)
		}
	}
}
