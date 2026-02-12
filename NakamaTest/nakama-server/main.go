package main

import (
	"context"
	"database/sql"
	"encoding/json"
	"strings"
	"time"

	"github.com/heroiclabs/nakama-common/runtime"
)

//goland:noinspection GoUnusedExportedFunction
func InitModule(ctx context.Context, logger runtime.Logger, db *sql.DB, nk runtime.NakamaModule, initializer runtime.Initializer) error {
	initStart := time.Now()

	if err := initializer.RegisterRpc("transform", rpcTransform); err != nil {
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
