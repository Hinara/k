#include "idt.h"
#include "gdt.h"

#define IDT_FULL_ENTRY(nb, error, str) void interrupt_handler_##nb();
#include "idt_table.h"
#undef IDT_FULL_ENTRY

#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

#define IDT_DEFAULT_ATTRIBUTES (IDT_ATTRIBUTE_PRESENT | IDT_ATTRIBUTE_RING0 | \
				IDT_ATTRIBUTE_GATE_32INT)

const struct idt_base_entry interrupt_entries[] = {
	#define IDT_FULL_ENTRY(nb, error, str) {str, interrupt_handler_##nb, GDT_KERNEL_CS*8, IDT_DEFAULT_ATTRIBUTES },
	#include "idt_table.h"
	#undef IDT_FULL_ENTRY
};
u64 interrupt_table[ARRAY_SIZE(interrupt_entries)];
struct idt_ptr idt = {
	.len = sizeof(interrupt_table) - 1,
	.ptr = (u32) interrupt_table
};

int_handler int_handler_table[ARRAY_SIZE(interrupt_entries)];

void set_idt()
{
	for (u16 i = 0; i < ARRAY_SIZE(interrupt_entries); i++) {
		interrupt_table[i] = IDT_ENTRY(\
			(u32) interrupt_entries[i].handler, \
			interrupt_entries[i].selector, \
			interrupt_entries[i].attributes \
		);
		int_handler_table[i] = NULL;
	}
	asm volatile ("lidt (%0)" : /* No output */ : "a"(&idt) : "memory");
}


void interrupt_handler(struct idt_params *params)
{
#include <stdio.h>
	int_handler handler = int_handler_table[params->interrupt];

	if (handler != NULL) {
		handler(&params->regs, params->interrupt, params->code);
	} else {
		printf("IntNo\t%02x\r\n", params->interrupt);
		printf("ErrCode\t%08x\r\n", params->code);
		printf("eax\t%08x\r\n", params->regs.eax);
		printf("ebx\t%08x\r\n", params->regs.ebx);
		printf("ecx\t%08x\r\n", params->regs.ecx);
		printf("edx\t%08x\r\n", params->regs.edx);
		printf("esi\t%08x\r\n", params->regs.esi);
		printf("edi\t%08x\r\n", params->regs.edi);
		printf("ebp\t%08x\r\n", params->regs.ebp);
		printf("esp\t%08x\r\n", params->regs.esp);
		printf("CS\t%04x\r\n", params->regs.cs); // WRONG
		printf("DS\t%04x\r\n", params->regs.ds);
		printf("SS\t%04x\r\n", params->regs.ss);
		printf("ES\t%04x\r\n", params->regs.es);
		printf("FS\t%04x\r\n", params->regs.fs);
		printf("GS\t%04x\r\n", params->regs.gs);
		printf("eflags\t%08x\r\n", params->regs.eflags);
		printf("eip\t%08x\r\n", params->regs.eip);
	}
}

int register_handler(u32 interrupt, int_handler handler, int_handler *old)
{
	if (interrupt >= ARRAY_SIZE(interrupt_entries)) {
		return 1;
	}
	if (old != NULL) {
		*old = int_handler_table[interrupt];
	}
	int_handler_table[interrupt] = handler;
	return 0;
}