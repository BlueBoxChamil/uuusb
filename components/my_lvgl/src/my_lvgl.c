/*
 * @Author: BlueBoxChamil 283040422@qq.com
 * @Date: 2022-09-27 13:32:23
 * @LastEditors: BlueBoxChamil 283040422@qq.com
 * @LastEditTime: 2022-10-12 14:28:31
 * @FilePath: \uuusb\components\my_lvgl\src\my_lvgl.c
 * @Description:
 *
 * Copyright (c) 2022 by BlueBoxChamil 283040422@qq.com, All Rights Reserved.
 */
#include "my_lvgl.h"

#define BUTTON_NUM 9

lv_obj_t *my_lvgl_cont;
lv_obj_t *btn0, *btn1, *btn2, *btn3, *btn4, *btn5, *btn6, *btn7, *btn8;
lv_obj_t *label_0, *label_1, *label_2, *label_3, *label_4, *label_5, *label_6, *label_7, *label_8;

void main_lvgl_demo(lv_obj_t *parent)
{
    lv_theme_default_init(NULL, lv_palette_main(LV_PALETTE_GREEN), lv_palette_main(LV_PALETTE_YELLOW), 0,
                          LV_FONT_DEFAULT);

    my_lvgl_cont = lv_obj_create(lv_scr_act());
    lv_obj_set_size(my_lvgl_cont, 240, 280);
    lv_obj_center(my_lvgl_cont);
    lv_obj_set_flex_flow(my_lvgl_cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_add_event_cb(my_lvgl_cont, scroll_event_cb, LV_EVENT_SCROLL, NULL);
    lv_obj_set_style_clip_corner(my_lvgl_cont, true, 0);
    lv_obj_set_scroll_dir(my_lvgl_cont, LV_DIR_VER);
    lv_obj_set_scroll_snap_y(my_lvgl_cont, LV_SCROLL_SNAP_CENTER);
    lv_obj_set_scrollbar_mode(my_lvgl_cont, LV_SCROLLBAR_MODE_OFF);

    uint32_t i;
    for (i = 0; i < BUTTON_NUM; i++)
    {
        lv_obj_t *btn = lv_btn_create(my_lvgl_cont);
        //将创建好的按钮指针指向对应按钮
        switch_button(i, btn);

        lv_obj_set_width(btn, lv_pct(50));
        lv_obj_set_height(btn, lv_pct(20));

        lv_obj_t *label = lv_label_create(btn);
        //将创建好的label指针指向对应label
        switch_lable(btn, label);
        lv_label_set_text_fmt(label, "Button %" LV_PRIu32, i);
    }

    /*Update the buttons position manually for first*/
    lv_event_send(my_lvgl_cont, LV_EVENT_SCROLL, NULL);

    /*Be sure the fist button is in the middle*/
    lv_obj_scroll_to_view(lv_obj_get_child(my_lvgl_cont, 0), LV_ANIM_OFF);

    //主界面按钮文字初始化
    my_lvgl_func_init();
}

void my_lvgl_func_init()
{
    my_lvgl_func_button_init(btn0, label_0, "Picture", my_lvgl_func_0_callback);
    my_lvgl_func_button_init(btn1, label_1, "Keyboard", my_lvgl_func_1_callback);
    my_lvgl_func_button_init(btn2, label_2, "Mouse", my_lvgl_func_2_callback);
}

/**
 * @brief 主界面单个按钮初始化
 *
 * @param btn
 * @param label
 * @param name
 * @param call_back
 */
void my_lvgl_func_button_init(lv_obj_t *btn, lv_obj_t *label, char *name, lv_event_cb_t call_back)
{
    //判断按钮是否为空
    if (is_object_null(btn) == true)
        return;
    //判断按钮文字是否为空
    if (is_object_null(label) == true)
        return;
    //重新修改按钮文字
    lv_label_set_text_fmt(label, name);
    //确保在触摸到按钮上的子级label时，触摸状态可以传递到父级按钮
    lv_obj_add_flag(label, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_CLICKABLE);
    //创建按钮回调函数
    lv_obj_add_event_cb(btn, call_back, LV_EVENT_ALL, NULL);

    my_lv_trans_init();
    my_lv_trans(btn, 0, LV_STATE_PRESSED, lv_palette_main(LV_PALETTE_YELLOW), lv_pct(100), lv_pct(40));
    my_lv_trans(btn, 1, LV_STATE_DEFAULT, lv_palette_main(LV_PALETTE_GREEN), lv_pct(50), lv_pct(20));
}

/**
 * @brief 按钮0回调函数
 *
 * @param event
 */
void my_lvgl_func_0_callback(lv_event_t *event)
{
    lv_event_code_t code = lv_event_get_code(event);
    if (code == LV_EVENT_SHORT_CLICKED)
    {
        //删除主界面
        lv_obj_del(my_lvgl_cont);
        my_img_init(lv_scr_act());
    }
}

/**
 * @brief 按钮1回调函数
 *
 * @param event
 */
void my_lvgl_func_1_callback(lv_event_t *event)
{
    lv_event_code_t code = lv_event_get_code(event);
    if (code == LV_EVENT_SHORT_CLICKED)
    {
        //删除主界面
        lv_obj_del(my_lvgl_cont);
        my_keyboard_init(lv_scr_act());
    }
}

/**
 * @brief 按钮2回调函数
 *
 * @param event
 */
void my_lvgl_func_2_callback(lv_event_t *event)
{
    lv_event_code_t code = lv_event_get_code(event);
    if (code == LV_EVENT_SHORT_CLICKED)
    {
        //删除主界面
        lv_obj_del(my_lvgl_cont);
        my_mouse_init(lv_scr_act());
    }
}

static void scroll_event_cb(lv_event_t *e)
{

    lv_obj_t *cont = lv_event_get_target(e);
    uint32_t child_cnt = lv_obj_get_child_cnt(cont);
    for (uint8_t i = 0; i < child_cnt; i++)
    {
        lv_obj_t *child = lv_obj_get_child(cont, i);
        lv_obj_set_style_translate_x(child, child->coords.y1 * 0.5 - 60, 0);
    }
}

/**
 * @brief 判断对象是否为空
 *
 * @param temp
 * @return true
 * @return false
 */
bool is_object_null(lv_obj_t *temp)
{
    if (temp == NULL)
        return true;
    else
        return false;
}

/**
 * @brief 将行列按钮对应到按钮对象上
 *
 * @param col
 * @param row
 * @param temp
 * @return lv_obj_t*
 */
lv_obj_t *switch_button(uint8_t i, lv_obj_t *temp)
{
    uint8_t btn_num = i;
    switch (btn_num)
    {
    case 0:
        btn0 = temp;
        break;
    case 1:
        btn1 = temp;
        break;
    case 2:
        btn2 = temp;
        break;
    case 3:
        btn3 = temp;
        break;
    case 4:
        btn4 = temp;
        break;
    case 5:
        btn5 = temp;
        break;
    case 6:
        btn6 = temp;
        break;
    case 7:
        btn7 = temp;
        break;
    case 8:
        btn8 = temp;
        break;

    default:
        break;
    }
    return temp;
}

/**
 * @brief 将label对应到按钮对象上
 *
 * @param btn_temp
 * @param label_temp
 * @return lv_obj_t*
 */
lv_obj_t *switch_lable(lv_obj_t *btn_temp, lv_obj_t *label_temp)
{
    if (btn_temp == btn0)
    {
        label_0 = label_temp;
    }
    else if (btn_temp == btn1)
    {
        label_1 = label_temp;
    }
    else if (btn_temp == btn2)
    {
        label_2 = label_temp;
    }
    else if (btn_temp == btn3)
    {
        label_3 = label_temp;
    }
    else if (btn_temp == btn4)
    {
        label_4 = label_temp;
    }
    else if (btn_temp == btn5)
    {
        label_5 = label_temp;
    }
    else if (btn_temp == btn6)
    {
        label_6 = label_temp;
    }
    else if (btn_temp == btn7)
    {
        label_7 = label_temp;
    }
    else if (btn_temp == btn8)
    {
        label_8 = label_temp;
    }

    return label_temp;
}