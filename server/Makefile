CXXFLAGS := -lpaho-mqttpp3 -lpaho-mqtt3as -lssl -lcrypto -Wall -O2

all: client clock server

client:
	g++ src/msg.pb.cc src/client/*.cc -lprotobuf $(CXXFLAGS) -o bin/client
clock:
	g++ src/clock/*.cc $(CXXFLAGS) -o bin/clock
server:
	g++ src/msg.pb.cc src/server/*.cc -pthread -lprotobuf $(CXXFLAGS) -o bin/server
