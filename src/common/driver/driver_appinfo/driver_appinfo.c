// DRIVER_APPINFO
// AUGUST 26, 2025

#include "driver_appinfo.h"
#include "debug.h"

extern const esp_app_desc_t esp_app_desc;

// Local Variables

// Local Functions

// External Functions
bool DRIVER_APPINFO_Init(void)
{
    //Initialize DRIVER_CHIPINFO

    ESP_LOGI(DEBUG_TAG_DRIVER_APPINFO, "Init");

    return true;
}

bool DRIVER_APPINFO_GetProjectName(char* str)
{
    // Return Project Name

    sprintf(str, "%s", esp_app_desc.project_name);

    return true;
}

bool DRIVER_APPINFO_GetCompileDateTime(char* str)
{
    // Return Compile Date & Time

    sprintf(str, "%s %s", 
        esp_app_desc.time,
        esp_app_desc.date);

    return true;
}

bool DRIVER_APPINFO_GetGitDetails(char* str)
{
    // Return Git Details

    sprintf(str, "Branch : %s Hash : %s Tag : %s", 
        GIT_BRANCH,
        GIT_HASH,
        GIT_TAG);

    return true;
}

bool DRIVER_APPINFO_GetIDFVersion(char* str)
{
    // Return IDF Version

    sprintf(str, "%u.%u.%u",
        ESP_IDF_VERSION_MAJOR,
        ESP_IDF_VERSION_MINOR,
        ESP_IDF_VERSION_PATCH
    );

    return true;
}