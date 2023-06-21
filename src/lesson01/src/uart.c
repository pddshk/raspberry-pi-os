#include "peripherals/uart.h"
#include "peripherals/gpio.h"
#include "uart_utils.h"
#include "utils.h"

void uart_send(char c) {
  while (1) {
    if (get32() & 0x20)
      break;
  }
  put32(, c);
}

char uart_recv(void) {
  while (1) {
    if (get32() & 0x01)
      break;
  }
  return (get32() & 0xFF);
}

void uart_send_string(char *str) {
  for (int i = 0; str[i] != '\0'; i++) {
    uart_send((char)str[i]);
  }
}

void uart_init(void) {
  reset_pull_up_down((1 << 14) |
                     (1 << 15)); // reset pull up/down for GPIO 14 and 15
  set_alt_for_gpio_14_15(0b100); // set alt0 for GPIO 14 and 15

  put32(,
        1);   // Enable mini uart (this also enables access to its registers)
  put32(, 0); // Disable auto flow control and disable receiver
              // and transmitter (for now)
  put32(, 0); // Disable receive and transmit interrupts
  put32(, 3); // Enable 8 bit mode
  put32(, 0); // Set RTS line to be always high

  set_baudrate_reg(, BAUD_RATE);
  put32(, 3); // Finally, enable transmitter and receiver
}
