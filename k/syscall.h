#ifndef SYSCALL_H_
#define SYSCALL_H_


#ifndef __ASSEMBLER__
#include "idt.h"
typedef u32 (*syscall_handler_t) (struct idt_registers *regs);
#define MAX_SYSCALL 0xff
#define SYSCALL_INTERRUPT 0x80
void set_syscalls();
void set_syscall_handler(u8 syscall, syscall_handler_t handler, syscall_handler_t *old);
#endif


#endif