idf_component_register(SRCS "driver_chipinfo.c"
                       INCLUDE_DIRS "include"
                       PRIV_REQUIRES
                            esp_hw_support
                            spi_flash
                            esp_system
                            defines
)
