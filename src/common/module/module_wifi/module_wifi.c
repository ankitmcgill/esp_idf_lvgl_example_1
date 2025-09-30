// MODULE_WIFI
// SEPTEMBER 6, 2025

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "module_wifi.h"
#include "define_common_data_types.h"
#include "define_rtos_globals.h"
#include "define_rtos_tasks.h"
#include "project_defines.h"

// Extern Variables
QueueHandle_t handle_queue_module_wifi;

// Local Variables
static module_wifi_state_t s_state;
static module_wifi_state_t s_state_prev;
static rtos_component_type_t s_component_type;
static TaskHandle_t s_task_handle;
static notification_type_t s_notification;

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
    s_set_state(MODULE_WIFI_STATE_IDLE);

    // Create Queue
    handle_queue_module_wifi = xQueueCreate(
        QUEUE_MODULE_WIFI_DEPTH,
        sizeof(notification_type_t)
    );

    // Create Task
    xTaskCreate(
        s_task_function,
        "t-m-wifi",
        TASK_STACK_DEPTH_MODULE_WIFI,
        NULL,
        TASK_PRIORITY_MODULE_WIFI,
        &s_task_handle
    );

    // Register Change Notification - Driver Wifi
    DRIVER_WIFI_RegisterChangeNotification(
        handle_queue_module_wifi,
        (1 << NOTIFICATION_TYPE_DRIVER_WIFI)
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

    ESP_LOGI(DEBUG_TAG_MODULE_WIFI, "%u -> %u", s_state_prev, s_state);
}

static void s_task_function(void *pvParameters)
{
    // Task Function

    xQueueReceive(
        handle_queue_module_wifi,
        (void*)&s_notification,
        portMAX_DELAY
    );

    if(s_notification.mask == (1 << MODULE_WIFI_CHANGE_SOURCE_TYPE_DRIVER_WIFI))
    {
        // Driver Wifi Notification
    }

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

        vTaskDelay(pdMS_TO_TICKS(500));
    };

    vTaskDelete(NULL);
}