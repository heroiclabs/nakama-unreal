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
	"fmt"
	"strings"

	"github.com/heroiclabs/nakama-common/runtime"
)

var (
	ErrBadContext    = runtime.NewError("bad context", 3)
	ErrJsonMarshal   = runtime.NewError("cannot marshal response", 13)
	ErrJsonUnmarshal = runtime.NewError("cannot unmarshal request", 13)
)

type CreatePartyCompletionResult int

const (
	CreatePartyCompletionResult_UnknownClientFailure          CreatePartyCompletionResult = -100
	CreatePartyCompletionResult_AlreadyInPartyOfSpecifiedType CreatePartyCompletionResult = -99
	CreatePartyCompletionResult_AlreadyCreatingParty          CreatePartyCompletionResult = -98
	CreatePartyCompletionResult_AlreadyInParty                CreatePartyCompletionResult = -97
	CreatePartyCompletionResult_FailedToCreateMucRoom         CreatePartyCompletionResult = -96
	CreatePartyCompletionResult_NoResponse                    CreatePartyCompletionResult = -95
	CreatePartyCompletionResult_LoggedOut                     CreatePartyCompletionResult = -94
	CreatePartyCompletionResult_UnknownInternalFailure        CreatePartyCompletionResult = 0
	CreatePartyCompletionResult_Succeeded                     CreatePartyCompletionResult = 1
)

type CreatePartyRequest struct {
	PartyTypeId        int64  `json:"party_type_id"`
	PartyConfiguration string `json:"party_configuration"`
}

type CreatePartyResponse struct {
	PartyId                     string                      `json:"party_id"`
	CreatePartyCompletionResult CreatePartyCompletionResult `json:"create_party_completion_result"`
}

func rpcCreateParty(ctx context.Context, logger runtime.Logger, db *sql.DB, nk runtime.NakamaModule, payload string) (string, error) {
	var session *SessionContext
	var err error
	if session, err = unpackContext(ctx); err != nil {
		logger.Error("unpack context failed: %v", err)
		return "", ErrBadContext
	}

	var request *CreatePartyRequest
	if err = json.Unmarshal([]byte(payload), &request); err != nil {
		return "", ErrJsonUnmarshal
	}

	// Validate input. Online party type ID must be an integer >= 0.
	if request.PartyTypeId < 0 {
		response := &CreatePartyResponse{
			CreatePartyCompletionResult: CreatePartyCompletionResult_FailedToCreateMucRoom,
		}
		responseBytes, err := json.Marshal(response)
		if err != nil {
			return "", ErrJsonMarshal
		}
		return string(responseBytes), nil
	}
	// Validate input. Party configuration must be a string <= 1024 bytes long.
	if len(request.PartyConfiguration) > 1024 {
		response := &CreatePartyResponse{
			CreatePartyCompletionResult: CreatePartyCompletionResult_FailedToCreateMucRoom,
		}
		responseBytes, err := json.Marshal(response)
		if err != nil {
			return "", ErrJsonMarshal
		}
		return string(responseBytes), nil
	}

	// Create the party match.
	matchId, err := nk.MatchCreate(ctx, fmt.Sprintf("%s-%s", serviceName, "Party"), map[string]interface{}{
		"creator": session.UserID,
		"type_id": request.PartyTypeId,
		"config":  request.PartyConfiguration,
	})
	if err != nil {
		response := &CreatePartyResponse{
			CreatePartyCompletionResult: CreatePartyCompletionResult_UnknownInternalFailure,
		}
		responseBytes, err := json.Marshal(response)
		if err != nil {
			return "", ErrJsonMarshal
		}
		return string(responseBytes), nil
	}

	// Return result to user.
	response := &CreatePartyResponse{
		PartyId:                     matchId,
		CreatePartyCompletionResult: CreatePartyCompletionResult_Succeeded,
	}
	responseBytes, err := json.Marshal(response)
	if err != nil {
		return "", ErrJsonMarshal
	}
	return string(responseBytes), nil
}

type GetAdvertisedPartyRequest struct {
	UserId      string `json:"user_id"`
	PartyTypeId int64  `json:"party_type_id"`
}

type GetAdvertisedPartyResponse struct {
	PartyId string `json:"party_id"`
}

func rpcGetAdvertisedParty(ctx context.Context, logger runtime.Logger, db *sql.DB, nk runtime.NakamaModule, payload string) (string, error) {
	var err error
	if _, err = unpackContext(ctx); err != nil {
		logger.Error("unpack context failed: %v", err)
		return "", ErrBadContext
	}

	var request *GetAdvertisedPartyRequest
	if err = json.Unmarshal([]byte(payload), &request); err != nil {
		return "", ErrJsonUnmarshal
	}

	// Validate input. Online party type ID must be an integer >= 0.
	if request.PartyTypeId < 0 {
		// Not an error necessarily, rather no possible matches.
		response := &GetAdvertisedPartyResponse{}
		responseBytes, err := json.Marshal(response)
		if err != nil {
			return "", ErrJsonMarshal
		}
		return string(responseBytes), nil
	}
	// Validate input. A non-empty user ID is required.
	if len(request.UserId) == 0 {
		// Not an error necessarily, rather no possible matches.
		response := &GetAdvertisedPartyResponse{}
		responseBytes, err := json.Marshal(response)
		if err != nil {
			return "", ErrJsonMarshal
		}
		return string(responseBytes), nil
	}

	// List matches looking for the appropriate one.
	query := fmt.Sprintf("+label.type_id:%v +label.members:%v", request.PartyTypeId, request.UserId)
	matches, err := nk.MatchList(ctx, 1, true, "", 0, 999, query)
	if err != nil {
		logger.Error("match list failed: %v", err)
		return "", ErrBadContext
	}

	// Return result to user.
	response := &GetAdvertisedPartyResponse{}
	if len(matches) >= 1 {
		response.PartyId = matches[0].MatchId
	}
	responseBytes, err := json.Marshal(response)
	if err != nil {
		return "", ErrJsonMarshal
	}
	return string(responseBytes), nil
}

type RejectPartyInviteRequest struct {
	PartyId string `json:"party_id"`
}

func rpcRejectPartyInvite(ctx context.Context, logger runtime.Logger, db *sql.DB, nk runtime.NakamaModule, payload string) (string, error) {
	var session *SessionContext
	var err error
	if session, err = unpackContext(ctx); err != nil {
		logger.Error("unpack context failed: %v", err)
		return "", ErrBadContext
	}

	req := RejectPartyInviteRequest{}
	if err := json.Unmarshal([]byte(payload), &req); err != nil {
		logger.Error("Failed to unmarshal json: %v", err)
		return "", ErrJsonUnmarshal
	}

	//Get stream ID from party match ID
	matchIdComponents := strings.SplitN(req.PartyId, ".", 2)
	if len(matchIdComponents) != 2 {
		return "", runtime.NewError("Error parsing match ID into components", 3)
	}

	//List users in party stream
	presences, err := nk.StreamUserList(6, matchIdComponents[0], "", matchIdComponents[1], true, true)
	if err != nil {
		logger.Error("Stream user list failed: %v", err)
		return "", err
	}

	//Prepare notification for each user in stream
	notifications := make([]*runtime.NotificationSend, 0, len(presences))
	content := map[string]interface{}{
		"party_id":  req.PartyId,
		"member_id": session.UserID,
	}
	for _, presence := range presences {
		notification := &runtime.NotificationSend{
			UserID:     presence.GetUserId(),
			Subject:    "Party reject invitation",
			Content:    content,
			Code:       1,
			Persistent: false,
		}
		notifications = append(notifications, notification)
	}

	//Send reject notifications
	err = nk.NotificationsSend(ctx, notifications)
	if err != nil {
		logger.Error("Error sending reject party invite: %v", err)
		return "", err
	}

	return "", nil
}

type SessionContext struct {
	UserID    string
	SessionID string
}

func unpackContext(ctx context.Context) (*SessionContext, error) {
	userId, ok := ctx.Value(runtime.RUNTIME_CTX_USER_ID).(string)
	if !ok {
		return nil, ErrBadContext
	}
	sessionId, ok := ctx.Value(runtime.RUNTIME_CTX_SESSION_ID).(string)
	if !ok {
		return nil, ErrBadContext
	}
	return &SessionContext{UserID: userId, SessionID: sessionId}, nil
}
