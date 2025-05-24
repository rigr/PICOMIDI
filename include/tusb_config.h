#ifndef _TUSB_CONFIG_H_
#define _TUSB_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------------------------------------------
// COMMON CONFIGURATION
//--------------------------------------------------------------------
#define CFG_TUSB_RHPORT0_MODE   (OPT_MODE_HOST | OPT_MODE_DEVICE)
#define CFG_TUSB_OS             OPT_OS_PICO
#define CFG_TUSB_MCU            OPT_MCU_RP2040

//--------------------------------------------------------------------
// DEVICE CONFIGURATION
//--------------------------------------------------------------------
#define CFG_TUD_ENABLED         1
#define CFG_TUD_MIDI            1
#define CFG_TUD_MIDI_RX_BUFSIZE 64
#define CFG_TUD_MIDI_TX_BUFSIZE 64

//--------------------------------------------------------------------
// HOST CONFIGURATION
//--------------------------------------------------------------------
#define CFG_TUH_ENABLED         1
#define CFG_TUH_MIDI            1  // This is the critical missing line
#define CFG_TUH_DEVICE_MAX      2

#ifdef __cplusplus
}
#endif

#endif
