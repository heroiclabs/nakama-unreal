package unreal

import "embed"

//go:embed templates/*.tmpl
var Templates embed.FS

//go:embed static/*
var StaticFiles embed.FS
