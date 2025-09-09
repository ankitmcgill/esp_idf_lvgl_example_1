idf_component_register(SRCS "module_wifi.c"
                       INCLUDE_DIRS "include"
                       PRIV_REQUIRES
                            defines
                            driver_wifi
                       REQUIRES
                            esp_wifi
                            nvs_flash
)
