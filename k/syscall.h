#ifndef SYSCALL_H_
#define SYSCALL_H_

#include "k/types.h"

#define MAX_SYSCALL		0xff
#define SYSCALL_INTERRUPT	0x80

typedef u32 (*syscall_handler_t) (struct x86_registers *regs);

void set_syscalls();
void set_syscall_handler(u8 syscall, syscall_handler_t handler, syscall_handler_t *old);

#endif