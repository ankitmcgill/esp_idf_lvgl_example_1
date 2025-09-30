// DEFINE RTOS GLOBALS
// SEPTEMBER 9, 2025

#ifndef _DEFINE_RTOS_GLOBALS_
#define _DEFINE_RTOS_GLOBALS_

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"

#define QUEUE_MODULE_WIFI_DEPTH (2)

// Queues
extern QueueHandle_t handle_queue_module_wifi;

// Event Groups
// extern EventGroupHandle_t handle_event_group_driver_wifi;
// extern EventGroupHandle_t handle_event_group_module_wifi;

#endif