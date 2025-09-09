// MODULE_WIFI
// SEPTEMBER 6, 2025

#include "module_wifi.h"
#include "common_data_types.h"
#include "tasks_tags.h"

// Local Variables
static component_type_t s_component_type;

// Local Functions

// External Functions
bool MODULE_WIFI_Init(void)
{
    // Initialize Module Wifi

    s_component_type = COMPONENT_TYPE_TASK;

    ESP_LOGI(DEBUG_TAG_MODULE_WIFI, "Type %u. Init", s_component_type);

    return true;
}

