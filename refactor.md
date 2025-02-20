# Protobuf
Add $GOPATH to env, then:
```bash
go install google.golang.org/protobuf/cmd/protoc-gen-go@latest
protoc --go_out=. --go_opt=Mmsg.proto={module}/msg  msg.proto
cd {module}
go get -u google.golang.org/protobuf/proto
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
- [ ] batch-router callbacks
- [ ] TLS for Redis
