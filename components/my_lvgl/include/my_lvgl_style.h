/*
 * @Author: BlueBoxChamil 283040422@qq.com
 * @Date: 2022-09-27 13:32:27
 * @LastEditors: BlueBoxChamil 283040422@qq.com
 * @LastEditTime: 2022-10-11 14:48:07
 * @FilePath: \uuusb\components\my_lvgl\include\my_lvgl_style.h
 * @Description:
 *
 * Copyright (c) 2022 by BlueBoxChamil 283040422@qq.com, All Rights Reserved.
 */
#ifndef __my_lvgl_style__
#define __my_lvgl_style__

// #include "lvgl.h"
#include "../../components/lvgl/lvgl.h"
#include "../../lvgl/src/core/lv_obj_style.h"
// #include "../../components/lvgl/src/core/lv_obj_style.h"

void my_lv_trans_init();
void my_lv_trans(lv_obj_t *object, int num, lv_style_selector_t selector, lv_color_t color, lv_coord_t width, lv_coord_t height);

#endif