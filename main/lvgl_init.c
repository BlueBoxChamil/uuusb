/*
 * @Author: BlueBoxChamil 283040422@qq.com
 * @Date: 2022-10-11 14:06:39
 * @LastEditors: BlueBoxChamil 283040422@qq.com
 * @LastEditTime: 2022-10-13 16:17:26
 * @FilePath: \uuusb\main\lvgl_init.c
 * @Description:
 *
 * Copyright (c) 2022 by BlueBoxChamil 283040422@qq.com, All Rights Reserved.
 */
#include "lvgl_init.h"
#include "my_lvgl.h"
#include "cst816t.h"
#include "tusb_hid.h"
// #include "../components/lv_examples/lv_examples/lv_demo.h"
/******************************************************************
 *  STATIC PROTOTYPES
 ******************************************************************/

void lv_tick_task(void *arg)
{
    lv_tick_inc(LV_TICK_PERIOD_MS);
}
/* Creates a semaphore to handle concurrent call to lvgl stuff
 * If you wish to call *any* lvgl function from other threads/tasks
 * you should lock on the very same semaphore! */
/*********************** GUI_SHOW_CODE_START***********************/
lv_obj_t *label_1;
lv_obj_t *label_2;

void UI_Init()
{
    // lv_obj_t *scr = lv_scr_act(); //创建scr
    // lv_obj_set_pos(scr, 0, 0);
    // lv_scr_load(scr);

    // label_1 = lv_label_create(scr);                                 //创建label
    // lv_label_set_recolor(label_1, 1);                               //颜色可变换
    // lv_label_set_long_mode(label_1, LV_LABEL_LONG_SCROLL_CIRCULAR); //设置滚动模式
    // lv_obj_set_pos(label_1, 20, 50);                                //设置位置
    // lv_obj_set_size(label_1, 160, 30);                              //设定大小
    // lv_label_set_text(label_1, "This is a GUI thread yes");         //设定文本内容

    // label_2 = lv_label_create(scr);                                 //创建labe2
    // lv_label_set_recolor(label_2, 1);                               //颜色可变换
    // lv_label_set_long_mode(label_2, LV_LABEL_LONG_SCROLL_CIRCULAR); //设置滚动模式
    // lv_obj_set_pos(label_2, 100, 40);                               //设置位置
    // lv_obj_set_size(label_2, 160, 40);                              //设定大小
    // lv_label_set_text(label_2, "#ff0000 red#");                     //设定文本内容

    // test_kkkeyboard();
    // test_uuusb();
    main_lvgl_demo(lv_scr_act());
    // my_img_init_1(lv_scr_act());

    // test_mmmouse();
}
/*********************** GUI_SHOW_CODE_END***********************/

void guiTask(void *p)
{
    iic_cst816t_init();
    // sd_fatfs_init();

    lv_init();

    // lv_fs_if_fatfs_init();
    // check_dir();
    /* Initialize SPI or I2C bus used by the drivers */
    lvgl_driver_init();

    // lv_color_t *buf1 = heap_caps_malloc(DISP_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_DMA);
    lv_color_t *buf1 = heap_caps_malloc(DISP_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_INTERNAL);
    // memset(buf1,0x00ff,DISP_BUF_SIZE * sizeof(lv_color_t));
    assert(buf1 != NULL);

    /* Use double buffered when not working with monochrome displays */
#ifndef CONFIG_LV_TFT_DISPLAY_MONOCHROME
    lv_color_t *buf2 = heap_caps_malloc(DISP_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_INTERNAL);
    // memset(buf2,0x00ff,DISP_BUF_SIZE * sizeof(lv_color_t));
    assert(buf2 != NULL);
#else
    static lv_color_t *buf2 = NULL;
#endif

    static lv_disp_draw_buf_t disp_buf;

    uint32_t size_in_px = DISP_BUF_SIZE;

#if defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_IL3820 || defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_JD79653A || defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_UC8151D || defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_SSD1306

    /* Actual size in pixels, not bytes. */
    size_in_px *= 8;
#endif

    /* Initialize the working buffer depending on the selected display.
     * NOTE: buf2 == NULL when using monochrome displays. */
    lv_disp_draw_buf_init(&disp_buf, buf1, buf2, size_in_px);

    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = LV_HOR_RES_MAX;
    disp_drv.ver_res = LV_VER_RES_MAX;
    disp_drv.flush_cb = disp_driver_flush;
    disp_drv.draw_buf = &disp_buf;
    lv_disp_drv_register(&disp_drv);

    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.read_cb = my_touchpad_read;
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    lv_indev_drv_register(&indev_drv);
    /* Register an input device when enabled on the menuconfig */
    // #if CONFIG_LV_TOUCH_CONTROLLER != TOUCH_CONTROLLER_NONE
    //     lv_indev_drv_t indev_drv;
    //     lv_indev_drv_init(&indev_drv);
    //     indev_drv.read_cb = touch_driver_read;
    //     indev_drv.type = LV_INDEV_TYPE_POINTER;
    //     lv_indev_drv_register(&indev_drv);
    // #endif

    /* Create and start a periodic timer interrupt to call lv_tick_inc */
    const esp_timer_create_args_t periodic_timer_args = {
        .callback = &lv_tick_task,
        .name = "periodic_gui"};
    esp_timer_handle_t periodic_timer;
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, LV_TICK_PERIOD_MS * 1000));

    UI_Init(); //基础UI渲染函数

    while (1)
    {
        /* Delay 1 tick (assumes FreeRTOS tick is 10ms */
        vTaskDelay(pdMS_TO_TICKS(10));
        lv_task_handler();
    }
    /* A task should NEVER return */
    free(buf1);
#ifndef CONFIG_LV_TFT_DISPLAY_MONOCHROME
    free(buf2);
#endif
    vTaskDelete(NULL);
}

/**
 *
 * 因在组件库无法找到头文件，在主函数中定义的该函数
 *
 */

/**
 * @brief lvgl键盘回调函数
 *
 * @param e
 */
void my_keyboard_event_cb_1(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    lv_keyboard_t *keyboard = (lv_keyboard_t *)obj;

    // if (code == LV_EVENT_VALUE_CHANGED)
    if (code == LV_EVENT_SHORT_CLICKED)
    {
        uint32_t id = lv_btnmatrix_get_selected_btn(obj);
        const char *txt = lv_btnmatrix_get_btn_text(obj, id); // 获取当前按键的文本
        printf("kb = %x\r\n", *txt);

        uint8_t keycodeee[2];
        memset(keycodeee, 0, sizeof(keycodeee));
        // 目前仅有小写字母有效
        if ((*txt >= 0x61) && (*txt <= 0x7A))
        {
            keycodeee[0] = ASCII_TO_USB_HID(*txt);
        }
        else if (*txt == 0xef)
        {
            keycodeee[0] = HID_KEY_BACKSPACE;
        }
        else
        {
            keycodeee[0] = HID_KEY_A;
        }

        tinyusb_hid_keyboard_report(keycodeee);
    }
}

/**
 * @brief 鼠标移动回调函数
 *
 * @param event
 */
void my_mouse_move_event_cb(lv_event_t *event)
{
    lv_obj_t *obj = lv_event_get_target(event);
    lv_indev_t *indev = lv_indev_get_act(); //获取活动界面输入设备
    lv_point_t vect;
    lv_indev_get_vect(indev, &vect); //获取vect point

    // printf("Data :%d %d\r\n", vect.x, vect.y);
    tinyusb_hid_mouse_move_report(vect.x * MOUSE_TIME, vect.y * MOUSE_TIME, 0, 0);
}

/**
 * @brief 鼠标点击回调函数
 *
 * @param event
 */
void my_mouse_click_event_cb(lv_event_t *event)
{
    tinyusb_hid_mouse_button_report(MOUSE_BUTTON_LEFT);
}
