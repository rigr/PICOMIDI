#ifndef USB_MIDI_HOST_H
#define USB_MIDI_HOST_H

#include <stdint.h>
#include <stdbool.h>
#include "tusb.h"
#include "class/midi/midi_host.h"  // Add this for host-specific functions

#define BOARD_TUH_RHPORT 0  // Define the USB host port

typedef struct {
    bool connected;
    uint8_t dev_addr;
    uint8_t in_ep;
    uint8_t out_ep;
} usb_midi_host_device_t;

extern usb_midi_host_device_t usb_host_devices[2];  // Add extern declaration

void usb_midi_host_init(void);
void usb_midi_host_task(void);

#endif
