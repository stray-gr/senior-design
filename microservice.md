# Microservices Documentation

## Table of Contents
- [Project Description](#project-description)
- [Prerequisites](#prerequisites)
- [Project Set Up](#project-set-up)
- [Microservice Dockerfile Configuration](#microservice-dockerfile-configuration)
- [Docker Compose Configuration](#docker-compose-configuration)
- [Integration Testing](#integration-testing)
- [Protobuf Message Definitions](#protobuf-message-definitions)
- [Useful References](#useful-references)
- [Credit](#credit)

## Project Description
This project demonstrates how a data pipeline can be created using microservices written in Go, a programming language that prioritizes simplicity without heavily sacrificing performance. This is due to Go's straightforward syntax, build process, and concurrency management when compared to other systems level languages (e.g. C++). 

Listed below is a brief description of each microservice in this project's repo:
1. [API](api/) - **TODO**
2. [Batch-Router](batch-router/) - **TODO** 
3. [Client](client/) - **TODO** 
4. [Clock](clock/) - **TODO** 

## Prerequisites
1. Unix-like OS, preferably Ubuntu 24.04 (**WSL works**)
2. [Visual Studio Code](https://code.visualstudio.com/download), with the following plugins:
    - ms-vscode-remote.remote-wsl (**Windows only**)
    - ms-azuretools.vscode-docker
    - tamasfe.even-better-toml
    - golang.go
    - ms-python.vscode-pylance
    - ms-python.python
    - zxh404.vscode-proto3
3. [Rancher Desktop](https://rancherdesktop.io/)
4. [MQTTX CLI](https://mqttx.app/cli)
5. [Go 1.24](https://go.dev/dl/)

## Project Set Up
1. Add ***/usr/local/go/bin*** to your environment's path variable:
    ```bash
    export PATH="$PATH:/usr/local/go/bin"
    ```

2. Create a *GOPATH* environment variable that points to the *go* folder in your home directory. Note that this directory should've been added when Go was installed:
    ```bash
    GOPATH=$HOME/go
    ```

3. Add ***$GOPATH/bin*** to your environment's path variable:
    ```bash
    export PATH=$PATH:$GOPATH/bin
    ```

4. Use the following commands to create a Go module (which will contain your microservice's source code):
    ```bash
    mkdir <module-name>
    go mod init <src-control-platform>/<user-name>/<module-name>

    # Example
    mkdir hello-world
    go mod init github.com/your-user-name/hello-world
    ``` 

6. If your microservice plans on using protobuf and gRPC, start by installing the protobuf and gRPC compiler for Go:
    ```bash
    go install google.golang.org/protobuf/cmd/protoc-gen-go@latest
    go install google.golang.org/grpc/cmd/protoc-gen-go-grpc@latest
    ```

    Next, open a terminal in the Go module's parent directory. Then run the following commands. Note that the *service.proto* file containing your RPC and message definitions should also be located in the parent directory:
    ```bash
    protoc --go_out=. --go_opt=Mservice.proto=<module-name>/service --go-grpc_out=. --go-grpc_opt=Mservice.proto=<module-name>/service service.proto
    ```

    Lastly, `cd` into the Go module's root directory and run the following commands to add the necessary dependencies:
    ```bash
    cd <module-name>
    go get google.golang.org/protobuf/proto
    go get google.golang.org/grpc 
    go mod tidy
    ```

7. If your microservice only plans on using protobuf, start by installing the protobuf compiler for Go:
    ```bash
    go install google.golang.org/protobuf/cmd/protoc-gen-go@latest
    ```

    Next, open a terminal in the Go module's parent directory. Then run the following commands. Note that the *msg.proto* file containing your message definitions should also be located in the parent directory:
    ```bash
    protoc --go_out=. --go_opt=Mmsg.proto=<module-name>/msg  msg.proto
    ```

    Lastly, `cd` into the Go module's root directory and run the following commands to add the protobuf dependencies:
    ```bash
    cd <module-name>
    go get -u google.golang.org/protobuf/proto
    go mod tidy
    ```

8. Now that any preliminary code gen has completed (e.g. gRPC/protobuf compilation), you can begin developing your microservice. Note that development in Go is typically an iterative process: 
    - Start by installing some dependecies using `go get`. Then add these dependencies to your source code **before** running `go mod tidy`. Doing so will generate a *go.sum* file, which outlines the full dependency tree of your module. As a result, make sure to run `go mod tidy` before committing changes upstream or building your module. That way, others can install the needed dependencies or build the module
    - **WARNING:** Running `go mod tidy` will also remove any unused dependencies. This includes dependencies that you've added but have not yet used in your source code. Therefore, make sure your project's source code is at a good stopping or saving point before running this command. That way, you won't have to re-add any dependencies that haven't been used just quite yet

9. If your microservice plans on using a GroupMe chat bot... **TODO**, make sure to shoutout example in batch-router

10. Once you're ready to build and test your microservice, create a *Dockerfile* to build your microservice and include any necessary files (e.g. TLS certs). This *Dockerfile* can then be used to define the microservice in the project's [docker compose](#docker-compose-configuration) file. For an example, refer to the section covering [microservice dockerfile configuration](#microservice-dockerfile-configuration).

## Microservice Dockerfile Configuration
The *Dockerfile* used by each microservice in this example repo follows the same overall structure:

1. Inherit Go's official Alpine Linux image as `build`. This image then gets used to build the microservice. This requires:
    - Copying the source code into the image, along with the *go.mod* and *go.sum* files
    - Running `go mod download` to download all of the dependencies needed for the microservice
    - Running `go mod build` to build the microservice and install its binary in *usr/local/bin/*

2. Inherit the offical Alpine Linux image as `main`, which gets used to run the microservice. This requires:
    - Installing any required system packages (e.g. ca-certificates package, which contains a bundle of commonly used an trusted CA certs) 
    - Copying any files needed by the microservice (e.g. self-signed TLS certs)
    - Running any commands to set up the system and update its CA cert cache
    - Copying the microservice's built binary from the `build` image into the `main` image
    - Defining an entrypoint that will execute your microservice's binary

Below is an example  that demonstrates all of thes practices. It was adapted from this repo's batch-router microservice. Note that using splitting the build process into a `build` and `main` image prevents the `main` docker image from having any unnecessary packages. This allows the `main` docker image to be as small as possible, which makes deploying your microservic easier and potentially less costly.

```Dockerfile
#####################################################
# Inherit from Golang's official Alpine Linux image #
#####################################################
FROM golang:1.24-alpine3.21 AS build

# Source code
COPY callbacks/ /callbacks/
COPY msg/       /msg/
COPY server/    /server/
COPY main.go    /main.go

# Dependencies
COPY go.mod /go.mod
COPY go.sum /go.sum

# Build and install
RUN go mod download
RUN go build -o /usr/local/bin/batch-router /main.go

###################################
# Inherit Alpine Linux 3.21 image #
###################################
FROM alpine:3.21 AS main

# Install common CA certs
RUN apk update && apk add ca-certificates && rm -rf /var/cache/apk/*

# Upload the project's self-signed CA cert
COPY ca.crt /usr/local/share/ca-certificates/ca.crt

# Update the system's CA cert cache
RUN update-ca-certificates

# Upload client certs
COPY certs/ /certs/

# Copy the built binary from the previous stage, then set it as the entry point
COPY --from=build /usr/local/bin/batch-router /usr/local/bin/batch-router
ENTRYPOINT [ "batch-router" ]
```

## Docker Compose Configuration

## Integration Testing
1. Build the services outlined by the project's docker compose using:
    ```bash
    docker-compose build
    ```

    Then, run the services by using
    ```bash
    docker-compose run
    ```

2. Once the services start running, check your GroupMe chat bot if applicable... **TODO** 

```bash
sudo service mosquitto stop
sudo service redis-server stop

dc build && dc up

# Wait, then check groupme for two outage reports

# New terminal
cd api/client/
source .venv/bin/activate
python client/main.py  # Next test should yield 1 - 16 (at 12 rn)
```

## Protobuf Message Definitions
### Pulse Messages
- **Topic Name:** `pulse`
- **Publisher:** Clock App
- **Subscribers:** Each ESP32 board
- **QoS:** 1 (at least once)
- **Payload:** empty

### Connect Messages
- **Topic Name:** `connect`
- **Publisher:** Each ESP32 board
- **Subscribers:** Batch-Router
- **QoS:** 1 (at least once)
- **Payload:**
    ```protobuf
    message Connect {
        string device = 1; // Device name
    }
    ```

### LWT Messages
- **Topic Name:** `lwt`
- **Publisher:** Each ESP32 board
- **Subscribers:** Batch-Router
- **QoS:** 1 (at least once)
- **Payload:**
    ```protobuf
    message LWT {
        string device = 1; // Device name
        int64  delay  = 2; // LWT delay interval (seconds)
    }
    ```

### Sensor Data Messages
- **Topic Name:** `data/sensor`
- **Publisher:** Each ESP32 board
- **Subscribers:** Batch-Router
- **QoS:** 1 (at least once)
- **Payload:**
    ```protobuf
    message SensorData {
        string device = 1; // Device name
        float  temp   = 2; // Temperature reading (°C)
        float  rh     = 3; // Relative humidity reading (%)
        int64  epoch  = 4; // Unix epoch time (seconds)
    }
    ```


## Useful References
- Go Redis docs
- Protobuf docs
- gRPC docs

## Credit
- Autopaho examples
