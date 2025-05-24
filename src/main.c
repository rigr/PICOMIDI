#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "tusb.h"
#include "hardware/uart.h"
#include "hardware/irq.h"
#include "usb_midi_host.h"
#include "din_midi.h"
#include "midi_router.h"
#include "config.h"

// Core 1 handles all MIDI processing
void core1_entry() {
    while (true) {
        // Process USB host MIDI
        usb_midi_host_task();
        
        // Process DIN MIDI (interrupt-driven, but we might have background tasks)
        din_midi_task();
        
        // Handle any routing tasks
        midi_router_task();
        
        // Small delay to prevent core from spinning too fast
        sleep_us(100);
    }
}

int main() {
    // Initialize basic Pico functionality
    stdio_init_all();
    
    // Wait for USB to connect if we're debugging
#if LIB_PICO_STDIO_USB
    while (!tud_cdc_connected()) {
        sleep_ms(100);
    }
#endif

    // Initialize all MIDI subsystems
    usb_midi_host_init();
    din_midi_init();
    midi_router_init();
    
    // Launch MIDI processing on core 1
    multicore_launch_core1(core1_entry);
    
    // Core 0 handles USB device tasks
    while (true) {
        tud_task(); // TinyUSB device task
    }
    
    return 0;
}
