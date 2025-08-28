idf_component_register(SRCS "main.c"
                        REQUIRES
                            driver_chipinfo
                            driver_appinfo
                            defines
                        PRIV_REQUIRES spi_flash
                        INCLUDE_DIRS "")
