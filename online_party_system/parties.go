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
	"github.com/heroiclabs/nakama/runtime"
	"math/rand"
	"strconv"
	"strings"
	"time"
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

type JoinPartyCompletionResult int

const (
	JoinPartyCompletionResult_UnknownClientFailure          JoinPartyCompletionResult = -100
	JoinPartyCompletionResult_BadBuild                      JoinPartyCompletionResult = -99
	JoinPartyCompletionResult_InvalidAccessKey              JoinPartyCompletionResult = -98
	JoinPartyCompletionResult_AlreadyInLeadersJoiningList   JoinPartyCompletionResult = -97
	JoinPartyCompletionResult_AlreadyInLeadersPartyRoster   JoinPartyCompletionResult = -96
	JoinPartyCompletionResult_NoSpace                       JoinPartyCompletionResult = -95
	JoinPartyCompletionResult_NotApproved                   JoinPartyCompletionResult = -94
	JoinPartyCompletionResult_RequesteeNotMember            JoinPartyCompletionResult = -93
	JoinPartyCompletionResult_RequesteeNotLeader            JoinPartyCompletionResult = -92
	JoinPartyCompletionResult_NoResponse                    JoinPartyCompletionResult = -91
	JoinPartyCompletionResult_LoggedOut                     JoinPartyCompletionResult = -90
	JoinPartyCompletionResult_UnableToRejoin                JoinPartyCompletionResult = -89
	JoinPartyCompletionResult_IncompatiblePlatform          JoinPartyCompletionResult = -88
	JoinPartyCompletionResult_AlreadyJoiningParty           JoinPartyCompletionResult = -87
	JoinPartyCompletionResult_AlreadyInParty                JoinPartyCompletionResult = -86
	JoinPartyCompletionResult_JoinInfoInvalid               JoinPartyCompletionResult = -85
	JoinPartyCompletionResult_AlreadyInPartyOfSpecifiedType JoinPartyCompletionResult = -84
	JoinPartyCompletionResult_MessagingFailure              JoinPartyCompletionResult = -83
	JoinPartyCompletionResult_GameSpecificReason            JoinPartyCompletionResult = -82
	JoinPartyCompletionResult_UnknownInternalFailure        JoinPartyCompletionResult = 0
	JoinPartyCompletionResult_Succeeded                     JoinPartyCompletionResult = 1
)

type LeavePartyCompletionResult int

const (
	LeavePartyCompletionResult_UnknownClientFailure    LeavePartyCompletionResult = -100
	LeavePartyCompletionResult_NoResponse              LeavePartyCompletionResult = -99
	LeavePartyCompletionResult_LoggedOut               LeavePartyCompletionResult = -98
	LeavePartyCompletionResult_UnknownParty            LeavePartyCompletionResult = -97
	LeavePartyCompletionResult_LeavePending            LeavePartyCompletionResult = -96
	LeavePartyCompletionResult_UnknownLocalUser        LeavePartyCompletionResult = -95
	LeavePartyCompletionResult_NotMember               LeavePartyCompletionResult = -94
	LeavePartyCompletionResult_MessagingFailure        LeavePartyCompletionResult = -93
	LeavePartyCompletionResult_UnknownTransportFailure LeavePartyCompletionResult = -92
	LeavePartyCompletionResult_UnknownInternalFailure  LeavePartyCompletionResult = 0
	LeavePartyCompletionResult_Succeeded               LeavePartyCompletionResult = 1
)

const (
	serviceName = "OnlinePartySystem"
)

var (
	ErrBadContext    = runtime.NewError("bad context", 3)
	ErrJsonMarshal   = runtime.NewError("cannot marshal response", 13)
	ErrJsonUnmarshal = runtime.NewError("cannot unmarshal request", 13)
	ErrBadPartyId    = runtime.NewError("bad party id", 3)
)

// Registers the collection of functions with Nakama required to provide an OnlinePartyService from Unreal Engine.
func Register(initializer runtime.Initializer) error {
	rand.Seed(time.Now().UnixNano())

	if err := initializer.RegisterRpc(fmt.Sprintf("%s-%s", serviceName, "CreateParty"), rpcCreateParty); err != nil {
		return err
	}
	if err := initializer.RegisterRpc(fmt.Sprintf("%s-%s", serviceName, "JoinParty"), rpcJoinParty); err != nil {
		return err
	}
	if err := initializer.RegisterRpc(fmt.Sprintf("%s-%s", serviceName, "LeaveParty"), rpcLeaveParty); err != nil {
		return err
	}
	if err := initializer.RegisterRpc(fmt.Sprintf("%s-%s", serviceName, "ApproveJoinRequest"), rpcApproveJoinRequest); err != nil {
		return err
	}
	return nil
}

type CreatePartyRequest struct {
	PartyTypeId        uint8  `json:"party_type_id"`
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

	// Validate input.
	if request.PartyTypeId < 10 {
		response := &CreatePartyResponse{
			CreatePartyCompletionResult: CreatePartyCompletionResult_FailedToCreateMucRoom,
		}
		responseBytes, err := json.Marshal(response)
		if err != nil {
			return "", ErrJsonMarshal
		}
		return string(responseBytes), nil
	}

	// Generate a new party ID and add the user to it.
	partyId := randomPartyId()
	_, err = nk.StreamUserJoin(request.PartyTypeId, "", "", partyId, session.UserID, session.SessionID, false, false, "")
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
		PartyId:                     encodePartyIdString(request.PartyTypeId, partyId),
		CreatePartyCompletionResult: CreatePartyCompletionResult_Succeeded,
	}
	responseBytes, err := json.Marshal(response)
	if err != nil {
		return "", ErrJsonMarshal
	}
	return string(responseBytes), nil
}

type JoinPartyRequest struct {
	// Original interface uses "IOnlinePartyJoinInfo" as input instead here.
	PartyId string `json:"party_id"`
}

type JoinPartyResponse struct {
	// Original interface uses "IOnlinePartyJoinInfo" as input instead here.
	PartyId                   string                    `json:"party_id"`
	// Only for immediate errors, some other errors may come from the party leader rejecting the join request etc.
	JoinPartyCompletionResult JoinPartyCompletionResult `json:"join_party_completion_result"`
}

type JoinRequestMessage struct {
	PartyId   string `json:"party_id"`
	SenderId  string `json:"sender_id"`
}

func rpcJoinParty(ctx context.Context, logger runtime.Logger, db *sql.DB, nk runtime.NakamaModule, payload string) (string, error) {
	var session *SessionContext
	var err error
	if session, err = unpackContext(ctx); err != nil {
		logger.Error("unpack context failed: %v", err)
		return "", ErrBadContext
	}

	var request *JoinPartyRequest
	if err = json.Unmarshal([]byte(payload), &request); err != nil {
		return "", ErrJsonUnmarshal
	}

	// Validate input.
	partyTypeId, partyId, err := decodePartyIdString(request.PartyId)
	if err != nil {
		response := &JoinPartyResponse{
			PartyId:                   request.PartyId,
			JoinPartyCompletionResult: JoinPartyCompletionResult_JoinInfoInvalid,
		}
		responseBytes, err := json.Marshal(response)
		if err != nil {
			return "", ErrJsonMarshal
		}
		return string(responseBytes), nil
	}

	// Send the join request to the party.
	joinRequestMessage := &JoinRequestMessage{
		PartyId:   request.PartyId,
		SenderId:  fmt.Sprintf("%v.%v", session.UserID, session.SessionID),
	}
	joinRequestMessageBytes, err := json.Marshal(joinRequestMessage)
	if err != nil {
		return "", ErrJsonMarshal
	}
	err = nk.StreamSend(partyTypeId, "", "", partyId, string(joinRequestMessageBytes), nil)
	if err != nil {
		response := &JoinPartyResponse{
			PartyId:                   request.PartyId,
			JoinPartyCompletionResult: JoinPartyCompletionResult_UnknownInternalFailure,
		}
		responseBytes, err := json.Marshal(response)
		if err != nil {
			return "", ErrJsonMarshal
		}
		return string(responseBytes), nil
	}

	// Final response is only possible when the party leader responds.
	return "", nil
}

type LeavePartyRequest struct {
	PartyId string `json:"party_id"`
}

type LeavePartyResponse struct {
	PartyId                    string                     `json:"party_id"`
	LeavePartyCompletionResult LeavePartyCompletionResult `json:"leave_party_completion_result"`
}

func rpcLeaveParty(ctx context.Context, logger runtime.Logger, db *sql.DB, nk runtime.NakamaModule, payload string) (string, error) {
	var session *SessionContext
	var err error
	if session, err = unpackContext(ctx); err != nil {
		logger.Error("unpack context failed: %v", err)
		return "", ErrBadContext
	}

	var request *LeavePartyRequest
	if err = json.Unmarshal([]byte(payload), &request); err != nil {
		return "", ErrJsonUnmarshal
	}

	// Validate input.
	partyTypeId, partyId, err := decodePartyIdString(request.PartyId)
	if err != nil {
		response := &LeavePartyResponse{
			PartyId:                    request.PartyId,
			LeavePartyCompletionResult: LeavePartyCompletionResult_UnknownParty,
		}
		responseBytes, err := json.Marshal(response)
		if err != nil {
			return "", ErrJsonMarshal
		}
		return string(responseBytes), nil
	}

	err = nk.StreamUserLeave(partyTypeId, "", "", partyId, session.UserID, session.SessionID)
	if err != nil {
		response := &LeavePartyResponse{
			PartyId:                    request.PartyId,
			LeavePartyCompletionResult: LeavePartyCompletionResult_UnknownInternalFailure,
		}
		responseBytes, err := json.Marshal(response)
		if err != nil {
			return "", ErrJsonMarshal
		}
		return string(responseBytes), nil
	}

	response := &LeavePartyResponse{
		PartyId:                    request.PartyId,
		LeavePartyCompletionResult: LeavePartyCompletionResult_Succeeded,
	}
	responseBytes, err := json.Marshal(response)
	if err != nil {
		return "", ErrJsonMarshal
	}
	return string(responseBytes), nil
}

type ApproveJoinRequest struct {
	PartyId          string `json:"party_id"`
	RecipientId      string `json:"recipient_id"`
	IsApproved       bool   `json:"is_approved"`
	DeniedResultCode int32  `json:"denied_result_code"`
}

func rpcApproveJoinRequest(ctx context.Context, logger runtime.Logger, db *sql.DB, nk runtime.NakamaModule, payload string) (string, error) {
	var session *SessionContext
	var err error
	if session, err = unpackContext(ctx); err != nil {
		logger.Error("unpack context failed: %v", err)
		return "", ErrBadContext
	}

	var request *ApproveJoinRequest
	if err = json.Unmarshal([]byte(payload), &request); err != nil {
		return "", ErrJsonUnmarshal
	}

	// Validate input.
	partyTypeId, partyId, err := decodePartyIdString(request.PartyId)
	if err != nil {
		return "", ErrJsonUnmarshal
	}
	recipient := strings.SplitN(request.RecipientId, ".", 2)
	if len(recipient) != 2 {
		return "", ErrJsonUnmarshal
	}

	meta, err := nk.StreamUserGet(partyTypeId, "", "", partyId, session.UserID, session.SessionID)
	if err != nil {
		return "", ErrJsonUnmarshal
	}
	if meta == nil {
		// User is not part of this party at all.
		return "", ErrJsonUnmarshal
	}

	// Notify the requester.
	data := map[string]interface{}{
		"party_id":                     request.PartyId,
		"join_party_completion_result": JoinPartyCompletionResult_Succeeded,
	}
	err = nk.NotificationSend(ctx, recipient[0], "JoinRequestApproved", data, 100, session.UserID, false)
	if err != nil {
		return "", ErrJsonMarshal
	}

	// Add the requester to the party.
	_, err = nk.StreamUserJoin(partyTypeId, "", "", partyId, recipient[0], recipient[1], false, false, "")
	if err != nil {
		return "", ErrJsonMarshal
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

func randomPartyId() string {
	const partyIdLength = 12
	const partyIdAlphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
	const partyIdAlphabetLength = len(partyIdAlphabet)

	partyId := make([]byte, partyIdLength)
	for i := 0; i < partyIdLength; i++ {
		partyId[i] = partyIdAlphabet[rand.Intn(partyIdAlphabetLength)]
	}
	return string(partyId)
}

func encodePartyIdString(partyTypeId uint8, partyId string) string {
	return fmt.Sprintf("%v.%v", partyTypeId, partyId)
}

func decodePartyIdString(partyId string) (uint8, string, error) {
	parts := strings.SplitN(partyId, ".", 2)
	if len(parts) != 2 {
		return 0, "", ErrBadPartyId
	}
	partyTypeId, err := strconv.Atoi(parts[0])
	if err != nil {
		return 0, "", ErrBadPartyId
	}
	return uint8(partyTypeId), parts[1], nil
}
