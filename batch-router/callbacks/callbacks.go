package callbacks

import (
	"context"
	"fmt"
)

// NOTE: Make sure to RPOP when consuming
func SensorData(ctx context.Context, sinkQ string) {
	fmt.Println("callback on: ", sinkQ)

	// https://gorm.io/docs/context.html
	db, ok := ctx.Value("DB").(string)
	if !ok {
		fmt.Println("SERVER | ERROR - Unable to get DB connection pool")
		return
	}

	fmt.Println(db)
}

// NOTE: Make sure to RPOP when consuming
func LWT(ctx context.Context, sinkQ string) {
	fmt.Println("callback on: ", sinkQ)
}
