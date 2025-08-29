#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "driver_chipinfo.h"
#include "driver_appinfo.h"
#include "debug.h"

void app_main(void)
{
    ESP_LOGI(DEBUG_TAG_MAINAPP, "");
    ESP_LOGI(DEBUG_TAG_MAINAPP, "");
    ESP_LOGI(DEBUG_TAG_MAINAPP, "Init");

    DRIVER_CHIPINFO_Init();
    DRIVER_APPINFO_Init();

    // Print Chip Information
    esp_chip_info_t c_info;
    uint8_t c_mac[50] = {0};
    uint32_t size_flash;
    uint32_t size_ram;

    DRIVER_CHIPINFO_GetChipInfo(&c_info);
    DRIVER_CHIPINFO_GetChipID(c_mac);
    size_flash = DRIVER_CHIPINFO_GetFlashSizeBytes();
    size_ram = DRIVER_CHIPINFO_GetRamSizeBytes();

    ESP_LOGI(DEBUG_TAG_MAINAPP, "**************************");
    ESP_LOGI(DEBUG_TAG_MAINAPP, "MAC "MACSTR, MAC2STR(c_mac));
    ESP_LOGI(DEBUG_TAG_MAINAPP, "CHIP INFO: %s %s %s %s",
        CONFIG_IDF_TARGET,
        (c_info.features & CHIP_FEATURE_WIFI_BGN) ? "WIFI" : "",
        (c_info.features & CHIP_FEATURE_BLE) ? "BLE" : "",
        (c_info.features & CHIP_FEATURE_BT) ? "BT" : ""
    );
    ESP_LOGI(DEBUG_TAG_MAINAPP, "FLASH : %u MB", size_flash/(1024 * 1024));
    ESP_LOGI(DEBUG_TAG_MAINAPP, "**************************");
}
