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
	"fmt"

	"github.com/heroiclabs/nakama-common/runtime"
)

const (
	serviceName = "OnlinePartySystem"
)

// Allow implementation-specific filtering of parameters received from clients in party join attempts.
type MatchJoinMetadataFilter func(metadata map[string]string) map[string]string

// MatchEndHook allows implementation-specific logic to run when a match ends.
type MatchEndHook func(matchID string, config PartyConfig, label *PartyMatchLabel)

// MatchInitHook allows implementation-specific logic to run when a match is initialized.
type MatchInitHook func(matchID string, config PartyConfig, label *PartyMatchLabel)

type MatchJoinAttemptHook func(matchID string, presence runtime.Presence, meta map[string]string) (bool, string)

type MatchLeaveHook func(matchID string, userId string)

type MatchKickHook func(matchID string, userId string)

func noopMatchJoinMetadataFilter(metadata map[string]string) map[string]string {
	return metadata
}

// Registers the collection of functions with Nakama required to provide an OnlinePartyService from Unreal Engine.
func Register(initializer runtime.Initializer, config PartyConfig) error {
	if config.MatchJoinMetadataFilter == nil {
		config.MatchJoinMetadataFilter = noopMatchJoinMetadataFilter
	}
	createPartyMatch := func(ctx context.Context, logger runtime.Logger, db *sql.DB, nk runtime.NakamaModule) (runtime.Match, error) {
		return &PartyMatch{
			config: config,
		}, nil
	}

	if err := initializer.RegisterMatch(fmt.Sprintf("%s-%s", serviceName, "Party"), createPartyMatch); err != nil {
		return err
	}
	if err := initializer.RegisterRpc(fmt.Sprintf("%s-%s", serviceName, "CreateParty"), rpcCreateParty); err != nil {
		return err
	}
	if err := initializer.RegisterRpc(fmt.Sprintf("%s-%s", serviceName, "GetAdvertisedParty"), rpcGetAdvertisedParty); err != nil {
		return err
	}
	if err := initializer.RegisterRpc(fmt.Sprintf("%s-%s", serviceName, "RejectPartyInvite"), rpcRejectPartyInvite); err != nil {
		return err
	}
	return nil
}
