package main

import (
	"context"
	"database/sql"
	"encoding/json"
	"fmt"
	"strings"
	"sync"
	"time"

	"github.com/heroiclabs/nakama-common/runtime"
)

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
