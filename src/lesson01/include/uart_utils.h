#ifndef _UART_UTILS_H
#define _UART_UTILS_H

#ifdef UART
#define SYSTEM_CLOCK_FREQ 48000000
#else 
#define SYSTEM_CLOCK_FREQ 250000000
#endif

void reset_pull_up_down(unsigned int);
void set_alt_for_gpio_14_15(int);
void set_baudrate_reg(unsigned int, int);

#endif