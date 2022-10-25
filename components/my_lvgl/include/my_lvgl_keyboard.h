/*
 * @Author: BlueBoxChamil 283040422@qq.com
 * @Date: 2022-10-12 11:09:46
 * @LastEditors: BlueBoxChamil 283040422@qq.com
 * @LastEditTime: 2022-10-12 14:25:02
 * @FilePath: \uuusb\components\my_lvgl\include\my_lvgl_keyboard.h
 * @Description:
 *
 * Copyright (c) 2022 by BlueBoxChamil 283040422@qq.com, All Rights Reserved.
 */
#ifndef __my_lvgl_keyboard__
#define __my_lvgl_keyboard__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "my_asc2usbhid.h"
#include "../../components/lvgl/lvgl.h"


void my_keyboard_init(lv_obj_t *parent);
void my_keyboard_event_cb(lv_event_t *e);

void my_keyboard_event_cb_1(lv_event_t *e);

#endif