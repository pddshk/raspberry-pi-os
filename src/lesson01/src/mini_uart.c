#include "utils.h"
#include "peripherals/mini_uart.h"
#include "peripherals/gpio.h"
#include "uart_utils.h"

void mini_uart_send(char c)
{
	while(1) {
		if(get32(AUX_MU_LSR_REG) & 0x20) 
			break;
	}
	put32(AUX_MU_IO_REG, c);
}

char mini_uart_recv(void)
{
	while(1) {
		if(get32(AUX_MU_LSR_REG) & 0x01) 
			break;
	}
	return(get32(AUX_MU_IO_REG) & 0xFF);
}

void mini_uart_send_string(char* str)
{
	for (int i = 0; str[i] != '\0'; i ++) {
		mini_uart_send((char)str[i]);
	}
}

void mini_uart_init(void)
{
	reset_pull_up_down((1<<14) | (1<<15));	// reset pull up/down for GPIO 14 and 15
	set_alt_for_gpio_14_15(0b010); 			// set alt5 for GPIO 14 and 15
	
	put32(AUX_ENABLES,1);                   //Enable mini uart (this also enables access to its registers)
	put32(AUX_MU_CNTL_REG,0);               //Disable auto flow control and disable receiver and transmitter (for now)
	put32(AUX_MU_IER_REG,0);                //Disable receive and transmit interrupts
	put32(AUX_MU_LCR_REG,3);                //Enable 8 bit mode
	put32(AUX_MU_MCR_REG,0);                //Set RTS line to be always high
	
	set_baudrate_reg(AUX_MU_BAUD_REG, BAUD_RATE);
	put32(AUX_MU_CNTL_REG,3);             	//Finally, enable transmitter and receiver
}
