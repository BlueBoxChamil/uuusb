<!--
 * @Author: BlueBoxChamil 283040422@qq.com
 * @Date: 2022-10-25 09:49:00
 * @LastEditors: BlueBoxChamil 283040422@qq.com
 * @LastEditTime: 2022-10-25 10:11:14
 * @FilePath: \undefinedd:\Docement\espidf-project\uuusb\README.md
 * @Description: 
 * 
 * Copyright (c) 2022 by BlueBoxChamil 283040422@qq.com, All Rights Reserved. 
-->
# uuusb

### 描述
 这是基于esp-idf拓展包创建的一个usb-hid工程，在添加以往lvgl的基础上，使其可以当作一个键盘或者鼠标，用以控制电脑等usb设备，目前只测试过电脑

 ### 功能
1.  图片显示
    1.  使用tabview创建了一个可以左右滑动的相册集，模仿手机左右翻看照片的功能。
    2. 问题：sd卡读取bin图片还存在问题，就暂时取消了挂载fatfs的功能
2. 键盘
   1. 可以打出小写26个字母
   2. 问题：因官方提供的hid库不全，无法将所有的ascii的字符转成usb的键盘符，因此只做了小写字母的转换
3. 鼠标
   1. 可以用屏幕代替鼠标
   2. 问题：lvgl使用的短击和长按在判断上有些问题，因此需要两次点击才能实现实体鼠标单击的功能


