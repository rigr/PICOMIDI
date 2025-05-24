#include "usb_descriptors.h"
#include "tusb.h"

// Device descriptor
uint8_t const * tud_descriptor_device_cb(void) {
    static tusb_desc_device_t desc_device = {
        .bLength            = sizeof(tusb_desc_device_t),
        .bDescriptorType    = TUSB_DESC_DEVICE,
        .bcdUSB             = 0x0200,
        .bDeviceClass       = TUSB_CLASS_MISC,
        .bDeviceSubClass    = MISC_SUBCLASS_COMMON,
        .bDeviceProtocol    = MISC_PROTOCOL_IAD,
        .bMaxPacketSize0    = CFG_TUD_ENDPOINT0_SIZE,
        .idVendor           = 0xCafe,
        .idProduct          = 0x4001,
        .bcdDevice          = 0x0100,
        .iManufacturer      = 0x01,
        .iProduct           = 0x02,
        .iSerialNumber      = 0x03,
        .bNumConfigurations = 0x01
    };
    return (uint8_t const *) &desc_device;
}

// Configuration descriptor
uint8_t const * tud_descriptor_configuration_cb(uint8_t index) {
    (void)index; // for multiple configurations
    static uint8_t desc_configuration[64] = { /* Your MIDI configuration descriptor here */ };
    return desc_configuration;
}

// String descriptors
uint16_t const* tud_descriptor_string_cb(uint8_t index, uint16_t langid) {
    (void)langid; // English only
    static uint16_t desc_str[32];
    
    switch(index) {
        case 0: // Language
            desc_str[0] = 0x0409; // English
            break;
        case 1: // Manufacturer
            memcpy(&desc_str[1], "PicoMIDI", 16);
            break;
        case 2: // Product
            memcpy(&desc_str[1], "MIDI Router", 22);
            break;
        case 3: // Serial
            memcpy(&desc_str[1], "123456", 12);
            break;
        default: return NULL;
    }
    
    // First byte is length, second byte is descriptor type
    desc_str[0] = (TUSB_DESC_STRING << 8) | (strlen((char*)&desc_str[1])*2 + 2);
    return desc_str;
}
