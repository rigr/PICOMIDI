cmake_minimum_required(VERSION 3.12)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
project(picomidi C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Force enable MIDI host
add_definitions(
    -DCFG_TUH_MIDI=1
    -DCFG_TUH_DEVICE_MAX=2
)

pico_sdk_init()

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src  # Add src to include path
    ${PICO_SDK_PATH}/lib/tinyusb/src
)

add_executable(picomidi
    src/main.c
    src/usb_midi_host.c
    src/din_midi.c
    src/midi_router.c
    src/usb_descriptors.c
    src/tusb_midi_host.c
)

pico_enable_stdio_usb(picomidi 0)
pico_enable_stdio_uart(picomidi 0)

target_link_libraries(picomidi
    pico_stdlib
    hardware_uart
    hardware_irq
    pico_multicore
    tinyusb_device
    tinyusb_host
)

pico_add_extra_outputs(picomidi)
