package server

import (
	"context"
	"fmt"
	"runtime"
	"time"

	"github.com/eclipse/paho.golang/autopaho"
	"github.com/google/uuid"
	"github.com/redis/go-redis/v9"
	"github.com/stray-gr/senior-design/batch-router/msg"
	"google.golang.org/protobuf/proto"
)

func mqttProxy(ctx context.Context, batches BatchMap) {
	rdb, ok := ctx.Value("REDIS_CLIENT").(*redis.Client)
	if !ok {
		panic("Unable to retreive values from context")
	}

	// Create new proxy client and connection
	proxy := NewMqttClient(ctx)
	conn, err := autopaho.NewConnection(ctx, proxy.config)
	if err != nil {
		panic(err)
	}

	// Wait for new connection to establish
	err = conn.AwaitConnection(ctx)
	if err != nil {
		panic(err)
	}

	// Consume messages
	fmt.Println("mqttProxy | INFO - Waiting for messages")
	for mqttMsg := range proxy.msgChan {
		switch mqttMsg.Topic {
		// Decode connect message and set device key
		case CONNECT_TOPIC:
			in := &msg.Connect{}
			if err := proto.Unmarshal(mqttMsg.Payload, in); err != nil {
				fmt.Println("mqttProxy | ERROR - Unable to decode connect:", err)
				continue
			}
			rdb.Set(ctx, in.Device, "", 0)

		// Decode LWT message and set device key w/ expiration
		case LWT_TOPIC:
			in := &msg.LWT{}
			if err := proto.Unmarshal(mqttMsg.Payload, in); err != nil {
				fmt.Println("mqttProxy | ERROR - Unable to decode LWT:", err)
				continue
			}
			rdb.Set(ctx, in.Device, "", time.Duration(in.Delay)*time.Second)

		// Forward message to queue
		default:
			b, found := batches[mqttMsg.Topic]
			if !found {
				fmt.Println("mqttProxy | Warning - Got MQTT message on:", mqttMsg.Topic)
				continue
			}
			rdb.LPush(ctx, b.sourceQ, mqttMsg.Payload)
		}
	}
}

// Listens for device key expirations
func keyPoll(ctx context.Context) {
	rdb, ok := ctx.Value("REDIS_CLIENT").(*redis.Client)
	if !ok {
		panic("Unable to retreive values from context")
	}

	// Subcribe to key expiration events
	subscriber := rdb.PSubscribe(ctx, "__keyevent*__:expired")
	msgChan := subscriber.Channel()

	// Redirect expired keys to LWT queue
	for msg := range msgChan {
		rdb.LPush(ctx, LWT_TOPIC, msg.Payload)
	}
}

// Monitors each redis queue
func queueManager(ctx context.Context, batches BatchMap, taskPool chan task) {
	rdb, ok := ctx.Value("REDIS_CLIENT").(*redis.Client)
	if !ok {
		panic("Unable to retreive values from context")
	}

	fmt.Println("queueManager | INFO - Monitoring queues")
	for {
		// Monitor queues of each batch
		for topic := range batches {
			// Copy batch ptr
			b := batches[topic]

			// Get source queue size
			srcLen, err := rdb.LLen(ctx, b.sourceQ).Result()
			if err != nil {
				fmt.Println("queueManager | ERROR - Unable to get source queue size:", err)
				continue
			}

			// Reset timeout if source queue isn't large enough
			if srcLen < b.minSize {
				b.t0 = time.Now()
			}

			// Get timeout (dt) for batch
			t1 := time.Now()
			dt := t1.Sub(b.t0).Seconds()

			// If batch conditions are met, exec callback
			if (srcLen >= b.minSize && dt >= b.timeout) || (srcLen >= b.maxSize) {
				// Generate unique sink queue name (prevents active sink queues from getting deleted)
				sinkQ := uuid.New().String()

				// Transfer messages to sink queue
				err := rdb.Copy(ctx, b.sourceQ, sinkQ, 0, true).Err()
				if err != nil {
					fmt.Println("queueManager | ERROR - Unable to transfer messages to sink queue:", err)
					continue
				}

				// Make sure source queue gets reset
				for {
					err = rdb.Del(ctx, b.sourceQ).Err()
					if err != nil {
						fmt.Println("queueManager | ERROR - Unable to clear source queue:", err)
						continue
					}
					break
				}

				// Reset timeout
				b.t0 = time.Now()

				// Send new task to task pool
				taskPool <- task{ctx, sinkQ, b.callback}
			}
		}
	}
}

func Start(ctx context.Context, batches BatchMap) {
	// Get CPU count
	cpus := runtime.GOMAXPROCS(0)

	// Spawn task workers
	taskChan := make(chan task)
	for i := 0; i < cpus; i++ {
		go func() {
			// Wait for new tasks
			for newTask := range taskChan {
				newTask.callback(newTask.ctx, newTask.sinkQ)
			}
		}()
	}

	// Redis
	go keyPoll(ctx)
	go queueManager(ctx, batches, taskChan)

	// Mosquitto
	mqttProxy(ctx, batches)
}
