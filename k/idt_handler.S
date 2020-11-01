#include "idt.h"

.text
.type   general_handler, @function
general_handler:
	add %esp, (%esp)

	pushl %esp
	pushl %ebp
	pushl %edi
	pushl %esi
	pushl %edx
	pushl %ecx
	pushl %ebx
	pushl %eax

	pushw %gs
	pushw %fs
	pushw %es
	pushw %ss
	pushw %ds
	pushw %cs

	push %esp
	call interrupt_handler
	pop %esp
	add $2, %esp # Drop cs
	popw %ds
	popw %ss
	popw %es
	popw %fs
	popw %gs

	popl %eax
	popl %ebx
	popl %ecx
	popl %edx
	popl %esi
	popl %edi
	popl %ebp
	add $4, %esp # %esp # Drop esp
	popl %esp
	iret

.macro interrupt_handler_error nb
	pushl \nb
	pushl $0x8
	jmp general_handler;
.endm

.macro interrupt_handler_noerror nb
	pushl $0x0
	pushl \nb
	pushl $0xC
	jmp general_handler;
.endm

#define IDT_NO_ERROR interrupt_handler_noerror
#define IDT_ERROR interrupt_handler_error
#define IDT_FULL_ENTRY(nb, handler, str) \
	.align ISR_ALIGN; \
	.section .text; \
	.global interrupt_handler_##nb; \
	.type interrupt_handler_##nb, @function; \
interrupt_handler_##nb:	\
	handler $##nb;
#include "idt_table.h"
#undef IDT_FULL_ENTRY


