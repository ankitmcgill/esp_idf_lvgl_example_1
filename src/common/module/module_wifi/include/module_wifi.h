// MODULE_WIFI
// SEPTEMBER 6, 2025

#ifndef _MODULE_WIFI_
#define _MODULE_WIFI_

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>

#include "driver_wifi.h"

typedef enum{
    MODULE_WIFI_STATE_IDLE = 0,
    MDOULE_WIFI_CHECK_PROVISIONED,
    MODULE_WIFI_STATE_CONNECT_DEFAULT,
    MODULE_WIFI_STATE_PROVISION_SMARTCONFIG,
    MODULE_WIFI_STATE_CONNECTING,
    MODULE_WIFI_STATE_CONNECTED,
    MODULE_WIFI_STATE_DISCONNECTING,
    MODULE_WIFI_STATE_DISCONNECTED,
}module_wifi_state_t;

bool MODULE_WIFI_Init(void);

#endif