#ifndef USB_MIDI_HOST_H
#define USB_MIDI_HOST_H

#include <stdint.h>
#include <stdbool.h>
#include "tusb.h"
#include "pico/stdlib.h"


// Maximum number of USB host devices we support
#define MAX_USB_HOST_DEVICES 2

typedef struct {
    bool connected;
    uint8_t dev_addr;
    uint8_t in_ep;
    uint8_t out_ep;
} usb_midi_host_device_t;

// Initialize USB MIDI host functionality
void usb_midi_host_init(void);

// Task that needs to be called periodically
void usb_midi_host_task(void);

// Callbacks for TinyUSB host
void tuh_midi_mount_cb(uint8_t dev_addr, uint8_t in_ep, uint8_t out_ep, uint8_t num_cables_rx, uint16_t num_cables_tx);
void tuh_midi_umount_cb(uint8_t dev_addr);
void tuh_midi_rx_cb(uint8_t dev_addr, uint32_t num_packets);

#endif // USB_MIDI_HOST_H
