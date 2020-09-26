
#include <stddef.h>
#include <stdbool.h>
#include "io.h"
#include "uart.h"

#define ENTRYSIZE(x) (sizeof(*x) / sizeof(x))

#ifndef BAUDRATE
#define BAUDRATE 38400
#endif 

void set_baudrate(u16 com, u32 baudrate) {
    u32 baudrate_value = UART_BASEBAUDRATE / baudrate;
    outb(com + UART_LCR_OFFSET, inb(com + UART_LCR_OFFSET) | LCR_DLAB_ON);
    outb(com + UART_DLL_OFFSET, (baudrate_value >> 0) & 0xFF);
    outb(com + UART_DLM_OFFSET, (baudrate_value >> 8) & 0xFF);
    outb(com + UART_LCR_OFFSET, inb(com + UART_LCR_OFFSET) & !LCR_DLAB_ON);
}
u32 get_baudrate(u16 com) {
    u32 baudrate_value = 0;
    outb(com + UART_LCR_OFFSET, inb(com + UART_LCR_OFFSET) | LCR_DLAB_ON);
    baudrate_value |= inb(com + UART_DLL_OFFSET) << 0;
    baudrate_value |= inb(com + UART_DLM_OFFSET) << 8;
    outb(com + UART_LCR_OFFSET, inb(com + UART_LCR_OFFSET) & !LCR_DLAB_ON);
    return UART_BASEBAUDRATE / baudrate_value;
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

int write(const char *buf, size_t size) {
    const u16 com = COM1_BASE;
    size_t count = 0;
    static bool init = false;
    if (init == false) {
        init_serial(com);
        init = true;
    }
    while (count < size) {
        outb(com + UART_THR_OFFSET, buf[count]);
        count += 1;
    }
    return count;
}
