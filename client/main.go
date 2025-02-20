package main

import (
	"context"
	"crypto/tls"
	"fmt"
	"net/url"
	"os"
	"time"

	"github.com/eclipse/paho.golang/autopaho"
	"github.com/eclipse/paho.golang/paho"
	"github.com/stray-gr/senior-design/client/msg"
	"google.golang.org/protobuf/proto"
)

const (
	CONNECT_TOPIC = "connect"
	DATA_TOPIC    = "data/sensor"
	LWT_DELAY     = 3
	LWT_TOPIC     = "lwt"
	PULSE_TOPIC   = "pulse"
	USER          = "client"
)

func mqttPoll(ctx context.Context) {
	// Retrieve env vars
	BROKER_URI, uriOk := os.LookupEnv("BROKER_URI")
	PASS, passOk := os.LookupEnv("MQTT_CLIENT_PASS")
	if !uriOk || !passOk {
		panic("Unable to get environment variables for Mosquitto")
	}

	// Parse broker URI
	uri, err := url.Parse(BROKER_URI)
	if err != nil {
		panic(err)
	}

	// Create message channel
	msgChan := make(chan *paho.Publish)

	// Encode LWT message
	lwt := &msg.LWT{
		Device: USER,
		Delay:  LWT_DELAY,
	}
	out, err := proto.Marshal(lwt)
	if err != nil {
		panic(err)
	}

	clientConfig := autopaho.ClientConfig{
		ServerUrls:                    []*url.URL{uri},
		KeepAlive:                     10,
		CleanStartOnInitialConnection: false,
		SessionExpiryInterval:         60,
		ConnectUsername:               USER,
		ConnectPassword:               []byte(PASS),
		TlsCfg: &tls.Config{
			ServerName: "stray-gr",
		},
		WillMessage: &paho.WillMessage{
			QoS:     1,
			Topic:   LWT_TOPIC,
			Payload: out,
		},
		OnConnectionUp: func(cm *autopaho.ConnectionManager, connAck *paho.Connack) {
			// Subscribe to pulse
			_, err := cm.Subscribe(ctx, &paho.Subscribe{
				Subscriptions: []paho.SubscribeOptions{
					{Topic: PULSE_TOPIC, QoS: 1},
				},
			})
			if err != nil {
				fmt.Println("CLIENT | ERROR - Pulse topic subscription failed:", err)
				return
			}

			// Encode connect message
			connMsg := &msg.Connect{
				Device: USER,
			}
			out, err := proto.Marshal(connMsg)
			if err != nil {
				fmt.Println("CLIENT | ERROR - Unable to encode connect:", err)
				return
			}

			// Publish connect message
			_, err = cm.Publish(ctx, &paho.Publish{
				QoS:     1,
				Topic:   CONNECT_TOPIC,
				Payload: out,
			})
			if err != nil {
				fmt.Println("CLIENT | ERROR - Unable to publish connect:", err)
				return
			}

			// Log success
			fmt.Println("CLIENT | Connected to broker")
		},
		OnConnectError: func(err error) { fmt.Println("CLIENT | ERROR - OnConnectError:", err) },
		ClientConfig: paho.ClientConfig{
			ClientID: USER,
			OnPublishReceived: []func(paho.PublishReceived) (bool, error){
				// OnPublishRecieved callback(s)
				func(recv paho.PublishReceived) (bool, error) {
					msgChan <- recv.Packet
					return true, nil
				},
			},
			OnClientError: func(err error) { fmt.Println("CLIENT | ERROR - OnClientError:", err) },
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

	// Listen for pulse messages
	for mqttMsg := range msgChan {
		switch mqttMsg.Topic {
		case PULSE_TOPIC:
			fmt.Println("CLIENT | Got pulse, sending data to:", DATA_TOPIC)

			// Encode data
			data := &msg.SensorData{
				Device: USER,
				Temp:   50.0,
				Rh:     75.5,
				Epoch:  time.Now().Unix(),
			}
			out, err := proto.Marshal(data)
			if err != nil {
				fmt.Println("CLIENT | ERROR - Unable to encode data:", err)
				continue
			}

			// Publish data
			_, err = conn.Publish(ctx, &paho.Publish{
				QoS:     1,
				Topic:   DATA_TOPIC,
				Payload: out,
			})
			if err != nil {
				fmt.Println("CLIENT | ERROR - Unable to publish data:", err)
				continue
			}
		}
	}
}

func main() {
	ctx := context.Background()
	mqttPoll(ctx)
}
