#include "usb_descriptors.h"

// Device Descriptor
tusb_desc_device_t const desc_device = {
    .bLength            = sizeof(tusb_desc_device_t),
    .bDescriptorType    = TUSB_DESC_DEVICE,
    .bcdUSB             = 0x0200,
    .bDeviceClass       = TUSB_CLASS_MISC,
    .bDeviceSubClass    = MISC_SUBCLASS_COMMON,
    .bDeviceProtocol    = MISC_PROTOCOL_IAD,
    .bMaxPacketSize0    = CFG_TUD_ENDPOINT0_SIZE,
    .idVendor           = CFG_TUD_VID,
    .idProduct          = CFG_TUD_PID,
    .bcdDevice          = 0x0100,
    .iManufacturer      = 0x01,
    .iProduct           = 0x02,
    .iSerialNumber      = 0x03,
    .bNumConfigurations = 0x01
};

// Configuration Descriptor
uint8_t const desc_configuration[] = {
    // Config number, interface count, string index, total length, attribute, power in mA
    TUD_CONFIG_DESCRIPTOR(1, ITF_NUM_TOTAL, 0, TUD_CONFIG_DESC_LEN + TUD_MIDI_DESC_LEN, TUSB_DESC_CONFIG_ATT_REMOTE_WAKEUP, 100),

    // MIDI Interface
    TUD_MIDI_DESCRIPTOR(ITF_NUM_MIDI, 0, EPNUM_MIDI_OUT, EPNUM_MIDI_IN, 64)
};

// String Descriptors
char const* string_desc_arr[] = {
    (const char[]) {0x09, 0x04}, // English
    "PicoMIDI",                  // Manufacturer
    "MIDI Router",               // Product
    "123456",                    // Serial
};

uint8_t const * tud_descriptor_device_cb(void) {
    return (uint8_t const *) &desc_device;
}

uint8_t const * tud_descriptor_configuration_cb(uint8_t index) {
    (void)index;
    return desc_configuration;
}

uint16_t const* tud_descriptor_string_cb(uint8_t index, uint16_t langid) {
    (void)langid;
    static uint16_t desc_str[32];
    
    if (index == 0) {
        memcpy(&desc_str[1], string_desc_arr[0], 2);
        desc_str[0] = (TUSB_DESC_STRING << 8) | 0x09;
    } else {
        const char* str = string_desc_arr[index];
        uint8_t len = strlen(str);
        
        for (uint8_t i = 0; i < len; i++) {
            desc_str[1 + i] = str[i];
        }
        
        desc_str[0] = (TUSB_DESC_STRING << 8) | (2*len + 2);
    }
    
    return desc_str;
}
