# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this is

A modular Protobuf-to-code generator written in Go. It reads `.proto` files describing the Nakama game server API and generates Unreal Engine C++ bindings (`Nakama.h` / `Nakama.cpp`). The design is intentionally layered so new target languages can be added without touching the core parser.

## Build & run

This directory is a Go workspace with two modules:

```
go.work
├── yacg/          # heroiclabs.com/yacg — framework + interfaces
└── unreal-sdk/    # heroiclabs.com/unreal-sdk — Unreal-specific implementation
```

Run the generator from `unreal-sdk/` (it must be run from there so relative paths to `protos/` and `templates/` resolve):

```sh
cd unreal-sdk && go run .
# Output lands in unreal-sdk/out/
```

Build everything:

```sh
go build ./...   # from codegen-modular/ workspace root
```

No test suite or Makefile exists yet.

## Architecture & data flow

```
protos/*.proto
    ↓  yacg.LoadApi()              -- yacg/api.go
    ↓  visitor pattern             -- yacg/proto_visitors.go
yacg.Api  {Enums, Messages, Rpcs}
    ↓  ApiMapper.MapApi()          -- unreal-sdk/api_mapper.go
modules.ApiMap  {Enums, Types, Funcs}
    ↓  text/template.Execute()     -- yacg/modules/module.go
out/Nakama.h + out/Nakama.cpp
```

### Package roles

| Package | Role |
|---|---|
| `heroiclabs.com/yacg` | Proto parsing — no target-language knowledge. Produces `yacg.Api`. |
| `heroiclabs.com/yacg/modules` | Shared interfaces (`ApiMapper`, `HttpApiMapper`, `NameResolver`) and the generic render pipeline (`Module` → `CompiledModule`). |
| `heroiclabs.com/unreal-sdk` (main) | Unreal-specific: `UnrealHttpApiMapper`, `UnrealNameResolver`, template files. Wires everything together in `main.go`. |

### Key types

- **`yacg.Api`** — raw parsed proto: enums, messages, RPCs with HTTP options (method, path, query, body).
- **`modules.ApiMap`** — target-language view: `[]Enum`, `[]Type`, `[]Function`. This is what templates receive.
- **`modules.Function.Locals`** — `map[string]any` carrying template-specific extras (e.g. auth mode, URL template, JSON key lists) that don't fit the generic `DataDecl` shape.
- **`modules.NameResolver`** — single `Resolve(input string, ctx NameResolveContext) string` method. The context enum (`Param`, `FieldType`, `JsonGetter`, `QueryFormat`, …) selects which facet of the type mapping to return.
- **`modules.TypeEntry`** — the full set of traits for one proto scalar type; the `UnrealNameResolver` builds a map of these at startup.

### Adding a new target language

1. Create a new Go module in a sibling directory (e.g. `dotnet-sdk/`).
2. Implement `modules.ApiMapper` (or `modules.HttpApiMapper`) and `modules.NameResolver`.
3. Write Go `text/template` templates.
4. Wire them into a `modules.Module{}` in `main.go` and call `module.Compile()` + `compiled.Generate()`.

### HTTP parameter extraction (how RPCs become functions)

`UnrealHttpApiMapper.MapRpc()` in `unreal-sdk/api_mapper.go`:
- **Path params** — extracted by regex from `{param}` placeholders in the HTTP option endpoint.
- **Query params** — request message fields not consumed as path params (GET requests).
- **Body params** — fields named by `body: "*"` or `body: "field_name"` in the HTTP option (POST/PUT).
- Each RPC can expand to multiple `Function` overloads (e.g. bearer-token auth vs. HTTP-key auth).

### Known TODOs in the code

- `module.go:87` — `MapApi` is called during `Generate` instead of during `Compile`; should move earlier.
- `UnrealNameResolver.Resolve()` — custom message types fall through to a stub; actual resolution is commented out.
