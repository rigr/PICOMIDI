#include "tusb.h"
#include "usb_midi_host.h"

// Implement missing host MIDI functions
uint32_t tuh_midi_stream_read(uint8_t dev_addr, uint8_t *cable_num, void *buffer, uint16_t bufsize) {
    return tuh_midi_stream_read_ext(dev_addr, 0, cable_num, buffer, bufsize);
}

bool tuh_midi_stream_write(uint8_t dev_addr, uint8_t cable_num, void const * buffer, uint16_t bufsize) {
    return tuh_midi_stream_write_ext(dev_addr, 0, cable_num, buffer, bufsize);
}
