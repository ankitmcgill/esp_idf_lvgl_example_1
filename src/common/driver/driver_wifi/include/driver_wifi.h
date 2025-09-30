// DRIVER_WIFI
// SEPTEMBER 6, 2025

#ifndef _DRIVER_WIFI_
#define _DRIVER_WIFI_

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>

#include "esp_wifi.h"

#define DRIVER_WIFI_LEN_SSID                    (32)
#define DRIVER_WIFI_LED_PWD                     (64)

#define DRIVER_WIFI_CHANGE_NOTIFICATION_CB_MAX  (1)

typedef enum{
    DRIVER_WIFI_STATE_IDLE,
    DRIVER_WIFI_STATE_DISCONNECTED = 0,
    DRIVER_WIFI_STATE_CONNECTED,
}driver_wifi_state_t;

typedef struct{
    driver_wifi_state_t state;
}driver_wifi_notification_t;

bool DRIVER_WIFI_Init(void);

bool DRIVER_WIFI_Connect(char* ssid, char* password);
bool DRIVER_WIFI_Disconnect(void);

bool DRIVER_WIFI_RegisterChangeNotification(QueueHandle_t q_handle, uint32_t cb_mask);

#endif