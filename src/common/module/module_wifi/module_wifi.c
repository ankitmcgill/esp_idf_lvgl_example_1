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
static module_wifi_state_t s_state_prev;
static component_type_t s_component_type;
static TaskHandle_t s_task_handle;

// Local Functions
static void s_set_state(module_wifi_state_t newstate);
static void s_task_function(void *pvParameters);

// External Functions
bool MODULE_WIFI_Init(void)
{
    // Initialize Module Wifi

    s_component_type = COMPONENT_TYPE_TASK;
    s_state = -1;
    s_state_prev = -1;

    // Create Event Group
    handle_event_group_module_wifi = xEventGroupCreate();

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

static void s_set_state(module_wifi_state_t newstate)
{
    // Module Wifi Set State
    
    if(s_state == newstate){
        return;
    }

    s_state_prev = s_state;
    s_state = newstate;
    xEventGroupClearBits(
        handle_event_group_module_wifi,
        0x00FFFFFF
    );
    xEventGroupSetBits(
        handle_event_group_module_wifi,
        BIT_VALUE(s_state)
    );

    ESP_LOGI(DEBUG_TAG_MODULE_WIFI, "%u -> %u", s_state_prev, s_state);
}

static void s_task_function(void *pvParameters)
{
    // Task Function

    uint32_t event_value;

    while(true){
        switch(s_state)
        {
            case MODULE_WIFI_STATE_IDLE:
                s_set_state(MDOULE_WIFI_CHECK_PROVISIONED);
                break;

            case MDOULE_WIFI_CHECK_PROVISIONED:
                s_set_state(MODULE_WIFI_STATE_CONNECT_DEFAULT);
                break;
            
            case MODULE_WIFI_STATE_CONNECT_DEFAULT:
                #if defined(DEFAULT_WIFI_SSID) && defined(DEFAULT_WIFI_PASSWORD)
                    if(strlen(DEFAULT_WIFI_SSID)!=0 && strlen(DEFAULT_WIFI_PASSWORD)!=0)
                    {
                        ESP_LOGI(DEBUG_TAG_MODULE_WIFI, "Connecting To Default Wifi: %s", DEFAULT_WIFI_SSID);
                        
                        DRIVER_WIFI_Connect(
                            DEFAULT_WIFI_SSID,
                            DEFAULT_WIFI_PASSWORD
                        );
                        s_set_state(MODULE_WIFI_STATE_CONNECTING);
                    }
                    break;
                #endif

                // Default Wifi SSID Or Password Not Avaialable
                s_set_state(MODULE_WIFI_STATE_PROVISION_SMARTCONFIG);
                break;

            case MODULE_WIFI_STATE_PROVISION_SMARTCONFIG:
                break;
            
            case MODULE_WIFI_STATE_CONNECTING:
                ESP_LOGI(DEBUG_TAG_MODULE_WIFI, "WiFi Connecting...");
                break;
            
            case MODULE_WIFI_STATE_CONNECTED:
                ESP_LOGI(DEBUG_TAG_MODULE_WIFI, "WiFi Connected");
                break;
            
            case MODULE_WIFI_STATE_DISCONNECTED:
                ESP_LOGI(DEBUG_TAG_MODULE_WIFI, "WiFi Connected");
                
                // Re-start Wifi Connection Cycle
                s_set_state(MODULE_WIFI_STATE_IDLE);
                break;

            default:
                break;
        }

        event_value = xEventGroupWaitBits(
            handle_event_group_driver_wifi,
            BIT_VALUE(DRIVER_WIFI_STATE_CONNECTED)|
            BIT_VALUE(DRIVER_WIFI_STATE_DISCONNECTED),
            pdFALSE,
            pdFALSE,
            portMAX_DELAY
        );

        if(event_value & BIT_VALUE(DRIVER_WIFI_STATE_CONNECTED))
        {
            // Wifi Connected
            
            s_set_state(DRIVER_WIFI_STATE_CONNECTED);
        }

        if(event_value & BIT_VALUE(DRIVER_WIFI_STATE_DISCONNECTED))
        {
            // Wifi Disconnected

            s_set_state(DRIVER_WIFI_STATE_DISCONNECTED);
        }

        vTaskDelay(pdMS_TO_TICKS(500));
    };

    vTaskDelete(NULL);
}