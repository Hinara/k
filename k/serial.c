#include "k/compiler.h"
#include "uart.h"
#include "k/types.h"
#include "io.h"

#ifndef BAUDRATE
#define BAUDRATE 38400
#endif 

static void set_baudrate(u16 com, u16 baudrate) {
	u32 baudrate_value = UART_BASEBAUDRATE / baudrate;
	outb(com + UART_LCR_OFFSET, inb(com + UART_LCR_OFFSET) | LCR_DLAB_ON);
	outb(com + UART_DLL_OFFSET, GET_U16_LSB(baudrate_value));
	outb(com + UART_DLM_OFFSET, GET_U16_MSB(baudrate_value));
	outb(com + UART_LCR_OFFSET, inb(com + UART_LCR_OFFSET) & !LCR_DLAB_ON);
}

__unused static u16 get_baudrate(u16 com) {
	u16 baudrate_value = 0;
	outb(com + UART_LCR_OFFSET, inb(com + UART_LCR_OFFSET) | LCR_DLAB_ON);
	baudrate_value = SET_U16_MSB_LSB(inb(com + UART_DLM_OFFSET), inb(com + UART_DLL_OFFSET));
	outb(com + UART_LCR_OFFSET, inb(com + UART_LCR_OFFSET) & !LCR_DLAB_ON);
	return (UART_BASEBAUDRATE / baudrate_value);
}

void init_serial(u16 com) {
	set_baudrate(com, BAUDRATE);
	outb(com + UART_LCR_OFFSET,
		LCR_8BITS |
		LCR_NOPARITY);
	outb(com + UART_FCR_OFFSET,
		FCR_ENABLE_FIFO |
		FCR_INTERRUPT_TRIGGER_14_BYTE |
		FCR_CLEAR_TRANSMIT_FIFO |
		FCR_CLEAR_RECEIVE_FIFO);
	outb(com + UART_IER_OFFSET, IER_RECEIVER_LINE_STATUS_REGISTER_CHANGE);
}

void send_com(u16 com, u8 value)
{
	outb(com + UART_THR_OFFSET, value);
}