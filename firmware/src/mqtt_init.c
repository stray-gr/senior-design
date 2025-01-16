#include <stdio.h>
#include <string.h>
#include "config.h"
#include "esp_event.h"
#include "esp_log.h"
#include "mqtt_client.h"
#include "msg.pb-c.h"

extern const uint8_t ca_crt_start[] asm("_binary_ca_crt_start");
extern const uint8_t ca_crt_end[] asm("_binary_ca_crt_end");

static const char *TAG = "MQTT";

static esp_mqtt5_publish_property_config_t pub_props = {
    .payload_format_indicator = 0,  // Specifies payload as bytes (not UTF-8)
};

static esp_mqtt5_subscribe_property_config_t sub_props = {
    // .subscribe_id = 1001, 
    .retain_handle = 2,           // Prevents retained pulse messages from getting sent on subscribe
    .is_share_subscribe = false,  // Sets this subscription as a unique (not shared) subscription
};

/*
 * @brief Event handler registered to receive MQTT events
 *
 * @param handler_args user data registered to the event.
 * @param base Event base for the handler(always MQTT Base in this example).
 * @param event_id The id for the received event.
 * @param event_data The data for the event, esp_mqtt_event_handle_t.
 */
static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    esp_mqtt_event_handle_t event = event_data;
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;

    switch ((esp_mqtt_event_id_t)event_id) {
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
        esp_mqtt5_client_set_subscribe_property(client, &sub_props);
        msg_id = esp_mqtt_client_subscribe(client, MQTT_PULSE_TOPIC, 0);
        ESP_LOGI(TAG, "SENT SUB REQ, msg_id = %d", msg_id);
        break;
    case MQTT_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
        break;
    case MQTT_EVENT_SUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id = %d", event->msg_id);
        break;
    case MQTT_EVENT_UNSUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id = %d", event->msg_id);
        break;
    case MQTT_EVENT_PUBLISHED:
        ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id = %d", event->msg_id);
        break;
    case MQTT_EVENT_DATA:
        ESP_LOGI(TAG, "MQTT_EVENT_DATA");
        if (strncmp(event->topic, MQTT_PULSE_TOPIC, event->topic_len) == 0) {
            // INIT message
            Data msg = DATA__INIT;
            void *buf;
            unsigned len;

            // Set message felds
            msg.device = MQTT_USER;
            msg.temp   = 10;
            msg.rh     = 99.9;
            msg.epoch  = 1733521830;

            // Serialize message
            len = data__get_packed_size(&msg);
            buf = malloc(len);
            data__pack(&msg, buf);

            // Send message
            ESP_LOGI(TAG, "RECV PULSE, sending data...");
            esp_mqtt5_client_set_publish_property(client, &pub_props);
            msg_id = esp_mqtt_client_publish(client, MQTT_DATA_TOPIC, buf, len, 0, 0);
            ESP_LOGD(TAG, "SENT DATA, msg_id = %d", msg_id);

            // Free message buffer
            free(buf);
        }
        break;
    case MQTT_EVENT_ERROR:
        ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
        if (event->error_handle->error_type == MQTT_ERROR_TYPE_TCP_TRANSPORT) {
            ESP_LOGE(TAG, "Reported from esp-tls: 0x%x", event->error_handle->esp_tls_last_esp_err);
            ESP_LOGE(TAG, "Reported from TLS stack: 0x%x", event->error_handle->esp_tls_stack_err);
            ESP_LOGE(
                TAG, "Socket errno: %d (%s)",  
                event->error_handle->esp_transport_sock_errno,
                strerror(event->error_handle->esp_transport_sock_errno)
            );
        } else if (event->error_handle->error_type == MQTT_ERROR_TYPE_CONNECTION_REFUSED) {
            ESP_LOGE(TAG, "Connection refused error: 0x%x", event->error_handle->connect_return_code);
        } else {
            ESP_LOGW(TAG, "Unknown error type: 0x%x", event->error_handle->error_type);
        }
        break;
    default:
        ESP_LOGW(TAG, "Other event id: %d", event->event_id);
        break;
    }
}

void mqtt_start(void)
{
    // Create LWT message
    LWT msg = LWT__INIT;
    msg.device = MQTT_USER;
    unsigned len = lwt__get_packed_size(&msg);
    void *buf = malloc(len);
    lwt__pack(&msg, buf);

    esp_mqtt_client_config_t mqtt_cfg = {
        .broker = {
            .address.uri = MSG_BROKER_URI,
            .verification.certificate = (const char *)ca_crt_start
        },
        .credentials = {
            // .username = MQTT_USER,
            // .authentication.password = MQTT_PASS,
        },
        .session = {
            .protocol_ver = MQTT_PROTOCOL_V_5,
            .last_will = {
                .topic = MQTT_LWT_TOPIC,
                .msg = buf,
                .msg_len = len,
                .qos = 0,
                .retain = false,
            },
        },
    };

    esp_mqtt5_connection_property_config_t conn_props = {
        .session_expiry_interval = 0,      // Session ends when connection is closed
        .maximum_packet_size = 1024,       // Max packet size (bytes)
        .receive_maximum = 1,              // Max no. of QoS 1 and 2 packets to process concurrently
        .topic_alias_maximum = 0,          // Max no. of topic aliases
        .request_resp_info = false,        // Disables request/response info from being sent
        .request_problem_info = true,      // Enables error info to be sent
        .will_delay_interval = LWT_DELAY,  // LWT delay
    };

    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt5_client_set_connect_property(client, &conn_props);
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);

    ESP_LOGI(TAG, "Connecting to %s", MSG_BROKER_URI);
    esp_mqtt_client_start(client);
    free(buf);
}