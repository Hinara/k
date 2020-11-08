#ifndef COMPILER_H
#define COMPILER_H

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#define __packed __attribute__((__packed__))
#define __unused __attribute__((unused))
#define ALIGN_UP(addr, bytes) (((addr) + (bytes) - 1) & ~((bytes) - 1))
#define GET_U16_MSB(x) ((x >> 8) & 0xff)
#define GET_U16_LSB(x) ((x >> 0) & 0xff)
#define SET_U16_MSB(x) ((x << 8) & 0xff00)
#define SET_U16_LSB(x) ((x << 0) & 0x00ff)
#define SET_U16_MSB_LSB(lsb, msb) (SET_U16_MSB(msb) | SET_U16_LSB(lsb))
#endif
