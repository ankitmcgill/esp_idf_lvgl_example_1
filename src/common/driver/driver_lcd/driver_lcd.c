// DRIVER_LCD
// SEPTEMBER 30, 2025

#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_rgb.h"
#include "esp_lvgl_port.h"
#include "esp_check.h"

#include "driver_lcd.h"
#include "project_ui.h"
#include "define_common_data_types.h"
#include "define_rtos_globals.h"
#include "define_rtos_tasks.h"
#include "bsp.h"

// Extern Variables

// Local Variables
static rtos_component_type_t s_component_type;
static esp_lcd_panel_handle_t s_handle_panel;
static lv_display_t* s_lv_display;

// Local Functions
static esp_err_t s_rgb_lcd_init(void);
static esp_err_t s_lvgl_port_init(void);
static esp_err_t s_lvgl_config(void);
static void s_lvgl_test_display(void);

// External Functions
bool DRIVER_LCD_Init(void)
{
    // Initialize Driver Lcd

    s_component_type = COMPONENT_TYPE_TASK;

    ESP_LOGI(DEBUG_TAG_DRIVER_LCD, "Type %u. Init", s_component_type);

    s_rgb_lcd_init();
    s_lvgl_port_init();
    s_lvgl_config();

    if (lvgl_port_lock(portMAX_DELAY)) {
        // s_lvgl_test_display();
        PROJECT_UI_Init();
        lvgl_port_unlock();
    }
    
    return true;
}

static esp_err_t s_rgb_lcd_init(void)
{
    // Initial ESP RGB LCD

    esp_err_t ret = ESP_OK;

    ESP_LOGI(DEBUG_TAG_DRIVER_LCD, "RGB LCD Panel Initializing...");

    s_handle_panel = NULL;
    esp_lcd_rgb_panel_config_t panel_config = {
        .clk_src = LCD_CLK_SRC_PLL160M,
        .timings = {
            .pclk_hz = DRIVER_LCD_PIXEL_CLK_HZ,
            .h_res = DRIVER_LCD_RESOLUTION_X,
            .v_res = DRIVER_LCD_RESOLUTION_Y,
            .hsync_pulse_width = 40,
            .hsync_back_porch = 40,
            .hsync_front_porch = 48,
            .vsync_pulse_width = 23,
            .vsync_back_porch = 32,
            .vsync_front_porch = 13,
            .flags.pclk_active_neg = true
        },
        .flags.fb_in_psram = true,
        .data_width = DRIVER_LCD_DATA_WIDTH,
        .bits_per_pixel = DRIVER_LCD_BITS_PER_PIXEL,
        .num_fbs = DRIVER_LCD_NUM_FBS,
        .sram_trans_align = 4,
        .psram_trans_align = 64,
        .hsync_gpio_num = BSP_LCD_GPIO_HSYNC,
        .vsync_gpio_num = BSP_LCD_GPIO_VSYNC,
        .pclk_gpio_num = BSP_LCD_GPIO_PCLK,
        .de_gpio_num = BSP_LCD_GPIO_DE,
        .disp_gpio_num = BSP_LCD_GPIO_DISP,
        .data_gpio_nums={
            BSP_LCD_GPIO_DATA0,
            BSP_LCD_GPIO_DATA1,
            BSP_LCD_GPIO_DATA2,
            BSP_LCD_GPIO_DATA3,
            BSP_LCD_GPIO_DATA4,
            BSP_LCD_GPIO_DATA5,
            BSP_LCD_GPIO_DATA6,
            BSP_LCD_GPIO_DATA7,
            BSP_LCD_GPIO_DATA8,
            BSP_LCD_GPIO_DATA9,
            BSP_LCD_GPIO_DATA10,
            BSP_LCD_GPIO_DATA11,
            BSP_LCD_GPIO_DATA12,
            BSP_LCD_GPIO_DATA13,
            BSP_LCD_GPIO_DATA14,
            BSP_LCD_GPIO_DATA15
        }
    };

    // Create New RGB Panel With This Configuration
    ESP_GOTO_ON_ERROR(esp_lcd_new_rgb_panel(&panel_config, &s_handle_panel), err, DEBUG_TAG_DRIVER_LCD, "RGB Panel Create Fail");
    ESP_GOTO_ON_ERROR(esp_lcd_panel_init(s_handle_panel) ,err, DEBUG_TAG_DRIVER_LCD, "LCD Init Fail");

    return ret;

    err:
        if(s_handle_panel){
            esp_lcd_panel_del(s_handle_panel);
        }
        return ret;
}

static esp_err_t s_lvgl_port_init(void)
{
    lvgl_port_cfg_t config_lvgl = {
        .task_priority = 4,
        .task_stack = 6144,
        .task_affinity = -1,
        .task_max_sleep_ms = 500,
        .timer_period_ms = 5
    };

    ESP_RETURN_ON_ERROR(lvgl_port_init(&config_lvgl), DEBUG_TAG_DRIVER_LCD, "Lvgl Port Init Fail");

    return ESP_OK;
}

static esp_err_t s_lvgl_config(void)
{
    uint32_t size_buffer;

    s_lv_display = NULL;
    size_buffer = DRIVER_LCD_RESOLUTION_X * DRIVER_LCD_RESOLUTION_Y;
    lvgl_port_display_cfg_t lvgl_disp_config = {
        .panel_handle = s_handle_panel,
        .buffer_size = size_buffer,
        .double_buffer = true,
        .hres = DRIVER_LCD_RESOLUTION_X,
        .vres = DRIVER_LCD_RESOLUTION_Y,
        .monochrome = false,
        .color_format = LV_COLOR_FORMAT_RGB565,
        .rotation = {
            .swap_xy = false,
            .mirror_x = false,
            .mirror_y = false
        },
        .flags = {
            .buff_dma = true,
            .buff_spiram = true,
            .full_refresh = false,
            .direct_mode = true,
            .swap_bytes = false,
        }
    };

    lvgl_port_display_rgb_cfg_t lvgl_rgb_config = {
        .flags = {
            .bb_mode = false,
            .avoid_tearing = true
        }
    };

    s_lv_display = lvgl_port_add_disp_rgb(&lvgl_disp_config, &lvgl_rgb_config);
    
    if(!s_lv_display){
        ESP_LOGE(DEBUG_TAG_DRIVER_LCD, "Lvgl Config Failed");
    }
    
    return ESP_OK;
}

static void s_lvgl_test_display(void)
{
    lv_obj_t *scr = lv_scr_act();

    /* Label */
    lv_obj_t *label = lv_label_create(scr);

    lv_obj_set_size(scr, DRIVER_LCD_RESOLUTION_X, DRIVER_LCD_RESOLUTION_Y);
    lv_obj_set_style_bg_color(scr, lv_color_hex(0xCAD34A), LV_PART_MAIN);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_text(
        label, 
        LV_SYMBOL_BELL" Hello world Espressif and LVGL "LV_SYMBOL_BELL"\n "LV_SYMBOL_WARNING" Test LVGL Project"LV_SYMBOL_WARNING
    );    
    lv_timer_handler();   // process pending tasks
    lv_obj_update_layout(scr);
    lv_obj_update_layout(label);
    lv_obj_center(label);

    
    /* Button */
    lv_obj_t *btn = lv_btn_create(scr);
    label = lv_label_create(btn);
    lv_label_set_text_static(label, "Rotate screen");
    lv_obj_align(btn, LV_ALIGN_BOTTOM_MID, 0, -30);
}
