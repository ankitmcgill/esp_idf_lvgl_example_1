// DRIVER_LCD
// SEPTEMBER 30, 2025

#include "driver_lcd.h"
#include "define_common_data_types.h"
#include "define_rtos_globals.h"
#include "define_rtos_tasks.h"

// Extern Variables

// Local Variables
static rtos_component_type_t s_component_type;

// Local Functions

// External Functions
bool DRIVER_LCD_Init(void)
{
    // Initialize Driver Lcd

    s_component_type = COMPONENT_TYPE_TASK;

    ESP_LOGI(DEBUG_TAG_DRIVER_LCD, "Type %u. Init", s_component_type);

    return true;
}