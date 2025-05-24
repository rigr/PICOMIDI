cmake_minimum_required(VERSION 3.12)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
project(picomidi C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

# Add explicit TinyUSB includes
include_directories(
    ${PICO_SDK_PATH}/lib/tinyusb/src
    ${PICO_SDK_PATH}/lib/tinyusb/hw
    ${PICO_SDK_PATH}/lib/tinyusb/src/class/midi
    ${PICO_SDK_PATH}/lib/tinyusb/src/common
)

add_executable(picomidi
    src/main.c
    src/usb_midi_host.c
    src/din_midi.c
    src/midi_router.c
)

target_include_directories(picomidi PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

pico_enable_stdio_usb(picomidi 1)
pico_enable_stdio_uart(picomidi 0)

pico_add_extra_outputs(picomidi)

target_link_libraries(picomidi
    pico_stdlib
    hardware_uart
    hardware_irq
    pico_multicore
    tinyusb_device
    tinyusb_host
)
