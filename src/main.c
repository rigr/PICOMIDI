#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/gpio.h"
#include "tusb.h"
#include "usb_midi_host.h"
#include "din_midi.h"
#include "midi_router.h"

#define LED_PIN 25
static uint32_t last_activity_time = 0;

void core1_entry() {
    uint32_t last_blink = 0;
    bool led_state = false;
    
    while (true) {
        uint32_t now = to_ms_since_boot(get_absolute_time());
        
        if (tud_mounted()) {  // Check if USB is properly mounted
            // Solid on when properly connected
            gpio_put(LED_PIN, true);
            
            // Blink briefly on activity
            if ((now - last_activity_time) < 50) { // 50ms blink
                gpio_put(LED_PIN, !gpio_get(LED_PIN));
            }
        } else {
            // Slow blink (500ms) when not properly connected
            if ((now - last_blink) > 500) {
                gpio_put(LED_PIN, !gpio_get(LED_PIN));
                last_blink = now;
            }
        }
        
        sleep_ms(10);
    }
}

int main() {
    stdio_init_all();
    
    // Initialize LED
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, false);
    
    // Initialize all components
    tusb_init();
    usb_midi_host_init();
    din_midi_init();
    midi_router_init();
    
    multicore_launch_core1(core1_entry);
    
    while (true) {
        tud_task();  // Handle device tasks
        tuh_task();  // Handle host tasks
        
        // Update activity time if MIDI is active
        if (tud_midi_available() || usb_host_devices[0].connected || usb_host_devices[1].connected) {
            last_activity_time = to_ms_since_boot(get_absolute_time());
        }
    }
    
    return 0;
}
