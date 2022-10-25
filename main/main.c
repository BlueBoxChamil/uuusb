/*
 * @Author: BlueBoxChamil 283040422@qq.com
 * @Date: 2022-10-11 10:45:46
 * @LastEditors: BlueBoxChamil 283040422@qq.com
 * @LastEditTime: 2022-10-12 16:14:47
 * @FilePath: \testusb\uuusb\main\main.c
 * @Description:
 *
 * Copyright (c) 2022 by BlueBoxChamil 283040422@qq.com, All Rights Reserved.
 */
// Copyright 2019-2021 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "board.h"
#include "tusb_hid.h"

#include "iot_button.h"

#define TAG "HID Example"

void obj_test_kkkey_cb(timer_t *tmr)
{
    // uint8_t keycode[1];
    // keycode[0] = HID_KEY_A;
    // tinyusb_hid_keyboard_report(keycode);
    tinyusb_hid_mouse_move_report(10, 10, 0, 0);
    ESP_LOGI(TAG, "Mouse x y");
}
esp_timer_handle_t periodic_timer;

void test_kkkey()
{
    const esp_timer_create_args_t periodic_timer_args = {
        .callback = &obj_test_kkkey_cb,
        /* name is optional, but may help identify the timer when debugging */
        .name = "periodic"}; //周期定时器配置
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));

    /* Start the timers */
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, 1000000)); // 1s回调一次
}

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lvgl_init.h"

void app_main(void)
{
    printf("esp32 sdk version :%s\n", esp_get_idf_version());
    //初始化usb hid
    /* Install tinyusb driver, Please enable `CONFIG_TINYUSB_HID_ENABLED` in menuconfig */
    tinyusb_config_t tusb_cfg = {
        .descriptor = NULL,
        .string_descriptor = NULL,
        .external_phy = false // In the most cases you need to use a `false` value
    };
    ESP_ERROR_CHECK(tinyusb_driver_install(&tusb_cfg));
    ESP_LOGI(TAG, "USB initialization DONE");
    button_cb_t button_cb = NULL;

    xTaskCreatePinnedToCore(guiTask, "gui", 4096 * 2, NULL, 1, NULL, 1);
}
