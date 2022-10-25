# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

set(EXTRA_COMPONENT_DIRS ./component)

#If IOT_SOLUTION_PATH is not defined, use relative path as default value
if(NOT DEFINED ENV{IOT_SOLUTION_PATH})
    get_filename_component(IOT_SOLUTION_PATH "${CMAKE_SOURCE_DIR}/../../../.." ABSOLUTE)
    # set(ENV{IOT_SOLUTION_PATH} ${IOT_SOLUTION_PATH})
    set(ENV{IOT_SOLUTION_PATH} "D:/SoftWare/IDF_TOOLS_PATH/esp/esp-iot-solution")
    message(WARNING "Can't detect IOT_SOLUTION_PATH in your environment, we infer it is $ENV{IOT_SOLUTION_PATH}")
endif()

# This example uses an extra component for common functions such as Wi-Fi and Ethernet connection.
set(EXTRA_COMPONENT_DIRS
                        $ENV{IOT_SOLUTION_PATH}/components/usb/tinyusb
                        $ENV{IOT_SOLUTION_PATH}/examples/common_components/boards
                        $ENV{IOT_SOLUTION_PATH}/components/bus
                        $ENV{IOT_SOLUTION_PATH}/components/button)

include($ENV{IOT_SOLUTION_PATH}/component.cmake)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(uuusb)