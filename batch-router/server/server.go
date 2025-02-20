package server

import (
	"context"
	"fmt"
	"os"
	"runtime"
	"time"

	"github.com/google/uuid"
	"github.com/redis/go-redis/v9"
)

type batch struct {
	sourceQ  string
	minSize  int64
	maxSize  int64
	timeout  float64
	callback cb
	t0       time.Time // ONLY FIELD THAT GETS MUTATED (by queuePoll)
}

type BatchMap = map[string]*batch

type cb = func(context.Context, string)

type task struct {
	ctx      context.Context
	sinkQ    string
	callback cb
}

// Creates batch
func NewBatch(sourceQ string, minSize, maxSize int, timeout float64, callback cb) *batch {
	b := batch{
		sourceQ,
		int64(minSize),
		int64(maxSize),
		timeout,
		callback,
		time.Now(),
	}

	return &b
}

// Queues new messages
func msgPoll(ctx context.Context, rdb *redis.Client, batches BatchMap) {
	// Make array to store topic names
	topicNames := make([]string, len(batches))

	// Add topic names to arrays
	itr := 0
	for k := range batches {
		topicNames[itr] = k
		itr += 1
	}

	// Subscribe to topics and create a message channel
	subscriber := rdb.PSubscribe(ctx, topicNames...)
	msgChan := subscriber.Channel()

	// For each message published to the channel, queue it
	for redisMsg := range msgChan {
		b, exists := batches[redisMsg.Pattern]
		if exists {
			rdb.LPush(ctx, b.sourceQ, redisMsg.Payload)
		}
	}
}

// Monitors each queue
func queuePoll(ctx context.Context, rdb *redis.Client, batches BatchMap, taskPool chan task) {
	for {
		// Monitor queues of each batch
		for topic := range batches {
			// Copy batch ptr
			b := batches[topic]

			// Get source queue size
			srcLen, err := rdb.LLen(ctx, b.sourceQ).Result()
			if err != nil {
				fmt.Println("SERVER | ERROR - Unable to get source queue size:", err)
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
					fmt.Println("SERVER | ERROR - Unable to transfer messages to sink queue:", err)
					continue
				}

				// Reset source queue
				err = rdb.Del(ctx, b.sourceQ).Err()
				if err != nil {
					fmt.Println("SERVER | ERROR - Unable to clear source queue:", err)
					continue
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

	// Create Redis conneciton pool
	REDIS_ADDR, ok := os.LookupEnv("REDIS_ADDR")
	if !ok {
		panic("Mising environment variables for Redis")
	}

	rdb := redis.NewClient(&redis.Options{
		Addr:     REDIS_ADDR,
		Username: "",
		Password: "",
		DB:       0,
		PoolSize: cpus,
	})

	fmt.Println("SERVER | Connected to Redis")

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

	// Spawn message and queue pollers
	go msgPoll(ctx, rdb, batches)
	queuePoll(ctx, rdb, batches, taskChan)
}
