#include "din_midi.h"
#include "midi_router.h"
#include "hardware/uart.h"
#include "hardware/irq.h"
#include "hardware/gpio.h"

#define NUM_DIN_PORTS 3

static uart_inst_t* din_uart[NUM_DIN_PORTS] = {uart0, uart1, uart0}; // Adjust based on your wiring
static uint din_tx_pin[NUM_DIN_PORTS] = {0, 4, 8}; // Example pins
static uint din_rx_pin[NUM_DIN_PORTS] = {1, 5, 9}; // Example pins

static void din_midi_irq_handler(uint port_index) {
    while (uart_is_readable(din_uart[port_index])) {
        uint8_t ch = uart_getc(din_uart[port_index]);
        midi_router_route(SOURCE_DIN_IN1 + port_index, &ch, 1);
    }
}

static void din_midi0_irq_handler(void) {
    din_midi_irq_handler(0);
}

static void din_midi1_irq_handler(void) {
    din_midi_irq_handler(1);
}

static void din_midi2_irq_handler(void) {
    din_midi_irq_handler(2);
}

void din_midi_init(void) {
    for (int i = 0; i < NUM_DIN_PORTS; i++) {
        uart_init(din_uart[i], 31250); // MIDI standard baud rate
        gpio_set_function(din_tx_pin[i], GPIO_FUNC_UART);
        gpio_set_function(din_rx_pin[i], GPIO_FUNC_UART);
        
        // Set up interrupts
        switch (i) {
            case 0:
                uart_set_irq_enables(din_uart[i], true, false);
                irq_set_exclusive_handler(UART0_IRQ, din_midi0_irq_handler);
                irq_set_enabled(UART0_IRQ, true);
                break;
            case 1:
                uart_set_irq_enables(din_uart[i], true, false);
                irq_set_exclusive_handler(UART1_IRQ, din_midi1_irq_handler);
                irq_set_enabled(UART1_IRQ, true);
                break;
            case 2:
                // You might need to use PIO for a third UART
                break;
        }
    }
}

void din_midi_task(void) {
    // Background processing if needed
}

void din_midi_send(uint8_t port, const uint8_t* data, size_t length) {
    for (size_t i = 0; i < length; i++) {
        uart_putc(din_uart[port], data[i]);
    }
}
