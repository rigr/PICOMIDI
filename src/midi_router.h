#ifndef MIDI_ROUTER_H
#define MIDI_ROUTER_H

#include <stdint.h>
#include <stddef.h>
#include "usb_midi_host.h"

typedef enum {
    SOURCE_USB_DEVICE,
    SOURCE_DIN_IN1,
    SOURCE_DIN_IN2,
    SOURCE_DIN_IN3,
    SOURCE_USB_HOST1,
    SOURCE_USB_HOST2,
    NUM_SOURCES
} midi_source_t;

typedef enum {
    DEST_USB_DEVICE,
    DEST_DIN_OUT1,
    DEST_DIN_OUT2,
    DEST_DIN_OUT3,
    DEST_USB_HOST1,
    DEST_USB_HOST2,
    NUM_DESTINATIONS
} midi_dest_t;

// Add routing table declaration
extern bool routing_table[NUM_SOURCES][NUM_DESTINATIONS];

void midi_router_init(void);
void midi_router_task(void);
void midi_router_route(midi_source_t source, const uint8_t* data, size_t length);

#endif
