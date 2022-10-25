/*
 * @Author: BlueBoxChamil 283040422@qq.com
 * @Date: 2022-10-12 11:09:37
 * @LastEditors: BlueBoxChamil 283040422@qq.com
 * @LastEditTime: 2022-10-12 11:35:43
 * @FilePath: \uuusb\components\my_lvgl\src\my_lvgl_keyboard.c
 * @Description:
 *
 * Copyright (c) 2022 by BlueBoxChamil 283040422@qq.com, All Rights Reserved.
 */
#include "my_lvgl_keyboard.h"

void my_keyboard_init(lv_obj_t *parent)
{
    lv_obj_t *obj = lv_keyboard_create(parent);
    lv_keyboard_set_mode(obj, LV_KEYBOARD_MODE_TEXT_UPPER);
    lv_obj_add_event_cb(obj, my_keyboard_event_cb_1, LV_EVENT_ALL, NULL);
}

/**
 * @brief lvgl键盘按键回调函数
 *
 * @param e
 * 因为在这边无法调用usb hid相关的函数以及头文件，故在其他文件中实现函数
 */
void my_keyboard_event_cb(lv_event_t *e)
{
    my_keyboard_event_cb_1(e);
}