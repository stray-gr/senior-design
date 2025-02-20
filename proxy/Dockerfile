#####################################################
# Inherit from Golang's official Alpine Linux image #
#####################################################
FROM golang:1.24-alpine3.21 AS build

COPY msg/    /msg/
COPY go.mod  /go.mod
COPY go.sum  /go.sum
COPY main.go /main.go

RUN go mod download
RUN go build -o /usr/local/bin/proxy /main.go

###################################
# Inherit Alpine Linux 3.21 image #
###################################
FROM alpine:3.21 AS main

# Upload broker CA cert
RUN apk update && apk add ca-certificates && rm -rf /var/cache/apk/*
COPY ca.crt /usr/local/share/ca-certificates/ca.crt
RUN update-ca-certificates

# Copy the server binary from the previous stage, then run it
COPY --from=build /usr/local/bin/proxy /usr/local/bin/proxy
ENTRYPOINT [ "proxy" ]