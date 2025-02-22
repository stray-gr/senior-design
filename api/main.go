package main

import (
	"crypto/tls"
	"crypto/x509"
	"net"
	"os"
	"runtime"

	"github.com/stray-gr/api/service"
	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials"
	"google.golang.org/protobuf/types/known/emptypb"
	"gorm.io/driver/postgres"
	"gorm.io/gorm"
)

type (
	// ORM model
	Sensor struct {
		EntryId    int32 `gorm:"primaryKey"`
		FacilityId int32
		Device     string
		Temp       float32
		Rh         float32
		Epoch      int64
	}

	// Server implementation
	apiServer struct {
		service.UnimplementedQueryServer
		db *gorm.DB
	}
)

// Update model's table name
func (Sensor) TableName() string {
	return "data.sensor"
}

// Stream query results using gorm
func (s *apiServer) GetSensorRows(_ *emptypb.Empty, stream service.Query_GetSensorRowsServer) error {
	rows, err := s.db.Model(&Sensor{}).Rows()
	if err != nil {
		return err
	}
	defer rows.Close()

	for rows.Next() {
		// Scan row into ORM model
		var dataRow Sensor
		s.db.ScanRows(rows, &dataRow)

		// Encode protobuf message using model
		msg := &service.SensorRows{
			EntryId:    dataRow.EntryId,
			FacilityId: dataRow.FacilityId,
			Device:     dataRow.Device,
			Temp:       dataRow.Temp,
			Rh:         dataRow.Rh,
			Epoch:      dataRow.Epoch,
		}

		// Send message to stream
		err := stream.Send(msg)
		if err != nil {
			return err
		}
	}
	return nil
}

func newServer() *apiServer {
	// Get environment variables for current facility
	API_CONN_STR, okConn := os.LookupEnv("API_CONN_STR")
	if !okConn {
		panic("Unable to get environment variables for API")
	}

	// Create GORM connection
	db, err := gorm.Open(postgres.Open(API_CONN_STR), &gorm.Config{})
	if err != nil {
		panic(err)
	}

	// Set size of GORM connection pool
	sqlDB, err := db.DB()
	if err != nil {
		panic(err)
	}
	sqlDB.SetMaxOpenConns(runtime.GOMAXPROCS(0))

	// Create and return server instance
	s := &apiServer{db: db}
	return s
}

func main() {
	// Load server certs
	cert, err := tls.LoadX509KeyPair("/certs/server.crt", "/certs/server.key")
	if err != nil {
		panic(err)
	}

	// Read CA cert
	caBytes, err := os.ReadFile("/certs/ca.crt")
	if err != nil {
		panic(err)
	}

	// Add CA cert to pool
	ca := x509.NewCertPool()
	ok := ca.AppendCertsFromPEM(caBytes)
	if !ok {
		panic("Unable to add CA cert to cert pool")
	}

	// Create TLS config
	config := &tls.Config{
		ClientAuth:   tls.RequireAndVerifyClientCert,
		Certificates: []tls.Certificate{cert},
		ClientCAs:    ca,
	}

	// Configure server and TCP listener
	s := grpc.NewServer(grpc.Creds(credentials.NewTLS(config)))
	service.RegisterQueryServer(s, newServer())
	listener, err := net.Listen("tcp", "0.0.0.0:3000")
	if err != nil {
		panic(err)
	}

	// Start server
	err = s.Serve(listener)
	if err != nil {
		panic(err)
	}
}
