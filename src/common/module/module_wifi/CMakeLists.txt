idf_component_register(SRCS "module_wifi.c"
                       INCLUDE_DIRS "include"
                       PRIV_REQUIRES
                            driver_wifi
                            defines
                            project_defines
                       REQUIRES
                            esp_wifi
                            nvs_flash
                            freertos
)
