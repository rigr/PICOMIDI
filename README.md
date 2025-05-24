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
