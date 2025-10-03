// DRIVER_LCD
// SEPTEMBER 30, 2025

#ifndef _DRIVER_LCD_
#define _DRIVER_LCD_

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>

#define DRIVER_LCD_PIXEL_CLK_HZ     (18 * 1000 * 1000)
#define DRIVER_LCD_RESOLUTION_X     (800)
#define DRIVER_LCD_RESOLUTION_Y     (480)
#define DRIVER_LCD_DATA_WIDTH       (16)
#define DRIVER_LCD_BITS_PER_PIXEL   (16)
#define DRIVER_LCD_NUM_FBS          (2)

bool DRIVER_LCD_Init(void);

#endif