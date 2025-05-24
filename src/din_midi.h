#ifndef DIN_MIDI_H
#define DIN_MIDI_H

#include <stdint.h>
#include <stdbool.h>
#include "hardware/uart.h"

// Number of DIN MIDI ports (3 IN, 3 OUT)
#define NUM_DIN_PORTS 3

// Initialize all DIN MIDI ports
void din_midi_init(void);

// Background task for DIN MIDI processing
void din_midi_task(void);

// Send MIDI data to a specific DIN port
void din_midi_send(uint8_t port, const uint8_t* data, size_t length);

// IRQ handlers (implemented in .c file)
static void din_midi0_irq_handler(void);
static void din_midi1_irq_handler(void);
static void din_midi2_irq_handler(void);

#endif // DIN_MIDI_H
