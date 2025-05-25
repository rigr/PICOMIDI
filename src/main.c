#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/gpio.h"
#include "tusb.h"
#include "usb_midi_host.h"
#include "din_midi.h"
#include "midi_router.h"

#define LED_PIN 25
bool led_state = false;
uint32_t last_activity_time = 0;

// LED task runs on core1
void core1_entry() {
    uint32_t last_blink = 0;
    while (true) {
        uint32_t now = to_ms_since_boot(get_absolute_time());
        
        // Solid on when connected
        if (tud_connected()) {
            gpio_put(LED_PIN, true);
            
            // Blink on activity
            if ((now - last_activity_time) < 50) { // 50ms blink on activity
                gpio_put(LED_PIN, !gpio_get(LED_PIN));
            }
        } else {
            // Slow blink when not connected
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
    
    // Initialize all MIDI components
    tusb_init();
    usb_midi_host_init();
    din_midi_init();
    midi_router_init();
    
    // Start LED task on core1
    multicore_launch_core1(core1_entry);
    
    // Core0 handles USB tasks
    while (true) {
        tud_task();
        tuh_task();
        
        // Update activity time if MIDI is active
        if (tud_midi_available() || tuh_midi_configured()) {
            last_activity_time = to_ms_since_boot(get_absolute_time());
        }
    }
    
    return 0;
}
