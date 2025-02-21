package main

import (
	"context"
	"os"
	"runtime"
	"strconv"

	"github.com/stray-gr/senior-design/batch-router/callbacks"
	"github.com/stray-gr/senior-design/batch-router/server"
	"gorm.io/driver/postgres"
	"gorm.io/gorm"
)

func main() {
	// Create batches
	batches := server.BatchMap{
		"data/sensor": server.NewBatch("sen_src", 1, 2, 5, callbacks.SensorData),
		"lwt":         server.NewBatch("lwt_src", 1, 2, 5, callbacks.LWT),
	}

	// Get Postgres environment variables for current facility
	F_CONN_STR, okConn := os.LookupEnv("F_CONN_STR")
	F_ID, okID := os.LookupEnv("F_ID")
	if !okConn || !okID {
		panic("Unable to get environment variables for Postgres")
	}

	// Convert facility ID from string to int32
	fID, err := strconv.ParseInt(F_ID, 10, 32)
	if err != nil {
		panic(err)
	}
	id := int32(fID)

	// Create GORM connection
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

	// Create context and add GORM connection details
	ctx := context.Background()
	ctx = context.WithValue(ctx, "DB", db)
	ctx = context.WithValue(ctx, "ID", id)

	// Start server
	server.Start(ctx, batches)
}
