#####################################################
# Inherit from Golang's official Alpine Linux image #
#####################################################
FROM golang:1.24-alpine3.21 AS build

COPY callbacks/ /callbacks/
COPY msg/       /msg/
COPY server/    /server/
COPY go.mod     /go.mod
COPY go.sum     /go.sum
COPY main.go    /main.go

RUN go mod download
RUN go build -o /usr/local/bin/batch-router /main.go

###################################
# Inherit Alpine Linux 3.21 image #
###################################
FROM alpine:3.21 AS main

# Upload CA cert
RUN apk update && apk add ca-certificates && rm -rf /var/cache/apk/*
COPY ca.crt /usr/local/share/ca-certificates/ca.crt
RUN update-ca-certificates

# Upload client certs
# RUN
COPY client.crt /certs/client.crt
COPY client.key /certs/client.key

# Copy the server binary from the previous stage, then run it
COPY --from=build /usr/local/bin/batch-router /usr/local/bin/batch-router
ENTRYPOINT [ "batch-router" ]
