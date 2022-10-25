/*
 * @Author: BlueBoxChamil 283040422@qq.com
 * @Date: 2022-09-22 11:39:04
 * @LastEditors: BlueBoxChamil 283040422@qq.com
 * @LastEditTime: 2022-09-22 11:39:12
 * @FilePath: \ledled\components\led\src\led.c
 * @Description:
 *
 * Copyright (c) 2022 by BlueBoxChamil 283040422@qq.com, All Rights Reserved.
 */
#include "led.h"

void led_init(void)
{
    /* Configure the IOMUX register for pad BLINK_GPIO (some pads are
       muxed to GPIO on reset already, but some default to other
       functions and need to be switched to GPIO. Consult the
       Technical Reference for a list of pads and their default
       functions.)
    */
    gpio_pad_select_gpio(LED_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);
}

void led_on(void)
{
    gpio_set_level(LED_GPIO, 1);
}

void led_off(void)
{
    gpio_set_level(LED_GPIO, 0);
}

void led_test(void)
{
    led_init();
    while (1)
    {
        led_on();
        // printf("ledled1\r\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        led_off();
        // printf("ledled2\r\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}