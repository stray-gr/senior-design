package callbacks

import (
	"context"
	"fmt"
	"net/http"
	"net/url"
	"strings"

	"github.com/redis/go-redis/v9"
	"github.com/stray-gr/senior-design/batch-router/msg"
	"google.golang.org/protobuf/proto"
	"gorm.io/gorm"
)

// ORM model
type Sensor struct {
	EntryId    int32 `gorm:"primaryKey"`
	FacilityId int32
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
	fmt.Println("SensorData | Callback with queue:", sinkQ)

	db, okDB := ctx.Value("DB").(*gorm.DB)
	id, okID := ctx.Value("ID").(int32)
	rdb, okRDB := ctx.Value("REDIS_CLIENT").(*redis.Client)
	DEBUG, okDebug := ctx.Value("DEBUG").(string)
	if !okDB || !okID || !okRDB || !okDebug {
		panic("Unable to retreive values from context")
	}

	// Read queue length
	sinkLen, err := rdb.LLen(ctx, sinkQ).Result()
	if err != nil {
		fmt.Println("SensorData | ERROR - LLen:", err)
		return
	}

	// Commit data to DB
	db.Transaction(func(tx *gorm.DB) error {
		i := 0
		for i < int(sinkLen) {
			// Consume protobuf message or try again
			pb, err := rdb.RPop(ctx, sinkQ).Bytes()
			if err != nil {
				fmt.Println("SensorData | ERROR - RPop:", err)
				continue
			}

			// Message consumed, update count
			i += 1

			// Decode protobuf message or skip it
			in := &msg.SensorData{}
			err = proto.Unmarshal(pb, in)
			if err != nil {
				fmt.Println("SensorData | ERROR - PB Unmarshal:", err)
				continue
			}

			// Insert data into DB or rollback transaction
			entry := &Sensor{
				FacilityId: id,
				Device:     in.Device,
				Temp:       in.Temp,
				Rh:         in.Rh,
				Epoch:      in.Epoch,
			}
			err = tx.Create(entry).Error
			if err != nil {
				return err
			}
		}

		// Commit transaction
		return nil
	})

	// Make sure sink queue gets deleted
	for {
		err := rdb.Del(ctx, sinkQ).Err()
		if err != nil {
			fmt.Println("SensorData | ERROR - Del:", err)
			continue
		}
		break
	}

	if DEBUG != "0" {
		// Create test queue
		rdb.LPush(ctx, "test", "client")
		rdb.LPush(ctx, "test", "client")

		// Call LWT
		LWT(ctx, "test")
	}
}

// NOTE: Make sure to RPOP when consuming
func LWT(ctx context.Context, sinkQ string) {
	fmt.Println("LWT | Callback with queue:", sinkQ)

	// Get Bot ID and Redis client from context
	botID, okBot := ctx.Value("BOT").(string)
	rdb, okRDB := ctx.Value("REDIS_CLIENT").(*redis.Client)
	if !okBot || !okRDB {
		panic("Unable to retreive values from context")
	}

	// Read queue length
	sinkLen, err := rdb.LLen(ctx, sinkQ).Result()
	if err != nil {
		fmt.Println("LWT | ERROR - LLen:", err)
		return
	}

	// Start outage report
	var sb strings.Builder
	sb.WriteString("The following device(s) have shut down:\n")

	i := 0
	for i < int(sinkLen) {
		// Consume protobuf message or try again
		devName, err := rdb.RPop(ctx, sinkQ).Result()
		if err != nil {
			fmt.Println("LWT | ERROR - RPop:", err)
			continue
		}

		// Message consumed, update count
		i += 1

		// Collect data into string
		sb.WriteString(fmt.Sprintf("> %s\n", devName))
	}

	// Send outage report
	urlForm := url.Values{
		"bot_id": {botID},
		"text":   {sb.String()},
	}
	resp, err := http.Post(
		fmt.Sprintf("https://api.groupme.com/v3/bots/post?%s", urlForm.Encode()),
		"application/x-www-form-urlencoded", nil,
	)
	if err != nil {
		fmt.Println("LWT | ERROR - Post:", err)
	} else {
		fmt.Println("LWT | INFO - Post:", resp.Status)
	}

	// Make sure sink queue gets deleted
	for {
		err := rdb.Del(ctx, sinkQ).Err()
		if err != nil {
			fmt.Println("LWT | ERROR - Del:", err)
			continue
		}
		break
	}
}
