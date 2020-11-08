#include "idt.h"

.text
.type   general_handler, @function
general_handler:
	add $-0x34, %esp
	movl %eax, 0x00(%esp)		# Fill EAX
	movl %ebx, 0x04(%esp)		# Fill EBX
	movl %ecx, 0x08(%esp)		# Fill ECX
	movl %edx, 0x0C(%esp)		# Fill EDX
	movl %esi, 0x10(%esp)		# Fill ESI
	movl %edi, 0x14(%esp)		# Fill EDI
	movl %ebp, 0x18(%esp)		# Fill EBP
	movl %esp, 0x1C(%esp)		# Fill ESP (WIP)

	movw 0x44(%esp), %ax		# Move CS to AX
	movw %ax, 0x20(%esp)		# Fill CS
	movw %ds, 0x22(%esp)		# Fill DS
	movw %ss, 0x24(%esp)		# Fill SS
	movw %es, 0x26(%esp)		# Fill ES
	movw %fs, 0x28(%esp)		# Fill FS
	movw %gs, 0x2A(%esp)		# Fill GS
	
	movl 0x3C(%esp), %eax		# Move EIP to EAX
	movl %eax, 0x2C(%esp)		# Fill EIP
	
	movl 0x44(%esp), %eax		# Move EFLAGS to EAX
	movl %eax, 0x30(%esp)		# Fill EFLAGS

	push %esp			# Push pointer of struct idt_params
	call interrupt_handler		# Call generic handler
	pop %esp			# Pop pointer of struct idt_params

	movl 0x30(%esp), %eax		# Move EFLAGS to EAX
	movl %eax, 0x44(%esp)		# Restore EFLAGS

	movl 0x2C(%esp), %eax		# Move EIP to EAX
	movl %eax, 0x3C(%esp)		# Restore EIP

	movw 0x2A(%esp), %gs		# Restore GS
	movw 0x28(%esp), %fs		# Restore FS
	movw 0x26(%esp), %es		# Restore ES
	movw 0x24(%esp), %ss		# Restore SS
	movw 0x22(%esp), %ds		# Restore DS
	movw 0x20(%esp), %ax		# Move CS to AX
	movw %ax, 0x44(%esp)		# Restore CS

	# movl 0x1C(%esp), %esp		# Restore ESP (WIP)
	movl 0x18(%esp), %ebp		# Restore EBP
	movl 0x14(%esp), %edi		# Restore EDI
	movl 0x10(%esp), %esi		# Restore ESI
	movl 0x0C(%esp), %edx		# Restore EDX
	movl 0x08(%esp), %ecx		# Restore ECX
	movl 0x04(%esp), %ebx		# Restore EBX
	movl 0x00(%esp), %eax		# Restore EAX

	add $0x3C, %esp			# Drop structure & interupt no & error code
	iret

.macro interrupt_handler_error nb
	pushl \nb
	jmp general_handler;
.endm

.macro interrupt_handler_noerror nb
	pushl $0x0
	pushl \nb
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
#include "idt_table.def"
#undef IDT_FULL_ENTRY


