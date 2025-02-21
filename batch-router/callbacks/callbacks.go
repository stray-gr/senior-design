package callbacks

import (
	"context"
	"fmt"

	"gorm.io/gorm"
)

// ORM model
type Sensor struct {
	EntryId    int32 `gorm:"primaryKey"`
	FacilityId int32 `gorm:"primaryKey;autoIncrement:false"`
	Device     string
	Temp       float32
	Rh         float32
	Epoch      int64
}

// Updates model's table name
// https://gorm.io/docs/conventions.html#TableName
func (Sensor) TableName() string {
	return "data.sensor"
}

// NOTE: Make sure to RPOP when consuming
func SensorData(ctx context.Context, sinkQ string) {
	fmt.Println("SERVER | SensorData callback on:", sinkQ)

	db, ok := ctx.Value("DB").(*gorm.DB)
	if !ok {
		fmt.Println("SERVER | ERROR - Unable to get DB connection pool")
		return
	}

	// https://gorm.io/docs/transactions.html#Transaction
	// https://gorm.io/docs/create.html

	// https://gorm.io/docs/create.html#Batch-Insert

	sqlDB, err := db.DB()
	if err != nil {
		fmt.Println("SERVER | ERROR - SensorData Callback:", err)
	}

	fmt.Println(sqlDB.Stats().MaxOpenConnections)
}

// NOTE: Make sure to RPOP when consuming
func LWT(ctx context.Context, sinkQ string) {
	fmt.Println("SERVER | LWT callback on:", sinkQ)
}
