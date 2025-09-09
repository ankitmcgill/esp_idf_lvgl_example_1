idf_component_register(SRCS "driver_wifi.c"
                       INCLUDE_DIRS "include"
                       PRIV_REQUIRES
                            defines
                       REQUIRES
                            esp_wifi
                            nvs_flash
                            freertos
)
