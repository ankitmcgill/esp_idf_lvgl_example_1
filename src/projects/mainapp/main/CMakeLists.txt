idf_component_register(SRCS "main.c"
                        REQUIRES
                            driver_chipinfo
                            driver_appinfo
                            driver_wifi
                            defines
                        PRIV_REQUIRES
                            spi_flash
                            nvs_flash
                            log
                        INCLUDE_DIRS "")
