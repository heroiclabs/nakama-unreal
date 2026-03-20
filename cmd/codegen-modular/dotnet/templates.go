package dotnet

import "embed"

//go:embed templates/*.tmpl
var Templates embed.FS
