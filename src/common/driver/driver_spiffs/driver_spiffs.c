// DRIVER_SPIFFS
// OCTOBER 3, 2025

#include "esp_err.h"
#include "esp_log.h"
#include "esp_spiffs.h"

#include "driver_spiffs.h"
#include "define_common_data_types.h"
#include "define_rtos_tasks.h"

// Extern Variables

// Local Variables
static rtos_component_type_t s_component_type;

// Local Functions

// External Functions
bool DRIVER_SPIFFS_Init(void)
{
    // Initialize Driver Spiffs

    esp_err_t ret;
    s_component_type = COMPONENT_TYPE_NON_TASK;
    esp_vfs_spiffs_conf_t config_spiffs = {
        .base_path = "/spiffs",
        .partition_label = NULL,
        .max_files = DRIVER_SPIFFS_FILES_MAX,
        .format_if_mount_failed = true
    };

    // Initialize & Mount Spiffs File System
    ret = esp_vfs_spiffs_register(&config_spiffs);

    switch(ret)
    {
        case ESP_FAIL:
            ESP_LOGE(DEBUG_TAG_DRIVER_SPIFFS, "FS Mount Or Format Failed!");
            return false;
            break;
        
        case ESP_ERR_NOT_FOUND:
            ESP_LOGE(DEBUG_TAG_DRIVER_SPIFFS, "Failed To Find Spiffs Partition!");
            return false;
            break;

        default:
            ESP_LOGE(DEBUG_TAG_DRIVER_SPIFFS, "Failed To Init - (%)!", esp_err_to_name(ret));
            return false;
            break;
    }

    ESP_LOGI(DEBUG_TAG_DRIVER_SPIFFS, "Type %u. Init", s_component_type);
    
    return true;
}