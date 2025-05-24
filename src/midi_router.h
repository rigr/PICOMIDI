#ifndef MIDI_ROUTER_H
#define MIDI_ROUTER_H

#include <stdint.h>
#include <stddef.h>

// MIDI source types
typedef enum {
    SOURCE_USB_DEVICE,  // From computer USB
    SOURCE_DIN_IN1,     // DIN MIDI IN 1
    SOURCE_DIN_IN2,     // DIN MIDI IN 2
    SOURCE_DIN_IN3,     // DIN MIDI IN 3
    SOURCE_USB_HOST1,   // USB Host port 1
    SOURCE_USB_HOST2,   // USB Host port 2
    NUM_SOURCES
} midi_source_t;

// MIDI destination types
typedef enum {
    DEST_USB_DEVICE,    // To computer USB
    DEST_DIN_OUT1,      // DIN MIDI OUT 1
    DEST_DIN_OUT2,      // DIN MIDI OUT 2
    DEST_DIN_OUT3,      // DIN MIDI OUT 3
    DEST_USB_HOST1,     // USB Host port 1
    DEST_USB_HOST2,     // USB Host port 2
    NUM_DESTINATIONS
} midi_dest_t;

// Initialize the MIDI router
void midi_router_init(void);

// Task that needs to be called periodically
void midi_router_task(void);

// Route MIDI data from a source
void midi_router_route(midi_source_t source, const uint8_t* data, size_t length);

#endif // MIDI_ROUTER_H
