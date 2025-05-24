#ifndef CONFIG_H
#define CONFIG_H

// Ensure TinyUSB is configured
#define CFG_TUSB_MCU OPT_MCU_RP2040
#define CFG_TUSB_OS  OPT_OS_PICO

// Hardware configuration
#define DIN1_UART_INST   uart0
#define DIN1_TX_PIN      0
#define DIN1_RX_PIN      1

#define DIN2_UART_INST   uart1
#define DIN2_TX_PIN      4
#define DIN2_RX_PIN      5

#define DIN3_UART_INST   uart0  // Note: May need PIO implementation
#define DIN3_TX_PIN      8
#define DIN3_RX_PIN      9

// USB Configuration
#define USB_MIDI_DEVICE_NAME   "PICOMIDI"
#define USB_MIDI_VENDOR_NAME   "PicoMIDI"
#define USB_MIDI_PRODUCT_NAME  "MIDI Router"

// MIDI settings
#define MIDI_BAUD_RATE   31250
#define MIDI_BUFFER_SIZE 128

#endif // CONFIG_H
