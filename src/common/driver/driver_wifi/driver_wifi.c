// DRIVER_WIFI
// SEPTEMBER 6, 2025

#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "lwip/err.h"
#include "lwip/sys.h"

#include "driver_wifi.h"
#include "common_data_types.h"
#include "globals.h"
#include "tasks_tags.h"

// Extern Variables
EventGroupHandle_t handle_event_group_driver_wifi = NULL;

// Local Variables
static driver_wifi_state_t s_state;
static driver_wifi_state_t s_state_prev;
static component_type_t s_component_type;

// Local Functions
static void s_set_state(driver_wifi_state_t newstate);
static void s_wifi_event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);

// External Functions
bool DRIVER_WIFI_Init(void)
{
    // Initialize Driver Wifi

    wifi_init_config_t wifi_config = WIFI_INIT_CONFIG_DEFAULT();
    esp_event_handler_instance_t event_handler_got_ip;
    esp_event_handler_instance_t event_handler_any_event;

    s_component_type = COMPONENT_TYPE_TASK;
    s_state = -1;
    s_state_prev = -1;

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();
    ESP_ERROR_CHECK(esp_wifi_init(&wifi_config));

    // Register Event Handlers
    ESP_ERROR_CHECK(esp_event_handler_instance_register(
        WIFI_EVENT,
        ESP_EVENT_ANY_ID,
        &s_wifi_event_handler,
        NULL,
        &event_handler_any_event
    ));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(
        IP_EVENT,
        IP_EVENT_STA_GOT_IP,
        &s_wifi_event_handler,
        NULL,
        &event_handler_got_ip
    ));

    // Create Event Group
    handle_event_group_driver_wifi = xEventGroupCreate();
    s_set_state(DRIVER_WIFI_STATE_DISCONNECTED);

    ESP_LOGI(DEBUG_TAG_DRIVER_WIFI, "Type %u. Init", s_component_type);

    return true;
}

bool DRIVER_WIFI_Connect(char* ssid, char* password)
{
    // Connect Wifi

    wifi_config_t w_config;

    strcpy((char*)w_config.sta.ssid, ssid);
    strcpy((char*)w_config.sta.password, password);
    w_config.sta.threshold.authmode = WIFI_AUTH_WPA_WPA2_PSK;
    w_config.sta.sae_pwe_h2e = WPA3_SAE_PWE_BOTH;

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &w_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(DEBUG_TAG_DRIVER_WIFI, "Connect");

    return true;
}

bool DRIVER_WIFI_Disconnect(void)
{
    // Disconnect Wifi

    esp_wifi_disconnect();

    ESP_LOGI(DEBUG_TAG_DRIVER_WIFI, "Disconnect");

    return true;
}

static void s_set_state(driver_wifi_state_t newstate)
{
    // Driver Wifi Set State
    
    if(s_state == newstate){
        return;
    }
    
    s_state_prev = s_state;
    s_state = newstate;
    xEventGroupClearBits(
        handle_event_group_driver_wifi,
        0x00FFFFFF
    );
    xEventGroupSetBits(
        handle_event_group_driver_wifi,
        BIT_VALUE(s_state)
    );

    ESP_LOGI(DEBUG_TAG_DRIVER_WIFI, "%u -> %u", s_state_prev, s_state);
}

static void s_wifi_event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data)
{
    // Wifi Event Handler

    if(event_base == WIFI_EVENT)
    {
        if(event_id == WIFI_EVENT_STA_START)
        {
            // Wifi Station Started. Connect To Wifi
            ESP_LOGI(DEBUG_TAG_DRIVER_WIFI, "Station Started. Connecting...");

            esp_wifi_connect();
        }
        else if(event_id == WIFI_EVENT_STA_DISCONNECTED)
        {
            s_set_state(DRIVER_WIFI_STATE_DISCONNECTED);

            ESP_LOGI(DEBUG_TAG_DRIVER_WIFI, "Station Disconnected");
        }

        return;
    }

    if(event_base == IP_EVENT)
    {
        if(event_id == IP_EVENT_STA_GOT_IP)
        {
            ip_event_got_ip_t* event = (ip_event_got_ip_t*)event_data;
            s_set_state(DRIVER_WIFI_STATE_DISCONNECTED);
            
            ESP_LOGI(DEBUG_TAG_DRIVER_WIFI, "Got IP : " IPSTR, IP2STR(&(event->ip_info.ip)));
        }
        else if(event_id == IP_EVENT_STA_LOST_IP)
        {
            // Lost IP. Disconnect

            ESP_LOGI(DEBUG_TAG_DRIVER_WIFI, "Lost IP");
            
            DRIVER_WIFI_Disconnect();
        }
    }
}