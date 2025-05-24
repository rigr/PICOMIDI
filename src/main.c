#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "tusb.h"
#include "usb_midi_host.h"
#include "din_midi.h"
#include "midi_router.h"

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
    
    // Initialize all components
    tusb_init();
    usb_midi_host_init();
    din_midi_init();
    midi_router_init();
    
    // Start processing on core 1
    multicore_launch_core1(core1_entry);
    
    // Core 0 handles USB tasks
    while (true) {
        tud_task(); // Device task
        tuh_task(); // Host task
    }
    
    return 0;
}
