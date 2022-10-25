/*
 * @Author: BlueBoxChamil 283040422@qq.com
 * @Date: 2022-10-12 11:09:46
 * @LastEditors: BlueBoxChamil 283040422@qq.com
 * @LastEditTime: 2022-10-13 15:18:02
 * @FilePath: \uuusb\components\my_lvgl\include\my_lvgl_mouse.h
 * @Description:
 *
 * Copyright (c) 2022 by BlueBoxChamil 283040422@qq.com, All Rights Reserved.
 */
#ifndef __my_lvgl_mouse__
#define __my_lvgl_mouse__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../components/lvgl/lvgl.h"

#define MOUSE_TIME 4

void my_mouse_init(lv_obj_t *parent);
void my_mouse_move_event_cb(lv_event_t *event);
void my_mouse_click_event_cb(lv_event_t *event);

#endif