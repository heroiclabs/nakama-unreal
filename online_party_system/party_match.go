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
	OpCodeRemoveUserForRejoin
	OpCodeSendInvitation
	OpCodeUpdateParty
	OpCodeUpdatePartyData
	OpCodeUpdatePartyMemberData
)

type PartyMatchLabel struct {
	OnlinePartyTypeId int64    `json:"type_id,omitempty"`
	Members           []string `json:"members,omitempty"`
}

type PartyMatchState struct {
	leader            runtime.Presence            // Identity of the current party leader. May change over the lifetime of the party.
	presences         map[string]runtime.Presence // Map of user IDs to presences. Keyed on user ID because multiple devices per user per party are not allowed.
	partyData         []byte                      // Arbitrary party data.
	partyMemberData   map[string][]byte           // Arbitrary party member data.
	approvedForRejoin map[string]struct{}         // User IDs approved for rejoin.
	invitations       map[string]struct{}         // User IDs that have been invited.
	joinRequests      map[string]runtime.Presence // User IDs that have requested to join the party.

	label             *PartyMatchLabel // Label exposed to Nakama's match listing system.
	creator           string           // Party creator user ID, used to allow the user to automatically join when they create.
	initialEmptyTicks int              // Number of ticks the party has been empty on creation, to ensure parties are cleaned up if their creator never joins.
}

type PartyConfig struct {
	MaxSize int // Maximum number of members allowed in party
}

type PartyMatch struct {
	config PartyConfig
}

func (p PartyMatch) MatchInit(ctx context.Context, logger runtime.Logger, db *sql.DB, nk runtime.NakamaModule, params map[string]interface{}) (interface{}, int, string) {
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
	_, ok = params["config"].(string)
	if !ok {
		logger.Error("Error creating party, no config in params")
		return nil, 0, ""
	}

	label := &PartyMatchLabel{
		OnlinePartyTypeId: typeId,
		Members:           make([]string, 0, 5),
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
		invitations:       make(map[string]struct{}),
		joinRequests:      make(map[string]runtime.Presence),

		label:             label,
		creator:           creator,
		initialEmptyTicks: 0,
	}

	return state, TickRate, string(labelBytes)
}

func (p PartyMatch) MatchJoinAttempt(ctx context.Context, logger runtime.Logger, db *sql.DB, nk runtime.NakamaModule, dispatcher runtime.MatchDispatcher, tick int64, state interface{}, presence runtime.Presence, metadata map[string]string) (interface{}, bool, string) {
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
		return s, true, ""
	}

	// Reject any joins that would exceed party size
	if p.config.MaxSize > 0 && len(s.presences) >= p.config.MaxSize {
		return s, false, "Party is full"
	}

	// Allow approved rejoins.
	if _, ok := s.approvedForRejoin[presence.GetUserId()]; ok {
		delete(s.approvedForRejoin, presence.GetUserId())
		return s, true, ""
	}

	// Allow users that have been invited.
	if _, ok := s.invitations[presence.GetUserId()]; ok {
		delete(s.invitations, presence.GetUserId())
		return s, true, ""
	}

	// Everyone else must be approved by the party leader.
	s.joinRequests[presence.GetUserId()] = presence
	if err := dispatcher.BroadcastMessage(OpCodeJoinRequest, nil, []runtime.Presence{s.leader}, presence, true); err != nil {
		logger.Warn("Error broadcasting join request to party leader: %v", err)
	}
	return s, false, "Join request sent"
}

func (p PartyMatch) MatchJoin(ctx context.Context, logger runtime.Logger, db *sql.DB, nk runtime.NakamaModule, dispatcher runtime.MatchDispatcher, tick int64, state interface{}, presences []runtime.Presence) interface{} {
	s := state.(*PartyMatchState)

	// Reaching this stage means the party member join was either approved by the leader or implicitly by the rejoin list.
	for _, presence := range presences {
		s.presences[presence.GetUserId()] = presence

		s.label.Members = append(s.label.Members, presence.GetUserId())
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

func (p PartyMatch) MatchLeave(ctx context.Context, logger runtime.Logger, db *sql.DB, nk runtime.NakamaModule, dispatcher runtime.MatchDispatcher, tick int64, state interface{}, presences []runtime.Presence) interface{} {
	s := state.(*PartyMatchState)

	// User has either left voluntarily or disconnected.
	for _, presence := range presences {
		delete(s.presences, presence.GetUserId())
		delete(s.partyMemberData, presence.GetUserId())

		for i := 0; i < len(s.label.Members); i++ {
			if s.label.Members[i] == presence.GetUserId() {
				s.label.Members[i] = s.label.Members[len(s.label.Members)-1]
				s.label.Members = s.label.Members[:len(s.label.Members)-1]
				break
			}
		}

		// If this was the party leader elect a new one randomly.
		if leftUserId := presence.GetUserId(); leftUserId == s.leader.GetUserId() {
			for userId, remainingPresence := range s.presences {
				if userId != leftUserId {
					s.leader = remainingPresence
					// Notify the party about the new leader.
					if err := dispatcher.BroadcastMessage(OpCodePromoteMember, nil, nil, remainingPresence, true); err != nil {
						logger.Warn("Error broadcasting member promotion: %v", err)
					}
					break
				}
			}
		}
	}

	// If the party is now empty stop it now.
	if len(s.presences) == 0 {
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

func (p PartyMatch) MatchLoop(ctx context.Context, logger runtime.Logger, db *sql.DB, nk runtime.NakamaModule, dispatcher runtime.MatchDispatcher, tick int64, state interface{}, messages []runtime.MatchData) interface{} {
	s := state.(*PartyMatchState)

	// Check if the party has been sitting empty since creation.
	if s.creator != "" && len(s.presences) == 0 {
		s.initialEmptyTicks++
		if s.initialEmptyTicks >= InitialJoinTicks {
			return nil
		}
	}

	// Process messages one by one.
	// Currently any unknown, malformed, or unexpected messages are just ignored.
	for _, message := range messages {
		switch message.GetOpCode() {
		case OpCodeApproveForRejoin:
			// Leader only action.
			if s.leader.GetUserId() != message.GetUserId() {
				continue
			}

			// Expects message data payload to be a user ID string to be approved for rejoin.
			s.approvedForRejoin[string(message.GetData())] = struct{}{}
		case OpCodeApproveJoinRequest:
			// Leader only action.
			if s.leader.GetUserId() != message.GetUserId() {
				continue
			}

			// Expects message data payload to be a user ID string to be approved for join.
			if presence, ok := s.joinRequests[string(message.GetData())]; ok {
				delete(s.joinRequests, string(message.GetData()))

				// Add the user to the match stream. This will lead to MatchJoin being triggered.
				matchIdComponents := strings.SplitN(ctx.Value(runtime.RUNTIME_CTX_MATCH_ID).(string), ".", 2)
				if len(matchIdComponents) != 2 {
					logger.Error("Error parsing match ID into components")
					continue
				}
				if _, err := nk.StreamUserJoin(6, matchIdComponents[0], "", matchIdComponents[1], presence.GetUserId(), presence.GetSessionId(), false, false, ""); err != nil {
					logger.Warn("Error adding user to match stream after party join request approved: %v", err)
				}
			}
		case OpCodeClearInvitations:
			// Leader only action.
			if s.leader.GetUserId() != message.GetUserId() {
				continue
			}

			s.invitations = make(map[string]struct{})
		case OpCodeGetPartyData:
			if err := dispatcher.BroadcastMessage(OpCodeGetPartyData, s.partyData, []runtime.Presence{message}, nil, true); err != nil {
				logger.Warn("Error broadcasting party data: %v", err)
			}
		case OpCodeGetPartyMemberData:
			// Expects message data payload to be a user ID string to retrieve party member data for.
			if presence, ok := s.presences[string(message.GetData())]; ok {
				if err := dispatcher.BroadcastMessage(OpCodeGetPartyMemberData, s.partyMemberData[string(message.GetData())], []runtime.Presence{message}, presence, true); err != nil {
					logger.Warn("Error broadcasting party member data: %v", err)
				}
			}
		case OpCodeGetPendingInvitedUsers:
			invitations := make([]string, 0, len(s.invitations))
			for userId, _ := range s.invitations {
				invitations = append(invitations, userId)
			}

			data, err := json.Marshal(invitations)
			if err != nil {
				logger.Warn("Error encoding invitations: %v", err)
				continue
			}

			// Outgoing data payload will be a JSON array of user IDs.
			if err := dispatcher.BroadcastMessage(OpCodeGetPendingInvitedUsers, data, []runtime.Presence{message}, nil, true); err != nil {
				logger.Warn("Error broadcasting pending invited users: %v", err)
			}
		case OpCodeGetPendingJoinRequests:
			joinRequests := make([]string, 0, len(s.invitations))
			for userId, _ := range s.joinRequests {
				joinRequests = append(joinRequests, userId)
			}

			data, err := json.Marshal(joinRequests)
			if err != nil {
				logger.Warn("Error encoding join requests: %v", err)
				continue
			}

			// Outgoing data payload will be a JSON array of user IDs.
			if err := dispatcher.BroadcastMessage(OpCodeGetPendingJoinRequests, data, []runtime.Presence{message}, nil, true); err != nil {
				logger.Warn("Error broadcasting pending join requests: %v", err)
			}
		case OpCodeGetUsersApprovedForRejoin:
			approvedRejoins := make([]string, 0, len(s.invitations))
			for userId, _ := range s.approvedForRejoin {
				approvedRejoins = append(approvedRejoins, userId)
			}

			data, err := json.Marshal(approvedRejoins)
			if err != nil {
				logger.Warn("Error encoding approved for rejoin: %v", err)
				continue
			}

			// Outgoing data payload will be a JSON array of user IDs.
			if err := dispatcher.BroadcastMessage(OpCodeGetUsersApprovedForRejoin, data, []runtime.Presence{message}, nil, true); err != nil {
				logger.Warn("Error broadcasting users approved for rejoin: %v", err)
			}
		case OpCodeIsMemberLeader:
			// Expects message data payload to be a user ID string to check if it's the party leader.
			isPartyLeader := "false"
			if s.leader.GetUserId() == string(message.GetData()) {
				isPartyLeader = "true"
			}

			// Outgoing data payload will contain the strings "true" or "false".
			if err := dispatcher.BroadcastMessage(OpCodeIsMemberLeader, []byte(isPartyLeader), []runtime.Presence{message}, nil, true); err != nil {
				logger.Warn("Error broadcasting is member leader: %v", err)
			}
		case OpCodeKickMember:
			// Leader only action.
			if s.leader.GetUserId() != message.GetUserId() {
				continue
			}

			// Expects message data payload to be a user ID string to be kicked.
			if presence, ok := s.presences[string(message.GetData())]; ok {
				if err := dispatcher.BroadcastMessage(OpCodeKickMember, nil, nil, presence, true); err != nil {
					logger.Warn("Error broadcasting party member kicked: %v", err)
				}
				if err := dispatcher.MatchKick([]runtime.Presence{presence}); err != nil {
					logger.Warn("Error kicking party member: %v", err)
					continue
				}

				delete(s.presences, presence.GetUserId())
				delete(s.partyMemberData, presence.GetUserId())
			}
		case OpCodePromoteMember:
			// Leader only action.
			if s.leader.GetUserId() != message.GetUserId() {
				continue
			}

			// Expects message data payload to be a user ID string to be promoted.
			if presence, ok := s.presences[string(message.GetData())]; ok {
				if err := dispatcher.BroadcastMessage(OpCodePromoteMember, nil, nil, presence, true); err != nil {
					logger.Warn("Error broadcasting party member promote: %v", err)
				}

				s.leader = presence
			}
		case OpCodeRemoveUserForRejoin:
			// Leader only action.
			if s.leader.GetUserId() != message.GetUserId() {
				continue
			}

			// Expects message data payload to be a user ID string to be removed for rejoin.
			delete(s.approvedForRejoin, string(message.GetData()))
		case OpCodeSendInvitation:
			// Leader only action.
			if s.leader.GetUserId() != message.GetUserId() {
				continue
			}

			// Expects message data payload to be a user ID string to be invited.
			if err := nk.NotificationSend(ctx, string(message.GetData()), "Party invitation", map[string]interface{}{"match_id": ctx.Value(runtime.RUNTIME_CTX_MATCH_ID)}, 1, message.GetUserId(), false); err != nil {
				logger.Warn("Error sending party invitation: %v", err)
				continue
			}
			s.invitations[string(message.GetData())] = struct{}{}
		case OpCodeUpdateParty:
			// Leader only action.
			if s.leader.GetUserId() != message.GetUserId() {
				continue
			}

			// Expects message data payload to be a new party configuration string <= 1024 bytes long.
			// TODO
		case OpCodeUpdatePartyData:
			// Leader only action.
			if s.leader.GetUserId() != message.GetUserId() {
				continue
			}

			s.partyData = message.GetData()

			if err := dispatcher.BroadcastMessage(OpCodeUpdatePartyData, message.GetData(), nil, nil, true); err != nil {
				logger.Warn("Error broadcasting party data update: %v", err)
			}
		case OpCodeUpdatePartyMemberData:
			// Users are allowed to change their own party member data at will.
			s.partyMemberData[message.GetUserId()] = message.GetData()

			if err := dispatcher.BroadcastMessage(OpCodeUpdatePartyMemberData, message.GetData(), nil, message, true); err != nil {
				logger.Warn("Error broadcasting party data update: %v", err)
			}
		default:
			// Unknown messages may be handled differently later.
			continue
		}
	}

	return s
}

func (p PartyMatch) MatchTerminate(ctx context.Context, logger runtime.Logger, db *sql.DB, nk runtime.NakamaModule, dispatcher runtime.MatchDispatcher, tick int64, state interface{}, graceSeconds int) interface{} {
	// Termination has been requested by the server, usually because it's shutting down.
	if err := dispatcher.BroadcastMessage(OpCodeTerminate, nil, nil, nil, true); err != nil {
		logger.Warn("Error broadcasting party terminate message: %v", err)
	}
	return nil
}
