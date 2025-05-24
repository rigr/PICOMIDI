cmake_minimum_required(VERSION 3.12)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
project(picomidi C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize SDK before any configuration
pico_sdk_init()

# Explicit USB configuration
set(PICO_STDIO_USB_HOST_DEVICE_ENUMERATION_FIX 1)
set(PICO_TINYUSB_HOST_DEVICE_COMBINED 1)

add_executable(picomidi
    src/main.c
    src/usb_midi_host.c
    src/din_midi.c
    src/midi_router.c
)

# Include paths
target_include_directories(picomidi PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${PICO_SDK_PATH}/lib/tinyusb/src
)

# USB configuration
pico_enable_stdio_usb(picomidi 0)  # Disable stdio USB since we're doing custom USB
pico_enable_stdio_uart(picomidi 0)

# Link libraries
target_link_libraries(picomidi
    pico_stdlib
    hardware_uart
    hardware_irq
    pico_multicore
    tinyusb_device
    tinyusb_host
    pico_stdlib
)

pico_add_extra_outputs(picomidi)
