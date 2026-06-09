package main

import (
	"context"
	"crypto/rand"
	"database/sql"
	"encoding/json"
	"fmt"
	"strings"
	"sync"
	"time"

	"github.com/heroiclabs/nakama-common/runtime"
)

// authoritativeMatchModule is the registered match handler name used by
// clientrpc.create_authoritative_match.
const authoritativeMatchModule = "test_authoritative_match"

// newUUID returns a random v4 UUID string (used for tournament ids).
func newUUID() string {
	b := make([]byte, 16)
	_, _ = rand.Read(b)
	b[6] = (b[6] & 0x0f) | 0x40
	b[8] = (b[8] & 0x3f) | 0x80
	return fmt.Sprintf("%x-%x-%x-%x-%x", b[0:4], b[4:6], b[6:8], b[8:10], b[10:16])
}

// retryAttempts tracks per-test_id call counts for the retry_test RPC.
var retryAttempts sync.Map

//goland:noinspection GoUnusedExportedFunction
func InitModule(ctx context.Context, logger runtime.Logger, db *sql.DB, nk runtime.NakamaModule, initializer runtime.Initializer) error {
	initStart := time.Now()

	if err := initializer.RegisterRpc("transform", rpcTransform); err != nil {
		return err
	}

	if err := initializer.RegisterRpc("always_fail", rpcAlwaysFail); err != nil {
		return err
	}

	if err := initializer.RegisterRpc("retry_test", rpcRetryTest); err != nil {
		return err
	}

	// Legacy clientrpc.* helpers used by the realtime test suite.
	if err := initializer.RegisterRpc("clientrpc.rpc", rpcEcho); err != nil {
		return err
	}
	if err := initializer.RegisterRpc("clientrpc.create_tournament", rpcCreateTournament); err != nil {
		return err
	}
	if err := initializer.RegisterRpc("clientrpc.create_authoritative_match", rpcCreateAuthoritativeMatch); err != nil {
		return err
	}
	if err := initializer.RegisterRpc("clientrpc.send_notification", rpcSendNotification); err != nil {
		return err
	}
	if err := initializer.RegisterMatch(authoritativeMatchModule, func(ctx context.Context, logger runtime.Logger, db *sql.DB, nk runtime.NakamaModule) (runtime.Match, error) {
		return &testMatch{}, nil
	}); err != nil {
		return err
	}

	logger.Info("Test server plugin loaded in %dms", time.Since(initStart).Milliseconds())
	return nil
}

func rpcTransform(ctx context.Context, logger runtime.Logger, db *sql.DB, nk runtime.NakamaModule, payload string) (string, error) {
	var input map[string]interface{}
	if err := json.Unmarshal([]byte(payload), &input); err != nil {
		return "", runtime.NewError("invalid JSON payload", 3) // INVALID_ARGUMENT
	}

	msg, ok := input["message"].(string)
	if !ok {
		return "", runtime.NewError("missing or invalid 'message' field", 3) // INVALID_ARGUMENT
	}

	// Reverse the string
	runes := []rune(msg)
	for i, j := 0, len(runes)-1; i < j; i, j = i+1, j-1 {
		runes[i], runes[j] = runes[j], runes[i]
	}

	result := map[string]interface{}{
		"original": msg,
		"reversed": string(runes),
		"length":   len([]rune(msg)),
		"upper":    strings.ToUpper(msg),
	}

	out, err := json.Marshal(result)
	if err != nil {
		return "", runtime.NewError("failed to marshal response", 13) // INTERNAL
	}
	return string(out), nil
}

func rpcAlwaysFail(ctx context.Context, logger runtime.Logger, db *sql.DB, nk runtime.NakamaModule, payload string) (string, error) {
	return "", runtime.NewError("always fails", 14) // UNAVAILABLE
}

func rpcRetryTest(ctx context.Context, logger runtime.Logger, db *sql.DB, nk runtime.NakamaModule, payload string) (string, error) {
	var input struct {
		TestID    string `json:"test_id"`
		FailCount int    `json:"fail_count"`
	}
	if err := json.Unmarshal([]byte(payload), &input); err != nil {
		return "", runtime.NewError("invalid JSON payload", 3) // INVALID_ARGUMENT
	}
	if input.TestID == "" {
		return "", runtime.NewError("missing test_id", 3) // INVALID_ARGUMENT
	}

	// Atomically increment the call count for this test_id.
	var count int
	if val, loaded := retryAttempts.LoadOrStore(input.TestID, new(int)); loaded {
		ptr := val.(*int)
		*ptr++
		count = *ptr
	} else {
		ptr := val.(*int)
		*ptr = 1
		count = 1
	}

	if count <= input.FailCount {
		return "", runtime.NewError(fmt.Sprintf("transient failure %d/%d", count, input.FailCount), 14) // UNAVAILABLE
	}

	result, _ := json.Marshal(map[string]interface{}{
		"attempts": count,
	})
	return string(result), nil
}

// rpcEcho returns the request payload unchanged. Backs clientrpc.rpc.
func rpcEcho(ctx context.Context, logger runtime.Logger, db *sql.DB, nk runtime.NakamaModule, payload string) (string, error) {
	return payload, nil
}

// asInt coerces a JSON value (float64 when present) to int with a default.
func asInt(m map[string]interface{}, key string, def int) int {
	if v, ok := m[key].(float64); ok {
		return int(v)
	}
	return def
}

func asString(m map[string]interface{}, key, def string) string {
	if v, ok := m[key].(string); ok {
		return v
	}
	return def
}

func asBool(m map[string]interface{}, key string, def bool) bool {
	if v, ok := m[key].(bool); ok {
		return v
	}
	return def
}

// rpcCreateTournament creates a tournament from the test payload and returns its id.
func rpcCreateTournament(ctx context.Context, logger runtime.Logger, db *sql.DB, nk runtime.NakamaModule, payload string) (string, error) {
	var in map[string]interface{}
	if err := json.Unmarshal([]byte(payload), &in); err != nil {
		return "", runtime.NewError("invalid JSON payload", 3) // INVALID_ARGUMENT
	}

	// The test payload requests a tiny (~5s) active window, which expires before the
	// client can round-trip a join. Force a long-lived, never-ending tournament so the
	// join test is deterministic: no end_time and at least a 1h duration.
	duration := asInt(in, "duration", 3600)
	if duration < 3600 {
		duration = 3600
	}

	id := newUUID()
	err := nk.TournamentCreate(
		ctx,
		id,
		asBool(in, "authoritative", true),
		asString(in, "sort_order", "desc"),
		asString(in, "operator", "best"),
		asString(in, "reset_schedule", ""),
		map[string]interface{}{},
		asString(in, "title", "Test Tournament"),
		asString(in, "description", ""),
		asInt(in, "category", 1),
		0, // start_time: now
		0, // end_time: never
		duration,
		asInt(in, "max_size", 10000),
		asInt(in, "max_num_score", 1000000),
		asBool(in, "join_required", false),
		false, // enableRanks
	)
	if err != nil {
		return "", runtime.NewError(fmt.Sprintf("failed to create tournament: %v", err), 13) // INTERNAL
	}

	out, _ := json.Marshal(map[string]interface{}{"tournament_id": id})
	return string(out), nil
}

// rpcCreateAuthoritativeMatch creates a match using the registered match handler
// and returns its id.
func rpcCreateAuthoritativeMatch(ctx context.Context, logger runtime.Logger, db *sql.DB, nk runtime.NakamaModule, payload string) (string, error) {
	var params map[string]interface{}
	if payload != "" {
		if err := json.Unmarshal([]byte(payload), &params); err != nil {
			return "", runtime.NewError("invalid JSON payload", 3) // INVALID_ARGUMENT
		}
	}

	matchID, err := nk.MatchCreate(ctx, authoritativeMatchModule, params)
	if err != nil {
		return "", runtime.NewError(fmt.Sprintf("failed to create match: %v", err), 13) // INTERNAL
	}

	out, _ := json.Marshal(map[string]interface{}{"match_id": matchID})
	return string(out), nil
}

// rpcSendNotification sends a persistent notification to the requesting user.
func rpcSendNotification(ctx context.Context, logger runtime.Logger, db *sql.DB, nk runtime.NakamaModule, payload string) (string, error) {
	var in struct {
		UserID string `json:"user_id"`
	}
	if err := json.Unmarshal([]byte(payload), &in); err != nil {
		return "", runtime.NewError("invalid JSON payload", 3) // INVALID_ARGUMENT
	}
	if in.UserID == "" {
		return "", runtime.NewError("missing user_id", 3) // INVALID_ARGUMENT
	}

	content := map[string]interface{}{"message": "test notification"}
	if err := nk.NotificationSend(ctx, in.UserID, "Test Notification", content, 1, "", true); err != nil {
		return "", runtime.NewError(fmt.Sprintf("failed to send notification: %v", err), 13) // INTERNAL
	}

	return "{}", nil
}

// testMatch is a minimal authoritative match handler sufficient for join tests.
type testMatch struct{}

func (m *testMatch) MatchInit(ctx context.Context, logger runtime.Logger, db *sql.DB, nk runtime.NakamaModule, params map[string]interface{}) (interface{}, int, string) {
	label := ""
	if params != nil {
		if v, ok := params["label"].(string); ok {
			label = v
		}
	}
	return map[string]interface{}{}, 1, label
}

func (m *testMatch) MatchJoinAttempt(ctx context.Context, logger runtime.Logger, db *sql.DB, nk runtime.NakamaModule, dispatcher runtime.MatchDispatcher, tick int64, state interface{}, presence runtime.Presence, metadata map[string]string) (interface{}, bool, string) {
	return state, true, ""
}

func (m *testMatch) MatchJoin(ctx context.Context, logger runtime.Logger, db *sql.DB, nk runtime.NakamaModule, dispatcher runtime.MatchDispatcher, tick int64, state interface{}, presences []runtime.Presence) interface{} {
	return state
}

func (m *testMatch) MatchLeave(ctx context.Context, logger runtime.Logger, db *sql.DB, nk runtime.NakamaModule, dispatcher runtime.MatchDispatcher, tick int64, state interface{}, presences []runtime.Presence) interface{} {
	return state
}

func (m *testMatch) MatchLoop(ctx context.Context, logger runtime.Logger, db *sql.DB, nk runtime.NakamaModule, dispatcher runtime.MatchDispatcher, tick int64, state interface{}, messages []runtime.MatchData) interface{} {
	return state
}

func (m *testMatch) MatchTerminate(ctx context.Context, logger runtime.Logger, db *sql.DB, nk runtime.NakamaModule, dispatcher runtime.MatchDispatcher, tick int64, state interface{}, graceSeconds int) interface{} {
	return state
}

func (m *testMatch) MatchSignal(ctx context.Context, logger runtime.Logger, db *sql.DB, nk runtime.NakamaModule, dispatcher runtime.MatchDispatcher, tick int64, state interface{}, data string) (interface{}, string) {
	return state, ""
}
