#include <stdio.h>
#include <string.h>
#include "config.h"
#include "esp_log.h"
#include "mqtt_init.h"
#include "net_init.h"

// static const char *TAG = "MAIN";

void app_main(void)
{
    wifi_connect();
    mqtt_start();
}