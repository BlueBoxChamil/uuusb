/*
 * @Author: BlueBoxChamil 283040422@qq.com
 * @Date: 2022-09-27 13:32:27
 * @LastEditors: BlueBoxChamil 283040422@qq.com
 * @LastEditTime: 2022-10-12 10:52:53
 * @FilePath: \uuusb\components\my_lvgl\include\my_asc2usbhid.h
 * @Description:
 *
 * Copyright (c) 2022 by BlueBoxChamil 283040422@qq.com, All Rights Reserved.
 */
#ifndef __my_ascii2usbhid__
#define __my_ascii2usbhid__

/**
 * 目前仅有小写字母有效
 *
 */

#define ASCII_TO_USB_HID(x) (x - 0X5d)

#endif