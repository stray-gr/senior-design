#####################################################
# Inherit from Golang's official Alpine Linux image #
#####################################################
FROM golang:1.24-alpine3.21 AS build

COPY callbacks/ /callbacks/
COPY msg/       /msg/
COPY server/    /server/
COPY go.mod     /go.mod
COPY main.go    /main.go

RUN go build /main.go

###################################
# Inherit Alpine Linux 3.21 image #
###################################
FROM alpine:3.21 AS main

# Install base SSL certificates, which are needed to send POST requests to GroupMe's chat bot API
RUN apk update && apk add ca-certificates && rm -rf /var/cache/apk/*

# Copy the server binary from the previous stage, then run it
COPY --from=build /main /main
ENTRYPOINT [ "/main" ]
