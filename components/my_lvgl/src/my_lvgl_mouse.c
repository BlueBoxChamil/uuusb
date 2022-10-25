/*
 * @Author: BlueBoxChamil 283040422@qq.com
 * @Date: 2022-10-12 11:09:37
 * @LastEditors: BlueBoxChamil 283040422@qq.com
 * @LastEditTime: 2022-10-13 16:10:30
 * @FilePath: \uuusb\components\my_lvgl\src\my_lvgl_mouse.c
 * @Description:
 *
 * Copyright (c) 2022 by BlueBoxChamil 283040422@qq.com, All Rights Reserved.
 */
#include "my_lvgl_mouse.h"

void my_mouse_init(lv_obj_t *parent)
{
    lv_obj_t *btn = lv_btn_create(lv_scr_act());
    lv_obj_set_size(btn, 240, 300);
    lv_obj_center(btn);
    lv_obj_add_event_cb(btn, my_mouse_move_event_cb, LV_EVENT_PRESSING, NULL);
    lv_obj_add_event_cb(btn, my_mouse_click_event_cb, LV_EVENT_SHORT_CLICKED, NULL);
}

/**
 * @brief lvgl键盘按键回调函数
 *
 * @param e
 * 因为在这边无法调用usb hid相关的函数以及头文件，故在其他文件中实现函数
 */
