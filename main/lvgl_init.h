/*
 * @Author: BlueBoxChamil 283040422@qq.com
 * @Date: 2022-10-08 14:34:20
 * @LastEditors: BlueBoxChamil 283040422@qq.com
 * @LastEditTime: 2022-10-11 15:20:50
 * @FilePath: \uuusb\main\lvgl_init.h
 * @Description:
 *
 * Copyright (c) 2022 by BlueBoxChamil 283040422@qq.com, All Rights Reserved.
 */
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "lvgl.h"
#include "freertos/semphr.h"
#include "esp_system.h"

/* Littlevgl specific */
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#include "lvgl_helpers.h"
#include "../components/lvgl/src/hal/lv_hal_disp.h"

#define LV_TICK_PERIOD_MS 1
#define BUF_W 20
#define BUF_H 10

void lv_tick_task(void *arg);
void guiTask(void *pvParameter);
void Show_State();