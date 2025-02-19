package main

import (
	"context"
	"fmt"
	"net/url"
	"time"

	"github.com/eclipse/paho.golang/autopaho"
	"github.com/eclipse/paho.golang/paho"
)

const (
	CLOCK_DELAY = time.Duration(1000) * time.Millisecond
	PULSE_TOPIC = "pulse"
)

func main() {
	// TODO: Read url from .env
	ctx := context.Background()
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
			fmt.Println("CLOCK  | Connected to broker")
		},
		OnConnectError: func(err error) { fmt.Println("CLOCK  | ERROR - OnConnectError:", err) },
		ClientConfig: paho.ClientConfig{
			ClientID:      "clock",
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

	for {
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
