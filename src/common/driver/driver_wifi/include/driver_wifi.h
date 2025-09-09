// DRIVER_WIFI
// SEPTEMBER 6, 2025

#ifndef _DRIVER_WIFI_
#define _DRIVER_WIFI_

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>

#include "esp_wifi.h"

#define DRIVER_WIFI_LEN_SSID    (32)
#define DRIVER_WIFI_LED_PWD     (64)

typedef enum{
    DRIVER_WIFI_STATE_DISCONNECTED = 0,
    DRIVER_WIFI_STATE_CONNECTED,
}driver_wifi_state_t;

bool DRIVER_WIFI_Init(void);

bool DRIVER_WIFI_Connect(char* ssid, char* password);
bool DRIVER_WIFI_Disconnect(void);

#endif