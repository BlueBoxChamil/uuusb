/*
 * @Author: BlueBoxChamil 283040422@qq.com
 * @Date: 2022-09-22 11:35:25
 * @LastEditors: BlueBoxChamil 283040422@qq.com
 * @LastEditTime: 2022-10-08 10:12:19
 * @FilePath: \20221008\components\led\include\led.h
 * @Description:
 *
 * Copyright (c) 2022 by BlueBoxChamil 283040422@qq.com, All Rights Reserved.
 */
#ifndef _LED_H_
#define _LED_H_

#include "sdkconfig.h"
#include "driver/gpio.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LED_GPIO 43 // TX引脚

void led_init();
void led_on();
void led_off();
void led_test(void);

#endif