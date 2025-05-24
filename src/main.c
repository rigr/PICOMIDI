#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "tusb.h"
#include "usb_midi_host.h"
#include "din_midi.h"
#include "midi_router.h"
#include "config.h"

void core1_entry() {
    while (true) {
        usb_midi_host_task();
        din_midi_task();
        midi_router_task();
        sleep_us(100);
    }
}

int main() {
    stdio_init_all();
    
    // Wait for USB to initialize
    while (!tud_connected()) {
        sleep_ms(100);
    }

    usb_midi_host_init();
    din_midi_init();
    midi_router_init();
    
    multicore_launch_core1(core1_entry);
    
    while (true) {
        tud_task();
    }
    
    return 0;
}
