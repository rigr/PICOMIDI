#ifndef USB_MIDI_HOST_H
#define USB_MIDI_HOST_H

#include <stdint.h>
#include <stdbool.h>
#include "tusb.h"

#if CFG_TUH_MIDI != 1
#error "TinyUSB Host MIDI must be enabled (CFG_TUH_MIDI=1)"
#endif

#define BOARD_TUH_RHPORT 0

typedef struct {
    bool connected;
    uint8_t dev_addr;
    uint8_t in_ep;
    uint8_t out_ep;
} usb_midi_host_device_t;

extern usb_midi_host_device_t usb_host_devices[2];

// MIDI Host API
bool tuh_midi_mounted(uint8_t dev_addr);
uint32_t tuh_midi_stream_read(uint8_t dev_addr, uint8_t *cable_num, void *buffer, uint16_t bufsize);
bool tuh_midi_stream_write(uint8_t dev_addr, uint8_t cable_num, void const * buffer, uint16_t bufsize);
void tuh_midi_init(void);
void tuh_midi_close(uint8_t dev_addr);

void usb_midi_host_init(void);
void usb_midi_host_task(void);

#endif
