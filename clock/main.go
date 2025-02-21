package main

import (
	"context"
	"fmt"
	"net/url"
	"os"
	"time"

	"github.com/eclipse/paho.golang/autopaho"
	"github.com/eclipse/paho.golang/paho"
)

const (
	CLOCK_DELAY = time.Duration(1000) * time.Millisecond
	PULSE_TOPIC = "pulse"
	USER        = "clock"
)

func main() {
	ctx := context.Background()

	// Retrieve env vars
	BROKER_URI, uriOk := os.LookupEnv("BROKER_URI")
	PASS, passOk := os.LookupEnv("MQTT_CLOCK_PASS")
	DEBUG, debugOk := os.LookupEnv("DEBUG")
	if !uriOk || !passOk || !debugOk {
		panic("Unable to get environment variables for Mosquitto")
	}

	// Parse broker URI
	uri, err := url.Parse(BROKER_URI)
	if err != nil {
		panic(err)
	}

	clientConfig := autopaho.ClientConfig{
		ServerUrls:                    []*url.URL{uri},
		CleanStartOnInitialConnection: false,
		ConnectUsername:               USER,
		ConnectPassword:               []byte(PASS),
		OnConnectionUp: func(cm *autopaho.ConnectionManager, connAck *paho.Connack) {
			fmt.Println("CLOCK  | Connected to broker")
		},
		OnConnectError: func(err error) { fmt.Println("CLOCK  | ERROR - OnConnectError:", err) },
		ClientConfig: paho.ClientConfig{
			ClientID:      USER,
			OnClientError: func(err error) { fmt.Println("CLOCK  | ERROR - OnClientError:", err) },
			OnServerDisconnect: func(d *paho.Disconnect) {
				if d.Properties != nil {
					fmt.Println("BROKER | Disconnected (reason):", d.Properties.ReasonString)
				} else {
					fmt.Println("BROKER | Disconnected (code):", d.ReasonCode)
				}
			},
		},
	}

	conn, err := autopaho.NewConnection(ctx, clientConfig)
	if err != nil {
		panic(err)
	}

	err = conn.AwaitConnection(ctx)
	if err != nil {
		panic(err)
	}

	itr := 0
	for {
		// If DEBUG, update itr and maybe exit
		if DEBUG == "1" {
			if itr < 4 {
				itr += 1
			} else {
				return
			}
		}

		// Publish pulse
		_, err := conn.Publish(ctx, &paho.Publish{
			QoS:     1,
			Topic:   PULSE_TOPIC,
			Payload: []byte{},
		})
		if err != nil {
			fmt.Println("CLOCK  | Unable to publish pulse:", err)
		}

		time.Sleep(CLOCK_DELAY)
	}
}
