package main

import (
	"context"

	"github.com/stray-gr/senior-design/batch-router/callbacks"
	"github.com/stray-gr/senior-design/batch-router/server"
)

func main() {
	batches := server.BatchMap{
		"data/sensor": server.NewBatch("sen_src", 1, 2, 5, callbacks.SensorData),
		"lwt":         server.NewBatch("lwt_src", 1, 2, 5, callbacks.LWT),
	}

	ctx := context.Background()
	ctx = context.WithValue(ctx, "DB", "DB Connection Pool")

	server.Start(ctx, batches)
}
