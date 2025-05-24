#include "midi_router.h"
#include "usb_midi_host.h"
#include "din_midi.h"
// #include "tusb.h"  already included in usb_midi_host.h

// MIDI routing table
static bool routing_table[NUM_SOURCES][NUM_DESTINATIONS] = {
    // USB Device, DIN1, DIN2, DIN3, USB Host1, USB Host2
    [SOURCE_USB_DEVICE] = {false, true, true, true, true, true},
    [SOURCE_DIN_IN1]    = {true, false, true, true, true, true},
    [SOURCE_DIN_IN2]    = {true, true, false, true, true, true},
    [SOURCE_DIN_IN3]    = {true, true, true, false, true, true},
    [SOURCE_USB_HOST1]  = {true, true, true, true, false, true},
    [SOURCE_USB_HOST2]  = {true, true, true, true, true, false}
};

void midi_router_init() {
    // Initialize any needed resources
}

void midi_router_task() {
    // Periodic tasks if needed
}

void midi_router_route(midi_source_t source, const uint8_t* data, size_t length) {
    // Route to USB Device (computer)
    if (routing_table[source][DEST_USB_DEVICE]) {
        if (tud_midi_connected()) {
            tud_midi_stream_write(0, data, length);
        }
    }
    
    // Route to DIN outputs
    for (int i = 0; i < 3; i++) {
        if (routing_table[source][DEST_DIN_OUT1 + i]) {
            din_midi_send(i, data, length);
        }
    }
    
    // Route to USB Host devices
    for (int i = 0; i < 2; i++) {
        if (routing_table[source][DEST_USB_HOST1 + i] && usb_host_devices[i].connected) {
            tuh_midi_stream_write(usb_host_devices[i].dev_addr, 0, data, length);
        }
    }
}
