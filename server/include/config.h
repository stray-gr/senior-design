#ifndef PROJECT_CONFIG
#define PROJECT_CONFIG

// Database Connection Pool Max Size
#define MAX_DB_CONN_POOL_SIZE 4

// MQTT Cert name
#define BROKER_CRT "broker-ca.crt"

// MQTT Usernames
#define MQTT_CLIENT_USER "dev-1"
#define MQTT_CLOCK_USER "clock"
#define MQTT_SERVER_USER "server"

// MQTT Topics
#define MQTT_DATA_TOPIC "data/sensor"
#define MQTT_LWT_TOPIC "data/lwt"
#define MQTT_PULSE_TOPIC "pulse"

#endif