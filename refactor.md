# Go Path
In your `.bashrc`:
```bash
export PATH="$PATH:/usr/local/go/bin"
export GOPATH=$HOME/go
export PATH=$PATH:$GOROOT/bin:$GOPATH/bin
```

# Protobuf
Add $GOPATH to env, then:
```bash
go install google.golang.org/protobuf/cmd/protoc-gen-go@latest
protoc --go_out=. --go_opt=Mmsg.proto={module}/msg  msg.proto
cd {module}
go get -u google.golang.org/protobuf/proto
```

# gRPC
Add $GOPATH to env, then:
```bash
go install google.golang.org/grpc/cmd/protoc-gen-go-grpc@latest
protoc --go_out=. --go_opt=Mservice.proto={module}/service --go-grpc_out=. --go-grpc_opt=Mservice.proto={module}/service service.proto
go get google.golang.org/grpc 
go get google.golang.org/protobuf/proto
```

# Integration test
```bash
sudo service mosquitto stop
sudo service redis-server stop

mosquitto
redis-server

redis-cli config set notify-keyspace-events Ex

# New terminals
cd proxy/ && go run main.go
cd batch-router/ && go run main.go
cd client/ && go run main.go
cd clock/ && go run main.go 
```

# MQTTX PUB/SUB using protobuf
```bash
cat a.proto | protoc --encode=msg.Cat ./msg.proto | mqttx pub -h localhost -p 1883 -t idk -s

mqttx sub -h localhost -p 1883 -t "connect" -Pp ./msg.proto -Pmn msg.Connect
mqttx sub -h localhost -p 1883 -t "lwt" -Pp ./msg.proto -Pmn msg.LWT
mqttx sub -h localhost -p 1883 -t "data/sensor" -Pp ./msg.proto -Pmn msg.SensorData
```

# TODO
- [X] batch-router callbacks
- [X] Add debug env var
- [X] gRPC API
- [ ] TLS and persistence for Redis
- [ ] Remove `old/api`, `old/server`, and `proxy` 
- [ ] Update docs
- [ ] final slides

# Idea
- 2 reserved topics and 1 reserved redis queue
    1. connect topic - mqtt proxy will set redis key by device name (no expiration) for each message
    2. lwt topic - mqtt proxy will set redis key by device name (expiration defined by message) for each message
    3. lwt queue - timeout poll will forward the device names of expired keys to here for processing. set lwt to false to disable
- All other channels are user-defined w/out special rules and restrictions
