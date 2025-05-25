#ifndef USB_DESCRIPTORS_H
#define USB_DESCRIPTORS_H

#include "tusb.h"

// Interface numbers
enum {
    ITF_NUM_MIDI = 0,
    ITF_NUM_MIDI_STREAMING,
    ITF_NUM_TOTAL
};

// Endpoint numbers
enum {
    EPNUM_MIDI_OUT = 0x01,
    EPNUM_MIDI_IN  = 0x81
};

uint8_t const * tud_descriptor_device_cb(void);
uint8_t const * tud_descriptor_configuration_cb(uint8_t index);
uint16_t const* tud_descriptor_string_cb(uint8_t index, uint16_t langid);

#endif
