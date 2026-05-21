# Codegen Architecture

The generator is a small Go template pipeline split into a reusable proto reader and SDK-specific generator modules.

## Pipeline

```text
.proto files
  -> yacg.LoadApi
  -> yacg.Api
  -> modules.ApiMapper + modules.TypeMapper
  -> modules.ApiMap
  -> text/template files
  -> generated SDK files
```

## Packages

### `yacg`

`cmd/codegen/yacg` parses protobuf source files with `github.com/emicklei/proto` and builds a simple intermediate representation:

- `yacg.Api` contains ordered `Enums`, `Messages`, and `Rpcs`, plus lookup maps by simple name.
- `ProtoEnum` contains enum comments and fields.
- `ProtoMessage` contains normal fields, map fields, oneof fields, and comments.
- `ProtoRpc` contains service method name, request/response messages, HTTP method/path/body metadata, and inferred path/query/body params.

This parser is intentionally lightweight. It assumes the Nakama/Satori flattened proto branches where messages are top-level, type names are simple after package trimming, and declaration order is compatible with lookup during parsing.

### `yacg/modules`

`cmd/codegen/yacg/modules` defines the target-neutral generation contracts.

`TypeMapper` maps protobuf identifiers and types into target-language names and type traits:

```go
type TypeMapper interface {
    ResolveIdentifier(input string, identifierType IdentifierType) string
    ResolveEntry(intype string) TypeEntry
}
```

`ApiMapper` maps the parsed proto API into the data shape templates consume:

```go
type ApiMapper interface {
    MapApi(api yacg.Api, typeMapper TypeMapper) (ApiMap, error)
    MapRpc(rpc *yacg.ProtoRpc, api yacg.Api, typeMapper TypeMapper) ([]Function, error)
    MapEnum(enum *yacg.ProtoEnum, api yacg.Api, typeMapper TypeMapper) (Enum, error)
    MapMessage(message *yacg.ProtoMessage, api yacg.Api, typeMapper TypeMapper) (Type, error)
}
```

`Module.Generate` executes one or more productions. A production combines:

- parsed API requirements
- one mapper pair
- one template
- one output path

### SDK modules

SDK modules live beside `yacg`, for example `cmd/codegen/unreal-sdk`.

An SDK module should contain:

- `main.go` to wire proto sets, mapper instances, templates, and output files.
- `typemappers/` for target-language type/name mapping.
- `apimappers/` for target-language SDK-surface mapping.
- `templates/` for generated files.

## What API Mappers Do

API mappers are the semantic translation layer between protobuf and SDK shape. They should not just copy proto fields; they decide what the generated SDK exposes.

Responsibilities:

- map protobuf messages to generated data types
- map protobuf enums to generated enums or literal unions
- map service RPCs to generated SDK functions
- produce overloads or wrappers when the target SDK needs them
- attach template metadata such as endpoint, method, path params, query params, body params, auth mode, JSON field names, and event names
- interpret Nakama-specific realtime `Envelope.oneof message` annotations when generating realtime SDKs

Use the `TypeMapper` from inside the `ApiMapper` for every target-language identifier and type decision. Templates should receive target-language-ready names and type entries, not raw protobuf names except where protocol wire names are needed.

## Current Unreal Mappers

- `UnrealHttpApiMapper` maps HTTP service RPCs into C++ API functions. It adds Nakama auth/session overloads and endpoint/body/query/path metadata.
- `UnrealBlueprintHttpApiMapper` maps HTTP RPCs into Blueprint-facing functions and delegate metadata.
- `UnrealRtApiMapper` maps annotated realtime envelope fields into request functions and event delegates.
- `UnrealTypeMapper` maps protobuf scalar/message/enum names into Unreal C++ types, params, JSON helpers, and default values.

# Adding A New Language Generator

## 1. Create a new SDK module

Create a sibling module under `cmd/codegen`, for example:

```text
cmd/codegen/typescript-sdk/
  go.mod
  main.go
  apimappers/
  typemappers/
  templates/
```

Add it to `cmd/codegen/go.work`:

```go
use (
  ./yacg
  ./unreal-sdk
  ./typescript-sdk
)
```

Use an SDK-specific module path such as `heroiclabs.com/yacg-modules/typescriptsdk`.

## 2. Implement a `TypeMapper`

The type mapper should be narrow and language-specific.

It must handle:

- protobuf scalar types
- well-known wrapper types used by Nakama, such as `BoolValue`, `Int32Value`, `UInt32Value`, `Int64Value`, `UInt64Value`, `FloatValue`, `DoubleValue`, `StringValue`, `BytesValue`
- `Timestamp`
- unknown message types
- enum identifiers
- reserved words in the target language

For message types, return the target SDK model name consistently. For TypeScript this could be the PascalCase interface/type name.

Keep wire names separate from SDK names. Proto field names like `group_id` are wire names for JSON/query/path; mapped names like `groupId` are SDK identifiers.

## 3. Implement HTTP `ApiMapper`

HTTP generation maps protobuf service RPCs and `google.api.http` annotations into request/response operations for the target SDK.

The HTTP mapper should:

- iterate `api.Enums`, `api.Messages`, and `api.Rpcs` in order
- skip SDK-owned/static messages only when there is a concrete reason
- call `MapEnum`, `MapMessage`, and `MapRpc` from `MapApi`
- use `typeMapper.ResolveIdentifier` for SDK names
- use `typeMapper.ResolveEntry` for all target types
- preserve protocol names in metadata for wire serialization:
  - JSON field names
  - query parameter keys
  - path placeholder names
- copy HTTP metadata from `yacg.ProtoRpc` into function metadata:
  - endpoint
  - method
  - path params
  - query params
  - body params
  - body-field/scalar-body behavior if needed

Do not parse proto files, walk proto ASTs, or inspect templates from the mapper. The mapper should only transform `yacg.Api` into `modules.ApiMap`.

## 4. Implement realtime `ApiMapper`

A complete Nakama SDK generator must include realtime/WebSocket operations as well as HTTP operations. Realtime generation is not based on normal protobuf `service` RPCs. It is derived from the annotated realtime `Envelope.oneof message` schema.

The realtime mapper should:

- iterate `api.Enums` and `api.Messages` to generate realtime data models
- locate the `Envelope` message
- skip generating the literal envelope type unless the target SDK explicitly needs it
- inspect `Envelope.OneofFields`
- treat oneof fields with `(category) = REQUEST` as client-to-server realtime operations
- treat oneof fields with `(category) = EVENT` as server-to-client event payloads
- treat oneof fields with `(category) = RESPONSE` as response payloads where useful for the target SDK
- use `(response_field)` to map a request field to its expected response message type
- use an empty response model or target-language equivalent when a request has no response field
- preserve the envelope wire field name in metadata; this is the JSON key sent over or received from the WebSocket
- use `typeMapper.ResolveIdentifier` for operation names, event names, and SDK field names
- use `typeMapper.ResolveEntry` for request, response, event, enum, and model types

The realtime mapper may synthesize `modules.Function` values from envelope request fields. This is the expected pattern because realtime requests are implicit in the envelope rather than declared as protobuf RPCs.

Realtime function metadata should include enough information for templates to print target-language WebSocket operations without rediscovering schema semantics, typically:

- envelope request field name
- SDK operation name
- request model type
- response model type
- whether the response is empty or absent

Do not require `(response_field)` to correspond to a separate envelope oneof field categorized as `RESPONSE`. In the Nakama realtime schema it is best treated first as a protobuf message type name. Some response types also appear as separate response envelope fields, but some do not; for example, a request can use `(response_field) = "Rpc"` where the response message type is `Rpc` and there is no distinct `RESPONSE` envelope field. If the target transport needs to correlate responses, correlation should primarily use the envelope `cid`; any response envelope field name should be optional metadata only when it can be resolved.

Realtime event metadata should include enough information for templates to print event registration/dispatch code, typically:

- envelope event field name
- SDK event name
- event payload model type

Do not make templates infer request/response/event categories from names. Category and response-field semantics belong in the realtime `ApiMapper`.

## 5. Implement templates

Templates should be dumb printers over `modules.ApiMap`.

They may contain target-language syntax decisions, but they should not reconstruct protobuf semantics.

Prefer passing explicit mapper metadata for repeated checks instead of embedding complex inference in templates.

Templates should use:

- `$.Enums` for enum-like definitions
- `$.Types` for model definitions and serializers
- `$.Funcs` for SDK functions
- `DataDecl.Metadata` for target-specific generation details

Generate separate files or one combined file based on the target SDK structure. The important rule is that both HTTP and realtime templates should consume mapper-produced `modules.ApiMap` values, not raw `yacg.Api` values.

## 6. Wire generation in `main.go`

`main.go` should:

- accept `--outdir`
- construct mapper instances
- construct type mapper instances
- call `modules.MakeProductionRequirements` for each proto set and mapper pair
- define `modules.Module{Produces: ...}` with template/output pairs
- call `module.Generate(outDir)`

For Nakama HTTP generation, use:

```go
nakamaApiProtos := []string{"proto/nakama-types.proto", "proto/nakama-api.proto"}
```

For Nakama realtime generation, use:

```go
nakamaRtApiProtos := []string{"proto/nakama-types.proto", "proto/realtime.proto"}
```

If the target SDK has both HTTP and realtime support, create separate production requirements for each proto set and mapper pair, then add productions for both sets of templates.

The command should normally be run from the SDK module directory, matching the existing Unreal generator convention.

## 7. Verify framework usage

Before judging language-specific style, verify these framework integration points:

- the new module is listed in `go.work`
- the generator builds with `go build` from its module directory
- `main.go` uses `modules.MakeProductionRequirements` and `modules.Module.Generate`
- mappers implement `modules.ApiMapper` and `modules.TypeMapper`
- mappers consume `yacg.Api`; they do not reparse proto files
- all SDK identifiers/types come from the type mapper
- wire names remain available in metadata and are not replaced by SDK identifiers
- templates consume `modules.ApiMap` rather than custom global state
- complete SDK targets generate both HTTP operations and realtime/WebSocket operations
- realtime operations are synthesized from annotated envelope fields by an `ApiMapper`, not by template name matching

## 8. Common mistakes

- Do not bypass `ApiMapper` by generating directly from `yacg.Api` inside templates.
- Do not put all type decisions in templates. Put them in `TypeMapper` and mapper metadata.
- Do not make templates parse endpoint strings to infer path/query/body params; `yacg.ProtoRpc` already contains that.
- Do not assume current `master` protos have realtime annotations. Use the flattened proto branches referenced by `Taskfile.yml`.
- Do not rely on nested protobuf messages being resolved correctly. The current parser assumes flattened schemas.
- Do not use raw proto field names as SDK identifiers. Keep both SDK identifier and wire name where both are needed.
- Do not stop at HTTP-only generation for a language SDK unless explicitly building an HTTP-only target.
- Do not put realtime request/event/response classification in templates; put it in the realtime `ApiMapper`.
