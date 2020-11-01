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

#include <stdio.h>
void print_u64(u64 n) {
	u32 high = (n >> 32) & 0xFFFFFFFF;
	u32 down = n & 0xFFFFFFFF;
	printf("(%08x%08x)\r\n", high, down);
}
void set_idt() {
	for (u16 i = 0; i < ARRAY_SIZE(interrupt_entries); i++) {
		interrupt_table[i] = IDT_ENTRY( \
			(u32) interrupt_entries[i].handler, \
			interrupt_entries[i].selector, \
			interrupt_entries[i].attributes \
		);
		print_u64(interrupt_table[i]);
	}
	asm volatile ("lidt (%0)" : /* No output */ : "a"(&idt) : "memory");
}

#include <stdio.h>

struct idt_registers {
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

} __attribute__((packed));

struct idt_params {
	struct idt_registers regs;
	u32 interrupt;
	u32 code;
};

void interrupt_handler(struct idt_params *params) {
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
	printf("CS\t%04x\r\n", params->regs.cs);
	printf("DS\t%04x\r\n", params->regs.ds);
	printf("SS\t%04x\r\n", params->regs.ss);
	printf("ES\t%04x\r\n", params->regs.es);
	printf("FS\t%04x\r\n", params->regs.fs);
	printf("GS\t%04x\r\n", params->regs.gs);
	printf("eflags\t%08x\r\n", params->regs.eflags);
	printf("eip\t%08x\r\n", params->regs.eip);
}