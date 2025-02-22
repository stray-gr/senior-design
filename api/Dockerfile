#####################################################
# Inherit from Golang's official Alpine Linux image #
#####################################################
FROM golang:1.24-alpine3.21 AS build

COPY service/ /service/
COPY go.mod   /go.mod
COPY go.sum   /go.sum
COPY main.go  /main.go

RUN go mod download
RUN go build -o /usr/local/bin/api /main.go

###################################
# Inherit Alpine Linux 3.21 image #
###################################
FROM alpine:3.21 AS main

# Copy the server binary from the previous stage, then run it
COPY certs/ /certs/
COPY --from=build /usr/local/bin/api /usr/local/bin/api
ENTRYPOINT [ "api" ]
