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
    
    // Find the device
    usb_midi_host_device_t* dev = NULL;
    for (int i = 0; i < 2; i++) {
        if (usb_host_devices[i].dev_addr == dev_addr) {
            dev = &usb_host_devices[i];
            break;
        }
    }
    if (!dev || !dev->in_ep) return 0;
    
    // Setup transfer
    tuh_xfer_t xfer = {
        .daddr = dev_addr,
        .ep_addr = dev->in_ep,
        .buffer = buffer,
        .buflen = bufsize,
        .complete_cb = NULL,
        .user_data = 0
    };
    
    if (!tuh_edpt_xfer(&xfer)) return 0;
    
    // Default cable number if not specified
    if (cable_num) *cable_num = 0;
    
    return xfer.actual_len;
}

bool tuh_midi_stream_write(uint8_t dev_addr, uint8_t cable_num, void const * buffer, uint16_t bufsize) {
    if (!tuh_midi_mounted(dev_addr)) return false;
    
    // Find the device
    usb_midi_host_device_t* dev = NULL;
    for (int i = 0; i < 2; i++) {
        if (usb_host_devices[i].dev_addr == dev_addr) {
            dev = &usb_host_devices[i];
            break;
        }
    }
    if (!dev || !dev->out_ep) return false;
    
    // Prepare message with cable number
    uint8_t msg[bufsize+1];
    msg[0] = cable_num;
    memcpy(&msg[1], buffer, bufsize);
    
    // Setup transfer
    tuh_xfer_t xfer = {
        .daddr = dev_addr,
        .ep_addr = dev->out_ep,
        .buffer = msg,
        .buflen = bufsize+1,
        .complete_cb = NULL,
        .user_data = 0
    };
    
    return tuh_edpt_xfer(&xfer);
}
