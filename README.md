# PICOMIDI - Raspberry Pi Pico MIDI Router

A versatile MIDI router with USB host and device capabilities built on Raspberry Pi Pico.

## Features

- 3x MIDI DIN IN ports
- 3x MIDI DIN OUT ports
- 2x USB MIDI Host ports (for connecting MIDI controllers/sound modules)
- USB MIDI Device mode (appears as "PICOMIDI" when connected to a computer)
- Transparent MIDI routing with no message filtering
- Supports all MIDI message types including SysEx

## Hardware Setup

### USB Host Connections

You'll need to add USB host functionality using one of these methods:

#### Option 1: Using USB Host Shield Breakout
1. Connect to GPIO pins:
   - VBUS: Connect to Pico's VBUS (pin 40) or 5V supply
   - D+: Connect to GPIO16 (pin 21)
   - D-: Connect to GPIO17 (pin 22)
   - GND: Connect to any GND pin

#### Option 2: Using MAX3421E Chip
1. Recommended wiring:
   - VBUS: 5V supply
   - D+: GPIO16 (pin 21)
   - D-: GPIO17 (pin 22)
   - INT: GPIO18 (pin 24)
   - CS: GPIO19 (pin 25)
   - SCK: GPIO18 (pin 24)
   - MOSI: GPIO19 (pin 25)
   - MISO: GPIO16 (pin 21)
   - GND: Connect to Pico's GND

### DIN MIDI Connections

| MIDI Port | UART | TX Pin | RX Pin |
|-----------|------|--------|--------|
| DIN1      | UART0| GPIO0  | GPIO1  |
| DIN2      | UART1| GPIO4  | GPIO5  |
| DIN3      | PIO  | GPIO8  | GPIO9  |

### Power Supply
- Connect 5V power to VSYS (pin 39)
- Ensure proper grounding between all connected devices

## Building the Firmware

1. Set up the Pico SDK development environment
2. Clone this repository with submodules:
  
   git clone --recursive https://github.com/yourusername/picomidi.git

Create a build directory:

  mkdir build
  cd build
  
Configure with CMake:

  cmake ..

Build:

  make -j4

## Flashing the Firmware

Hold the BOOTSEL button on the Pico while connecting it to your computer

Drag and drop the picomidi.uf2 file to the RPI-RP2 drive

The Pico will reboot and start running the firmware

## Usage

Connect MIDI devices to the DIN ports

Connect USB MIDI devices to the host ports

Connect the Pico to a computer via USB for MIDI device mode

All MIDI messages will be automatically routed between all connected ports

## Configuration

Edit include/config.h to:

Change USB device name

Modify MIDI routing behavior

Adjust buffer sizes

License
MIT License - see LICENSE file for details


Key hardware notes included:
1. Clear USB host connection options with specific GPIO pins
2. DIN MIDI port mapping table
3. Power supply requirements
4. Visual pin references for easy wiring
5. Multiple implementation options for USB host

