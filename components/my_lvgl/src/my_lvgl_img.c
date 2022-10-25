/*
 * @Author: BlueBoxChamil 283040422@qq.com
 * @Date: 2022-09-27 14:49:00
 * @LastEditors: BlueBoxChamil 283040422@qq.com
 * @LastEditTime: 2022-10-12 11:45:09
 * @FilePath: \uuusb\components\my_lvgl\src\my_lvgl_img.c
 * @Description:
 *
 * Copyright (c) 2022 by BlueBoxChamil 283040422@qq.com, All Rights Reserved.
 */
#include "my_lvgl_img.h"

static lv_obj_t *tv;
// static lv_obj_t *back_btn;

/**
 * @brief 图片库初始化
 *
 * @param parent
 */
void my_img_init(lv_obj_t *parent)
{
    tv = lv_tabview_create(parent, LV_DIR_TOP, 0);
    lv_obj_set_style_text_font(lv_scr_act(), LV_FONT_DEFAULT, 0);
    lv_obj_t *t0 = lv_tabview_add_tab(tv, "");
    lv_obj_t *t1 = lv_tabview_add_tab(tv, "");

    my_img_init_0(t0);
    my_img_init_1(t1);
}

/**
 * @brief 图片0初始化
 *
 * @param parent
 */
void my_img_init_0(lv_obj_t *parent)
{
    //秒针 使用官方图像
    // LV_IMG_DECLARE(fenzhen)

    // lv_obj_t *img = lv_img_create(parent);
    // lv_img_set_src(img, &fenzhen);
    // lv_obj_center(img);
    LV_IMG_DECLARE(touxiang)

    lv_obj_t *img = lv_img_create(parent);
    lv_img_set_src(img, &touxiang);
    lv_obj_center(img);
}
#include "stdio.h"
// #include "flash_fatfs.h"
void test_two_file();
/**
 * @brief 图片1初始化
 *
 * @param parent
 */
void my_img_init_1(lv_obj_t *parent)
{
    // //秒针 使用官方图像
    // LV_IMG_DECLARE(fenzhen)

    // lv_obj_t *img = lv_img_create(parent);
    // lv_img_set_src(img, &fenzhen);
    // lv_obj_center(img);
    // test_two_file();
    lv_obj_t *bg_img;
    bg_img = lv_img_create(parent);
    lv_img_set_src(bg_img, "F:1.bin");
    // lv_img_set_src(bg_img, "/data/test.bin");
    lv_obj_center(bg_img);
}