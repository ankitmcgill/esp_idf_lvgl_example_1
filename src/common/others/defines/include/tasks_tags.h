// DEFINES - TASKS TAGS
// SEPTEMBER 9, 2025

#ifndef _DEFINES_TASKS_TAGS_
#define _DEFINES_TASKS_TAGS_

#include "esp_log.h"

// Task Priority
#define TASK_PRIORITY_DRIVER_WIFI       (2)
#define TASK_PRIORITY_MODULE_WIFI       (2)

// Task Stack Depth
#define TASK_STACK_DEPTH_MODULE_WIFI    (64)

// Task Debug Tag
#define DEBUG_TAG_DRIVER_CHIPINFO       ("D.ChipInfo")
#define DEBUG_TAG_DRIVER_APPINFO        ("D.AppInfo")
#define DEBUG_TAG_DRIVER_WIFI           ("D.Wifi")
#define DEBUG_TAG_MODULE_WIFI           ("M.Wifi")

#endif