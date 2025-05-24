#include "usb_midi_host.h"
#include "midi_router.h"

usb_midi_host_device_t usb_host_devices[2];

void usb_midi_host_init(void) {
    for (int i = 0; i < 2; i++) {
        usb_host_devices[i].connected = false;
        usb_host_devices[i].dev_addr = 0;
    }
    tuh_init(BOARD_TUH_RHPORT);
}

void usb_midi_host_task(void) {
    tuh_task();
}

void tuh_midi_mount_cb(uint8_t dev_addr, uint8_t in_ep, uint8_t out_ep, uint8_t num_cables_rx, uint16_t num_cables_tx) {
    for (int i = 0; i < 2; i++) {
        if (!usb_host_devices[i].connected) {
            usb_host_devices[i].connected = true;
            usb_host_devices[i].dev_addr = dev_addr;
            usb_host_devices[i].in_ep = in_ep;
            usb_host_devices[i].out_ep = out_ep;
            break;
        }
    }
}

void tuh_midi_umount_cb(uint8_t dev_addr) {
    for (int i = 0; i < 2; i++) {
        if (usb_host_devices[i].dev_addr == dev_addr) {
            usb_host_devices[i].connected = false;
            break;
        }
    }
}

void tuh_midi_rx_cb(uint8_t dev_addr, uint32_t num_packets) {
    uint8_t cable_num;
    uint8_t buffer[48];
    uint32_t bytes_read = tuh_midi_stream_read(dev_addr, &cable_num, buffer, sizeof(buffer));
    
    if (bytes_read > 0) {
        midi_router_route(SOURCE_USB_HOST1, buffer, bytes_read);
    }
}
