package server

import (
	"context"
	"crypto/tls"
	"fmt"
	"net/url"
	"os"
	"runtime"
	"strconv"
	"time"

	"github.com/eclipse/paho.golang/autopaho"
	"github.com/eclipse/paho.golang/paho"
	"github.com/redis/go-redis/v9"
	"gorm.io/driver/postgres"
	"gorm.io/gorm"
)

// Private types
type (
	batch struct {
		minSize  int64
		maxSize  int64
		timeout  float64
		callback cb
		t0       time.Time
	}

	cb = func(context.Context, string)

	mqttClient struct {
		config  autopaho.ClientConfig
		msgChan chan *paho.Publish
	}

	task struct {
		ctx      context.Context
		sinkQ    string
		callback cb
	}
)

// Public types
type (
	BatchMap = map[string]*batch

	PgClient struct {
		ID int32
		DB *gorm.DB
	}
)

// Type constructors
func NewBatch(minSize, maxSize int, timeout float64, callback cb) *batch {
	return &batch{
		int64(minSize),
		int64(maxSize),
		timeout,
		callback,
		time.Now(),
	}
}

func NewMqttClient(ctx context.Context) *mqttClient {
	// Retrieve env vars for Mosquitto
	BROKER_URI, uriOk := os.LookupEnv("BROKER_URI")
	PASS, passOk := os.LookupEnv("MQTT_PROXY_PASS")
	if !uriOk || !passOk {
		panic("Unable to get env vars for Mosquitto")
	}

	// Parse broker URI
	uri, err := url.Parse(BROKER_URI)
	if err != nil {
		panic(err)
	}

	// Create message channel
	msgChan := make(chan *paho.Publish)

	clientConfig := autopaho.ClientConfig{
		ServerUrls:                    []*url.URL{uri},
		CleanStartOnInitialConnection: false,
		ConnectUsername:               USER,
		ConnectPassword:               []byte(PASS),
		OnConnectionUp: func(cm *autopaho.ConnectionManager, connAck *paho.Connack) {
			_, err := cm.Subscribe(ctx, &paho.Subscribe{
				Subscriptions: []paho.SubscribeOptions{
					{Topic: "#", QoS: 1}, // Subcribe to all topics
				},
			})
			if err != nil {
				fmt.Println("MqttClient | ERROR - OnConnectionUp:", err)
			} else {
				fmt.Println("MqttClient | Connected to broker")
			}
		},
		OnConnectError: func(err error) { fmt.Println("MqttClient | ERROR - OnConnectError:", err) },
		ClientConfig: paho.ClientConfig{
			ClientID: USER,
			OnPublishReceived: []func(paho.PublishReceived) (bool, error){
				// OnPublishRecieved callback(s)
				func(recv paho.PublishReceived) (bool, error) {
					msgChan <- recv.Packet
					return true, nil
				},
			},
			OnClientError: func(err error) { fmt.Println("MqttClient | ERROR - OnClientError:", err) },
			OnServerDisconnect: func(d *paho.Disconnect) {
				if d.Properties != nil {
					fmt.Println("MqttClient | Broker disconnected (reason):", d.Properties.ReasonString)
				} else {
					fmt.Println("MqttClient | Broker disconnected (code):", d.ReasonCode)
				}
			},
		},
	}

	return &mqttClient{
		config:  clientConfig,
		msgChan: msgChan,
	}
}

func NewPgClient() *PgClient {
	// Get postgres env vars
	F_CONN_STR, okConn := os.LookupEnv("F_CONN_STR")
	F_ID, okID := os.LookupEnv("F_ID")
	if !okConn || !okID {
		panic("Unable to get env vars for PgClient")
	}

	// Convert facility ID from string to int32
	fID, err := strconv.ParseInt(F_ID, 10, 32)
	if err != nil {
		panic(err)
	}
	id := int32(fID)

	// Create GORM postgres client
	db, err := gorm.Open(postgres.Open(F_CONN_STR), &gorm.Config{})
	if err != nil {
		panic(err)
	}

	// Set size of GORM connection pool
	sqlDB, err := db.DB()
	if err != nil {
		panic(err)
	}
	sqlDB.SetMaxOpenConns(runtime.GOMAXPROCS(0))

	// Return client
	return &PgClient{
		ID: id,
		DB: db,
	}
}

func NewRedisClient() *redis.Client {
	// Get redis env vars
	REDIS_ADDR, ok := os.LookupEnv("REDIS_ADDR")
	if !ok {
		panic("Mising env vars for RedisClient")
	}

	// Paths defined in Dockerfile
	cert, err := tls.LoadX509KeyPair("/certs/client.crt", "/certs/client.key")
	if err != nil {
		panic(err)
	}

	// Create and return client
	return redis.NewClient(&redis.Options{
		Addr:     REDIS_ADDR,
		Username: "",
		Password: "",
		DB:       0,
		PoolSize: runtime.GOMAXPROCS(0),
		TLSConfig: &tls.Config{
			Certificates: []tls.Certificate{cert},
		},
	})
}
