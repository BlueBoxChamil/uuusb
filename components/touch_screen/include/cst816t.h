/*
 * @Author: BlueBoxChamil 283040422@qq.com
 * @Date: 2022-09-23 09:31:52
 * @LastEditors: BlueBoxChamil 283040422@qq.com
 * @LastEditTime: 2022-10-12 14:03:32
 * @FilePath: \uuusb\components\touch_screen\include\cst816t.h
 * @Description:
 *
 * Copyright (c) 2022 by BlueBoxChamil 283040422@qq.com, All Rights Reserved.
 */
#ifndef __cst816t__h
#define __cst816t__h

// #if 1
// #define cst816t_debug(format, ...) my_debug("[ cst816t]- ", format, ##__VA_ARGS__);
// #else
// #define cst816t_debug(format, ...) ;
// #endif

#include "stdio.h"
#include "lvgl.h"
#include "esp_log.h"
#include "driver/i2c.h"
#define CST816T_ADDR 0X15

void i2c2_init(void);
void i2c2_uninit(void);

uint8_t cst816t_init(void);
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data);

void iic_cst816t_init();

#define I2C_PORT_NUM_TP (0)
#define GPIO_TP_I2C_SCL 16
#define GPIO_TP_I2C_SDA 15

#define I2C_MASTER_FREQ_HZ 400000   /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE 0 /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE 0 /*!< I2C master doesn't need buffer */
#define I2C_MASTER_TIMEOUT_MS 1000

#endif
