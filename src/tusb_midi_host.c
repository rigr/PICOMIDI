#include "tusb.h"
#include "usb_midi_host.h"

// Implement all required MIDI host functions
bool tuh_midi_mounted(uint8_t dev_addr) {
    for (int i = 0; i < 2; i++) {
        if (usb_host_devices[i].dev_addr == dev_addr) {
            return usb_host_devices[i].connected;
        }
    }
    return false;
}

uint32_t tuh_midi_stream_read(uint8_t dev_addr, uint8_t *cable_num, void *buffer, uint16_t bufsize) {
    if (!tuh_midi_mounted(dev_addr)) return 0;
    
    // Simple implementation - reads from endpoint
    uint8_t ep_addr = usb_host_devices[dev_addr-1].in_ep;
    TU_ASSERT(ep_addr, 0);
    
    uint32_t bytes_read = 0;
    TU_VERIFY(tuh_edpt_xfer(dev_addr, ep_addr, buffer, bufsize), 0);
    
    // Default cable number if not specified
    if (cable_num) *cable_num = 0;
    
    return bytes_read;
}

bool tuh_midi_stream_write(uint8_t dev_addr, uint8_t cable_num, void const * buffer, uint16_t bufsize) {
    if (!tuh_midi_mounted(dev_addr)) return false;
    
    // Simple implementation - writes to endpoint
    uint8_t ep_addr = usb_host_devices[dev_addr-1].out_ep;
    TU_ASSERT(ep_addr, false);
    
    // Add cable number to message if needed
    uint8_t msg[bufsize+1];
    msg[0] = cable_num;
    memcpy(&msg[1], buffer, bufsize);
    
    return tuh_edpt_xfer(dev_addr, ep_addr, msg, bufsize+1) == XFER_RESULT_SUCCESS;
}
