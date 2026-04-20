package internal

import "strings"

func TrimUntilLastDot(s string) string {
	return s[strings.LastIndex(s, ".")+1:]
}
