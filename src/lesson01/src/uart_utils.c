#include "uart_utils.h"
#include "peripherals/gpio.h"
#include "utils.h"

void reset_pull_up_down(unsigned int bitmask)
{
	put32(GPPUD, 0);
	delay(150);
	put32(GPPUDCLK0, bitmask);
	delay(150);
	put32(GPPUDCLK0, 0);
}

void set_alt_for_gpio_14_15(int code)
{
	unsigned int selector;

	selector = get32(GPFSEL1);
	selector &= ~(7<<12);                  // clean gpio14
	selector |= code << 12;                // set code for gpio14
	selector &= ~(7<<15);                  // clean gpio15
	selector |= code << 15;                // set code for gpio15
	put32(GPFSEL1, selector);
}

void set_baudrate_reg(unsigned int baudrate_reg, int baudrate)
{
	unsigned int value = -1 + SYSTEM_CLOCK_FREQ/(8 * baudrate);
	put32(baudrate_reg, value);
}