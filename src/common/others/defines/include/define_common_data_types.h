// DEFINE COMMON DATA TYPES
// SEPTEMBER 9, 2025

#ifndef _DEFINE_COMMON_DATA_TYPES_
#define _DEFINE_COMMON_DATA_TYPES_

#include "driver_wifi.h"

#define BIT_VALUE(x)    (1 << x)
typedef enum{
    COMPONENT_TYPE_NON_TASK = 0,
    COMPONENT_TYPE_TASK
}rtos_component_type_t;

typedef enum{
    NOTIFICATION_TYPE_DRIVER_WIFI = 0
}notification_type_mask_t;

typedef struct{
    uint32_t mask;
    union{
        driver_wifi_notification_t notification_driver_wifi;
    }notification;
}notification_type_t;

#endif