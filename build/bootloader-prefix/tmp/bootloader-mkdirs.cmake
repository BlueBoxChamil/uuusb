# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/SoftWare/IDF_TOOLS_PATH/esp/esp-idf/components/bootloader/subproject"
  "D:/Docement/espidf-project/uuusb/build/bootloader"
  "D:/Docement/espidf-project/uuusb/build/bootloader-prefix"
  "D:/Docement/espidf-project/uuusb/build/bootloader-prefix/tmp"
  "D:/Docement/espidf-project/uuusb/build/bootloader-prefix/src/bootloader-stamp"
  "D:/Docement/espidf-project/uuusb/build/bootloader-prefix/src"
  "D:/Docement/espidf-project/uuusb/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/Docement/espidf-project/uuusb/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
