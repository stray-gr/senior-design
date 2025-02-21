package main

import "github.com/stray-gr/api/service"

// https://github.com/grpc/grpc-go/blob/master/examples/route_guide/server/server.go
// Use `ListFeatures` as an example
type apiServer struct {
	service.UnimplementedQueryServer
}

// https://gorm.io/docs/advanced_query.html#Iteration
// Stream query results using gorm
