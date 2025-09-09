// MODULE_WIFI
// SEPTEMBER 6, 2025

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "module_wifi.h"
#include "common_data_types.h"
#include "globals.h"
#include "tasks_tags.h"
#include "project_defines.h"

// Extern Variables
EventGroupHandle_t handle_event_group_module_wifi;

// Local Variables
static module_wifi_state_t s_state;
static component_type_t s_component_type;
static TaskHandle_t s_task_handle;

// Local Functions
static void s_module_wifi_set_state(module_wifi_state_t newstate);
static void s_task_function(void *pvParameters);

// External Functions
bool MODULE_WIFI_Init(void)
{
    // Initialize Module Wifi

    s_component_type = COMPONENT_TYPE_TASK;
    s_state = -1;

    // Create Event Group
    handle_event_group_module_wifi = xEventGroupCreate();
    s_module_wifi_set_state(DRIVER_WIFI_STATE_DISCONNECTED);

    // Create Task
    xTaskCreate(
        s_task_function,
        "t-m-wifi",
        TASK_STACK_DEPTH_MODULE_WIFI,
        NULL,
        TASK_PRIORITY_MODULE_WIFI,
        &s_task_handle
    );

    ESP_LOGI(DEBUG_TAG_MODULE_WIFI, "Type %u. Init", s_component_type);

    return true;
}

static void s_module_wifi_set_state(module_wifi_state_t newstate)
{
    // Module Wifi Set State
    
    module_wifi_state_t old_state = s_state;
    s_state = newstate;
    xEventGroupClearBits(
        handle_event_group_module_wifi,
        0x00FFFFFF
    );
    xEventGroupSetBits(
        handle_event_group_module_wifi,
        (1 << s_state)
    );
    s_state = newstate;

    ESP_LOGD(DEBUG_TAG_MODULE_WIFI, "%u -> %u", old_state, s_state);
}

static void s_task_function(void *pvParameters)
{
    // Task Function

    while(true){
        vTaskDelay(pdMS_TO_TICKS(500));

        ESP_LOGE("uuuuu", "hello");
    };

    vTaskDelete(NULL);
}
