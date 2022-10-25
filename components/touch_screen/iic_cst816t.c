/*
 * @Author: BlueBoxChamil 283040422@qq.com
 * @Date: 2022-09-23 09:31:52
 * @LastEditors: BlueBoxChamil 283040422@qq.com
 * @LastEditTime: 2022-10-08 15:49:23
 * @FilePath: \20221008\components\touch_screen\iic_cst816t.c
 * @Description:
 *
 * Copyright (c) 2022 by BlueBoxChamil 283040422@qq.com, All Rights Reserved.
 */
#include "cst816t.h"

static esp_err_t i2c2_master_init(void)
{
    int i2c_master_port = I2C_PORT_NUM_TP;

    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = GPIO_TP_I2C_SDA,
        .scl_io_num = GPIO_TP_I2C_SCL,
        .sda_pullup_en = GPIO_PULLUP_DISABLE,
        .scl_pullup_en = GPIO_PULLUP_DISABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };

    i2c_param_config(i2c_master_port, &conf);

    return i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}

void bsp_i2c_test_task(void *pvParameter)
{

    uint8_t dummy;
    uint8_t data = 0XA7;
    uint8_t buf[] = {0xA7, 0X00};
    uint8_t i = 0;

    // i2c_read(twiAddress, 0x15, &dummy, 1);
    // vTaskDelay(5);
    // i2c_read(twiAddress, 0xa7, &dummy, 1);
    // vTaskDelay(5);
    // for(int i=0;i<0xff;i++)
    i = 0x15;
    while (1)
    {
        // for(i=0;i<0xff;i++])
        {
            if (i2c_master_write_read_device(I2C_PORT_NUM_TP, i, &data, 1, &dummy, 1, I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS) == ESP_OK)
            {
                printf("成功 地址:0x%02x 数据:0x%02x \r\n", i, dummy);
            }
            else
            {
                printf("失败 地址:0x%02x 数据:0x%02x \r\n", i, dummy);
            }
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }

    vTaskDelete(NULL);
}

void i2c2_init(void)
{
    if (i2c2_master_init() == ESP_OK)
    {
        printf("i2c2初始化成功\r\n");
        // xTaskCreate(bsp_i2c_test_task,"bsp_i2c_test_task",1024*5,NULL,12,NULL);
    }
    else
    {
        printf("i2c2初始化失败\r\n");
    }
}
void i2c2_uninit(void)
{
    ESP_ERROR_CHECK(i2c_driver_delete(I2C_PORT_NUM_TP));
    printf("I2C de-initialized successfully");
}

uint8_t cst816t_read_len(uint16_t reg_addr, uint8_t *data, uint8_t len)
{
    uint8_t res = 0;
    res = i2c_master_write_read_device(I2C_PORT_NUM_TP, CST816T_ADDR, &reg_addr, 1, data, len, 1000 / portTICK_PERIOD_MS);

    return res;
}

uint8_t cst816t_register_write_byte(uint8_t reg_addr, uint8_t data)
{
    int ret;
    uint8_t write_buf[2] = {reg_addr, data};

    ret = i2c_master_write_to_device(I2C_PORT_NUM_TP, CST816T_ADDR, write_buf, sizeof(write_buf), 1000 / portTICK_PERIOD_MS);

    return ret;
}

uint8_t cst816t_chipId(void)
{

    return 0;
}
static esp_err_t cst816t_get_touch_points_num(uint8_t *touch_points_num)
{
    uint8_t res = 0;
    res = cst816t_read_len(0x02, touch_points_num, 1);
    return res;
}

esp_err_t cst816t_read_pos(uint8_t *touch_points_num, uint16_t *x, uint16_t *y)
{
    uint8_t data[4];

    cst816t_get_touch_points_num(touch_points_num);
    if (0 == *touch_points_num)
    {
        *x = 0;
        *y = 0;
        return 1;
    }
    else
    {
        cst816t_read_len(0x03, data, 4);

        *x = ((data[0] & 0x0f) << 8) | data[1];
        *y = ((data[2] & 0x0f) << 8) | data[3];
    }

    return ESP_OK;
}

void cst816t_test_task(void *pvParameter)
{

    uint8_t res = 0;

    uint8_t touch_points_num = 0;
    uint16_t x = 0;
    uint16_t y = 0;
    while (1)
    {

        res = cst816t_read_pos(&touch_points_num, &x, &y);
        if (res == ESP_OK)
        {
            printf("成功 点数:%d X:%d Y:%d \r\n", touch_points_num, x, y);
        }
        else
        {
            // printf("失败 点数:%d X:%d Y:%d \r\n", touch_points_num, x, y);
        }

        vTaskDelay(pdMS_TO_TICKS(100));
    }

    vTaskDelete(NULL);
}

uint8_t cst816t_init(void)
{
    uint8_t buf[10];
    cst816t_read_len(0x15, buf, 1);
    vTaskDelay(pdMS_TO_TICKS(10));
    cst816t_read_len(0xa7, buf, 1);
    vTaskDelay(pdMS_TO_TICKS(10));
    // xTaskCreate(cst816t_test_task, "cst816t_test_task", 1024 * 5, NULL, 10, NULL);

    return 0;
}

/*Read the touchpad*/
/**
 * @brief 触摸屏回调函数
 *
 * @param indev_driver
 * @param data
 */
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
    static uint8_t tp_num = 0;
    static uint16_t x = 0, y = 0;

    cst816t_read_pos(&tp_num, &x, &y);

    if (0 == tp_num)
    {
        data->state = LV_INDEV_STATE_REL;
    }
    else
    {
        /* Swap xy order and invert y direction */
        data->point.x = x;
        data->point.y = y; // LV_VER_RES_MAX - x - 1;
        data->state = LV_INDEV_STATE_PR;

        // printf("Data :%d %d\r\n", x, y);
    }
    // system_data.mouse = *data;
}

void iic_cst816t_init()
{
    i2c2_init();
    cst816t_init();
}