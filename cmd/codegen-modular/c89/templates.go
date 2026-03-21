package c89

import "embed"

//go:embed templates/*.tmpl
var Templates embed.FS
