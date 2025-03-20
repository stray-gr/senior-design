package main

import (
	"context"
	"os"

	"github.com/stray-gr/senior-design/batch-router/callbacks"
	"github.com/stray-gr/senior-design/batch-router/server"
)

func main() {
	// Create batches
	batches := server.BatchMap{
		"data/sensor": server.NewBatch(1, 2, 5, callbacks.SensorData),
		"lwt":         server.NewBatch(1, 2, 5, callbacks.LWT),
	}

	GROUPME_BOT_ID, okBot := os.LookupEnv("GROUPME_BOT_ID")
	DEBUG, okDebug := os.LookupEnv("DEBUG")
	if !okBot || !okDebug {
		panic("Unable to get env vars for batch router")
	}

	// Create context
	ctx := context.Background()
	ctx = context.WithValue(ctx, "BOT", GROUPME_BOT_ID)
	ctx = context.WithValue(ctx, "DEBUG", DEBUG)
	ctx = context.WithValue(ctx, "PG_CLIENT", server.NewPgClient())
	ctx = context.WithValue(ctx, "REDIS_CLIENT", server.NewRedisClient())

	// Start server
	server.Start(ctx, batches)
}
