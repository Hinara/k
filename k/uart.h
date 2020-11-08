#ifndef UART_H_
#define UART_H_

// UART Offsets

#define UART_RBR_OFFSET 0x0
#define UART_THR_OFFSET 0x0
#define UART_IER_OFFSET 0x1
#define UART_IRR_OFFSET 0x2
#define UART_FCR_OFFSET 0x2
#define UART_LCR_OFFSET 0x3
#define UART_MCR_OFFSET 0x3
#define UART_DLL_OFFSET 0x0
#define UART_DLM_OFFSET 0x1
#define UART_LSR_OFFSET 0x5
#define UART_MSR_OFFSET 0x6
#define UART_SCR_OFFSET 0x7


// LCR
#define LCR_5BITS           (0b00 << 0)
#define LCR_6BITS           (0b01 << 0)
#define LCR_7BITS           (0b10 << 0)
#define LCR_8BITS           (0b11 << 0)

#define LCR_1STOPBIT        (0b0 << 2)
#define LCR_1_5STOPBIT      (0b1 << 2)
#define LCR_2STOPBIT        (0b1 << 2)

#define LCR_NOPARITY        (0b000 << 3)
#define LCR_ODDPARITY       (0b001 << 3)
#define LCR_EVENPARITY      (0b011 << 3)
#define LCR_HIGHPARITY      (0b101 << 3)
#define LCR_LOWPARITY       (0b111 << 3)

#define LCR_BREAKSIGNAL_OFF (0b0 << 6)
#define LCR_BREAKSIGNAL_ON  (0b1 << 6)

#define LCR_DLAB_ON         (0b1 << 7)
#define LCR_DLAB_OFF        (0b0 << 7)

#define LCR_DLAB_RBR_THR_IER LCR_DLAB_OFF
#define LCR_DLAB_DLL_DLM LCR_DLAB_ON

// IER
#define IER_RECEIVE_DATA_AVAILABLE                  0x0
#define IER_TRANSMITTER_HOLDING_REGISTER_EMPTY      0x1
#define IER_RECEIVER_LINE_STATUS_REGISTER_CHANGE    0x2
#define IER_MODEM_STATUS_REGISTER_CHANGE            0x3
#define IER_SLEEP_MODE                              0x4
#define IER_LOW_POWER_MODE                          0x5

// FCR
#define FCR_DISABLE_FIFO                (0b0 << 0)
#define FCR_ENABLE_FIFO                 (0b1 << 0)
#define FCR_CLEAR_RECEIVE_FIFO          (0b1 << 1)
#define FCR_CLEAR_TRANSMIT_FIFO         (0b1 << 2)
#define FCR_SELECT_DMA_MODE_0           (0b0 << 3)
#define FCR_SELECT_DMA_MODE_1           (0b1 << 3)
#define FCR_64_BYTE_FIFO                (0b1 << 5)
#define FCR_INTERRUPT_TRIGGER_1_BYTE    (0b00 << 6)
#define FCR_INTERRUPT_TRIGGER_4_BYTE    (0b01 << 6)
#define FCR_INTERRUPT_TRIGGER_8_BYTE    (0b10 << 6)
#define FCR_INTERRUPT_TRIGGER_14_BYTE   (0b11 << 6)


#define UART_BASEBAUDRATE 115200

#endif