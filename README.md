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

### Connections

- **DIN MIDI Ports**:
  - UART0: DIN1 (TX=GP0, RX=GP1)
  - UART1: DIN2 (TX=GP4, RX=GP5)
  - PIO or Software UART: DIN3 (TX=GP8, RX=GP9)
  
- **USB Host Ports**:
  - Connect USB host controllers to GPIO pins configured for USB host mode

- **Power**:
  - 5V power supply connected to VSYS

## Building the Firmware

1. Set up the Pico SDK development environment
2. Clone this repository with submodules:

   git clone --recursive https://github.com/yourusername/picomidi.git

4. Create a build directory:

   mkdir build
   cd build

6. Configure with CMake:

   cmake ..

8. Build:

   make

The resulting `picomidi.uf2` file will be in the build directory.

## Flashing the Firmware

1. Hold the BOOTSEL button on the Pico while connecting it to your computer
2. Drag and drop the `picomidi.uf2` file to the RPI-RP2 drive
3. The Pico will reboot and start running the firmware

## Usage

1. Connect MIDI devices to the DIN ports
2. Connect USB MIDI devices to the host ports
3. Connect the Pico to a computer via USB for MIDI device mode
4. All MIDI messages will be automatically routed between all connected ports

## License

MIT License - see LICENSE file for details
