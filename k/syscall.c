#include "syscall.h"
#include "k/kstd.h"
#include "k/compiler.h"
#include "idt.h"

static syscall_handler_t syscall_handler_table[MAX_SYSCALL];

static void syscall_handler(struct x86_registers *regs, u32 interrupt, u32 code)
{
	(void) code;
	(void) interrupt;
	syscall_handler_t handler;
	u32 syscall = regs->eax;

	if (syscall >= MAX_SYSCALL) {
		regs->eax = -ENOSYS;
		return;
	}
	handler = syscall_handler_table[syscall];
	if (handler == NULL) {
		regs->eax = -ENOSYS;
		return;
	}
	regs->eax = handler(regs);
}

void set_syscalls()
{
	for (u32 i = 0; i < MAX_SYSCALL; i++) {
		syscall_handler_table[i] = NULL;
	}
	register_handler(SYSCALL_INTERRUPT, syscall_handler, NULL);
}

void set_syscall_handler(u8 syscall, syscall_handler_t handler, syscall_handler_t *old)
{
	if (syscall >= ARRAY_SIZE(syscall_handler_table)) {
		return;
	}
	if (old != NULL) {
		*old = syscall_handler_table[syscall];
	}
	syscall_handler_table[syscall] = handler;
}