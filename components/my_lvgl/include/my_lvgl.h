/*
 * @Author: BlueBoxChamil 283040422@qq.com
 * @Date: 2022-09-27 13:32:27
 * @LastEditors: BlueBoxChamil 283040422@qq.com
 * @LastEditTime: 2022-10-12 14:27:16
 * @FilePath: \uuusb\components\my_lvgl\include\my_lvgl.h
 * @Description:
 *
 * Copyright (c) 2022 by BlueBoxChamil 283040422@qq.com, All Rights Reserved.
 */
#ifndef __my_lvgl__
#define __my_lvgl__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../components/lvgl/lvgl.h"
#include "my_lvgl_style.h"
#include "my_lvgl_img.h"
#include "my_asc2usbhid.h"
#include "my_lvgl_keyboard.h"
#include "my_lvgl_mouse.h"

void main_lvgl_demo(lv_obj_t *parent);

static void scroll_event_cb(lv_event_t *e);

void my_lvgl_func_init();

void my_lvgl_func_button_init(lv_obj_t *btn, lv_obj_t *label, char *name, lv_event_cb_t call_back);
void my_lvgl_func_0_callback(lv_event_t *event);
void my_lvgl_func_1_callback(lv_event_t *event);
void my_lvgl_func_2_callback(lv_event_t *event);

bool is_object_null(lv_obj_t *temp);
lv_obj_t *switch_button(uint8_t i, lv_obj_t *temp);
lv_obj_t *switch_lable(lv_obj_t *btn_temp, lv_obj_t *label_temp);

#endif