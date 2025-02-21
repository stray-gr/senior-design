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

const DEBUG = true

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
func SensorData(ctx context.Context, rdb *redis.Client, sinkQ string) {
	fmt.Println("SERVER | SensorData callback on:", sinkQ)

	// Get DB connection pool and facility ID from context
	db, okDB := ctx.Value("DB").(*gorm.DB)
	id, okID := ctx.Value("ID").(int32)
	if !okDB || !okID {
		fmt.Println("SERVER | ERROR - SensorData: Unable to retreive values from context")
		return
	}

	// Read queue length
	sinkLen, err := rdb.LLen(ctx, sinkQ).Result()
	if err != nil {
		fmt.Println("SERVER | ERROR - SensorData:", err)
		return
	}

	// Commit data to DB
	db.Transaction(func(tx *gorm.DB) error {
		i := 0
		for i < int(sinkLen) {
			// Consume protobuf message or try again
			pb, err := rdb.RPop(ctx, sinkQ).Bytes()
			if err != nil {
				fmt.Println("SERVER | ERROR - SensorData:", err)
				continue
			}

			// Message consumed, update count
			i += 1

			// Decode protobuf message or skip it
			in := &msg.SensorData{}
			err = proto.Unmarshal(pb, in)
			if err != nil {
				fmt.Println("SERVER | ERROR - SensorData:", err)
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
			fmt.Println("SERVER | ERROR - SensorData:", err)
			continue
		}
		break
	}

	if DEBUG {
		// Encode LWT message
		lwt := &msg.LWT{
			Device: "client",
			Delay:  0,
		}
		out, err := proto.Marshal(lwt)
		if err != nil {
			return
		}

		// Create test queue
		rdb.LPush(ctx, "test", out)
		rdb.LPush(ctx, "test", out)

		// Call LWT
		LWT(ctx, rdb, "test")
	}
}

// NOTE: Make sure to RPOP when consuming
func LWT(ctx context.Context, rdb *redis.Client, sinkQ string) {
	fmt.Println("SERVER | LWT callback on:", sinkQ)

	// Get Bot ID from context
	botID, okBot := ctx.Value("BOT").(string)
	if !okBot {
		fmt.Println("SERVER | ERROR - LWT: Unable to retreive values from context")
		return
	}

	// Read queue length
	sinkLen, err := rdb.LLen(ctx, sinkQ).Result()
	if err != nil {
		fmt.Println("SERVER | ERROR - LWT:", err)
		return
	}

	// Start outage report
	var sb strings.Builder
	sb.WriteString("The following device(s) have shut down:\n")

	i := 0
	for i < int(sinkLen) {
		// Consume protobuf message or try again
		pb, err := rdb.RPop(ctx, sinkQ).Bytes()
		if err != nil {
			fmt.Println("SERVER | ERROR - LWT:", err)
			continue
		}

		// Message consumed, update count
		i += 1

		// Decode protobuf message or skip it
		in := &msg.LWT{}
		err = proto.Unmarshal(pb, in)
		if err != nil {
			fmt.Println("SERVER | ERROR - LWT:", err)
			continue
		}

		// Collect data into string
		sb.WriteString(fmt.Sprintf("> %s\n", in.Device))
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
		fmt.Println("SERVER | ERROR - LWT:", err)
	} else {
		fmt.Println("SERVER | LWT:", resp.Status)
	}

	// Make sure sink queue gets deleted
	for {
		err := rdb.Del(ctx, sinkQ).Err()
		if err != nil {
			fmt.Println("SERVER | ERROR - LWT:", err)
			continue
		}
		break
	}
}
