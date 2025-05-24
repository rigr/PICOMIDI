#ifndef _TUSB_CONFIG_H_
#define _TUSB_CONFIG_H_

#define CFG_TUSB_RHPORT0_MODE   (OPT_MODE_HOST | OPT_MODE_DEVICE)

#define CFG_TUSB_OS             OPT_OS_PICO
#define CFG_TUSB_MCU            OPT_MCU_RP2040

#define CFG_TUD_ENABLED         1
#define CFG_TUH_ENABLED         1

// Device configuration
#define CFG_TUD_MIDI           1
#define CFG_TUD_MIDI_RX_BUFSIZE 64
#define CFG_TUD_MIDI_TX_BUFSIZE 64

// Host configuration
#define CFG_TUH_MIDI           1
#define CFG_TUH_DEVICE_MAX     2

#endif
