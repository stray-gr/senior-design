package main

import (
	"context"
	"fmt"
	"net/url"
	"runtime"
	"time"

	"github.com/eclipse/paho.golang/autopaho"
	"github.com/eclipse/paho.golang/paho"
	"github.com/redis/go-redis/v9"
	"github.com/stray-gr/senior-design/proxy/msg"
	"google.golang.org/protobuf/proto"
)

const (
	CONNECT_TOPIC = "connect"
	LWT_TOPIC     = "lwt"
)

func mqttPoll(ctx context.Context, rdb *redis.Client) {
	// TODO: Read url from .env
	msgChan := make(chan *paho.Publish)
	uri, err := url.Parse("mqtt://localhost:1883")
	if err != nil {
		panic(err)
	}

	clientConfig := autopaho.ClientConfig{
		ServerUrls:                    []*url.URL{uri},
		KeepAlive:                     10,
		CleanStartOnInitialConnection: false,
		SessionExpiryInterval:         60,
		OnConnectionUp: func(cm *autopaho.ConnectionManager, connAck *paho.Connack) {
			_, err := cm.Subscribe(ctx, &paho.Subscribe{
				Subscriptions: []paho.SubscribeOptions{
					{Topic: "#", QoS: 1}, // Subcribe to all topics
				},
			})
			if err != nil {
				fmt.Println("PROXY  | ERROR - OnConnectionUp:", err)
			} else {
				fmt.Println("PROXY  | Connected to broker")
			}
		},
		OnConnectError: func(err error) { fmt.Println("PROXY  | ERROR - OnConnectError:", err) },
		ClientConfig: paho.ClientConfig{
			ClientID: "proxy",
			OnPublishReceived: []func(paho.PublishReceived) (bool, error){
				// OnPublishRecieved callback(s)
				func(recv paho.PublishReceived) (bool, error) {
					msgChan <- recv.Packet
					return true, nil
				},
			},
			OnClientError: func(err error) { fmt.Println("PROXY  | ERROR - OnClientError:", err) },
			OnServerDisconnect: func(d *paho.Disconnect) {
				if d.Properties != nil {
					fmt.Println("BROKER | Disconnected (reason):", d.Properties.ReasonString)
				} else {
					fmt.Println("BROKER | Disconnected (code):", d.ReasonCode)
				}
			},
		},
	}

	// Create new connection
	conn, err := autopaho.NewConnection(ctx, clientConfig)
	if err != nil {
		panic(err)
	}

	// Wait for new connection to establish
	err = conn.AwaitConnection(ctx)
	if err != nil {
		panic(err)
	}

	// PROXY ROUTER
	for mqttMsg := range msgChan {
		fmt.Println("PROXY  | Got MQTT message on:", mqttMsg.Topic)
		switch mqttMsg.Topic {
		case CONNECT_TOPIC:
			// Decode connect message
			in := &msg.Connect{}
			err := proto.Unmarshal(mqttMsg.Payload, in)
			if err != nil {
				fmt.Println("PROXY  | ERROR - Unable to decode connect:", err)
				continue
			}

			// Set device key
			rdb.Set(ctx, in.Device, "", 0)

		case LWT_TOPIC:
			// Decode LWT message
			in := &msg.LWT{}
			err := proto.Unmarshal(mqttMsg.Payload, in)
			if err != nil {
				fmt.Println("PROXY  | ERROR - Unable to decode LWT:", err)
				continue
			}

			// Set device key with expiration
			rdb.Set(ctx, in.Device, "", time.Duration(in.Delay)*time.Second)

		default:
			// Forward message
			rdb.Publish(ctx, mqttMsg.Topic, mqttMsg.Payload)
		}
	}
}

func redisPoll(ctx context.Context, rdb *redis.Client) {
	subscriber := rdb.PSubscribe(ctx, "__keyevent*__:expired")
	msgChan := subscriber.Channel()

	fmt.Println("PROXY  | Listening for expired Redis keys")

	// Redirect expired keys to LWT redis channel
	for msg := range msgChan {
		rdb.Publish(ctx, LWT_TOPIC, msg.Payload)
	}
}

func main() {
	cpus := runtime.GOMAXPROCS(0)

	// Create Redis connection pool
	// TODO: Read addr, username, and password from .env
	ctx := context.Background()
	rdb := redis.NewClient(&redis.Options{
		Addr:     "localhost:6379",
		Username: "",
		Password: "",
		DB:       0,
		PoolSize: cpus,
	})

	go mqttPoll(ctx, rdb)
	redisPoll(ctx, rdb)
}
