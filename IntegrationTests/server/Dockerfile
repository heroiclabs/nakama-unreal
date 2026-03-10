ARG NAKAMA_VERSION=3.37.0

FROM docker.io/heroiclabs/nakama-pluginbuilder:${NAKAMA_VERSION} AS builder

ENV GO111MODULE=on
ENV CGO_ENABLED=1

WORKDIR /backend
COPY go.mod go.sum ./
RUN go mod download

COPY . .
RUN go build -buildmode=plugin -trimpath -o /backend/backend.so

FROM docker.io/heroiclabs/nakama:${NAKAMA_VERSION}

COPY --from=builder /backend/backend.so /nakama/data/modules/backend.so
