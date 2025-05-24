#include "midi_router.h"
#include "usb_midi_host.h"
#include "din_midi.h"
#include "tusb.h"

void midi_router_route(midi_source_t source, const uint8_t* data, size_t length) {
    // Route to USB Device (computer)
    if (routing_table[source][DEST_USB_DEVICE]) {
        if (tud_midi_mounted()) {  // Changed from tud_midi_connected()
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
