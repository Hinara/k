#ifndef K_TYPES_H
#define K_TYPES_H

#include <stddef.h>

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned long long u64;
typedef signed long long s64;


struct x86_registers {
// General registers
	u32	eax;
	u32	ebx;
	u32	ecx;
	u32	edx;
	u32	esi;
	u32	edi;
	u32	ebp;
	u32	esp;
// Segment registers
	u16	cs;
	u16	ds;
	u16	ss;
	u16	es;
	u16	fs;
	u16	gs;
// Other registers
	u32	eip;
	u32	eflags;
};

#endif
