#ifndef SERIAL_H_
#define SERIAL_H_

#include "k/types.h"

// COM Base addresses

#define COM1_BASE 0x3F8
#define COM2_BASE 0x2F8
#define COM3_BASE 0x3E8
#define COM4_BASE 0x2E8

void init_serial(u16 com);
void send_com(u16 com, u8 value);

#endif